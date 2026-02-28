#include "interface/ONESInterfaceHeader.h"
#include "TB_Force_VHH.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Force_VHH::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Force_VHH -- started");
    //double ForceHighVoltage;
    //double ForceHighVoltage1;
    //double Current_Pass_High;
    //double Current_Pass_Low;
    //ResultMap ResultI;
    //double POWERPIN[100];
    //double vhhIClamp_High = 500 MA;
    //double vhhIClamp_Low = -500 MA;
    //double vhhILimit_Low = 0   MA;
    //double vhhILimit_High = 3   MA;
    //TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    //TestExecuteParameter* theParameter = nullptr;
    //if (theParameters->TryGetParameter("VHH", theParameter))
    //{
    //    ForceHighVoltage = theParameter->GetValueAsDouble();
    //    Print("ForceHighVoltage = %.2f V", ForceHighVoltage);
    //}
    //if (theParameters->TryGetParameter("VAA", theParameter))
    //{
    //    ForceHighVoltage1 = theParameter->GetValueAsDouble();
    //    Print("ForceHighVoltage1 = %.2f V", ForceHighVoltage1);
    //}
    //if (theParameters->TryGetParameter("DC_Test_high_limit", theParameter))
    //{
    //    Current_Pass_High = theParameter->GetValueAsDouble();
    //    Print("Current_Pass_High = %.2f UA", Current_Pass_High);
    //}
    //if (theParameters->TryGetParameter("DC_Test_low_limit", theParameter))
    //{
    //    Current_Pass_Low = theParameter->GetValueAsDouble();
    //    Print("Current_Pass_Low = %.2f UA", Current_Pass_Low);
    //}
    //Current_Pass_High = Current_Pass_High UA;
    //Current_Pass_Low = Current_Pass_Low  UA;
    //DPS_Off("VHH");
    //Time.Delay(1 MS);
    //DPS_FV("VHH", ForceHighVoltage V, 500 MA, 500 MA, -500 MA, ENUM_SENSE_REMOTE);
    //Time.Delay(5 MS);
    //VI.SetIRange("VHH", 2.5 MA);
    //VI.SetIClamp("VHH", 2.5 MA, -2.5 MA);
    //Time.Delay(20 MS);
    ////VI.SetMeasureParameter("VHH", 100, 100);
    //VI.GetMeasureValue("VHH", ResultI);
    //DUT_LOOP_START
    //    POWERPIN[dut - 1] = ResultI[dut]["VHH"];
    //Print("DeepPowerDownCurrent %f ", POWERPIN[dut - 1]);
    //if ((Current_Pass_Low < POWERPIN[dut - 1]) && (POWERPIN[dut - 1] < Current_Pass_High))
    //{
    //    (*item)->SetValue(0);
    //}
    //else
    //{
    //    (*item)->SetValue(1);
    //}
    //DUT_LOOP_END
    double ForceHighVoltage;
    double ForceHighVoltage1;
    double Current_Pass_High;
    double Current_Pass_Low;
    ResultMap ResultI;
    double POWERPIN[100];
    string pf = "PASS";
    double vhhIClamp_High = 500 MA;
    double vhhIClamp_Low = -500 MA;
    double vhhILimit_Low = 0   MA;
    double vhhILimit_High = 3   MA;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("VHH", theParameter))
    {
    ForceHighVoltage = theParameter->GetValueAsDouble();
    //Print("ForceHighVoltage = %.2f V", ForceHighVoltage);
    }
    if (theParameters->TryGetParameter("VAA", theParameter))
    {
    ForceHighVoltage1 = theParameter->GetValueAsDouble();
    //Print("ForceHighVoltage1 = %.2f V", ForceHighVoltage1);
    }
    if (theParameters->TryGetParameter("DC_Test_high_limit", theParameter))
    {
    Current_Pass_High = theParameter->GetValueAsInt();
    //Print("Current_Pass_High = %d UA", Current_Pass_High);
    }
    if (theParameters->TryGetParameter("DC_Test_low_limit", theParameter))
    {
    Current_Pass_Low = theParameter->GetValueAsInt();
    //Print("Current_Pass_Low = %d UA", Current_Pass_Low);
    }
    Current_Pass_High = Current_Pass_High UA;
    Current_Pass_Low = Current_Pass_Low  UA;
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    DPS_Off("VHH");
    Time.Delay(1 MS);
    DPS_FV("VHH", ForceHighVoltage V, 500 MA, 500 MA, -500 MA, ENUM_SENSE_REMOTE);
    Time.Delay(5 MS);
    VI.SetIRange("VHH", 2.5 MA);
    VI.SetIClamp("VHH", 2.5 MA, -2.5 MA);
    Time.Delay(20 MS);
    //VI.SetMeasureParameter("VHH", 100, 100);
    VI.GetMeasureValue("VHH", ResultI);
    Print("---------------------------------------------------------------------VHH_Current----------------------------------------------------------------------");
    Print("%-15s %-15s %-20s %-12s %-12s %-10s %-10s %-15s %-18s %-18s %-18s", "PASS/FAIL", "TestNumber", "TestName", "SysID", "LocalID", "X", "Y", "PinList", "HighLimit(A)", "LowLimit(A)", "MeasuredValue(A)");
    DUT_LOOP_START
    POWERPIN[dut - 1] = ResultI[dut]["VHH"];
    //Print("DeepPowerDownCurrent %f ", POWERPIN[dut - 1]);
    if ((Current_Pass_Low < POWERPIN[dut - 1]) && (POWERPIN[dut - 1] < Current_Pass_High))
    {
    (*item)->SetValue(0);
    Print("%-15s %-15s %-20s %-12d %-12d %-10d %-10d %-15s %-18.10f %-18.10f %-18.10f", pf.data(), TestNumber.data(), TestName.data(), (*item)->GetSysID(), dut, dutx[dutz], duty[dutz], "VHH", Current_Pass_High, Current_Pass_Low, POWERPIN[dut - 1]);
    }
    else
    {
    pf = "FAIL";
    (*item)->SetValue(1);
    Print("%-15s %-15s %-20s %-12d %-12d %-10d %-10d %-15s %-18.10f %-18.10f %-18.10f", pf.data(), TestNumber.data(), TestName.data(), (*item)->GetSysID(), dut, dutx[dutz], duty[dutz], "VHH", Current_Pass_High, Current_Pass_Low, POWERPIN[dut - 1]);
    }
    DUT_LOOP_END
    //this->Info("[Test Item] TB_Force_VHH -- end");
    }

/**
* Constructor
*/
TB_Force_VHH::TB_Force_VHH(TestItemExecuteContext * aContext) : TestItem("TB_Force_VHH", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Force_VHH::~TB_Force_VHH() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Force_VHH::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Force_VHH::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Force_VHH::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Force_VHH::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Force_VHH::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Force_VHH::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Force_VHH, TestItemExecuteContext *)

