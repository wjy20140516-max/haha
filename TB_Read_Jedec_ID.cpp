#include "interface/ONESInterfaceHeader.h"
#include "TB_Read_Jedec_ID.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Read_Jedec_ID::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Read_Jedec_ID -- started");
    double ForceHighVoltage;
    int Solid_Data = 0;
    bool specifyID = true;
    char cBuf[512] = { 0 };
    string pa;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("VAA", theParameter))
    {
    ForceHighVoltage = theParameter->GetValueAsDouble();
    //Print("ForceHighVoltage = %.2f V", ForceHighVoltage);
    }
    if (theParameters->TryGetParameter("Solid_Data", theParameter))
    {
    pa = theParameter->GetValueAsString();
    //Print("Solid_Data s= %s", pa.c_str());
    Solid_Data = std::stoi(pa.c_str(), nullptr, 16);
    //Print("Solid_Data = %d(dec) 0x%06x(hex)   ", Solid_Data, Solid_Data);
    }
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    unsigned int RD_JDE_ID1;
    unsigned int RD_JDE_ID2;
    unsigned int RD_JDE_ID3;
    if (specifyID)
    {
    RD_JDE_ID1 = (Solid_Data >> 16) & 0xFF;
    RD_JDE_ID2 = (Solid_Data >> 8) & 0xFF;
    RD_JDE_ID3 = Solid_Data & 0xFF;
    }
    Digital.AFM.Config(12, 12, "DO", ENUM_DATA_WIDTH_BIT_8, ENUM_ALPG_SDR, ENUM_ADDRESS_MODE_1);
    Digital.AFM.SetResultMode(ENUM_OVERWRITE);
    Digital.AFM.ResetData(0x11);
    Digital.Pattern.RunRegister("pReadJedecID", ENUM_PATTERNSTOP_INTERRUPT, 5 S);
    Digital.Pattern.RunModule("pReadJedecID", "fReadJedecID", ENUM_PATTERNSTOP_INTERRUPT, 1 S);
    Time.Delay(1 MS);
    DUT_LOOP_START
    update_local_time();
    unsigned int Data[3];
    Digital.AFM.Read(dut, 0, Data, 3);
    Print("[JEDID_RD]DUT%d Reg 9Fh = %02X %02X %02X (Hex)", dut, Data[0], Data[1], Data[2]);
    //testlog.Info("[JEDID_RD] Reg 9Fh = %02X %02X %02X (Hex)", Data[0], Data[1], Data[2]);
    if (specifyID)
    {
    // жChip ID
    if ((Data[0] == RD_JDE_ID1) && (Data[1] == RD_JDE_ID2) && (Data[2] == RD_JDE_ID3))
    {
    (*item)->SetValue(0);
    TB_Read_Jedec_ID_1510[dut-1] = 0;
    }
    else
    {
    (*item)->SetValue(1);
    TB_Read_Jedec_ID_1510[dut-1] = 1;
    }
    }
    else
    {
    // жChip ID
    if (((Data[0] == 0x00) || (Data[0] == 0xFF)) && ((Data[1] == 0x00) || (Data[1] == 0xFF)) && ((Data[2] == 0x00) || (Data[2] == 0xFF)))
    {
    (*item)->SetValue(0);
    TB_Read_Jedec_ID_1510[dut - 1] = 0;
    }
    else
    {
    (*item)->SetValue(1);
    TB_Read_Jedec_ID_1510[dut - 1] = 1;
    }
    }
    DUT_LOOP_END
    //this->Info("[Test Item] TB_Read_Jedec_ID -- end");
    }

/**
* Constructor
*/
TB_Read_Jedec_ID::TB_Read_Jedec_ID(TestItemExecuteContext * aContext) : TestItem("TB_Read_Jedec_ID", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Read_Jedec_ID::~TB_Read_Jedec_ID() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Read_Jedec_ID::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Read_Jedec_ID::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Read_Jedec_ID::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Read_Jedec_ID::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Read_Jedec_ID::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Read_Jedec_ID::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Read_Jedec_ID, TestItemExecuteContext *)

