L1: EQU 1
L2: EQU                                           1
;oi meu chapa
SECTION                                        TEXT
;linha de comentarios
BEGIN
rot1: rot2: ;rotulo redefinindo rotulo?
rot3: L1;teste
9rpt: ;?
rot4: 42
rot1: 1; redefiniu?
9rpt: ;?
power_of_DARK_SIDE A B ; isso nao existe jovem
LOAD A rot3+b
LOAD  rot3+b
LOAD A rot3+2
LOAD rot3+2
COPY A,rot3
COPY A, rot3
COPY A ;ops B
COPY ben10,rot3
COPY ben10+2,rot3+4
;STOP
C#: space 3
SECTION DATA
ben10: CONST 5
END
