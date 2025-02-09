#ifndef CLASES_H
#define CLASES_H

#include <vector>
#include <string>
#include <fstream>

//--------------------------------------------------------
// EnlacePlataforma
//--------------------------------------------------------
class EnlacePlataforma {
public:
    std::string nombrePlataforma;
    std::string link;

    void guardar(std::ofstream& archivo) {
        size_t size = nombrePlataforma.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(nombrePlataforma.c_str(), size);
        
        size = link.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(link.c_str(), size);
    }

    void cargar(std::ifstream& archivo) {
        size_t size;
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        nombrePlataforma.resize(size);
        archivo.read(&nombrePlataforma[0], size);
        
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        link.resize(size);
        archivo.read(&link[0], size);
    }
};

//--------------------------------------------------------
// Artista
//--------------------------------------------------------
class Artista {
public:
    std::string nombreReal;
    std::string nombreArtistico;
    std::string paisOrigen;
    std::string instrumento;
    std::string rol; // nuevo

    void guardar(std::ofstream& archivo) {
        size_t size = nombreReal.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(nombreReal.c_str(), size);
        
        size = nombreArtistico.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(nombreArtistico.c_str(), size);
        
        size = paisOrigen.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(paisOrigen.c_str(), size);
        
        size = instrumento.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(instrumento.c_str(), size);
        
        size = rol.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(rol.c_str(), size);
    }

    void cargar(std::ifstream& archivo) {
        size_t size;
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        nombreReal.resize(size);
        archivo.read(&nombreReal[0], size);
        
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        nombreArtistico.resize(size);
        archivo.read(&nombreArtistico[0], size);
        
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        paisOrigen.resize(size);
        archivo.read(&paisOrigen[0], size);
        
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        instrumento.resize(size);
        archivo.read(&instrumento[0], size);
        
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        rol.resize(size);
        archivo.read(&rol[0], size);
    }
};

//--------------------------------------------------------
// Version
//--------------------------------------------------------
class Version {
public:
    std::string tituloVersion;
    std::string tipoVersion;
    std::vector<EnlacePlataforma> enlaces;

    // Nuevos campos para la consulta 6:
    std::string artistaPrincipal;
    std::string genero;
    int anioPublicacion;
    std::string paisPublicacion;
    std::string obraOriginal;

    void guardar(std::ofstream& archivo) {
        size_t size = tituloVersion.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(tituloVersion.c_str(), size);
        
        size = tipoVersion.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(tipoVersion.c_str(), size);
        
        size = enlaces.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        for (auto& e : enlaces) e.guardar(archivo);

        // Guardar nuevos campos:
        size = artistaPrincipal.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(artistaPrincipal.c_str(), size);

        size = genero.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(genero.c_str(), size);

        archivo.write(reinterpret_cast<char*>(&anioPublicacion), sizeof(anioPublicacion));

        size = paisPublicacion.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(paisPublicacion.c_str(), size);

        size = obraOriginal.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(obraOriginal.c_str(), size);
    }

