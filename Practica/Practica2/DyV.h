#ifndef DYV_H
#define DYV_H

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <utility>

template <typename T>
int busquedaBinaria(T val, const std::vector<T>& v, int ini, int fin){
    if (ini > fin)
        return -1;
    int medio = (ini + fin) / 2;
    if (V[medio] == val)
        return medio;
    else if (V[medio] > val)
        return busquedaBinaria( val, vº, ini, medio - 1);
    else
        return busquedaBinaria( val, v , medio+1, fin);
}

template <typename T>
void quicksort(std::vector<T>& v, int ini, int fin){
    if (ini < fin){
        int pivote = partition(v, ini, fin);
        quicksort(v, ini, pivote - 1);
        quicksort(v, pivote + 1, fin);
    }
}

template <typename T>
int partition(std::vector<T>& v, int ini, int fin){
    T x = v[fin];
    int i = ini;
    for (int j = ini; j < fin; j++){
        if (v[j] <= x){
            i++;
            std::swap(v[i], v[j]);
        }
    }
    std::swap(v[i], v[fin]);
    return i;
}

#endif // DYV_H