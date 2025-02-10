// src/GestorCanciones.cpp
#include <iostream>
#include <sstream>
#include "GestorCanciones.h"
#include "AVL.h"
#include "Clases.h"

extern AVL arbol;
extern void guardarDatos();

void gestionarCanciones() {
    int opcion;
    do {
        std::cout << "\n===== Gestión de Canciones =====\n";
        std::cout << "1. Agregar Canción\n";
        std::cout << "2. Eliminar Canción\n";
        std::cout << "3. Ver Canciones\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: agregarCancion(); break;
            case 2: eliminarCancion(); break;
            case 3: verCanciones(); break;
            case 0: break;
            default: std::cout << "Opción no válida.\n";
        }
    } while (opcion != 0);
}

void agregarCancion() {
    std::cout << "=== Agregar Canción ===\n";
    
    std::string albumTitulo;
    std::cout << "Ingrese el título del álbum destino: ";
    std::getline(std::cin, albumTitulo);
    
    Album* album = arbol.buscarAlbum(albumTitulo);
    if (!album) {
        std::cout << "Álbum no encontrado.\n";
        return;
    }
    
    Cancion* nueva = new Cancion();
    std::cout << "Nombre de la canción: ";
    std::getline(std::cin, nueva->nombreCancion);
    
    std::string duracionStr;
    std::cout << "Duración (HH:MM:SS): ";
    std::getline(std::cin, duracionStr);
    int horas, minutos, segundos;
    char sep;
    std::istringstream iss(duracionStr);
    iss >> horas >> sep >> minutos >> sep >> segundos;
    nueva->duracion = horas * 3600 + minutos * 60 + segundos;
    
    std::string ciudadGrabacion, paisGrabacion, genero;
    int anioGrabacion;
    std::cout << "Ciudad de grabación: ";
    std::getline(std::cin, ciudadGrabacion);
    std::cout << "País de grabación: ";
    std::getline(std::cin, paisGrabacion);
    std::cout << "Año de la primera publicación de la canción: ";
    std::cin >> anioGrabacion;
    std::cin.ignore();
    std::cout << "Género: ";
    std::getline(std::cin, genero);
    nueva->anioGrabacion = anioGrabacion;
    nueva->genero = genero;
    // (Si se requieren más datos en Cancion, se deben ampliar en Clases.h)
    
    int numArtistas;
    std::cout << "Número de artistas participantes: ";
    std::cin >> numArtistas;
    std::cin.ignore();
    for (int i = 0; i < numArtistas; i++) {
        Artista artista;
        std::cout << "Datos del artista " << i+1 << ":\n";
        std::cout << "  Nombre real: ";
        std::getline(std::cin, artista.nombreReal);
        std::cout << "  Nombre artístico: ";
        std::getline(std::cin, artista.nombreArtistico);
        std::cout << "  País de origen: ";
        std::getline(std::cin, artista.paisOrigen);
        std::cout << "  Instrumento que interpreta: ";
        std::getline(std::cin, artista.instrumento);
        std::cout << "  Rol (ej. compositor letra, compositor música, arreglista, etc.): ";
        std::getline(std::cin, artista.rol);
        nueva->artistas.push_back(artista);
    }
    
    int numLinks;
    std::cout << "Número de links de la canción: ";
    std::cin >> numLinks;
    std::cin.ignore();
    for (int i = 0; i < numLinks; i++) {
        EnlacePlataforma ep;
        std::cout << "  Link " << (i+1) << " - Nombre de la plataforma: ";
        std::getline(std::cin, ep.nombrePlataforma);
        std::cout << "  Link " << (i+1) << " - URL: ";
        std::getline(std::cin, ep.link);
        nueva->enlaces.push_back(ep);
    }
    
    int numVersiones;
    std::cout << "Número de versiones: ";
    std::cin >> numVersiones;
    std::cin.ignore();
    for (int i = 0; i < numVersiones; ++i) {
        Version version;
        std::cout << "Datos de la versión " << i+1 << ":\n";
        std::cout << "  Título de la versión: ";
        std::getline(std::cin, version.tituloVersion);
        std::cout << "  Tipo de versión (ej. Remix, Directo, etc.): ";
        std::getline(std::cin, version.tipoVersion);
        std::cout << "  Artista principal: ";
        std::getline(std::cin, version.artistaPrincipal);
        std::cout << "  Ciudad de grabación de la versión: ";
        std::string ciudadV;
        std::getline(std::cin, ciudadV);
        // (Si se desea almacenar, se podría ampliar la clase Version)
        std::cout << "  País de grabación de la versión: ";
        std::string paisV;
        std::getline(std::cin, paisV);
        version.paisPublicacion = paisV;
        std::cout << "  Género de la versión: ";
        std::getline(std::cin, version.genero);
        std::cout << "  Año de publicación de la versión: ";
        std::cin >> version.anioPublicacion;
        std::cin.ignore();
        
        int numLinksVersion;
        std::cout << "  Número de links de la versión: ";
        std::cin >> numLinksVersion;
        std::cin.ignore();
        for (int j = 0; j < numLinksVersion; j++) {
            EnlacePlataforma ep;
            std::cout << "    Link " << (j+1) << " - Nombre de la plataforma: ";
            std::getline(std::cin, ep.nombrePlataforma);
            std::cout << "    Link " << (j+1) << " - URL: ";
            std::getline(std::cin, ep.link);
            version.enlaces.push_back(ep);
        }
        nueva->versiones.push_back(version);
    }
    
    // Vincular la canción al final de la lista enlazada del álbum.
    if (!album->listaCanciones)
        album->listaCanciones = nueva;
    else {
        Cancion* actual = album->listaCanciones;
        while (actual->siguiente)
            actual = actual->siguiente;
        actual->siguiente = nueva;
    }
    
    guardarDatos();
    std::cout << "Canción agregada con éxito.\n";
}

void eliminarCancion() {
    std::string tituloAlbum, nombreCancion;
    std::cout << "Título del álbum: ";
    std::getline(std::cin, tituloAlbum);
    std::cout << "Nombre de la canción: ";
    std::getline(std::cin, nombreCancion);
    
    Album* album = arbol.buscarAlbum(tituloAlbum);
    if (!album) {
        std::cout << "Álbum no encontrado.\n";
        return;
    }
    
    Cancion* actual = album->listaCanciones;
    Cancion* anterior = nullptr;
    while (actual && actual->nombreCancion != nombreCancion) {
        anterior = actual;
        actual = actual->siguiente;
    }
    
    if (!actual) {
        std::cout << "Canción no encontrada.\n";
        return;
    }
    
    if (!anterior)
        album->listaCanciones = actual->siguiente;
    else
        anterior->siguiente = actual->siguiente;
    
    delete actual;
    guardarDatos();
    std::cout << "Canción eliminada con éxito.\n";
}

void verCanciones() {
    std::string tituloAlbum;
    std::cout << "Título del álbum: ";
    std::getline(std::cin, tituloAlbum);
    
    Album* album = arbol.buscarAlbum(tituloAlbum);
    if (!album) {
        std::cout << "Álbum no encontrado.\n";
        return;
    }
    
    Cancion* actual = album->listaCanciones;
    while (actual) {
        std::cout << "Canción: " << actual->nombreCancion 
                  << " | Duración: " << actual->duracion << "s\n";
        actual = actual->siguiente;
    }
}

