// src/GestorCanciones.cpp
#include <iostream>
#include <sstream>
#include <cstdlib>    // Para system("cls") o system("clear")
#include "GestorCanciones.h"
#include "AVL.h"
#include "Clases.h"

extern AVL arbol;
extern void guardarDatos();

void gestionarCanciones() {
    int opcion;
    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        std::cout << "\033[1;36m===== Gestion de Canciones =====\033[0m\n";
        std::cout << "\033[1;33m1. Agregar Cancion\033[0m\n";
        std::cout << "\033[1;33m2. Eliminar Cancion\033[0m\n";
        std::cout << "\033[1;33m3. Ver Canciones\033[0m\n";
        std::cout << "\033[1;33m0. Volver\033[0m\n";
        std::cout << "\033[1;32mSeleccione una opcion: \033[0m";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: agregarCancion(); break;
            case 2: eliminarCancion(); break;
            case 3: verCanciones(); break;
            case 0: break;
            default: std::cout << "\033[1;31mOpcion no valida.\033[0m\n";
        }
    } while (opcion != 0);
}

void agregarCancion() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    std::cout << "\033[1;36m=== Agregar Cancion ===\033[0m\n";
    
    std::string albumTitulo;
    std::cout << "\033[1;33mIngrese el titulo del album destino: \033[0m";
    std::getline(std::cin, albumTitulo);
    
    Album* album = arbol.buscarAlbum(albumTitulo);
    if (!album) {
        std::cout << "\033[1;31mAlbum no encontrado.\033[0m\n";
        return;
    }
    
    Cancion* nueva = new Cancion();
    std::cout << "\033[1;33mNombre de la cancion: \033[0m";
    std::getline(std::cin, nueva->nombreCancion);
    
    std::string duracionStr;
    std::cout << "\033[1;33mDuracion (HH:MM:SS): \033[0m";
    std::getline(std::cin, duracionStr);
    int horas, minutos, segundos;
    char sep;
    std::istringstream iss(duracionStr);
    iss >> horas >> sep >> minutos >> sep >> segundos;
    nueva->duracion = horas * 3600 + minutos * 60 + segundos;
    
    std::string ciudadGrabacion, paisGrabacion, genero;
    int anioGrabacion;
    std::cout << "\033[1;33mCiudad de grabacion: \033[0m";
    std::getline(std::cin, ciudadGrabacion);
    std::cout << "\033[1;33mPais de grabacion: \033[0m";
    std::getline(std::cin, paisGrabacion);
    std::cout << "\033[1;33mAnio de la primera publicacion de la cancion: \033[0m";
    std::cin >> anioGrabacion;
    std::cin.ignore();
    std::cout << "\033[1;33mGenero: \033[0m";
    std::getline(std::cin, genero);
    nueva->anioGrabacion = anioGrabacion;
    nueva->genero = genero;
    // (Si se requieren mas datos en Cancion, se deben ampliar en Clases.h)
    
    int numArtistas;
    std::cout << "\033[1;33mNumero de artistas participantes: \033[0m";
    std::cin >> numArtistas;
    std::cin.ignore();
    for (int i = 0; i < numArtistas; i++) {
        Artista artista;
        std::cout << "\033[1;33mDatos del artista " << i+1 << ":\033[0m\n";
        std::cout << "\033[1;33m  Nombre real: \033[0m";
        std::getline(std::cin, artista.nombreReal);
        std::cout << "\033[1;33m  Nombre artistico: \033[0m";
        std::getline(std::cin, artista.nombreArtistico);
        std::cout << "\033[1;33m  Pais de origen: \033[0m";
        std::getline(std::cin, artista.paisOrigen);
        std::cout << "\033[1;33m  Instrumento que interpreta: \033[0m";
        std::getline(std::cin, artista.instrumento);
        std::cout << "\033[1;33m  Rol (ej. compositor letra, compositor musica, arreglista, etc.): \033[0m";
        std::getline(std::cin, artista.rol);
        nueva->artistas.push_back(artista);
    }
    
    int numLinks;
    std::cout << "\033[1;33mNumero de links de la cancion: \033[0m";
    std::cin >> numLinks;
    std::cin.ignore();
    for (int i = 0; i < numLinks; i++) {
        EnlacePlataforma ep;
        std::cout << "\033[1;33m  Link " << (i+1) << " - Nombre de la plataforma: \033[0m";
        std::getline(std::cin, ep.nombrePlataforma);
        std::cout << "\033[1;33m  Link " << (i+1) << " - URL: \033[0m";
        std::getline(std::cin, ep.link);
        nueva->enlaces.push_back(ep);
    }
    
    int numVersiones;
    std::cout << "\033[1;33mNumero de versiones: \033[0m";
    std::cin >> numVersiones;
    std::cin.ignore();
    for (int i = 0; i < numVersiones; ++i) {
        Version version;
        std::cout << "\033[1;33mDatos de la version " << i+1 << ":\033[0m\n";
        std::cout << "\033[1;33m  Titulo de la version: \033[0m";
        std::getline(std::cin, version.tituloVersion);
        std::cout << "\033[1;33m  Tipo de version (ej. Remix, Directo, etc.): \033[0m";
        std::getline(std::cin, version.tipoVersion);
        std::cout << "\033[1;33m  Artista principal: \033[0m";
        std::getline(std::cin, version.artistaPrincipal);
        std::cout << "\033[1;33m  Ciudad de grabacion de la version: \033[0m";
        std::string ciudadV;
        std::getline(std::cin, ciudadV);
        // (Si se desea almacenar, se podria ampliar la clase Version)
        std::cout << "\033[1;33m  Pais de grabacion de la version: \033[0m";
        std::string paisV;
        std::getline(std::cin, paisV);
        version.paisPublicacion = paisV;
        std::cout << "\033[1;33m  Genero de la version: \033[0m";
        std::getline(std::cin, version.genero);
        std::cout << "\033[1;33m  Anio de publicacion de la version: \033[0m";
        std::cin >> version.anioPublicacion;
        std::cin.ignore();
        
        int numLinksVersion;
        std::cout << "\033[1;33m  Numero de links de la version: \033[0m";
        std::cin >> numLinksVersion;
        std::cin.ignore();
        for (int j = 0; j < numLinksVersion; j++) {
            EnlacePlataforma ep;
            std::cout << "\033[1;33m    Link " << (j+1) << " - Nombre de la plataforma: \033[0m";
            std::getline(std::cin, ep.nombrePlataforma);
            std::cout << "\033[1;33m    Link " << (j+1) << " - URL: \033[0m";
            std::getline(std::cin, ep.link);
            version.enlaces.push_back(ep);
        }
        nueva->versiones.push_back(version);
    }
    
    // Vincular la cancion al final de la lista enlazada del album.
    if (!album->listaCanciones)
        album->listaCanciones = nueva;
    else {
        Cancion* actual = album->listaCanciones;
        while (actual->siguiente)
            actual = actual->siguiente;
        actual->siguiente = nueva;
    }
    
    guardarDatos();
    std::cout << "\033[1;32mCancion agregada con exito.\033[0m\n";
}

