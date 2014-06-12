#include <stdio.h>
#include "error.h"

/**
 * \file error.c
 * \brief implementation de error.h
 * \version 0.3
 * \date 10 Juin 2014
 * \author Maylanie
 */
 

//! Affichage d'une erreur et fin du simulateur
/*!
 * \note Toutes les erreurs étant fatales on ne revient jamais de cette
 * fonction. L'attribut \a noreturn est une extension (non standard) de GNU C
 * qui indique ce fait.
 * 
 * \param err code de l'erreur
 * \param addr adresse de l'erreur
 */
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

//! Affichage d'un avertissement
/*!
 * \param warn code de l'avertissement
 * \param addr adresse de l'erreur
 */
void warning(Warning warn, unsigned addr){
	if (warn == WARN_HALT){
		printf("WARNING: HALT reached at address 0x%04x\n", addr);
	}
}

