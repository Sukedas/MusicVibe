// src/GestorAlbumes.cpp
#include <iostream>
#include <vector>
#include "GestorAlbumes.h"
#include "AVL.h"
#include "Clases.h"

// Se asume que la variable global "arbol" está declarada en main.cpp (o en un archivo de cabecera común)
// Si lo prefieres, puedes declararla como extern:
extern AVL arbol;
extern void guardarDatos();  // Declaración de la función de guardado (definida en main.cpp)

void gestionarAlbumes() {
    int opcion;
    do {
        std::cout << "\n===== Gestión de Álbumes =====\n";
        std::cout << "1. Agregar Álbum\n";
        std::cout << "2. Eliminar Álbum\n";
        std::cout << "3. Ver Álbumes\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: agregarAlbum(); break;
            case 2: eliminarAlbum(); break;
            case 3: verAlbumes(); break;
            case 0: break;
            default: std::cout << "Opción no válida.\n";
        }
    } while (opcion != 0);
}

void agregarAlbum() {
    Album* nuevo = new Album();
    
    std::cout << "=== Agregar Álbum ===\n";
    std::cout << "Título del álbum: ";
    std::getline(std::cin, nuevo->titulo);
    std::cout << "Nombre artístico: ";
    std::getline(std::cin, nuevo->nombreArtistico);
    std::cout << "País de grabación del álbum: ";
    std::getline(std::cin, nuevo->paisGrabacion);
    std::cout << "Año de publicación: ";
    std::cin >> nuevo->anioPublicacion;
    std::cin.ignore();
    std::cout << "Cover Art (nombre del encargado de la portada): ";
    std::getline(std::cin, nuevo->encargadoCoverArt);
    std::cout << "Fotografía (nombre del encargado de la fotografía): ";
    std::getline(std::cin, nuevo->encargadoFotografia);
    std::cout << "Editora (a la que pertenecen los derechos): ";
    std::getline(std::cin, nuevo->editora);
    std::cout << "Estudio de Grabación: ";
    std::getline(std::cin, nuevo->estudioGrabacion);
    std::cout << "Ciudad de grabación del álbum: ";
    std::getline(std::cin, nuevo->ciudadGrabacion);
    
    int numLinks;
    std::cout << "Número de links del álbum: ";
    std::cin >> numLinks;
    std::cin.ignore();
    for (int i = 0; i < numLinks; i++) {
        EnlacePlataforma ep;
        std::cout << "  Link " << (i+1) << " - Nombre de la plataforma: ";
        std::getline(std::cin, ep.nombrePlataforma);
        std::cout << "  Link " << (i+1) << " - URL: ";
        std::getline(std::cin, ep.link);
        nuevo->enlacesAlbum.push_back(ep);
    }
    
    arbol.insertar(nuevo);
    guardarDatos();
    std::cout << "Álbum agregado con éxito.\n";
}

void eliminarAlbum() {
    std::string titulo;
    std::cout << "Título del álbum a eliminar: ";
    std::getline(std::cin, titulo);
    
    Album* album = arbol.buscarAlbum(titulo);
    if (!album) {
        std::cout << "Álbum no encontrado.\n";
        return;
    }
    
    arbol.eliminarAlbum(titulo);
    guardarDatos();
    std::cout << "Álbum eliminado.\n";
}

void verAlbumes() {
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    for (Album* a : albumes) {
        std::cout << "Álbum: " << a->titulo 
                  << " | Artista: " << a->nombreArtistico 
                  << " | Año: " << a->anioPublicacion << "\n";
    }
}

