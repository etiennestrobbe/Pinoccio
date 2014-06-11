#include "machine.h"
#include "exec.h"
#include "debug.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>



/**
 * \file machine.c
 * \brief implementation de la machine
 * \version 0.1
 * \date 11 Juin 2014
 * 
 * Implémentation de la machine décrite dans machine.h
 */


//! Chargement d'un programme
/*!
 * La machine est réinitialisée et ses segments de texte et de données sont
 * remplacés par ceux fournis en paramètre.
 *
 * \param pmach la machine en cours d'exécution
 * \param textsize taille utile du segment de texte
 * \param text le contenu du segment de texte
 * \param datasize taille utile du segment de données
 * \param data le contenu initial du segment de texte
 * 
 * \author Maylanie
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
		
		
		//on vide les registres sauf sp
		int i;
		for (i = 0; i < NREGISTERS-1; i++){
			pmach->_registers[i] = 0;
		}
}
	
//! Affichage des registres du CPU
/*!
 * Les registres généraux sont affichées en format hexadécimal et décimal.
 *
 * \param pmach la machine en cours d'exécution
 * 
 * \author Maylanie
 */	
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
	
//! Affichage des données du programme
/*!
 * Les valeurs sont affichées en format hexadécimal et décimal.
 *
 * \param pmach la machine en cours d'exécution
 * 
 * \author Maylanie
 */
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
//! Affichage des instructions du programme
/*!
 * Les instructions sont affichées sous forme symbolique, précédées de leur adresse.
.* 
 * \param pmach la machine en cours d'exécution
 * 
 * \author Remy
 */
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

//! Lecture d'un programme depuis un fichier binaire
/*!
 * Le fichier binaire a le format suivant :
 * 
 *    - 3 entiers non signés, la taille du segment de texte (\c textsize),
 *    celle du segment de données (\c datasize) et la première adresse libre de
 *    données (\c dataend) ;
 *
 *    - une suite de \c textsize entiers non signés représentant le contenu du
 *    segment de texte (les instructions) ;
 *
 *    - une suite de \c datasize entiers non signés représentant le contenu initial du
 *    segment de données.
 *
 * Tous les entiers font 32 bits et les adresses de chaque segment commencent à
 * 0. La fonction initialise complétement la machine.
 *
 * \param pmach la machine à simuler
 * \param programfile le nom du fichier binaire
 * 
 * \author Remy
 *
 */
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

//! Affichage du programme et des données
/*!
 * On affiche les instruction et les données en format hexadécimal, sous une
 * forme prête à être coupée-collée dans le simulateur.
 *
 * Pendant qu'on y est, on produit aussi un dump binaire dans le fichier
 * dump.prog. Le format de ce fichier est compatible avec l'option -b de
 * test_simul.
 *
 * \param pmach la machine en cours d'exécution
 * \author Etienne
 */
void dump_memory(Machine *pmach){
}

/**
 * \fn bool do_one_step (Machine *pmach)
 * \brief Excecute une instruction
 * 
 * \param pmach la machine considérée
 * \author Etienne
 * 
 * Excecute l'instruction suivante (renseignée dans pc) de la 
 * machine passée en parametre.
 */
bool do_one_step(Machine *pmach){
	Instruction instr = (pmach->_text)[(pmach->_pc)++];
	trace("Executing",pmach,instr,(pmach->_pc));
	return decode_execute(pmach,instr);
}


//! Simulation
/*!
 * La boucle de simualtion est très simple : recherche de l'instruction
 * suivante (pointée par le compteur ordinal \c _pc) puis décodage et exécution
 * de l'instruction.
 *
 * \param pmach la machine en cours d'exécution
 * \param debug mode de mise au point (pas à apas) ?
 * 
 * \author Etienne
 */
void simul(Machine *pmach, bool debug){
	bool halt = true;
	while(halt){
		if(debug){
			debug = debug_ask(pmach);
		}
		halt = do_one_step(pmach);
	}
}
		
