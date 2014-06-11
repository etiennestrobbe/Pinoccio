#include "debug.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50


void print_help();
void print_end();
void simul_instruction(Machine *pmach);
bool debug = true;

//! Dialogue de mise au point interactive pour l'instruction courante.
/*!
 * Cette fonction gère le dialogue pour l'option \c -d (debug). Dans ce mode,
 * elle est invoquée après l'exécution de chaque instruction.  Elle affiche le
 * menu de mise au point et on exécute le choix de l'utilisateur. Si cette
 * fonction retourne faux, on abandonne le mode de mise au point interactive
 * pour les instructions suivantes et jusqu'à la fin du programme.
 * 
 * \param mach la machine/programme en cours de simulation
 * \return vrai si l'on doit continuer en mode debug, faux sinon
 */
bool debug_ask(Machine *pmach){
	int size = MAX;
	char c[MAX];
	while(debug){
		printf("DEBUG ? ");
		fgets(c,size,stdin);
		if(strcmp(c,"RET\n")==0 || strcmp(c,"\n")==0){
			simul_instruction(pmach);
		}			
		switch(*c){
			case 'h':print_help();break;
			case 'c':debug = false;break;
			case 's':simul_instruction(pmach);break;
			case 'm':print_cpu(pmach);print_data(pmach);break;
			case 'r':print_cpu(pmach);break;
			case 'd':print_data(pmach);break;
			case 't':
			case 'p':print_program(pmach);break;
			default:fflush(stdin);break;		
		}	
			
	}
	return debug;
	
	
}

void simul_instruction(Machine *pmach){
	Instruction *text = pmach->_text;
	if(text[pmach->_pc].instr_generic._cop == LAST_COP){
		simul(pmach,false);
		print_end(pmach);
		exit(0);	
	}
	else{
		simul(pmach,true);
	}	
}

void print_help(){
	printf("\
	Available commands:\n\
	h	help\n\
	c	continue (exit interactive debug mode)\n\
	s	step by step (next instruction)\n\
	RET	step by step (next instruction)\n\
	r	print registers\n\
	d	print data memory\n\
	t	print text (program) memory\n\
	p	print text (program) memory\n\
	m	print registers and data memory\n");
}

void print_end(Machine *pmach){
	printf("*** Machine state after execution ***\n");
	print_program(pmach);
	print_data(pmach);
	print_cpu(pmach);
}
