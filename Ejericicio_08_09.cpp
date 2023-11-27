// Materia: Programación I, Paralelo 1

// Autor: Judith Marisol Romero Cori

// Fecha creación: 22/11/2023

// Fecha modificación: 26/11/2023

// Número de ejericio: 9

// Problema planteado:Dado una tabla grabada en un fichero en formato binario <nombre>.BIN hallar la suma
//horizontal y vertical y grabar la tabla y los resultados en otro fichero de texto o binario según se
//introduzca por pantalla.
//El resultado en texto sería el siguiente:
//Ej:
//1.23 3.45 12.5 17,18
//4.8 3.9 0.83 9,53
//6,03 7,35 13,33 26,71
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

// Función para leer la tabla desde un archivo binario
void leerTablaBinaria(const string& nombreArchivo, vector<vector<double>>& tabla) {
    ifstream archivoEntrada(nombreArchivo, ios::binary);

    if (!archivoEntrada.is_open()) {
        cout << "No se pudo abrir el archivo de entrada." << endl;
        return;
    }

    // Leer las dimensiones de la tabla
    size_t filas, columnas;
    archivoEntrada.read(reinterpret_cast<char*>(&filas), sizeof(size_t));
    archivoEntrada.read(reinterpret_cast<char*>(&columnas), sizeof(size_t));

    // Redimensionar la tabla
    tabla.resize(filas, vector<double>(columnas));

    // Leer los elementos de la tabla
    for (size_t i = 0; i < filas; ++i) {
        for (size_t j = 0; j < columnas; ++j) {
            archivoEntrada.read(reinterpret_cast<char*>(&tabla[i][j]), sizeof(double));
        }
    }

    archivoEntrada.close();
}

// Función para calcular la suma horizontal y vertical
void calcularSumas(const vector<vector<double>>& tabla, vector<double>& sumasHorizontales, vector<double>& sumasVerticales) {
    size_t filas = tabla.size();
    size_t columnas = tabla[0].size();

    // Inicializar vectores de sumas con ceros
    sumasHorizontales.resize(filas, 0.0);
    sumasVerticales.resize(columnas, 0.0);

    // Calcular sumas horizontales
    for (size_t i = 0; i < filas; ++i) {
        for (size_t j = 0; j < columnas; ++j) {
            sumasHorizontales[i] += tabla[i][j];
        }
    }

    // Calcular sumas verticales
    for (size_t j = 0; j < columnas; ++j) {
        for (size_t i = 0; i < filas; ++i) {
            sumasVerticales[j] += tabla[i][j];
        }
    }
}

// Función para escribir la tabla y las sumas en un archivo (texto o binario)
void escribirResultado(const string& nombreArchivo, const vector<vector<double>>& tabla,
                       const vector<double>& sumasHorizontales, const vector<double>& sumasVerticales) {
    ofstream archivoSalida(nombreArchivo);

    if (!archivoSalida.is_open()) {
        cout << "No se pudo abrir el archivo de salida." << endl;
        return;
    }

    // Escribir la tabla original en el archivo
    for (size_t i = 0; i < tabla.size(); ++i) {
        for (size_t j = 0; j < tabla[i].size(); ++j) {
            archivoSalida << fixed << setprecision(2) << tabla[i][j] << " ";
        }
        archivoSalida << fixed << setprecision(2) << sumasHorizontales[i] << endl;
    }

    // Escribir las sumas verticales en la última fila
    for (size_t j = 0; j < sumasVerticales.size(); ++j) {
        archivoSalida << fixed << setprecision(2) << sumasVerticales[j] << " ";
    }
    archivoSalida << endl;

    archivoSalida.close();
}

int main() {
    string nombreArchivoEntrada, nombreArchivoSalida;
    vector<vector<double>> tabla;
    vector<double> sumasHorizontales, sumasVerticales;

    // Solicitar al usuario el nombre del archivo de entrada
    cout << "Ingrese el nombre del archivo de entrada: ";
    getline(cin, nombreArchivoEntrada);

    // Leer la tabla desde el archivo binario
    leerTablaBinaria(nombreArchivoEntrada, tabla);

    // Calcular sumas horizontales y verticales
    calcularSumas(tabla, sumasHorizontales, sumasVerticales);

    // Solicitar al usuario el nombre del archivo de salida
    cout << "Ingrese el nombre del archivo de salida: ";
    getline(cin, nombreArchivoSalida);

    // Escribir la tabla y las sumas en el archivo de salida
    escribirResultado(nombreArchivoSalida, tabla, sumasHorizontales, sumasVerticales);

    cout << "Proceso finalizado. Se ha creado el archivo '" << nombreArchivoSalida << "'." << endl
