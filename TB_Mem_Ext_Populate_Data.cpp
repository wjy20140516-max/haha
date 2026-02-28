#include "interface/ONESInterfaceHeader.h"
#include "TB_Mem_Ext_Populate_Data.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Mem_Ext_Populate_Data::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Mem_Ext_Populate_Data -- started");
    std::string Cfg_Filename;
    std::string Populate_Data_File;
    int Mem_Ext_Write_Page;
    int Page_Length;
    int Cycle_Number;
    int TFB_Limit;
    int DFB_Limit;
    int WaitDummy;
    int Register_Address;
    int Solid_Data;
    string pa;
    double ForceHighVoltage;
    double ForceLowVoltage = 0;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("VAA", theParameter))
    {
    ForceHighVoltage = theParameter->GetValueAsDouble();
    //Print("ForceHighVoltage = %.2f V", ForceHighVoltage);
    }
    if (theParameters->TryGetParameter("Page_Length", theParameter))
    {
    Page_Length = theParameter->GetValueAsInt();
    //Print("Page_Length = %d", Page_Length);
    }
    if (theParameters->TryGetParameter("1st_Page_Addressain", theParameter))
    {
    pa = theParameter->GetValueAsString();
    //Print("1st_Page_Addressain s= %s", pa.c_str());
    Mem_Ext_Write_Page = std::stoi(pa.c_str(), nullptr, 16);
    //Print("1st_Page_Addressain = %d(dec) 0x%04x(hex)   ", Mem_Ext_Write_Page, Mem_Ext_Write_Page);
    }
    if (theParameters->TryGetParameter("Cycle_Number", theParameter))
    {
    Cycle_Number = theParameter->GetValueAsInt();
    //Print("Cycle_Number =%d ", Cycle_Number);
    }
    if (theParameters->TryGetParameter("TFB_Limit", theParameter))
    {
    TFB_Limit = theParameter->GetValueAsInt();
    //Print("TFB_Limit = %d", TFB_Limit);
    }
    else
    {
    TFB_Limit = MAX_BYTE_NUM_FULL;
    }
    if (theParameters->TryGetParameter("DFB_Limit", theParameter))
    {
    DFB_Limit = theParameter->GetValueAsInt();
    //Print("DFB_Limit = %d", DFB_Limit);
    }
    else
    {
    TFB_Limit = MAX_BYTE_NUM_FULL;
    }
    if (theParameters->TryGetParameter("Wait_Dummy", theParameter))
    {
    WaitDummy = theParameter->GetValueAsInt();
    //Print("Wait_Dummy = %d", WaitDummy);
    }
    if (theParameters->TryGetParameter("Register_Address", theParameter))
    {
    pa = theParameter->GetValueAsString();
    //Print("Register_Address s= %s", pa.c_str());
    Register_Address = std::stoi(pa.c_str(), nullptr, 16);
    //Print("Register_Address = %d(dec) 0x%04x(hex)   ", Register_Address, Register_Address);
    }
    if (theParameters->TryGetParameter("Solid_Data", theParameter))
    {
    pa = theParameter->GetValueAsString();
    //Print("Solid_Data s= %s", pa.c_str());
    Solid_Data = std::stoi(pa.c_str(), nullptr, 16);
    //Print("Solid_Data = %d(dec) 0x%04x(hex)   ", Solid_Data, Solid_Data);
    }
    double VIH = ForceHighVoltage V;
    double VIL = 0 V;
    double VOH = VIH * 0.55 V;
    double VOL = VIH * 0.45 V;
    //Print("VIH %f", VIH);
    //Print("VIL %f", VIL);
    //Print("VOH %f", VOH);
    //Print("VOL %f", VOL);
    //PMU_DigitalSet("pl_function_pins", VIH, VIL, VOH, VOL);
    //DPS_FV("VAA", ForceHighVoltage V, 500 MA, 500 MA, -500 MA, ENUM_SENSE_REMOTE);
    //Time.Delay(2 MS);
    Cfg_Filename =  "TJ_CFG_DEMO.txt";
    Populate_Data_File =  "TJ_CFG_DEMO.txt";
    //Cfg_Filename = Cfg_Filename + ".txt";
    //Populate_Data_File = Populate_Data_File + ".txt";
    // AutoMation
    #ifdef RRAM_B2_AUTOMATION
    std::string logName = log_name_setting(aContext, lotnum, wafernum, Die_X, Die_Y, testname);
    #else
    std::string logName = log_name_setting(aContext, TestName);
    #endif
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    // Step1 Load CFG And Compare
    LoadConfigFile(aContext, false, "TJ_CFG_DEMO.bin");
    // Step2 Write T-reg
    TRegWrite(Register_Address, Solid_Data);
    // if (OP_TR_DELAY)
    // {
    //     usleep(100000);
    // }
    // Read T-Reg
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
    // Step4 Ext Write
    Array_result_t error_flag;
    string theCfgFile = "TJ_CFG_DEMO.bin";
    Digital.DBM.Write(0, theCfgFile);
    std::vector<uint8_t> theCfgFileSize;
    loadHexFile(theCfgFile, theCfgFileSize);
    //    Print("*** imported %d bytes", theCfgFileSize.size());
    //DUT_LOOP_START
    //    if (theCfgFileSize.size() < Page_Length * 128) //20250807->fail cfg file
    //    {
    //        Print("-ERROR: imported %d bytes(<%d}) memory data from file %s", theCfgFileSize.size(), Page_Length * 128, logName.c_str());
    //        //testlog.Info("-ERROR: imported {} bytes(<{}) memory data from file {}", theCfgFileSize.size(), Page_Length * 128, logName);
    //        // Judge then go to fail bin
    //        (*item)->SetValue(1);
    //        //Print("[Test Item] TB_Mem_Ext_Populate_Data --end");
    //        // return;
    //
    }

/**
* Constructor
*/
TB_Mem_Ext_Populate_Data::TB_Mem_Ext_Populate_Data(TestItemExecuteContext * aContext) : TestItem("TB_Mem_Ext_Populate_Data", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Mem_Ext_Populate_Data::~TB_Mem_Ext_Populate_Data() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Mem_Ext_Populate_Data::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Mem_Ext_Populate_Data::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Mem_Ext_Populate_Data::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Mem_Ext_Populate_Data::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Mem_Ext_Populate_Data::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Mem_Ext_Populate_Data::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Mem_Ext_Populate_Data, TestItemExecuteContext *)

