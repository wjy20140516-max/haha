/*********************************************************************************************************************************/
/*Company:NCATEST                                                                                                                */
/*Author:Peddy Ji                                                                                                                 */
/*Update Time:2022/06/29																										 */
/*********************************************************************************************************************************/
#pragma once
#include "interface/ONESCommon.h"
#include "interface/ONESInterfaceHeader.h"
#include "interface/TestItem.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>
#include "interface/TestDomainExecuteContext.h"
#include <unistd.h>
//#include <corecrt.h>
#include <ctime>
#include <sstream>
#include <algorithm>

#include <unistd.h>   // getwd 所需头文件
#include <limits.h>   // PATH_MAX 所需头文件
#include <cstring>    // strerror 所需头文件
#include <errno.h>    // errno 所需头文件
#include <dlfcn.h>
#include <iomanip>





//**********log print global variable start******************
extern std::string test_num;
extern std::string cp_ver;
extern std::string lotnum;
extern std::string wafernum;
extern int Die_X;
extern int Die_Y;
extern std::string testname;





extern string start_time_s;
extern string end_time_s;
extern int TD;
extern ResultMap RsltVSS_OS_global;
extern ResultMap Rslt_VAA_global;
extern ResultMap Rslt_VHH_global;
extern bool TB_Power_On_Uninitialized_1010[16];
extern bool TB_Read_Cregs_TestMode_1020[16];
extern bool TB_Read_Version_ID_1030[16];
extern double TB_IAA_Stanby_1040[16];
extern bool TB_Load_CRegs_from_File_1050[16];
extern double TB_IAA_Stanby_1060[16];
extern bool TB_VHH_Trim_Source_1070[16];
extern bool TB_Mem_Main_Read_vsFFh_DDW_1080[16];
extern bool TB_Force_VHH_1090[16];
extern bool TB_Mbist_Write_00h_DDW_1100[16];
extern bool TB_Mem_Ext_Write_FFh_DDW_1110[16];
extern bool TB_Mem_Main_Read_vs00h_DDW_1120[16];
extern bool TB_Mbist_Write_FFh_DDW_1130[16];
extern bool TB_Mem_Ext_Write_00h_DDW_1140[16];
extern bool TB_Mem_Main_Read_vs00h_DDW_1150[16];
extern bool TB_Mem_Ext_Write_FF00h_DDW_1160[16];
extern bool TB_Mem_Main_Read_vsFFh_DDW_1170[16];
extern bool TB_Mbist_Write_FF00h_Cycles_DDW_1180[16];
extern bool TB_Mem_Main_Read_vs00h_DDW_1190[16];
extern bool TB_Mem_Ext_Write_00FFh_DDW_1200[16];
extern bool TB_Mem_Main_Read_vs00h_DDW_1210[16];
extern bool TB_Mbist_Write_CKB_DDW_1220[16];
extern bool TB_Mem_Main_Read_vsCKB_DDW_1230[16];
extern bool TB_Mem_Main_Read_vs00h_DDW_1240[16];
extern double  TB_Float_VHH_1250[16];
extern bool TB_Mbist_Write_InvCKB_DDW_1260[16];
extern bool TB_Mem_Main_Read_vsInvCKB_DDW_1270[16];
extern bool TB_Mbist_Write_InvCKB_DDW_1280[16];
extern bool TB_Mem_Main_Read2PT_Trim_vsInvCKB_DDWDIS_1290[16];
extern bool TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS_1300[16];
extern bool TB_Mem_Main_Read_DArch_vsInvCKB_DDWDIS_1310[16];
extern bool TB_Load_CRegs_from_File_1320[16];
extern double TB_Chip_Erase_1330[16];
extern bool TB_Mem_Ext_Populate_Data_1340[16];
extern bool TB_Mem_Ext_Populate_vhhtrim_1350[16];
extern bool TB_Mem_Ext_Populate_2pTrim_DataDIS_vhhtrim_1360[16];
extern bool TB_Mem_Main_Read_vs00h_DDW_1370[16];
extern bool TB_Write_TReg_1380[16];
extern bool TB_Mem_Ext_Populate_CustomizedUniCode_1390[16];
extern double  TB_Float_VHH_1400[16];
extern bool TB_Power_Down_1410[16];
extern bool TB_Power_On_Initialized_1420[16];
extern bool TB_Read_StatusReg1_1430[16];
extern bool TB_Read_StatusReg2_1440[16];
extern bool TB_Read_SFDP_1450[16];
extern bool TB_Read_SecurityRegisters_1460[16];
extern bool TB_Read_SecurityRegisters_1470[16];
extern bool TB_Read_SecurityRegisters_1480[16];
extern bool TB_Read_Manufacturer_ID_1490[16];
extern bool TB_Read_Unique_ID_1500[16];
extern bool TB_Read_Jedec_ID_1510[16];
extern bool TB_Mem_Populate_Data_1520[16];
extern double TB_IAA_Stanby_1530[16];
extern bool TB_Read_Cregs_TestMode_1540[16];
extern bool TB_Power_Down_1550[16];
//**********log print global variable end******************

// #define POLLING_BY_JMATCH
#define DUT_NUM 8
#define DUT_FAIL {dutpf[dutz]=dutpf[dutz]|1;str_pf[dutz]="F";dutpfa[dutz]=dutpfa[dutz]|1;}

extern int Data_conversion[DUT_NUM][1000000];
extern int test_mode_debug_power;
extern char local_time_s[100];

extern int LocalID;
extern int SysID;
extern int Fail_data_1[DUT_NUM][1000000];
extern int Fail_addr_1[DUT_NUM][1000000];
extern string TestName;
extern string TestNumber;
extern string TestFlow;



extern unsigned int  ubm_data[DUT_NUM][96];







using namespace std;
extern std::vector<std::string> ctrlPins;
extern std::vector<std::string> ioPins;
extern std::vector<std::string> powerPins;

