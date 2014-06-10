#include "machine.h"

//! Second exemple de segment de texte.
/*!
 * \note On voit ici l'intérêt de l'initialisation d'une union avec nommage
 * explicite des champs.
 */

Instruction text[] = {
//   type		 cop	imm	ind	regcond	operand
//-------------------------------------------------------------
    /*{.instr_absolute =  {PUSH, 	 false, false, 	0, 	2	}},  // 0
    {.instr_absolute =  {PUSH, 	 false, false, 	0, 	3	}},  // 1
    {.instr_absolute =  {PUSH, 	 true, false, 	0, 	27	}},  // 2
    {.instr_absolute =  {PUSH, 	 true, false, 	0, 	28	}},  // 3
    {.instr_absolute =  {PUSH, 	 true, false, 	0, 	28	}},  // 3
    {.instr_absolute =  {PUSH, 	 false, true, 	0, 	2	}},  // 4
    {.instr_absolute =  {PUSH, 	 false, true, 	0, 	3	}},  // 5
    {.instr_absolute =  {PUSH, 	 true, true, 	0, 	27	}},  // 6
    {.instr_absolute =  {PUSH, 	 true, true, 	0, 	28	}},  // 8
    {.instr_absolute =  {PUSH, 	 true, true, 	0, 	28	}},  // 9
    {.instr_absolute =  {PUSH, 	 true, true, 	0, 	28	}},  // A
    {.instr_absolute =  {PUSH, 	 true, true, 	0, 	28	}},  // B
    {.instr_absolute =  {PUSH, 	 true, true, 	0, 	28	}},  // C
    {.instr_absolute =  {PUSH, 	 true, true, 	0, 	28	}},  // D
    {.instr_absolute =  {PUSH, 	 true, true, 	0, 	28	}},  // E
    {.instr_absolute =  {PUSH, 	 true, true, 	0, 	28	}},  // F
    {.instr_absolute =  {PUSH, 	 true, true, 	0, 	28	}},  // 10
    {.instr_absolute =  {PUSH, 	 true, true, 	0, 	28	}},  // 11
    {.instr_absolute =  {PUSH, 	 true, true, 	0, 	28	}},  // 12
    {.instr_absolute =  {PUSH, 	 true, true, 	0, 	28	}},  // 13
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 14
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 15
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 16
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 17
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 18
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 19
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 1A
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 1B
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 1C
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 1D
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 1E
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 1F
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 20
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 21
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 22
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 23
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 24
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 25
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 26
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 27
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 28
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0	}},  // 29
    {.instr_absolute =  {CALL, 	 false, false, 	0, 	3	}},  // 2A
    {.instr_absolute =  {NOP, 	 false, false, 	0, 	0	}},  // 2B
    {.instr_absolute =  {HALT, 	 false, false, 	0, 	0	}},  // 2C
    {.instr_absolute =  {PUSH, 	 true, true, 	0, 	1	}},  // 2D
    {.instr_absolute =  {PUSH, 	 false, false, 	0, 	1 	}},  // 2E
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0 	}},  // 2E
    {.instr_absolute =  {POP, 	 false, false, 	0, 	0 	}},  // 2E
    {.instr_absolute =  {RET, 	 false, true, 	0, 	0	}},  // 2F*/
    {.instr_absolute =  {LOAD, 	 false, false, 	0, 	2	}},  // 00
    {.instr_absolute =  {SUB, 	 true, false, 	0, 	25	}},  // 00
    {.instr_absolute =  {STORE,	 false, false, 	0, 	1	}},  // 00
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
