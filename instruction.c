#include "instruction.h"
#include <stdio.h>

const char* cop_names[] = {"ILLOP", "NOP", "LOAD", "STORE", "ADD", "SUB", "BRANCH", "CALL", "RET", "PUSH", "POP", "HALT"};

const char* condition_names[] = {"NC", "EQ", "NE", "GT", "GE", "LT", "LE"};

void print_registre(Instruction i){
	(i.instr_generic._regcond >= 10) ? printf("R%d, ", i.instr_generic._regcond) : printf("R0%d, ", i.instr_generic._regcond);
	// Ca dépote le ternaire !
}

void print_condition(Instruction i){
	printf("%s, ",condition_names[i.instr_generic._regcond]); //VERIFIER QUE i.instr_generic._regcond <= 6 !!!!!!!!! (lors de l'appelle)
}

void print_operande(Instruction i){
	if (i.instr_generic._immediate == 1){
		printf("#%d", i.instr_immediate._value);
	}
	else{
		if (i.instr_generic._indexed == 1){
			(i.instr_indexed._rindex >= 10) ? printf("%d[R%d]", i.instr_indexed._offset, i.instr_indexed._rindex) : printf("%d[R0%d]", i.instr_indexed._offset, i.instr_indexed._rindex);
			//Encore un !
		}
		else{ //TESTER LES 4 CAS !
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

void print_instruction(Instruction instr, unsigned addr){
	//printf("0x%u: ", addr); NE SERT A RIEN
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