extern double temp_value[DUT_NUM][10];
extern int red_cnt[10][2];
extern int red_addr[10][2][16];
extern int DUT_LIST[11];
extern int rcam_exp_data[64];
extern double tx_current[11][7];  // dut tx
extern string DeviceName;
extern string LotNumber;
extern string WaferId;
extern string ProberId;
extern string WaferSlotNumber;
extern int dutx[1000];
extern int duty[1000];
extern int device_num[1000];
extern int bin_num[1000];
extern int sort_num[1000];
//extern double vdd;
//extern double vdd_min;
extern int fail_flag;

//extern double vdd_value;
extern int DUT_LIST[11];
extern int dlog;
extern int DUTA_MASK; //1->mask die, 0->don't know
extern int DUTB_MASK;

extern int CUR_DUT_COUNT;
extern int CUR_FAIL_MASK;
extern int CUR_DUT_MASK;
extern int DUT_MASK;
extern string PinList;
extern char str_results[1024];
extern char str_results1[1024];
extern char rdata_temp[12];
extern int logflag;
extern int Para_Item;
extern int flg_jump;
extern int flg_break;
extern int itfail;
extern int Fail_data[1000000];
extern int Fail_data_H[1000000];
extern int Fail_data_L[1000000];
extern int Fail_addr[1000000];
extern char buf[200000];
extern char cmd[200000];
extern int FLG_PF[DUT_NUM];
extern int dutpf[1000000];
extern int dutpfa[1000000];
extern string str_pf[1000000];
extern int get_pin_list(string pinlists, string* pinlist);

enum UseDataFormat { raw_data_fmt, true_data_fmt };


// #define RRAM_B2_DEBUG   

#define RRAM_B2_ERR_LOG

//#define RRAM_B2_AUTOMATION

#define Print_Random_Data

// #define POLLING_BY_JMATCH

#define DPS_SHARE

// #define POLLING_DELAY 

// DPS's sense mode
#define DPS_SENSE_MODE          DC_SENSE_MODE_E::DC_SENSE_MODE_REMOTE 
// PE's sense mode 
#define PE_SENSE_MODE           DC_SENSE_MODE_E::DC_SENSE_MODE_LOCAL

// Custom UniCode

#define PRESET_NO_DUT_FAIL		0
#define PRESET_ALL_DUT_FAIL		0xFFFFFFF

// VHH Trim Code

#define USE_BLUEFIN_INSTRUCTION_SET 1

#define XREG_COUNT              128
#define TYP_IP_PERDUT           1

// #define ip_inx               1

#define V1_ADDR_INDEX			0x0C    
#define V1_ADDR_MASK			0x0F    
#define V1_ADDR_BITSHIFT		4       
#define V2_ADDR_INDEX			0x0C
#define V2_ADDR_MASK			0xF8	
#define V2_ADDR_BITSHIFT		0

#define DEF_TARGET_V2_MV	    3600.0    
#define INCREMENT_V2_MV		    110.0    
#define INCREMENT_V1_MV		    78.0

extern double  TARGET_V2_MV;
typedef unsigned long long UINT64;

#define V1_TRIM_MAX			    0xF	      
#define V1_TRIM_MIN			    0x0	

#define V2_TRIM_MAX			    0x7	
#define V2_TRIM_MIN			    0x0	

#define BYTE_WIDTH			    8           
#define TRIM_TIMES			    2   

/// ================ Polling Gap ================= ///
#define MBIST_CKB_VHH_POLLING_IDLE_GAP_768      1000
#define MBIST_CKB_VHH_POLLING_IDLE_GAP_1280     1800
#define MBIST_CKB_VHH_POLLING_IDLE_GAP_1        10
#define MBIST_CKB_POLLING_IDLE_GAP_768          6000
#define MBIST_CKB_POLLING_IDLE_GAP_1280         11000
#define MBIST_CKB_POLLING_IDLE_GAP_1            10


/// ================ Criteria Control ================= ///
#define DFB_LMT_FLAG					0
#define TFB_LMT_FLAG					1
#define TFB_CNT							2
#define ERR_CHAR						3  ///// count of all characters
#define MAX_BYTE_NUM_FULL               0xC03000 //0x340000
#define POLLING_ONE_TIME                1
#define POLLING_ONE_TIME_MBIST          2   
#define POLLING_ONE_TIME_MEMEXT         2                  


/// ================ SPI Command ================= ///
#define OP_DPD			    0xB9
#define OP_RLS_DPD		    0xAB	
#define OP_READ_ID          0x05
#define OP_DDW_ON	        0x44
#define OP_DDW_OFF	        0x00
#define USER_ON	        	0x07    
#define USER_OFF	        0x00    
#define OP_POLLING          0x05
#define OP_MBIST_READ       0x0B


/// ================ Test Parameters ================= ///
#define CHIP_ID_DATA_COUNT              3
#define MAX_DUTS                        16
#define POLLING_LIMIT                   5000
#define CFG_FILE_LENGTH                 96
#define MBIST_WRITE_DDW_PAGE            128
#define MBIST_WRITE_USER_PAGE           128
#define MBIST_WRITE_START_PAGE_MODE1    0x000
#define MBIST_WRITE_START_PAGE_MODE2    0x300
#define DDW_SET_DATA                    0x00
#define DDW_SET_CKB_DATA                0x55
#define DDW_RESET_InvCKB_DATA           0xAA
#define DDW_RESET_DATA                  0xFF
#define CKB_USER_DATA                   0x00
#define INVCKB_USER_DATA                0xFF
#define POLLING_DATA                    0x00
#define MBIST_READ_CFG_ADDR             0x07
#define MBIST_READ_DDW_PAGE             192
#define MBIST_READ_USER_PAGE            128
#define MBIST_READ_PAGES_MODE1          768
#define MBIST_READ_PAGES_MODE2          1280
#define MBIST_READ_ALL_PAGES            2048
#define MBIST_WRITE_READ                0
#define EXT_WRITE_READ                  1
#define OP_TR_DELAY                    1
#define TURN_ON_TR_VFY                  0
#define TURN_ON_TR_ITEM_VFY             1
#define TURN_ON_TR_ITEM_BIN             0 
#define TURN_ON_TR_BIN                  0
#define ENABLE_VDD_TRIM_SLEEP           true
#define ENABLE_VDD_TRIM_STANDBY         true

