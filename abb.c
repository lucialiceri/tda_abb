#include "abb.h"
#include <stdio.h>

#define ERROR_MEMORIA "No se pudo reservar memoria"
/*
 *  PRE: Recibe como parametros un comparador de elementos y un destructor de los mismos.
 *  POST: Devuelve un arbol para cual se reservó la memoria necesaria de manera exitosa.
 */
abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
    abb_t* abb = calloc(1, sizeof(abb_t));
    if(!abb)
        return NULL;
    abb->comparador = comparador;
    abb->destructor = destructor;
    return abb;
}

/*
 *  PRE: Recibe como parametro un arbol, un nodo y el elemento a incertar. Esta función se llama solo si el arbol
 *       ya tiene nodo raiz. 
 *  POST: Devuelve el nodo insertado en el lugar correspondiente de manera recursiva. Para esto se reservó  la memoria 
 *        necesaria de manera exitosa.
 */
nodo_abb_t* arbol_insertar_elemento(abb_t* arbol, nodo_abb_t* nodo, void* elemento){
    if(!nodo){
        nodo_abb_t* nodo_aux = calloc(1, sizeof(nodo_abb_t));
        if(!nodo_aux){
            free(nodo_aux);
            printf("%s\n", ERROR_MEMORIA);
            return NULL;
        }
        nodo = nodo_aux;
        nodo->elemento = elemento;
        nodo->izquierda = NULL;
        nodo->derecha = NULL;
        return nodo;
    }
    if(arbol->comparador(elemento, nodo->elemento) >= 0){
        nodo->derecha = arbol_insertar_elemento(arbol, nodo->derecha, elemento); 
        return nodo;
    }
    else{
      nodo->izquierda = arbol_insertar_elemento(arbol, nodo->izquierda, elemento);
    }
    return nodo;
}
/*
 * PRE: Recibe el elemento a insertar y el arbol.   
 * POST: Devuelve 0 en caso de haberse podido insertar de manera exitosa, en el caso contrario devuelve -1.
 */
int arbol_insertar(abb_t* arbol, void* elemento){
    if(!arbol) return -1;
    if(!arbol->nodo_raiz){
        nodo_abb_t* nodo_aux = calloc(1, sizeof(nodo_abb_t));
        if(!nodo_aux){
            free(nodo_aux);
            printf("%s\n", ERROR_MEMORIA);
            return -1;
        }
        arbol->nodo_raiz = nodo_aux;
        arbol->nodo_raiz->elemento = elemento;
        arbol->nodo_raiz->izquierda = NULL;
        arbol->nodo_raiz->derecha = NULL;
        return 0;
    }
    arbol_insertar_elemento(arbol, arbol->nodo_raiz, elemento); // Inserto de maneera recursiva.
    return 0;
}
/*
 * PRE: Recibe por paramentros el arbol, el nodo por el cual se inicia la busqueda y el elemento a buscar.
 * POST: Recorre el arbol de manera recursiva segun los resultados del comparador.
 */
void* arbol_buscar_elemento(abb_t* arbol, nodo_abb_t* nodo, void* elemento){
	if(!nodo){
		return NULL;
	}
	if(arbol->comparador(nodo->elemento, elemento) == 0){
		return nodo->elemento;
	}
	if(arbol->comparador(nodo->elemento, elemento) > 0){
		return arbol_buscar_elemento(arbol, nodo->izquierda, elemento);
	}

	return arbol_buscar_elemento(arbol, nodo->derecha, elemento);
	
}
/*
 * PRE: Recibe un arbol y un elemento a encontrar.
 * POST: Luego de buscar de manera recursiva devuelve el elemento de ser encontrado, en el caso contrario devuelve NULL.
 */
void* arbol_buscar(abb_t* arbol, void* elemento){
	if(!arbol) return NULL;
	if(!arbol->nodo_raiz || !arbol->comparador) return NULL;

	return arbol_buscar_elemento(arbol, arbol->nodo_raiz, elemento);

}


/*nodo_abb_t* busco_al_nuevo_padre(nodo_abb_t* nodo, nodo_abb_t* nodo_aux){
    if(nodo->izquierda && (nodo->izquierda != nodo_aux)){
            nodo = nodo->izquierda;
        while(nodo->derecha && (nodo->derecha != nodo_aux)){
            nodo = nodo->derecha;
        }
    }
    return nodo;
}*/

nodo_abb_t* el_mayor_de_los_menores(nodo_abb_t* nodo){
    if(!nodo)
        return NULL;
    if(nodo->derecha)
        return el_mayor_de_los_menores(nodo->derecha);
    else{
        return nodo;
    }
}

