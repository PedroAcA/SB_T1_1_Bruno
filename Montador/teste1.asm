SECTION TEXT
MOD_A: BEGIN
	MOD_B: EXTERN
	PUBLIC FAT
	PUBLIC N
	INPUT N
	LOAD N
	FAT: SUB ONE
	JMPZ FIM
	JMP MOD_B
;SECTION DATA
	FIM: OUTPUT N
	STOP
SECTION DATA
	N: SPACE
	ONE: CONST 1
END