#define GET_FLOW_PAR_STR(FUNC_VAR, FLOW_PAR)                                                             \
							if (theParameters->TryGetParameter(FLOW_PAR, theParameter))              \
							{                                                                        \
								FUNC_VAR = theParameter->GetValueAsString();                        \
							}

#define DISABLE_DUTMASK(DUT_MASK)                                                               \
							DUT_LOOP_START                                                      \
							if (((DUT_MASK >> (dut - 1)) & 0x01))                             \
							{                                                                   \
							(*item)->Disable();                                                 \
							this->Info("Disable DUT ID:" + to_string(dut));     \
							}                                                                   \
							DUT_LOOP_END      

#define DUT_PER_SITE 8


//TheDevice.init();
//UniCusCOde.init();
//OlnTrim.init();

////==========driver=============
//
//typedef bool(*HND_INIT)();
//typedef int(*DRV_FET) (int, int, unsigned int*, unsigned int*, bool);
//typedef int(*DRV_FET_DIRC) (int, int, unsigned int*, bool);
//typedef int(*DRV_FET_MULTRIM) (int, int, int, int, unsigned int*, unsigned int, bool, bool);
//typedef int(*DRV_FET_RDCRS) (unsigned int, unsigned int*, bool);
//
//
//class CDriver
//{
//	void* hSoInstance;
//	std::string		cSoFileName;
//public:
//	CDriver();
//	virtual ~CDriver();
//	virtual void init();
//	virtual void ChangeSO(std::string cName);
//	virtual void SetSO(std::string cName);
//	virtual std::string GetSO();
//
//	HND_INIT		Hnd_Init;
//	DRV_FET			Drv_FetUpdCRs;
//	DRV_FET_DIRC    Drv_FetUpdMemCode;
//	DRV_FET_MULTRIM Drv_FetMultiTrim;
//	DRV_FET_RDCRS 	Drv_FetCrsRead;
//
//};
//
//extern CDriver TheDevice;
//
//extern unsigned int curr_crs[128];
////===================Driver====================================

////===================onlinetrim===========
//typedef bool(*HND_INIT)();
//typedef int (*DRV_FET) (int, int, unsigned int*, unsigned int*, bool);
//typedef int (*DRV_FET_MULTRIM_DBL)(double, double, int, int, unsigned int*, unsigned int, bool, bool);
//typedef int (*DRV_FET_RDCRS)(unsigned int, unsigned int*, bool);
/////// used by new format unique id test
//typedef int (*UNI_GET_CUSUNICODE) (const char*, char, std::vector<std::vector<int>>&, int, int, int, UINT64, char);
//
//
//class DynamicTrimM5
//{
//	void* hDllInstance;
//	std::string			cDllFileName;
//public:
//	DynamicTrimM5();
//	virtual ~DynamicTrimM5();
//	virtual void init();
//	virtual void ChangeDLL(std::string cName);
//	virtual void SetDLL(std::string cName);
//	virtual std::string GetDLL();
//
//
//	DRV_FET				Drv_FetUpdCRs;
//	DRV_FET_MULTRIM_DBL Drv_FetMultiTrim;
//	DRV_FET_RDCRS       Drv_FetCrsRead;
//
//};
//extern DynamicTrimM5 OlnTrim;
//
//
//
//class DynamicUniCode
//{
//	void* hDllInstance;
//	std::string			cDllFileName;
//public:
//	DynamicUniCode();
//	virtual ~DynamicUniCode();
//	virtual void init();
//	virtual void ChangeDLL(std::string cName);
//	virtual void SetDLL(std::string cName);
//	virtual std::string GetDLL();
//
//	UNI_GET_CUSUNICODE			Gen_GetCusUniCode;
//
//};
//extern DynamicUniCode UniCusCOde;
//
//typedef struct MRTRIMBUFF {
//
//	int ArchMnsTFC;
//	int ArchPlsTFC;
//	int DutX;
//	int DutY;
//
//}TF_MRTRIMBUFF;
//
////======================================================================
//
//

typedef struct
{
	int gbl_addr;
	int container;// 0-1
	int redgbl;   // 0-7
}rep_info;

struct Err_set
{
	unsigned int byte;
	unsigned int bit;
	unsigned int err_type; // 0  1
};

struct Array_result_t 
{
	int  Creg40h;
	int  error_flags[MAX_DUTS][3];
	int  error_cnt[MAX_DUTS];
	int  max_ddw_dwfb[MAX_DUTS];
	int  err_flags[MAX_DUTS];
};

struct MultiTrim
{
	int ArchMnsTFC;
	int ArchPlsTFC;
	int DutX;
	int DutY;
};

extern MultiTrim MulDUTArch[MAX_DUTS];


enum Sel_Tester {
	Sel_Magunm = 0,
	Sel_M5000 = 2
};


enum Sel_Product {
	Sel_Taiji = 2
};


enum Sel_IoMode {
	sel_spi = 1,
	sel_qpi = 2,
	sel_dpi = 4
};
enum Sel_DataMode {
	sel_Raw = 2,
	sel_User = 4
};


//                 dut bank redgbl_num
extern rep_info fail_gbl_info[11][2][16];
//               dut bank container
extern int fail_gbl_cnt[11][2][2];
extern int DUT_LIST[11];
void TryGetParameter_AsDouble(string Name, TestExecuteContext* aContext);
//void TRegWrite(int CReg_Addr, int CReg_Data);
void TRegWrite(int TReg_Addr, int TReg_Data);
void AFM_READ_Non_cross_VP(int afm_size_num, int addr_start, int DATA, TestItemExecuteContext* aContext);
void TRegRead(TestItemExecuteContext* aContext, int TReg_Addr, int* TReg_ReadData);
void EnterTestModeTJ();
void MbistWriteDDW(int Mbist_Write_StartPage, int Mbist_Write_Date);
void MbistReadDDW(int Mbist_Read_StartPage, int Mbist_Read_Pages);
//void LoadConfigFile(TestItemExecuteContext* aContext, bool Judge);
void LoadConfigFile(TestItemExecuteContext* aContext, bool Judge, string ConfigFileName);
void MemMainReadDDW(int Mbist_Read_StartPage, int Mbist_Read_Pages);
void MemMainReadDDW_All(int comparedata, int Mbist_Read_StartPage, int loop1, int loop2);
void MemExtWrite(int PageAddr, int Mem_Ext_Write_Data);
void update_local_time();
void ReadConfigFileTrim(TestItemExecuteContext* aContext);
int  TRegsRead(TestItemExecuteContext* aContext, int TReg_Addr, int* TReg_ReadData);
void Polling_Soft(TestItemExecuteContext* aContext, const std::string pins, int polling_gap, int WaitDummy);
void Polling_Soft_RND(TestItemExecuteContext* aContext, std::string pins, int polling_gap, int WaitDummy);
void ReadConfigFile(TestItemExecuteContext* aContext);
void MemExtWritePopulateData(int PageAddr, int Page_Num);
void MemExtReadPopulateData(int PageAddr, int PageLength);
void MemExtWriteUniqeTrim(int PageAddr, int Page_Num);
int CRegTrimWrite(int CReg_Addr, int CReg_Data);

