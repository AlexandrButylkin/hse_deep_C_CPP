
#include "test_str.h"
#include "str.h"
#include <stdio.h>
#include <string.h>

bool StrsEqual(const char* str1, const char* str2){
    return strcmp(str1, str2) == 0;
}

int PrintPartResult(const char* str, bool result){
    if(!result){
        printf("%s", str);
        printf(" is Failed\n");
        return 0;
    } else{
        return 1;
    }
}

void PrintAllResult(const char* str, bool result){
    if(result){
        printf("%s", str);
        printf(" is Correct\n");
    } else {
        printf("    ");
        printf("%s", str);
        printf(" is Failed\n");
    }
}


bool StrCpy_Empty(){
    char str1[128] = "";
    const char* str2 = "";
    const char * expected = "";
    return StrsEqual(my_strcpy(str1, str2), expected);
}

bool StrCpy_FirstEmptySecondNotEmpty(){
    char str1[128] = "";
    const char* str2 = "abc";
    const char * expected = "abc";
    return StrsEqual(my_strcpy(str1, str2), expected);
}

bool StrCpy_FirstNotEmptySecondEmpty(){
    char str1[128] = "abc";
    const char* str2 = "";
    const char * expected = "";
    return StrsEqual(my_strcpy(str1, str2), expected);
}

bool StrCpy_NotEmpty(){
    char str1[128] = "aaa";
    const char* str2 = "abc";
    const char * expected = "abc";
    return StrsEqual(my_strcpy(str1, str2), expected);
}

bool StrCpy_FirstSizeGreaterSecondSize(){
    char str1[128] = "aaaaaa";
    const char* str2 = "abc";
    const char * expected = "abc";
    return StrsEqual(my_strcpy(str1, str2), expected);
}

bool StrCpy_FirstSizeLessSecondSize(){
    char str1[128] = "aaa";
    const char* str2 = "abcabc";
    const char * expected = "abcabc";
    return StrsEqual(my_strcpy(str1, str2), expected);
}

bool StrCpy_Equal(){
    char str1[128] = "aaa";
    const char* str2 = "aaa";
    const char * expected = "aaa";
    return StrsEqual(my_strcpy(str1, str2), expected);
}

int Test_StrCpy(){
    const int countTests = 7;
    int countCorrectTests = 0;

    countCorrectTests += PrintPartResult("StrCpy_Empty", StrCpy_Empty());
    countCorrectTests += PrintPartResult("StrCpy_FirstEmptySecondNotEmpty", StrCpy_FirstEmptySecondNotEmpty());
    countCorrectTests += PrintPartResult("StrCpy_FirstNotEmptySecondEmpty", StrCpy_FirstNotEmptySecondEmpty());
    countCorrectTests += PrintPartResult("StrCpy_NotEmpty", StrCpy_NotEmpty());
    countCorrectTests += PrintPartResult("StrCpy_FirstSizeGreaterSecondSize", StrCpy_FirstSizeGreaterSecondSize());
    countCorrectTests += PrintPartResult("StrCpy_FirstSizeLessSecondSize", StrCpy_FirstSizeLessSecondSize());
    countCorrectTests += PrintPartResult("StrCpy_Equal", StrCpy_Equal());

    PrintAllResult("Test_StrCpy", countCorrectTests == countTests);
    return countTests - countCorrectTests;
}


bool StrCat_Empty(){
    char str1[128] = "";
    const char* str2 = "";
    const char* expected = "";
    return StrsEqual(my_strcat(str1, str2), expected);
}

bool StrCat_FirstEmtpySecondNotEmptyStr(){
    char str1[128] = "";
    const char* str2 = "abc";
    const char* expected = "abc";
    return StrsEqual(my_strcat(str1, str2), expected);
}

bool StrCat_FirstNotEmtpySecondEmptyStr(){
    char str1[128] = "abc";
    const char* str2 = "";
    const char* expected = "abc";
    return StrsEqual(my_strcat(str1, str2), expected);
}

bool StrCat_NotEmpty(){
    char str1[128] = "abc";
    const char* str2 = "abc";
    const char* expected = "abcabc";
    return StrsEqual(my_strcat(str1, str2), expected);
}

