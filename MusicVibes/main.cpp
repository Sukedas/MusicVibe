#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>
#include <utility>
#include <sstream>
#include "AVL.h"
#include "Clases.h"

// Prototipos de funciones
void mostrarMenuPrincipal();
void gestionarAlbumes();
void gestionarCanciones();
void realizarConsultas();
void agregarAlbum();
void eliminarAlbum();
void verAlbumes();
void agregarCancion();
void eliminarCancion();
void verCanciones();
bool archivoExiste(const std::string& nombreArchivo);
bool archivoVacio(const std::string& nombreArchivo);
void consulta1();
void consulta2();
void consulta3();
void consulta4();
void consulta5();
void consulta6();
void consulta7();
void consulta8();
void consulta9();
void consulta10();

AVL arbol;
const std::string ARCHIVO_DATOS = "musica.txt";

// Verificar si el archivo existe
bool archivoExiste(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    return archivo.good();
}

// Verificar si el archivo está vacío
bool archivoVacio(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo, std::ios::ate);
    return archivo.tellg() == 0;
}

// Guardar datos en el archivo
void guardarDatos() {
    if (!archivoExiste(ARCHIVO_DATOS)) {
        std::cout << "Creando nuevo archivo de datos...\n";
    }
    arbol.guardar(ARCHIVO_DATOS);
    std::cout << "Datos guardados correctamente.\n";
}

// Cargar datos desde el archivo
void cargarDatos() {
    if (archivoExiste(ARCHIVO_DATOS) && !archivoVacio(ARCHIVO_DATOS)) {
        arbol.liberarArbol(); // Liberar memoria antes de cargar
        arbol.cargar(ARCHIVO_DATOS);
        std::cout << "Datos cargados correctamente.\n";
    } else {
        std::cout << "No se encontró un archivo de datos o está vacío. Se creará uno nuevo al guardar.\n";
    }
}

void mostrarMenuPrincipal() {
    std::cout << "\n===== Menú Principal =====\n";
    std::cout << "1. Gestionar Álbumes\n";
    std::cout << "2. Gestionar Canciones\n";
    std::cout << "3. Realizar Consultas\n";
    std::cout << "0. Salir\n";
}

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
    
    // Solicitar el listado de links del álbum
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
    
    // Insertar el álbum en el árbol AVL
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
    
    // Crear una nueva canción
    Cancion* nueva = new Cancion();
    
    std::cout << "Nombre de la canción: ";
    std::getline(std::cin, nueva->nombreCancion);
    
    // Ingresar la duración en formato HH:MM:SS y convertir a segundos.
    std::string duracionStr;
    std::cout << "Duración (HH:MM:SS): ";
    std::getline(std::cin, duracionStr);
    int horas, minutos, segundos;
    char sep;
    std::istringstream iss(duracionStr);
    iss >> horas >> sep >> minutos >> sep >> segundos;
    nueva->duracion = horas * 3600 + minutos * 60 + segundos;
    
    // Ingresar datos de grabación para la canción.
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
    // (Si deseas almacenar ciudad y país en la canción, deberás ampliar la clase Cancion.)
    
    // Ingresar el listado de artistas participantes.
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
    
    // Ingresar el listado de links de la canción.
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
    
    // Ingresar el listado de versiones de la canción.
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
        // (Para almacenar, se podría ampliar la clase Version con un campo 'ciudadGrabacion'.)
        std::cout << "  País de grabación de la versión: ";
        std::string paisV;
        std::getline(std::cin, paisV);
        version.paisPublicacion = paisV;
        std::cout << "  Género de la versión: ";
        std::getline(std::cin, version.genero);
        std::cout << "  Año de publicación de la versión: ";
        std::cin >> version.anioPublicacion;
        std::cin.ignore();
        // Ingresar el listado de links de la versión.
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
    
    // Vincular la nueva canción al final de la lista enlazada del álbum.
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
    
    if (!anterior) {
        album->listaCanciones = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }
    
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

//---------------------------------------------------------
// Consulta 1: Álbumes de una editora dada, ordenados por año y artista
//---------------------------------------------------------
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
    // Ordenar por año de publicación y nombre artístico
    std::sort(filtrados.begin(), filtrados.end(), [](Album* a, Album* b) {
        if (a->anioPublicacion == b->anioPublicacion)
            return a->nombreArtistico < b->nombreArtistico;
        return a->anioPublicacion < b->anioPublicacion;
    });
    
    std::cout << "Total de álbumes: " << filtrados.size() << "\n";
    for (Album* a : filtrados) {
        std::cout << "Álbum: " << a->titulo 
                  << " | Año: " << a->anioPublicacion 
                  << " | Artista: " << a->nombreArtistico << "\n";
    }
}

