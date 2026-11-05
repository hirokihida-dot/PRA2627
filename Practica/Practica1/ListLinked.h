#ifndef LIST_LINKED_H
#define LIST_LINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

    private:
 
        // Atributos privados

        Node<T>* first; // puntero al primer nodo de la secuencia enlazada
        int n; // numero de elementos de la lista

        // devuelve el nodo en la posicion pos (pos debe ser valida)
        Node<T>* getNode(int pos){
            Node<T>* curr = first;
            for (int i = 0; i < pos; i++)
                curr = curr->next;
            return curr;
        }

    public:

        // metodos publicos heredados de List.h
		void insert (int pos, T e) override{
            if (pos < 0 || pos > n) // comprobamos si la posicion esta fuera del rango
                throw std::out_of_range("Posicion fuera de rango"); // lanzamos la excepcion fuera de rango 
            if (pos == 0){ // si la posicion es 0, insertamos al principio
                first = new Node<T>(e, first); // creamos un nuevo nodo con el elemento e y apuntando al primer nodo
            } else { // si la posicion es mayor que 0, insertamos en medio 
                Node<T>* prev = getNode(pos-1); // obtenemos el nodo anterior a la posicion donde queremos insertar
                prev->next = new Node<T>(e, prev->next); // creamos un nuevo nodo con el elemento e y apuntando al siguiente nodo del anterior
            }
            n++; // aumentamos el numero de elementos en la lista
        }

		void append(T e) override{
            insert(n, e); // insertamos el elemento e al final de la lista
        }

		void prepend(T e) override{
            insert(0, e); // insertamos el elemento e al principio de la lista
        }

		T remove (int pos) override{
            if (pos < 0 || pos >= n) // comprobamos si la posicion esta fuera del rango
                throw std::out_of_range("Posicion fuera de rango"); // lanzamos la excepcion fuera de rango 
            Node<T>* to_delete; // puntero al nodo que vamos a eliminar
            T element; // elemento que vamos a devolver
            if (pos == 0){ // si la posicion es 0, eliminamos el primer nodo
                to_delete = first; // apuntamos al primer nodo
                first = first->next; // movemos el puntero first al siguiente nodo
            } else { // si la posicion es mayor que 0, eliminamos un nodo en medio
                Node<T>* prev = getNode(pos-1); // obtenemos el nodo anterior al que queremos eliminar
                to_delete = prev->next; // apuntamos al nodo que vamos a eliminar
                prev->next = to_delete->next; // enlazamos el nodo anterior con el siguiente del nodo a eliminar
            }
            element = to_delete->data; // guardamos el elemento del nodo a eliminar
            delete to_delete; // eliminamos el nodo
            n--; // disminuimos el numero de elementos en la lista
            return element; // devolvemos el elemento eliminado
        }

		T get (int pos) override{
            if (pos < 0 || pos >= n) // comprobamos si la posicion estña fuera de rango
                throw std::out_of_range("Posicion fuera de rango"); // lanzamos la excepcion fuera de rango
            return getNode(pos)->data; // devolvemos el dato del nodo en la posicion pos
        }

		int search(T e) override{
            Node<T>* curr = first; // puntero auxiliar para recorrer la lista
            int index = 0; // indice del nodo actual
            while (curr != nullptr){ // mientras no lleguemos al final de la lista
                if (curr->data == e) // si encontramos el elemento e
                    return index; // devolvemos el indice del nodo donde se encuentra e
                index++; // aumentamos el indice
                curr = curr->next; // movemos el puntero al siguiente nodo
            }
            return -1; // devolvemos -1 si no encontramos el elemento e
           
        }

    	bool empty() override{
            return n == 0; // devolvemos true si la lista esta vacia, false en caso contrario
        }

		int size() override{
            return n; // devolvemos el numero de elementos en la lista
        }

		 

        // metodos publicos propios
        ListLinked(){
            first =  nullptr; // el primero es un nodo vacio
            n = 0;  // la cantidad de nodos es 0
        };

        ~ListLinked() override{
            while(first != nullptr){ // bucle para repetir mientras el primer nodo no este vacio
                Node<T>* aux = first->next; // generamos un puntero auxiliar apuntando a donde apunta first
                delete first; // eliminamos first
                first = aux; // first se convierte a donde apunta aux
            }
            n = 0; // la cantidad de nodos es 0        
        };

        T operator[](int pos){
            return get(pos); // llamamos al metodo get para obtener el elemento en la posicion pos
        };

        friend std::ostream& operator<<(std::ostream &out, ListLinked &list){
            Node<T>* aux = list.first; // creamos un puntero auxiliar apuntando al primer nodo de la lista
            out << "["; // imprimimos el corchete de apertura

            while (aux != nullptr){ // bucle para recorrer la lista mientras aux no sea un nodo vacio
                out << aux->data; // imprimimos el dato del nodo donde apunta aux
                if (aux->next != nullptr) // solo ponemos coma si hay un nodo siguiente
                    out << ",";
                aux = aux->next; // movemos aux al siguiente nodo de la lista
            }
            
            out << "]"; // imprimimos el corchete de cierre

            return out; // devolvemos el flujo de salida
            
        };
    

        
};

#endif // LIST_LINKED_H
