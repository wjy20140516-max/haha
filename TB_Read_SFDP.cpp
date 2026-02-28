#include "interface/ONESInterfaceHeader.h"
#include "TB_Read_SFDP.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Read_SFDP::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Read_SFDP -- started");
    int Page_Length;
    int Page_addr;
    string pa;
    double ForceHighVoltage;
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
   // Print("1st_Page_Addressain s= %s", pa.c_str());
    Page_addr = std::stoi(pa.c_str(), nullptr, 16);
    //Print("1st_Page_Addressain = %d(dec) 0x%04x(hex)   ", Page_addr, Page_addr);
    }
    int Read_Bytes = Page_Length * 0x80;
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    PMU_DigitalSet("pl_function_pins", 1.65 V, 0, 0.8 V, 0.8 V);
    DPS_FV("VAA", 1.65 V, 500 MA, 500 MA, -500 MA, ENUM_SENSE_REMOTE);
    Digital.AFM.Config(12, 12, "DO", ENUM_DATA_WIDTH_BIT_8, ENUM_ALPG_SDR, ENUM_ADDRESS_MODE_1);
    Digital.AFM.SetResultMode(ENUM_OVERWRITE);
    Digital.AFM.ResetData(0x11);
    Digital.Pattern.RunRegister("pReadSFDP", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
    Digital.Pattern.RunModule("pReadSFDP", "fReadSFDP", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
    unsigned int* Data = new unsigned int[Read_Bytes];
    DUT_LOOP_START
    Digital.AFM.Read(dut, 0, Data, Read_Bytes);
    update_local_time();
    int r = 0;
    for (int j = 0; j <= (Page_Length * 8 - 1); j++)
    {
    Print("[SFDP]DUT%d Reg 5Ah = %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
    dut, Data[r], Data[r + 1], Data[r + 2], Data[r + 3], Data[r + 4], Data[r + 5], Data[r + 6], Data[r + 7],
    Data[r + 8], Data[r + 9], Data[r + 10], Data[r + 11], Data[r + 12], Data[r + 13], Data[r + 14], Data[r + 15]);
    r = r + 16;
    }
    Print("TB_Read_SFDP chip expect and read compare:", false);
    (*item)->SetValue(0);
    TB_Read_SFDP_1450[dut-1] = 0;
    DUT_LOOP_END
    //this->Info("[Test Item] TB_Read_SFDP -- end");
    }

/**
* Constructor
*/
TB_Read_SFDP::TB_Read_SFDP(TestItemExecuteContext * aContext) : TestItem("TB_Read_SFDP", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Read_SFDP::~TB_Read_SFDP() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Read_SFDP::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Read_SFDP::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Read_SFDP::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Read_SFDP::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Read_SFDP::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Read_SFDP::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Read_SFDP, TestItemExecuteContext *)

