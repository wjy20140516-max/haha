#ifndef ATE_CONTROLLER_H
#define ATE_CONTROLLER_H

#include <vector>
#include <string>
#include <stdexcept>
#include <mutex>
#include <map>

// === 枚举类型定义 ===
enum class IOMode { MODE0, MODE1, MODE2, UNKNOWN };
enum class SCKMode { MODE0, MODE1, MODE2, UNKNOWN };
enum class LogControl { ON, OFF };
enum class AteTestResult { PASS, FAIL, ERROR };

// === 子参数结构体 ===
struct SupplyVoltage {
    double Vaa = 0.0;
    double Vhh = 0.0;
    bool isVaaCare = true;
    bool isVhhCare = true;
};

struct ClockSettings {
    int TesterClock_ns = 0;
    SCKMode SCK_Mode = SCKMode::UNKNOWN;
    int WaitDummy = 0;
    bool isWaitDummyCare = true;
};

struct DACConfig {
    int FirstDAC = 0;
    int LastDAC = 0;
    int DACStep = 0;
    bool isDACCare = true;
};

struct TestLimits {
    int TFB_Limit = 0;
    int DFB_Limit = 0;
    int DCHighLimit = 0;
    int DCLowLimit = 0;
    bool isLimitsCare = true;
};

// === 完整测试项结构体 ===
struct TestItem {
    int No = 0;
    std::string CPTestItem;
    SupplyVoltage supply;
    ClockSettings clock;
    DACConfig dac;
    std::string CregConfigFile;
    std::string MemoryDataInput;
    std::string SaveToFile;
    int RegisterAddress = 0;
    int SolidData = 0;
    int FirstPageAddress = 0;
    int PageLength = 0;
    int CycleNumber = 0;
    TestLimits limits;
    int ArchivePoint = 0;
    int FailBin = -1;
    LogControl logCtrl = LogControl::OFF;
};

// === 1. CSV配置管理器（饿汉式单例）===
// 负责管理全局唯一的CSV路径和配置
class CsvConfigManager {
private:
    // 私有构造函数：禁止外部创建
    CsvConfigManager() {
        // 固定CSV路径（可替换为你的实际路径）
       // m_csvPath = "/mnt/TJ_CP_K8k_Development_validation_flow_V0.csv";
        m_csvPath = "CommRes/data/TJ_CP_K8k_Development_validation_flow_V0.csv";
        // 可扩展其他全局配置
        m_logPath = "./test_logs/";
    }

    // 禁用拷贝和赋值
    CsvConfigManager(const CsvConfigManager&) = delete;
    CsvConfigManager& operator=(const CsvConfigManager&) = delete;

    // 静态私有实例（饿汉式：程序启动即初始化）
    static CsvConfigManager m_instance;

    // 配置参数
    std::string m_csvPath;
    std::string m_logPath;

public:
    // 全局访问点：获取唯一实例
    static CsvConfigManager& getInstance() {
        return m_instance;
    }

    // 获取CSV路径
    std::string getCsvPath() const {
        return m_csvPath;
    }

    // 获取日志路径
    std::string getLogPath() const {
        return m_logPath;
    }

    // 扩展：修改CSV路径（如需动态调整）
    void setCsvPath(const std::string& path) {
        m_csvPath = path;
    }
};

// === 2. ATE硬件接口类（纯虚接口）===
class AteHardwareInterface {
public:
    virtual ~AteHardwareInterface() = default;
    virtual bool init() = 0;
    virtual bool configure(const TestItem& item) = 0;
    virtual AteTestResult runTest(const TestItem& item) = 0;
    virtual void close() = 0;
};

// === 3. ATE测试控制器（懒汉式单例）===
// 全局唯一的测试控制器，管理测试流程和硬件接口
class AteTestController {
private:
    // 私有构造函数：禁止外部创建
    AteTestController() : m_hardware(nullptr), m_isInitialized(false) {}

    // 禁用拷贝和赋值
    AteTestController(const AteTestController&) = delete;
    AteTestController& operator=(const AteTestController&) = delete;

    // 静态私有实例（懒汉式：按需创建）
    static AteTestController* m_instance;
    static std::mutex m_mutex; // 线程安全锁

    // 成员变量
    AteHardwareInterface* m_hardware;
    std::vector<TestItem> m_testItems;
    bool m_isInitialized;

    // 内部工具函数
    std::string trim(const std::string& str);
    std::vector<std::string> splitCSVLine(const std::string& line);
    int hexToInt(const std::string& hexStr, bool& isCare);
    int strToInt(const std::string& str, bool& isCare);
    double strToDouble(const std::string& str, bool& isCare);

public:
    // 全局访问点：获取唯一实例（双重检查锁定，线程安全）
    static AteTestController& getInstance() {
        if (m_instance == nullptr) {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_instance == nullptr) {
                m_instance = new AteTestController();
            }
        }
        return *m_instance;
    }

    // 设置硬件接口（仅初始化一次）
    void setHardware(AteHardwareInterface* hardware) {
        if (m_isInitialized) {
            throw std::runtime_error("控制器已初始化，无法修改硬件接口");
        }
        if (!hardware) {
            throw std::invalid_argument("硬件接口指针不能为空");
        }
        m_hardware = hardware;
    }

    // 加载CSV参数（使用单例配置管理器的路径）
    bool loadParameters();

    // 执行测试
    void runSingleTest(size_t index);
    void runBatchTests();

    // 获取测试项数量
    size_t getTestItemCount() const { return m_testItems.size(); }

    // 初始化硬件
    bool initHardware() {
        if (!m_hardware) {
            throw std::runtime_error("未设置硬件接口");
        }
        m_isInitialized = m_hardware->init();
        return m_isInitialized;
    }

    // 关闭硬件
    void closeHardware() {
        if (m_hardware && m_isInitialized) {
            m_hardware->close();
            m_isInitialized = false;
        }
    }
};

// === 4. 示例硬件实现（模拟器）===
class AteSimulator : public AteHardwareInterface {
public:
    bool init() override;
    bool configure(const TestItem& item) override;
    AteTestResult runTest(const TestItem& item) override;
    void close() override;
};

#endif // ATE_CONTROLLER_H