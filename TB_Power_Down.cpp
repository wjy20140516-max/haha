#include "interface/ONESInterfaceHeader.h"
#include "TB_Power_Down.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Power_Down::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here
    //this->Info("[Test Item] TB_Power_Down -- started");
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    PMU_Off("pl_function_pins");
   // this->Info("All DCL Pins Turn Off");
    DPS_FV("VAA", 0 V, 1.2 A, 1.2 A, -1.2 A, ENUM_SENSE_REMOTE);
    Time.Delay(3 MS);
    DPS_Off("VAA");
   // this->Info("All DPS Pins Turn Off");
    //this->Info("[Test Item] TB_Power_Down -- end");
    }

/**
* Constructor
*/
TB_Power_Down::TB_Power_Down(TestItemExecuteContext * aContext) : TestItem("TB_Power_Down", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Power_Down::~TB_Power_Down() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Power_Down::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Power_Down::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Power_Down::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Power_Down::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Power_Down::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Power_Down::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Power_Down, TestItemExecuteContext *)

