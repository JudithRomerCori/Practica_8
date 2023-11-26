// Materia: Programaci�n I, Paralelo 1

// Autor: Judith Marisol Romero Cori

// Fecha creaci�n: 20/11/2023

// Fecha modificaci�n: 25/11/2023

// N�mero de ejericio: 1

// Problema planteado:Escribir un programa con la opci�n de encriptar y de desencriptar un fichero de texto.
//La encriptaci�n consiste en que dado un fichero de texto de entrada genere otro fichero de
//salida de extensi�n <nombre>.COD donde el texto estar� codificado (encriptado).
//Esta codificaci�n consiste en reemplazar cada car�cter por el tercero siguiente seg�n la tabla
//ASCII.
//La opci�n de desencriptado consiste en leer un fichero <nombre>.COD y recuperar la
//informaci�n original.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void encriptarArchivo(const string &nombreEntrada, const string &nombreSalida);
void desencriptarArchivo(const string &nombreEntrada, const string &nombreSalida);

int main() {
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo: ";
    getline(cin, nombreArchivo);

    // Encriptar el archivo
    encriptarArchivo(nombreArchivo, nombreArchivo + ".COD");

    // Desencriptar el archivo
    desencriptarArchivo(nombreArchivo + ".COD", nombreArchivo + "_desencriptado.txt");

    return 0;
}

void encriptarArchivo(const string &nombreEntrada, const string &nombreSalida) {
    ifstream archivoEntrada(nombreEntrada);
    ofstream archivoSalida(nombreSalida);

    if (!archivoEntrada.is_open() || !archivoSalida.is_open()) {
        cout << "Error al abrir los archivos." << endl;
        return;
    }

    char caracter;
    while (archivoEntrada.get(caracter)) {
        // Encriptar: reemplazar cada car�cter por el tercero siguiente en la tabla ASCII
        caracter = caracter + 3;
        archivoSalida.put(caracter);
    }

    archivoEntrada.close();
    archivoSalida.close();

    cout << "Encriptaci�n completada. Archivo encriptado: " << nombreSalida << endl;
}

void desencriptarArchivo(const string &nombreEntrada, const string &nombreSalida) {
    ifstream archivoEntrada(nombreEntrada);
    ofstream archivoSalida(nombreSalida);

    if (!archivoEntrada.is_open() || !archivoSalida.is_open()) {
        cout << "Error al abrir los archivos." << endl;
        return;
    }

    char caracter;
    while (archivoEntrada.get(caracter)) {
        // Desencriptar: reemplazar cada car�cter por el tercero anterior en la tabla ASCII
        caracter = caracter - 3;
        archivoSalida.put(caracter);
    }

    archivoEntrada.close();
    archivoSalida.close();

    cout << "Desencriptaci�n completada. Archivo desencriptado: " << nombreSalida << endl;
}

