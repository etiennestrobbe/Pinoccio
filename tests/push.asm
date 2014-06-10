//-----------------
// Instructions
//-----------------
        TEXT 30

        // Programme principal
main	PUSH @op1
		PUSH @op2
		CALL NC, @prog
        STORE R00, @result
        STORE R01, @op2
        //POP R00
        HALT
        
prog	LOAD R00, 3[R15]
		LOAD R01, 2[R15]
loop	SUB R01, #1
		BRANCH LE, @return
		ADD R00, 3[R15]
		BRANCH NC, @loop
return	RET

        
        END
        
//-----------------
// Données et pile
//-----------------
        DATA 00

result  WORD 0
op1     WORD 14
op2     WORD 7
        END
