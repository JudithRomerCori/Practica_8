// Materia: Programación I, Paralelo 1

// Autor: Judith Marisol Romero Cori

// Fecha creación: 20/11/2023

// Fecha modificación: 25/11/2023

// Número de ejericio: 3

// Problema planteado:Amplíe el programa anterior que procesa clientes de una agencia matrimonial para que tome
//los datos de todos los candidatos a estudiar del fichero PERSONAS.DAT del ejercicio anterior,
//lea el cliente del teclado y finalmente genere como resultado un listado por pantalla con los
//nombres de los candidatos aceptados y un fichero llamado ACEPTADOS.DAT con toda la
//información correspondiente a los candidatos aceptados.
//Una persona del fichero PERSONAS.DAT se considerará aceptable como candidato si tiene
//diferente sexo y que haya nacido en el mes y año (El programa debe ser capaz de trabajar con
//cualquier número de personas en el fichero PERSONAS.DAT).
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

const char* NOMBRE_ARCHIVO_ENTRADA = "PERSONAS.BIN";
const char* NOMBRE_ARCHIVO_SALIDA = "ACEPTADOS.DAT";

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

    if (!archivoEscritura.is_open())
    {
        cout << "No se pudo abrir el archivo para escritura." << endl;
        return;
    }

    archivoEscritura.write(reinterpret_cast<const char*>(&persona), sizeof(Persona));

    archivoEscritura.close();
}

bool esAceptable(const Persona& persona)
{
    // Obtener la fecha actual para comparar con la fecha de nacimiento
    time_t tiempoActual = time(nullptr);
    tm* fechaActual = localtime(&tiempoActual);

    // Obtener el mes y el año de la fecha de nacimiento
    int mesNacimiento, anioNacimiento;
    sscanf(persona.fechaNacimiento, "%d/%*d/%d", &mesNacimiento, &anioNacimiento);

    // Verificar si el sexo es diferente y la persona nació en el mismo año y mes actual
    return (persona.sexo != 'M' && persona.sexo != 'F') ||
           (persona.sexo != 'M' && mesNacimiento == fechaActual->tm_mon + 1 && anioNacimiento == fechaActual->tm_year + 1900);
}

void procesarCandidatos()
{
    ifstream archivoEntrada(NOMBRE_ARCHIVO_ENTRADA);
    ofstream archivoSalida(NOMBRE_ARCHIVO_SALIDA, ios::binary);

    if (!archivoEntrada.is_open() || !archivoSalida.is_open())
    {
        cout << "Error al abrir los archivos." << endl;
        return;
    }

    Persona candidato;

    cout << "Candidatos aceptados:" << endl;

    while (archivoEntrada.read(reinterpret_cast<char*>(&candidato), sizeof(Persona)))
    {
        if (esAceptable(candidato))
        {
            cout << candidato.nombre << endl;
            escribirArchivoBinario(candidato, NOMBRE_ARCHIVO_SALIDA);
        }
    }

    archivoEntrada.close();
    archivoSalida.close();
}

int main()
{
    procesarCandidatos();

    return 0;
}


