#include "../Headers/generaArreglos.h"

//Funcion que genera un Arreglo con Distribucion Lineal de forma ordenada
vector<int> generaArregloLineal(int n, int epsilon, int semilla) {
    vector<int> arreglo(n);
    srand(semilla);
    arreglo[0] = rand() % n;
    for (int i = 1; i < n; ++i) {
        arreglo[i] = arreglo[i-1] + (rand() % epsilon) + 1 ;
    }
    return arreglo;
}

//Funcion que genera un Arreglo con Distribucion normal de forma ordenada
vector<int> generaArregloNormal(int n, double media, double desviacion_estandar, int semilla) {
    vector<int> arreglo(n);
    default_random_engine generador(semilla);
    normal_distribution<double> distribucion(media, desviacion_estandar);

    for (int i = 0; i < n; ++i) {
        arreglo[i] = static_cast<int>(distribucion(generador));
        //cout<<array[i]<<endl;
    }
   sort(arreglo.begin(), arreglo.end());
    
    return arreglo;
}



void guardarEnArchivo(const std::vector<int>& arreglo, const std::string& nombreArchivo) {
    // Crear la carpeta "Archivos" si no existe
    fs::path directorio = "Archivos";
    if (!fs::exists(directorio)) {
        fs::create_directory(directorio);
    }

    // Crear la ruta completa del archivo
    fs::path rutaArchivo = directorio / nombreArchivo;
    
    std::ofstream archivo(rutaArchivo);
    
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return;
    }

    for (size_t i = 0; i < arreglo.size(); ++i) {
        archivo << arreglo[i];
        if (i != arreglo.size() - 1) {
            archivo << ",";
        }
    }

    archivo.close();
}
