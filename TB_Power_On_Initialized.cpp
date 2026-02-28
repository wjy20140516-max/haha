#include "interface/ONESInterfaceHeader.h"
#include "TB_Power_On_Initialized.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Power_On_Initialized::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here
    //this->Info("[Test Item] TB_Power_On_Initialized -- started");
    double ForceHighVoltage;
    double ForceLowVoltage = 0;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("VAA", theParameter))
    {
    ForceHighVoltage = theParameter->GetValueAsDouble();
    //Print("ForceHighVoltage = %.2f V", ForceHighVoltage);
    }
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    double dpsIClamp_High = 250 MA;
    double dpsIClamp_Low = -250 MA;
    double dpsVLimit_High = ForceHighVoltage * 1.03;    //DPS VaaѹӦ 1.030.97֮
    double dpsVLimit_Low = ForceHighVoltage * 0.97;
    // PPMU
    double peIClamp_High = 200;
    double peIClamp_Low = -200;
    // DCL
    double VIH = ForceHighVoltage V;
    double VIL = 0 V;
    double VOH = VIH * 0.55 V;
    double VOL = VIH * 0.45 V;
    DPS_FV("VAA", ForceHighVoltage V, 500 MA, 500 MA, -500 MA, ENUM_SENSE_REMOTE);
    Time.Delay(5 MS);
    PMU_DigitalSet("pl_function_pins", VIH, VIL, VOH, VOL);
    Time.Delay(5 MS);
    //    this->Info("[Test Item] TB_Power_On_Initialized -- end");
    }

/**
* Constructor
*/
TB_Power_On_Initialized::TB_Power_On_Initialized(TestItemExecuteContext * aContext) : TestItem("TB_Power_On_Initialized", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Power_On_Initialized::~TB_Power_On_Initialized() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Power_On_Initialized::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Power_On_Initialized::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Power_On_Initialized::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Power_On_Initialized::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Power_On_Initialized::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Power_On_Initialized::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Power_On_Initialized, TestItemExecuteContext *)

