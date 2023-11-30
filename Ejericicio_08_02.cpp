// Materia: Programación I, Paralelo 1

// Autor: Judith Marisol Romero Cori

// Fecha creación: 20/11/2023

// Fecha modificación: 25/11/2023

// Número de ejericio: 2

// Problema planteado:Escriba un programa que cree un fichero de texto llamado "PERSONAS.BIN" en el que se
//guarde la información de un número indeterminado de personas.
//La información que se guardará por cada persona será:
//• Nombre: De 1 a 30 caracteres.
//• Edad numérico (>= 1 y <=100)
//• Sexo CHAR (M/F).
//• FechaNacimiento CHAR(10) (formato dd/mm/yyyy)
//La información correspondiente a cada persona se leerá del teclado.
//El proceso finalizará cuando se teclee un campo "Nombre" que esté solamente con el carácter
//de espacio.
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char* NOMBRE_ARCHIVO = "PERSONAS.BIN";

struct Persona
{
    char nombre[31];
    int edad;
    char sexo;
    char fechaNacimiento[11];
};

void escribirArchivoBinario(const Persona& persona)
{
    ofstream archivoEscritura;
    archivoEscritura.open(NOMBRE_ARCHIVO, ios::app | ios::binary);

    if (!archivoEscritura.is_open())
    {
        cout << "No se pudo abrir el archivo para escritura." << endl;
        return;
    }

    archivoEscritura.write(reinterpret_cast<const char*>(&persona), sizeof(Persona));

    archivoEscritura.close();
}

int main()
{
    while (true)
    {
        Persona nuevaPersona;

        // Ingresar información de la persona
        cout << "Ingrese el nombre de la persona (Espacio para finalizar): ";
        cin.ignore();  // Limpiar el buffer antes de leer la línea
        cin.getline(nuevaPersona.nombre, 30);

        if (strlen(nuevaPersona.nombre) == 0)
            break;

        cout << "Ingrese la edad de la persona: ";
        cin >> nuevaPersona.edad;

        cout << "Ingrese el sexo de la persona (M/F): ";
        cin >> nuevaPersona.sexo;

        cout << "Ingrese la fecha de nacimiento (dd/mm/yyyy): ";
        cin.ignore();  // Limpiar el buffer antes de leer la línea
        cin.getline(nuevaPersona.fechaNacimiento, 10);

        // Escribir la nueva persona en el archivo
        escribirArchivoBinario(nuevaPersona);
    }

    cout << "Proceso finalizado. Se ha creado el archivo 'PERSONAS.BIN'." << endl;

    return 0;
}

