#include "interface/ONESInterfaceHeader.h"
#include "TB_Mbist_Write_FF00h_Cycles_DDW.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Mbist_Write_FF00h_Cycles_DDW::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Mbist_Write_FF00h_Cycles_DDW -- started");
    int Mbist_Start_Page;
    int Mbist_Pages;
    int Cycle_Number;
    int TFB_Limit;
    int DFB_Limit;
    int WaitDummy;
    string pa;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters != nullptr && theParameters->TryGetParameter("Page_Length", theParameter))
    {
    Mbist_Pages = theParameter->GetValueAsInt();
    //Print("Page_Length =%d ", Mbist_Pages);
    }
    else
    {
    Mbist_Pages = 8192;
    }
    if (theParameters != nullptr && theParameters->TryGetParameter("1st_Page_Addressain", theParameter))
    {
    pa = theParameter->GetValueAsString();
    //Print("1st_Page_Addressain s= %s", pa.c_str());
    Mbist_Start_Page = std::stoi(pa.c_str(), nullptr, 16);
    //Print("1st_Page_Addressain = %d(dec) 0x%04x(hex)   ", Mbist_Start_Page, Mbist_Start_Page);
    }
    else
    {
    Mbist_Start_Page = 0x0;
    }
    if (theParameters != nullptr && theParameters->TryGetParameter("Cycle_Number", theParameter))
    {
    Cycle_Number = theParameter->GetValueAsInt();
    //Print("Cycle_Number = %d", Cycle_Number);
    }
    if (theParameters != nullptr && theParameters->TryGetParameter("TFB_Limit", theParameter))
    {
    TFB_Limit = theParameter->GetValueAsInt();
    //Print("TFB_Limit =%d ", TFB_Limit);
    }
    else
    {
    TFB_Limit = MAX_BYTE_NUM_FULL;
    }
    if (theParameters != nullptr && theParameters->TryGetParameter("DFB_Limit", theParameter))
    {
    DFB_Limit = theParameter->GetValueAsInt();
    //Print("DFB_Limit =%d ", DFB_Limit);
    }
    else
    {
    DFB_Limit = MAX_BYTE_NUM_FULL;
    }
    if (theParameters != nullptr && theParameters->TryGetParameter("Wait_Dummy", theParameter))
    {
    WaitDummy = theParameter->GetValueAsInt();
    Print("Wait_Dummy =%d ", WaitDummy);
    }
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    LoadConfigFile(aContext, false, "TJ_CFG_DEMO.bin");
    TRegWrite(0x03, OP_DDW_ON);
    if (OP_TR_DELAY)
    {
    Time.Delay(100 MS);
    }
    // Read T-Reg
    if (TURN_ON_TR_VFY)
    {
    int TReg_ReadData[MAX_DUTS] = { 0 };
    TRegRead(aContext, 0x03, TReg_ReadData);
    DUT_LOOP_START
    if (TURN_ON_TR_BIN)
    {
    if (TReg_ReadData[dutz]!= OP_DDW_ON)
    {
    Print("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", 0x03, TReg_ReadData[dut]);
    //testlog.Info("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", 0x03, TReg_ReadData[dut]);
    (*item)->SetValue(1);
    }
    }
    DUT_LOOP_END
    }
    // Step3 send 24-bit address and 1-page data then run Mbist in DDW Mode
    int Mbist_Page_Bytes = MBIST_READ_DDW_PAGE;
    int Read_Bytes = Mbist_Pages * Mbist_Page_Bytes;
    for (int cycle = 0; cycle < Cycle_Number; cycle++) {
    auto start = std::chrono::high_resolution_clock::now();
    MbistWriteDDW(Mbist_Start_Page, DDW_RESET_DATA);
    // Polling
    #ifdef POLLING_BY_JMATCH
    RRAM_TJ::Polling_Judge(theDUTs, POLLING_ONE_TIME_MBIST, Polling_Max);
    #else
    //Polling_Soft_RND(aContext, "DO", POLLING_ONE_TIME_MBIST, WaitDummy);

    Polling_By_Mloop(aContext, "DO", POLLING_ONE_TIME_MBIST, WaitDummy);
    #endif
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm = end - start;
    Print("- Issue MBIST WRITE: MEM_Address=%04X00h, MEM_Data=FFh, MBIST in DDW Mode, Cycle#%d, dut<%d:1>=0x%02X)", Mbist_Start_Page, cycle + 1, MAX_DUTS, MAX_DUTS);
    //Print("Mbist Elapsed Time (sec)%.6f  ", tm.count() / 1000);
    //testlog.Info("- Issue MBIST WRITE: MEM_Address={:04X}00h, MEM_Data=FFh, MBIST in DDW Mode, Cycle#{}, dut<{}:1>=0x{:02X})", Mbist_Start_Page, cycle + 1, MAX_DUTS, MAX_DUTS);
    DUT_LOOP_START
    Print("DUT %d Polling Elapsed Time(sec) %.6f", dut, PST.Polling_Count[dutz]/ 1000);
    //testlog.Info("DUT {} Polling Elapsed Time(sec) {:.6f}", i, PST.Polling_Count[i] / 1000);
    DUT_LOOP_END
    Print("Mbist Elapsed Time (sec)%.6f  ", tm.count() / 1000);
    auto start1 = std::chrono::high_resolution_clock::now();
    MbistWriteDDW(Mbist_Start_Page, DDW_SET_DATA);
    // Polling
    #ifdef POLLING_BY_JMATCH
    RRAM_TJ::Polling_Judge(theDUTs, POLLING_ONE_TIME_MBIST, Polling_Max);
    #else
    //Polling_Soft_RND(aContext, "DO", POLLING_ONE_TIME_MBIST, WaitDummy);
    Polling_By_Mloop(aContext, "DO", POLLING_ONE_TIME_MBIST, WaitDummy);
    #endif
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm1 = end1 - start1;
    Print("- Issue MBIST WRITE: MEM_Address=%04X00h, MEM_Data=00h, MBIST in DDW Mode, Cycle#%d, dut<%d:1>=0x%02X", Mbist_Start_Page, cycle + 1, MAX_DUTS, MAX_DUTS);
    //Print("Mbist Elapsed Time (sec)%.6f  ", tm1.count() / 1000);
    //testlog.Info("- Issue MBIST WRITE: MEM_Address={:04X}00h, MEM_Data=00h, MBIST in DDW Mode, Cycle#{}, dut<{}:1>=0x{:02X})", Mbist_Start_Page, cycle + 1, MAX_DUTS, MAX_DUTS);
    DUT_LOOP_START
    Print("DUT %d Polling Elapsed Time(sec) %.6f", dut, PST.Polling_Count[dutz]/ 1000);
    //testlog.Info("DUT {} Polling Elapsed Time(sec) {:.6f}", i, PST.Polling_Count[i] / 1000);
    DUT_LOOP_END
    Print("Mbist Elapsed Time (sec)%.6f  ", tm1.count() / 1000);
    }
    //Step6 write T-reg
    TRegWrite(0x03, OP_DDW_OFF);
    // Read T-Reg
    if (TURN_ON_TR_VFY)
    {
    int TReg_ReadData[MAX_DUTS] = { 0 };
    TRegRead(aContext, 0x03, TReg_ReadData);
    DUT_LOOP_START
    if (TURN_ON_TR_BIN)
    {
    if (TReg_ReadData[dutz]!= OP_DDW_OFF)
    {
    Print("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", 0x03, TReg_ReadData[dut]);
    //testlog.Info("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", 0x03, TReg_ReadData[dut]);
    (*item)->SetValue(1);
    TB_Mbist_Write_FF00h_Cycles_DDW_1180[dut-1] = 1;
    }
    }
    DUT_LOOP_END
    }
    //this->Info("[Test Item] TB_Mbist_Write_FF00h_Cycles_DDW -- end");
    }

/**
* Constructor
*/
TB_Mbist_Write_FF00h_Cycles_DDW::TB_Mbist_Write_FF00h_Cycles_DDW(TestItemExecuteContext * aContext) : TestItem("TB_Mbist_Write_FF00h_Cycles_DDW", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Mbist_Write_FF00h_Cycles_DDW::~TB_Mbist_Write_FF00h_Cycles_DDW() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Mbist_Write_FF00h_Cycles_DDW::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Mbist_Write_FF00h_Cycles_DDW::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Mbist_Write_FF00h_Cycles_DDW::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Mbist_Write_FF00h_Cycles_DDW::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Mbist_Write_FF00h_Cycles_DDW::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Mbist_Write_FF00h_Cycles_DDW::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Mbist_Write_FF00h_Cycles_DDW, TestItemExecuteContext *)

