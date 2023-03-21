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
#define CMD_NOT_EXECUTED -3		// if a CS error is detected (command not executed)
#define STRING_FORMAT_WRONG -4  // if string format is wrong     

/* Function prototypes */
int cmdProcessor(void);
int newCmdChar(unsigned char newChar);
void resetCmdString(void);

#endif
