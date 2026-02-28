#include "interface/ONESInterfaceHeader.h"
#include "TB_Float_VHH.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Float_VHH::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Float_VHH -- started");
    // Force Voltage
    double ForceLowVoltage;
    ResultMap ResultV;
    double POWERPIN[100];
    // Param Set
    double VLimit_High;
    double VLimit_Low;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("VHH", theParameter))
    {
    ForceLowVoltage = theParameter->GetValueAsDouble();
    //Print("ForceLowVoltage = %.2f V", ForceLowVoltage);
    }
    if (theParameters->TryGetParameter("DC_Test_high_limit", theParameter))
    {
    VLimit_High = theParameter->GetValueAsInt();
    //Print("VLimit_High = %d uV", VLimit_High);
    }
    if (theParameters->TryGetParameter("DC_Test_low_limit", theParameter))
    {
    VLimit_Low = theParameter->GetValueAsInt();
    //Print("VLimit_Low = %d uV", VLimit_Low);
    }
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    VLimit_High = VLimit_High  UV;
    VLimit_Low = VLimit_Low   UV;
    double vhhIClamp_High = 1200 UA;
    double vhhIClamp_Low = -1200 UA;
    double vhhVLimit_Low = 2.8 V;
    double vhhVLimit_High = 3.1 V;
    string pf = "PASS";
    DPS_FV("VHH", 0 V, 1200 MA, 1200 MA, -1200 MA, ENUM_SENSE_REMOTE);
    Time.Delay(5 MS);
    DPS_Off("VHH");
    VI.Connect("VHH");
    VI.SetPMUMode("VHH", PMU_MVM);
    VI.TurnOn("VHH");
    VI.GetMeasureValue("VHH", ResultV);
    string testitem = (aContext->GetActiveTestName()).c_str();
    Print("---------------------------------------------------------------------VHH_Voltage----------------------------------------------------------------------");
    Print("%-15s %-15s %-20s %-12s %-12s %-10s %-10s %-15s %-18s %-18s %-18s", "PASS/FAIL", "TestNumber", "TestName", "SysID", "LocalID", "X", "Y", "PinList", "HighLimit(V)", "LowLimit(V)", "MeasuredValue(V)");
    DUT_LOOP_START
    POWERPIN[dut - 1] = ResultV[dut]["VHH"];
    if (testitem == "1250_TB_Float_VHH")
    {
    TB_Float_VHH_1250[dut - 1] = ResultV[dut]["VHH"];
    }
    if (testitem == "1400_TB_Float_VHH")
    {
    TB_Float_VHH_1400[dut - 1] = ResultV[dut]["VHH"];
    }
    //Print("DeepPowerDownCurrent %f ", POWERPIN[dut - 1]);
    if ((VLimit_Low < POWERPIN[dut - 1]) && (POWERPIN[dut - 1] < VLimit_High))
    {
    (*item)->SetValue(0);
    Print("%-15s %-15s %-20s %-12d %-12d %-10d %-10d %-15s %-18.10f %-18.10f %-18.10f", pf.data(), TestNumber.data(), TestName.data(), (*item)->GetSysID(), dut, dutx[dutz], duty[dutz], "VHH", VLimit_High, VLimit_Low, POWERPIN[dut - 1]);
    }
    else
    {
    pf = "FAIL";
    (*item)->SetValue(1);
    Print("%-15s %-15s %-20s %-12d %-12d %-10d %-10d %-15s %-18.10f %-18.10f %-18.10f", pf.data(), TestNumber.data(), TestName.data(), (*item)->GetSysID(), dut, dutx[dutz], duty[dutz], "VHH", VLimit_High, VLimit_Low, POWERPIN[dut - 1]);
    }
    DUT_LOOP_END
    DPS_Off("VHH");
    Time.Delay(5 MS);
    //this->Info("[Test Item] TB_Float_VHH -- end");
    }

/**
* Constructor
*/
TB_Float_VHH::TB_Float_VHH(TestItemExecuteContext * aContext) : TestItem("TB_Float_VHH", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Float_VHH::~TB_Float_VHH() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Float_VHH::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Float_VHH::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Float_VHH::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Float_VHH::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Float_VHH::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Float_VHH::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Float_VHH, TestItemExecuteContext *)