    void cargar(std::ifstream& archivo) {
        size_t size;
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        tituloVersion.resize(size);
        archivo.read(&tituloVersion[0], size);
        
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        tipoVersion.resize(size);
        archivo.read(&tipoVersion[0], size);
        
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        enlaces.resize(size);
        for (auto& e : enlaces) e.cargar(archivo);

        // Cargar nuevos campos:
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        artistaPrincipal.resize(size);
        archivo.read(&artistaPrincipal[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        genero.resize(size);
        archivo.read(&genero[0], size);

        archivo.read(reinterpret_cast<char*>(&anioPublicacion), sizeof(anioPublicacion));

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        paisPublicacion.resize(size);
        archivo.read(&paisPublicacion[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        obraOriginal.resize(size);
        archivo.read(&obraOriginal[0], size);
    }
};

//--------------------------------------------------------
// Cancion
//--------------------------------------------------------
class Cancion {
public:
    std::string nombreCancion;
    std::vector<Artista> artistas;
    std::vector<Version> versiones;
    std::vector<EnlacePlataforma> enlaces;
    int duracion;

    // Nuevos campos para consultas 4, 5 y 10:
    std::string genero;
    int anioGrabacion;

    Cancion* siguiente;

    Cancion() : siguiente(nullptr) {}

    void guardar(std::ofstream& archivo) {
        size_t size = nombreCancion.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(nombreCancion.c_str(), size);
        
        archivo.write(reinterpret_cast<char*>(&duracion), sizeof(duracion));
        
        size = artistas.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        for (auto& a : artistas) a.guardar(archivo);
        
        size = versiones.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        for (auto& v : versiones) v.guardar(archivo);
        
        size = enlaces.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        for (auto& e : enlaces) e.guardar(archivo);

        // Guardar nuevos campos:
        size = genero.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(genero.c_str(), size);

        archivo.write(reinterpret_cast<char*>(&anioGrabacion), sizeof(anioGrabacion));
    }

    void cargar(std::ifstream& archivo) {
        size_t size;
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        nombreCancion.resize(size);
        archivo.read(&nombreCancion[0], size);
        
        archivo.read(reinterpret_cast<char*>(&duracion), sizeof(duracion));
        
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        artistas.resize(size);
        for (auto& a : artistas) a.cargar(archivo);
        
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        versiones.resize(size);
        for (auto& v : versiones) v.cargar(archivo);
        
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        enlaces.resize(size);
        for (auto& e : enlaces) e.cargar(archivo);

        // Cargar nuevos campos:
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        genero.resize(size);
        archivo.read(&genero[0], size);

        archivo.read(reinterpret_cast<char*>(&anioGrabacion), sizeof(anioGrabacion));
    }
};

//--------------------------------------------------------
// Album
//--------------------------------------------------------
class Album {
public:
    std::string titulo;
    std::string nombreArtistico;
    int anioPublicacion;
    
    // Miembros para las canciones y para el árbol AVL:
    Cancion* listaCanciones;
    Album* izquierda;
    Album* derecha;
    int altura;

    // Nuevos campos para las consultas:
    std::string editora;
    std::string estudioGrabacion;
    std::string paisGrabacion;
    std::string ciudadGrabacion;
    std::string encargadoFotografia;
    std::string encargadoCoverArt;
    std::vector<EnlacePlataforma> enlacesAlbum;

    Album() : listaCanciones(nullptr), izquierda(nullptr), derecha(nullptr), altura(1) {}

    void guardar(std::ofstream& archivo) {
        size_t size = titulo.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(titulo.c_str(), size);
        
        size = nombreArtistico.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(nombreArtistico.c_str(), size);
        
        archivo.write(reinterpret_cast<char*>(&anioPublicacion), sizeof(anioPublicacion));

        // Guardar nuevos campos:
        size = editora.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(editora.c_str(), size);

        size = estudioGrabacion.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(estudioGrabacion.c_str(), size);

        size = paisGrabacion.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(paisGrabacion.c_str(), size);

        size = ciudadGrabacion.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(ciudadGrabacion.c_str(), size);

        size = encargadoFotografia.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(encargadoFotografia.c_str(), size);

        size = encargadoCoverArt.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(encargadoCoverArt.c_str(), size);

        // Guardar lista de canciones: primero la cantidad y luego cada una
        int numCanciones = 0;
        Cancion* actual = listaCanciones;
        while (actual) {
            numCanciones++;
            actual = actual->siguiente;
        }
        archivo.write(reinterpret_cast<char*>(&numCanciones), sizeof(numCanciones));
        
        actual = listaCanciones;
        while (actual) {
            actual->guardar(archivo);
            actual = actual->siguiente;
        }
    }

    void cargar(std::ifstream& archivo) {
        size_t size;
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        titulo.resize(size);
        archivo.read(&titulo[0], size);
        
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        nombreArtistico.resize(size);
        archivo.read(&nombreArtistico[0], size);
        
        archivo.read(reinterpret_cast<char*>(&anioPublicacion), sizeof(anioPublicacion));

        // Cargar nuevos campos:
        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        editora.resize(size);
        archivo.read(&editora[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        estudioGrabacion.resize(size);
        archivo.read(&estudioGrabacion[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        paisGrabacion.resize(size);
        archivo.read(&paisGrabacion[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        ciudadGrabacion.resize(size);
        archivo.read(&ciudadGrabacion[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        encargadoFotografia.resize(size);
        archivo.read(&encargadoFotografia[0], size);

        archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
        encargadoCoverArt.resize(size);
        archivo.read(&encargadoCoverArt[0], size);

        // Cargar lista de canciones
        int numCanciones;
        archivo.read(reinterpret_cast<char*>(&numCanciones), sizeof(numCanciones));
        
        Cancion* ultima = nullptr;
        listaCanciones = nullptr;
        for (int i = 0; i < numCanciones; i++) {
            Cancion* nueva = new Cancion();
            nueva->cargar(archivo);
            nueva->siguiente = nullptr;
            if (!listaCanciones) {
                listaCanciones = nueva;
            } else {
                ultima->siguiente = nueva;
            }
            ultima = nueva;
        }
    }
};

#endif

