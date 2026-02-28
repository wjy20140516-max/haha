#include "interface/ONESInterfaceHeader.h"
#include "TB_Chip_Erase.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Chip_Erase::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here
    int DPSILimit_High;
    int DPSILimit_Low;
    ResultMap ResultI;
    int WaitDummy;
    double POWERPIN[100];
    double vaa;
    int cycle_number;
    int archive_point;
    string pa;
    // Get User Variable
    //test_num = context->GetSiteContext()->GetCurrentUnit()->GetNumber();
    test_num = TestNumber;
    //RRAM_TJ::GetUserVariable<std::string>(context, "ConditionTableName", cp_ver);
    //RRAM_TJ::GetUserVariable<std::string>(context, "Save_to_File(String)", testname);
    //RRAM_TJ::GetUserVariable<double>(context, "DC Test high limit", dpsILimit_High);
    //RRAM_TJ::GetUserVariable<double>(context, "DC Test low limit", dpsILimit_Low);
    //RRAM_TJ::GetUserVariable<int>(context, "Wait Dummy(Dec)", WaitDummy);
    //string pa;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("DC_Test_high_limit", theParameter))
    {
    DPSILimit_High = theParameter->GetValueAsInt();
    //Print("DC_Test_high_limit = %d UA", dpsILimit_High);
    }
    if (theParameters->TryGetParameter("DC_Test_low_limit", theParameter))
    {
    DPSILimit_Low = theParameter->GetValueAsInt();
    //Print("DC_Test_high_limit = %d UA", dpsILimit_Low);
    }
    if (theParameters->TryGetParameter("Wait_Dummy", theParameter))
    {
    WaitDummy = theParameter->GetValueAsInt();
    //Print("Wait_Dummy = %d ", WaitDummy);
    }
    if (theParameters->TryGetParameter("VAA", theParameter))
    {
    vaa = theParameter->GetValueAsDouble();
    //Print("VAA = %.2f ", vaa);
    }
    if (theParameters->TryGetParameter("Cycle_Number", theParameter))
    {
    cycle_number = theParameter->GetValueAsInt();
    //Print("Cycle_Number = %d ", cycle_number);
    }
    if (theParameters->TryGetParameter("Archive_Point", theParameter))
    {
    pa = theParameter->GetValueAsString();
    //Print("Archive_Point s= %s", pa.c_str());
    archive_point = std::stoi(pa.c_str(), nullptr, 16);
    //Print("Archive_Point = %d(dec) 0x%04x(hex)   ", archive_point, archive_point);
    }
    double dpsILimit_Low;
    double dpsILimit_High;
    dpsILimit_High = DPSILimit_High UA;
    dpsILimit_Low = DPSILimit_Low  UA;
    double VIH = 1.65 V;
    double VIL = 0 V;
    double VOH = VIH * 0.55 V;
    double VOL = VIH * 0.45 V;
    //Print("VIH %f", VIH);
    //Print("VIL %f", VIL);
    //Print("VOH %f", VOH);
    //Print("VOL %f", VOL);
    PMU_DigitalSet("pl_function_pins", VIH, VIL, VOH, VOL);
    DPS_FV("VAA", 1.65 V, 500 MA, 500 MA, -500 MA, ENUM_SENSE_REMOTE);
    Time.Delay(2 MS);
    // Switch WaveForm
    //RRAM_TJ::SwitchWaveForm(context);
    // AutoMation
    #ifdef RRAM_B2_AUTOMATION
    std::string logName = RRAM_TJ::log_name_setting(context->GetSiteContext(), lotnum, wafernum, Die_X, Die_Y, testname);
    #else
    //std::string logName = RRAM_TJ::log_name_setting(context->GetSiteContext(), testname);
    #endif
    // Log Head Info
    //UserLog testlog(logName);
    //RRAM_TJ::log_file_head_information(testlog, test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    int precision = 10;
    #ifdef POLLING_BY_JMATCH
    // Polling PreSet
    int Polling_Max = WaitDummy / POLLING_ONE_TIME_MBIST;
    RRAM_TJ::Polling_Preset(context, "DO", Polling_Max);
    #endif
    auto start = std::chrono::high_resolution_clock::now();
    std::string PatternName = "pChipErase";
    std::string FuncName = "fChipErase";
    string pf = "PASS";
    //Pattern::Run(PatternName, FuncName, true, InterruptType::INT_ANY, 5 * 1000 * 1000);
    AFM_CONFIG_SET("DO", 12, 12, aContext);
    Digital.Pattern.RunRegister("pChipErase", ENUM_PATTERNSTOP_INTERRUPT, 1 S);
    Digital.Pattern.RunModule("pChipErase", "fChipErase", ENUM_PATTERNSTOP_INTERRUPT, 50 S);
    // Delay 3ms
    usleep(1 * 1000);
    //adc::Measure(context, theDUTs, "VAA", dpsILimit_Low, dpsILimit_High);
    //VI.GetMeasureValue("VAA", ResultI);
    //site::OutputCurrentToLog(testlog, "TB_Chip_Erase_Current", "VAA", precision);
    VI.GetMeasureValue("VAA", ResultI);
    Print("----------------------------------------------------------------TB_Chip_Erase_Current-----------------------------------------------------------------");
    Print("%-15s %-15s %-20s %-12s %-12s %-10s %-10s %-15s %-18s %-18s %-18s", "PASS/FAIL", "TestNumber", "TestName", "SysID", "LocalID", "X", "Y", "PinList", "HighLimit(A)", "LowLimit(A)", "MeasuredValue(A)");
    DUT_LOOP_START
    POWERPIN[dut - 1] = ResultI[dut]["VAA"];
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
    Print(" ");
    Print(" ");
    // Polling
    #ifdef POLLING_BY_JMATCH
    RRAM_TJ::Polling_Judge(theDUTs, POLLING_ONE_TIME_MBIST, Polling_Max);
    #else
    //RRAM_TJ::Polling_Soft(theDUTs, "DO", POLLING_ONE_TIME_MBIST, WaitDummy);
    //Polling_Soft(aContext, "DO", POLLING_ONE_TIME_MBIST, WaitDummy);
    Polling_By_Mloop(aContext, "DO", POLLING_ONE_TIME_MBIST, WaitDummy);
    #endif
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm = end - start;
    //ETLog::Info("- Issue MBIST WRITE: MEM_Address={:04X}00h, MEM_Data=FFh, MBIST in DDW Mode, Cycle#{}, dut<{}:1>=0x{:02X})", 0, 1, MAX_DUTS, MAX_DUTS);
    //ETLog::Info("Mbist Elapsed Time (sec){:.6f}  ", tm.count() / 1000);
    Print("- Issue MBIST WRITE: MEM_Address=%04X00h, MEM_Data=FFh, MBIST in DDW Mode, Cycle#%d, dut<%d:1>=0x%02X)", 0, 1, MAX_DUTS, MAX_DUTS);
    //for (auto itDUT : *theDUTs)
    //{
    DUT_LOOP_START
    //int i = itDUT->GetLocalID();
    Print("DUT %d Polling Elapsed Time(sec) %.6f", dut, PST.Polling_Count[dut-1] / 1000);
    DUT_LOOP_END
    //}
    Print("Mbist Elapsed Time (sec)%.6f  ", tm.count() / 1000);
    //// Bin Judge
    //std::string FailBin = "-1";
    //RRAM_TJ::GetUserVariable<std::string>(context, "FailBin#", FailBin);
    //// -1 зbin
    //if (FailBin == "-1")
    //{
    //    theDUTs->SetResult(0);
    //}
    //debug
    // for(auto itDUT : *theDUTs) {
    //     itDUT->SetResult(0);
    // }
    //    this->Info("[Test Item] TB_Chip_Erase_Current -- end");
    //
    }

/**
* Constructor
*/
TB_Chip_Erase::TB_Chip_Erase(TestItemExecuteContext * aContext) : TestItem("TB_Chip_Erase", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Chip_Erase::~TB_Chip_Erase() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Chip_Erase::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Chip_Erase::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Chip_Erase::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Chip_Erase::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Chip_Erase::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Chip_Erase::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Chip_Erase, TestItemExecuteContext *)

