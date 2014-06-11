//-----------------
// Instructions
//-----------------
		TEXT 10

		//Programme Principal
main	EQU *
		PUSH @result
		PUSH @op1
		PUSH @op1
		PUSH @op2
		PUSH @result
		HALT

		END

//-----------------
// Données et pile
//-----------------
        DATA 25
        
        WORD 0
result  WORD 99
op1     WORD 20
op2     WORD 5
        
        END
