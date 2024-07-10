#include "Headers/generaArreglos.h"
#include "Headers/busquedaBinaria.h"
#include <chrono>
#include <iostream>


using namespace std;



int main(int argc, char** argv) {
    if (argc != 6) { // Corrobora que el programa se ejecute de una forma correcta
        cout << "Error. Debe ejecutarse como ./explicit <n> <epsilon> <media> <dE> <semilla>" << endl;
        exit(EXIT_FAILURE);
    }
    cout << endl;
    auto tInicioPrograma = chrono::high_resolution_clock::now();
    cout << "Programa Ejecutado: Explicit" << endl << endl;

    //-----------------Declarando Variables-------------------

    int semilla, n, epsilon, datoBuscadoLineal, datoBuscadoNormal, indiceLineal, indiceNormal;
    double media, desviacion_estandar;
    vector<int> arregloLineal, arregloNormal;

    //-----------------Inicializando Variables-------------------

    n = atoi(argv[1]); //100000; // Tamaño del arreglo
    epsilon = atoi(argv[2]); //10;   // Valor para la distribución lineal
    media = atof(argv[3]); //0.0;  // Media para la distribución normal
    desviacion_estandar = atof(argv[4]); //10.0; // Desviación estándar para la distribución normal
    semilla = atoi(argv[5]); //1234;

    //-----------------Validando Variables-------------------

    if ((n < 0) || (epsilon < 0) || (media < 0) || (desviacion_estandar < 0) || (semilla < 0)) {
        cout << "Error, Ingrese números válidos mayores a 0" << endl;
        exit(EXIT_FAILURE);
    }

    //------------------->Generación de arreglos<-----------------

    // Arreglo con distribución Lineal
    auto tInicialArrLineal = chrono::high_resolution_clock::now();
    arregloLineal = generaArregloLineal(n, epsilon, semilla);
    auto tFinalArrLienal = chrono::high_resolution_clock::now();
    string nombreArchivo = "explicitLineal.txt";
    guardarEnArchivo(arregloLineal, nombreArchivo);
    // Arreglo con distribución Normal
    auto tInicialArrNormal = chrono::high_resolution_clock::now();
    arregloNormal = generaArregloNormal(n, media, desviacion_estandar, semilla);
    auto tFinalArrNormal = chrono::high_resolution_clock::now();
    nombreArchivo = "explicitNormal.txt";
    guardarEnArchivo(arregloNormal, nombreArchivo);
    // Tiempos:
    chrono::duration<double> tGenArrLineal = tFinalArrLienal - tInicialArrLineal;
    chrono::duration<double> tGenArrNormal = tFinalArrNormal - tInicialArrNormal;

    //------------------Para el Arreglo con Distribución Lineal----------------------

    datoBuscadoLineal = rand() % (arregloLineal.size() * epsilon); // Valor a buscar
    // Medición del tiempo de búsqueda binaria: 
    auto tIniBBLineal = chrono::high_resolution_clock::now();
    indiceLineal = busquedaBinaria(arregloLineal, datoBuscadoLineal);
    auto tFinBBLineal = chrono::high_resolution_clock::now();
    // Costo Computacional (tiempo de búsqueda):
    chrono::duration<double> tTotalBBLineal = tFinBBLineal - tIniBBLineal;

    //--------------Para el Sample del Arreglo con Distribución normal----------------------  

    datoBuscadoNormal = static_cast<int>(media);
    // Medición del tiempo de búsqueda binaria:
    auto tIniBBNormal = chrono::high_resolution_clock::now();
    indiceNormal = busquedaBinaria(arregloNormal, datoBuscadoNormal);
    auto tFinBBNormal = chrono::high_resolution_clock::now();
    // Costo Computacional (tiempo de búsqueda):
    chrono::duration<double> tTotalBBNormal = tFinBBNormal - tIniBBNormal;

    //------------------------------->Resultados<-----------------------------------------

    // Impresión Datos: Arreglo Distribución LINEAL
    cout << "-----------Arreglo Distribución Lineal-----------" << endl;
    cout << "Tiempo para Generar el Arreglo con D.Lineal: " << tGenArrLineal.count() << " segundos." << endl;
    imprimeResultadosBB(indiceLineal, datoBuscadoLineal);
    cout << "Tiempo de búsqueda: " << tTotalBBLineal.count() << " segundos." << endl;
    cout << "Uso de Memoria: " << sizeof(int) * arregloLineal.size() << " bytes" << endl;
    cout << "Memoria residente actual: " << getMemoryUsage() << " KB" << endl << endl;

    // Impresión Datos: Distribución NORMAL
    cout << "-----------Arreglo Distribución Normal-----------" << endl;
    cout << "Tiempo para Generar el Arreglo con D.Normal: " << tGenArrNormal.count() << " segundos." << endl;
    imprimeResultadosBB(indiceNormal, datoBuscadoNormal);
    cout << "Tiempo de búsqueda: " << tTotalBBNormal.count() << " segundos." << endl;
    cout << "Uso de Memoria: " << sizeof(int) * arregloNormal.size() << " bytes" << endl;
    cout << "Memoria residente actual: " << getMemoryUsage() << " KB" << endl << endl;


    //------------------Tiempo total en ejecución--------------------------------
    auto tFinalPrograma = chrono::high_resolution_clock::now();
    chrono::duration<double> tTotalPrograma = tFinalPrograma - tInicioPrograma;
    cout << "Tiempo total del programa en ejecución: " << tTotalPrograma.count() << endl;


    return 0;
}
