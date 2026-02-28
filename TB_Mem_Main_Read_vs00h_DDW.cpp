#include "interface/ONESInterfaceHeader.h"
#include "TB_Mem_Main_Read_vs00h_DDW.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Mem_Main_Read_vs00h_DDW::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Mem_Main_Read_vs00h_DDW -- started");
    //std::string test_num = "1150";
    //std::string cp_ver = "Taiji1p8_CP_ProductionFlow_V1p1";
    //std::string lotnum = "B550064";
    //std::string wafernum = "B550064-14";
    //int Die_X = 0;
    //int Die_Y = 0;
    //std::string testname;
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
    //Print("Page_Length =%d ", Mbist_Pages);
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
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    LoadConfigFile(aContext, false, "TJ_CFG_DEMO.bin");
    // Step2 Read Data
    int Mbist_Page_Bytes = MBIST_READ_DDW_PAGE;
    int Read_Bytes = Mbist_Pages * Mbist_Page_Bytes;
    TRegWrite(0x03, 0x40);
    if (TURN_ON_TR_VFY)
    {
    int TReg_ReadData[MAX_DUTS] = { 0 };
    TRegRead(aContext, 0x03, TReg_ReadData);
    DUT_LOOP_START
    if (TURN_ON_TR_BIN)
    {
    if (TReg_ReadData[dut-1] != 0x40)
    {
    Print("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", 0x03, TReg_ReadData[dut-1]);
    //testlog.Info("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", 0x03, TReg_ReadData[dut]);
    (*item)->SetValue(1);
    }
    }
    DUT_LOOP_END
    }
    auto start = std::chrono::high_resolution_clock::now();
    //MemMainReadDDW(Mbist_Start_Page, Mbist_Pages * 0xC0);
    MemMainReadDDW_All(0x00, Mbist_Start_Page,  Mbist_Pages, Mbist_Page_Bytes);
    std::vector<uint32_t> Data(Read_Bytes, 0);
    std::vector<int> error_bfr(Read_Bytes, 0);
    std::vector<std::vector<int>> All_DUTs_Date(MAX_DUTS, std::vector<int>(MAX_BYTE_NUM_FULL, 0));
    Array_result_t error_flag;
    // AFM Read
    DUT_LOOP_START
    Digital.AFM.Read(dut, 0, Data.data(), Read_Bytes);
    for (int j = 0; j < Read_Bytes; j++)
    {
    All_DUTs_Date[dut-1][j] = Data[j];
    }
    DUT_LOOP_END
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm = end - start;
    Print("TB_Mem_Main_Read_vs00h_DDW- array ecr  read cost %.6f second", tm.count() / 1000);
    //testlog.Info("TB_Mem_Main_Read_vs00h_DDW- array ecr  read cost {:.6f} second", tm.count() / 1000);
    update_local_time;
    // Data Check and Print
    auto start1 = std::chrono::high_resolution_clock::now();
    Data_Compare_Mbist_array_print(raw_data_fmt, Read_Bytes, All_DUTs_Date, DDW_SET_DATA, error_bfr, &error_flag, Mbist_Start_Page, TFB_Limit, DFB_Limit, aContext);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm1 = end1 - start1;
    Print("TB_Mem_Main_Read_vs00h_DDW- array print log cost %.6f second", tm1.count() / 1000);
    //testlog.Info("TB_Mem_Main_Read_vs00h_DDW- array print log cost {:.6f} second", tm1.count() / 1000);
    string testitem = (aContext->GetActiveTestName()).c_str();
    DUT_LOOP_START
    if ((error_flag.error_flags[dut-1][DFB_LMT_FLAG] != 1) || (error_flag.error_flags[dut-1][TFB_LMT_FLAG] != 1))
    {
    (*item)->SetValue(1);
    if (testitem == "1120_TB_Mem_Main_Read_vs00h_DDW")
    {
    TB_Mem_Main_Read_vs00h_DDW_1120[dut-1] = 1;
    }
    if (testitem == "1150_TB_Mem_Main_Read_vs00h_DDW")
    {
    TB_Mem_Main_Read_vs00h_DDW_1150[dut - 1] = 1;
    }
    if (testitem == "1190_TB_Mem_Main_Read_vs00h_DDW")
    {
    TB_Mem_Main_Read_vs00h_DDW_1190[dut - 1] = 1;
    }
    if (testitem == "1210_TB_Mem_Main_Read_vs00h_DDW")
    {
    TB_Mem_Main_Read_vs00h_DDW_1210[dut - 1] = 1;
    }
    if (testitem == "1240_TB_Mem_Main_Read_vs00h_DDW")
    {
    TB_Mem_Main_Read_vs00h_DDW_1240[dut - 1] = 1;
    }
    if (testitem == "1370_TB_Mem_Main_Read_vs00h_DDW")
    {
    TB_Mem_Main_Read_vs00h_DDW_1370[dut - 1] = 1;
    }
    }
    else
    {
    (*item)->SetValue(0);
    if (testitem == "1120_TB_Mem_Main_Read_vs00h_DDW")
    {
    TB_Mem_Main_Read_vs00h_DDW_1120[dut - 1] = 0;
    }
    if (testitem == "1150_TB_Mem_Main_Read_vs00h_DDW")
    {
    TB_Mem_Main_Read_vs00h_DDW_1150[dut - 1] = 0;
    }
    if (testitem == "1190_TB_Mem_Main_Read_vs00h_DDW")
    {
    TB_Mem_Main_Read_vs00h_DDW_1190[dut - 1] = 0;
    }
    if (testitem == "1210_TB_Mem_Main_Read_vs00h_DDW")
    {
    TB_Mem_Main_Read_vs00h_DDW_1210[dut - 1] = 0;
    }
    if (testitem == "1240_TB_Mem_Main_Read_vs00h_DDW")
    {
    TB_Mem_Main_Read_vs00h_DDW_1240[dut - 1] = 0;
    }
    if (testitem == "1370_TB_Mem_Main_Read_vs00h_DDW")
    {
    TB_Mem_Main_Read_vs00h_DDW_1370[dut - 1] = 0;
    }
    }
    DUT_LOOP_END
    TRegWrite(0x03, OP_DDW_OFF);
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
    //this->Info("[Test Item] TB_Mem_Main_Read_vs00h_DDW -- end");
    }

/**
* Constructor
*/
TB_Mem_Main_Read_vs00h_DDW::TB_Mem_Main_Read_vs00h_DDW(TestItemExecuteContext * aContext) : TestItem("TB_Mem_Main_Read_vs00h_DDW", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Mem_Main_Read_vs00h_DDW::~TB_Mem_Main_Read_vs00h_DDW() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Mem_Main_Read_vs00h_DDW::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Mem_Main_Read_vs00h_DDW::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Mem_Main_Read_vs00h_DDW::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Mem_Main_Read_vs00h_DDW::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Mem_Main_Read_vs00h_DDW::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Mem_Main_Read_vs00h_DDW::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Mem_Main_Read_vs00h_DDW, TestItemExecuteContext *)

