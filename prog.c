#include "machine.h"

//! Second exemple de segment de texte.
/*!
 * \note On voit ici l'intérêt de l'initialisation d'une union avec nommage
 * explicite des champs.
 */

Instruction text[] = {
//   type		 cop	imm	ind	regcond	operand
//-------------------------------------------------------------
    
    {.instr_absolute =  {CALL, 	 true, false, 	0, 	3	}},  // 00
    {.instr_absolute =  {NOP, 	 true, false, 	0, 	25	}},  // 00
    {.instr_absolute =  {NOP,	 false, false, 	0, 	1	}},  // 00
    {.instr_absolute =  {HALT,	 false, false, 	0, 	0	}},  // 00
    
    
    
    
};

//! Taille utile du programme
const unsigned textsize = sizeof(text) / sizeof(Instruction);

//! Premier exemple de segment de données initial
Word data[20] = {
    0,  // 0
    0,  // 1: résultat
    20, // 2: premier opérande
    5,  // 3: second opérande
};

//! Fin de la zone de données utile
const unsigned dataend = 10;

//! Taille utile du segment de données
const unsigned datasize = sizeof(data) / sizeof(Word);  
