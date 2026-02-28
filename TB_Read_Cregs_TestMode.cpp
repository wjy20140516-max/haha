#include "interface/ONESInterfaceHeader.h"
#include "TB_Read_Cregs_TestMode.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Read_Cregs_TestMode::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Read_Cregs_TestMode -- started");
    double ForceVoltage;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("VAA", theParameter))
    {
    ForceVoltage = theParameter->GetValueAsDouble();
    //Print("ForceHighVoltage = %.2f V", ForceVoltage);
    }
    //std::string test_num = "1020";
    //std::string cp_ver = "Taiji1p8_CP_ProductionFlow_V1p1";
    //std::string lotnum = "B550064";
    //std::string wafernum = "B550064-14";
    //int Die_X = 0;
    //int Die_Y = 0;
    //std::string testname;
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    PMU_DigitalSet("pl_function_pins", 1.65 V, 0, 0.8 V, 0.8 V);
    DPS_FV("VAA", 1.65 V, 500 MA, 500 MA, -500 MA, ENUM_SENSE_REMOTE);
    Time.Delay(5 MS);
    AFM_CONFIG_SET("DO", 12, 12, aContext);
    //---------------------------
    //EnterTestModeTJ;//ûЧע⣡
    Digital.Pattern.RunRegister("pEnterTestModeTJ", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
    Digital.Pattern.RunModule("pEnterTestModeTJ", "fEnterTestModeTJ", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
    Time.Delay(5 MS);
    //---------------------------
    Digital.Pattern.RunRegister("pReadCfgReg", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
    Digital.Pattern.RunModule("pReadCfgReg", "fReadCfgReg", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
    Time.Delay(1 MS);
    unsigned int rdata[96];
    DUT_LOOP_START
    Digital.AFM.Read(dut, 0, rdata, 96);
    int r = 0;
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
    TB_Read_Cregs_TestMode_1020[dut - 1] = 0;
    TB_Read_Cregs_TestMode_1540[dut - 1] = 0;
    DUT_LOOP_END
    //this->Info("[Test Item] TB_Read_Cregs_TestMode -- end");
    }

/**
* Constructor
*/
TB_Read_Cregs_TestMode::TB_Read_Cregs_TestMode(TestItemExecuteContext * aContext) : TestItem("TB_Read_Cregs_TestMode", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Read_Cregs_TestMode::~TB_Read_Cregs_TestMode() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Read_Cregs_TestMode::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Read_Cregs_TestMode::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Read_Cregs_TestMode::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Read_Cregs_TestMode::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Read_Cregs_TestMode::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Read_Cregs_TestMode::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Read_Cregs_TestMode, TestItemExecuteContext *)

