#include "pa2mm.h"
#include "abb.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct Palomas{
	int peso;
	int plumas;	
}paloma_t;

int comparador_palomas_peso(void* paloma_1, void* paloma_2){
    if(((paloma_t*)paloma_1)->peso > ((paloma_t*)paloma_2)->peso)
        return 1;
    if(((paloma_t*)paloma_1)->peso < ((paloma_t*)paloma_2)->peso)
        return  -1;
    return 0;
}

void destructor(void* elemento){
	return;
}
void probar_crear_abb(){

	abb_t* arbol = arbol_crear(comparador_palomas_peso, destructor);
	pa2m_afirmar(arbol != NULL, "Puedo crear un arbol.");
	pa2m_afirmar(arbol_vacio(arbol), "Se crea vacio");
	pa2m_afirmar(arbol->nodo_raiz == NULL, "El nodo raiz se crea apuntando a NULL.");
	arbol_destruir(arbol);
}
void probar_insertar_abb(){
	paloma_t una_paloma = {10, 15};
	paloma_t otra_paloma = {12, 10};
	paloma_t palomita = {5, 3};
	paloma_t palomota = {20, 50};

	abb_t* abb = arbol_crear(comparador_palomas_peso, destructor);
	arbol_insertar(abb, &una_paloma);
	arbol_insertar(abb, &otra_paloma);
	arbol_insertar(abb, &palomita);
	arbol_insertar(abb, &palomota);

	pa2m_afirmar(&una_paloma == arbol_raiz(abb), "La primer paloma se inserta en el nodo raiz.");
	pa2m_afirmar(&otra_paloma == abb->nodo_raiz->derecha->elemento, "Se inserta una segunda paloma mayor a la derecha.");
	pa2m_afirmar(&palomita == abb->nodo_raiz->izquierda->elemento, "Se inserta una tercer paloma menor a la izquierda.");
	arbol_destruir(abb);
}

void probar_buscar_abb(){
	paloma_t una_paloma = {10, 15};
	paloma_t otra_paloma = {12, 10};
	paloma_t palomita = {5, 3};
	paloma_t palomota = {20, 50};

	paloma_t paloma_buscada = {5, 5};
	paloma_t otra_paloma_buscada = {12, 5};
	paloma_t paloma_no_existe = {100, 5};

	abb_t* abb = arbol_crear(comparador_palomas_peso, destructor);
	arbol_insertar(abb, &una_paloma);
	arbol_insertar(abb, &otra_paloma);
	arbol_insertar(abb, &palomita);
	arbol_insertar(abb, &palomota);

	pa2m_afirmar(arbol_buscar(abb, &paloma_buscada) == &palomita, "Encontré a la paloma que buscaba.");
	pa2m_afirmar(arbol_buscar(abb, &otra_paloma_buscada) == &otra_paloma, "Encontré a la paloma que buscaba.");
	pa2m_afirmar(arbol_buscar(abb, &paloma_no_existe) == NULL, "Puedo buscar una paloma que no este en mi arbol.");
	arbol_destruir(abb);
}

