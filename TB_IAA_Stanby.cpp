#include "interface/ONESInterfaceHeader.h"
#include "TB_IAA_Stanby.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_IAA_Stanby::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here
    //this->Info("Test Item] TB_IAA_Stanby -- started");
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    double ForceHighVoltage;
    double ForceLowVoltage = 0 V;
    double dpsILimit_Low;
    double dpsILimit_High;
    ResultMap ResultI;
    double POWERPIN[100];
    string pf = "PASS";
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("VAA", theParameter))
    {
    ForceHighVoltage = theParameter->GetValueAsDouble();
    //Print("ForceHighVoltage = %.2f V", ForceHighVoltage);
    }
    if (theParameters->TryGetParameter("DC_Test_high_limit", theParameter))
    {
    dpsILimit_High = theParameter->GetValueAsInt() * 1e-6;
    }
    if (theParameters->TryGetParameter("DC_Test_low_limit", theParameter))
    {
    dpsILimit_Low = theParameter->GetValueAsInt()*1e-6;
    }
    // DPS
    double dpsIClamp_High_250mA = 250   MA;
    double dpsIClamp_Low_250mA = -250  MA;
    double dpsIClamp_High_250uA = 250  UA;
    double dpsIClamp_Low_250uA = -250 UA;
    // PPMU
    double peIClamp_High = 200 UA;
    double peIClamp_Low = -200 UA;
    // DCL
    double VIH = ForceHighVoltage;
    double VIL = 0 V;
    double VOH = VIH * 0.55;
    double VOL = VIH * 0.45;
    PMU_Off("pl_function_pins");
    VI.SetIRange("VAA", 250 UA);
    VI.SetIClamp("VAA", 250 UA, -250 UA);
    Time.Delay(10 MS);
    PMU_FV("pl_standby_high", ForceHighVoltage V, 200 UA, 200 UA, -200 UA);
    PMU_FV("pl_standby_low", 0 V, 200 UA, 200 UA, -200 UA);
    Time.Delay(5 NS);
    VI.GetMeasureValue("VAA", ResultI);
    Print("--------------------------------------------------------------------StandbyCurrent--------------------------------------------------------------------");
    Print("%-15s %-15s %-20s %-12s %-12s %-10s %-10s %-15s %-18s %-18s %-18s", "PASS/FAIL", "TestNumber", "TestName", "SysID", "LocalID", "X", "Y", "PinList", "HighLimit(A)", "LowLimit(A)", "MeasuredValue(A)");
    string testitem= (aContext->GetActiveTestName()).c_str();
    DUT_LOOP_START
    POWERPIN[dut - 1] = ResultI[dut]["VAA"];
    if (testitem == "1040_TB_IAA_Stanby")
    {
    TB_IAA_Stanby_1040[dut - 1] = POWERPIN[dut - 1];
    }
    if (testitem == "1060_TB_IAA_Stanby")
    {
    TB_IAA_Stanby_1060[dut - 1] = POWERPIN[dut - 1];
    }
    if (testitem == "1530_TB_IAA_Stanby")
    {
    TB_IAA_Stanby_1530[dut - 1] = POWERPIN[dut - 1];
    }
    if ((dpsILimit_Low < POWERPIN[dut - 1]) && (POWERPIN[dut - 1] < dpsILimit_High))
    {
    Print("%-15s %-15s %-20s %-12d %-12d %-10d %-10d %-15s %-18.10f %-18.10f %-18.10f", pf.data(), TestNumber.data(), TestName.data(), (*item)->GetSysID(), dut, dutx[dutz], duty[dutz], "VAA", dpsILimit_High, dpsILimit_Low, POWERPIN[dut - 1]);
    }
    else
    {
    pf = "FAIL";
    FLG_PF[dut - 1] = 1;
    Print("%-15s %-15s %-20s %-12d %-12d %-10d %-10d %-15s %-18.10f %-18.10f %-18.10f", pf.data(), TestNumber.data(), TestName.data(), (*item)->GetSysID(), dut, dutx[dutz], duty[dutz], "VAA", dpsILimit_High, dpsILimit_Low, POWERPIN[dut - 1]);
    }
    DUT_LOOP_END
    VI.SetIRange("VAA", 1200 MA);
    VI.SetIClamp("VAA", 1200 MA, -1200 MA);
    Time.Delay(1 MS);
    PMU_FV("pl_standby_pins", 0 V, 200 UA, 200 UA, -200 UA);
    PMU_Off("pl_standby_pins");
    PMU_DigitalSet("pl_function_pins", VIH, VIL, VOH, VOL);
    Time.Delay(1 MS);
    DUT_LOOP_START
    if (FLG_PF[dut - 1] == 1)
    {
    (*item)->SetValue(1);
    }
    else
    {
    (*item)->SetValue(0);
    }
    DUT_LOOP_END
    //this->Info("[Test Item] TB_IAA_Stanby -- end");
    }

/**
* Constructor
*/
TB_IAA_Stanby::TB_IAA_Stanby(TestItemExecuteContext * aContext) : TestItem("TB_IAA_Stanby", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_IAA_Stanby::~TB_IAA_Stanby() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_IAA_Stanby::Initialize(TestItemExecuteContext * aContext) {
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
void TB_IAA_Stanby::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_IAA_Stanby::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_IAA_Stanby::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_IAA_Stanby::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_IAA_Stanby::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_IAA_Stanby, TestItemExecuteContext *)

