#include "machine.h"

//! Second exemple de segment de texte.
/*!
 * \note On voit ici l'intérêt de l'initialisation d'une union avec nommage
 * explicite des champs.
 */

Instruction text[] = {
//   type		 cop	imm	ind	regcond	operand
//-------------------------------------------------------------
    
    {.instr_generic =  {LOAD,	 true, false, 	0, 	4	}},  // 00
    {.instr_generic =  {STORE,	 false, false, 	0, 	5	}},  // 00
        
};

//! Taille utile du programme
const unsigned textsize = sizeof(text) / sizeof(Instruction);

//! Premier exemple de segment de données initial
Word data[4] = {
    0,  // 0
    1,  // 1
    2,  // 2
};

//! Fin de la zone de données utile
const unsigned dataend = 2;

//! Taille utile du segment de données
const unsigned datasize = sizeof(data) / sizeof(Word);  