int get_new_voltage_trim_bit(TestItemExecuteContext* aContext, int iteration_counter, unsigned char v2_trim, unsigned char v1_trim, double curr_vh_mv, double curr_vr_mv);
int Data_Compare_Ext_print(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int start_page, Array_result_t* errflag, TestItemExecuteContext* aContext);
int Data_Compare_Ext_array_XOR_array(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, std::vector<std::vector<int>>& UniqueCharArray, std::vector<int>& get_error_bit, Array_result_t* errflag, int TFB_Limit, int DFB_Limit, TestItemExecuteContext* aContext);
int Data_Compare_Ext_array_XOR_array(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, std::vector<unsigned int>& target_byte_patt, std::vector<int>& get_error_bit, Array_result_t* errflag, int TFB_Limit, int DFB_Limit, TestItemExecuteContext* aContext);

int Data_Compare_Mbist_array_print(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int target_byte_patt, std::vector<int>& get_error_bit, Array_result_t* errflag, int start_page, int TFB_Limit, int DFB_Limit, TestItemExecuteContext* aContext, bool IsEccOut = true);
int Data_Compare_Mbist_array_print(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int target_byte_patt, int* get_error_bit, Array_result_t* errflag, int start_page, int TFB_Limit, int DFB_Limit, TestItemExecuteContext* context, bool IsEccOut = true);
int Data_Compare_Mbist_array_print_bak(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int target_byte_patt, std::vector<int>& get_error_bit, Array_result_t* errflag, int start_page, int TFB_Limit, int DFB_Limit, TestItemExecuteContext* aContext, bool IsEccOut = true);



int Data_Compare_CKB_DDW_array_print(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int target_byte_patt, std::vector<int>& get_error_bit, Array_result_t* errflag, int start_page, int TFB_Limit, int DFB_Limit, TestItemExecuteContext* aContext, bool IsEccOut = true);

void LoadConfigFileBySo(TestItemExecuteContext* aContext, const std::string fileName, int maxByte, unsigned int* cfgReg, int arch_pt, bool read_oper);
void FileRead(TestItemExecuteContext* aContext, const std::string& fileName, unsigned int* value, unsigned long size);

void Print(const char* format, ...);
// count err021/err120 + convert_512byte
void err_bit_comp(const unsigned int* exp_data, const unsigned int* data, const unsigned int len_data,
	unsigned int* err021, unsigned int* err120, unsigned int* sum_err,
	Err_set* err_set, const unsigned int len_err_set, const unsigned int byte_offset,
	unsigned int* compressed_data, TestItemExecuteContext* aContext);

// count err021/err120
void err_bit_comp(const unsigned int* exp_data, const unsigned int* data, const unsigned int len_data,
	unsigned int* err021, unsigned int* err120, unsigned int* sum_err,
	Err_set* err_set, const unsigned int len_err_set, TestItemExecuteContext* aContext);

// count 1 (err021)
void err_bit_comp(const unsigned int* data, const unsigned int len_data,
	unsigned int* sum_err, Err_set* err_set, const unsigned int len_err_set,
	TestItemExecuteContext* aContext);

void afm_err_count(const unsigned short dut, const unsigned int offset_addr, 
	const unsigned int count_size, unsigned int* err021, unsigned int* err120, 
	unsigned int* sum_err,Err_set* err_set, const unsigned int len_err_set, 
	TestItemExecuteContext* aContext);
void power_up_level();
void AFM_CONFIG_SET_keep_default(string pins, int x, int y, TestItemExecuteContext* aContext);
void power_up_level_set(double val);
void AFM_CONFIG_SET(string pins, int x, int y, TestItemExecuteContext* aContext);
void AFM_CONFIG_SET_OSCILLATOR(string pins, int x, int y, TestItemExecuteContext* aContext);
void MARCH_WRITE_PATTERN(string pat_name, string module_name, int write_addr, int write_data, int blk_num, TestItemExecuteContext* aContext);
void MARCH_READ_PATTERN(string pat_name, string module_name, int read_addr, int read_data, int blk_num, TestItemExecuteContext* aContext);
void init_rcam_exp_data();
void init_gbl_info();
void append_fail_gbl(unsigned short dut, int bank, int gbl_addr, int container);
void print_rcam_exp_data(TestItemExecuteContext* aContext);
void print_gbl_info(TestItemExecuteContext* aContext);
void print_gbl_info(int dut, int bank, TestItemExecuteContext* aContext);
void print_gbl_info(int sum_redgbl_num, TestItemExecuteContext* aContext);
void AFM_READ_CHECK(int block_num,int afm_size_num, int addr_start, TestItemExecuteContext* aContext);
void AFM_READ_CHECK_addr_add(int step, string mark_flg, int block_num, int afm_size_num, int addr_start, TestItemExecuteContext* aContext);
void AFM_READ_CHECK_addr_sub(int step, string mark_flg, int block_num, int afm_size_num, int addr_start, TestItemExecuteContext* aContext);
void AFM_READ_CHECK_BR(int block_num, int afm_size_num, int addr_start, TestItemExecuteContext* aContext);
void AFM_READ_CHECK_HL(int block_num, int afm_size_num, int addr_start, TestItemExecuteContext* aContext);
void AFM_READ_CHECK_vdd(int block_num, int afm_size_num, double temp, int addr_start, TestItemExecuteContext* aContext);
void March_pgm(int block_num, char up_down, int data_W, TestItemExecuteContext* aContext);
void dc_print(string testname, string pinname, ResultMap doublem, double hlimit, double llimit, string unit, TestItemExecuteContext* aContext);
void March_read(int block_num, char up_down, int data_R, TestItemExecuteContext* aContext);
double getMax(TestItemExecuteContext* aContext, double array[], int count);
double getAvg(TestItemExecuteContext* aContext, double array[], int count, double spec);

