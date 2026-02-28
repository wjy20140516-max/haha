#include "interface/ONESInterfaceHeader.h"
#include "TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS -- started");
    //std::string test_num = "1290";
    //std::string cp_ver = "Taiji1p8_CP_ProductionFlow_V1p1";
    //std::string lotnum = "B550064";
    //std::string wafernum = "B550064-14";
    //int Die_X = 0;
    //int Die_Y = 0;
    //std::string testname;
    std::string Cfg_Filename;
    int Mbist_Start_Page;
    int Mbist_Pages;
    int TFB_Limit;
    int DFB_Limit;
    int Archive_Point;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("Page_Length", theParameter))
    {
    Mbist_Pages = theParameter->GetValueAsInt();
    //Print("Page_Length =%d", Page_Length);
    }
    if (theParameters->TryGetParameter("1st_Page_Addressain", theParameter))
    {
    string pa = theParameter->GetValueAsString();
    //Print("1st_Page_Addressain s= %s", pa.c_str());
    Mbist_Start_Page = std::stoi(pa.c_str(), nullptr, 16);
    //Print("1st_Page_Addressain = %d(dec) 0x%04x(hex)   ", Mbist_Start_Page, Mbist_Start_Page);
    }
    if (theParameters->TryGetParameter("TFB_Limit", theParameter))
    {
    TFB_Limit = theParameter->GetValueAsInt();
    //Print("TFB_Limit =%d", TFB_Limit);
    }
    if (theParameters->TryGetParameter("DFB_Limit", theParameter))
    {
    DFB_Limit = theParameter->GetValueAsInt();
    //Print("DFB_Limit =%d", DFB_Limit);
    }
    if (theParameters->TryGetParameter("Archive_Point", theParameter))
    {
    string pa = theParameter->GetValueAsString();
    Archive_Point = std::stoi(pa.c_str(), nullptr, 16);
    //Print("Archive_Point = %d(dec) 0x%04x(hex)   ", Archive_Point, Archive_Point);
    }
    Cfg_Filename = "TJ_CFG_DEMO.txt";
    // AutoMation
    #ifdef RRAM_B2_AUTOMATION
    std::string logName = log_name_setting(aContext, lotnum, wafernum, Die_X, Die_Y, testname);
    #else
    std::string logName = log_name_setting(aContext, testname);
    #endif
    // Log Head Info
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    TRegWrite(0x03, 0x40);
    if (TURN_ON_TR_VFY)
    {
    int TReg_ReadData[MAX_DUTS] = { 0 };
    TRegRead(aContext, 0x03, TReg_ReadData);
    DUT_LOOP_START
    if (TURN_ON_TR_BIN)
    {
    if (TReg_ReadData[dutz] != 0x40)
    {
    Print("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", 0x03, TReg_ReadData[dutz]);
    //testlog.Info("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", 0x03, TReg_ReadData[dutz]);
    (*item)->SetValue(1);
    TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS_1290[dut-1] = 1;
    }
    }
    }
    DUT_LOOP_END
    // Step1 update CRS array
    // Step2 OverWrite CRS onto chips
    std::vector<unsigned int> cfgReg(CFG_FILE_LENGTH, 0);
    LoadConfigFileBySo(aContext, Cfg_Filename, CFG_FILE_LENGTH, cfgReg.data(), Archive_Point, true);
    //Print("3333333");
    auto start = std::chrono::high_resolution_clock::now();
    ReadConfigFile(aContext);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm = end - start;
    Print("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- cfg read  cost %.6f second", tm.count() / 1000);
    //testlog.Info("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- cfg read  cost {:.6f} second", tm.count() / 1000);
    // Step3 read memory and get total error bit count
    int Mbist_Page_Bytes = MBIST_READ_DDW_PAGE;
    int Read_Bytes = Mbist_Pages * MBIST_READ_DDW_PAGE;
    auto start1 = std::chrono::high_resolution_clock::now();
    // RRAM_TJ::MbistReadDDW(Mbist_Start_Page,Mbist_Pages);
    //MemMainReadDDW(Mbist_Start_Page, Mbist_Pages * 0xC0);
    MemMainReadDDW_All(0x00, Mbist_Start_Page, Mbist_Pages, Mbist_Page_Bytes);
    // Step3 Data Check
    std::vector<uint> Data(Read_Bytes, 0);
    std::vector<int> error_bfr(Read_Bytes, 0);
    std::vector<std::vector<int>> All_DUTs_Date(MAX_DUTS, std::vector<int>(MAX_BYTE_NUM_FULL, 0));
    Array_result_t error_flag;
    // AFM Read
    DUT_LOOP_START
    Digital.AFM.Read(dut, 0, Data.data(), Read_Bytes);
    for (int j = 0; j < Read_Bytes; j++)
    {
    All_DUTs_Date[dutz][j] = Data[j];
    }
    DUT_LOOP_END
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm1 = end1 - start1;
    //Print("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- array ecr  read cost %.6f second", tm1.count() / 1000);
    //testlog.Info("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- array ecr  read cost {:.6f} second", tm1.count() / 1000);
    update_local_time();
    // Data Check and Print
    int DAC = cfgReg[64];
    auto start2 = std::chrono::high_resolution_clock::now();
    Data_Compare_CKB_DDW_array_print(raw_data_fmt, Read_Bytes, All_DUTs_Date, DDW_RESET_InvCKB_DATA, error_bfr, &error_flag, Mbist_Start_Page, TFB_Limit, DFB_Limit,  aContext, DAC);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm2 = end2 - start2;
    //Print("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- array print log cost %.6f second", tm2.count() / 1000);
    //testlog.Info("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- array print log cost {:.6f} second", tm2.count() / 1000);
    DUT_LOOP_START;
    MulDUTArch[dutz].ArchMnsTFC = error_flag.error_cnt[dutz];
    DUT_LOOP_END
    // Step4 update CRS array
    // Step5 overwrite CRS onto chips
    LoadConfigFileBySo(aContext, Cfg_Filename, CFG_FILE_LENGTH, cfgReg.data(), Archive_Point, false);
    auto start3 = std::chrono::high_resolution_clock::now();
    ReadConfigFile(aContext);
    auto end3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm3 = end3 - start3;
    //Print("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- cfg read  cost %.6f second", tm3.count() / 1000);
    //testlog.Info("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- cfg read  cost {:.6f} second", tm3.count() / 1000);
    // Step6 read memory and get total error bit count
    auto start4 = std::chrono::high_resolution_clock::now();
    // RRAM_TJ::MbistReadDDW(Mbist_Start_Page,Mbist_Pages);
    //MemMainReadDDW(Mbist_Start_Page, Mbist_Pages * 0xC0);
    MemMainReadDDW_All(0x00, Mbist_Start_Page, Mbist_Pages, Mbist_Page_Bytes);
    // Step3 Data Check
    std::vector<uint> Data1(Read_Bytes, 0);
    std::vector<int> error_bfr1(Read_Bytes, 0);
    std::vector<std::vector<int>> All_DUTs_Date1(MAX_DUTS, std::vector<int>(MAX_BYTE_NUM_FULL, 0));
    Array_result_t error_flag1;
    // AFM Read
    DUT_LOOP_START
    Digital.AFM.Read(dut, 0, Data1.data(), Read_Bytes);
    for (int j = 0; j < Read_Bytes; j++)
    {
    All_DUTs_Date1[dutz][j] = Data1[j];
    }
    DUT_LOOP_END
    auto end4 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm4 = end4 - start4;
    //Print("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- array ecr  read cost %.6f second", tm4.count() / 1000);
    //testlog.Info("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- array ecr  read cost {:.6f} second", tm4.count() / 1000);
    update_local_time();
    // Data Check and Print
    DAC = cfgReg[64];
    auto start5 = std::chrono::high_resolution_clock::now();
    Data_Compare_CKB_DDW_array_print(raw_data_fmt, Read_Bytes, All_DUTs_Date1, DDW_RESET_InvCKB_DATA, error_bfr1, &error_flag1, Mbist_Start_Page, TFB_Limit, DFB_Limit, aContext, DAC);
    auto end5 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm5 = end5 - start5;
    //Print("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- array print log cost %.6f second", tm5.count() / 1000);
    //testlog.Info("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- array print log cost {:.6f} second", tm5.count() / 1000);
    DUT_LOOP_START
    MulDUTArch[dutz].ArchPlsTFC = error_flag1.error_cnt[dutz];
    DUT_LOOP_END
    // Step7 loop all the DUTs and get new CRS for each die/DUT
    std::vector <unsigned int> cfgReg_fromFile(CFG_FILE_LENGTH, 0);   // add an initial array of cfg values
    std::vector <unsigned int> cfgReg_cpyFromFile(CFG_FILE_LENGTH, 0);    // add a copy
    FileRead(aContext, Cfg_Filename, cfgReg_fromFile.data(), CFG_FILE_LENGTH);
    std::vector<UBMCacheData> buffer{};
    UBMCacheData UBM_Buffer{};
    unsigned int UbmSize = CFG_FILE_LENGTH;
    unsigned int UbmData[16][96] = { 0 };
    Digital.UBM.Config("DI");
    DUT_LOOP_START
    cfgReg_cpyFromFile = cfgReg_fromFile;
    int dutid = dutz;
    string Die_X = (*item)->GetX();
    string Die_Y = (*item)->GetY();
    int DieX = std::stoi(Die_X);
    int DieY = std::stoi(Die_Y);
    Print("DUT[%d] Location(%d,%d)", (*item)->GetSysID(), DieX, DieY);
    //ETLog::Info("DUT[{}] ArchMnsTFC is {}  ArchPlsTFC is {}", itDUT->GetSysID(), MulDUTArch[dutid].ArchMnsTFC, MulDUTArch[dutid].ArchPlsTFC);
    TheDevice.Drv_FetMultiTrim(
    MulDUTArch[dutid].ArchMnsTFC, /* read_tfbc */
    MulDUTArch[dutid].ArchPlsTFC, /* read_tfbc */
    DieX, /* dut x coordinate */
    DieY, /* dut y coordinate */
    cfgReg_cpyFromFile.data(), /* cfg byte array or ext code array */
    0, /* DEFAULT value */
    false, /* true: array point to ext_code; false: array point to cfg */
    false /* true: enable location based trim; false: disable location based trim */
    );
    std::unique_ptr<unsigned char[]> cfgUBM(new unsigned char[CFG_FILE_LENGTH]());
    for (int i = 0; i < CFG_FILE_LENGTH; i++) {
    UbmData[dut - 1][i] = static_cast<unsigned char>(cfgReg_cpyFromFile[i] & 0xFF);
    }
    Digital.UBM.Write(dut, ENUM_D_TYPE, 0, UbmData[dut-1], UbmSize);
    DUT_LOOP_END
    Print("- imported %d bytes memory data from file %s", Mbist_Pages * 128, logName.c_str());
    //// Step8 overwrite CRS onto chips
    // write cfg reg
    std::string PatternName = "pWriteCfgRegTrim";            //Pattern Name
    std::string FuncName = "fWriteCfgRegTrim";               //Pattern Fun Name
    //double TimeOutValue = 5 S;                           //Patternʱֹʱ5s
    //bool Include_RegisterInit = true;                    //ǷĴʼ true
    Digital.Pattern.RunModule("pWriteCfgRegTrim", "fWriteCfgRegTrim", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
    //// Delete Memory
    ////!!!!!!  for (auto Buf_Release : buffer)
    ////!!!!!!  {
    ////!!!!!!      delete[] Buf_Release.Value;
    ////!!!!!!      Buf_Release.Value = nullptr;
    ////!!!!!!  }
    ////!!!!!!  UBM_Buffer.Value.clear;
    std::vector<UBMCacheData>().swap(buffer);
    // read cfg reg
    auto start8 = std::chrono::high_resolution_clock::now();
    ReadConfigFile(aContext);
    auto end8 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm8 = end8 - start8;
    //Print("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- cfg read  cost %.6f second", tm8.count() / 1000);
    //testlog.Info("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- array ecr  read cost {:.6f} second", tm8.count() / 1000);
    // Step9 read memory and get fail DUT out
    auto start6 = std::chrono::high_resolution_clock::now();
    // RRAM_TJ::MbistReadDDW(Mbist_Start_Page,Mbist_Pages);
    //MemMainReadDDW(Mbist_Start_Page, Mbist_Pages * 0xC0);
    MemMainReadDDW_All(0x00, Mbist_Start_Page, Mbist_Pages, Mbist_Page_Bytes);
    // Data Check
    std::vector<uint> Data2(Read_Bytes, 0);
    std::vector<int> error_bfr2(Read_Bytes, 0);
    std::vector<std::vector<int>> All_DUTs_Date2(MAX_DUTS, std::vector<int>(MAX_BYTE_NUM_FULL, 0));
    Array_result_t error_flag2;
    // AFM Read
    DUT_LOOP_START
    Digital.AFM.Read(dut, 0, Data2.data(), Read_Bytes);
    for (int j = 0; j < Read_Bytes; j++)
    {
    All_DUTs_Date2[dutz][j] = Data2[j];
    }
    DUT_LOOP_END
    auto end6 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm6 = end6 - start6;
    //Print("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- array ecr  read cost %.6f second", tm6.count() / 1000);
    //testlog.Info("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- array ecr  read cost {:.6f} second", tm6.count() / 1000);
    update_local_time();
    // Data Check and Print
    DAC = cfgReg[64];
    auto start7 = std::chrono::high_resolution_clock::now();
    Data_Compare_CKB_DDW_array_print(raw_data_fmt, Read_Bytes, All_DUTs_Date2, DDW_RESET_InvCKB_DATA, error_bfr2, &error_flag2, Mbist_Start_Page, TFB_Limit, DFB_Limit, aContext, DAC);
    auto end7 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm7 = end7 - start7;
    //Print("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- array print log cost %.6f second", tm7.count() / 1000);
    //testlog.Info("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS- array print log cost {:.6f} second", tm7.count() / 1000);
    // Judge
    DUT_LOOP_START
    if ((error_flag2.error_flags[dutz][DFB_LMT_FLAG] != 1) || (error_flag2.error_flags[dutz][TFB_LMT_FLAG] != 1))
    {
    (*item)->SetValue(1);
    }
    DUT_LOOP_END
    // Write T-Reg
    TRegWrite(0x03, OP_DDW_OFF);
    // Read T-Reg
    if (TURN_ON_TR_VFY)
    {
    int TReg_ReadData[MAX_DUTS] = { 0 };
    TRegRead(aContext, 0x03, TReg_ReadData);
    DUT_LOOP_START
    if (TURN_ON_TR_BIN)
    {
    if (TReg_ReadData[dutz] != OP_DDW_OFF)
    {
    Print("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", 0x03, TReg_ReadData[dutz]);
    //testlog.Info("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", 0x03, TReg_ReadData[dutz]);
    (*item)->SetValue(1);
    }
    }
    DUT_LOOP_END
    }
    //this->Info("[Test Item] TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS -- end");
    }

/**
* Constructor
*/
TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS::TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS(TestItemExecuteContext * aContext) : TestItem("TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS::~TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS::Initialize(TestItemExecuteContext * aContext) {
	if(!this->UserInitialize(aContext))
	{
	 	return false;		
	}
	//add code here.

	return true;
}

/**
* Exit test
*/
void TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS, TestItemExecuteContext *)

