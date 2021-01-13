Tipo de Dato Abstracto: ARBOL DE BUSQUEDA BINARI0.					Lucia Maria Liceri Martinez	Padron: 105964

En este .zip se encuentra la implementacion de un arbol de busqueda binario. Se implementa desde su creación hasta su destrucción 
junto a las funciones principales del mismo, como buscar, borrar e insertar. Ademas se implementan 3 tipos de recorrido (Inorden,
preorden, postorden) y un iterador interno que recorrerá el arbol segun el tipo de recorrido que se le asigne.
Además, en este .zip se encuentra un conjunto de pruebas unitarias que verifican el correcto funcionamiento de la implementación.

La implementación de esta Arbol de Busqueda Binario se compila utilizando:
• gcc *.c -o abb -g -std=c99 -Wall -Wconversion -Wtype -limits -pedantic -Werror -O0
Y se ejecuta utlizando:
• valgrind --leak -check=full --track -origins=yes --show -reachable=yes ./abb

CONCEPTOS A DESARROLLAR:

• Explicar qué es un ABB y cómo se diferencia de un Árbol Binario.

	Un ABB, es decir, un arbol de busqueda binario se diferencia de un simple Árbol Binario en que el ABB tiene reglas de inserción.
	Esto facilita la busqueda de elementos. Un Árbol Binario es simplemente un conjunto de nodos enlazados donde cada nodo tiene por
	lo menos dos hijos y a su vez esos nodos tienen hasta dos hijos cada uno. Estos nodos se insertan sin ningun tipo de criterio. 
	Cuando se establecen reglas, en el caso del ABB, que los mayores se insertan a la derecha y los menores a la izquierda, se facilita
	la busqueda dentro del mismo.

• Explicar cuál es el objetivo de tener una función de destrucción en el TDA y qué implicaría para el usuariono tenerla.

	El objetivo de tener una funcion de destruccion en el TDA es liberar la memoria almacenada por el mismo. Al reservar memoria, 
	esta queda para uso del programador y por lo tanto es el encargado de liberarla. Si el usuario no tuviera esta función, la 
	memoria reservada no sería liberada y le traeria problemas al momento de la ejecución.	
	
• ¿Cuál es la complejidad de las diferentes operaciones del ABB? Justifique.

	Tanto en el caso de insertar, buscar y eliminar la complejidad es O(n) ya que si pensamos en el peor caso posible, este sería
	cuando el árbol se degenera en lista. Entonces el tiempo de ejecución de las operaciones dependerían de la cantidad de objetos
	que se hayan insertado en el mismo.