void eliminarCancion() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    std::string tituloAlbum, nombreCancion;
    std::cout << "\033[1;33mTitulo del album: \033[0m";
    std::getline(std::cin, tituloAlbum);
    std::cout << "\033[1;33mNombre de la cancion: \033[0m";
    std::getline(std::cin, nombreCancion);
    
    Album* album = arbol.buscarAlbum(tituloAlbum);
    if (!album) {
        std::cout << "\033[1;31mAlbum no encontrado.\033[0m\n";
        return;
    }
    
    Cancion* actual = album->listaCanciones;
    Cancion* anterior = nullptr;
    while (actual && actual->nombreCancion != nombreCancion) {
        anterior = actual;
        actual = actual->siguiente;
    }
    
    if (!actual) {
        std::cout << "\033[1;31mCancion no encontrada.\033[0m\n";
        return;
    }
    
    if (!anterior)
        album->listaCanciones = actual->siguiente;
    else
        anterior->siguiente = actual->siguiente;
    
    delete actual;
    guardarDatos();
    std::cout << "\033[1;32mCancion eliminada con exito.\033[0m\n";
}

void verCanciones() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    std::string tituloAlbum;
    std::cout << "\033[1;33mTitulo del album: \033[0m";
    std::getline(std::cin, tituloAlbum);
    
    Album* album = arbol.buscarAlbum(tituloAlbum);
    if (!album) {
        std::cout << "\033[1;31mAlbum no encontrado.\033[0m\n";
        return;
    }
    
    Cancion* actual = album->listaCanciones;
    std::cout << "\033[1;36m===== Canciones =====\033[0m\n";
    while (actual) {
        std::cout << "\033[1;33mCancion: \033[0m" << actual->nombreCancion 
                  << " \033[1;33m| Duracion: \033[0m" << actual->duracion << "s\n";
        actual = actual->siguiente;
    }
    std::cout << "\n\033[1;32mPresione Enter para continuar...\033[0m";
    std::cin.get();
}

