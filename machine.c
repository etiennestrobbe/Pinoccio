#include "machine.h"
#include "exec.h"
#include "debug.h"
#include <stdio.h>

/**
 * \file machine.h
 * \brief implementation de la machine
 * \author Maylanie
 * \version 0.1
 * \date 11 Juin 2014
 * 
 * Implémentation de la machine décrite dans machine.h
 */

void load_program 	( 	Machine *  	pmach,
		unsigned  	textsize,
		Instruction  	text[textsize],
		unsigned  	datasize,
		Word  	data[datasize],
		unsigned  	dataend 
	){
		pmach->_textsize = textsize;
		pmach->_text = text;
		pmach->_datasize = datasize;
		pmach->_data = data;
		pmach->_dataend = dataend;
		
		//re-initialisation de pc
		pmach->_pc = 0;
		
		//la pile est vide à l'initialisation:
		pmach->_sp = datasize - 1; 
		
		
		//on vide les registres sauf sp?
		int i;
		for (i = 0; i < NREGISTERS-1; i++){
			pmach->_registers[i] = 0;
		}
}
	
	

void print_cpu 	( 	Machine *  	pmach	){
	Word *registres = pmach->_registers;
	
	printf("\n\n *** CPU ***\n\n");
	
	printf("PC: 0x%08x  \t", pmach->_pc);
	printf("CC: 0x%08x \n \n", pmach->_cc);
	
	int i;
	int cnt = 0;
	for (i = 0; i < NREGISTERS; i++){
		printf("R%2d : 0x%08x %d \t",i, registres[i], registres[i]);
		cnt++;

		if (cnt == 3){
			cnt = 0;
			printf("\n");
		}
	}
}
	
	
void print_data 	( 	Machine *  	pmach	){
	
	printf("\n\n *** DATA (size: %d, end = 0x%08x (%d))*** \n \n",pmach->_datasize, pmach->_dataend, pmach->_dataend);
	
	int i;
	int cnt = 0;
	for (i = 0; i < pmach->_datasize; i++){
		printf("0x%04x : 0x%08x %d \t",i, pmach->_data[i], pmach->_data[i]);
		cnt++;

		if (cnt == 3){
			cnt = 0;
			printf("\n");
		}
	}
	printf("\n");
	printf("\n");

}

void print_program 	( 	Machine *  	pmach	){
	printf("\n *** PROGRAM (size: %d) ***\n",pmach -> _textsize);
	unsigned add = 0;
	int i;
	for (i = 0; i < pmach ->_textsize; i++){
		printf("0x%04x: 0x%08x		",i,pmach -> _text[i]._raw);		
		print_instruction(pmach -> _text[i], add);
		putchar('\n');
	}
}

void read_program(Machine *mach, const char *programfile){
}

void dump_memory(Machine *pmach){
}

bool do_one_step(Machine *pmach){
	Instruction instr = (pmach->_text)[(pmach->_pc)++];
	trace("Executing",pmach,instr,(pmach->_pc));
	return decode_execute(pmach,instr);
}

void simul(Machine *pmach, bool debug){
	bool halt = true;
	while(halt){
		if(debug){
			debug = debug_ask(pmach);
		}
		halt = do_one_step(pmach);
	}
}
		