void POWERON(int flag, double VIH);


void POWEROFF(int flag);

void Get_Pin_Group();

void run_module(string PatternName, string ModuleName, double TimeOut);

double GetCycleAver(int dut, double rate, unsigned int size);
int Get_Local_Time(char* local_time_buf, int buf_size);
int Get_Local_Time_1(char* local_time_buf, int buf_size);
int PrintLogall(TestDomainExecuteContext* aContext);
void Print2buff(const char* format, ...);
void log_file_head_information(const std::string testNum, const std::string cp_ver, const std::string LotId, const std::string WaferId, const int Die_X, const int Die_Y);
string log_name_setting(TestItemExecuteContext* aContext, std::string& LotId, std::string& WaferId, int& Die_X, int& Die_Y, const std::string testname);
string log_name_setting(TestItemExecuteContext* aContext, const std::string testname);
int CustomizedUniCode(TestItemExecuteContext* aContext, std::string& LotId, std::string& WaferId, int& Die_X, int& Die_Y, UINT64 customized_4byte, std::vector<std::vector<int>>& UniqueCharArray, int Mem_Ext_Write_Page, int Page_Num);
void loadHexFile(const std::string& filepath, std::vector<uint8_t>& data);
void Polling_By_Mloop(TestItemExecuteContext* aContext, const std::string pins, int polling_gap, int WaitDummy);
int Data_Compare_vsFF_User_array_print(UseDataFormat dataFmt, int byte_limt, std::vector<std::vector<int>>& output_array, int target_byte_patt, int* get_error_bit, Array_result_t* errflag, int start_page, int TFB_Limit, int DFB_Limit, TestItemExecuteContext* aContext, int DAC = 0x1b, bool IsEccOut = true);
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define GET_DUT_LIST		DUTList* theDUTArray = aContext->GetDUTs();\
							list<DUT*> theDUTList = *(theDUTArray->GetDUTList()); 

