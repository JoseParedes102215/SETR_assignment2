/* ***************************************************** */
/* SETR 22/23, Paulo Pedreiras                           */
/* Base code for Unit Testing                            */
/*    Simple example of command processor                */
/*    Note that there are several simplifications        */
/*    E.g. Kp, Ti and Td usually are not integer values  */
/*    Code can (and should) be improved. E.g. error      */ 
/*        codes are "magic numbers" in the middle of the */
/*        code instead of being (defined) text literals  */
/* ***************************************************** */

#include <stdio.h>

#include "cmdproc.h"

/* PID parameters */
/* Note that in a real application these vars would be extern */
char Kp, Ti, Td;

/* Process variables */ 
/* Note that in a real application these vars would be extern */
int setpoint, output, error; 

/* Internal variables */
static char cmdString[MAX_CMDSTRING_SIZE];
static unsigned char cmdStringLen = 0; 

/* ************************************************************ */
/* Processes the the chars received so far looking for commands */
/* Returns:                                                     */
/*  	 0: if a valid command was found and executed           */
/* 	-1: if empty string or incomplete command found             */
/* 	-2: if an invalid command was found                         */
/* 	-3: if a CS error is detected (command not executed)        */
/* 	-4: if string format is wrong                               */
/* ************************************************************ */
int cmdProcessor(void)
{
    int i;

    /* Detect empty cmd string */
    if(cmdStringLen == 0)
        return CMD_EMPTY_STRING;

    /* Find index of SOF */
    for(i=0; i < cmdStringLen; i++) {
        if(cmdString[i] == SOF_SYM) {
            break;
        }
    }
	
	/* If a SOF was found look for commands */
	if(i < cmdStringLen) {
		if(cmdString[i+1] == 'P') { /* P command detected */
			if (cmdString[i] != '#' || cmdString[i+6] !='!'){
				return FRAMING_ERROR;
			}
			Kp = cmdString[i+2];
			Ti = cmdString[i+3];
			Td = cmdString[i+4];
			int cs_calculado = (unsigned char)('P'+cmdString[i+2] + cmdString[i+3] + cmdString[i+4]);
			int cs_received =(unsigned char)cmdString[i+5];
			if (cs_received != cs_calculado){
				return CMD_CS_ERROR;
			}
			//printf("%d\n",(unsigned char)cmdString[i+5]);
			//printf("%d\n",(unsigned char)('P'+cmdString[i+2] + cmdString[i+3] + cmdString[i+4]));
			resetCmdString();
			return 0;
		}
		
		if(cmdString[i+1] == 'S') { /* S command detected */
			if (cmdString[i] != '#' || cmdString[i+2] !='!'){
				return FRAMING_ERROR;
			}
			printf("Setpoint = %d, Output = %d, Error = %d\n", setpoint, output, error);
			resetCmdString();
			return 0;
		}
		else{
			return INVALID_CMD;
		}
	}
	
	/* cmd string not null and SOF not found */
	else{
		return SOF_SYM_NOT_FOUND;
	}
	return INV_MSG;
}

/* ******************************** */
/* Adds a char to the cmd string 	*/
/* Returns: 				        */
/*  	 0: if success 		        */
/* 		-1: if cmd string full 	    */
/* ******************************** */
int newCmdChar(unsigned char newChar)
{
	/* If cmd string not full add char to it */
	if (cmdStringLen < MAX_CMDSTRING_SIZE) {
		cmdString[cmdStringLen] = newChar;
		cmdStringLen = cmdStringLen +1;
		return 0;		
	}
	
	/* If cmd string full return error */
	else{
		return CMD_STRING_FULL;
	}
}

void resetCmdString(void)
{
	cmdStringLen = 0;		
	return;
}

void PrintCmdString(void){
	for(int i=0; i < cmdStringLen; i++) {
		printf("%c ",cmdString[i]);
	}
	printf("\n");
}

int cmdStringLength(void){
	return cmdStringLen;
}