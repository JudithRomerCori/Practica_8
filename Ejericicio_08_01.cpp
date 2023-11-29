// Materia: Programación I, Paralelo 1

// Autor: Judith Marisol Romero Cori

// Fecha creación: 20/11/2023

// Fecha modificación: 25/11/2023

// Número de ejericio: 1

// Problema planteado:Escribir un programa con la opción de encriptar y de desencriptar un fichero de texto.
//La encriptación consiste en que dado un fichero de texto de entrada genere otro fichero de
//salida de extensión <nombre>.COD donde el texto estará codificado (encriptado).
//Esta codificación consiste en reemplazar cada carácter por el tercero siguiente según la tabla
//ASCII.
//La opción de desencriptado consiste en leer un fichero <nombre>.COD y recuperar la
//información original.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Función para encriptar un caracter según la tabla ASCII
char encriptarCaracter(char c) {
    return c + 3;  // Reemplazar por el tercer siguiente en la tabla ASCII
}

// Función para desencriptar un caracter
char desencriptarCaracter(char c) {
    return c - 3;  // Recuperar el caracter original
}

// Función para encriptar un archivo de texto
void encriptarArchivo(const string& nombreEntrada, const string& nombreSalida) {
    ifstream archivoEntrada(nombreEntrada);
    ofstream archivoSalida(nombreSalida + ".COD");

    if (!archivoEntrada.is_open() || !archivoSalida.is_open()) {
        cout << "Error al abrir los archivos." << endl;
        return;
    }

    char caracter;
    while (archivoEntrada.get(caracter)) {
        archivoSalida.put(encriptarCaracter(caracter));
    }

    archivoEntrada.close();
    archivoSalida.close();

    cout << "Encriptación completada." << endl;
}

// Función para desencriptar un archivo de texto
void desencriptarArchivo(const string& nombreEntrada, const string& nombreSalida) {
    ifstream archivoEntrada(nombreEntrada + ".COD");
    ofstream archivoSalida(nombreSalida);

    if (!archivoEntrada.is_open() || !archivoSalida.is_open()) {
        cout << "Error al abrir los archivos." << endl;
        return;
    }

    char caracter;
    while (archivoEntrada.get(caracter)) {
        archivoSalida.put(desencriptarCaracter(caracter));
    }

    archivoEntrada.close();
    archivoSalida.close();

    cout << "Desencriptación completada." << endl;
}

int main() {
    int opcion;
    string nombreEntrada, nombreSalida;

    cout << "Ingrese el nombre del archivo de entrada: ";
    getline(cin, nombreEntrada);

    cout << "Ingrese el nombre del archivo de salida: ";
    getline(cin, nombreSalida);

    cout << "Seleccione una opción:\n";
    cout << "1. Encriptar\n";
    cout << "2. Desencriptar\n";
    cin >> opcion;

    switch (opcion) {
        case 1:
            encriptarArchivo(nombreEntrada, nombreSalida);
            break;
        case 2:
            desencriptarArchivo(nombreEntrada, nombreSalida);
            break;
        default:
            cout << "Opción no válida." << endl;
            break;
    }

    return 0;
}

