#include "machine.h"
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
	
	printf("\n CPU:\n\n");
	
	printf("PC: 0x%08x \n", pmach->_pc);
	printf("CC: 0x%08x \n \n", pmach->_cc);
	
	int i = 0;
	for (i = 0; i < NREGISTERS; i++){
		if (i == 1%3){
			printf("R[%d] = 0x%08x \n",i, registres[i]);
		}
		else{
			printf("R[%d] = 0x%08x \t",i, registres[i]);
		}
	}
}
	
	
void print_data 	( 	Machine *  	pmach	){
	
	printf("\n ETATS DES DATA: \n\n");
	int i;
	for (i = 0; i < pmach->_dataend; i++){
		printf("DATA[%d] = 0x%04x \n\n",i, pmach->_data[i]);
	}
	
	// Si le premier de la pile est vide, c'est qu'il faut se placer apres sp 
	printf("\n ETATS DE LA PILE");
	for (i = pmach->_sp; i < pmach->_datasize; i++){
		printf("STACK[%d] = 0x%04x \n\n",i, pmach->_data[i]);
	}
}
