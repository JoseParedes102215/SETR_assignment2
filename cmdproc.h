/**

@file cmdproc.h
@brief header das funçoes de processamento

 @author José Paredes Manuel Miranda
 @date 28 March 2023
*/

#ifndef __CMD_PROC_H_
#define __CMD_PROC_H_

/* Some defines */
/* Other defines should be return codes of the functions */
/* E.g. #define CMD_EMPTY_STRING -1                      */
#define MAX_CMDSTRING_SIZE 10 /* Maximum size of the command string */ 
#define SOF_SYM '#'	          /* Start of Frame Symbol */
#define EOF_SYM '!'           /* End of Frame Symbol */
#define CMD_EMPTY_STRING -1		// if empty string or incomplete command found
#define INVALID_CMD -2			// if an invalid command was found  
#define SOF_SYM_NOT_FOUND -3  	// if "#" is not found
#define CMD_STRING_FULL -4		// excedido o numero maximo de caracteres para um comando
#define CMD_CS_ERROR -5			// erro no checksum
#define FRAMING_ERROR -6        // erro na estrutura do comando
#define INV_MSG -7

/* Function prototypes */

/**
@brief processa um array de caracteres
@return CMD_EMPTY_STRING se vazio
@return 0 se sucesso
@return INVALID_CMD se o comando processado é invalido
@return SOF_SYM_NOT_FOUND se nao foi encontrado #
*/
int cmdProcessor(void);

/**
@brief Envia um caracter para o array
@param newChar Caracter a ser enviado
@return 0 se tiver sucesso
@return CMD_STRING_FULL se o array estiver cheio
*/
int newCmdChar(unsigned char newChar);

/**
@brief Repõe o array
*/
void resetCmdString(void);

/**
@brief Imprime o conteudo do array
*/
void PrintCmdString(void);

/**
@brief Verifica o numero de caracteres a serem processados
@return Tamanho atual do array
*/
int cmdStringLength(void);

#endif
