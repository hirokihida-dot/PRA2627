#ifndef LIST_ARRAY_H
#define LIST_ARRAY_H

#include <ostream>
#include <stdexcept>
#include "List.h"

template <typename T> // Definimos la clase de datos T
class ListArray : public List<T> {

    private:
        // miembros privados
        T* arr; // Puntero al inicio del array que almacena los elemntos de la lista de forma contigua
        int max; // Tamanyo actual del array
        int n; // numero de elementos que contiene la lista
        static const int MINSIZE = 2; // tamanyo minimo del array, se tiene que inicializar a 2.

    public:
        // miembros públicos, incluidos los heredados de List<T>
		void insert (int pos, T e) override{
	        if (pos < 0 || pos > n)  // comprobamos si la posicion esta fuera del rango
                throw std::out_of_range("Posicion fuera de rango"); // lanzamos la excepcion fuera de rango
            if (n == max) // comprobamos si hemos llegado al maximo de tamanyo del vector
                resize (max*2); // hacemos resize del tamanyo si fuera necesario
            for (int i = n; i > pos; i--) // recorremos el bucle de atras a adelante
                arr[i] = arr[i-1]; // movemos el elemento que tenemos detras a esta posicion
            arr[pos] = e; // insertamos elemento e en posicion pos
            n++; // aumentamos en uno el tamanyo
	    }
	    
        	void append(T e) override{
            insert(n, e);   // insertamos el elemento e en la ultima posicion del array
        }
        
		void prepend(T e) override{
	        insert(0, e); // insertamos el elemento e en la primera posicion del array
	    }
	    
		T remove (int pos) override{
	        if (pos < 0 || pos >= n)  // comprobamos si la posicion esta fuera del rango
                throw std::out_of_range("Posicion fuera de rango"); // lanzamos la excepcion fuera de rango
            T element = arr[pos]; // guardamos el elemento en pos para luego hacer el return
            for (int i = pos; i < n-1; i++) // recorremos el vector hacia adelante, desde pos hasta el penultimo elemento 
                arr[i] = arr[i+1]; // reemplazamos el elemento en la posicion actual por el siguiente
            n--; // reducimos la cantidad de elementos en el vector
            if (n <  max/2 && max/2 >= MINSIZE ) // comprobamos si sobra tamanyo
                resize (max/2); // reajustamos el tamanyo
            return element;
	    
	    }
	    
		T get (int pos) override{
	        if (pos < 0 || pos >= n)  // comprobamos si la posicion esta fuera del rango
                throw std::out_of_range("Posicion fuera de rango"); // lanzamos la excepcion fuera de rango
            return arr[pos]; // devuelve el elemento en las posicion pos
	    }
	        
		int search(T e) override{
            for (int i = 0; i < n; i++) // recorre todo el vector
	            if (arr[i] == e) // comprueba si el elemento actual corresponde con el elemento e
	                return i; // devuelve la posicion donde esta el elemento e
	        return -1; // devuelve un -1 si no encuentr anada
    	}
		
		bool empty() override{
	        return n == 0; // devuelve true si esta vacia y false si hay algun elemento
	    }
	
		int size() override{
	        return n; // devuelve la cantidad de elementos de la lista
	    }
	    
			        
        ListArray(){
            arr = new T[MINSIZE];  // reservamos memoria
            max = MINSIZE;  // definimos el tamanyo maximo como el tamanyo minio
            n = 0; // inciailizamos la cantidad de elementos del array a 0
        }
        
        ~ListArray() override{
            delete[] arr; // liberamos memoria 
        }
        
        T operator[](int pos){
            return get(pos); // devuelve el elemento en la posicion pos
        }
        
        friend std::ostream& operator<<(std::ostream &out, ListArray<T> &list){
            out << "["; // imprimimos el corchete de apertura
            for (int i = 0; i < list.n; i++)
                out << list.arr[i] << ",";  // imprime todos los elementos del array
            out << "]"; // imprimimos el corchete de cierre
            return out; // devuelve el flujo de salida
        }
        
        void resize(int new_size){
            T* new_arr = new T[new_size]; // Creamos un nuevo array dinamico de new_size elementos

            int elements_to_copy = (n < new_size ? n : new_size); // creamos una nueva variable y comparamos el valor de n con el nuevo valor, para ver si en el bucle usamos n o new_size
            for (int i = 0; i < elements_to_copy; i++) // Copiamos los elementos del array antiguo al nuevo
                new_arr[i] = arr[i];
            delete[] arr; // Liberamos espacio de memoria del array antiguo
            arr = new_arr; // hacemos que arr apunte al nuevo array
            max = new_size; // actualizamos el tamanyo maximo 
             
        }
};

#endif
