#include "interface/ONESInterfaceHeader.h"
#include "TB_Mem_Ext_Read_vsFFh_User.h"
#include "Common.h"
#include "OnlineTrim.h"
#include "Driver.h"
#include <sys/time.h>

/**
* Run test
*/
void TB_Mem_Ext_Read_vsFFh_User::Run(TestItemExecuteContext * aContext) {
	this->UserRun(aContext);
	//Add code here
    //this->Info("[Test Item] TB_Mem_Ext_Read_vsFFh_User -- started");


    // AC Param
    std::string Cfg_Filename;
    int Frist_DAC;
    int Last_DAC;
    int DAC_Step;
    int Mbist_Start_Page;
    int Mbist_Pages;
    int TFB_Limit;
    int DFB_Limit;

    // Get User Variable
   // test_num = context->GetSiteContext()->GetCurrentUnit()->GetNumber();
   // RRAM_TJ::GetUserVariable<std::string>(context, "ConditionTableName", cp_ver);
   // RRAM_TJ::GetUserVariable<std::string>(context, "Save_to_File(String)", testname);
   // RRAM_TJ::GetUserVariable<std::string>(context, "Creg Config File(String)", Cfg_Filename);
   // RRAM_TJ::GetUserVariable<int>(context, "Page Length(Dec)", Mbist_Pages);
   // //RRAM_TJ::ConvertHex(context, "the First DAC(hex)", Frist_DAC);
   ////RRAM_TJ::ConvertHex(context, "the Last DAC(hex)", Last_DAC);
   // //RRAM_TJ::ConvertHex(context, "DAC Step(hex)", DAC_Step);
   // RRAM_TJ::ConvertHex(context, "1st Page Addressain<23:0>(Hex)", Mbist_Start_Page);
   // RRAM_TJ::GetUserVariable<int>(context, "TFB_Limit(Dec)", TFB_Limit);
   // RRAM_TJ::GetUserVariable<int>(context, "DFB_Limit(Dec)", DFB_Limit);



    string pa;
    TestExecuteParameterCollection* theParameters = aContext->GetParameters();
    TestExecuteParameter* theParameter = nullptr;
    if (theParameters->TryGetParameter("Page_Length", theParameter))
    {
        Mbist_Pages = theParameter->GetValueAsInt();
        //Print("Page_Length = %d", Mbist_Pages);
    }
    if (theParameters->TryGetParameter("1st_Page_Addressain", theParameter))
    {
        pa = theParameter->GetValueAsString();
        //Print("1st_Page_Addressain s= %s", pa.c_str());
        Mbist_Start_Page = std::stoi(pa.c_str(), nullptr, 16);
        //Print("1st_Page_Addressain = %d(dec) 0x%04x(hex)   ", Mbist_Start_Page, Mbist_Start_Page);
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





    Cfg_Filename = Cfg_Filename + ".txt";





    // Switch WaveForm
    //RRAM_TJ::SwitchWaveForm(context);

    // AutoMation
#ifdef RRAM_B2_AUTOMATION
    std::string logName = RRAM_TJ::log_name_setting(context->GetSiteContext(), lotnum, wafernum, Die_X, Die_Y, testname);
#else
    std::string logName = log_name_setting(aContext, testname);
#endif

    // Log Head Info
   // UserLog testlog(logName);
    //log_file_head_information(testlog, test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);
    log_file_head_information(test_num, cp_ver, lotnum, wafernum, Die_X, Die_Y);

   // AFM::Config(12, 12, "DO", Data_Width_Mode::bit_8, BitCompress_Mode::bitCompress_1);
    AFM_CONFIG_SET("DO", 12, 12, aContext);
    // Step1 Load CFG And Compare
   // LoadConfigFile(context, Cfg_Filename, testlog, false);
    LoadConfigFile(aContext, false, "TJ_CFG_DEMO.bin");

    // Step2 Read Data
    int Mbist_Page_Bytes = MBIST_READ_USER_PAGE;
    int Read_Bytes = Mbist_Pages * Mbist_Page_Bytes;//8192*128

    TRegWrite(0x03, OP_DDW_OFF);
    if (TURN_ON_TR_VFY)
    {
        int TReg_ReadData[MAX_DUTS] = { 0 };
        TRegRead(aContext, 0x03, TReg_ReadData);
       // for (auto itDUT : *theDUTs)
       // {
        DUT_LOOP_START
           // int dut = itDUT->GetLocalID();
            if (TURN_ON_TR_BIN)
            {
                if (TReg_ReadData[dut-1] != OP_DDW_OFF)
                {
                   // ETLog::Info("[TR_RD_ERROR] Read T-Reg Add {:02X}h = {:02X}", 0x03, TReg_ReadData[dut]);
                    //testlog.Info("[TR_RD_ERROR] Read T-Reg Add {:02X}h = {:02X}", 0x03, TReg_ReadData[dut]);
                    Print("[TR_RD_ERROR] Read T-Reg Add %02Xh = %02X", 0x03, TReg_ReadData[dut-1]);

             
                    //itDUT->SetResult(1);
                      (*item)->SetValue(1);
                }
            }
       // }
            DUT_LOOP_END
    }

    auto start = std::chrono::high_resolution_clock::now();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm = end - start;
    //ETLog::Info("TB_Mem_Ext_Read_vsFFh_User- array ecr  read cost {:.6f} second", tm.count() / 1000);
    //testlog.Info("TB_Mem_Ext_Read_vsFFh_User- array ecr  read cost {:.6f} second", tm.count() / 1000);
   Print("TB_Mem_Ext_Read_vsFFh_User- array ecr  read cost %.6f second", tm.count() / 1000);
    // Data Check and Print
    auto start1 = std::chrono::high_resolution_clock::now();


    MemExtReadPopulateData(Mbist_Start_Page, Mbist_Pages * 0x80);


    std::vector <unsigned int> value(Read_Bytes, 0xFF);
    std::vector<uint32_t> Data(Read_Bytes, 0);
    Array_result_t error_flag;

   // int error_bfr[Read_Bytes] = { 0 };
    int error_bfr[8192 * 128] = { 0 };
   
    std::vector<std::vector<int>> All_DUTs_Date(MAX_DUTS, std::vector<int>(MAX_BYTE_NUM_FULL, 0));
    // AFM Read
    //for (auto itDUT : *theDUTs) {
        //int dut = itDUT->GetLocalID();
       // ET_AFMRead(dut, 0, Data.data(), Read_Bytes);
        DUT_LOOP_START
            Digital.AFM.Read(dut, 0, Data.data(), Read_Bytes);
        for (int j = 0; j < Read_Bytes; j++)
        {
            All_DUTs_Date[dut-1][j] = Data[j];
        }
        DUT_LOOP_END
   // }



    Data_Compare_vsFF_User_array_print(true_data_fmt, Read_Bytes, All_DUTs_Date, 0xFF, error_bfr, &error_flag, Mbist_Start_Page, TFB_Limit, DFB_Limit, aContext);

    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm1 = end1 - start1;
    //ETLog::Info("TB_Mem_Ext_Read_vsFFh_User- array print log cost {:.6f} second", tm1.count() / 1000);
    //testlog.Info("TB_Mem_Ext_Read_vsFFh_User- array print log cost {:.6f} second", tm1.count() / 1000);
    Print("TB_Mem_Ext_Read_vsFFh_User- array print log cost %.6f second", tm1.count() / 1000);
    // Judge
  //  for (auto itDUT : *theDUTs)
    //{
    DUT_LOOP_START
        //int dut = itDUT->GetLocalID();
        if ((error_flag.error_flags[dut-1][DFB_LMT_FLAG] != 1) || (error_flag.error_flags[dut-1][DFB_LMT_FLAG] != 1))
        {
            //itDUT->SetResult(1);
            (*item)->SetValue(1);
        }
        DUT_LOOP_END
   // }



    //// Bin Judge
    //std::string FailBin = "-1";
    //RRAM_TJ::GetUserVariable<std::string>(context, "FailBin#", FailBin);
    //// -1 不进行分bin
    //if (FailBin == "-1")
    //{
    //    theDUTs->SetResult(0);
    //}



    // Test End
    //ETLog::Info("[Test Item] TB_Mem_Ext_Read_vsFFh_User -- end\r\n");

    //this->Info("[Test Item] TB_Mem_Ext_Read_vsFFh_User -- end\r\n");

    }

/**
* Constructor
*/
TB_Mem_Ext_Read_vsFFh_User::TB_Mem_Ext_Read_vsFFh_User(TestItemExecuteContext * aContext) : TestItem("TB_Mem_Ext_Read_vsFFh_User", aContext){
	//DO NOT add code here unless necessary.
}

/**
* Destructor
*/
TB_Mem_Ext_Read_vsFFh_User::~TB_Mem_Ext_Read_vsFFh_User() {
	//DO NOT add code here unless necessary.
}

/**
* Init test
*/
bool TB_Mem_Ext_Read_vsFFh_User::Initialize(TestItemExecuteContext * aContext) {
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
void TB_Mem_Ext_Read_vsFFh_User::Exit(TestItemExecuteContext * aContext) {
	this->UserExit(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Pause test
*/
void TB_Mem_Ext_Read_vsFFh_User::Pause(TestItemExecuteContext * aContext) {
	this->UserPause(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Resume test
*/
void TB_Mem_Ext_Read_vsFFh_User::Resume(TestItemExecuteContext * aContext) {
	this->UserResume(aContext);
	//DO NOT add code here unless necessary.
}

/**
* Stop test
*/
void TB_Mem_Ext_Read_vsFFh_User::Stop(TestItemExecuteContext * aContext) {
	this->UserStop(aContext);
	//DO NOT add code here unless necessary.
}

#ifdef USER_AFTER_BIN
/**
* AfterBin test
*/
void TB_Mem_Ext_Read_vsFFh_User::AfterBin(TestItemExecuteContext * aContext) {
	this->UserAfterBin(aContext);
	//Add code here
}
#endif

/**
* DO NOT modify or delete
*/
REGISTER_REFLECTABLE_TYPE_WITH_PARAMETER2(TB_Mem_Ext_Read_vsFFh_User, TestItemExecuteContext *)

