// src/Consultas.cpp
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <cstdlib>    // Para system("cls") o system("clear")
#include "Consultas.h"
#include "AVL.h"
#include "Clases.h"

extern AVL arbol;

void consulta1() {
    std::cout << "\033[1;36m=== Consulta 1: Albumes por editora ===\033[0m\n";
    std::cout << "\033[1;33mIngrese el nombre de la editora: \033[0m";
    std::string editora;
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
    
    std::cout << "\033[1;32mTotal de albumes: " << filtrados.size() << "\033[0m\n";
    for (Album* a : filtrados) {
        std::cout << "\033[1;33mAlbum: \033[0m" << a->titulo 
                  << " \033[1;33m| Anio: \033[0m" << a->anioPublicacion 
                  << " \033[1;33m| Artista: \033[0m" << a->nombreArtistico << "\n";
    }
}

void consulta2() {
    std::cout << "\033[1;36m=== Consulta 2: Canciones grabadas en un estudio ===\033[0m\n";
    std::cout << "\033[1;33mIngrese el nombre del estudio de grabacion: \033[0m";
    std::string estudio;
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
        std::cout << "\033[1;33mAlbum: \033[0m" << a->titulo 
                  << " \033[1;33m| Anio: \033[0m" << a->anioPublicacion 
                  << " \033[1;33m| Pais: \033[0m" << a->paisGrabacion << "\n";
        Cancion* actual = a->listaCanciones;
        while (actual) {
            std::cout << "  - \033[1;32mCancion: \033[0m" << actual->nombreCancion << "\n";
            actual = actual->siguiente;
        }
    }
}

void consulta3() {
    std::cout << "\033[1;36m=== Consulta 3: Canciones por duracion y ciudad de grabacion ===\033[0m\n";
    std::cout << "\033[1;33mIngrese la duracion minima (en segundos): \033[0m";
    int tiempo;
    std::cin >> tiempo;
    std::cin.ignore();
    
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    for (Album* a : albumes) {
        bool seMostroCabecera = false;
        Cancion* actual = a->listaCanciones;
        while (actual) {
            if (actual->duracion > tiempo) {
                if (!seMostroCabecera) {
                    std::cout << "\033[1;32mCiudad de grabacion: \033[0m" << a->ciudadGrabacion << "\n";
                    seMostroCabecera = true;
                }
                std::cout << "  \033[1;33mCancion: \033[0m" << actual->nombreCancion 
                          << " \033[1;33m(Duracion: \033[0m" << actual->duracion << "s)\n";
                for (const Artista& art : actual->artistas) {
                    if (art.rol == "arreglista" || art.rol == "letrista" || art.rol == "compositor") {
                        std::cout << "     \033[1;32m" << art.rol << ": \033[0m" 
                                  << art.nombreArtistico 
                                  << " (" << art.nombreReal << ")\n";
                    }
                }
            }
            actual = actual->siguiente;
        }
    }
}

void consulta4() {
    std::cout << "\033[1;36m=== Consulta 4: Canciones por genero e instrumento ===\033[0m\n";
    std::cout << "\033[1;33mIngrese el genero: \033[0m";
    std::string genero;
    std::getline(std::cin, genero);
    std::cout << "\033[1;33mIngrese el instrumento: \033[0m";
    std::string instrumento;
    std::getline(std::cin, instrumento);
    
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    for (Album* a : albumes) {
        Cancion* actual = a->listaCanciones;
        while (actual) {
            if (actual->genero == genero) {
                for (const Artista& art : actual->artistas) {
                    if (art.instrumento == instrumento) {
                        std::cout << "\033[1;33mCancion: \033[0m" << actual->nombreCancion 
                                  << " \033[1;33m| Album: \033[0m" << a->titulo 
                                  << " \033[1;33m| Artista: \033[0m" << art.nombreArtistico << "\n";
                        break;
                    }
                }
            }
            actual = actual->siguiente;
        }
    }
}

void consulta5() {
    std::cout << "\033[1;36m=== Consulta 5: Canciones con versiones >= un numero ===\033[0m\n";
    std::cout << "\033[1;33mIngrese el numero minimo de versiones: \033[0m";
    int num;
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
        std::cout << "\033[1;33mGenero: \033[0m" << par.first.first 
                  << " \033[1;33m| Anio: \033[0m" << par.first.second 
                  << " -> " << par.second << " cancion(es)\n";
    }
}

