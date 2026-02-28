#include "interface/ONESInterfaceHeader.h"
#include "TB_Mem_Populate_Data.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Mem_Populate_Data::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here

    //this->Info("[Test Item] TB_Mem_Populate_Data -- started");
    // AC Param
    std::string Mem_Data_Input;
    int Mem_Ext_Write_Page;
    int Page_Length;
    int Cycle_Number;
    int TFB_Limit;
    int DFB_Limit;
    int WaitDummy;
    string pa;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("Page_Length", theParameter))
    {
    Page_Length = theParameter->GetValueAsInt();
    //Print("Page_Length =%d ", Page_Length);
    }
    if (theParameters->TryGetParameter("1st_Page_Addressain", theParameter))
    {
    pa = theParameter->GetValueAsString();
    //Print("1st_Page_Addressain s= %s", pa.c_str());
    Mem_Ext_Write_Page = std::stoi(pa.c_str(), nullptr, 16);
    //Print("1st_Page_Addressain = %d(dec) 0x%04x(hex)   ", Mem_Ext_Write_Page, Mem_Ext_Write_Page);
    }
    if (theParameters->TryGetParameter("Cycle_Number", theParameter))
    {
    Cycle_Number = theParameter->GetValueAsInt();
    //Print("Cycle_Number = %d", Cycle_Number);
    }
    if (theParameters->TryGetParameter("TFB_Limit", theParameter))
    {
    TFB_Limit = theParameter->GetValueAsInt();
    //Print("TFB_Limit = %d", TFB_Limit);
    }
    if (theParameters->TryGetParameter("DFB_Limit", theParameter))
    {
    DFB_Limit = theParameter->GetValueAsInt();
    //Print("DFB_Limit = %d", DFB_Limit);
    }
    if (theParameters->TryGetParameter("Wait_Dummy", theParameter))
    {
    WaitDummy = theParameter->GetValueAsInt();
    //Print("Wait_Dummy = %d", WaitDummy);
    }
    // AutoMation
    #ifdef RRAM_B2_AUTOMATION
    std::string logName = log_name_setting(aContext, lotnum, wafernum, Die_X, Die_Y, testname);
    #else
    std::string logName = log_name_setting(aContext, TestName);
    #endif
    //log_file_head_information();
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    //Mem_Data_Input =  "TJ_CFG_DEMO.txt";
    // Step4 Ext Write
    Array_result_t error_flag;
    for (int cycle = 0; cycle < Cycle_Number; cycle++)
    {
    //std::string theCfgFile = context->GetSiteContext()->GetDataFile(Mem_Data_Input);
    string theCfgFile = "TJ_CFG_DEMO.bin";
    Digital.DBM.Write(0, theCfgFile);
    Print("- imported %d bytes memory data from file %s", Page_Length * 128, logName.c_str());
    //testlog.Info("- imported {} bytes memory data from file {}", Page_Length * 128, logName);
    for (int page_num = 0; page_num < Page_Length; page_num++)
    {
    MemExtWritePopulateData(Mem_Ext_Write_Page + page_num * 0x80, page_num);
    #ifdef POLLING_DELAY
    usleep(5 * 1000);
    #endif
    // Polling Judge
    #ifdef POLLING_BY_JMATCH
    RRAM_TJ::Polling_Judge(theDUTs, POLLING_ONE_TIME_MEMEXT, Polling_Max);
    #else
    //Polling_Soft(aContext, "DO", POLLING_ONE_TIME_MEMEXT, WaitDummy);
    Polling_By_Mloop(aContext, "DO", POLLING_ONE_TIME_MBIST, WaitDummy);
    #endif
    }
    if (EXT_WRITE_READ)
    {
    // Step5 Read Data
    //0Bh-->read data
    MemExtReadPopulateData(Mem_Ext_Write_Page, Page_Length * 0x80);
    int Read_Bytes = Page_Length * 128;
    // uint Data[Read_Bytes]       = { 0 };
    // int error_bfr[Read_Bytes]   = { 0 };
    std::vector<uint32_t> Data(Read_Bytes, 0);
    std::vector<int> error_bfr(Read_Bytes, 0);
    std::vector<std::vector<int>> All_DUTs_Date(MAX_DUTS, std::vector<int>(MAX_BYTE_NUM_FULL, 0));
    // AFM Read
    DUT_LOOP_START
    Digital.AFM.Read(dut, 0, Data.data(), Read_Bytes);
    for (int j = 0; j < Read_Bytes; j++)
    {
    All_DUTs_Date[dutz][j] = Data[j];
    }
    DUT_LOOP_END
    // Data Check and Print
    std::vector <unsigned int> value(Read_Bytes, 0);
    Digital.DBM.Read(0, value.data(), Read_Bytes);
    Data_Compare_Ext_array_XOR_array(true_data_fmt, Read_Bytes, All_DUTs_Date, value, error_bfr, &error_flag, TFB_Limit, DFB_Limit, aContext);
    Data_Compare_Ext_print(true_data_fmt, Read_Bytes, All_DUTs_Date, Mem_Ext_Write_Page, &error_flag, aContext);
    }
    }
    if (EXT_WRITE_READ)
    {
    DUT_LOOP_START
    if (error_flag.error_flags[dutz][1] != 1)
    {
    (*item)->SetValue(1);
    TB_Mem_Populate_Data_1520[dut-1] =1;
    }
    DUT_LOOP_END
    }
    //this->Info("[Test Item] TB_Mem_Populate_Data -- end");
    }

/**
* Constructor
*/
TB_Mem_Populate_Data::TB_Mem_Populate_Data(TestItemExecuteContext * aContext) : TestItem("TB_Mem_Populate_Data", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Mem_Populate_Data::~TB_Mem_Populate_Data() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Mem_Populate_Data::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Mem_Populate_Data::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Mem_Populate_Data::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Mem_Populate_Data::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Mem_Populate_Data::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Mem_Populate_Data::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Mem_Populate_Data, TestItemExecuteContext *)

