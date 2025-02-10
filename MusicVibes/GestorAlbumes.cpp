// src/GestorAlbumes.cpp
#include <iostream>
#include <vector>
#include <cstdlib>    // Para system("cls") o system("clear")
#include "GestorAlbumes.h"
#include "AVL.h"
#include "Clases.h"

// Se asume que la variable global "arbol" esta declarada en main.cpp (o en un archivo de cabecera comun)
// Si lo prefieres, puedes declararla como extern:
extern AVL arbol;
extern void guardarDatos();  // Declaracion de la funcion de guardado (definida en main.cpp)

void gestionarAlbumes() {
    int opcion;
    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        std::cout << "\033[1;36m===== Gestion de Albumes =====\033[0m\n";
        std::cout << "\033[1;33m1. Agregar Album\033[0m\n";
        std::cout << "\033[1;33m2. Eliminar Album\033[0m\n";
        std::cout << "\033[1;33m3. Ver Albumes\033[0m\n";
        std::cout << "\033[1;33m0. Volver\033[0m\n";
        std::cout << "\033[1;32mSeleccione una opcion: \033[0m";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: agregarAlbum(); break;
            case 2: eliminarAlbum(); break;
            case 3: verAlbumes(); break;
            case 0: break;
            default: std::cout << "\033[1;31mOpcion no valida.\033[0m\n";
        }
    } while (opcion != 0);
}

void agregarAlbum() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    Album* nuevo = new Album();
    
    std::cout << "\033[1;36m=== Agregar Album ===\033[0m\n";
    std::cout << "\033[1;33mTitulo del album: \033[0m";
    std::getline(std::cin, nuevo->titulo);
    std::cout << "\033[1;33mNombre artistico: \033[0m";
    std::getline(std::cin, nuevo->nombreArtistico);
    std::cout << "\033[1;33mPais de grabacion del album: \033[0m";
    std::getline(std::cin, nuevo->paisGrabacion);
    std::cout << "\033[1;33mAnio de publicacion: \033[0m";
    std::cin >> nuevo->anioPublicacion;
    std::cin.ignore();
    std::cout << "\033[1;33mCover Art (nombre del encargado de la portada): \033[0m";
    std::getline(std::cin, nuevo->encargadoCoverArt);
    std::cout << "\033[1;33mFotografia (nombre del encargado de la fotografia): \033[0m";
    std::getline(std::cin, nuevo->encargadoFotografia);
    std::cout << "\033[1;33mEditora (a la que pertenecen los derechos): \033[0m";
    std::getline(std::cin, nuevo->editora);
    std::cout << "\033[1;33mEstudio de Grabacion: \033[0m";
    std::getline(std::cin, nuevo->estudioGrabacion);
    std::cout << "\033[1;33mCiudad de grabacion del album: \033[0m";
    std::getline(std::cin, nuevo->ciudadGrabacion);
    
    int numLinks;
    std::cout << "\033[1;33mNumero de links del album: \033[0m";
    std::cin >> numLinks;
    std::cin.ignore();
    for (int i = 0; i < numLinks; i++) {
        EnlacePlataforma ep;
        std::cout << "\033[1;33m  Link " << (i+1) << " - Nombre de la plataforma: \033[0m";
        std::getline(std::cin, ep.nombrePlataforma);
        std::cout << "\033[1;33m  Link " << (i+1) << " - URL: \033[0m";
        std::getline(std::cin, ep.link);
        nuevo->enlacesAlbum.push_back(ep);
    }
    
    arbol.insertar(nuevo);
    guardarDatos();
    std::cout << "\033[1;32mAlbum agregado con exito.\033[0m\n";
}

void eliminarAlbum() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    std::string titulo;
    std::cout << "\033[1;33mTitulo del album a eliminar: \033[0m";
    std::getline(std::cin, titulo);
    
    Album* album = arbol.buscarAlbum(titulo);
    if (!album) {
        std::cout << "\033[1;31mAlbum no encontrado.\033[0m\n";
        return;
    }
    
    arbol.eliminarAlbum(titulo);
    guardarDatos();
    std::cout << "\033[1;32mAlbum eliminado.\033[0m\n";
}

void verAlbumes() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    std::cout << "\033[1;36m===== Albumes =====\033[0m\n";
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    for (Album* a : albumes) {
        std::cout << "\033[1;33mAlbum: \033[0m" << a->titulo 
                  << " \033[1;33m| Artista: \033[0m" << a->nombreArtistico 
                  << " \033[1;33m| Anio: \033[0m" << a->anioPublicacion << "\n";
    }
    std::cout << "\n\033[1;32mPresione Enter para continuar...\033[0m";
    std::cin.get();
}