void consulta6() {
    std::cout << "\033[1;36m=== Consulta 6: Versiones por tipo y multiples plataformas ===\033[0m\n";
    std::cout << "\033[1;33mIngrese el tipo de version: \033[0m";
    std::string tipo;
    std::getline(std::cin, tipo);
    
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    for (Album* a : albumes) {
        Cancion* actual = a->listaCanciones;
        while (actual) {
            for (const Version& v : actual->versiones) {
                if (v.tipoVersion == tipo && v.enlaces.size() > 1) {
                    std::cout << "\033[1;33mVersion: \033[0m" << v.tituloVersion << "\n";
                    std::cout << "  \033[1;33mArtista principal: \033[0m" << v.artistaPrincipal << "\n";
                    std::cout << "  \033[1;33mGenero: \033[0m" << v.genero << "\n";
                    std::cout << "  \033[1;33mAnio: \033[0m" << v.anioPublicacion 
                              << " \033[1;33m| Pais: \033[0m" << v.paisPublicacion << "\n";
                    std::cout << "  \033[1;33mObra original: \033[0m" << v.obraOriginal << "\n";
                    std::cout << "  \033[1;33mPlataformas:\033[0m\n";
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
    std::cout << "\033[1;36m=== Consulta 7: Links de una cancion (original y versiones) ===\033[0m\n";
    std::cout << "\033[1;33mIngrese el titulo del album: \033[0m";
    std::string albumTitulo;
    std::getline(std::cin, albumTitulo);
    std::cout << "\033[1;33mIngrese el nombre de la cancion: \033[0m";
    std::string cancionNombre;
    std::getline(std::cin, cancionNombre);
    
    Album* album = arbol.buscarAlbum(albumTitulo);
    if (!album) {
        std::cout << "\033[1;31mAlbum no encontrado.\033[0m\n";
        return;
    }
    Cancion* actual = album->listaCanciones;
    while (actual) {
        if (actual->nombreCancion == cancionNombre) {
            std::cout << "\033[1;32mPlataformas de la cancion original:\033[0m\n";
            for (const EnlacePlataforma& ep : actual->enlaces) {
                std::cout << "   " << ep.nombrePlataforma << ": " << ep.link << "\n";
            }
            for (const Version& v : actual->versiones) {
                std::cout << "\033[1;32mVersion '" << v.tituloVersion << "' en:\033[0m\n";
                for (const EnlacePlataforma& ep : v.enlaces) {
                    std::cout << "   " << ep.nombrePlataforma << ": " << ep.link << "\n";
                }
            }
            return;
        }
        actual = actual->siguiente;
    }
    std::cout << "\033[1;31mCancion no encontrada.\033[0m\n";
}

void consulta8() {
    std::cout << "\033[1;36m=== Consulta 8: Canciones y versiones por Cover Art ===\033[0m\n";
    std::map<std::tuple<std::string, std::string, int>, std::pair<int, int>> info;
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    for (Album* a : albumes) {
        std::string encargado = a->encargadoCoverArt;
        Cancion* actual = a->listaCanciones;
        while (actual) {
            auto clave = std::make_tuple(encargado, actual->genero, a->anioPublicacion);
            info[clave].first++; // cuenta la cancion
            info[clave].second += actual->versiones.size();
            actual = actual->siguiente;
        }
    }
    for (const auto& par : info) {
        std::string encargado, genero;
        int anio;
        std::tie(encargado, genero, anio) = par.first;
        std::cout << "\033[1;33mEncargado: \033[0m" << encargado 
                  << " \033[1;33m| Genero: \033[0m" << genero 
                  << " \033[1;33m| Anio: \033[0m" << anio 
                  << " -> \033[1;32mCanciones: \033[0m" << par.second.first 
                  << ", \033[1;32mVersiones: \033[0m" << par.second.second << "\n";
    }
}

void consulta9() {
    std::cout << "\033[1;36m=== Consulta 9: Albumes por encargado de fotografia y estudio ===\033[0m\n";
    std::cout << "\033[1;33mIngrese el nombre del encargado de fotografia: \033[0m";
    std::string encargadoFotografia;
    std::getline(std::cin, encargadoFotografia);
    std::cout << "\033[1;33mIngrese el nombre del estudio de grabacion: \033[0m";
    std::string estudio;
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
        std::cout << "\033[1;33mAlbum: \033[0m" << a->titulo 
                  << " \033[1;33m| Pais de grabacion: \033[0m" << a->paisGrabacion << "\n";
    }
}

void consulta10() {
    std::cout << "\033[1;36m=== Consulta 10: Canciones por compositor de la letra ===\033[0m\n";
    std::cout << "\033[1;33mIngrese el nombre del compositor de la letra: \033[0m";
    std::string compositor;
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
                std::cout << "\033[1;33mCancion: \033[0m" << actual->nombreCancion 
                          << " \033[1;33m| Genero: \033[0m" << actual->genero 
                          << " \033[1;33m| Anio: \033[0m" << actual->anioGrabacion 
                          << " \033[1;33m| Album: \033[0m" << a->titulo 
                          << " \033[1;33m| Plataformas: \033[0m" << actual->enlaces.size() << "\n";
            }
            actual = actual->siguiente;
        }
    }
}

void realizarConsultas() {
    int opcion;
    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        std::cout << "\033[1;36m===== Menu de Consultas =====\033[0m\n";
        std::cout << "\033[1;33m1. Consulta de albumes por editora\033[0m\n";
        std::cout << "\033[1;33m2. Consulta de canciones grabadas en un estudio\033[0m\n";
        std::cout << "\033[1;33m3. Consulta de canciones por duracion y ciudad de grabacion\033[0m\n";
        std::cout << "\033[1;33m4. Consulta de canciones por genero e instrumento\033[0m\n";
        std::cout << "\033[1;33m5. Consulta de canciones con versiones >= un numero\033[0m\n";
        std::cout << "\033[1;33m6. Consulta de versiones por tipo y multiples plataformas\033[0m\n";
        std::cout << "\033[1;33m7. Consulta de links de una cancion (original y versiones)\033[0m\n";
        std::cout << "\033[1;33m8. Consulta de numero de canciones y versiones por Cover Art\033[0m\n";
        std::cout << "\033[1;33m9. Consulta de albumes por encargado de fotografia y estudio\033[0m\n";
        std::cout << "\033[1;33m10. Consulta de canciones por compositor de la letra\033[0m\n";
        std::cout << "\033[1;33m0. Volver al menu principal\033[0m\n";
        std::cout << "\033[1;32mSeleccione una opcion: \033[0m";
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
            default: std::cout << "\033[1;31mOpcion no valida.\033[0m\n";
        }
        std::cout << "\n\033[1;32mPresione Enter para continuar...\033[0m";
        std::cin.get();
    } while (opcion != 0);
}

