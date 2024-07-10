#ifndef GENERAARREGLO_H
#define GENERAARREGLO_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <string>
#include <filesystem> // Para std::filesystem

namespace fs = std::filesystem;
using namespace std;

vector<int> generaArregloLineal(int n, int epsilon, int semilla);
vector<int> generaArregloNormal(int n, double media, double desviacion_estandar, int semilla);
void guardarEnArchivo(const vector<int>& arreglo, const string& nombreArchivo);


#endif