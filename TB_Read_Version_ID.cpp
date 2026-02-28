#include "interface/ONESInterfaceHeader.h"
#include "TB_Read_Version_ID.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Read_Version_ID::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Read_Version_ID -- started");
    std::string testname;
    bool VersionID = true;
    int Solid_Data = 0;
    string Solid_Data_1 = "";
    // Ac Param
    double ForceHighVoltage;
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("VAA", theParameter))
    {
    ForceHighVoltage = theParameter->GetValueAsDouble();
    //Print("ForceHighVoltage = %.2f V", ForceHighVoltage);
    }
    if (theParameters->TryGetParameter("Solid_Data", theParameter))
    {
    theParameter->GetValueAsString();
    //Solid_Data = theParameter->GetValueAsString();
    Solid_Data_1 = theParameter->GetValueAsString();
    //Print("Solid_Data_1 = %s", Solid_Data_1.c_str());
    Solid_Data = std::stoul(Solid_Data_1, nullptr, 16);
    //Print("Solid_Data =  %04X", Solid_Data);
    }
    unsigned int CHIP_ID_SECOND_BYTE;
    unsigned int CHIP_ID_THIRD_BYTE;
    if (VersionID)
    {
    CHIP_ID_THIRD_BYTE = (Solid_Data >> 8) & 0xFF;
    CHIP_ID_SECOND_BYTE = Solid_Data & 0xFF;
    }
    if (test_mode_debug_power)
    //if (1)
    {
    PMU_FV("pl_function_pins", 0 V, 25 MA, 25 MA, -25 MA);
    DPS_FV("VAA", 0 V, 500 MA, 500 MA, -500 MA, ENUM_SENSE_REMOTE);
    PMU_DigitalSet("pl_function_pins", 1.65, 0, 0.83, 0.83);
    DPS_FV("VAA", 1.65 V, 500 MA, 500 MA, -500 MA, ENUM_SENSE_REMOTE);
    }
    AFM_CONFIG_SET("DO", 12, 12, aContext);
    TRegWrite(0x00, 0x90);
    //Digital.Pattern.RunRegister("pReadChipID", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
    Digital.Pattern.RunModule("pReadChipID", "fReadChipID", ENUM_PATTERNSTOP_INTERRUPT, 1 S);
    Time.Delay(1 MS);
    //AFM_READ_Non_cross_VP(3, 0, 0x00, aContext);//DEBUG
    unsigned rdata[3];
    DUT_LOOP_START
    //Get_Local_Time_1(local_time_s, sizeof(local_time_s));
    update_local_time();
    Digital.AFM.Read(dut, 0, rdata, 3);
    //Print("[SR_RD] Reg 05h[dut%d] = %02X %02X %02X (Hex)", dut, rdata[0], rdata[1], rdata[2]);
    Print("[SR_RD] Reg 05h = %02X %02X %02X (Hex)", rdata[0], rdata[1], rdata[2]);
    if ((rdata[1] == CHIP_ID_SECOND_BYTE) && (rdata[2] == CHIP_ID_THIRD_BYTE)) {
    // ETLog::Info(50, "TB_Read_Version_ID chip expect and read compare:", true);
    // testlog.Info(50, "TB_Read_Version_ID chip expect and read compare:", true);
    (*item)->SetValue(0);
    TB_Read_Version_ID_1030[dut-1] = 0;
    }
    else {
    //Print("TB_Read_Version_ID chip expect and read compare:", false);
    // testlog.Info(50, "TB_Read_Version_ID chip expect and read compare:", false);
    (*item)->SetValue(1);
    TB_Read_Version_ID_1030[dut - 1] = 1;
    }
    DUT_LOOP_END
    TRegWrite(0x00, 0x00);
    //this->Info("[Test Item] TB_Read_Version_ID -- end");
    }

/**
* Constructor
*/
TB_Read_Version_ID::TB_Read_Version_ID(TestItemExecuteContext * aContext) : TestItem("TB_Read_Version_ID", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Read_Version_ID::~TB_Read_Version_ID() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Read_Version_ID::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Read_Version_ID::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Read_Version_ID::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Read_Version_ID::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Read_Version_ID::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Read_Version_ID::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Read_Version_ID, TestItemExecuteContext *)

