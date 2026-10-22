// Programa que resuelve el problema de la devolución de monedas utilizando programación dinámica.
#include <limits>
#include <iostream>
#include <vector>
#include <algorithm>

// inicializamos las variables globales necesarias
int inf_val = std::numeric_limits<int>::max(); // Valor infinito para inicializar la matriz



int devolverMoneda (const std::vector<int>& m, int cantidad, std::vector<int>& s){
    int n = static_cast<int>(m.size()); // Número de tipos de monedas
    s.assign(n, 0); // Inicializamos el vector de soluciones con ceros
    if (n == 0 || cantidad < 0) 
        return -1; // Si no hay monedas o la cantidad es negativa, retornamos -1
    std::vector<std::vector<int>> T(n, std::vector<int>(cantidad + 1, inf_val)); // Matriz de programación dinámica

    T[0][0] = 0; // Inicializamos el elemento en la primera fila y columna de la matriz
    for (int j = 1; j <= cantidad; j++) { // Rellenamos la primera fila de la matriz
        if (j >= m[0] && T[0][j - m[0]] != inf_val) { 
            T[0][j] = 1 + T[0][j - m[0]]; // Si podemos usar la primera moneda, actualizamos el valor en la matriz
        }
    }
    
    for (int i = 1; i < n; i++) { // Rellenamos el resto de la matriz
        T[i][0] = 0; // Inicializamos la primera columna de cada fila con cero
        for (int j = 1; j <= cantidad; j++) {
            if (j < m[i] || T[i][j - m[i]] == inf_val) { // Si no podemos usar la moneda o no hay solución para la cantidad restante
                T[i][j] = T[i - 1][j]; // Copiamos el valor de la fila anterior
            } else if (T[i-1][j] != inf_val) { // Si podemos usar la moneda y hay solución para la cantidad restante
                T[i][j] = std::min(T[i - 1][j], 1 + T[i][j - m[i]]); // Tomamos el mínimo entre no usar la moneda y usarla
            } else {
                T[i][j] = 1 + T[i][j - m[i]]; // Usamos la moneda y actualizamos el valor en la matriz
            }
        }
    }

    if (T[n-1][cantidad] == inf_val)
        return -1; // Si no hay solución, devolvemos -1
    // recuperamos la solucion a partir de la matriz T

    int i = n - 1;
    int j = cantidad;
    while (j != 0){
        if (i ==0 || T[i][j] != T[i-1][j]){ // Si la moneda i se usó
            s[i]++; // Incrementamos el contador de la moneda i
            j -= m[i]; // Reducimos la cantidad restante
        } else {
            i--; // Pasamos a la moneda anterior
        }
    }
    return T[n-1][cantidad]; // Devolvemos el número mínimo de monedas necesarias
}

int main (){
    std::vector<int> monedas = {1, 5, 10, 25}; // Tipos de monedas disponibles
    int cantidad = 63; // Cantidad a devolver
    std::vector<int> solucion; // Vector para almacenar la solución
    int resultado = devolverMoneda(monedas, cantidad, solucion); // Llamamos a la función para devolver monedas
    if (resultado == -1) {
        std::cout << "No es posible devolver" << cantidad << "con las monedas disponibles." << std::endl; // Si no hay solución, mostramos un mensaje
        return 0; // Salimos del programa
    }

    std::cout << "Cantidad a devolver: " << cantidad << std::endl; // Mostramos la cantidad a devolver 
    std::cout << "Número mínimo de monedas necesarias: " << resultado << std::endl; // Mostramos el número mínimo de monedas necesarias
    for (size_t i = 0; i < monedas.size(); i++) { // Mostramos la cantidad de cada tipo de moneda utilizada
        if (solucion[i] > 0) {
            std::cout << "Moneda de " << monedas[i] << ": " << solucion[i] << std::endl; // Mostramos la cantidad de cada tipo de moneda utilizada
        }
    }
    return 0; // Salimos del programa
}
