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
        std::cout << "\n===== Gesti�n de Canciones =====\n";
        std::cout << "1. Agregar Canci�n\n";
        std::cout << "2. Eliminar Canci�n\n";
        std::cout << "3. Ver Canciones\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opci�n: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: agregarCancion(); break;
            case 2: eliminarCancion(); break;
            case 3: verCanciones(); break;
            case 0: break;
            default: std::cout << "Opci�n no v�lida.\n";
        }
    } while (opcion != 0);
}

void agregarCancion() {
    std::cout << "=== Agregar Canci�n ===\n";
    
    std::string albumTitulo;
    std::cout << "Ingrese el t�tulo del �lbum destino: ";
    std::getline(std::cin, albumTitulo);
    
    Album* album = arbol.buscarAlbum(albumTitulo);
    if (!album) {
        std::cout << "�lbum no encontrado.\n";
        return;
    }
    
    Cancion* nueva = new Cancion();
    std::cout << "Nombre de la canci�n: ";
    std::getline(std::cin, nueva->nombreCancion);
    
    std::string duracionStr;
    std::cout << "Duraci�n (HH:MM:SS): ";
    std::getline(std::cin, duracionStr);
    int horas, minutos, segundos;
    char sep;
    std::istringstream iss(duracionStr);
    iss >> horas >> sep >> minutos >> sep >> segundos;
    nueva->duracion = horas * 3600 + minutos * 60 + segundos;
    
    std::string ciudadGrabacion, paisGrabacion, genero;
    int anioGrabacion;
    std::cout << "Ciudad de grabaci�n: ";
    std::getline(std::cin, ciudadGrabacion);
    std::cout << "Pa�s de grabaci�n: ";
    std::getline(std::cin, paisGrabacion);
    std::cout << "A�o de la primera publicaci�n de la canci�n: ";
    std::cin >> anioGrabacion;
    std::cin.ignore();
    std::cout << "G�nero: ";
    std::getline(std::cin, genero);
    nueva->anioGrabacion = anioGrabacion;
    nueva->genero = genero;
    // (Si se requieren m�s datos en Cancion, se deben ampliar en Clases.h)
    
    int numArtistas;
    std::cout << "N�mero de artistas participantes: ";
    std::cin >> numArtistas;
    std::cin.ignore();
    for (int i = 0; i < numArtistas; i++) {
        Artista artista;
        std::cout << "Datos del artista " << i+1 << ":\n";
        std::cout << "  Nombre real: ";
        std::getline(std::cin, artista.nombreReal);
        std::cout << "  Nombre art�stico: ";
        std::getline(std::cin, artista.nombreArtistico);
        std::cout << "  Pa�s de origen: ";
        std::getline(std::cin, artista.paisOrigen);
        std::cout << "  Instrumento que interpreta: ";
        std::getline(std::cin, artista.instrumento);
        std::cout << "  Rol (ej. compositor letra, compositor m�sica, arreglista, etc.): ";
        std::getline(std::cin, artista.rol);
        nueva->artistas.push_back(artista);
    }
    
    int numLinks;
    std::cout << "N�mero de links de la canci�n: ";
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
    std::cout << "N�mero de versiones: ";
    std::cin >> numVersiones;
    std::cin.ignore();
    for (int i = 0; i < numVersiones; ++i) {
        Version version;
        std::cout << "Datos de la versi�n " << i+1 << ":\n";
        std::cout << "  T�tulo de la versi�n: ";
        std::getline(std::cin, version.tituloVersion);
        std::cout << "  Tipo de versi�n (ej. Remix, Directo, etc.): ";
        std::getline(std::cin, version.tipoVersion);
        std::cout << "  Artista principal: ";
        std::getline(std::cin, version.artistaPrincipal);
        std::cout << "  Ciudad de grabaci�n de la versi�n: ";
        std::string ciudadV;
        std::getline(std::cin, ciudadV);
        // (Si se desea almacenar, se podr�a ampliar la clase Version)
        std::cout << "  Pa�s de grabaci�n de la versi�n: ";
        std::string paisV;
        std::getline(std::cin, paisV);
        version.paisPublicacion = paisV;
        std::cout << "  G�nero de la versi�n: ";
        std::getline(std::cin, version.genero);
        std::cout << "  A�o de publicaci�n de la versi�n: ";
        std::cin >> version.anioPublicacion;
        std::cin.ignore();
        
        int numLinksVersion;
        std::cout << "  N�mero de links de la versi�n: ";
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
    
    // Vincular la canci�n al final de la lista enlazada del �lbum.
    if (!album->listaCanciones)
        album->listaCanciones = nueva;
    else {
        Cancion* actual = album->listaCanciones;
        while (actual->siguiente)
            actual = actual->siguiente;
        actual->siguiente = nueva;
    }
    
    guardarDatos();
    std::cout << "Canci�n agregada con �xito.\n";
}

void eliminarCancion() {
    std::string tituloAlbum, nombreCancion;
    std::cout << "T�tulo del �lbum: ";
    std::getline(std::cin, tituloAlbum);
    std::cout << "Nombre de la canci�n: ";
    std::getline(std::cin, nombreCancion);
    
    Album* album = arbol.buscarAlbum(tituloAlbum);
    if (!album) {
        std::cout << "�lbum no encontrado.\n";
        return;
    }
    
    Cancion* actual = album->listaCanciones;
    Cancion* anterior = nullptr;
    while (actual && actual->nombreCancion != nombreCancion) {
        anterior = actual;
        actual = actual->siguiente;
    }
    
    if (!actual) {
        std::cout << "Canci�n no encontrada.\n";
        return;
    }
    
    if (!anterior)
        album->listaCanciones = actual->siguiente;
    else
        anterior->siguiente = actual->siguiente;
    
    delete actual;
    guardarDatos();
    std::cout << "Canci�n eliminada con �xito.\n";
}

void verCanciones() {
    std::string tituloAlbum;
    std::cout << "T�tulo del �lbum: ";
    std::getline(std::cin, tituloAlbum);
    
    Album* album = arbol.buscarAlbum(tituloAlbum);
    if (!album) {
        std::cout << "�lbum no encontrado.\n";
        return;
    }
    
    Cancion* actual = album->listaCanciones;
    while (actual) {
        std::cout << "Canci�n: " << actual->nombreCancion 
                  << " | Duraci�n: " << actual->duracion << "s\n";
        actual = actual->siguiente;
    }
}

