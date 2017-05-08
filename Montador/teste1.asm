L1: EQU 1
L2: EQU                                           1
;oi meu chapa
SECTION                                        TEXT
;linha de comentarios
rot1: rot2: ;rotulo redefinindo rotulo?
rot3: ;teste
9rpt: ;?
rot4: 42
rot1: 1; redefiniu?
9rpt: ;?
power_of_DARK_SIDE A B ; isso nao existe jovem
LOAD A rot3+b
LOAD A rot3+2
COPY A,rot3
COPY A, rot3
COPY A ;ops B
STOP