void probar_borrar_abb(){
    paloma_t una_paloma = {15, 15};
	paloma_t otra_paloma = {12, 10};
	paloma_t palomita = {5, 3};
	paloma_t palomota = {20, 50};
	paloma_t paloma1 = {3, 4};
	paloma_t paloma2 = {14, 5};
	paloma_t paloma3 = {4, 5};
	paloma_t paloma4 = {6, 5};
	paloma_t paloma5 = {30, 5};
	paloma_t paloma13 = {13, 5};
	paloma_t paloma45 = {45, 5};
	paloma_t paloma25 = {25, 5};
	paloma_t paloma11 = {11, 5};

	abb_t* abb = arbol_crear(comparador_palomas_peso, destructor);
	arbol_insertar(abb, &una_paloma);
	arbol_insertar(abb, &otra_paloma);
	arbol_insertar(abb, &palomita);
	arbol_insertar(abb, &palomota);
	arbol_insertar(abb, &paloma1);
	arbol_insertar(abb, &paloma2);
	arbol_insertar(abb, &paloma3);
	arbol_insertar(abb, &paloma4);
	arbol_insertar(abb, &paloma5);
	arbol_insertar(abb, &paloma13);
	arbol_insertar(abb, &paloma45);
	arbol_insertar(abb, &paloma25);

	paloma_t paloma_buscada = {12, 5};
	paloma_t paloma_buscada3 = {3, 5};
	paloma_t paloma_buscada4 = {4, 5};
	paloma_t paloma_buscada15 = {15, 5};
	paloma_t paloma_buscada5 = {5, 5};
	paloma_t paloma_buscada14 = {14, 5};
	paloma_t paloma_buscada6 = {6, 5};
	paloma_t paloma_buscada20 = {20, 6};
	paloma_t paloma_buscada30 = {30, 5};
	paloma_t paloma_buscada13 = {13, 9};
	paloma_t paloma_buscada11 = {11, 5};
	paloma_t paloma_buscada45 = {45, 5};
	paloma_t paloma_buscada25 = {25, 5};
	paloma_t paloma_no_existe = {100, 40};

	pa2m_afirmar(arbol_borrar(abb, &paloma_no_existe) == -1, "Borrar un elemento que no existe devuelve error");
	arbol_borrar(abb, &paloma_buscada20);
	pa2m_afirmar(arbol_buscar(abb, &paloma_buscada20) == NULL, "Puedo borrar un nodo con un hijo no hoja");
	arbol_borrar(abb, &paloma_buscada);
	pa2m_afirmar(arbol_buscar(abb, &paloma_buscada) == NULL, "Puedo borrar una paloma con dos hijos");

	arbol_borrar(abb, &paloma_buscada3);
	pa2m_afirmar(arbol_buscar(abb, &paloma_buscada3) == NULL, "Puedo borrar una paloma con 1 hijo.");

	arbol_borrar(abb, &paloma_buscada4);
	pa2m_afirmar(arbol_buscar(abb, &paloma_buscada4) == NULL, "Puedo borrar una paloma con sin hijos.");

	arbol_insertar(abb, &paloma11);	
	arbol_borrar(abb, &paloma_buscada15);
	pa2m_afirmar(arbol_buscar(abb, &paloma_buscada15) == NULL, "Puedo borrar la paloma raiz.");
	pa2m_afirmar(abb->nodo_raiz->elemento == &paloma2, "Me queda el elemento correcto en la raiz");

	arbol_borrar(abb, &paloma_buscada13);
	pa2m_afirmar(arbol_buscar(abb, &paloma_buscada13) == NULL, "Puedo borrar una paloma no hoja con un hijo");

	arbol_borrar(abb, &paloma_buscada5);
	arbol_borrar(abb, &paloma_buscada14);
	arbol_borrar(abb, &paloma_buscada6);
	arbol_borrar(abb, &paloma_buscada25);
	arbol_borrar(abb, &paloma_buscada45);

	pa2m_afirmar(abb->nodo_raiz->elemento == &paloma11, "Me queda el elemento correcto en la raiz");
	pa2m_afirmar(abb->nodo_raiz->izquierda == NULL, "Nodo raiz queda sin hijo izquierdo");

	
	arbol_borrar(abb, &paloma_buscada11);
	pa2m_afirmar(abb->nodo_raiz->derecha == NULL, "Nodo raiz queda sin hijo derecho");

	arbol_borrar(abb, &paloma_buscada30);

	pa2m_afirmar(arbol_vacio(abb), "Puedo borrar el arbol entero");
	arbol_destruir(abb);

}

void probar_borrar_raiz(){
	paloma_t una_paloma = {15, 15};
	paloma_t otra_paloma = {12, 10};
	paloma_t palomita = {5, 3};
	paloma_t palomota = {20, 50};
	paloma_t paloma1 = {3, 4};
	paloma_t paloma2 = {14, 5};
	paloma_t paloma3 = {4, 5};
	paloma_t paloma4 = {6, 5};
	paloma_t paloma5 = {30, 5};
	paloma_t paloma13 = {13, 5};
	paloma_t paloma45 = {45, 5};
	paloma_t paloma25 = {25, 5};
	//paloma_t paloma11 = {11, 5};

	abb_t* abb = arbol_crear(comparador_palomas_peso, destructor);
	arbol_insertar(abb, &una_paloma);
	arbol_insertar(abb, &otra_paloma);
	arbol_insertar(abb, &palomita);
	arbol_insertar(abb, &palomota);
	arbol_insertar(abb, &paloma1);
	arbol_insertar(abb, &paloma2);
	arbol_insertar(abb, &paloma3);
	arbol_insertar(abb, &paloma4);
	arbol_insertar(abb, &paloma5);
	arbol_insertar(abb, &paloma13);
	arbol_insertar(abb, &paloma45);
	arbol_insertar(abb, &paloma25);


	arbol_borrar(abb, abb->nodo_raiz->elemento);
	pa2m_afirmar(arbol_raiz(abb) != &una_paloma, "Puedo borrar la raiz");

	arbol_borrar(abb, abb->nodo_raiz->elemento);
	pa2m_afirmar(arbol_raiz(abb) != &paloma2, "Puedo borrar la raiz");

	//arbol_borrar(abb, abb->nodo_raiz->elemento);
	pa2m_afirmar(arbol_raiz(abb) != &paloma13, "Puedo borrar la raiz");

	arbol_destruir(abb);
}

