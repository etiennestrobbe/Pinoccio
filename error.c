#include <stdio.h>
#include "error.h"
 
void error(Error err, unsigned addr){
	
	//verifie que l'erreur existe:
	if (err >=0 && err <= LAST_ERROR){
		switch (err){
			case ERR_NOERROR:
				printf("ERR_NOERROR at adress 0x%04x : not an error \n ", addr);
				break;
			case ERR_UNKNOWN:
				printf("ERR_UNKNOWN at adress 0x%04x : Unknown Instruction \n", addr);
				break;
			case ERR_ILLEGAL:
				printf("ERR_ILLEGAL at adress 0x%04x : Illegal Instruction \n", addr);
				break;
			case ERR_CONDITION:
				printf("ERR_CONDITION at adress 0x%04x : Illegal Condition \n", addr);
				break;
			case ERR_IMMEDIATE:
				printf("ERR_IMMEDIATE at adress 0x%04x : Forbiden use of Immediate Variable \n", addr);
				break;
			case ERR_SEGTEXT:
				printf("ERR_SEGTEXT at adress 0x%04x : Violation of size of text's segment \n", addr);
				break;
			case ERR_SEGDATA:
				printf("ERR_SEGDATA at adress 0x%04x : Violation of size of data's segment \n", addr);
				break;
			case ERR_SEGSTACK:
				printf("ERR_SEGSTACK at adress 0x%04x : Violation of size of stack's segment \n", addr);
				break;
			default:
				break;
			}
	}
	exit(0);
}

void warning(Warning warn, unsigned addr){
	if (warn == WARN_HALT){
		printf("ERR_SEGSTACK at adress 0x%04x : Violation of size of stack's segment \n", addr);
	}
}

