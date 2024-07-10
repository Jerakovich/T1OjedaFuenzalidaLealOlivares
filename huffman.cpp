#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <bitset>
#include "Headers/generaArreglos.h"
#include "Headers/gCoding.h"
#include "Headers/busquedaBinaria.h"

using namespace std;

// Estructura del Arbol de Huffman 
struct HuffmanNode {
    int value;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    
    HuffmanNode(int val, int freq) : value(val), frequency(freq), left(nullptr), right(nullptr) {}
};

// minHeap
struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->frequency > r->frequency;
    }
};


// función para contar la frecuencia de los valores en el arreglo de gaps
unordered_map<int, int> contadorFrecuencias(const vector<int>& gaps) {
    unordered_map<int, int> frec;
    for (int gap : gaps) {
        frec[gap]++;
    }
    return frec;
}

// construcción del árbol de Huffman
HuffmanNode* construyeArbolHuffman(const unordered_map<int, int>& freq) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;
    for (auto pair : freq) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();
        HuffmanNode* merged = new HuffmanNode(-1, left->frequency + right->frequency);
        merged->left = left;
        merged->right = right;
        minHeap.push(merged);
    }

    return minHeap.top();
}

// generar códigos de Huffman
void generaCodigosHuffman(HuffmanNode* raiz, const string& codigo, unordered_map<int, string>& codigosHuffman) {
    if (!raiz) return;
    if (raiz->value != -1) {
        codigosHuffman[raiz->value] = codigo;
    }
    generaCodigosHuffman(raiz->left, codigo + "0", codigosHuffman);
    generaCodigosHuffman(raiz->right, codigo + "1", codigosHuffman);
}

// comprimir el arreglo gap-coded usando Huffman codes
vector<uint16_t> comprimeGapCoding(const vector<int>& gaps, const unordered_map<int, string>& codigosHuffman) {
    vector<uint16_t> comprimido;
    for (int gap : gaps) {
        string codigo = codigosHuffman.at(gap);
        uint16_t codigoComprimido = static_cast<uint16_t>(stoi(codigo, nullptr, 2)); // Convertir cadena binaria a entero
        comprimido.push_back(codigoComprimido);
    }
    return comprimido;
}

// buscar un elemento en el arreglo original con Gap-Coding y Huffman-Coding
int buscaElemento(const vector<int>& arreglo, const vector<int>& gapCoding, const vector<int>& sample, int elemento) {
    int posSample, n, b, ini_Index,actual;
    posSample = busquedaBinaria(sample, elemento);
    n = arreglo.size();
    b = n / sample.size();
    ini_Index = posSample * b;
    actual = arreglo[ini_Index];

    for (int i = ini_Index; i < n; ++i) {
        if (actual == elemento) {
            return i;
        }
        actual += gapCoding[i];
    }
    return -1; // no se encontró
}

