#include "interface/ONESInterfaceHeader.h"
#include "TB_Read_StatusReg2.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Read_StatusReg2::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Read_StatusReg2 -- started");
    double ForceHighVoltage;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("VAA", theParameter))
    {
    ForceHighVoltage = theParameter->GetValueAsDouble();
    //Print("ForceHighVoltage = %.2f V", ForceHighVoltage);
    }
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    PMU_DigitalSet("pl_function_pins", 1.65 V, 0, 0.8 V, 0.8 V);
    DPS_FV("VAA", 1.65 V, 500 MA, 500 MA, -500 MA, ENUM_SENSE_REMOTE);
    Digital.AFM.Config(12, 12, "DO", ENUM_DATA_WIDTH_BIT_8, ENUM_ALPG_SDR, ENUM_ADDRESS_MODE_1);
    Digital.AFM.SetResultMode(ENUM_OVERWRITE);
    Digital.AFM.ResetData(0x11);
    Digital.Pattern.RunRegister("pReadStatusReg2", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
    Digital.Pattern.RunModule("pReadStatusReg2", "fReadStatusReg2", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
    Time.Delay(1 MS);
    unsigned int Data[7];
    DUT_LOOP_START
    Digital.AFM.Read(dut, 0, Data, 7);
    Print("[SR_RD] Reg 35h[%d] = %02X %02X %02X (Hex)", dut, Data[0], Data[1], Data[2]);
    (*item)->SetValue(0);
    TB_Read_StatusReg2_1440[dut-1] = 0;
    DUT_LOOP_END
    //    this->Info("[Test Item] TB_Read_StatusReg2 -- end");
    }

/**
* Constructor
*/
TB_Read_StatusReg2::TB_Read_StatusReg2(TestItemExecuteContext * aContext) : TestItem("TB_Read_StatusReg2", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Read_StatusReg2::~TB_Read_StatusReg2() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Read_StatusReg2::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Read_StatusReg2::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Read_StatusReg2::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Read_StatusReg2::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Read_StatusReg2::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Read_StatusReg2::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Read_StatusReg2, TestItemExecuteContext *)

