// src/Consultas.cpp
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include "Consultas.h"
#include "AVL.h"
#include "Clases.h"

extern AVL arbol;

void consulta1() {
    std::string editora;
    std::cout << "Ingrese el nombre de la editora: ";
    std::getline(std::cin, editora);
    
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    std::vector<Album*> filtrados;
    for (Album* a : albumes) {
        if (a->editora == editora)
            filtrados.push_back(a);
    }
    std::sort(filtrados.begin(), filtrados.end(), [](Album* a, Album* b) {
        if (a->anioPublicacion == b->anioPublicacion)
            return a->nombreArtistico < b->nombreArtistico;
        return a->anioPublicacion < b->anioPublicacion;
    });
    
    std::cout << "Total de �lbumes: " << filtrados.size() << "\n";
    for (Album* a : filtrados) {
        std::cout << "�lbum: " << a->titulo 
                  << " | A�o: " << a->anioPublicacion 
                  << " | Artista: " << a->nombreArtistico << "\n";
    }
}

void consulta2() {
    std::string estudio;
    std::cout << "Ingrese el nombre del estudio de grabaci�n: ";
    std::getline(std::cin, estudio);
    
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    std::vector<Album*> filtrados;
    for (Album* a : albumes) {
        if (a->estudioGrabacion == estudio)
            filtrados.push_back(a);
    }
    std::sort(filtrados.begin(), filtrados.end(), [](Album* a, Album* b) {
        if (a->anioPublicacion == b->anioPublicacion)
            return a->paisGrabacion < b->paisGrabacion;
        return a->anioPublicacion < b->anioPublicacion;
    });
    
    for (Album* a : filtrados) {
        std::cout << "�lbum: " << a->titulo << " (" << a->anioPublicacion 
                  << ", " << a->paisGrabacion << ")\n";
        Cancion* actual = a->listaCanciones;
        while (actual) {
            std::cout << "  - Canci�n: " << actual->nombreCancion << "\n";
            actual = actual->siguiente;
        }
    }
}

void consulta3() {
    int tiempo;
    std::cout << "Ingrese la duraci�n m�nima (en segundos): ";
    std::cin >> tiempo;
    std::cin.ignore();
    
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    for (Album* a : albumes) {
        bool seMostroCabecera = false;
        Cancion* actual = a->listaCanciones;
        while (actual) {
            if (actual->duracion > tiempo) {
                if (!seMostroCabecera) {
                    std::cout << "Ciudad de grabaci�n: " << a->ciudadGrabacion << "\n";
                    seMostroCabecera = true;
                }
                std::cout << "  Canci�n: " << actual->nombreCancion 
                          << " (Duraci�n: " << actual->duracion << "s)\n";
                for (const Artista& art : actual->artistas) {
                    if (art.rol == "arreglista" || art.rol == "letrista" || art.rol == "compositor") {
                        std::cout << "     " << art.rol << ": " << art.nombreArtistico 
                                  << " (" << art.nombreReal << ")\n";
                    }
                }
            }
            actual = actual->siguiente;
        }
    }
}

void consulta4() {
    std::string genero, instrumento;
    std::cout << "Ingrese el g�nero: ";
    std::getline(std::cin, genero);
    std::cout << "Ingrese el instrumento: ";
    std::getline(std::cin, instrumento);
    
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    for (Album* a : albumes) {
        Cancion* actual = a->listaCanciones;
        while (actual) {
            if (actual->genero == genero) {
                for (const Artista& art : actual->artistas) {
                    if (art.instrumento == instrumento) {
                        std::cout << "Canci�n: " << actual->nombreCancion 
                                  << " | �lbum: " << a->titulo 
                                  << " | Artista: " << art.nombreArtistico << "\n";
                        break;
                    }
                }
            }
            actual = actual->siguiente;
        }
    }
}

void consulta5() {
    int num;
    std::cout << "Ingrese el n�mero m�nimo de versiones: ";
    std::cin >> num;
    std::cin.ignore();
    
    std::map<std::pair<std::string, int>, int> grupos;
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    for (Album* a : albumes) {
        Cancion* actual = a->listaCanciones;
        while (actual) {
            if (actual->versiones.size() >= static_cast<size_t>(num)) {
                grupos[std::make_pair(actual->genero, actual->anioGrabacion)]++;
            }
            actual = actual->siguiente;
        }
    }
    for (const auto& par : grupos) {
        std::cout << "G�nero: " << par.first.first 
                  << " | A�o: " << par.first.second 
                  << " -> " << par.second << " canci�n(es)\n";
    }
}

void consulta6() {
    std::string tipo;
    std::cout << "Ingrese el tipo de versi�n: ";
    std::getline(std::cin, tipo);
    
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    for (Album* a : albumes) {
        Cancion* actual = a->listaCanciones;
        while (actual) {
            for (const Version& v : actual->versiones) {
                if (v.tipoVersion == tipo && v.enlaces.size() > 1) {
                    std::cout << "Versi�n: " << v.tituloVersion << "\n";
                    std::cout << "  Artista principal: " << v.artistaPrincipal << "\n";
                    std::cout << "  G�nero: " << v.genero << "\n";
                    std::cout << "  A�o: " << v.anioPublicacion 
                              << " | Pa�s: " << v.paisPublicacion << "\n";
                    std::cout << "  Obra original: " << v.obraOriginal << "\n";
                    std::cout << "  Plataformas:\n";
                    for (const EnlacePlataforma& ep : v.enlaces) {
                        std::cout << "     " << ep.nombrePlataforma << ": " << ep.link << "\n";
                    }
                    std::cout << "\n";
                }
            }
            actual = actual->siguiente;
        }
    }
}

