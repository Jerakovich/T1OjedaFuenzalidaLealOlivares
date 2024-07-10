#include "../Headers/gCoding.h"

// Funcion para calcular el Gap-Coding de un arreglo
vector<int> calcularGapCoding(const vector<int>& arreglo) {
    vector<int> gapCoding(arreglo.size());
    gapCoding[0] = arreglo[0];
    for (size_t i = 1; i < arreglo.size(); ++i) {
        gapCoding[i] = arreglo[i] - arreglo[i - 1];
    }
    return gapCoding;
}

// Función para generar la estructura "sample"
vector<int> generarSample(const vector<int>& arreglo, int m, int b) {
    vector<int> sample(m);
    int index = 0;
    for (int i = 0; i < m; ++i) {
        sample[i] = arreglo[index];
        index += b;
    }
    return sample;
}

