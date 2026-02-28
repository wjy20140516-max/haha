#include "interface/ONESInterfaceHeader.h"
#include "TB_Mem_Main_Read_vsFFh_DDW.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Mem_Main_Read_vsFFh_DDW::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Mem_Main_Read_vsFFh_DDW -- started");
    double ForceVoltage;
    //std::string Cfg_Filename;
    int Mbist_Start_Page;
    int Mbist_Pages;
    int TFB_Limit;
    int DFB_Limit;
    string pa;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("Page_Length", theParameter))
    {
    Mbist_Pages = theParameter->GetValueAsInt();
    //Print("Page_Length = %d", Mbist_Pages);
    }
    if (theParameters->TryGetParameter("1st_Page_Addressain", theParameter))
    {
    pa = theParameter->GetValueAsString();
    //Print("1st_Page_Addressain s= %s", pa.c_str());
    Mbist_Start_Page = std::stoi(pa.c_str(), nullptr, 16);
    //Print("1st_Page_Addressain = %d(dec) 0x%04x(hex)   ", Mbist_Start_Page, Mbist_Start_Page);
    }
    if (theParameters->TryGetParameter("TFB_Limit", theParameter))
    {
    TFB_Limit = theParameter->GetValueAsInt();
    //Print("TFB_Limit = %d", TFB_Limit);
    }
    if (theParameters->TryGetParameter("DFB_Limit", theParameter))
    {
    DFB_Limit = theParameter->GetValueAsInt();
    //Print("DFB_Limit = %d", DFB_Limit);
    }
    AFM_CONFIG_SET("DO", 12, 12, aContext);
    //power on debug =============================================================
    if (test_mode_debug_power)
    {
    PMU_DigitalSet("pl_function_pins", 1.65 V, 0, 0.8 V, 0.8 V);
    DPS_FV("VAA", 1.65 V, 500 MA, 500 MA, -500 MA, ENUM_SENSE_REMOTE);
    }
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    //power on debug =============================================================
    LoadConfigFile(aContext, false, "TJ_CFG_DEMO.bin");
    //Digital.UBM.Config("DI");
    //DUT_LOOP_START
    //Digital.UBM.Write(dut, ENUM_D_TYPE, 0, ubm_data[dut - 1], 96);
    //DUT_LOOP_END
    //// write cfg reg
    //Digital.Pattern.RunModule("pWriteCfgRegUbm", "fWriteCfgRegUbm", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
    //// read cfg reg
    //Digital.Pattern.RunModule("pReadCfgReg", "fReadCfgReg", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
    ////AFM_READ_Non_cross_VP(96, 0, 0x00, aContext);
    //
    //
    //unsigned int rdata[96];
    //DUT_LOOP_START
    //Digital.AFM.Read(dut, 0, rdata, 96);
    //int r = 0;
    //Get_Local_Time_1(local_time_s, sizeof(local_time_s));
    //this->Info("Start_Addr=000000h,Byte Num=96");
    //this->Info("[CR_RD] 		   Hex  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
    //for (int j = 0; j < 6; j++)
    //{
    //    Print("[CR_RD]Dut %d %06XH-%06XH:%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
    //        dut, r, r + 15, rdata[r], rdata[r + 1], rdata[r + 2], rdata[r + 3], rdata[r + 4], rdata[r + 5], rdata[r + 6], rdata[r + 7],
    //        rdata[r + 8], rdata[r + 9], rdata[r + 10], rdata[r + 11], rdata[r + 12], rdata[r + 13], rdata[r + 14], rdata[r + 15]);
    //
    //    r = r + 16;
    //}
    //(*item)->SetValue(0);
    //DUT_LOOP_END
    //
    //
    //Print("TRIG START=============================================================");
    //Time.Delay(5 S);
    int Mbist_Page_Bytes = MBIST_READ_DDW_PAGE;
    int Read_Bytes = Mbist_Pages * Mbist_Page_Bytes;
    //Print("pages , %d , value :%d", Mbist_Pages, Read_Bytes);
    TRegWrite(0x03, 0x40);
    // Read T-Reg
    if (TURN_ON_TR_VFY)
    {
    int TReg_ReadData[MAX_DUTS] = { 0 };
    TRegRead(aContext, 0x03, TReg_ReadData);
    //DUT_LOOP_START
    //AFM_READ_Non_cross_VP(1, 0, 0x00, aContext);
    //Print("[TR_RD] Read T-Reg Add %02Xh = %02X", 0x03, Data_conversion[dut - 1][0]);
    //Print("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", 0x03, TReg_ReadData[dut - 1]);
    //DUT_LOOP_END
    DUT_LOOP_START
    if (TURN_ON_TR_BIN)
    {
    if (TReg_ReadData[dut-1] != 0x40)
    {
    Print("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", 0x03, TReg_ReadData[dut - 1]);
    (*item)->SetValue(1);
    }
    }
    DUT_LOOP_END
    }
    //string PatternName = "pMemMainRead";
    //string FuncName = "fMemMainRead";
    //double TimeOutValue = 30 MS;
    ////bool Include_RegisterInit = true;
    ////0Bh-->read Set data
    //Digital.Pattern.SetRegister(ONES_REG_D2, 0xFF);
    //Digital.Pattern.SetRegister(ONES_REG_Z1, 0);
    //Digital.Pattern.SetRegister(ONES_REG_LI1, 0xFFE);//4096
    //Digital.Pattern.SetRegister(ONES_REG_LI2, 0x17E);//384
    //Digital.Pattern.RunModule(PatternName, FuncName, ENUM_PATTERNSTOP_INTERRUPT, 100 S);
    //
    //MemMainReadDDW(Mbist_Start_Page, Mbist_Pages * 0xC0);
    // d) 0Bh-->read data
    auto start = std::chrono::high_resolution_clock::now();
    //RRAM_TJ::MemMainReadDDW(Mbist_Start_Page, Mbist_Pages * 0xC0);
    MemMainReadDDW_All(0x00, Mbist_Start_Page, Mbist_Pages, Mbist_Page_Bytes);
    //unsigned int size = 1572864;
    //AFM_READ_Non_cross_VP(size, 0, 0x00, aContext);
    // Step3 Data Check
    // uint Data[Read_Bytes]       = { 0 };
    // int error_bfr[Read_Bytes]   = { 0 };
    std::vector<uint32_t> Data(Read_Bytes, 0);
    std::vector<int> error_bfr(Read_Bytes, 0);
    std::vector<std::vector<int>> All_DUTs_Date(MAX_DUTS, std::vector<int>(MAX_BYTE_NUM_FULL, 0));
    Array_result_t error_flag;
    DUT_LOOP_START
    Digital.AFM.Read(dut, 0, Data.data(), Read_Bytes);
    for (int j = 0; j < Read_Bytes; j++)
    {
    All_DUTs_Date[dut-1][j] = Data[j];
    }
    DUT_LOOP_END
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm = end - start;
    //ETLog::Info("TB_Mem_Main_Read_vsFFh_DDW- array ecr  read cost {:.6f} second", tm.count() / 1000);
    Print("TB_Mem_Main_Read_vsFFh_DDW- array ecr  read cost %.6f second", tm.count() / 1000);
    update_local_time();
    // Data Check and Print
    auto start1 = std::chrono::high_resolution_clock::now();
    //Data_Compare_Mbist_array_print(raw_data_fmt, Read_Bytes, All_DUTs_Date, DDW_RESET_DATA, error_bfr, &error_flag, Mbist_Start_Page, TFB_Limit, DFB_Limit, testlog, context);
    Data_Compare_Mbist_array_print(raw_data_fmt, Read_Bytes, All_DUTs_Date, DDW_RESET_DATA, error_bfr, &error_flag, Mbist_Start_Page, TFB_Limit, DFB_Limit, aContext, 1);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm1 = end1 - start1;
    //ETLog::Info("TB_Mem_Main_Read_vsFFh_DDW- array print log cost {:.6f} second", tm1.count() / 1000);
    Print("TB_Mem_Main_Read_vsFFh_DDW- array print log cost %.6f second", tm1.count() / 1000);
    string testitem = (aContext->GetActiveTestName()).c_str();
    DUT_LOOP_START
    if ((error_flag.error_flags[dut-1][DFB_LMT_FLAG] != 1) || (error_flag.error_flags[dut-1][TFB_LMT_FLAG] != 1))
    {
    (*item)->SetValue(1);
    if (testitem == "1080_TB_Mem_Main_Read_vsFFh_DDW")
    {
    TB_Mem_Main_Read_vsFFh_DDW_1080[dut - 1] = 1;
    }
    if (testitem == "1170_TB_Mem_Main_Read_vsFFh_DDW")
    {
    TB_Mem_Main_Read_vsFFh_DDW_1170[dut - 1] = 1;
    }
    }
    else
    {
    if (testitem == "1080_TB_Mem_Main_Read_vsFFh_DDW")
    {
    TB_Mem_Main_Read_vsFFh_DDW_1080[dut - 1] = 0;
    }
    if (testitem == "1170_TB_Mem_Main_Read_vsFFh_DDW")
    {
    TB_Mem_Main_Read_vsFFh_DDW_1170[dut - 1] = 0;
    }
    (*item)->SetValue(0);
    }
    DUT_LOOP_END
    // Shmoo Stop
    TRegWrite(0x03, OP_DDW_OFF);
    // Read T-Reg
    if (TURN_ON_TR_VFY)
    {
    int TReg_ReadData[MAX_DUTS] = { 0 };
    TRegRead(aContext, 0x03, TReg_ReadData);
    DUT_LOOP_START
    if (TURN_ON_TR_BIN)
    {
    if (TReg_ReadData[dut-1] != OP_DDW_OFF)
    {
    Print("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", 0x03, TReg_ReadData[dut-1]);
    //testlog.Info("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", 0x03, TReg_ReadData[dut]);
    (*item)->SetValue(1);
    }
    }
    DUT_LOOP_END
    }
    //this->Info("[Test Item] TB_Mem_Main_Read_vsFFh_DDW -- end");
    }

/**
* Constructor
*/
TB_Mem_Main_Read_vsFFh_DDW::TB_Mem_Main_Read_vsFFh_DDW(TestItemExecuteContext * aContext) : TestItem("TB_Mem_Main_Read_vsFFh_DDW", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Mem_Main_Read_vsFFh_DDW::~TB_Mem_Main_Read_vsFFh_DDW() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Mem_Main_Read_vsFFh_DDW::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Mem_Main_Read_vsFFh_DDW::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Mem_Main_Read_vsFFh_DDW::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Mem_Main_Read_vsFFh_DDW::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Mem_Main_Read_vsFFh_DDW::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Mem_Main_Read_vsFFh_DDW::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Mem_Main_Read_vsFFh_DDW, TestItemExecuteContext *)

