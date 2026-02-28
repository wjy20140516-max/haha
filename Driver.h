#pragma once

#include "../include/Common.h"
//////////////////////////////////////////////////////////////////////
// Driver.h: CDriver 
//
//////////////////////////////////////////////////////////////////////
//
typedef bool(*HND_INIT)();
typedef int(*DRV_FET) (int, int, unsigned int*, unsigned int*, bool);
typedef int(*DRV_FET_DIRC) (int, int, unsigned int*, bool);
typedef int(*DRV_FET_MULTRIM) (int, int, int, int, unsigned int*, unsigned int, bool, bool);
typedef int(*DRV_FET_RDCRS) (unsigned int,  unsigned int*, bool);


class CDriver
{	
	void*			hSoInstance;
	std::string		cSoFileName;
public:
	         CDriver();
	virtual ~CDriver();
	virtual void init();
	virtual void ChangeSO(std::string cName);
	virtual void SetSO(std::string cName);
	virtual std::string GetSO();
	
	HND_INIT		Hnd_Init;
	DRV_FET			Drv_FetUpdCRs;
	DRV_FET_DIRC    Drv_FetUpdMemCode;
	DRV_FET_MULTRIM Drv_FetMultiTrim;
	DRV_FET_RDCRS 	Drv_FetCrsRead;

}; 

extern CDriver TheDevice;

extern unsigned int curr_crs[128];


