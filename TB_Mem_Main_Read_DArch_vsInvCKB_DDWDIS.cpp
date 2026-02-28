#include "interface/ONESInterfaceHeader.h"
#include "TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS -- started");
    int Mbist_Start_Page;
    int Mbist_Pages;
    int TFB_Limit;
    int DFB_Limit;
    int Archive_Point;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("Page_Length", theParameter))
    if (theParameters->TryGetParameter("Page_Length", theParameter))
    {
    Mbist_Pages = theParameter->GetValueAsInt();
    //Print("Page_Length =%d", Mbist_Pages);
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
    string Cfg_Filename = "TJ_CFG_DEMO.txt";
    // AutoMation
    #ifdef RRAM_B2_AUTOMATION
    std::string logName = log_name_setting(aContext, lotnum, wafernum, Die_X, Die_Y, testname);
    #else
    std::string logName = log_name_setting(aContext, testname);
    #endif
    // Log Head Info
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    //  a) Write TReg
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
    }
    }
    DUT_LOOP_END
    }
    // b) call DLL func
    std::vector <unsigned int> cfgReg(CFG_FILE_LENGTH, 0);
    std::vector <unsigned int> cfgReg_cpy(CFG_FILE_LENGTH, 0); // add a copy
    FileRead(aContext, Cfg_Filename, cfgReg.data(), CFG_FILE_LENGTH);
    std::vector<UBMCacheData> buffer{};
    UBMCacheData UBM_Buffer{};
    Digital.UBM.Config("DI");
    DUT_LOOP_START
    cfgReg_cpy = cfgReg;
    int dutid = dutz;
    string Die_X = (*item)->GetX();
    string Die_Y = (*item)->GetY();
    int DieX = std::stoi(Die_X);
    int DieY = std::stoi(Die_Y);
    //Print("DUT[%d] Location(%d,%d)", (*item)->GetSysID(), DieX, DieY);
    //Print("DUT[%d] ArchMnsTFC is %d  ArchPlsTFC is %d", (*item)->GetSysID(), MulDUTArch[dutid].ArchMnsTFC, MulDUTArch[dutid].ArchPlsTFC);
    TheDevice.Drv_FetMultiTrim(
    MulDUTArch[dutid].ArchMnsTFC, /* read_tfbc */
    MulDUTArch[dutid].ArchPlsTFC, /* read_tfbc */
    DieX, /* dut x coordinate */
    DieY, /* dut y coordinate */
    cfgReg_cpy.data(), /* cfg byte array or ext code array */
    0, /* Set 0 for Darch */
    false, /* true: array point to ext_code; false: array point to cfg */
    false /* true: enable location based trim; false: disable location based trim */
    );
    // Write to UBM
    //unsigned char cfgUBM[CFG_FILE_LENGTH];
    unsigned int UbmSize = CFG_FILE_LENGTH;
    unsigned int UbmData[16][96] = { 0 };
    for (int i = 0; i < CFG_FILE_LENGTH; i++)
    {
    UbmData[dut - 1][i] = static_cast<unsigned char> (cfgReg_cpy[i]);
    }
    Digital.UBM.Write(dut, ENUM_D_TYPE, 0, UbmData[dut-1], UbmSize);
    DUT_LOOP_END
    // write cfg reg
    std::string PatternName = "pWriteCfgRegTrim";            //Pattern Name
    std::string FuncName = "fWriteCfgRegTrim";               //Pattern Fun Name
    //double TimeOutValue = 5 S;                           //Patternʱֹʱ5s
    //bool Include_RegisterInit = true;                    //ǷĴʼ true
    Digital.Pattern.RunModule("pWriteCfgRegTrim", "fWriteCfgRegTrim", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
    // d) read data from pages
    auto start = std::chrono::high_resolution_clock::now();
    ReadConfigFile(aContext);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm = end - start;
    //Print("TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS- cfg read  cost %.6f second", tm.count() / 1000);
    //testlog.Info("TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS- cfg read  cost {:.6f} second", tm.count() / 1000);
    // Step3 read memory and get total error bit count
    int Read_Bytes = Mbist_Pages * MBIST_READ_DDW_PAGE;
    auto start1 = std::chrono::high_resolution_clock::now();
    // RRAM_TJ::MbistReadDDW(Mbist_Start_Page,Mbist_Pages);
    //MemMainReadDDW(Mbist_Start_Page, Mbist_Pages * 0xC0);
    MemMainReadDDW_All(0x00, Mbist_Start_Page, Mbist_Pages, MBIST_READ_DDW_PAGE);
    // Step3 Data Check
    // uint Data[Read_Bytes]       = { 0 };
    // int error_bfr[Read_Bytes]   = { 0 };
    std::vector<uint32_t> Data(Read_Bytes, 0);
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
    //Print("TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS- array ecr  read cost %.6f second", tm1.count() / 1000);
    //testlog.Info("TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS- array ecr  read cost {:.6f} second", tm1.count() / 1000);
    update_local_time();
    // Data Check and Print
    int DAC = cfgReg[64];
    auto start2 = std::chrono::high_resolution_clock::now();
    Data_Compare_CKB_DDW_array_print(raw_data_fmt, Read_Bytes, All_DUTs_Date, DDW_RESET_InvCKB_DATA, error_bfr, &error_flag, Mbist_Start_Page, TFB_Limit, DFB_Limit, aContext, DAC);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm2 = end2 - start2;
    Print("TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS- array print log cost %.6f second", tm2.count() / 1000);
    //testlog.Info("TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS- array print log cost {:.6f} second", tm2.count() / 1000);
    // Judge
    string testitem = (aContext->GetActiveTestName()).c_str();
    DUT_LOOP_START
    if ((error_flag.error_flags[dutz][DFB_LMT_FLAG] != 1) || (error_flag.error_flags[dutz][TFB_LMT_FLAG] != 1))
    {
    (*item)->SetValue(1);
    if (testitem=="1300_TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS") {
    TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS_1300[dut-1] = 1;
    }
    if (testitem == "1310_TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS") {
    TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS_1310[dut-1] = 1;
    }
    }
    else
    {
    (*item)->SetValue(0);
    if (testitem == "1300_TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS") {
    TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS_1300[dut - 1] = 0;
    }
    if (testitem == "1310_TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS") {
    TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS_1310[dut - 1] = 0;
    }
    }
    DUT_LOOP_END
    // Write T-Reg
    TRegWrite(0x03, OP_DDW_OFF);
    // Read T-Reg Addr 06h
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
    //this->Info("[Test Item] TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS -- end");
    }

/**
* Constructor
*/
TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS::TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS(TestItemExecuteContext * aContext) : TestItem("TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS::~TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS, TestItemExecuteContext *)

