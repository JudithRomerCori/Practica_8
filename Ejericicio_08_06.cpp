// Materia: Programaci�n I, Paralelo 1

// Autor: Judith Marisol Romero Cori

// Fecha creaci�n: 22/11/2023

// Fecha modificaci�n: 26/11/2023

// N�mero de ejericio: 6

// Problema planteado:Escriba un programa que tome como entrada el fichero del ejercicio 4 y una condici�n sobre el
//campo Precio. La condici�n podr� ser:
//Precio mayo o igual a 100 o cualquier otro dato ingresado por teclado.
//Este programa debe generar como salida un fichero llamado "salida.dat" que contenga todos
//aquellos art�culos para los que se cumple la condici�n de entrada.
//Mostrar el archivo de salida �salida.dat�
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const char* NOMBRE_ARCHIVO_ENTRADA = "almacen.dat";
const char* NOMBRE_ARCHIVO_SALIDA = "salida.dat";

struct Articulo
{
    int codigo;
    char nombre[50];
    int existencias;
    double precio;
};

bool compararPorCodigo(const Articulo& a, const Articulo& b)
{
    return a.codigo < b.codigo;
}

void escribirArchivoBinario(const vector<Articulo>& articulos, const char* nombreArchivo)
{
    ofstream archivoEscritura;
    archivoEscritura.open(nombreArchivo, ios::binary);

    if (!archivoEscritura.is_open())
    {
        cout << "No se pudo abrir el archivo para escritura." << endl;
        return;
    }

    for (const Articulo& articulo : articulos)
    {
        archivoEscritura.write(reinterpret_cast<const char*>(&articulo), sizeof(Articulo));
    }

    archivoEscritura.close();
}

int main()
{
    vector<Articulo> articulos;

    // Leer datos del archivo de entrada
    ifstream archivoLectura(NOMBRE_ARCHIVO_ENTRADA, ios::binary);

    if (!archivoLectura.is_open())
    {
        cout << "No se pudo abrir el archivo de entrada." << endl;
        return 1;
    }

    while (true)
    {
        Articulo nuevoArticulo;
        archivoLectura.read(reinterpret_cast<char*>(&nuevoArticulo), sizeof(Articulo));

        if (archivoLectura.eof())
            break;

        // Verificar si el precio cumple con la condici�n
        // Puedes ajustar la condici�n seg�n tus necesidades
        if (nuevoArticulo.precio <= 100)
        {
            articulos.push_back(nuevoArticulo);
        }
    }

    archivoLectura.close();

    // Ordenar el vector por c�digo antes de escribir en el archivo de salida
    sort(articulos.begin(), articulos.end(), compararPorCodigo);

    // Escribir la informaci�n en el archivo de salida
    escribirArchivoBinario(articulos, NOMBRE_ARCHIVO_SALIDA);

    cout << "Proceso finalizado. Se ha creado el archivo 'salida.dat'." << endl;

    return 0;
}
