// src/main.cpp
#include <iostream>
#include "GestorAlbumes.h"
#include "GestorCanciones.h"
#include "Consultas.h"
#include "AVL.h"
#include "Clases.h"

// Declaraci�n de la variable global del �rbol AVL y el nombre del archivo de datos
AVL arbol;
const std::string ARCHIVO_DATOS = "musica.txt";

// Funciones de utilidad para archivo
bool archivoExiste(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    return archivo.good();
}

bool archivoVacio(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo, std::ios::ate);
    return archivo.tellg() == 0;
}

void guardarDatos() {
    if (!archivoExiste(ARCHIVO_DATOS)) {
        std::cout << "Creando nuevo archivo de datos...\n";
    }
    arbol.guardar(ARCHIVO_DATOS);
    std::cout << "Datos guardados correctamente.\n";
}

void cargarDatos() {
    if (archivoExiste(ARCHIVO_DATOS) && !archivoVacio(ARCHIVO_DATOS)) {
        arbol.liberarArbol(); // Liberar memoria antes de cargar
        arbol.cargar(ARCHIVO_DATOS);
        std::cout << "Datos cargados correctamente.\n";
    } else {
        std::cout << "No se encontr� un archivo de datos o est� vac�o. Se crear� uno nuevo al guardar.\n";
    }
}

void mostrarMenuPrincipal() {
    std::cout << "\n===== Men� Principal =====\n";
    std::cout << "1. Gestionar �lbumes\n";
    std::cout << "2. Gestionar Canciones\n";
    std::cout << "3. Realizar Consultas\n";
    std::cout << "0. Salir\n";
}

int main() {
    cargarDatos(); // Cargar datos al iniciar el programa

    int opcion;
    do {
        mostrarMenuPrincipal();
        std::cout << "Seleccione una opci�n: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: gestionarAlbumes(); break;
            case 2: gestionarCanciones(); break;
            case 3: realizarConsultas(); break;
            case 0: std::cout << "Cerrando programa...\n"; break;
            default: std::cout << "Opci�n no v�lida.\n";
        }
    } while (opcion != 0);

    guardarDatos(); // Guardar datos al cerrar el programa
    return 0;
}