nodo_abb_t* arbol_borrar_elemento(abb_t* arbol, nodo_abb_t* nodo, void* elemento){
    if(!nodo){
            return NULL;
        }

    if(arbol->comparador(elemento, nodo->elemento) == 0){  // Encontre mi elemento
        if(!nodo->izquierda && !nodo->derecha){     // Si no tiene hijos, lo borro y listo.
            if(arbol->destructor && nodo->elemento)    
                arbol->destructor(nodo->elemento);
            free(nodo);
            return NULL;
        }
        if(nodo->derecha && nodo->izquierda){   // Si tiene dos hijos, busco al mayor de los menores para que lo reemplace.
            nodo_abb_t* menor = el_mayor_de_los_menores(nodo->izquierda);
            if(arbol->destructor){
                arbol->destructor(nodo->elemento);
            }
            nodo->elemento = menor->elemento; // Reemplazo con el mayor de los menores. 
            menor->elemento = elemento; // Apunto al nuevo elemento con el mismo valor que el anterior.
            arbol_borrar_elemento(arbol, nodo->izquierda, elemento);
        }
        nodo_abb_t* nuevo_nodo = nodo->derecha? nodo->derecha : nodo->izquierda; // Si tiene un solo hijo o reemplazo por ese.
        if(arbol->destructor && nodo->elemento)
            arbol->destructor(nodo->elemento);
        free(nodo);
        return nuevo_nodo;
    }
    else if(arbol->comparador(elemento, nodo->elemento) > 0){    // Voy a la derecha
        nodo->derecha = arbol_borrar_elemento(arbol, nodo->derecha, elemento);
    }
    else{
        nodo->izquierda = arbol_borrar_elemento(arbol, nodo->izquierda, elemento);  // Voy a la izquierda
    }
    return nodo;   
}

/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación) y si lo encuentra lo quita del arbol.
 * Adicionalmente, si encuentra el elemento, invoca el destructor con
 * dicho elemento.
 * Devuelve 0 si pudo eliminar el elemento o -1 en caso contrario.
 */
int arbol_borrar(abb_t* arbol, void* elemento){
	if(!arbol) return -1;
	if(!arbol->nodo_raiz)
		return -1;
	
    if(arbol_buscar(arbol, elemento) == NULL){
        return -1;
    }
    arbol->nodo_raiz = arbol_borrar_elemento(arbol, arbol->nodo_raiz, elemento);

	return 0;
}

/*
 * PRE: Recibe un puntero a un arbol binario de busqueda.
 * POST: Devuelve el elemento situado en la raiz. En caso de no existir el arbol o de no existir la raiz se devuelve NULL.
 */
void* arbol_raiz(abb_t* arbol){
    if(!arbol) 
        return NULL;
    if(!arbol->nodo_raiz)
        return NULL;
    return arbol->nodo_raiz->elemento;
}

/*
 * PRE: Recibe un arbol de busqueda binario.
 * POST: Devuelve true si está vacío o el arbol no existe, false si el árbol tiene elementos.
 */
bool arbol_vacio(abb_t* arbol){
    if(!arbol || !arbol->nodo_raiz)
        return true;
    return false;
    
}

/*
 * PRE: Recibe un arbol, el nodo por el cual comienza el recorrido, el numero actual del contador, el array y su tamanio.
 * POST: Recorre primero la izquierda, luego la raiz y por ultimo va a la derecha mientras no se haya llenado el array ni
 *       terminado el arbol.
 */
size_t* recorrdio_inorden_recursivo(abb_t* arbol, nodo_abb_t* nodo, size_t* contador, void** array, size_t tamanio_array){

    if(tamanio_array > (*contador) && nodo){
        if(nodo->izquierda)
            recorrdio_inorden_recursivo(arbol, nodo->izquierda, contador, array, tamanio_array); 

        if(tamanio_array > (*contador)){
                array[(*contador)] = nodo->elemento;
                (*contador)++;
            }

        if(nodo->derecha)
            recorrdio_inorden_recursivo(arbol, nodo->derecha, contador, array, tamanio_array);
    }
    return contador;
}
/*
 * PRE: Se recibe por parametro un árbol, un puntero a un array de elementos y el tamaño del array.
 * POST: Devuelve el numero de elementos recorridos inorden y añadidos al array.
 */
size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
    if(!arbol || !arbol->nodo_raiz || tamanio_array == 0 || !array)
        return 0;
    size_t contador = 0;
    recorrdio_inorden_recursivo(arbol, arbol->nodo_raiz, &contador, array, tamanio_array);
    
    return contador;
}
/*
 * PRE: Recibe un arbol, el nodo por donde comienzo a recorrer, el numero actual del contador, un array y su tamaño.
 * POST: Luego de recorrer la raiz, luego la izquierda y por ultimo la derecha devuelve el numero de elementos recorridos y
 *       añadidos al array.
 */
size_t* recorrido_preorden_recursivo(abb_t* arbol, nodo_abb_t* nodo, size_t* contador, void** array, size_t tamanio_array){
    if(tamanio_array > (*contador) && nodo){
        array[(*contador)] = nodo->elemento;
        (*contador)++;

        if(nodo->izquierda)
            recorrido_preorden_recursivo(arbol, nodo->izquierda, contador, array, tamanio_array);

        if(nodo->derecha)
            recorrido_preorden_recursivo(arbol, nodo->derecha, contador, array, tamanio_array);
    }
    return contador;
}
/*
 * PRE: Recibe un arbol, un array y el tamanio del mismo.
 * POST: Devuelve la cantidad de elementos recorridos preorden y añadidos al array.
 */
