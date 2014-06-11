#include "machine.h"

//! Second exemple de segment de texte.
/*!
 * \note On voit ici l'intérêt de l'initialisation d'une union avec nommage
 * explicite des champs.
 */

Instruction text[] = {
//   type		 cop	imm	ind	regcond	operand
//-------------------------------------------------------------
    
    {.instr_generic =  {CALL, 	 false, false, 	0, 	10	}},  // 00
    {.instr_indexed =  {CALL,  	false, true, 	0,10,  1	}},  // 01
    {.instr_generic =  {HALT, 	 false, false, 	0, 	0	}},  // 02
    {.instr_generic =  {NOP, 	 false, false, 	0, 	0	}},  // 03
    {.instr_generic =  {NOP, 	 false, false, 	0, 	0	}},  // 04
    {.instr_generic =  {BRANCH,  false, false, 	0, 	2	}},  // 05
    {.instr_generic =  {NOP, 	 false, false, 	0, 	0	}},  // 06
    {.instr_generic =  {NOP, 	 false, false, 	0, 	0	}},  // 07
    {.instr_generic =  {NOP, 	 false, false, 	0, 	0	}},  // 08
    {.instr_generic =  {NOP, 	 false, false, 	0, 	0	}},  // 09
    {.instr_generic =  {LOAD, 	 true, false, 	10, 10	}},  // 10
    {.instr_generic =  {LOAD, 	 true, false, 	0, 	16	}},  // 11
    {.instr_generic =  {LOAD, 	 false, false, 	1, 	2	}},  // 12
    {.instr_generic =  {LOAD, 	 true, false, 	2, 	0	}},  // 13
    {.instr_generic =  {STORE, 	 false, false, 	0, 	0	}},  // 14
    {.instr_generic =  {STORE, 	 false, false, 	1, 	1	}},  // 15
    {.instr_generic =  {ADD, 	 true, false, 	0, 	1	}},  // 16
    {.instr_generic =  {ADD, 	 false, false, 	0, 	3	}},  // 17
    {.instr_indexed =  {ADD, 	 false, true, 0, 2 ,0	}},  // 18
    {.instr_generic =  {LOAD, 	 true,  true,   3,  40	}},  // 19
    {.instr_generic =  {SUB, 	 true,  true,   3,  20	}},  // 20
    {.instr_generic =  {SUB, 	 false,  false,   3,  0	}},  // 21
    {.instr_indexed =  {SUB, 	 false, true, 0, 2 ,0	}},  // 22
    {.instr_generic =  {RET, 	 false, false, 	0, 	0	}},  // 23
    
    
    
    
    
};

//! Taille utile du programme
const unsigned textsize = sizeof(text) / sizeof(Instruction);

//! Premier exemple de segment de données initial
Word data[20] = {
    0,  // 0
    1,  // 1: résultat
    20, // 2: premier opérande
    5,  // 3: second opérande
};

//! Fin de la zone de données utile
const unsigned dataend = 10;

//! Taille utile du segment de données
const unsigned datasize = sizeof(data) / sizeof(Word);  