int main(int argc, char** argv) {
    if(argc != 7){//Corrobora que el programa se ejecute de una forma correcta
		cout << "Error. Debe ejecutarse como: ./huffman <n> <epsilon> <media> <dE> <semilla> <m>" << endl;
		exit(EXIT_FAILURE);
	}

    cout << endl;
    auto tInicioPrograma = chrono::high_resolution_clock::now();
    cout << "Programa Ejecutado: Huffman" << endl<< endl << endl;
    
    //-----------------Declarando Variables-------------------

    int semilla, n, epsilon, m, b, datoBuscadoLineal, datoBuscadoNormal, indiceLineal, indiceNormal;
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


    //----------->Construccion de los Arboles de Huffman<-----------------

        // Contando frecuencias de los gaps
    unordered_map<int, int> frecuenciaLineal = contadorFrecuencias(gapCodingLineal);
    unordered_map<int, int> frecuenciaNormal = contadorFrecuencias(gapCodingNormal);
        // Construir árbol de Huffman(Lineal)
    auto tIniArbLineal = chrono::high_resolution_clock::now();
    HuffmanNode* arbolLineal = construyeArbolHuffman(frecuenciaLineal);
    auto tFinArbLineal = chrono::high_resolution_clock::now();
        // Construir árbol de Huffman(Lineal)
    auto tIniArbNormal = chrono::high_resolution_clock::now();
    HuffmanNode* arbolNormal = construyeArbolHuffman(frecuenciaNormal);
    auto tFinArbNormal = chrono::high_resolution_clock::now();
        // Tiempos Construccion Arboles:
    chrono::duration<double> tTotalArbLineal = tFinArbLineal - tIniArbLineal;
    chrono::duration<double> tTotalArbNormal = tFinArbNormal - tIniArbNormal;


    //----------->Generar Codigos de Huffman<-----------------

    unordered_map<int, string> codigosHuffmanLineal;
    unordered_map<int, string> codigosHuffmanNormal;
        // Genera códigos de Huffman (Lineal)
    auto tIniCodLineal = chrono::high_resolution_clock::now();
    generaCodigosHuffman(arbolLineal, "", codigosHuffmanLineal);
    auto tFinCodLineal = chrono::high_resolution_clock::now();
        // Genera códigos de Huffman (Normal)
    auto tIniCodNormal = chrono::high_resolution_clock::now();
    generaCodigosHuffman(arbolNormal, "", codigosHuffmanNormal);
    auto tFinCodNormal = chrono::high_resolution_clock::now();
        // Tiempos Generacion Codgios Huffman:
    chrono::duration<double> tTotalCodLineal = tFinCodLineal - tIniCodLineal;
    chrono::duration<double> tTotalCodNormal = tFinCodNormal - tIniCodNormal;



    //----------->Comprimir el arreglo Gap-Coded usando Huffman<-----------------
        
        // Comprimir el arreglo Lineal
    auto tIniComprLineal = chrono::high_resolution_clock::now();
    vector<uint16_t> arrComprimidoLineal = comprimeGapCoding(gapCodingLineal, codigosHuffmanLineal);
    auto tFinComprLineal = chrono::high_resolution_clock::now();
        // Comprimir el arreglo Normal
    auto tIniComprNormal = chrono::high_resolution_clock::now();
    vector<uint16_t> arrComprimidoNormal = comprimeGapCoding(gapCodingLineal, codigosHuffmanLineal);
    auto tFinComprNormal = chrono::high_resolution_clock::now();
        // Tiempos Generacion Codgios Huffman:
    chrono::duration<double> tTotalComprLineal = tFinComprLineal - tIniComprLineal;
    chrono::duration<double> tTotalComprNormal = tFinComprNormal - tIniComprNormal;


    //----------->Busqueda Binaria<-----------------

        //Para el arreglo Lineal
    datoBuscadoLineal = arregloLineal[rand() % n];
    auto tIniBBLineal = chrono::high_resolution_clock::now();
    indiceLineal = buscaElemento(arregloLineal, gapCodingLineal, sampleLineal, datoBuscadoLineal);
    auto tFinBBLineal = chrono::high_resolution_clock::now();
        //Costo Computacional (tiempo de busqueda):
    chrono::duration<double> tTotalBBLineal = tFinBBLineal - tIniBBLineal;
        //Para el arreglo Normal
    datoBuscadoNormal = arregloNormal[rand() % n];
    auto tIniBBNormal = chrono::high_resolution_clock::now();
    indiceNormal = buscaElemento(arregloNormal, gapCodingNormal, sampleNormal, datoBuscadoNormal);
    auto tFinBBNormal = chrono::high_resolution_clock::now();
        //Costo Computacional (tiempo de busqueda):
    chrono::duration<double> tTotalBBNormal = tFinBBNormal - tIniBBNormal;


    //----------->Cálculo de tamaños en bits<----------------

        //Para el arreglo Lineal
    size_t n_OriginalBitsLineal = arregloLineal.size() * sizeof(int) * 8; // tamaño del arreglo original en bits
    size_t nComprimidoBitsLineal = 0;
    for (const auto& gap : gapCodingLineal) {
        nComprimidoBitsLineal += codigosHuffmanLineal[gap].length();
    }
        //Para el arreglo Normal
    size_t n_OriginalBitsNormal = arregloNormal.size() * sizeof(int) * 8; // tamaño del arreglo original en bits
    size_t nComprimidoBitsNormal = 0;
    for (const auto& gap : gapCodingNormal) {
        nComprimidoBitsNormal += codigosHuffmanNormal[gap].length();
    }


    //------------------------------->Resultados<-----------------------------------------

        // Impresion Datos: Distribucion LINEAL
    cout << "-----------Arreglo Distribucion Lineal-----------" << endl;
    cout << "Tiempo para Generar el Arreglo con D.Lineal: " << tGenArrLineal.count() << " segundos." << endl;
    cout << "Tiempo para Calcular GapCoding del Arreglo con D.Lineal: " << tCalcArrLineal.count() << " segundos." << endl;
    cout << "Tiempo para Construir el Sample del Arreglo con D.Lineal: " << tSampleArrLineal.count() << " segundos." << endl;
    cout << "Tiempo para construir el árbol de Huffman: " << tTotalArbLineal.count() << " segundos." << endl;
    cout << "Tiempo para generar los códigos de Huffman: " << tTotalCodLineal.count() << " segundos." << endl;
    cout << "Tiempo para comprimir los gaps usando Huffman: " << tTotalComprLineal.count() << " segundos." << endl << endl;
    cout << "Posición del elemento final del Arreglo Gap-Coded: " << gapCodingLineal.size() - 1 << endl;
    imprimeResultadosBB(indiceLineal, datoBuscadoLineal);
    cout << "Tiempo de busqueda: " << tTotalBBLineal.count() << " segundos." <<endl;
    cout << "Tamaño del arreglo original: " << n_OriginalBitsLineal << " bits" << endl;
    cout << "Tamaño del arreglo comprimido: " << nComprimidoBitsLineal << " bits" << endl ;
    cout << "Memoria residente actual: " << getMemoryUsage() << " KB" << endl << endl << endl;

        // Impresion Datos: Distribucion NORMAL
    cout << "-----------Arreglo Distribucion Normal-----------" << endl;
    cout << "Tiempo para Generar el Arreglo con D.Normal: " << tGenArrNormal.count() << " segundos." << endl;
    cout << "Tiempo para Calcular GapCoding del Arreglo con D.Normal: " << tCalcArrNormal.count() << " segundos." << endl;
    cout << "Tiempo para Construir el Sample del Arreglo con D.Normal: " << tSampleArrNormal.count() << " segundos." << endl;
    cout << "Tiempo para construir el árbol de Huffman: " << tTotalArbNormal.count() << " segundos." << endl;
    cout << "Tiempo para generar los códigos de Huffman: " << tTotalCodNormal.count() << " segundos." << endl;
    cout << "Tiempo para comprimir los gaps usando Huffman: " << tTotalComprNormal.count() << " segundos." << endl<< endl;
    cout << "Posición del elemento final del Arreglo Gap-Coded: " << gapCodingNormal.size() - 1 << endl;
    imprimeResultadosBB(indiceNormal, datoBuscadoNormal);
    cout << "Tiempo de busqueda: " << tTotalBBNormal.count() << " segundos." << endl;
    cout << "Tamaño del arreglo original: " << n_OriginalBitsNormal << " bits" << endl;
    cout << "Tamaño del arreglo comprimido: " << nComprimidoBitsNormal << " bits" << endl;
    cout << "Memoria residente actual: " << getMemoryUsage() << " KB" << endl << endl;

    //--------------->Liberar memoria de los árboles de Huffman<-----------------
    delete arbolLineal;
    delete arbolNormal;

    //----------------->Tiempo total en ejecucion<--------------------------------
    auto tFinalPrograma  = chrono::high_resolution_clock::now();
    chrono::duration<double> tTotalPrograma = tFinalPrograma - tInicioPrograma;
    cout<<"Tiempo total del programa en ejecución: "<< tTotalPrograma.count() <<endl << endl;
    
    return 0;
}
