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
	
	printf("\n ETATS DES REGISTRES:");

	int i = 0;
	for (i = 0; i < NREGISTERS; i++){
		printf("R[%d] = %x",i, registres[i]);
	}
}
	
	
void print_data 	( 	Machine *  	pmach	){
	
	printf("\n ETATS DES DATA:");
	int i;
	for (i = 0; i < pmach->_dataend; i++){
		printf("DATA[%d] = %x",i, pmach->_data[i]);
	}
	
	// Si le premier de la pile est vide, c'est qu'il faut se placer apres sp 
	printf("\n ETATS DE LA PILE");
	for (i = pmach->_sp; i < pmach->_datasize; i++){
		printf("STACK[%d] = %x",i, pmach->_data[i]);
	}
}


void print_program 	( 	Machine *  	pmach	){
	
	printf("\n LE PROGRAMME A EXCECUTER:");
	
	int i;
	for (i=0; i < pmach->_textsize; i++){
		//pas fini
	}
}

void read_program(Machine *mach, const char *programfile){
}

void dump_memory(Machine *pmach){
}

void simul(Machine*pmach, bool debug){
	for(int i=0;i<pmach->_textsize;i++){
		(pmach->_pc)++;
		
	
}

		
