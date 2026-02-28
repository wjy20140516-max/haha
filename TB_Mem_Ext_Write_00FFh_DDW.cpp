#include "interface/ONESInterfaceHeader.h"
#include "TB_Mem_Ext_Write_00FFh_DDW.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Mem_Ext_Write_00FFh_DDW::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Mem_Ext_Write_00FFh_DDW -- started");
    int Mem_Ext_Write_Page;
    int Page_Length;
    int Cycle_Number;
    int TFB_Limit;
    int DFB_Limit;
    int WaitDummy;
    int Register_Address;
    int Solid_Data;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("Page_Length", theParameter))
    {
    Page_Length = theParameter->GetValueAsInt();
    //Print("Page_Length =%d ", Page_Length);
    }
    if (theParameters->TryGetParameter("1st_Page_Addressain", theParameter))
    {
    string pa = theParameter->GetValueAsString();
    //Print("1st_Page_Addressain s= %s", pa.c_str());
    Mem_Ext_Write_Page = std::stoi(pa.c_str(), nullptr, 16);
    //Print("1st_Page_Addressain = %d(dec) 0x%04x(hex)   ", Mem_Ext_Write_Page, Mem_Ext_Write_Page);
    }
    if (theParameters->TryGetParameter("Cycle_Number", theParameter))
    {
    Cycle_Number = theParameter->GetValueAsInt();
    //Print("Cycle_Number = %d", Cycle_Number);
    }
    if (theParameters != nullptr && theParameters->TryGetParameter("TFB_Limit", theParameter))
    {
    TFB_Limit = theParameter->GetValueAsInt();
    //Print("TFB_Limit = %d", TFB_Limit);
    }
    else
    {
    TFB_Limit = MAX_BYTE_NUM_FULL;
    }
    if (theParameters != nullptr && theParameters->TryGetParameter("DFB_Limit", theParameter))
    {
    DFB_Limit = theParameter->GetValueAsInt();
    //Print("DFB_Limit = %d", DFB_Limit);
    }
    else
    {
    DFB_Limit = MAX_BYTE_NUM_FULL;
    }
    if (theParameters->TryGetParameter("Register_Address", theParameter))
    {
    string pa = theParameter->GetValueAsString();
    //Print("Register_Address s= %s", pa.c_str());
    Register_Address = std::stoi(pa.c_str(), nullptr, 16);
    //Print("Register_Address = %d(dec) 0x%04x(hex)   ", Register_Address, Register_Address);
    }
    if (theParameters->TryGetParameter("Solid_Data", theParameter))
    {
    string pa = theParameter->GetValueAsString();
    //Print("Solid_Data s= %s", pa.c_str());
    Solid_Data = std::stoi(pa.c_str(), nullptr, 16);
    //Print("Solid_Data = %d(dec) 0x%04x(hex)   ", Solid_Data, Solid_Data);
    }
    if (theParameters->TryGetParameter("Wait_Dummy", theParameter))
    {
    WaitDummy = theParameter->GetValueAsInt();
    //Print("Wait_Dummy = %d", WaitDummy);
    }
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    LoadConfigFile(aContext, false, "TJ_CFG_DEMO.bin");
    TRegWrite(Register_Address, Solid_Data);
    if (TURN_ON_TR_VFY)
    {
    int TReg_ReadData[MAX_DUTS] = { 0 };
    TRegRead(aContext, Register_Address, TReg_ReadData);
    DUT_LOOP_START
    if (TURN_ON_TR_BIN)
    {
    if (TReg_ReadData[dutz] != Solid_Data)
    {
    Print("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", Register_Address, TReg_ReadData[dutz]);
    //testlog.Info("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", Register_Address, TReg_ReadData[dutz]);
    (*item)->SetValue(1);
    }
    }
    DUT_LOOP_END
    }
    // Step3 Write T-Reg
    TRegWrite(0x03, 0x40);
    // Read T-Reg
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
    // Step4 Ext Write
    for (int cycle = 0; cycle < Cycle_Number; cycle++) {
    for (int pg = Mem_Ext_Write_Page; pg < Mem_Ext_Write_Page + (Page_Length * 0x80); pg += 0x80)
    {
    MemExtWrite(pg, 0x00);
    // Polling Judge
    #ifdef POLLING_BY_JMATCH
    RRAM_TJ::Polling_Judge(theDUTs, POLLING_ONE_TIME_MEMEXT, Polling_Max);
    #else
    //Polling_Soft(aContext, "DO", POLLING_ONE_TIME_MEMEXT, WaitDummy);
    Polling_By_Mloop(aContext, "DO", POLLING_ONE_TIME_MBIST, WaitDummy);
    #endif
    // Reset
    MemExtWrite(pg, 0xFF);
    // Polling Judge
    #ifdef POLLING_BY_JMATCH
    RRAM_TJ::Polling_Judge(theDUTs, POLLING_ONE_TIME_MEMEXT, Polling_Max);
    #else
   // Polling_Soft(aContext, "DO", POLLING_ONE_TIME_MEMEXT, WaitDummy);
    Polling_By_Mloop(aContext, "DO", POLLING_ONE_TIME_MBIST, WaitDummy);
    #endif
    }
    }
    // Step6 write T-reg
    TRegWrite(0x03, 0x00);
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
    TB_Mem_Ext_Write_00FFh_DDW_1200[dut-1] = 1;
    }
    }
    DUT_LOOP_END
    }
    //this->Info("[Test Item] TB_Mem_Ext_Write_00FFh_DDW -- end");
    }

/**
* Constructor
*/
TB_Mem_Ext_Write_00FFh_DDW::TB_Mem_Ext_Write_00FFh_DDW(TestItemExecuteContext * aContext) : TestItem("TB_Mem_Ext_Write_00FFh_DDW", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Mem_Ext_Write_00FFh_DDW::~TB_Mem_Ext_Write_00FFh_DDW() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Mem_Ext_Write_00FFh_DDW::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Mem_Ext_Write_00FFh_DDW::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Mem_Ext_Write_00FFh_DDW::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Mem_Ext_Write_00FFh_DDW::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Mem_Ext_Write_00FFh_DDW::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Mem_Ext_Write_00FFh_DDW::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Mem_Ext_Write_00FFh_DDW, TestItemExecuteContext *)

