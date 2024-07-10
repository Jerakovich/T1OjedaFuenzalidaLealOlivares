#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <chrono>
#include "Headers/generaArreglos.h"
#include "Headers/busquedaBinaria.h"
#include "Headers/gCoding.h"

using namespace std;

int main(int argc, char** argv) {
    if(argc != 7){//Corrobora que el programa se ejecute de una forma correcta
		cout << "Error. Debe ejecutarse como: ./gapCoding <n> <epsilon> <media> <dE> <semilla> <m>" << endl;
		exit(EXIT_FAILURE);
	}
    cout << endl;
    auto tInicioPrograma = chrono::high_resolution_clock::now();
    cout << "Programa Ejecutado: Gap-Coding" << endl<< endl << endl;
    
    //-----------------Declarando Variables-------------------
    int semilla, n, epsilon, m, b, datoBuscadoLineal, datoBuscadoNormal, indiceSampleLineal, indiceSampleNormal;
    double media, desviacion_estandar;
    vector<int> arregloLineal, arregloNormal, gapCodingLineal, gapCodingNormal, sampleLineal, sampleNormal;

    //-----------------Inicializando Variables-------------------
    n = atoi(argv[1]); //100000; // Tamaño del arreglo
    epsilon = atoi(argv[2]); //10;   // Valor para la distribución lineal
    media = atoi(argv[3]);//0.0;  // Media para la distribución normal
    desviacion_estandar = atoi(argv[4]);//10.0; // Desviación estándar para la distribución normal
    semilla = atoi(argv[5]);//1234;
    m = atoi(argv[6]); // tamaño del sample

    //-----------------Validando Variables-------------------
    if((n<0)||(epsilon<0)||(media<0)||(desviacion_estandar<0)||(semilla<0)||(m<0)){
        cout<<"Error, Ingrese numeros validos mayores a 0"<<endl;
        exit(EXIT_FAILURE);
    }
    

    //------------------->Generación de arreglos<-----------------
        // Arreglo con distribucion Lineal
    auto tInicialArrLineal = chrono::high_resolution_clock::now();
    arregloLineal = generaArregloLineal(n, epsilon, semilla);
    auto tFinalArrLienal = chrono::high_resolution_clock::now();
        // Arreglo con distribucion Normal
    auto tInicialArrNormal = chrono::high_resolution_clock::now();
    arregloNormal = generaArregloNormal(n, media, desviacion_estandar, semilla);
    auto tFinalArrNormal = chrono::high_resolution_clock::now();
        // Tiempos:
    chrono::duration<double> tGenArrLineal = tFinalArrLienal - tInicialArrLineal;
    chrono::duration<double> tGenArrNormal = tFinalArrNormal - tInicialArrNormal;


    //-------------->Calcular Gap-Coding de arreglos<-----------------
        // Arreglo con distribucion Lineal
    auto tIniCalcGPLineal = chrono::high_resolution_clock::now();
    gapCodingLineal = calcularGapCoding(arregloLineal); //Lineal
    auto tFinCalcGPLineal = chrono::high_resolution_clock::now();
        // Arreglo con distribucion Normal
    auto tIniCalcGPNormal = chrono::high_resolution_clock::now();
    gapCodingNormal = calcularGapCoding(arregloNormal); //Distribucion Normal
    auto tFinCalcGPNormal = chrono::high_resolution_clock::now();
        // Tiempos Calculo del Gap Coding:
    chrono::duration<double> tCalcArrLineal = tFinCalcGPLineal - tIniCalcGPLineal;
    chrono::duration<double> tCalcArrNormal = tFinCalcGPNormal - tIniCalcGPNormal;


    //----------->Genera la estructura "sample" de los arreglos<-----------------
        // Arreglo con distribucion Lineal
    b = n / m; //espacio entre los elementos del sample
    auto tIniSampleLineal = chrono::high_resolution_clock::now();
    sampleLineal = generarSample(arregloLineal, m, b); //Lineal
    auto tFinSampleLineal = chrono::high_resolution_clock::now();
        // Arreglo con distribucion Normal
    auto tIniSamplePNormal = chrono::high_resolution_clock::now();
    sampleNormal = generarSample(arregloNormal, m, b); //Distribucion Normal
    auto tFinSampleNormal = chrono::high_resolution_clock::now();
        // Tiempos de Construccion del Gap Coding:
    chrono::duration<double> tSampleArrLineal = tFinSampleLineal - tIniSampleLineal;
    chrono::duration<double> tSampleArrNormal = tFinSampleNormal - tIniSamplePNormal;


    //------------------Para el Sample del Arreglo con Distribucion Lineal----------------------
    datoBuscadoLineal = rand() % (arregloLineal.size() * epsilon);// Valor a buscar
        // Medición del tiempo de búsqueda binaria: 
    auto tIniBBLineal = chrono::high_resolution_clock::now();
    indiceSampleLineal = busquedaBinaria(sampleLineal, datoBuscadoLineal);
    auto tFinBBLineal = chrono::high_resolution_clock::now();
        //Costo Computacional (tiempo de busqueda):
    chrono::duration<double> tTotalBBLineal = tFinBBLineal - tIniBBLineal;


    //--------------Para el Sample del Arreglo con Distribucion normal----------------------  
    datoBuscadoNormal = static_cast<int>(media);
        // Medición del tiempo de búsqueda binaria:
    auto tIniBBNormal = chrono::high_resolution_clock::now(); 
    indiceSampleNormal = busquedaBinaria(sampleNormal, datoBuscadoNormal);
    auto tFinBBNormal = chrono::high_resolution_clock::now();
        //Costo Computacional (tiempo de busqueda):
    chrono::duration<double> tTotalBBNormal = tFinBBNormal - tIniBBNormal;


    //------------------------------->Resultados<-----------------------------------------
        // Impresion Datos: Distribucion LINEAL
    cout << "-----------Arreglo Distribucion Lineal-----------" << endl;
    cout << "Tiempo para Generar el Arreglo con D.Lineal: " << tGenArrLineal.count() << " segundos." << endl;
    cout << "Tiempo para Calcular GapCoding del Arreglo con D.Lineal: " << tCalcArrLineal.count() << " segundos." << endl;
    cout << "Tiempo para Construir el Sample del Arreglo con D.Lineal: " << tSampleArrLineal.count() << " segundos." << endl<< endl;
    cout << "Posición del elemento final del Arreglo Gap-Coded: " << gapCodingLineal.size() - 1 << endl;
    imprimeResultadosBB(indiceSampleLineal, datoBuscadoLineal);
    cout << "Tiempo de busqueda: " << tTotalBBLineal.count() << " segundos." <<endl;
    cout << "Uso de Memoria: " << sizeof(int) * arregloLineal.size() << " bytes" << endl ;
    cout << "Memoria residente actual: " << getMemoryUsage() << " KB" << endl << endl << endl;
            // Impresion Datos: Distribucion NORMAL
    cout << "-----------Arreglo Distribucion Normal-----------" << endl;
    cout << "Tiempo para Generar el Arreglo con D.Normal: " << tGenArrNormal.count() << " segundos." << endl;
    cout << "Tiempo para Calcular GapCoding del Arreglo con D.Normal: " << tCalcArrNormal.count() << " segundos." << endl;
    cout << "Tiempo para Construir el Sample del Arreglo con D.Normal: " << tSampleArrNormal.count() << " segundos." << endl<< endl;
    cout << "Posición del elemento final del Arreglo Gap-Coded: " << gapCodingNormal.size() - 1 << endl;
    imprimeResultadosBB(indiceSampleNormal, datoBuscadoNormal);
    cout << "Tiempo de busqueda: " << tTotalBBNormal.count() << " segundos." << endl;
    cout << "Memoria residente actual: " << getMemoryUsage() << " KB" << endl << endl;

    //------------------Tiempo total en ejecucion--------------------------------
    auto tFinalPrograma  = chrono::high_resolution_clock::now();
    chrono::duration<double> tTotalPrograma = tFinalPrograma - tInicioPrograma;
    cout<<"Tiempo total del programa en ejecución: "<< tTotalPrograma.count() <<endl << endl;
    
    return 0;
}
