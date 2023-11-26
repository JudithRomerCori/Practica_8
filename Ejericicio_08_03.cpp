// Materia: Programaci�n I, Paralelo 1

// Autor: Judith Marisol Romero Cori

// Fecha creaci�n: 20/11/2023

// Fecha modificaci�n: 25/11/2023

// N�mero de ejericio: 3

// Problema planteado:Ampl�e el programa anterior que procesa clientes de una agencia matrimonial para que tome
//los datos de todos los candidatos a estudiar del fichero PERSONAS.DAT del ejercicio anterior,
//lea el cliente del teclado y finalmente genere como resultado un listado por pantalla con los
//nombres de los candidatos aceptados y un fichero llamado ACEPTADOS.DAT con toda la
//informaci�n correspondiente a los candidatos aceptados.
//Una persona del fichero PERSONAS.DAT se considerar� aceptable como candidato si tiene
//diferente sexo y que haya nacido en el mes y a�o (El programa debe ser capaz de trabajar con
//cualquier n�mero de personas en el fichero PERSONAS.DAT).
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char* NOMBRE_ARCHIVO_PERSONAS = "PERSONAS.BIN";
const char* NOMBRE_ARCHIVO_ACEPTADOS = "ACEPTADOS.BIN";

struct Persona
{
    char nombre[31];
    int edad;
    char sexo;
    char fechaNacimiento[11];
};

void escribirArchivoBinario(const Persona& persona, const char* nombreArchivo)
{
    ofstream archivoEscritura;
    archivoEscritura.open(nombreArchivo, ios::app | ios::binary);
    archivoEscritura.write(reinterpret_cast<const char*>(&persona), sizeof(Persona));
    archivoEscritura.close();
}

void procesarCandidatos()
{
    ifstream archivoPersonas;
    Persona persona;

    archivoPersonas.open(NOMBRE_ARCHIVO_PERSONAS, ios::in | ios::binary);

    if (!archivoPersonas.is_open())
    {
        cout << "No se pudo abrir el archivo de personas." << endl;
        return;
    }

    cout << "\nCandidatos aceptados:" << endl;

    while (archivoPersonas.read(reinterpret_cast<char*>(&persona), sizeof(Persona)))
    {
        // Verificar si la persona es un candidato aceptado
        if (persona.sexo != 'M' && persona.sexo != 'F')
        {
            cout << "Error: Sexo no v�lido para " << persona.nombre << endl;
            continue;
        }

        // Obtener el mes y a�o de nacimiento
        int mes, anno;
        sscanf(persona.fechaNacimiento, "%*d/%d/%d", &mes, &anno);

        // Verificar si es un candidato aceptado
        if (mes % 2 == 0 && anno % 2 != 0)
        {
            cout << "Nombre: " << persona.nombre << ", Edad: " << persona.edad << ", Sexo: " << persona.sexo << ", Fecha Nacimiento: " << persona.fechaNacimiento << endl;

            // Escribir la informaci�n en el archivo de aceptados
            escribirArchivoBinario(persona, NOMBRE_ARCHIVO_ACEPTADOS);
        }
    }

    archivoPersonas.close();
}

int main()
{
    // C�digo para ingresar personas al archivo PERSONAS.BIN (del ejercicio anterior)

    // Llamada para procesar candidatos y generar archivo de aceptados
    procesarCandidatos();

    return 0;
}

