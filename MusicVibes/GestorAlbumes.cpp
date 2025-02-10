// src/GestorAlbumes.cpp
#include <iostream>
#include <vector>
#include "GestorAlbumes.h"
#include "AVL.h"
#include "Clases.h"

// Se asume que la variable global "arbol" est� declarada en main.cpp (o en un archivo de cabecera com�n)
// Si lo prefieres, puedes declararla como extern:
extern AVL arbol;
extern void guardarDatos();  // Declaraci�n de la funci�n de guardado (definida en main.cpp)

void gestionarAlbumes() {
    int opcion;
    do {
        std::cout << "\n===== Gesti�n de �lbumes =====\n";
        std::cout << "1. Agregar �lbum\n";
        std::cout << "2. Eliminar �lbum\n";
        std::cout << "3. Ver �lbumes\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opci�n: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: agregarAlbum(); break;
            case 2: eliminarAlbum(); break;
            case 3: verAlbumes(); break;
            case 0: break;
            default: std::cout << "Opci�n no v�lida.\n";
        }
    } while (opcion != 0);
}

void agregarAlbum() {
    Album* nuevo = new Album();
    
    std::cout << "=== Agregar �lbum ===\n";
    std::cout << "T�tulo del �lbum: ";
    std::getline(std::cin, nuevo->titulo);
    std::cout << "Nombre art�stico: ";
    std::getline(std::cin, nuevo->nombreArtistico);
    std::cout << "Pa�s de grabaci�n del �lbum: ";
    std::getline(std::cin, nuevo->paisGrabacion);
    std::cout << "A�o de publicaci�n: ";
    std::cin >> nuevo->anioPublicacion;
    std::cin.ignore();
    std::cout << "Cover Art (nombre del encargado de la portada): ";
    std::getline(std::cin, nuevo->encargadoCoverArt);
    std::cout << "Fotograf�a (nombre del encargado de la fotograf�a): ";
    std::getline(std::cin, nuevo->encargadoFotografia);
    std::cout << "Editora (a la que pertenecen los derechos): ";
    std::getline(std::cin, nuevo->editora);
    std::cout << "Estudio de Grabaci�n: ";
    std::getline(std::cin, nuevo->estudioGrabacion);
    std::cout << "Ciudad de grabaci�n del �lbum: ";
    std::getline(std::cin, nuevo->ciudadGrabacion);
    
    int numLinks;
    std::cout << "N�mero de links del �lbum: ";
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
    std::cout << "�lbum agregado con �xito.\n";
}

void eliminarAlbum() {
    std::string titulo;
    std::cout << "T�tulo del �lbum a eliminar: ";
    std::getline(std::cin, titulo);
    
    Album* album = arbol.buscarAlbum(titulo);
    if (!album) {
        std::cout << "�lbum no encontrado.\n";
        return;
    }
    
    arbol.eliminarAlbum(titulo);
    guardarDatos();
    std::cout << "�lbum eliminado.\n";
}

void verAlbumes() {
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    for (Album* a : albumes) {
        std::cout << "�lbum: " << a->titulo 
                  << " | Artista: " << a->nombreArtistico 
                  << " | A�o: " << a->anioPublicacion << "\n";
    }
}

