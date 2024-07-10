# INFO145: Diseño y Análisis de Algoritmos
# Tarea: Técnicas de Representación y Comprensión de Arreglos Ordenados



### Integrantes 
* Luis Olivares
* Carmen Fuenzalida
* Jeral Ojeda
* Eduardo Leal

## Compilacion 
Para compilar el programa se ejecuta el comando 'make'

## Ejecución de los Programas
* Para Explicit: ./explicit n epsilon media dE semilla
* Para Gap-Coding: ./explicit n epsilon media dE semilla m
* Para Huffman: ./explicit n epsilon media dE semilla m

##### Siendo:
* n: Tamaño del arreglo original
* epsilon: Espacio que hay entre los numeros del arreglo Lineal
* media: Media para el arreglo con distribución Normal
* dE: Desviacion estandar para el arreglo con distribucion Normal 
* m: Tamaño del Sample de los gap de Gap Coding

## Archivos principales
* explicit.cpp: Implementación del arreglo explícito y búsqueda binaria.
* gapCoding.cpp: Implementación de Gap-Coding y búsqueda binaria.
* huffman.cpp: Implementación de Huffman Coding aplicado a Gap-Coding y búsqueda binaria.

## Modularizado:
Dentro de "Funciones" existe 3 scripts:
* busquedaBinaria.cpp
* gCoding.cpp
* generaArreglos.cpp

## Dentro de "Headers" existen 3 scripts:
* busquedaBinaria.h
* gCoding.h
* generaArreglos.h

### Dentro de Archivos:
Se guardan los datos generados por los arreglos# T1OjedaFuenzalidaLealOlivares
