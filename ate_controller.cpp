#include "ate_controller.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

// === 1. 单例初始化 ===
// CsvConfigManager 饿汉式单例初始化
CsvConfigManager CsvConfigManager::m_instance;

// AteTestController 懒汉式单例初始化
AteTestController* AteTestController::m_instance = nullptr;
mutex AteTestController::m_mutex;

// === 2. AteTestController 工具函数实现 ===
string AteTestController::trim(const string& str) {
    auto start = str.begin();
    while (start != str.end() && isspace(static_cast<unsigned char>(*start))) start++;
    auto end = str.end();
    do { end--; } while (distance(start, end) > 0 && isspace(static_cast<unsigned char>(*end)));
    return string(start, end + 1);
}

vector<string> AteTestController::splitCSVLine(const string& line) {
    vector<string> fields;
    string currentField;
    bool inQuotes = false;

    for (char c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        }
        else if (c == ',' && !inQuotes) {
            fields.push_back(trim(currentField));
            currentField.clear();
        }
        else {
            currentField += c;
        }
    }
    fields.push_back(trim(currentField));
    return fields;
}

int AteTestController::hexToInt(const string& hexStr, bool& isCare) {
    string str = trim(hexStr);
    if (str == "XCARE" || str.empty()) {
        isCare = true;
        return 0;
    }
    isCare = false;
    if (str.substr(0, 2) == "0x" || str.substr(0, 2) == "0X") str = str.substr(2);

    stringstream ss;
    ss << hex << str;
    int value;
    ss >> value;
    if (ss.fail()) throw invalid_argument("无效Hex: " + hexStr);
    return value;
}

int AteTestController::strToInt(const string& str, bool& isCare) {
    string trimmed = trim(str);
    if (trimmed == "XCARE" || trimmed.empty()) {
        isCare = true;
        return 0;
    }
    isCare = false;
    stringstream ss(trimmed);
    int value;
    ss >> value;
    if (ss.fail()) throw invalid_argument("无效整数: " + str);
    return value;
}

double AteTestController::strToDouble(const string& str, bool& isCare) {
    string trimmed = trim(str);
    if (trimmed == "XCARE" || trimmed.empty()) {
        isCare = true;
        return 0.0;
    }
    isCare = false;
    stringstream ss(trimmed);
    double value;
    ss >> value;
    if (ss.fail()) throw invalid_argument("无效浮点数: " + str);
    return value;
}

// === 3. AteTestController 核心功能实现 ===
bool AteTestController::loadParameters() {
    // 从单例配置管理器获取CSV路径
    string csvPath = CsvConfigManager::getInstance().getCsvPath();
    cout << "[信息] 从单例配置加载CSV路径: " << csvPath << endl;

    ifstream file(csvPath);
    if (!file.is_open()) {
        cerr << "[错误] 无法打开文件: " << csvPath << endl;
        return false;
    }

    m_testItems.clear();
    string line;
    bool isFirstLine = true;

    while (getline(file, line)) {
        if (line.empty() || isFirstLine) {
            isFirstLine = false;
            continue;
        }

        try {
            vector<string> fields = splitCSVLine(line);
            if (fields.size() < 26) {
                cerr << "[警告] 列数不足，跳过行: " << line << endl;
                continue;
            }

            TestItem item;
            bool tempCare;

            item.No = strToInt(fields[0], tempCare);
            item.CPTestItem = fields[1];
            item.supply.Vaa = strToDouble(fields[2], item.supply.isVaaCare);
            item.supply.Vhh = strToDouble(fields[3], item.supply.isVhhCare);
            item.clock.TesterClock_ns = strToInt(fields[4], tempCare);

            if (fields[5] == "Mode0") item.clock.SCK_Mode = SCKMode::MODE0;
            else if (fields[5] == "Mode1") item.clock.SCK_Mode = SCKMode::MODE1;
            else item.clock.SCK_Mode = SCKMode::UNKNOWN;

            item.CregConfigFile = fields[6];
            item.MemoryDataInput = fields[7];
            item.SaveToFile = fields[8];
            item.dac.FirstDAC = hexToInt(fields[9], item.dac.isDACCare);
            item.dac.LastDAC = hexToInt(fields[10], item.dac.isDACCare);
            item.dac.DACStep = hexToInt(fields[11], item.dac.isDACCare);
            item.RegisterAddress = hexToInt(fields[12], tempCare);
            item.SolidData = hexToInt(fields[13], tempCare);
            item.FirstPageAddress = hexToInt(fields[14], tempCare);
            item.PageLength = strToInt(fields[15], tempCare);
            item.CycleNumber = strToInt(fields[16], tempCare);
            item.limits.TFB_Limit = strToInt(fields[17], item.limits.isLimitsCare);
            item.limits.DFB_Limit = strToInt(fields[18], item.limits.isLimitsCare);
            item.limits.DCHighLimit = strToInt(fields[19], item.limits.isLimitsCare);
            item.limits.DCLowLimit = strToInt(fields[20], item.limits.isLimitsCare);
            item.ArchivePoint = hexToInt(fields[21], tempCare);

            if (fields[22] == "Mode0") item.clock.SCK_Mode = SCKMode::MODE0;
            else if (fields[22] == "Mode1") item.clock.SCK_Mode = SCKMode::MODE1;
            else item.clock.SCK_Mode = SCKMode::UNKNOWN;

            item.clock.WaitDummy = strToInt(fields[23], item.clock.isWaitDummyCare);
            item.FailBin = strToInt(fields[24], tempCare);
            item.logCtrl = (fields[25] == "ON") ? LogControl::ON : LogControl::OFF;

            m_testItems.push_back(item);
        }
        catch (const exception& e) {
            cerr << "[错误] 解析失败: " << e.what() << " | 行: " << line << endl;
            continue;
        }
    }

    file.close();
    cout << "[信息] 成功加载 " << m_testItems.size() << " 个测试项" << endl;
    return !m_testItems.empty();
}

