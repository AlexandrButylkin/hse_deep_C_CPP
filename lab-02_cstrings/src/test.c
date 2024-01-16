#include "test_str.h"
#include "stdio.h"

int RunAllTests(){
    int countFailedTests = 0;

    countFailedTests += Test_StrCpy();
    countFailedTests += Test_StrCat();
    countFailedTests += Test_StrCmp();
    countFailedTests += Test_StrLen();

    return countFailedTests;
}

int main(){
    int count = RunAllTests();
    if(count){
        printf("Failed %d tests!", count);
        return 1;
    } else {
        printf("All tests succeeded!");
        return 0;
    }
}