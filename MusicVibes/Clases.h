#ifndef CLASES_H
#define CLASES_H

#include <vector>
#include <string>
#include <fstream>

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

class Artista {
public:
    std::string nombreReal;
    std::string nombreArtistico;
    std::string paisOrigen;
    std::string instrumento;

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
    }
};

class Version {
public:
    std::string tituloVersion;
    std::string tipoVersion;
    std::vector<EnlacePlataforma> enlaces;

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
    }
};

class Cancion {
public:
    std::string nombreCancion;
    std::vector<Artista> artistas;
    std::vector<Version> versiones;
    std::vector<EnlacePlataforma> enlaces;
    int duracion;
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
    }
};

class Album {
public:
    std::string titulo;
    std::string nombreArtistico;
    int anioPublicacion;
    Cancion* listaCanciones;
    Album* izquierda;
    Album* derecha;
    int altura; // Agregar este atributo

    Album() : listaCanciones(nullptr), izquierda(nullptr), derecha(nullptr), altura(1) {}

    void guardar(std::ofstream& archivo) {
        size_t size = titulo.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(titulo.c_str(), size);
        
        size = nombreArtistico.size();
        archivo.write(reinterpret_cast<char*>(&size), sizeof(size));
        archivo.write(nombreArtistico.c_str(), size);
        
        archivo.write(reinterpret_cast<char*>(&anioPublicacion), sizeof(anioPublicacion));
        
        // Guardar canciones como lista enlazada
        Cancion* actual = listaCanciones;
        while (actual) {
            actual->guardar(archivo);
            actual = actual->siguiente;
        }
        // Marcar fin de lista
        bool fin = true;
        archivo.write(reinterpret_cast<char*>(&fin), sizeof(fin));
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
        
        // Cargar canciones
        bool fin;
        Cancion* ultima = nullptr;
        do {
            Cancion* nueva = new Cancion();
            nueva->cargar(archivo);
            archivo.read(reinterpret_cast<char*>(&fin), sizeof(fin));
            
            if (!listaCanciones) listaCanciones = nueva;
            else ultima->siguiente = nueva;
            ultima = nueva;
        } while (!fin);
    }
};

#endif