void AteTestController::runSingleTest(size_t index) {
    if (index >= m_testItems.size()) {
        cerr << "[错误] 测试项索引超出范围" << endl;
        return;
    }

    if (!m_hardware || !m_isInitialized) {
        cerr << "[错误] 硬件未初始化" << endl;
        return;
    }

    const TestItem& item = m_testItems[index];
    cout << "\n=== 执行测试项 [" << index << "] " << item.CPTestItem << " ===" << endl;

    if (m_hardware->configure(item)) {
        AteTestResult result = m_hardware->runTest(item);
        cout << "[结果] " << (result == AteTestResult::PASS ? "PASS" : "FAIL") << endl;
    }
    else {
        cerr << "[错误] 配置失败" << endl;
    }
}

void AteTestController::runBatchTests() {
    if (!m_hardware || !m_isInitialized) {
        cerr << "[错误] 硬件未初始化" << endl;
        return;
    }

    cout << "\n=== 开始批量测试 (总计: " << m_testItems.size() << " 项) ===" << endl;
    int pass = 0, fail = 0;

    for (size_t i = 0; i < m_testItems.size(); ++i) {
        try {
            const TestItem& item = m_testItems[i];
            cout << "\n--- 测试项 " << i + 1 << "/" << m_testItems.size() << ": " << item.CPTestItem << " ---" << endl;

            if (m_hardware->configure(item)) {
                AteTestResult res = m_hardware->runTest(item);
                if (res == AteTestResult::PASS) pass++;
                else fail++;
            }
            else {
                fail++;
            }
        }
        catch (const exception& e) {
            fail++;
            cerr << "[异常] " << e.what() << endl;
        }
    }

    cout << "\n=== 批量测试完成 ===" << endl;
    cout << "通过: " << pass << " | 失败: " << fail << " | 通过率: "
        << fixed << setprecision(2) << (static_cast<double>(pass) / (pass + fail)) * 100 << "%" << endl;
}

// === 4. 示例模拟器实现 ===
bool AteSimulator::init() {
    cout << "[ATE-Sim] 硬件初始化成功" << endl;
    return true;
}

bool AteSimulator::configure(const TestItem& item) {
    cout << "[ATE-Sim] 配置 Vaa=" << (item.supply.isVaaCare ? "XCARE" : to_string(item.supply.Vaa));
    cout << " | Clock=" << item.clock.TesterClock_ns << "ns";
    cout << " | FailBin=" << item.FailBin << endl;
    return true;
}

AteTestResult AteSimulator::runTest(const TestItem& item) {
    return (item.FailBin >= 0) ? AteTestResult::PASS : AteTestResult::FAIL;
}

void AteSimulator::close() {
    cout << "[ATE-Sim] 硬件已关闭" << endl;
}