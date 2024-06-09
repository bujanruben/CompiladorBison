# CalculadoraBison

Calculadora usando Bison y flex junto a C.

Se pueden introducir operaciones en la linea de comandos después del puntero que aparece. Al dar enter, la calculadora ejecuta la operación. Se mostrará por pantalla si la opción echo está en on y no acaba en ';'. Se pueden usar tanto operaciones simples como ciertas funciones más complejas.

También tiene la opción de usar ciertas comandos de código, como ejecutar un archivo con líneas con operaciones que ejecutará en orden línea a línea.

Constantes:

PI

Número de euler

Operaciones simples admitidas:

Suma '+'

Resta '-'

Multiplicación '*'

División '/'

Potencia '^'

Módulo '%'

+=	-=

++ 		-- 		*= 		/= 		????

Operaciones con funciones:

sin

cos

tan

sec

cosec

cotan

log

ln

exp

sqrt

Comandos complementarios:

echo(on/off)    	Enciende o apaga echo (por defecto está en on)
help()          	Muestra ayuda general
quit()         	    Cierra el programa
workspace()         Muestra todas las variables del sistema asignadas
clear()         	Limpia las variables de trabajo creadas
load()          	Carga fichero que se imprime segun la configuración de echo


Compilación y ejecución:

Compilación en ubuntu LTS 22.04.3 usando ./compilacion.sh
Ejecución con ./calculadora
Ejecución de un archivo con ./calculadora archivo.txt