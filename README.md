Ap_template
===========

Esta es la plantilla necesaria para la creación de un proyecto que será luego grabado con el boot

Para utilizar la plantilla, se debe de abrir el proyecto mediante el MPLABX, no cambiar los bits de 
configuración y escribir el código directamente dentro de la función main, es recomendable revisar
la configuración de los puertos antes de grabar el micro.

La distribución de patas para el 18F4550 es:



Reset   1   -       -   40  RB7/PGD
RA0     2   -       -   39  RB6/PGC
RA1     3   -       -   38  RB5
RA2     4   -       -   37  RB4
RA3     5   -       -   36  RB3
RA4     6   -       -   35  RB2
RA5     7   -       -   34  RB1
RE0     8   -       -   33  RB0
RE1     9   -       -   32  VDD
RE2     10  -       -   31  VSS
VDD     11  -       -   30  RD7
VSS     12  -       -   29  RD6
OSC1    13  -       -   28  RD5
OSC2    14  -       -   27  RD4
RC0     15  -       -   26  RC7
RC1     16  -       -   25  RC6
RC2     17  -       -   24  RC5/D+
VUSB    18  -       -   23  RC4/D-
RD0     19  -       -   22  RD3
RD1     20  -       -   21  RD2
