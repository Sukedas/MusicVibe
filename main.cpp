#include <iostream>
#include <cstdlib>   // Para system()
#include <fstream>   // Para manejo de archivos
#include "GestorAlbumes.h"
#include "GestorCanciones.h"
#include "Consultas.h"
#include "AVL.h"
#include "Clases.h"

// Declaracion de la variable global del arbol AVL y el nombre del archivo de datos
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
        std::cout << "No se encontro un archivo de datos o esta vacio. Se creara uno nuevo al guardar.\n";
    }
}

void mostrarMenuPrincipal() {
    // Limpieza de pantalla (compatible con Windows y Linux/Mac)
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    // Menu con colores: titulo en cian brillante y opciones en amarillo brillante.
    std::cout << "\033[1;36m===== Menu Principal =====\033[0m\n";
    std::cout << "\033[1;33m1. Gestionar Albumes\033[0m\n";
    std::cout << "\033[1;33m2. Gestionar Canciones\033[0m\n";
    std::cout << "\033[1;33m3. Realizar Consultas\033[0m\n";
    std::cout << "\033[1;33m0. Salir\033[0m\n";
}

int main() {
    cargarDatos(); // Cargar datos al iniciar el programa

    int opcion;
    do {
        mostrarMenuPrincipal();
        std::cout << "\033[1;32mSeleccione una opcion: \033[0m";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: gestionarAlbumes(); break;
            case 2: gestionarCanciones(); break;
            case 3: realizarConsultas(); break;
            case 0: std::cout << "Cerrando programa...\n"; break;
            default: std::cout << "\033[1;31mOpcion no valida.\033[0m\n";
        }
    } while (opcion != 0);

    guardarDatos(); // Guardar datos al cerrar el programa
    return 0;
}