void probar_inorden(){
	paloma_t una_paloma = {15, 15};
	paloma_t otra_paloma = {12, 10};
	paloma_t palomita = {5, 3};
	paloma_t palomota = {35, 50};
	paloma_t paloma1 = {3, 4};
	paloma_t paloma2 = {14, 5};
	paloma_t paloma3 = {20, 5};
	paloma_t paloma4 = {40, 5};
	
	abb_t* abb = arbol_crear(comparador_palomas_peso, destructor);
	pa2m_afirmar(arbol_recorrido_inorden(abb, NULL, 0) == 0, "Un arbol vacio devuelve 0")

	arbol_insertar(abb, &una_paloma);
	arbol_insertar(abb, &otra_paloma);
	arbol_insertar(abb, &palomita);
	arbol_insertar(abb, &palomota);
	arbol_insertar(abb, &paloma1);
	arbol_insertar(abb, &paloma2);
	arbol_insertar(abb, &paloma3);
	arbol_insertar(abb, &paloma4);


	paloma_t* casita[4];

	pa2m_afirmar(arbol_recorrido_inorden(abb, (void*)(&casita), 4) == 4, "Devuelve la cantidad correcta de elementos.");
	pa2m_afirmar(casita[0] == &paloma1, "El primer elemento de es correcto.");
	pa2m_afirmar(casita[1] == &palomita, "El segundo elemento de es correcto.");
	pa2m_afirmar(casita[3] == &paloma2, "El último elemento de es correcto.");

	paloma_t* bosque[20];
	pa2m_afirmar(arbol_recorrido_inorden(abb, (void*)(&bosque), 20) == 8, "Devuelve la cantidad correcta de elementos.");
	pa2m_afirmar(bosque[7] == &paloma4, "El último elemento es el correcto.");
	arbol_destruir(abb);
}

void porbar_preorden(){
	paloma_t una_paloma = {15, 15};
	paloma_t otra_paloma = {12, 10};
	paloma_t palomita = {5, 3};
	paloma_t palomota = {35, 50};
	paloma_t paloma1 = {3, 4};
	paloma_t paloma2 = {14, 5};
	paloma_t paloma3 = {20, 5};
	paloma_t paloma4 = {40, 5};
	
	abb_t* abb = arbol_crear(comparador_palomas_peso, destructor);
	pa2m_afirmar(arbol_recorrido_preorden(abb, NULL, 0) == 0, "Un arbol vacio devuelve 0.")

	arbol_insertar(abb, &una_paloma);
	arbol_insertar(abb, &otra_paloma);
	arbol_insertar(abb, &palomita);
	arbol_insertar(abb, &palomota);
	arbol_insertar(abb, &paloma1);
	arbol_insertar(abb, &paloma2);
	arbol_insertar(abb, &paloma3);
	arbol_insertar(abb, &paloma4);

	paloma_t* casita[4];

	pa2m_afirmar(arbol_recorrido_preorden(abb, (void*)(&casita), 4) == 4, "Devuelve la cantidad correcta de elementos.");
	pa2m_afirmar(casita[0] == &una_paloma, "El primer elemento de es correcto y es la raiz.");
	pa2m_afirmar(casita[1] == &otra_paloma, "El segundo elemento de es correcto.");
	pa2m_afirmar(casita[3] == &paloma1, "El último elemento de es correcto.");

	paloma_t* bosque[20];
	pa2m_afirmar(arbol_recorrido_preorden(abb, (void*)(&bosque), 20) == 8, "Devuelve la cantidad correcta de elementos.");
	pa2m_afirmar(bosque[7] == &paloma4, "El último elemento es el correcto.");

	arbol_destruir(abb);
}

