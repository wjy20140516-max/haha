#pragma once

#include "../include/Common.h"

//===================onlinetrim===========
typedef bool(*HND_INIT)();
typedef int (*DRV_FET) (int, int, unsigned int*, unsigned int*, bool);
typedef int (*DRV_FET_MULTRIM_DBL)(double, double, int, int, unsigned int*, unsigned int, bool, bool);
typedef int (*DRV_FET_RDCRS)(unsigned int, unsigned int*, bool);
///// used by new format unique id test
typedef int (*UNI_GET_CUSUNICODE) (const char*, char, std::vector<std::vector<int>>&, int, int, int, UINT64, char);


class DynamicTrimM5
{
	void* hDllInstance;
	std::string			cDllFileName;
public:
	DynamicTrimM5();
	virtual ~DynamicTrimM5();
	virtual void init();
	virtual void ChangeDLL(std::string cName);
	virtual void SetDLL(std::string cName);
	virtual std::string GetDLL();


	DRV_FET				Drv_FetUpdCRs;
	DRV_FET_MULTRIM_DBL Drv_FetMultiTrim;
	DRV_FET_RDCRS       Drv_FetCrsRead;

};
extern DynamicTrimM5 OlnTrim;



class DynamicUniCode
{
	void* hDllInstance;
	std::string			cDllFileName;
public:
	DynamicUniCode();
	virtual ~DynamicUniCode();
	virtual void init();
	virtual void ChangeDLL(std::string cName);
	virtual void SetDLL(std::string cName);
	virtual std::string GetDLL();

	UNI_GET_CUSUNICODE			Gen_GetCusUniCode;

};
extern DynamicUniCode UniCusCOde;

typedef struct MRTRIMBUFF {

	int ArchMnsTFC;
	int ArchPlsTFC;
	int DutX;
	int DutY;

}TF_MRTRIMBUFF;

////======================================================================

