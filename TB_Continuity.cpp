#include "interface/ONESInterfaceHeader.h"
#include "TB_Continuity.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Continuity::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Continuity -- started");
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    //Get_Local_Time(local_time_s, sizeof(local_time_s));
    //Print("");
    ////Print("[TEST_NUM]=#1010");
    //Print("[TEST_NUM]=#%s", TestNumber.c_str());
    ////Print("[CP_VER]=#Taiji1p8_CP_ProductionFlow_V1p1");
    //Print("[CP_VER]=#%s", TestFlow.c_str());
    ////Print("LotNum=B550064,WaferNum=B550064-14 Die_X=-1,Die_Y=-1 LOCAL TIME:2026-1-28 10:07:56 ");
    //
    //DUT_LOOP_START
    //Print("LotNum=%s,WaferNum=%s Die_X=%d,Die_Y=%d LOCAL TIME:%s ", LotNumber.c_str(),WaferId.c_str(),dutx[dutz], duty[dutz], local_time_s);
    //DUT_LOOP_END
    double VLimit_High;
    double VLimit_Low;
    double OS_PINS[100][4];
    double POWER_PINS[100];
    string pinname[4] = { "CS","DO","SCK","DI"};
    ResultMap theDoubleL;
    int FLG_PF_OS[DUT_NUM][3] = {0};
    ResultMap ResultV;
    ResultMap ResultD;
    ResultMap ResultDH;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("DC_Test_high_limit", theParameter))
    {
    VLimit_High = theParameter->GetValueAsDouble();
    //Print("VLimit_High = %.2f uA", VLimit_High);
    }
    if (theParameters->TryGetParameter("DC_Test_low_limit", theParameter))
    {
    VLimit_Low = theParameter->GetValueAsDouble();
    //Print("VLimit_Low = %.2f uA", VLimit_Low);
    }
    //this->Info("[Test Item] TB_Continuity -- started");
    Print("------------------------------------------------------------------TB_Continuity-Open------------------------------------------------------------------");
    Print("%-15s %-15s %-20s %-12s %-12s %-10s %-10s %-15s %-18s %-18s %-18s", "PASS/FAIL", "TestNumber", "TestName", "SysID", "LocalID", "X", "Y", "PinList", "HighLimit(V)", "LowLimit(V)", "MeasuredValue(V)");
    DPS_FV("VHH", 0 V, 25 MA, 25 MA, -25 MA, ENUM_SENSE_REMOTE);
    DPS_FV("VAA", 0 V, 25 MA, 25 MA, -25 MA, ENUM_SENSE_REMOTE);
    Time.Delay(1 MS);
    PMU_FI("pl_os_pins", -100 UA, 200 UA, 2 V, -2 V);
    Time.Delay(5 MS);
    PMU_MeasV("pl_os_pins", ResultV);
    string pf = "PASS";
    DUT_LOOP_START
    for (int i = 0; i < 4; i++)
    {
    OS_PINS[dut - 1][i] = ResultV[dut][pinname[i]];
    RsltVSS_OS_global[dut][pinname[i]] = ResultV[dut][pinname[i]];
    if ((VLimit_Low < OS_PINS[dut - 1][i]) && (OS_PINS[dut - 1][i] < VLimit_High))
    {
    Print("%-15s %-15s %-20s %-12d %-12d %-10d %-10d %-15s %-18.10f %-18.10f %-18.10f", pf.data(), TestNumber.data(), TestName.data(), (*item)->GetSysID(), dut, dutx[dutz], duty[dutz], pinname[i].data(), VLimit_High, VLimit_Low, OS_PINS[dut - 1][i]);
    }
    else
    {
    pf = "FAIL";
    Print("%-15s %-15s %-20s %-12d %-12d %-10d %-10d %-15s %-18.10f %-18.10f %-18.10f", pf.data(), TestNumber.data(), TestName.data(), (*item)->GetSysID(), dut, dutx[dutz], duty[dutz], pinname[i].data(), VLimit_High, VLimit_Low, OS_PINS[dut - 1][i]);
    FLG_PF_OS[dut - 1][0] = 1;
    }
    }
    DUT_LOOP_END
    PMU_Off("pl_os_pins");
    Print("");
    Print("------------------------------------------------------------------------VAA_OS------------------------------------------------------------------------");
    Print("%-15s %-15s %-20s %-12s %-12s %-10s %-10s %-15s %-18s %-18s %-18s", "PASS/FAIL", "TestNumber", "TestName", "SysID", "LocalID", "X", "Y", "PinList", "HighLimit(A)", "LowLimit(A)", "MeasuredValue(A)");
    VLimit_High = 0.00001;
    VLimit_Low = -0.00001;
    pf = "PASS";
    DPS_FV("VAA", 0.1 V, 25 UA, 25 UA, -25 UA, ENUM_SENSE_REMOTE);
    Time.Delay(5 MS);
    DPS_MI("VAA", ResultD);
    DUT_LOOP_START
    POWER_PINS[dut - 1] = ResultD[dut]["VAA"];
    Rslt_VAA_global[dut]["VAA"] = ResultD[dut]["VAA"];
    if ((VLimit_Low < POWER_PINS[dut - 1]) && (POWER_PINS[dut - 1] < VLimit_High))
    {
    Print("%-15s %-15s %-20s %-12d %-12d %-10d %-10d %-15s %-18.10f %-18.10f %-18.10f", pf.data(), TestNumber.data(), TestName.data(), (*item)->GetSysID(), dut, dutx[dutz], duty[dutz], "VAA", VLimit_High, VLimit_Low, POWER_PINS[dut - 1]);
    }
    else
    {
    pf = "FAIL";
    FLG_PF_OS[dut - 1][1] = 1;
    Print("%-15s %-15s %-20s %-12d %-12d %-10d %-10d %-15s %-18.10f %-18.10f %-18.10f", pf.data(), TestNumber.data(), TestName.data(), (*item)->GetSysID(), dut, dutx[dutz], duty[dutz], "VAA", VLimit_High, VLimit_Low, POWER_PINS[dut - 1]);
    }
    DUT_LOOP_END
    VI.ForceV("VAA", 0 V);
    DPS_Off("VAA");
    Print("");
    Print("---------------------------------------------------------------------VHH_Current----------------------------------------------------------------------");
    Print("%-15s %-15s %-20s %-12s %-12s %-10s %-10s %-15s %-18s %-18s %-18s", "PASS/FAIL", "TestNumber", "TestName", "SysID", "LocalID", "X", "Y", "PinList", "HighLimit(A)", "LowLimit(A)", "MeasuredValue(A)");
    VLimit_High = 0.00001;
    VLimit_Low = -0.00001;
    pf = "PASS";
    DPS_FV("VHH", 0.1 V, 25 UA,25 UA, -25 UA, ENUM_SENSE_REMOTE);
    Time.Delay(5 MS);
    DPS_MI("VHH", ResultDH);
    DUT_LOOP_START
    POWER_PINS[dut - 1] = ResultDH[dut]["VHH"];
    Rslt_VHH_global[dut]["VHH"] = ResultDH[dut]["VHH"];
    if ((VLimit_Low < POWER_PINS[dut - 1]) && (POWER_PINS[dut - 1] < VLimit_High))
    {
    Print("%-15s %-15s %-20s %-12d %-12d %-10d %-10d %-15s %-18.10f %-18.10f %-18.10f", pf.data(), TestNumber.data(), TestName.data(), (*item)->GetSysID(), dut, dutx[dutz], duty[dutz], "VHH", VLimit_High, VLimit_Low, POWER_PINS[dut - 1]);
    }
    else
    {
    pf = "FAIL";
    FLG_PF_OS[dut - 1][2]= 1;
    Print("%-15s %-15s %-20s %-12d %-12d %-10d %-10d %-15s %-18.10f %-18.10f %-18.10f", pf.data(), TestNumber.data(), TestName.data(), (*item)->GetSysID(), dut, dutx[dutz], duty[dutz], "VHH", VLimit_High, VLimit_Low, POWER_PINS[dut - 1]);
    }
    DUT_LOOP_END
    DPS_Off("VHH");
    DUT_LOOP_START
    if ((FLG_PF_OS[dut - 1][0]== 1) || (FLG_PF_OS[dut - 1][1] == 1) || (FLG_PF_OS[dut - 1][2] == 1))
    {
    (*item)->SetValue(1);
    }
    else
    {
    (*item)->SetValue(0);
    }
    DUT_LOOP_END
    //this->Info("[Test Item] TB_Continuity -- end");
    }

/**
* Constructor
*/
TB_Continuity::TB_Continuity(TestItemExecuteContext * aContext) : TestItem("TB_Continuity", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Continuity::~TB_Continuity() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Continuity::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Continuity::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Continuity::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Continuity::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Continuity::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Continuity::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Continuity, TestItemExecuteContext *)