//---------------------------------------------------------
// Consulta 2: Listado de canciones (y su álbum) grabadas en un estudio dado,
// ordenadas por año y país de grabación
//---------------------------------------------------------
void consulta2() {
    std::string estudio;
    std::cout << "Ingrese el nombre del estudio de grabación: ";
    std::getline(std::cin, estudio);
    
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    // Filtrar álbumes por estudio
    std::vector<Album*> filtrados;
    for (Album* a : albumes) {
        if (a->estudioGrabacion == estudio)
            filtrados.push_back(a);
    }
    // Ordenar por año y país de grabación
    std::sort(filtrados.begin(), filtrados.end(), [](Album* a, Album* b) {
        if (a->anioPublicacion == b->anioPublicacion)
            return a->paisGrabacion < b->paisGrabacion;
        return a->anioPublicacion < b->anioPublicacion;
    });
    
    for (Album* a : filtrados) {
        std::cout << "Álbum: " << a->titulo << " (" << a->anioPublicacion 
                  << ", " << a->paisGrabacion << ")\n";
        // Listar canciones del álbum
        Cancion* actual = a->listaCanciones;
        while (actual) {
            std::cout << "  - Canción: " << actual->nombreCancion << "\n";
            actual = actual->siguiente;
        }
    }
}

//---------------------------------------------------------
// Consulta 3: Listado de canciones (con arreglista y autores) de duración mayor a un tiempo,
// clasificadas por ciudad de grabación (dato que se almacena en el álbum)
//---------------------------------------------------------
void consulta3() {
    int tiempo;
    std::cout << "Ingrese la duración mínima (en segundos): ";
    std::cin >> tiempo;
    std::cin.ignore();
    
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    // Para cada álbum, listar las canciones que cumplan la condición
    for (Album* a : albumes) {
        bool seMostroCabecera = false;
        Cancion* actual = a->listaCanciones;
        while (actual) {
            if (actual->duracion > tiempo) {
                if (!seMostroCabecera) {
                    std::cout << "Ciudad de grabación: " << a->ciudadGrabacion << "\n";
                    seMostroCabecera = true;
                }
                std::cout << "  Canción: " << actual->nombreCancion << " (Duración: " << actual->duracion << "s)\n";
                // Mostrar artistas con rol de arreglista, letrista y compositor
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

//---------------------------------------------------------
// Consulta 4: Listado de canciones de un género dado que incluyan un instrumento dado
//---------------------------------------------------------
void consulta4() {
    std::string genero, instrumento;
    std::cout << "Ingrese el género: ";
    std::getline(std::cin, genero);
    std::cout << "Ingrese el instrumento: ";
    std::getline(std::cin, instrumento);
    
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    for (Album* a : albumes) {
        Cancion* actual = a->listaCanciones;
        while (actual) {
            if (actual->genero == genero) {
                // Verificar si alguno de los artistas toca el instrumento dado
                for (const Artista& art : actual->artistas) {
                    if (art.instrumento == instrumento) {
                        std::cout << "Canción: " << actual->nombreCancion 
                                  << " | Álbum: " << a->titulo 
                                  << " | Artista: " << art.nombreArtistico << "\n";
                        break;
                    }
                }
            }
            actual = actual->siguiente;
        }
    }
}

//---------------------------------------------------------
// Consulta 5: Número de canciones con cantidad de versiones >= un número dado,
// agrupadas por género y año de la primera grabación (campo anioGrabacion en Cancion)
//---------------------------------------------------------
void consulta5() {
    int num;
    std::cout << "Ingrese el número mínimo de versiones: ";
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
        std::cout << "Género: " << par.first.first 
                  << " | Año: " << par.first.second 
                  << " -> " << par.second << " canción(es)\n";
    }
}

//---------------------------------------------------------
// Consulta 6: Listado de versiones de un tipo dado y en más de una plataforma
//---------------------------------------------------------
void consulta6() {
    std::string tipo;
    std::cout << "Ingrese el tipo de versión: ";
    std::getline(std::cin, tipo);
    
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    for (Album* a : albumes) {
        Cancion* actual = a->listaCanciones;
        while (actual) {
            for (const Version& v : actual->versiones) {
                if (v.tipoVersion == tipo && v.enlaces.size() > 1) {
                    std::cout << "Versión: " << v.tituloVersion << "\n";
                    std::cout << "  Artista principal: " << v.artistaPrincipal << "\n";
                    std::cout << "  Género: " << v.genero << "\n";
                    std::cout << "  Año: " << v.anioPublicacion 
                              << " | País: " << v.paisPublicacion << "\n";
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

//---------------------------------------------------------
// Consulta 7: Dada una canción, listar todos los links de plataformas (original y versiones)
//---------------------------------------------------------
void consulta7() {
    std::string albumTitulo, cancionNombre;
    std::cout << "Ingrese el título del álbum: ";
    std::getline(std::cin, albumTitulo);
    std::cout << "Ingrese el nombre de la canción: ";
    std::getline(std::cin, cancionNombre);
    
    Album* album = arbol.buscarAlbum(albumTitulo);
    if (!album) {
        std::cout << "Álbum no encontrado.\n";
        return;
    }
    Cancion* actual = album->listaCanciones;
    while (actual) {
        if (actual->nombreCancion == cancionNombre) {
            std::cout << "Plataformas de la canción original:\n";
            for (const EnlacePlataforma& ep : actual->enlaces) {
                std::cout << "   " << ep.nombrePlataforma << ": " << ep.link << "\n";
            }
            for (const Version& v : actual->versiones) {
                std::cout << "Versión '" << v.tituloVersion << "' en:\n";
                for (const EnlacePlataforma& ep : v.enlaces) {
                    std::cout << "   " << ep.nombrePlataforma << ": " << ep.link << "\n";
                }
            }
            return;
        }
        actual = actual->siguiente;
    }
    std::cout << "Canción no encontrada.\n";
}

//---------------------------------------------------------
// Consulta 8: Número de canciones y versiones por encargado de Cover Art,
// agrupadas por género y año de publicación
//---------------------------------------------------------
void consulta8() {
    std::map<std::tuple<std::string, std::string, int>, std::pair<int, int>> info;
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    for (Album* a : albumes) {
        std::string encargado = a->encargadoCoverArt;
        Cancion* actual = a->listaCanciones;
        while (actual) {
            auto clave = std::make_tuple(encargado, actual->genero, a->anioPublicacion);
            info[clave].first++; // cuenta la canción
            info[clave].second += actual->versiones.size();
            actual = actual->siguiente;
        }
    }
    for (const auto& par : info) {
        std::string encargado, genero;
        int anio;
        std::tie(encargado, genero, anio) = par.first;
        std::cout << "Encargado: " << encargado 
                  << " | Género: " << genero 
                  << " | Año: " << anio 
                  << " -> Canciones: " << par.second.first 
                  << ", Versiones: " << par.second.second << "\n";
    }
}

//---------------------------------------------------------
// Consulta 9: Lista de álbumes grabados en un estudio y con un encargado de fotografía dados,
// ordenados por país de grabación
//---------------------------------------------------------
void consulta9() {
    std::string encargadoFotografia, estudio;
    std::cout << "Ingrese el nombre del encargado de fotografía: ";
    std::getline(std::cin, encargadoFotografia);
    std::cout << "Ingrese el nombre del estudio de grabación: ";
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
        std::cout << "Álbum: " << a->titulo 
                  << " | País de grabación: " << a->paisGrabacion << "\n";
    }
}

//---------------------------------------------------------
// Consulta 10: Listar canciones compuestas por un compositor de la letra dado,
// mostrando género, año, nombre de la canción, álbum y número de plataformas
//---------------------------------------------------------
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
                std::cout << "Canción: " << actual->nombreCancion 
                          << " | Género: " << actual->genero 
                          << " | Año: " << actual->anioGrabacion 
                          << " | Álbum: " << a->titulo 
                          << " | Plataformas: " << actual->enlaces.size() << "\n";
            }
            actual = actual->siguiente;
        }
    }
}

//---------------------------------------------------------
// Menú de consultas
//---------------------------------------------------------
void realizarConsultas() {
    int opcion;
    do {
        std::cout << "\n===== Menú de Consultas =====\n";
        std::cout << "1. Consulta de álbumes por editora\n";
        std::cout << "2. Consulta de canciones grabadas en un estudio\n";
        std::cout << "3. Consulta de canciones por duración y ciudad de grabación\n";
        std::cout << "4. Consulta de canciones por género e instrumento\n";
        std::cout << "5. Consulta de canciones con versiones >= un número\n";
        std::cout << "6. Consulta de versiones por tipo y múltiples plataformas\n";
        std::cout << "7. Consulta de links de una canción (original y versiones)\n";
        std::cout << "8. Consulta de número de canciones y versiones por Cover Art\n";
        std::cout << "9. Consulta de álbumes por encargado de fotografía y estudio\n";
        std::cout << "10. Consulta de canciones por compositor de la letra\n";
        std::cout << "0. Volver al menú principal\n";
        std::cout << "Seleccione una opción: ";
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
            default: std::cout << "Opción no válida.\n";
        }
    } while (opcion != 0);
}

int main() {
    cargarDatos(); // Cargar datos al iniciar el programa   
    
    int opcion;
    do {
        mostrarMenuPrincipal();
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();
        
        switch (opcion) {
            case 1: gestionarAlbumes(); break;
            case 2: gestionarCanciones(); break;
            case 3: realizarConsultas(); break;
            case 0: std::cout << "Cerrando programa...\n"; break;
            default: std::cout << "Opción no válida.\n";
        }
    } while (opcion != 0);
    
    guardarDatos(); // Guardar datos al cerrar el programa
    return 0;
}

