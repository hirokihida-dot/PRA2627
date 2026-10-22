// Programa que resuelve el problema de la mochila por programaciń dinámica.

#include <iostream>
#include <vector>
#include <algorithm>

int mochila(const std::vector<int>& pesos, const std::vector<int>& beneficios, int capacidad, std::vector<int>& solucion){
    size_t n = pesos.size(); // Número de elementos
    solucion.assign(n, 0); // Inicializamos el vector de soluciones con ceros
    if (n == 0 || capacidad <= 0) 
        return 0; // Si no hay elementos o la capacidad es nula o negativa, retornamos 0

    std::vector<std::vector<int>> T(n + 1, std::vector<int>(capacidad + 1, 0)); // Matriz de programación dinámica

    for (int i=1; i <=n; i++){
        int peso = pesos[i-1]; // Peso del elemento actual
        int beneficio = beneficios[i-1]; // Beneficio del elemento actual
        for (int j=0; j <= capacidad; j++){
            if (peso > j)
                T[i][j] = T[i-1][j]; // No podemos incluir el elemento actual
            else
                T[i][j] = std::max(T[i-1][j], beneficio + T[i-1][j-peso]); // Tomamos el máximo entre incluir o no el elemento actual
        }
    }
    // Recuperamos la solución a partir de la matriz T
    int j = capacidad;  
    for (int i = n; i >= 1; i--){
        if (T[i][j] != T[i-1][j]){ // Si el elemento j se incluyó
            solucion[i-1] = 1; // Marcamos el elemento j como incluido
            j -= pesos[i-1]; // Reducimos la capacidad restante
        }
    }
    return T[n][capacidad]; // Devolvemos el beneficio máximo
}

void prueba(const std::vector<int>& pesos, const std::vector<int>& beneficios, int capacidad)
{
    std::vector<int> solucion;
    int beneficio = mochila(pesos, beneficios, capacidad, solucion);
 
    std::cout << "M = " << capacidad << "\n";
    std::cout << "Elementos elegidos:";
    for (size_t k = 0; k < solucion.size(); k++)
        if (solucion[k] == 1) std::cout << " " << k;
    std::cout << "\nVector s: ";
    for (int x : solucion) std::cout << x << " ";
    std::cout << "\nBeneficio maximo: " << beneficio << "\n\n";
}

int main(){
        // Ejemplo de las diapositivas: elegir 0 y 1, beneficio 78
    prueba({9, 6, 5}, {38, 40, 24}, 15);
 
    // Segundo ejemplo: elegir 1 y 2, beneficio 35
    prueba({1, 3, 2, 4}, {10, 20, 15, 20}, 5);

}