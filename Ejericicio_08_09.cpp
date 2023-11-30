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
#include <vector>
#include <iomanip>

using namespace std;

void leerArchivoBinario(const string& nombreArchivo, vector<vector<double>>& tabla) {
    ifstream archivoEntrada(nombreArchivo, ios::binary);

    if (!archivoEntrada.is_open()) {
        cout << "Error al abrir el archivo binario." << endl;
        return;
    }

    double numero;
    vector<double> fila;

    while (archivoEntrada.read(reinterpret_cast<char*>(&numero), sizeof(double))) {
        fila.push_back(numero);
    }

    archivoEntrada.close();

    // Asumimos que la tabla es cuadrada para simplificar el código
    size_t n = static_cast<size_t>(sqrt(fila.size()));

    tabla.resize(n, vector<double>(n));

    size_t contador = 0;

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            tabla[i][j] = fila[contador++];
        }
    }
}

void escribirArchivoTexto(const string& nombreArchivo, const vector<vector<double>>& tabla, const vector<double>& sumaHorizontal, const vector<double>& sumaVertical) {
    ofstream archivoSalida(nombreArchivo);

    if (!archivoSalida.is_open()) {
        cout << "Error al abrir el archivo de texto." << endl;
        return;
    }

    size_t n = tabla.size();

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            archivoSalida << fixed << setprecision(2) << tabla[i][j] << " ";
        }
        archivoSalida << fixed << setprecision(2) << sumaHorizontal[i] << endl;
    }

    for (size_t i = 0; i < n; ++i) {
        archivoSalida << fixed << setprecision(2) << sumaVertical[i] << " ";
    }

    archivoSalida.close();

    cout << "Proceso completado. Se ha creado el archivo de texto '" << nombreArchivo << "'." << endl;
}

int main() {
    string nombreArchivoEntrada, nombreArchivoSalida;
    vector<vector<double>> tabla;
    vector<double> sumaHorizontal, sumaVertical;

    cout << "Ingrese el nombre del archivo binario de entrada: ";
    getline(cin, nombreArchivoEntrada);

    leerArchivoBinario(nombreArchivoEntrada, tabla);

    // Calcular suma horizontal
    for (const auto& fila : tabla) {
        sumaHorizontal.push_back(accumulate(fila.begin(), fila.end(), 0.0));
    }

    // Calcular suma vertical
    size_t n = tabla.size();
    sumaVertical.resize(n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            sumaVertical[j] += tabla[i][j];
        }
    }

    cout << "Ingrese el nombre del archivo de salida (con extensión .txt): ";
    getline(cin, nombreArchivoSalida);

    escribirArchivoTexto(nombreArchivoSalida, tabla, sumaHorizontal, sumaVertical);

    return 0;
}

