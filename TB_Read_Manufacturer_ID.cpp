#include "interface/ONESInterfaceHeader.h"
#include "TB_Read_Manufacturer_ID.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Read_Manufacturer_ID::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Read_Manufacturer_ID -- started");
    double ForceHighVoltage;
    int Solid_Data = 0;
    bool specifyID = true;
    char cBuf[512] = { 0 };
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("VAA", theParameter))
    {
    ForceHighVoltage = theParameter->GetValueAsDouble();
    //Print("ForceHighVoltage = %.2f V", ForceHighVoltage);
    }
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    Digital.AFM.Config(12, 12, "DO", ENUM_DATA_WIDTH_BIT_8, ENUM_ALPG_SDR, ENUM_ADDRESS_MODE_1);
    Digital.AFM.SetResultMode(ENUM_OVERWRITE);
    Digital.AFM.ResetData(0x11);
    Digital.Pattern.RunRegister("pReadManufacturerID", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
    Digital.Pattern.RunModule("pReadManufacturerID", "fReadManufacturerID", ENUM_PATTERNSTOP_INTERRUPT, 1 S);
    Time.Delay(1 MS);
    DUT_LOOP_START
    unsigned int Data[5];
    update_local_time();
    Digital.AFM.Read(dut, 0, Data, 5);
    (*item)->SetValue(0);
    Print("[ReadManufacturerID]DUT%d Reg 90h = %02X  %02X %02X %02X %02X (Hex)", dut, Data[0], Data[1], Data[2],Data[3],Data[4]);
    DUT_LOOP_END
    //this->Info("[Test Item] TB_Read_Manufacturer_ID -- end");
    }

/**
* Constructor
*/
TB_Read_Manufacturer_ID::TB_Read_Manufacturer_ID(TestItemExecuteContext * aContext) : TestItem("TB_Read_Manufacturer_ID", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Read_Manufacturer_ID::~TB_Read_Manufacturer_ID() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Read_Manufacturer_ID::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Read_Manufacturer_ID::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Read_Manufacturer_ID::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Read_Manufacturer_ID::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Read_Manufacturer_ID::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Read_Manufacturer_ID::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Read_Manufacturer_ID, TestItemExecuteContext *)

