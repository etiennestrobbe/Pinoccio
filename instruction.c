/**
 * \file instruction.c
 * \brief Affichage des instructions
 * \author Rémy.D
 * \date 10 juin 2014
 *
 * Programme permettant l'affichage d'une instruction sous la forme : COP REG, OP.
 */
#include "instruction.h"
#include <stdio.h>

//! Forme imprimable des codes opérations
const char* cop_names[] = {"ILLOP", "NOP", "LOAD", "STORE", "ADD", "SUB", "BRANCH", "CALL", "RET", "PUSH", "POP", "HALT"};

//! Forme imprimable des conditions
const char* condition_names[] = {"NC", "EQ", "NE", "GT", "GE", "LT", "LE"};

/**
 * \fn void print_registre(Instruction i)
 * \brief Affiche le registre de l'instruction
 * \param i, l'instruction a afficher.
 */
void print_registre(Instruction i){
	(i.instr_generic._regcond >= 10) ? printf("R%d, ", i.instr_generic._regcond) : printf("R0%d, ", i.instr_generic._regcond);
}

/**
 * \fn void print_condition(Instruction i)
 * \brief Affiche la condition de l'instruction
 * \param i, l'instruction a afficher.
 */
void print_condition(Instruction i){
	printf("%s, ",condition_names[i.instr_generic._regcond]);
}

/**
 * \fn void print_operande(Instruction i)
 * \brief Affiche l'opérande de l'instruction: la valeur immédiate ou l'adresse absolue ou l'adresse indexée
 * \param i, l'instruction a afficher.
 */
void print_operande(Instruction i){
	if (i.instr_generic._immediate == 1){
		printf("#%d", i.instr_immediate._value);
	}
	else{
		if (i.instr_generic._indexed == 1){
			(i.instr_indexed._rindex >= 10) ? printf("%d[R%d]", i.instr_indexed._offset, i.instr_indexed._rindex) : printf("%d[R0%d]", i.instr_indexed._offset, i.instr_indexed._rindex);
		}
		else{
			if (i.instr_absolute._address < 16){
				printf("@0x000%x", i.instr_absolute._address); //%x permet l'affiche en hexadecimal
			}
			else if (i.instr_absolute._address >= 16 && i.instr_absolute._address < 256){
				printf("@0x00%x", i.instr_absolute._address);
			}	
			else if (i.instr_absolute._address >=256 && i.instr_absolute._address<4096){
				printf("@0x0%x", i.instr_absolute._address);
			}
			else{
				printf("@0x%x", i.instr_absolute._address);
			}
		}
	}
}

/**
 * \fn void print_instruction(Instruction instr, unsigned addr)
 * \brief Affiche une instruction en entière
 * \param i, l'instruction a afficher.
 */
void print_instruction(Instruction instr, unsigned addr){
	printf("%s ",cop_names[instr.instr_generic._cop]);
	switch(instr.instr_generic._cop){
		case LOAD:
			print_registre(instr);
			print_operande(instr);
			break;
		case STORE:
			print_registre(instr);
			print_operande(instr);
			break;
		case ADD:
			print_registre(instr);
			print_operande(instr);
			break;
		case SUB:
			print_registre(instr);
			print_operande(instr);
			break;
		case BRANCH:
			print_condition(instr);
			print_operande(instr);
			break;
		case CALL:
			print_condition(instr);
			print_operande(instr);
			break;
		case PUSH:
			print_operande(instr);
			break;
		case POP:
			print_operande(instr);
			break;
		default:
			break;		
	}
}
