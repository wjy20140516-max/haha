#include "interface/ONESInterfaceHeader.h"
#include "TB_Load_CRegs_from_File.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Load_CRegs_from_File::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Load_CRegs_from_File -- started");
    double ForceVoltage;
    //std::string Cfg_Filename;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("VAA", theParameter))
    {
    ForceVoltage = theParameter->GetValueAsDouble();
    //Print("ForceHighVoltage = %.2f V", ForceVoltage);
    }
    if (test_mode_debug_power)
    {
    PMU_DigitalSet("pl_function_pins", 1.65 V, 0, 0.8 V, 0.8 V);
    DPS_FV("VAA", 1.65 V, 500 MA, 500 MA, -500 MA, ENUM_SENSE_REMOTE);
    }
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    AFM_CONFIG_SET("DO", 12, 12, aContext);
    Digital.UBM.Config("DI");
    DUT_LOOP_START
    Digital.UBM.Write(dut, ENUM_D_TYPE, 0, ubm_data[dut - 1], 96);
    DUT_LOOP_END
    // write cfg reg
    Digital.Pattern.RunModule("pWriteCfgRegUbm", "fWriteCfgRegUbm", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
    // read cfg reg
    Digital.Pattern.RunModule("pReadCfgReg", "fReadCfgReg", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
    //AFM_READ_Non_cross_VP(96, 0, 0x00, aContext);
    Time.Delay(1 MS);
    unsigned int rdata[96];
    string testitem = (aContext->GetActiveTestName()).c_str();
    DUT_LOOP_START
    Digital.AFM.Read(dut, 0, rdata, 96);
    int r = 0;
    //Get_Local_Time_1(local_time_s, sizeof(local_time_s));
    update_local_time();
    this->Info("Start_Addr=000000h,Byte Num=96");
    this->Info("[CR_RD] 		   Hex  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
    for (int j = 0; j < 6; j++)
    {
    Print("[CR_RD]Dut %d %06XH-%06XH:%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
    dut, r, r + 15, rdata[r], rdata[r + 1], rdata[r + 2], rdata[r + 3], rdata[r + 4], rdata[r + 5], rdata[r + 6], rdata[r + 7],
    rdata[r + 8], rdata[r + 9], rdata[r + 10], rdata[r + 11], rdata[r + 12], rdata[r + 13], rdata[r + 14], rdata[r + 15]);
    r = r + 16;
    }
    (*item)->SetValue(0);
    if (testitem == "1050_TB_Load_CRegs_from_File")
    {
    TB_Load_CRegs_from_File_1050[dut - 1] = 0;
    }
    if (testitem == "1320_TB_Load_CRegs_from_File")
    {
    TB_Load_CRegs_from_File_1320[dut - 1] = 0;
    }
    DUT_LOOP_END
    //this->Info("[Test Item] TB_Load_CRegs_from_File -- end");
    }

/**
* Constructor
*/
TB_Load_CRegs_from_File::TB_Load_CRegs_from_File(TestItemExecuteContext * aContext) : TestItem("TB_Load_CRegs_from_File", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Load_CRegs_from_File::~TB_Load_CRegs_from_File() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Load_CRegs_from_File::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Load_CRegs_from_File::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Load_CRegs_from_File::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Load_CRegs_from_File::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Load_CRegs_from_File::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Load_CRegs_from_File::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Load_CRegs_from_File, TestItemExecuteContext *)

