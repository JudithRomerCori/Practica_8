// Materia: Programación I, Paralelo 1

// Autor: Judith Marisol Romero Cori

// Fecha creación: 22/11/2023

// Fecha modificación: 26/11/2023

// Número de ejericio: 5

// Problema planteado:Escriba un programa que dados dos ficheros generados por el programa anterior y ordenados
//genere un tercer fichero que sea el resultado de mezclar de formar ordenada los dos primeros

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char* NOMBRE_ARCHIVO_ORDENADO_1 = "almacen_ordenado_1.dat";
const char* NOMBRE_ARCHIVO_ORDENADO_2 = "almacen_ordenado_2.dat";
const char* NOMBRE_ARCHIVO_RESULTADO = "almacen_resultado.dat";

struct Articulo
{
    int codigo;
    char nombre[50];
    int existencias;
    double precio;
};

void mezclarArchivos(const char* nombreArchivo1, const char* nombreArchivo2, const char* nombreArchivoResultado)
{
    ifstream archivo1(nombreArchivo1, ios::binary);
    ifstream archivo2(nombreArchivo2, ios::binary);
    ofstream archivoResultado(nombreArchivoResultado, ios::binary);

    Articulo articulo1, articulo2;

    // Leer el primer artículo de cada archivo
    archivo1.read(reinterpret_cast<char*>(&articulo1), sizeof(Articulo));
    archivo2.read(reinterpret_cast<char*>(&articulo2), sizeof(Articulo));

    while (!archivo1.eof() && !archivo2.eof())
    {
        // Comparar los códigos de los artículos y escribir el menor en el archivo de resultado
        if (articulo1.codigo < articulo2.codigo)
        {
            archivoResultado.write(reinterpret_cast<const char*>(&articulo1), sizeof(Articulo));
            archivo1.read(reinterpret_cast<char*>(&articulo1), sizeof(Articulo));
        }
        else
        {
            archivoResultado.write(reinterpret_cast<const char*>(&articulo2), sizeof(Articulo));
            archivo2.read(reinterpret_cast<char*>(&articulo2), sizeof(Articulo));
        }
    }

    // Escribir el contenido restante del archivo 1, si lo hay
    while (!archivo1.eof())
    {
        archivoResultado.write(reinterpret_cast<const char*>(&articulo1), sizeof(Articulo));
        archivo1.read(reinterpret_cast<char*>(&articulo1), sizeof(Articulo));
    }

    // Escribir el contenido restante del archivo 2, si lo hay
    while (!archivo2.eof())
    {
        archivoResultado.write(reinterpret_cast<const char*>(&articulo2), sizeof(Articulo));
        archivo2.read(reinterpret_cast<char*>(&articulo2), sizeof(Articulo));
    }

    archivo1.close();
    archivo2.close();
    archivoResultado.close();
}

int main()
{
    mezclarArchivos(NOMBRE_ARCHIVO_ORDENADO_1, NOMBRE_ARCHIVO_ORDENADO_2, NOMBRE_ARCHIVO_RESULTADO);

    cout << "Proceso de mezcla finalizado. Se ha creado el archivo 'almacen_resultado.dat'." << endl;

    return 0;
}