size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
    if(!arbol || !array || tamanio_array == 0)
        return 0;

    size_t contador = 0;
    recorrido_preorden_recursivo(arbol, arbol->nodo_raiz, &contador, array, tamanio_array);

    return contador;
}
/*
 * PRE: Recibe por parametro un arbol, el nodo por el cual inicio el recorrido, el valor actual del contador, un array y su
 *      tamaño.
 * POST: Recorre de manera recursiva primero la derecha, luego la izquierda y por ultimo la raiz retornando la cantidad de
 *       elementos recorridos y añadidos al array.
 */
size_t* recorrido_postorden_recursivo(abb_t* arbol, nodo_abb_t* nodo, size_t* contador, void** array, size_t tamanio_array){
    if(tamanio_array > (*contador) && nodo){

        recorrido_postorden_recursivo(arbol, nodo->izquierda, contador, array, tamanio_array);

        recorrido_postorden_recursivo(arbol, nodo->derecha, contador, array, tamanio_array);

        if(tamanio_array > (*contador)){
            array[(*contador)] = nodo->elemento;
            (*contador)++;
        }
    }
    return contador;
}
/*
 * PRE: Recibe un arbol, un array y su tamaño.
 * POST: Devuelve la cantidad de elementos recorridos postorden y añadidos al array.
 */
size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
    if(!arbol || !array || tamanio_array == 0)
        return 0;

    size_t contador = 0;
    recorrido_postorden_recursivo(arbol, arbol->nodo_raiz, &contador, array, tamanio_array);

    return contador;
}

/*
 * Iterador interno. Recorre el arbol e invoca la funcion con cada
 * elemento del mismo. El puntero 'extra' se pasa como segundo
 * parámetro a la función. Si la función devuelve true, se finaliza el
 * recorrido aun si quedan elementos por recorrer. Si devuelve false
 * se sigue recorriendo mientras queden elementos.
 * El recorrido se realiza de acuerdo al recorrido solicitado.  Los
 * recorridos válidos son: ABB_RECORRER_INORDEN, ABB_RECORRER_PREORDEN
 * y ABB_RECORRER_POSTORDEN.
 * Devuelve la cantidad de elementos que fueron recorridos.
*/
size_t* inorden_con_cada_elemento(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra, size_t* cantidad){
    if(nodo){
        inorden_con_cada_elemento(nodo->izquierda, funcion, extra, cantidad); 
        
        if(funcion(nodo->elemento, extra)){
            (*cantidad)++;      
            inorden_con_cada_elemento(nodo->derecha, funcion, extra, cantidad); 
        }
    }
    return cantidad;
}
size_t* preorden_con_cada_elemento(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra, size_t* cantidad){
    if(nodo){
        bool terminar = funcion(nodo->elemento, extra);
        (*cantidad)++;

        if(terminar){
            preorden_con_cada_elemento(nodo->izquierda, funcion, extra, cantidad);
            preorden_con_cada_elemento(nodo->derecha, funcion, extra, cantidad);
        }
    }
    return cantidad;
}
size_t* postorden_con_cada_elemento(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra, size_t* cantidad){
    if(nodo){

        postorden_con_cada_elemento(nodo->izquierda, funcion, extra, cantidad);
        postorden_con_cada_elemento(nodo->derecha, funcion, extra, cantidad);

        bool terminar = funcion(nodo->elemento, extra);
        if(terminar){
            (*cantidad)++;
        }
        else{
            return cantidad;
        }
    }

    return cantidad;
}
size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
    if(!arbol || funcion == NULL || !arbol->nodo_raiz)
        return 0;
    
    size_t cantidad = 1; // Voy a recorrer por lo menos 1 elemento

    if(recorrido == ABB_RECORRER_INORDEN){
        inorden_con_cada_elemento(arbol->nodo_raiz, funcion, extra, &cantidad);
    }
    if(recorrido == ABB_RECORRER_PREORDEN){
        preorden_con_cada_elemento(arbol->nodo_raiz, funcion, extra, &cantidad);
    }
    if(recorrido == ABB_RECORRER_POSTORDEN){
        postorden_con_cada_elemento(arbol->nodo_raiz, funcion, extra, &cantidad);
    }


    return cantidad;
}
/*
 * PRE: Se liberal los nodos hojas de manera recursiva invocando al destructor en caso de existir.
 * POST: Se libera toda la memoria reservada para la estructura.
 */
void arbol_destruir_recursivo(abb_t* arbol, nodo_abb_t* nodo){
    if(nodo){
    
        arbol_destruir_recursivo(arbol, nodo->derecha);
    
        arbol_destruir_recursivo(arbol, nodo->izquierda);


    if(arbol->destructor && nodo->elemento)
        arbol->destructor(nodo->elemento);

    free(nodo);
    }

    return;
}
/*
 * PRE: Recibe un arbol de busqueda binario.
 * POST: Se invoca a la funcion destructiva recursiva y finalmente se libera la memoria reservada para el arbol.
 */
void arbol_destruir(abb_t* arbol){
    if(!arbol) 
        return; 

    arbol_destruir_recursivo(arbol, arbol->nodo_raiz);
    free(arbol);
}