void consulta7() {
    std::string albumTitulo, cancionNombre;
    std::cout << "Ingrese el t�tulo del �lbum: ";
    std::getline(std::cin, albumTitulo);
    std::cout << "Ingrese el nombre de la canci�n: ";
    std::getline(std::cin, cancionNombre);
    
    Album* album = arbol.buscarAlbum(albumTitulo);
    if (!album) {
        std::cout << "�lbum no encontrado.\n";
        return;
    }
    Cancion* actual = album->listaCanciones;
    while (actual) {
        if (actual->nombreCancion == cancionNombre) {
            std::cout << "Plataformas de la canci�n original:\n";
            for (const EnlacePlataforma& ep : actual->enlaces) {
                std::cout << "   " << ep.nombrePlataforma << ": " << ep.link << "\n";
            }
            for (const Version& v : actual->versiones) {
                std::cout << "Versi�n '" << v.tituloVersion << "' en:\n";
                for (const EnlacePlataforma& ep : v.enlaces) {
                    std::cout << "   " << ep.nombrePlataforma << ": " << ep.link << "\n";
                }
            }
            return;
        }
        actual = actual->siguiente;
    }
    std::cout << "Canci�n no encontrada.\n";
}

void consulta8() {
    std::map<std::tuple<std::string, std::string, int>, std::pair<int, int>> info;
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    for (Album* a : albumes) {
        std::string encargado = a->encargadoCoverArt;
        Cancion* actual = a->listaCanciones;
        while (actual) {
            auto clave = std::make_tuple(encargado, actual->genero, a->anioPublicacion);
            info[clave].first++; // cuenta la canci�n
            info[clave].second += actual->versiones.size();
            actual = actual->siguiente;
        }
    }
    for (const auto& par : info) {
        std::string encargado, genero;
        int anio;
        std::tie(encargado, genero, anio) = par.first;
        std::cout << "Encargado: " << encargado 
                  << " | G�nero: " << genero 
                  << " | A�o: " << anio 
                  << " -> Canciones: " << par.second.first 
                  << ", Versiones: " << par.second.second << "\n";
    }
}

void consulta9() {
    std::string encargadoFotografia, estudio;
    std::cout << "Ingrese el nombre del encargado de fotograf�a: ";
    std::getline(std::cin, encargadoFotografia);
    std::cout << "Ingrese el nombre del estudio de grabaci�n: ";
    std::getline(std::cin, estudio);
    
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    std::vector<Album*> filtrados;
    for (Album* a : albumes) {
        if (a->encargadoFotografia == encargadoFotografia &&
            a->estudioGrabacion == estudio)
            filtrados.push_back(a);
    }
    std::sort(filtrados.begin(), filtrados.end(), [](Album* a, Album* b) {
        return a->paisGrabacion < b->paisGrabacion;
    });
    
    for (Album* a : filtrados) {
        std::cout << "�lbum: " << a->titulo 
                  << " | Pa�s de grabaci�n: " << a->paisGrabacion << "\n";
    }
}

void consulta10() {
    std::string compositor;
    std::cout << "Ingrese el nombre del compositor de la letra: ";
    std::getline(std::cin, compositor);
    
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    for (Album* a : albumes) {
        Cancion* actual = a->listaCanciones;
        while (actual) {
            bool encontrado = false;
            for (const Artista& art : actual->artistas) {
                if (art.rol == "compositor de la letra" && art.nombreArtistico == compositor) {
                    encontrado = true;
                    break;
                }
            }
            if (encontrado) {
                std::cout << "Canci�n: " << actual->nombreCancion 
                          << " | G�nero: " << actual->genero 
                          << " | A�o: " << actual->anioGrabacion 
                          << " | �lbum: " << a->titulo 
                          << " | Plataformas: " << actual->enlaces.size() << "\n";
            }
            actual = actual->siguiente;
        }
    }
}

void realizarConsultas() {
    int opcion;
    do {
        std::cout << "\n===== Men� de Consultas =====\n";
        std::cout << "1. Consulta de �lbumes por editora\n";
        std::cout << "2. Consulta de canciones grabadas en un estudio\n";
        std::cout << "3. Consulta de canciones por duraci�n y ciudad de grabaci�n\n";
        std::cout << "4. Consulta de canciones por g�nero e instrumento\n";
        std::cout << "5. Consulta de canciones con versiones >= un n�mero\n";
        std::cout << "6. Consulta de versiones por tipo y m�ltiples plataformas\n";
        std::cout << "7. Consulta de links de una canci�n (original y versiones)\n";
        std::cout << "8. Consulta de n�mero de canciones y versiones por Cover Art\n";
        std::cout << "9. Consulta de �lbumes por encargado de fotograf�a y estudio\n";
        std::cout << "10. Consulta de canciones por compositor de la letra\n";
        std::cout << "0. Volver al men� principal\n";
        std::cout << "Seleccione una opci�n: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: consulta1(); break;
            case 2: consulta2(); break;
            case 3: consulta3(); break;
            case 4: consulta4(); break;
            case 5: consulta5(); break;
            case 6: consulta6(); break;
            case 7: consulta7(); break;
            case 8: consulta8(); break;
            case 9: consulta9(); break;
            case 10: consulta10(); break;
            case 0: break;
            default: std::cout << "Opci�n no v�lida.\n";
        }
    } while (opcion != 0);
}

