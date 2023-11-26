// Materia: Programaci�n I, Paralelo 1

// Autor: Judith Marisol Romero Cori

// Fecha creaci�n: 20/11/2023

// Fecha modificaci�n: 25/11/2023

// N�mero de ejericio: 4

// Problema planteado:Codifique un programa que cree un fichero para contener los datos relativos a los art�culos de
//un almac�n.
//Para cada art�culo habr� de guardar la siguiente informaci�n:
//� C�digo del art�culo (Num�rico)
//� Nombre del art�culo (Cadena de caracteres)
//� Existencias actuales (Num�rico)
//� Precio (Num�rico decimal).
//Se deber�n pedir datos de cada art�culo por teclado hasta que como c�digo se teclee el c�digo 0.
//El fichero se habr� de crear ordenado por el c�digo del art�culo.
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const char* NOMBRE_ARCHIVO = "almacen.dat";

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

void escribirArchivoBinario(const vector<Articulo>& articulos)
{
    ofstream archivoEscritura;
    archivoEscritura.open(NOMBRE_ARCHIVO, ios::binary);

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

    while (true)
    {
        Articulo nuevoArticulo;

        // Ingresar informaci�n del art�culo
        cout << "Ingrese el c�digo del art�culo (0 para finalizar): ";
        cin >> nuevoArticulo.codigo;

        if (nuevoArticulo.codigo == 0)
            break;

        cin.ignore(); // Limpiar el buffer despu�s de leer el c�digo

        cout << "Ingrese el nombre del art�culo: ";
        cin.getline(nuevoArticulo.nombre, 50);

        cout << "Ingrese las existencias actuales: ";
        cin >> nuevoArticulo.existencias;

        cout << "Ingrese el precio: ";
        cin >> nuevoArticulo.precio;

        // Agregar el nuevo art�culo al vector
        articulos.push_back(nuevoArticulo);
    }

    // Ordenar el vector por c�digo antes de escribir en el archivo
    sort(articulos.begin(), articulos.end(), compararPorCodigo);

    // Escribir la informaci�n en el archivo
    escribirArchivoBinario(articulos);

    cout << "Proceso finalizado. Se ha creado el archivo 'almacen.dat'." << endl;

    return 0;
}

