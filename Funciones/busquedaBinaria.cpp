#include "../Headers/busquedaBinaria.h"


int busquedaBinaria(const vector<int>& arreglo, int elemento) {
    int izquierda, derecha;
    izquierda = 0;
    derecha = arreglo.size() - 1;
    while (izquierda <= derecha) {
        int mitad = izquierda + (derecha - izquierda) / 2;
        if (arreglo[mitad] == elemento) {
            return mitad;
        }
        if (arreglo[mitad] < elemento) izquierda = mitad + 1;
        else derecha = mitad - 1;
    }
    return -1;
}

void imprimeResultadosBB(int indice, int elemento){
    if (indice != -1) {
        cout << "Elemento " << elemento << " encontrado en la posición " << indice << "." << endl;
    } else {
        cout << "Elemento " << elemento << " no encontrado." << endl;
    }
}

// Función para obtener el uso de memoria residente (en KB)
size_t getMemoryUsage() {
    std::ifstream stat_stream("/proc/self/status", std::ios_base::in);
    std::string line;
    size_t vm_rss = 0; // in KB

    while (std::getline(stat_stream, line)) {
        if (line.substr(0, 6) == "VmRSS:") {
            std::istringstream iss(line);
            std::string temp;
            iss >> temp >> vm_rss; // "VmRSS:" y el valor
            break;
        }
    }
    return vm_rss;
}


