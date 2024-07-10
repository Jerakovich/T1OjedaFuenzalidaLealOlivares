#ifndef BUSQUEDABINARIA_H
#define BUSQUEDABINARIA_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream> 
using namespace std;

int busquedaBinaria(const vector<int>& sample, int elemento);
void imprimeResultadosBB(int indice, int elemento);
size_t getMemoryUsage();
#endif