#include "interface/ONESInterfaceHeader.h"
#include "TB_Power_On_Uninitialized.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Power_On_Uninitialized::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here
    //this->Info("[Test Item] TB_Power_On_Uninitialized -- started");
    int WaitDummy;
    // Force Voltage
    double ForceHighVoltage;
    double ForceLowVoltage = 0 V;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("VAA", theParameter))
    {
    ForceHighVoltage = theParameter->GetValueAsDouble();
    //Print("ForceHighVoltage = %.2f V", ForceHighVoltage);
    }
    if (theParameters->TryGetParameter("Wait_Dummy", theParameter))
    {
    WaitDummy = theParameter->GetValueAsInt();
    //Print("Wait_Dummy = %d ", WaitDummy);
    }
    else
    {
    WaitDummy = 1;
    }
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    double dpsIClamp_High = 250 MA;
    double dpsIClamp_Low = -250 MA;
    double dpsVLimit_High = ForceHighVoltage * 1.03;    //DPS VaaѹӦ 1.030.97֮
    double dpsVLimit_Low = ForceHighVoltage * 0.97;
    // PPMU
    double peIClamp_High = 200 UA;
    double peIClamp_Low = -200 UA;
    // DCL
    double VIH = ForceHighVoltage V;
    double VIL = 0 V;
    double VOH = VIH * 0.55 V;
    double VOL = VIH * 0.45 V;
    //Print("VIH %f", VIH);
    //Print("VIL %f", VIL);
    //Print("VOH %f", VOH);
    //Print("VOL %f", VOL);
    PMU_DigitalSet("pl_function_pins", VIH, VIL, VOH, VOL);
    DPS_FV("VAA", ForceHighVoltage V, 500 MA, 500 MA, -500 MA, ENUM_SENSE_REMOTE);
    Time.Delay(2 MS);
    auto start = std::chrono::high_resolution_clock::now();
    Time.Delay(1 MS);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm = end - start;
    double cost_seconds = tm.count() / 1000;
    //Print("TB_Power_On_Uninitialized- VAA delay cost %.6f second", cost_seconds);
    int TReg_ReadData[DUT_NUM] = { 0 };
    AFM_CONFIG_SET("DO", 12, 12, aContext);
    TRegWrite(0x00, 0x10);
    TRegRead(aContext, 0x00, TReg_ReadData);
    DUT_LOOP_START
    //Print("The DUT %d TReg Wite Addr %02X, Write Data %02X, Read Data %02X", dut, 0x00, 0x10, TReg_ReadData[dut-1]);
    //Print("DUT[%d],VAA is %.3f", dut, ForceHighVoltage);
    if (TReg_ReadData[dut - 1] != 0x10)
    {
    (*item)->SetValue(1);
    TB_Power_On_Uninitialized_1010[dut - 1] = 1;
    }
    else
    {
    (*item)->SetValue(0);
    TB_Power_On_Uninitialized_1010[dut - 1] = 0;
    }
    DUT_LOOP_END
    // this->Info("[Test Item] TB_Power_On_Uninitialized -- end");

    }

/**
* Constructor
*/
TB_Power_On_Uninitialized::TB_Power_On_Uninitialized(TestItemExecuteContext * aContext) : TestItem("TB_Power_On_Uninitialized", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Power_On_Uninitialized::~TB_Power_On_Uninitialized() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Power_On_Uninitialized::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Power_On_Uninitialized::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Power_On_Uninitialized::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Power_On_Uninitialized::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Power_On_Uninitialized::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Power_On_Uninitialized::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Power_On_Uninitialized, TestItemExecuteContext *)