int Test_StrCat(){
    const int countTests = 4;
    int countCorrectTests = 0;

    countCorrectTests += PrintPartResult("StrCat_Empty", StrCat_Empty());
    countCorrectTests += PrintPartResult("StrCat_FirstEmtpySecondNotEmptyStr", StrCat_FirstEmtpySecondNotEmptyStr());
    countCorrectTests += PrintPartResult("StrCat_FirstNotEmtpySecondEmptyStr", StrCat_FirstNotEmtpySecondEmptyStr());
    countCorrectTests += PrintPartResult("StrCat_NotEmpty", StrCat_NotEmpty());

    PrintAllResult("Test_StrCat", countCorrectTests == countTests);
    return countTests - countCorrectTests;
}


bool StrCmp_EmptyStr(){
    const char* str1 = "";
    const char* str2 = "";
    return my_strcmp(str1, str2) == 0;
}

bool StrCmp_NotEmptyEqualStr(){
    const char* str1 = "abc";
    const char* str2 = "abc";
    const int expected = 0;
    return my_strcmp(str1, str2) == 0;
}

bool StrCmp_NotEmptyFirstGreaterSecond(){
    const char* str1 = "aaa";
    const char* str2 = "bbb";
    return my_strcmp(str1, str2) < 0;
}

bool StrCmp_NotEmptyFirstLessSecond(){
    const char* str1 = "bbb";
    const char* str2 = "aaa";
    return my_strcmp(str1, str2) > 0;
}

bool StrCmp_NotEmptyFirstSizeGreaterSecondSize(){
    const char* str1 = "aaaa";
    const char* str2 = "aaa";
    return my_strcmp(str1, str2) > 0;
}

bool StrCmp_NotEmptyFirstSizeLessSecondSize(){
    const char* str1 = "aaa";
    const char* str2 = "aaaa";
    return my_strcmp(str1, str2) < 0;
}

bool StrCmp_FirstEmptySecondNotEmpty(){
    const char* str1 = "";
    const char* str2 = "abc";
    return my_strcmp(str1, str2) < 0;
}

bool StrCmp_FirstNotEmptySecondEmpty(){
    const char* str1 = "abc";
    const char* str2 = "";
    return my_strcmp(str1, str2) > 0;
}

int Test_StrCmp(){
    const int countTests = 7;
    int countCorrectTests = 0;

    countCorrectTests += PrintPartResult("StrCmp_EmptyStr", StrCmp_EmptyStr());
    countCorrectTests += PrintPartResult("StrCmp_NotEmptyEqualStr", StrCmp_NotEmptyEqualStr());
    countCorrectTests += PrintPartResult("StrCmp_NotEmptyFirstGreaterSecond", StrCmp_NotEmptyFirstGreaterSecond());
    countCorrectTests += PrintPartResult("StrCmp_NotEmptyFirstLessSecond", StrCmp_NotEmptyFirstLessSecond());
    countCorrectTests += PrintPartResult("StrCmp_NotEmptyFirstSizeGreaterSecondSize", StrCmp_NotEmptyFirstSizeGreaterSecondSize());
    countCorrectTests += PrintPartResult("StrCmp_NotEmptyFirstSizeLessSecondSize", StrCmp_NotEmptyFirstSizeLessSecondSize());
    countCorrectTests += PrintPartResult("StrCmp_FirstEmptySecondNotEmpty", StrCmp_FirstEmptySecondNotEmpty());

    PrintAllResult("Test_StrCmp", countCorrectTests == countTests);
    return countTests - countCorrectTests;
}


bool StrLen_EmptyStr(){
    const char* str = "";
    const int expected = 0;
    return my_strlen(str) == expected;
}

bool StrLen_NotEmptyStr(){
    const char* str = "aaa";
    const int expected = 3;
    return my_strlen(str) == expected;
}

int Test_StrLen(){
    const int countTests = 2;
    int countCorrectTests = 0;

    countCorrectTests += PrintPartResult("StrLen_EmptyStr", StrLen_EmptyStr());
    countCorrectTests += PrintPartResult("StrLen_NotEmptyStr", StrLen_NotEmptyStr());

    PrintAllResult("Test_StrLen", countCorrectTests == countTests);
    return countTests - countCorrectTests;
}
