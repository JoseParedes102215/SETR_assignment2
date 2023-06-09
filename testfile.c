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


/**
@brief Inicialização das variaveis
*/
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

/**
@brief Testa o caso de processar um array vazio
*/
void test_cmdProcessor_emptyString(void){
    TEST_ASSERT_EQUAL(CMD_EMPTY_STRING, cmdProcessor());
}

/**
@brief Testa a inserção de um caracter
*/
void test_newCmdChar_success(void){
    resetCmdString();
    TEST_ASSERT_EQUAL(0, newCmdChar('#'));
    //printf("%d\n",cmdStringLen);
    //TEST_ASSERT_EQUAL(1, cmdStringLen);
    TEST_ASSERT_EQUAL(1, cmdStringLength());
}

/**
@brief Testa a "limpeza" do array
*/
void test_resetCmdString(void){
    resetCmdString();
    newCmdChar('A');
    newCmdChar('B');
    resetCmdString();
    TEST_ASSERT_EQUAL(0, cmdStringLen);
    TEST_ASSERT_EQUAL('\0', cmdString[0]);
}

/**
@brief Testa a inserção de um caracter quando 
        o array está cheio
*/
void test_newCmdChar_full(void){
    resetCmdString();
    // enche o array com 10 elementos
    for (int i = 0; i < MAX_CMDSTRING_SIZE; i++) {
        newCmdChar('A');
    }
    TEST_ASSERT_EQUAL(CMD_STRING_FULL, newCmdChar('B'));
}

/**
@brief Processa um array sem o SOF_SYM (i.e. #)
*/
void test_cmdProcessor_NoHastag(void){
    resetCmdString();
    newCmdChar('P');
    newCmdChar('1');
    newCmdChar('2');
    newCmdChar('3');
    newCmdChar((unsigned char)('P'+'1'+'2'+'3'));
    newCmdChar('!');
    TEST_ASSERT_EQUAL(SOF_SYM_NOT_FOUND, cmdProcessor());
    //PrintCmdString();
}

/**
@brief Processa uma mensagem com o campo CMD com caracteres errados
        (CMD != 'P' && 'S')
*/
void test_cmdProcessor_invalidCMD(void){
    resetCmdString();
    newCmdChar('#');
    newCmdChar('X');
    newCmdChar('Y');
    newCmdChar('Z');
    newCmdChar('!');
    //PrintCmdString();
    TEST_ASSERT_EQUAL(INVALID_CMD, cmdProcessor());

    resetCmdString();
    newCmdChar('#');
    newCmdChar('Z');
    newCmdChar('1');
    newCmdChar('2');
    newCmdChar('!');
    //PrintCmdString();
    TEST_ASSERT_EQUAL(INVALID_CMD, cmdProcessor());
}

/**
@brief Testa o comando "P"
*/
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

/**
@brief Testa o comando "S"
*/
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

/**
@brief Testa a checksum do comando "P"
*/
void test_cmdProcessor_PCommand_Checksum(void){
    resetCmdString();
    newCmdChar('#');
    newCmdChar('P');
    newCmdChar('1');
    newCmdChar('2');
    newCmdChar('3');
    newCmdChar((unsigned char)('P'+'1'+'2'+'5'));
    newCmdChar('!');
    TEST_ASSERT_EQUAL(CMD_CS_ERROR, cmdProcessor());
}

/**
@brief Testa a estrutura do comando "P"
*/
void test_cmdProcessor_PCommand_FramingError(void){
    resetCmdString();
    newCmdChar('#');
    newCmdChar('P');
    newCmdChar('1');
    newCmdChar('2');
    newCmdChar('3');
    newCmdChar('4');
    newCmdChar((unsigned char)('P'+'1'+'2'+'5'));
    newCmdChar('!');
    TEST_ASSERT_EQUAL(FRAMING_ERROR, cmdProcessor());

    resetCmdString();
    newCmdChar('#');
    newCmdChar('P');
    newCmdChar('1');
    newCmdChar('2');
    newCmdChar('3');
    //newCmdChar('4');
    newCmdChar((unsigned char)('P'+'1'+'2'+'3'));
    newCmdChar('!');
    TEST_ASSERT_EQUAL(0, cmdProcessor());
}

/**
@brief Testa a estrutura do comando "S"
*/
void test_cmdProcessor_SCommand_FramingError(void){
    resetCmdString();
    newCmdChar('#');
    newCmdChar('S');
    newCmdChar('!');
    TEST_ASSERT_EQUAL(0, cmdProcessor());

    resetCmdString();
    newCmdChar('#');
    newCmdChar('S');
    newCmdChar('S');
    newCmdChar('!');
    TEST_ASSERT_EQUAL(FRAMING_ERROR, cmdProcessor());
}

/**
@brief Testa a existencia de EOF_SYM (!)
*/
void test_cmdProcessor_NoEOF(void){
    resetCmdString();
    newCmdChar('#');
    newCmdChar('P');
    newCmdChar('1');
    newCmdChar('2');
    newCmdChar('3');
    newCmdChar((unsigned char)('P'+'1'+'2'+'3'));
    newCmdChar('r');
    TEST_ASSERT_EQUAL(EOF_SYM_NOT_FOUND, cmdProcessor());   
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(test_cmdProcessor_emptyString);
    RUN_TEST(test_newCmdChar_success);
    RUN_TEST(test_resetCmdString);
    RUN_TEST(test_newCmdChar_full);
    RUN_TEST(test_cmdProcessor_NoHastag);
    RUN_TEST(test_cmdProcessor_invalidCMD);
    RUN_TEST(test_cmdProcessor_PCommand);
    RUN_TEST(test_cmdProcessor_SCommand);

    RUN_TEST(test_cmdProcessor_PCommand_Checksum);
    RUN_TEST(test_cmdProcessor_PCommand_FramingError);
    RUN_TEST(test_cmdProcessor_SCommand_FramingError);

    RUN_TEST(test_cmdProcessor_NoEOF);
    UNITY_END();

    return 0;
}