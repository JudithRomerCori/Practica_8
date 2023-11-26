// Materia: Programaci�n I, Paralelo 1

// Autor: Judith Marisol Romero Cori

// Fecha creaci�n: 20/11/2023

// Fecha modificaci�n: 25/11/2023

// N�mero de ejericio: 2

// Problema planteado:Escriba un programa que cree un fichero de texto llamado "PERSONAS.BIN" en el que se
//guarde la informaci�n de un n�mero indeterminado de personas.
//La informaci�n que se guardar� por cada persona ser�:
//� Nombre: De 1 a 30 caracteres.
//� Edad num�rico (>= 1 y <=100)
//� Sexo CHAR (M/F).
//� FechaNacimiento CHAR(10) (formato dd/mm/yyyy)
//La informaci�n correspondiente a cada persona se leer� del teclado.
//El proceso finalizar� cuando se teclee un campo "Nombre" que est� solamente con el car�cter
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
    archivoEscritura.write(reinterpret_cast<const char*>(&persona), sizeof(Persona));
    archivoEscritura.close();
}

int main()
{
    Persona persona;

    while (true)
    {
        // Ingresar informaci�n de la persona
        cout << "Ingrese el nombre (o espacio para finalizar): ";
        cin.getline(persona.nombre, 31);

        // Verificar si se debe finalizar el programa
        if (strlen(persona.nombre) == 0 || persona.nombre[0] == ' ')
            break;

        cout << "Ingrese la edad: ";
        cin >> persona.edad;

        cout << "Ingrese el sexo (M/F): ";
        cin >> persona.sexo;

        cout << "Ingrese la fecha de nacimiento (dd/mm/yyyy): ";
        cin >> persona.fechaNacimiento;

        // Limpiar el buffer despu�s de leer el sexo
        cin.ignore();

        // Escribir la informaci�n en el archivo binario
        escribirArchivoBinario(persona);
    }

    cout << "Proceso finalizado. Se ha creado el archivo 'PERSONAS.BIN'." << endl;

    return 0;
}
