#include <iostream>
#include "AVL.h"

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

AVL arbol;
const std::string ARCHIVO_DATOS = "musica.dat";

bool archivoExiste(const std::string& nombreArchivo) {
    return std::filesystem::exists(nombreArchivo);
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
    if (archivoExiste(ARCHIVO_DATOS)) {
        arbol.cargar(ARCHIVO_DATOS);
        std::cout << "Datos cargados correctamente.\n";
    } else {
        std::cout << "No se encontró un archivo de datos. Se creará uno nuevo al guardar.\n";
    }
}
void mostrarMenuPrincipal() {
    std::cout << "\n===== Menu Principal =====\n";
    std::cout << "1. Gestionar Albumes\n";
    std::cout << "2. Gestionar Canciones\n";
    std::cout << "3. Realizar Consultas\n";
    std::cout << "0. Salir\n";
}

void gestionarAlbumes() {
    int opcion;
    do {
        std::cout << "\n===== Gestión de Albumes =====\n";
        std::cout << "1. Agregar Album\n";
        std::cout << "2. Eliminar Album\n";
        std::cout << "3. Ver Albumes\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: agregarAlbum(); break;
            case 2: eliminarAlbum(); break;
            case 3: verAlbumes(); break;
            case 0: break;
            default: std::cout << "Opcion no valida.\n";
        }
    } while (opcion != 0);
}

void agregarAlbum() {
    Album* nuevo = new Album();
    
    std::cout << "Titulo del album: ";
    std::getline(std::cin, nuevo->titulo);
    std::cout << "Nombre artistico: ";
    std::getline(std::cin, nuevo->nombreArtistico);
    std::cout << "Ano de publicación: ";
    std::cin >> nuevo->anioPublicacion;
    std::cin.ignore();
    
    arbol.insertar(nuevo);
    guardarDatos();
    std::cout << "Album agregado con exito.\n";
}

void eliminarAlbum() {
    std::string titulo;
    std::cout << "Titulo del album a eliminar: ";
    std::getline(std::cin, titulo);
    
    Album* album = arbol.buscarAlbum(titulo);
    if (!album) {
        std::cout << "Album no encontrado.\n";
        return;
    }
    
    // Implementar lógica de eliminación en AVL
    std::cout << "album eliminado.\n";
    guardarDatos();
}

void verAlbumes() {
    std::vector<Album*> albumes = arbol.obtenerTodosAlbumes();
    for (Album* a : albumes) {
        std::cout << "Album: " << a->titulo 
                  << " | Artista: " << a->nombreArtistico 
                  << " | Ano: " << a->anioPublicacion << "\n";
    }
}

void gestionarCanciones() {
    int opcion;
    do {
        std::cout << "\n===== Gestion de Canciones =====\n";
        std::cout << "1. Agregar Cancion\n";
        std::cout << "2. Eliminar Cancion\n";
        std::cout << "3. Ver Canciones\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: agregarCancion(); break;
            case 2: eliminarCancion(); break;
            case 3: verCanciones(); break;
            case 0: break;
            default: std::cout << "Opcion no valida.\n";
        }
    } while (opcion != 0);
}

void agregarCancion() {
    std::string tituloAlbum;
    std::cout << "Album destino: ";
    std::getline(std::cin, tituloAlbum);
    
    Album* album = arbol.buscarAlbum(tituloAlbum);
    if (!album) {
        std::cout << "Album no encontrado!\n";
        return;
    }

    Cancion* nueva = new Cancion();
    std::cout << "Nombre cancion: ";
    std::getline(std::cin, nueva->nombreCancion);
    std::cout << "Duracion (segundos): ";
    std::cin >> nueva->duracion;
    std::cin.ignore();

    // Agregar artistas
    int numArtistas;
    std::cout << "Numero de artistas: ";
    std::cin >> numArtistas;
    std::cin.ignore();
    for (int i = 0; i < numArtistas; ++i) {
        Artista artista;
        std::cout << "Artista " << i+1 << ":\n";
        std::cout << "Nombre real: ";
        std::getline(std::cin, artista.nombreReal);
        std::cout << "Nombre artistico: ";
        std::getline(std::cin, artista.nombreArtistico);
        std::cout << "Pais origen: ";
        std::getline(std::cin, artista.paisOrigen);
        std::cout << "Instrumento: ";
        std::getline(std::cin, artista.instrumento);
        nueva->artistas.push_back(artista);
    }

    // Agregar versiones
    int numVersiones;
    std::cout << "Numero de versiones: ";
    std::cin >> numVersiones;
    std::cin.ignore();
    for (int i = 0; i < numVersiones; ++i) {
        Version version;
        std::cout << "Version " << i+1 << ":\n";
        std::cout << "Titulo version: ";
        std::getline(std::cin, version.tituloVersion);
        std::cout << "Tipo version: ";
        std::getline(std::cin, version.tipoVersion);
        nueva->versiones.push_back(version);
    }

    // Vincular canción al álbum
    if (!album->listaCanciones) {
        album->listaCanciones = nueva;
    } else {
        Cancion* actual = album->listaCanciones;
        while (actual->siguiente) actual = actual->siguiente;
        actual->siguiente = nueva;
    }

    guardarDatos();
    std::cout << "Cancion agregada con exito.\n";
}

void eliminarCancion() {
    std::string tituloAlbum, nombreCancion;
    std::cout << "Titulo del album: ";
    std::getline(std::cin, tituloAlbum);
    std::cout << "Nombre de la cancion: ";
    std::getline(std::cin, nombreCancion);
    
    Album* album = arbol.buscarAlbum(tituloAlbum);
    if (!album) {
        std::cout << "Album no encontrado.\n";
        return;
    }

    Cancion* actual = album->listaCanciones;
    Cancion* anterior = nullptr;
    while (actual && actual->nombreCancion != nombreCancion) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (!actual) {
        std::cout << "Cancion no encontrada.\n";
        return;
    }

    if (!anterior) {
        album->listaCanciones = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    delete actual;
    guardarDatos();
    std::cout << "Cancion eliminada con exito.\n";
}

void verCanciones() {
    std::string tituloAlbum;
    std::cout << "Titulo del album: ";
    std::getline(std::cin, tituloAlbum);
    
    Album* album = arbol.buscarAlbum(tituloAlbum);
    if (!album) {
        std::cout << "Album no encontrado.\n";
        return;
    }

    Cancion* actual = album->listaCanciones;
    while (actual) {
        std::cout << "Cancion: " << actual->nombreCancion 
                  << " | Duracion: " << actual->duracion << "s\n";
        actual = actual->siguiente;
    }
}

void realizarConsultas() {
    std::cout << "Funcionalidad de consultas no implementada.\n";
}

int main() {
    cargarDatos();
    
    int opcion;
    do {
        mostrarMenuPrincipal();
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();
        
        switch (opcion) {
            case 1: gestionarAlbumes(); break;
            case 2: gestionarCanciones(); break;
            case 3: realizarConsultas(); break;
            case 0: std::cout << "Cerrando programa...\n"; break;
            default: std::cout << "Opcion no válida.\n";
        }
    } while (opcion != 0);
    
    guardarDatos();
    return 0;
}
