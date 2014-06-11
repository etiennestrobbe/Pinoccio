//-----------------
// Instructions
//-----------------
		TEXT 10

		//Programme Principal
main	EQU *
		LOAD R1, @mot2		
		STORE R1, @15
		STORE R1, @16
		STORE R1, @255
		STORE R1, @256
		STORE R1, @4095
		STORE R1, @4096
		STORE R1, @4100 
		HALT

		END

//-----------------
// Données et pile
//-----------------
        DATA 260
        
mot1    WORD 28
mot2	WORD 28
mot3    WORD 28
mot4    WORD 28
mot5	WORD 28
mot6	WORD 28
        
        END
