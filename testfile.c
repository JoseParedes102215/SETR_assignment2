/**

@file testfile.c
@brief ficheiro de teste Unity

 @author José Paredes Manuel Miranda
 @date 28 March 2023
*/

#include "unity.h"
#include "cmdproc.h"

char Kp, Ti, Td;
int setpoint, output, error;
static char cmdString[MAX_CMDSTRING_SIZE];
static unsigned char cmdStringLen = 0;

void setUp(void){
    // inicializacao das variaveis
    Kp = 0;
    Ti = 0;
    Td = 0;
    setpoint = 0;
    output = 0;
    error = 0;
    cmdStringLen = 0;
    for (int i = 0; i < MAX_CMDSTRING_SIZE; i++) {
        cmdString[i] = '\0';
    }
}

void tearDown(void)
{

}

void test_cmdProcessor_emptyString(void){
    TEST_ASSERT_EQUAL(CMD_EMPTY_STRING, cmdProcessor());
}

void test_newCmdChar_success(void){
    resetCmdString();
    TEST_ASSERT_EQUAL(0, newCmdChar('#'));
    //printf("%d\n",cmdStringLen);
    //TEST_ASSERT_EQUAL(1, cmdStringLen);
    TEST_ASSERT_EQUAL(1, cmdStringLength());
}

void test_resetCmdString(void){
    resetCmdString();
    newCmdChar('A');
    newCmdChar('B');
    resetCmdString();
    TEST_ASSERT_EQUAL(0, cmdStringLen);
    TEST_ASSERT_EQUAL('\0', cmdString[0]);
}

void test_newCmdChar_full(void){
    resetCmdString();
    // enche o array com 10 elementos
    for (int i = 0; i < MAX_CMDSTRING_SIZE; i++) {
        newCmdChar('A');
    }
    TEST_ASSERT_EQUAL(CMD_STRING_FULL, newCmdChar('B'));
}

void test_cmdProcessor_NoHastag(void){
    resetCmdString();
    newCmdChar('P');
    TEST_ASSERT_EQUAL(SOF_SYM_NOT_FOUND, cmdProcessor());
    //PrintCmdString();
}

void test_cmdProcessor_invalidMessage(void){
    resetCmdString();
    //PrintCmdString();
    newCmdChar('9');
    newCmdChar('#');
    newCmdChar('2');
    newCmdChar('3');
    newCmdChar('P');
    //PrintCmdString();
    TEST_ASSERT_EQUAL(INVALID_CMD, cmdProcessor());
}

void test_cmdProcessor_invalid_command(void) {
    resetCmdString();
    newCmdChar('#');
    newCmdChar('X');
    newCmdChar('Y');
    newCmdChar('Z');
    newCmdChar('3');
    //PrintCmdString();
    TEST_ASSERT_EQUAL(INVALID_CMD, cmdProcessor());
}

void test_cmdProcessor_PCommand(void){
    resetCmdString();
    newCmdChar('#');
    newCmdChar('P');
    newCmdChar('1');
    newCmdChar('2');
    newCmdChar('3');
    newCmdChar((unsigned char)('P'+'1'+'2'+'3'));
    newCmdChar('!');
    //PrintCmdString();
    TEST_ASSERT_EQUAL(0, cmdProcessor());
    TEST_ASSERT_EQUAL('1', Kp);
    TEST_ASSERT_EQUAL('2', Ti);
    TEST_ASSERT_EQUAL('3', Td);
}

void test_cmdProcessor_SCommand(void){
    resetCmdString();
    setpoint = 10;
    output = 20;
    error = 30;
    newCmdChar('#');
    newCmdChar('S');
    newCmdChar('!');
    TEST_ASSERT_EQUAL(0, cmdProcessor());
    // verificar se o printf foi executado corretamente
}

/* to do:
- verficar o checksum
*/

int main(void){
    UNITY_BEGIN();
    RUN_TEST(test_cmdProcessor_emptyString);
    RUN_TEST(test_newCmdChar_success);
    RUN_TEST(test_resetCmdString);
    RUN_TEST(test_newCmdChar_full);
    RUN_TEST(test_cmdProcessor_NoHastag);
    RUN_TEST(test_cmdProcessor_invalidMessage);
    RUN_TEST(test_cmdProcessor_invalid_command);
    RUN_TEST(test_cmdProcessor_PCommand);
    RUN_TEST(test_cmdProcessor_SCommand);
    UNITY_END();

    return 0;
}