#define DUT_LOOP_START   {   DUTList* theDUTArray = aContext->GetDUTs();\
                             list<DUT*> theDUTList = *(theDUTArray->GetDUTList()); \
	for (list<DUT*>::iterator item = theDUTList.begin(); item != theDUTList.end(); item++){\
							int dut=(*item)->GetID();int dutz=dut-1;

#define DUT_LOOP_START0  {   DUTList* theDUTArray = aContext->GetDUTs();\
                             list<DUT*> theDUTList = *(theDUTArray->GetDUTList()); \	
	for (list<DUT*>::iterator item = theDUTList.begin(); item != theDUTList.end(); item++) {\
			                 int dut = ((*item)->GetID()) - 1;

#define DUT_LOOP_END		}}

#define POWER_UP			PMU_DigitalSet("IO_PINS", 3.3 V, 0 V, 1.0 V, 1.0 V);\
							Pattern_SetChannelHIGH("CS#");\
							Time.Delay(1 MS);\
							DPS_FV("POWER", 3.3 V, 250 MA, 250 MA, -250 MA, ENUM_SENSE_REMOTE);\
							Time.Delay(1 MS);

#define POWER_DOWN			DPS_Off("POWER");\
							PMU_Off("CtrlPins");
	//                        dut bank
	//extern int Red_cnt_global[10][2];
	//extern int Red_addr_global[10][2][16];
	//extern int DUT_LIST_global[10];
	typedef bool(*HND_INIT)();
	typedef int(*DRV_FET) (int, int, unsigned int*, unsigned int*, bool);
	typedef int(*DRV_FET_DIRC) (int, int, unsigned int*, bool);
	typedef int(*DRV_FET_MULTRIM) (int, int, int, int, unsigned int*, unsigned int, bool, bool);
	typedef int(*DRV_FET_RDCRS) (unsigned int, unsigned int*, bool);



	struct rndFlag
	{
		// uint rndFlag = 0;
		std::vector<uint8_t>flaglist = std::vector<uint8_t>(MAX_DUTS, 0);
	};

	extern rndFlag RNDFlag;

	struct DUTListFlag
	{
		bool Flag[MAX_DUTS];
		DUTListFlag() { Reset(); }

		void Reset()
		{
			for (int i = 0; i < MAX_DUTS; i++)
			{
				Flag[i] = true;
			}
		}
		void Invalidut(int dutid)
		{
			if (dutid >= 0 && dutid < MAX_DUTS)
				Flag[dutid] = false;
		}
		bool Validut(int dutid) const
		{
			// return Flag[dutid];
			return (dutid >= 0 && dutid < MAX_DUTS) ? Flag[dutid] : false;
		}
	};

	extern DUTListFlag DUTRNDFlag;

	struct DataD8 {
		//typedef unsigned char typeof_data;
		unsigned char byte[XREG_COUNT];
		
		
	};

	struct Data_FBC {
		//typedef int typeof_data;
		int count;
	};


	class USER_REGBFR
	{
	public:
		USER_REGBFR()/*: xreg_errcnt(MAX_DUTS, 0)*/ {
			for (int ii = 0; ii < MAX_DUTS; ++ii) {
				trim_flag[ii] = false;
			}
		}
		~USER_REGBFR() {
		}


		DataD8 xreg_target[MAX_DUTS][TYP_IP_PERDUT];
		DataD8 xreg_errmask[MAX_DUTS][TYP_IP_PERDUT];
		Data_FBC error[MAX_DUTS][TYP_IP_PERDUT];
		int lastErrByte[MAX_DUTS][TYP_IP_PERDUT];



		void set_v1_trim_val(int dut, int ip, int value) {
			v1_trim[dut][ip] = value;
			// ETLog::Info("<COLOR=Red> V1 trim = %0x (%x)</COLOR>", value, v1_trim[dut][ip]);
		}
		void set_v2_trim_val(int dut, int ip, int value) {
			v2_trim[dut][ip] = value;
			// ETLog::Info("<COLOR=Red> V2 trim = %0x (%x)</COLOR>", value, v2_trim[dut][ip]);
		}

		int get_v1_trim_val(int dut, int ip) {
			return v1_trim[dut][ip];
		}
		int get_v2_trim_val(int dut, int ip) {
			return v2_trim[dut][ip];
		}




		void clear_xreg_errmask(int ipn) {
			for (int ii = 0; ii < MAX_DUTS; ++ii) {
				//for (int jj = 0; jj < TYP_IP_PERDUT; ++jj){
				error[ii][ipn].count = 0;
				lastErrByte[ii][ipn] = 0;
				for (int kk = 0; kk < XREG_COUNT; ++kk)
					xreg_errmask[ii][ipn].byte[kk] = 0;
				//}
			}
		}

		void clear_xreg_errmask(int dut, int ipn) {
			error[dut][ipn].count = 0;
			for (int kk = 0; kk < XREG_COUNT; ++kk)
				xreg_errmask[dut][ipn].byte[kk] = 0;
		}

		void set_xreg_target(std::vector<unsigned char> fetch_bytes) {
			for (int ii = 0; ii < MAX_DUTS; ++ii) {
				for (int jj = 0; jj < TYP_IP_PERDUT; ++jj) {
					for (size_t kk = 0; kk < fetch_bytes.size(); ++kk) {
						if (kk < XREG_COUNT)
							xreg_target[ii][jj].byte[kk] = fetch_bytes[kk];
						// ETLog::Info("[XREG_TARGET]:{:02X} ", fetch_bytes[kk]);

					}
				}
			}
		}


		void set_xreg_target(int dut, int ip, std::vector<unsigned char> fetch_bytes) {
			for (size_t kk = 0; kk < fetch_bytes.size(); ++kk) {
				if (kk < XREG_COUNT)
					xreg_target[dut][ip].byte[kk] = fetch_bytes[kk];
			}
		}





		int get_xreg_target_XOR_errmask_result(int dut, int ip, size_t byte_count) {
			int temp_errbyte_count = 0;
			for (size_t kk = 0; kk < byte_count; ++kk) {
				if ((kk < XREG_COUNT) && (xreg_target[dut][ip].byte[kk] ^ xreg_errmask[dut][ip].byte[kk]))
					temp_errbyte_count++;
			}
			error[dut][ip].count = temp_errbyte_count;
			return error[dut][ip].count;
		}





		void get_trim_val_update(int dut, int ip, std::vector<unsigned char>& fetch_bytes) {
			if ((trim_flag[dut]/*true*/) && (fetch_bytes.size() >= V1_ADDR_INDEX) && (fetch_bytes.size() >= V2_ADDR_INDEX))
			{
				fetch_bytes[V2_ADDR_INDEX] = (v2_trim[dut][ip] << V2_ADDR_BITSHIFT) + (fetch_bytes[V2_ADDR_INDEX] & V2_ADDR_MASK);
				fetch_bytes[V1_ADDR_INDEX] = (v1_trim[dut][ip] << V1_ADDR_BITSHIFT) + (fetch_bytes[V1_ADDR_INDEX] & V1_ADDR_MASK);
			}
		}

		void get_trim1_val_update(int dut, int ip, unsigned char* fetch_byte) {
			if (trim_flag[dut]/*true*/) {
				*fetch_byte = (v1_trim[dut][ip] << V1_ADDR_BITSHIFT) + (*fetch_byte & V1_ADDR_MASK);
				// ETLog::Info("<COLOR=Red> DUT#%0d V1 trim = %0x (%x)</COLOR>\\", dut, *fetch_byte, v1_trim[dut][ip]);
			}
		}
		void get_trim2_val_update(int dut, int ip, unsigned char* fetch_byte) {
			if (trim_flag[dut]/*true*/) {
				*fetch_byte = (v2_trim[dut][ip] << V2_ADDR_BITSHIFT) + (*fetch_byte & V2_ADDR_MASK);
				// ETLog::Info("<COLOR=Red> DUT#%0d V2 trim = %0x (%x)</COLOR>\\", dut, *fetch_byte, v2_trim[dut][ip]);
			}
		}


		int get_trim_flag(int dut)
		{
			return trim_flag[dut];
		}

		void set_trim_flag(int dut, int input)
		{
			trim_flag[dut] = input;
		}



	private:
		//// initial value = -1 which stands for null
		int trim_flag[MAX_DUTS];
		int v1_trim[MAX_DUTS][TYP_IP_PERDUT];
		int v2_trim[MAX_DUTS][TYP_IP_PERDUT];
		int i1_trim[MAX_DUTS][TYP_IP_PERDUT];
		int i2_trim[MAX_DUTS][TYP_IP_PERDUT];
		int o1_trim[MAX_DUTS][TYP_IP_PERDUT];
		int o2_trim[MAX_DUTS][TYP_IP_PERDUT];
	};

	extern USER_REGBFR UserRegs;

	struct PollingTime_Count
	{
		double Polling_Count[MAX_DUTS] = { 0 };
		void Reset()
		{
			for (int i = 0; i < MAX_DUTS; i++)
			{
				Polling_Count[i] = 0;
			}
		}
	};

	extern PollingTime_Count PST;

	class  TABLE_VAR
	{
	public:
		TABLE_VAR() {
			// initialize_all_table_variables();
		}
		virtual ~TABLE_VAR() {

		}
		bool use_ui_as_tv_source;
		///// variables controlled by auto test table

		std::string tv_test_item;
		int tv_test_number;

		// ip selector
		int tv_ip_num;

		// interface clock period
		int tv_clock_period;
		// dummy in pattern
		int tv_wait_dummy;

		// register
		int tv_register_addr;
		int tv_solid_byte;  // used in memory test as well
		int tv_byte_number;
		// memory read limit
		int tv_tfbc_limit_up;
		int tv_dfbc_limit_up;
		// memory
		int tv_mem_full_addr;
		int tv_dword_number;
		int tv_cycle_number;
		// memory write/read data pattern
		std::vector<unsigned char>  tv_dword_pattern;

		// file paths
		std::string tv_load_path;
		std::string tv_save_path;
		std::string tv_test_log_name;
		std::string tv_regdata_tfile;
		std::string tv_memdata_tfile;

		// increment loop for read shmoo for most of time
		std::vector<unsigned char> tv_series;  // convert from std::string type which uses space " " as separator
		std::vector<double> tv_series_ana; // convert from std::string type which uses space " " as separator

		// voltage of power supply
		double tv_vaa_mv;
		double tv_vccio_mv;
		double tv_vhh_mv;
		double tv_vdd_mv;
		double tv_vss_mv;

		double tv_vref_mv;
		double tv_vcia_mv;
		double tv_vccm_mv;

		// limit of dc test
		double tv_dc_limit_up;
		double tv_dc_limit_dn;

		double utv_dc_settling_ms;

		///////// functions  
		// void initialize_all_table_variables(void);
		// void update_pub_tv_from_ui(void);
		// void update_tv_path_from_ui(void);
		// const char* print_all_test_variables(void);

		// const char* get_time_marker(void);
		// const char* get_current_die(void);
		// const char* get_current_wafer(void);

		void set_dc_test_force_curr(double current_ua) {
			tv_dc_force_curr = current_ua;
		}
		void set_dc_test_force_volt(double voltage_mv) {
			tv_dc_force_volt = voltage_mv;
		}

		///// get implemented immediately
		void set_dc_test_settling_time(double dc_settling_time) {
			//set_pmu_settling_time(dc_settling_time);
			utv_dc_settling_ms = dc_settling_time / (1 MS);
		}

		double get_dc_test_force_ua(void) {
			return (tv_dc_force_curr / (1 MA));
		}
		double get_dc_test_force_mv(void) {
			return (tv_dc_force_volt / (1 MV));
		}
		double get_dc_test_settling_time_ms(void) {
			//return (/*unit:ps*/partime() * 0.000000001);
			return utv_dc_settling_ms;
		}

	private:
		std::string tv_current_die;
		std::string tv_current_wafer;
		std::string tv_time_mark;

		double tv_dc_force_volt;
		double tv_dc_force_curr;
	};
	extern TABLE_VAR TableVar;



	typedef bool(*HND_INIT)();
	typedef int(*DRV_FET) (int, int, unsigned int*, unsigned int*, bool);
	typedef int(*DRV_FET_DIRC) (int, int, unsigned int*, bool);
	typedef int(*DRV_FET_MULTRIM) (int, int, int, int, unsigned int*, unsigned int, bool, bool);
	typedef int(*DRV_FET_RDCRS) (unsigned int, unsigned int*, bool);


	unsigned int iterate_ip_voltage_trim(TestItemExecuteContext* aContext, unsigned int dut_pass_mask, int iterate_counter, int ip_inx, double TrimVtarget_mv, USER_REGBFR& reg_buffer);


	//extern unsigned int curr_crs[128];



	//====================================================CFX DEFINE=======================================
	// define in Common.cpp
	
	// need to Init compressed_data first
	void convert_512(const unsigned int* data, const unsigned int len_data,
		unsigned int* compressed_data, TestItemExecuteContext* aContext);
	
	void repeat(const unsigned int* data, const unsigned int len_data, unsigned int* repeat_data, const unsigned int len_repeat_data);
	void Config_AFM(unsigned int XNum, unsigned int YNum, string PinList,
	DATA_WIDTH_MODE_E DataWidthMode, ADDRESS_MODE_E AddressMode,
	AFM_RESULT_MODE_E ResultMode, unsigned int ResetData);
	void Enable_QPI(TestItemExecuteContext* aContext);
	void Disable_QPI(TestItemExecuteContext* aContext);

	//=====================================================PMU=======================================================================//
	void PMU_FV(string PinList, double VoltageValue, double IRangeValue, double ICLAMPH, double ICLAMPL);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void PMU_FI(string PinList, double CurrentValue, double IRangeValue, double VCLAMPH, double VCLAMPL );
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void PMU_MeasV(string PinList, ResultMap& ResultMap);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void PMU_MeasI(string PinList, ResultMap& ResultMap);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void PMU_Off(string PinList);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void PMU_DigitalSet(string PinList, double VIH, double VIL, double VOH, double VOL);
	/********************************************************************************************************************************

	********************************************************************************************************************************/
	void Pin_LevelSet(string PinList, double VDD);

	void PMU_DtoMVSet(string PinList, double VIH, double VIL, double VOH, double VOL);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void PMU_VrefSet(string PinList, double VRef, double IOH, double IOL);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void PMU_MVMSet(string PinList);

	//=========================================================DPS================================================================//
	void DPS_FV(string PinList, double VoltageValue, double IRangeValue, double ICLAMPH, double ICLAMPL, SENSE_MODE_E SenseMode);
	/********************************************************************************************************************************
	近端模式.
	ENUM_SENSE_LOCAL,
	远端模式.
	ENUM_SENSE_REMOTE,
	高阻抗远端模式.
	ENUM_SENSE_REMOTE_HIZ
	********************************************************************************************************************************/
	void DPS_FV_SLEW(string PinList, double VoltageValue, double IRangeValue, double ICLAMPH, double ICLAMPL, double SlewRate, SENSE_MODE_E SenseMode);
	void DPS_MI(string PinList, ResultMap& ResultMap);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void DPS_Off(string PinList);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void DPS_LOOP_FV(string PinList, double VoltageValue, double IRangeValue, double ICLAMPH, double ICLAMPL);
    /********************************************************************************************************************************
    
    ********************************************************************************************************************************/
	void DPS_LOOP_MVM(string PinList);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void DPS_LOOP_Connect(unsigned short dut, string PinList);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void DPS_LOOP_Measure(unsigned short dut, string PinList, ResultMap& ResultMap);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void DPS_LOOP_Disconnect(unsigned short dut, string PinList);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void DPS_LOOP_OFF(string PinList);
	/********************************************************************************************************************************

	********************************************************************************************************************************/



























	void HV_FV(string PinList, double VoltageValue, double IRangeValue, double ICLAMPH, double ICLAMPL, SENSE_MODE_E SenseMode);
	/********************************************************************************************************************************
	近端模式.
	ENUM_SENSE_LOCAL,
	远端模式.
	ENUM_SENSE_REMOTE,
	高阻抗远端模式.
	ENUM_SENSE_REMOTE_HIZ
	********************************************************************************************************************************/

	void HV_MI(string PinList, ResultMap& ResultMap);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void HV_Off(string PinList);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void HV_MV(string PinList, ResultMap& ResultMap);
	/********************************************************************************************************************************

	********************************************************************************************************************************/


	//void DPS_PatternTrigMISET(unsigned int dut, string PinList, unsigned int SampleCount, unsigned int SampleInterval);
	///********************************************************************************************************************************
	//
	//********************************************************************************************************************************/
	//
	//void DPS_ManualTrigMISET(unsigned int dut, string PinList, unsigned int SampleCount, unsigned int SampleInterval);
	///********************************************************************************************************************************
	//
	//********************************************************************************************************************************/
	//
	//void DPS_GetTrigAverageMeasureValue(unsigned short dut, string PinList, double* aMeasureValue);
	///********************************************************************************************************************************
	//
	//********************************************************************************************************************************/
	//
	//void DPS_TrigOff(unsigned short dut, string PinList);
	///********************************************************************************************************************************
	//
	//********************************************************************************************************************************/



	//=========================================================AFM================================================================//
	void AFM_Set(unsigned int XNum, unsigned int YNum, const string PinList, DATA_WIDTH_MODE_E DataWidth, ALPG_MODE_E ALPGMode, unsigned int AddressCount);
	/********************************************************************************************************************************
	8 比特位宽
	ENUM_DATA_WIDTH_BIT_8 = 1,
	16 比特位宽
	ENUM_DATA_WIDTH_BIT_16 = 2,
	32 比特位宽
	ENUM_DATA_WIDTH_BBIT_32 = 4,

	1周期模式
	ENUM_ALPG_SDR = 1,
	2周期模式
	ENUM_ALPG_DDR = 2,
	4周期模式
	ENUM_ALPG_QDR = 4,

	AddressCount：由于我们的底层AFM是32bit,如果8bit，addresscount就可以填4个。目前最好填1。目的是用来分析failaddress和failbit
	********************************************************************************************************************************/

	void AFM_Read(unsigned short dut, unsigned int StartAddress, unsigned int* Value, unsigned int Size);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void AFM_Refresh(unsigned int Data);
	/********************************************************************************************************************************
	备注：可以刷成任何想要的数字；目前只支持整片刷。
	********************************************************************************************************************************/

	void AFM_Clear();
	/********************************************************************************************************************************
	备注：清除的是AFM_SET的参数
	********************************************************************************************************************************/

	//=========================================================FMM================================================================//
	void RestryCount_Set(string PinList, unsigned int RTC_MAX);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void FMM_Set(string PinList, unsigned int RTC_MAX, unsigned int BBC_MAX);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void FMM_FailCountAddress(unsigned int XStart, unsigned int YStart, unsigned int Xend, unsigned int Yend);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void FFM_GetFailBitCount(unsigned short dut, unsigned int& FailBitCount);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void FFM_GetFailAddressCount(unsigned short dut, unsigned int& FailAddressCount);
	/********************************************************************************************************************************
	
	********************************************************************************************************************************/



	//=========================================================UBM================================================================//
	void UBM_Write(string PinList, unsigned short dut, DATA_TYPE_E DataType, unsigned int Address, unsigned int* Value, unsigned int Size);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void UBM_Read(unsigned short aDUTID, DATA_TYPE_E DataType, unsigned int Address, unsigned int* Value, unsigned int Size);
	/********************************************************************************************************************************
	第一种数据 
	ENUM_D_TYPE, 代替D域的数据
	第二种数据 
	ENUM_SD_TYPE,代替SD域的数据
	********************************************************************************************************************************/

	//=========================================================DBM================================================================//
	void DBM_Set(unsigned int SegmentCount, unsigned int XAddressBitLength, unsigned int YAddressBitLength);
	/********************************************************************************************************************************
	bool 填写 true or false 表示是否打开开关
	********************************************************************************************************************************/

	void DBM_Write(unsigned int SegmentID, unsigned long Address, unsigned int* Value, unsigned long Size);
	/********************************************************************************************************************************
	第一种数据
	ENUM_D_TYPE, 代替D域的数据；
	第二种数据
	ENUM_SD_TYPE,代替SD域的数据；
	********************************************************************************************************************************/

	void DBM_Read(unsigned int SegmentID, unsigned long Address, unsigned int* Value, unsigned long Size);
	/********************************************************************************************************************************
	第一种数据
	ENUM_D_TYPE, 代替D域的数据；
	第二种数据
	ENUM_SD_TYPE,代替SD域的数据；
	********************************************************************************************************************************/

	void DBM_Clear();
	/********************************************************************************************************************************
	清除 DBM_SET的设置；
	********************************************************************************************************************************/


	void Generate_Random_Data(unsigned int* RandomArray, int Size, int MaxData);
	/********************************************************************************************************************************
	产生小于MAXData的随机数；
	********************************************************************************************************************************/

	void ChangeMapValue(ResultMap& Result, int Time);
	/********************************************************************************************************************************
	我们的测试机默认A(安培)；需要换算成mA(毫安)则Time=3等价于10^3；需要换算成uA(微安)则Time=6等价于10^6；
	我们的测试机默认V(伏特)；需要换算成mV(毫伏)则Time=3等价于10^3；需要换算成uV(微伏)则Time=6等价于10^6；
	********************************************************************************************************************************/

	void Pattern_SetChannelHIGH(string PinList);
	/********************************************************************************************************************************

	********************************************************************************************************************************/

	void Pattern_SetChannelLOW(string PinList);
	/********************************************************************************************************************************

	********************************************************************************************************************************/


#ifdef __cplusplus
}
#endif /* __cplusplus */


