#include "machine.h"

//! Second exemple de segment de texte.
/*!
 * \note On voit ici l'intérêt de l'initialisation d'une union avec nommage
 * explicite des champs.
 */

Instruction text[] = {
//   type		 cop	imm	ind	regcond	operand
//-------------------------------------------------------------
    
    {.instr_generic =  {BRANCH,	 false, false, 	8, 	4	}},  // 01
        
};

//! Taille utile du programme
const unsigned textsize = sizeof(text) / sizeof(Instruction);

//! Premier exemple de segment de données initial
Word data[4] = {
    0,  // 0
    0,  // 0
    0,  // 0
    0,  // 0
};

//! Fin de la zone de données utile
const unsigned dataend = 2;

//! Taille utile du segment de données
const unsigned datasize = sizeof(data) / sizeof(Word);  
