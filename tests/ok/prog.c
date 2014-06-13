#include "machine.h"

//! Second exemple de segment de texte.
/*!
 * \note On voit ici l'intérêt de l'initialisation d'une union avec nommage
 * explicite des champs.
 */

Instruction text[] = {
//   type		 cop	imm	ind	regcond	operand
//-------------------------------------------------------------
    
    {.instr_generic =  {NOP, 	 false, false, 	0, 	0	}},  // 00
    {.instr_generic =  {LOAD, 	 true, false, 	0, 	2	}},  // 01
    {.instr_generic =  {LOAD, 	 false, false, 	1, 	0	}},  // 02
    {.instr_indexed =  {LOAD, 	 false, true, 	2, 	0,2	}},  // 03
    {.instr_generic =  {BRANCH,	 false, false, 	3, 	7	}},  // 04
    {.instr_generic =  {NOP,	 false, false, 	3, 	7	}},  // 05
    {.instr_generic =  {NOP,	 false, false, 	3, 	7	}},  // 06
    {.instr_generic =  {LOAD,	 true, false, 	3, 	0	}},  // 07
    {.instr_generic =  {ADD,	 true, false, 	0, 	1	}},  // 08
    {.instr_indexed =  {BRANCH,	 false, true, 	4,3,11	}},  // 09
    {.instr_generic =  {NOP,	 false, true, 	4,10	}},  // 10
    {.instr_generic =  {ADD,	 false, false, 	1,4		}},  // 11
    {.instr_indexed =  {ADD,	 false, true, 	2,3,0	}},  // 12
    {.instr_generic =  {CALL,	 false, false, 	2,18	}},  // 13
    {.instr_generic =  {STORE,	 false, false, 	0,1		}},  // 14
    {.instr_indexed =  {STORE,	 false, true, 	2,3,2	}},  // 15
    {.instr_generic =  {HALT,	 false, false, 	2,18	}},  // 16
    {.instr_generic =  {NOP,	 false, false, 	2,18	}},  // 17
    {.instr_generic =  {SUB,	 true, false, 	0,3		}},  // 18
    {.instr_indexed =  {CALL,	 false, true, 	1,2,2	}},  // 19
    {.instr_generic =  {RET,	 false, true, 	1,2		}},  // 20
    {.instr_generic =  {NOP,	 false, true, 	1,2		}},  // 21
    {.instr_generic =  {NOP,	 false, true, 	1,2		}},  // 22
    {.instr_generic =  {SUB,	 false, false, 	0,4		}},  // 23
    {.instr_generic =  {CALL,	 false, false, 	6,27	}},  // 24
    {.instr_generic =  {RET,	 false, false, 	6,27	}},  // 25
    {.instr_generic =  {NOP,	 false, false, 	6,27	}},  // 26
    {.instr_generic =  {SUB,	 true, false, 	1,31	}},  // 27
    {.instr_generic =  {RET,	 true, false, 	0,31	}},  // 28
    
    
    
    
    
};

//! Taille utile du programme
const unsigned textsize = sizeof(text) / sizeof(Instruction);

//! Premier exemple de segment de données initial
Word data[20] = {
    4,  // 0
    0,  // 1
    0, // 2
    0,  // 3
    17,  // 4
};

//! Fin de la zone de données utile
const unsigned dataend = 10;

//! Taille utile du segment de données
const unsigned datasize = sizeof(data) / sizeof(Word);  
