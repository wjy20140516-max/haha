#include "BaseItemOperation.h"
#include "Common.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
* Run test
*/
void BaseItemOperation::UserRun(TestItemExecuteContext * aContext) {
}


/**
* Init test
*/
bool BaseItemOperation::UserInitialize(TestItemExecuteContext * aContext) {

    const char* original_str = (aContext->GetActiveTestName()).c_str();
    const char* delimiter = "_TB";
    char testnumber[100] = { 0 };
    char testname1[100] = { 0 };

    char* tb_pos = strstr(original_str, delimiter);

    if (tb_pos == NULL) {
        Print("Error: Delimiter not found in the original string! \"%s\"", delimiter);
        return 1;
    }

    int number_len = tb_pos - original_str;

    strncpy(testnumber, original_str, number_len);
    testnumber[number_len] = '\0';
    strcpy(testname1, tb_pos + 1);

    //Print("original_str:%s", original_str);
    //Print("testnumber:%s", testnumber);
    //Print("testname:%s", testname);




    TestNumber = testnumber;
    TestName = testname1;



    TestFlow = aContext->GetActiveFlowName();


    test_num = TestNumber;
    cp_ver = TestFlow;
    lotnum = "B550064";
    wafernum = "B550064-14";
    Die_X = 0;
    Die_Y = 0;
    testname = TestName;




	return true;
}

/**
* Exit test
*/
void BaseItemOperation::UserExit(TestItemExecuteContext * aContext) {
}

/**
* Pause test
*/
void BaseItemOperation::UserPause(TestItemExecuteContext * aContext) {
}

/**
* Resume test
*/
void BaseItemOperation::UserResume(TestItemExecuteContext * aContext) {
}

/**
* Stop test
*/
void BaseItemOperation::UserStop(TestItemExecuteContext * aContext) {
}

/**
* AfterBin test
*/
void BaseItemOperation::UserAfterBin(TestItemExecuteContext* aContext) {
}



