#include "machine.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>



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
	printf("\n *** PROGRAM (size: %d) ***\n",pmach -> _textsize);
	unsigned add = 0;
	int i;
	for (i = 0; i < pmach ->_textsize; i++){
		printf("0x%04x: 0x%08x		",i,pmach -> _text[i]._raw);		
		print_instruction(pmach -> _text[i], add);
		putchar('\n');
	}
}

void read_program(Machine *pmach, const char *programfile){
	int fichier;
	unsigned textsize, datasize, dataend;
	char c[50];	
		
	fichier = open(programfile, O_RDONLY); // fichier vaut -1 si open n'arrive pas a ouvrir le fichier.
	
	// Les 3 premiers entier non signés
	read(fichier, &c, sizeof(pmach -> _textsize));
	read(fichier, &c, sizeof(pmach -> _datasize));
	read(fichier, &c, sizeof(pmach -> _dataend));

	//Les instructions
	Instruction *text = malloc(textsize * sizeof(Instruction));
	for (int i = 0; i < textsize; i++){
		read(fichier, &text, sizeof(text));
	}
	//Les données
	Word *data = malloc(datasize * sizeof(Word));
	for (int i = 0; i < datasize; i++){
		read(fichier, &data, sizeof(data));
	}

	close(fichier);
	load_program(pmach, textsize, text, datasize, data, dataend);
	free(text);
	free(data);
}

void dump_memory(Machine *pmach){
}


void simul(Machine*pmach, bool debug){
	/*for(int i=0;i<pmach->_textsize;i++){
		(pmach->_pc)++;
		*/
	
}

		
