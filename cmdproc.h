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
//#define CMD_CS_ERROR -5			// erro no checksum

/* Function prototypes */
int cmdProcessor(void);
int newCmdChar(unsigned char newChar);
void resetCmdString(void);
void PrintCmdString(void);
int cmdStringLength(void);

#endif