void porbar_prostrden(){
	paloma_t una_paloma = {15, 15};
	paloma_t otra_paloma = {12, 10};
	paloma_t palomita = {5, 3};
	paloma_t palomota = {35, 50};
	paloma_t paloma1 = {3, 4};
	paloma_t paloma2 = {14, 5};
	paloma_t paloma3 = {20, 5};
	paloma_t paloma4 = {40, 5};
	
	abb_t* abb = arbol_crear(comparador_palomas_peso, destructor);
	pa2m_afirmar(arbol_recorrido_postorden(abb, NULL, 0) == 0, "Un arbol vacio devuelve 0.")

	arbol_insertar(abb, &una_paloma);
	arbol_insertar(abb, &otra_paloma);
	arbol_insertar(abb, &palomita);
	arbol_insertar(abb, &palomota);
	arbol_insertar(abb, &paloma1);
	arbol_insertar(abb, &paloma2);
	arbol_insertar(abb, &paloma3);
	arbol_insertar(abb, &paloma4);

	paloma_t* casita[4];
	size_t cantidad = arbol_recorrido_postorden(abb, (void*)(&casita), 4);

	pa2m_afirmar(cantidad == 4, "Devuelve la cantidad correcta de elementos.");
	pa2m_afirmar(casita[0] == &paloma1, "El primer elemento de es correcto y es la raiz.");
	pa2m_afirmar(casita[1] == &palomita, "El segundo elemento de es correcto.");
	pa2m_afirmar(casita[3] == &otra_paloma, "El último elemento de es correcto.");

	paloma_t* bosque[20];
	pa2m_afirmar(arbol_recorrido_postorden(abb, (void*)(&bosque), 20) == 8, "Devuelve la cantidad correcta de elementos.");
	pa2m_afirmar(bosque[7] == &una_paloma, "El último elemento es el correcto.");


	arbol_destruir(abb);
}
/* Recorre hasta encontrar una paloma mas peluda que la pretendida.
*/
bool es_mas_peluda(void* recibida, void* pretendida){
	if(((paloma_t*)recibida)->plumas < ((paloma_t*)pretendida)->plumas)
		return true;

	return false;
}
void porbar_iterador(){
	paloma_t una_paloma = {15, 15};
	paloma_t otra_paloma = {12, 7};
	paloma_t palomita = {5, 3};
	paloma_t palomota = {35, 50};
	paloma_t paloma1 = {3, 4};
	paloma_t paloma2 = {14, 10};
	paloma_t paloma3 = {20, 32};
	paloma_t paloma4 = {40, 17};
	
	abb_t* abb = arbol_crear(comparador_palomas_peso, destructor);
	pa2m_afirmar(abb_con_cada_elemento(abb, ABB_RECORRER_INORDEN, es_mas_peluda, NULL) == 0, "Un arbol vacio devuelve 0.")

	arbol_insertar(abb, &una_paloma);
	arbol_insertar(abb, &otra_paloma);
	arbol_insertar(abb, &palomita);
	arbol_insertar(abb, &palomota);
	arbol_insertar(abb, &paloma1);
	arbol_insertar(abb, &paloma2);
	arbol_insertar(abb, &paloma3);
	arbol_insertar(abb, &paloma4);

	paloma_t paloma_buscada = {12, 48};
	paloma_t paloma_buscada1 = {3, 5};
	//paloma_t paloma_buscada2 = {4, 5};
	//paloma_t paloma_buscada3 = {15, 5};

	size_t total_inorden = abb_con_cada_elemento(abb, ABB_RECORRER_INORDEN, es_mas_peluda, &paloma_buscada);
	pa2m_afirmar(total_inorden == 7, "Recorri la cantidad correcta de elementos inorden.");

	size_t total_inorden1 = abb_con_cada_elemento(abb, ABB_RECORRER_INORDEN, es_mas_peluda, &paloma_buscada1);
	pa2m_afirmar(total_inorden1 == 3, "Recorri la cantidad correcta de elementos inorden.");

	size_t total_preorden = abb_con_cada_elemento(abb, ABB_RECORRER_PREORDEN, es_mas_peluda, &paloma_buscada);
	pa2m_afirmar(total_preorden == 7, "Recorri la cantidad correcta de elementos preorden.");

	size_t total_preorden1 = abb_con_cada_elemento(abb, ABB_RECORRER_PREORDEN, es_mas_peluda, &paloma_buscada1);
	pa2m_afirmar(total_preorden1 == 2, "Recorri la cantidad correcta de elementos preorden.");

	size_t total_postorden = abb_con_cada_elemento(abb, ABB_RECORRER_POSTORDEN, es_mas_peluda, &paloma_buscada);
	pa2m_afirmar(total_postorden == 8, "Recorri la cantidad correcta de elementos postorden.");

	arbol_destruir(abb);
}

int main(){
	pa2m_nuevo_grupo("CREAR ARBOL");
	probar_crear_abb();

	pa2m_nuevo_grupo("INSERTAR EN EL ARBOL");
	probar_insertar_abb();

	pa2m_nuevo_grupo("BUSCAR EN EL ARBOL");
	probar_buscar_abb();

	pa2m_nuevo_grupo("BORRAR ELEMENTO");
	probar_borrar_abb();

	pa2m_nuevo_grupo("BORRAR RAIZ");
	//probar_borrar_raiz();

	pa2m_nuevo_grupo("RECORRER INORDEN");
	probar_inorden();

	pa2m_nuevo_grupo("RECORRER PREORDEN");
	porbar_preorden();

	pa2m_nuevo_grupo("RECORRER POSTORDEN");
	porbar_prostrden();

	pa2m_nuevo_grupo("ITERADOR INTERNO");
	porbar_iterador();

	return 0;
}