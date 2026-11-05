#ifndef NODE_H
#define NODE_H

#include <ostream>

template <typename T> 
class Node {
    public:
        // miembros públicos
    	// Atributos publicos
    	T data; // elemento almacenado de tipo T
    	Node <T>* next; // Puntero al siguiente nodo

    	// Metodos publicos
    	Node(T data, Node<T>* next=nullptr){ // metodo constructor, crea nodo con un dato de tipo T, y un puntero apuntando a nullptr si no se indica nada
			this->data = data; // coloca el dato de tipo T data, dentro del nodo
			this->next = next; // el puntero marca a la posicion del siguiente, que es nullptr si no hay.
		}
    
    	friend std::ostream& operator<<(std::ostream &out, const Node<T> &node){ // sobrecarga del operador << para imprimir una instancia de Node<T>
			out << node.data; // imprime el dato del nodo
			return out; // devuelve el flujo de salida
		}
};

#endif
