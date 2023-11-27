
// Materia: Programaci�n I, Paralelo 1

// Autor: Judith Marisol Romero Cori

// Fecha creaci�n: 22/11/2023

// Fecha modificaci�n: 26/11/2023

// N�mero de ejericio: 8

// Problema planteado:Escribir un programa que genere a partir de un fichero de entrada que contiene una tabla de
//n�meros reales otro fichero de salida <nombre>.BIN grabado en formato binario.
//Ej:
//1.23 3.45 12.5
//4.8 3.9 0.83 ........................
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Funci�n para generar un archivo binario a partir de un archivo de entrada
void generarArchivoBinario(const string& nombreArchivoEntrada, const string& nombreArchivoSalida) {
    // Abrir el archivo de entrada en modo lectura
    ifstream archivoEntrada(nombreArchivoEntrada);

    // Verificar si el archivo de entrada se abri� correctamente
    if (!archivoEntrada.is_open()) {
        cout << "No se pudo abrir el archivo de entrada." << endl;
        return;
    }

    // Abrir el archivo de salida en modo binario
    ofstream archivoSalida(nombreArchivoSalida, ios::binary);

    // Verificar si el archivo de salida se abri� correctamente
    if (!archivoSalida.is_open()) {
        cout << "No se pudo abrir el archivo de salida." << endl;
        archivoEntrada.close();  // Cerrar el archivo de entrada antes de salir
        return;
    }

    // Variable para almacenar cada n�mero del archivo de entrada
    double numero;

    // Leer n�meros del archivo de entrada y escribirlos en el archivo de salida en formato binario
    while (archivoEntrada >> numero) {
        archivoSalida.write(reinterpret_cast<const char*>(&numero), sizeof(double));
    }

    // Cerrar los archivos
    archivoEntrada.close();
    archivoSalida.close();

    // Mensaje de �xito
    cout << "Proceso finalizado. Se ha creado el archivo '" << nombreArchivoSalida << "'." << endl;
}

int main() {
    // Variables para almacenar los nombres de archivo
    string nombreArchivoEntrada, nombreArchivoSalida;

    // Solicitar al usuario el nombre del archivo de entrada
    cout << "Ingrese el nombre del archivo de entrada: ";
    getline(cin, nombreArchivoEntrada);

    // Solicitar al usuario el nombre del archivo de salida (con extensi�n .BIN)
    cout << "Ingrese el nombre del archivo de salida (con extensi�n .BIN): ";
    getline(cin, nombreArchivoSalida);

    // Llamar a la funci�n para generar el archivo binario
    generarArchivoBinario(nombreArchivoEntrada, nombreArchivoSalida);

    return 0;
}
