#ifndef AVL_H
#define AVL_H

#include "Clases.h"
#include <fstream>
#include <algorithm>

class AVL {
private:
    Album* raiz;

    int altura(Album* nodo) {
        return nodo ? nodo->altura : 0;
    }

    int balance(Album* nodo) {
        return nodo ? altura(nodo->izquierda) - altura(nodo->derecha) : 0;
    }

    Album* rotacionDerecha(Album* y) {
        Album* x = y->izquierda;
        Album* T2 = x->derecha;
        x->derecha = y;
        y->izquierda = T2;
        y->altura = std::max(altura(y->izquierda), altura(y->derecha)) + 1;
        x->altura = std::max(altura(x->izquierda), altura(x->derecha)) + 1;
        return x;
    }

    Album* rotacionIzquierda(Album* x) {
        Album* y = x->derecha;
        Album* T2 = y->izquierda;
        y->izquierda = x;
        x->derecha = T2;
        x->altura = std::max(altura(x->izquierda), altura(x->derecha)) + 1;
        y->altura = std::max(altura(y->izquierda), altura(y->derecha)) + 1;
        return y;
    }

    Album* insertar(Album* nodo, Album* nuevo) {
        if (!nodo) return nuevo;

        if (nuevo->titulo < nodo->titulo)
            nodo->izquierda = insertar(nodo->izquierda, nuevo);
        else if (nuevo->titulo > nodo->titulo)
            nodo->derecha = insertar(nodo->derecha, nuevo);
        else
            return nodo;

        nodo->altura = 1 + std::max(altura(nodo->izquierda), altura(nodo->derecha));
        int balanceFactor = balance(nodo);

        if (balanceFactor > 1 && nuevo->titulo < nodo->izquierda->titulo)
            return rotacionDerecha(nodo);
        if (balanceFactor < -1 && nuevo->titulo > nodo->derecha->titulo)
            return rotacionIzquierda(nodo);
        if (balanceFactor > 1 && nuevo->titulo > nodo->izquierda->titulo) {
            nodo->izquierda = rotacionIzquierda(nodo->izquierda);
            return rotacionDerecha(nodo);
        }
        if (balanceFactor < -1 && nuevo->titulo < nodo->derecha->titulo) {
            nodo->derecha = rotacionDerecha(nodo->derecha);
            return rotacionIzquierda(nodo);
        }

        return nodo;
    }

    void inOrder(Album* nodo, std::vector<Album*>& resultado) {
        if (!nodo) return;
        inOrder(nodo->izquierda, resultado);
        resultado.push_back(nodo);
        inOrder(nodo->derecha, resultado);
    }

        void liberarMemoria(Album* nodo) {
        if (!nodo) return;
        liberarMemoria(nodo->izquierda);
        liberarMemoria(nodo->derecha);

        // Liberar lista de canciones
        Cancion* actual = nodo->listaCanciones;
        while (actual) {
            Cancion* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }

        delete nodo;
    }
	Album* buscar(Album* nodo, const std::string& titulo) {
    if (!nodo || nodo->titulo == titulo)
        return nodo;
    if (titulo < nodo->titulo)
        return buscar(nodo->izquierda, titulo);
    return buscar(nodo->derecha, titulo);
}

    // ---- Funciones nuevas para eliminación ----

    Album* minValueNode(Album* nodo) {
        Album* current = nodo;
        while (current && current->izquierda != nullptr)
             current = current->izquierda;
        return current;
    }

    void liberarAlbumRecursos(Album* album) {
        Cancion* actual = album->listaCanciones;
        while (actual) {
            Cancion* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        album->listaCanciones = nullptr;
    }

    Album* eliminar(Album* nodo, const std::string& titulo) {
        if (!nodo) return nodo;

        if (titulo < nodo->titulo) {
            nodo->izquierda = eliminar(nodo->izquierda, titulo);
        } else if (titulo > nodo->titulo) {
            nodo->derecha = eliminar(nodo->derecha, titulo);
        } else {
            // Nodo a eliminar encontrado
            if (nodo->izquierda == nullptr || nodo->derecha == nullptr) {
                Album* temp = nodo->izquierda ? nodo->izquierda : nodo->derecha;
                liberarAlbumRecursos(nodo);
                delete nodo;
                return temp;
            } else {
                Album* temp = minValueNode(nodo->derecha);
                nodo->titulo = temp->titulo;
                nodo->nombreArtistico = temp->nombreArtistico;
                nodo->anioPublicacion = temp->anioPublicacion;
                std::swap(nodo->listaCanciones, temp->listaCanciones);
                nodo->derecha = eliminar(nodo->derecha, temp->titulo);
            }
        }
        
        if (!nodo) return nodo;
        
        nodo->altura = 1 + std::max(altura(nodo->izquierda), altura(nodo->derecha));
        int balanceFactor = balance(nodo);
        
        if (balanceFactor > 1 && balance(nodo->izquierda) >= 0)
            return rotacionDerecha(nodo);
        if (balanceFactor > 1 && balance(nodo->izquierda) < 0) {
            nodo->izquierda = rotacionIzquierda(nodo->izquierda);
            return rotacionDerecha(nodo);
        }
        if (balanceFactor < -1 && balance(nodo->derecha) <= 0)
            return rotacionIzquierda(nodo);
        if (balanceFactor < -1 && balance(nodo->derecha) > 0) {
            nodo->derecha = rotacionDerecha(nodo->derecha);
            return rotacionIzquierda(nodo);
        }
        
        return nodo;
    }

    // -------------------------------------------

    void guardarRecursivo(Album* nodo, std::ofstream& archivo) {
        bool existe = (nodo != nullptr);
        archivo.write(reinterpret_cast<char*>(&existe), sizeof(existe));
        if (!existe)
            return;
        
        nodo->guardar(archivo);
        guardarRecursivo(nodo->izquierda, archivo);
        guardarRecursivo(nodo->derecha, archivo);
    }

    Album* cargarRecursivo(std::ifstream& archivo) {
        bool existe;
        archivo.read(reinterpret_cast<char*>(&existe), sizeof(existe));
        if (!existe)
            return nullptr;
        
        Album* nuevo = new Album();
        nuevo->cargar(archivo);
        nuevo->izquierda = cargarRecursivo(archivo);
        nuevo->derecha = cargarRecursivo(archivo);
        return nuevo;
    }

public:
    AVL() : raiz(nullptr) {}

    void insertar(Album* nuevo) {
        raiz = insertar(raiz, nuevo);
    }

    Album* buscarAlbum(const std::string& titulo) {
        // La función buscar se había definido previamente (ya corregida)
        return buscar(raiz, titulo);
    }

    std::vector<Album*> obtenerTodosAlbumes() {
        std::vector<Album*> resultado;
        inOrder(raiz, resultado);
        return resultado;
    }

    void liberarArbol() {
        liberarMemoria(raiz);
        raiz = nullptr;
    }

    void guardar(const std::string& filename) {
        std::ofstream archivo(filename, std::ios::binary);
        guardarRecursivo(raiz, archivo);
    }

    void cargar(const std::string& filename) {
        std::ifstream archivo(filename, std::ios::binary);
        if (!archivo) return;
        
        liberarArbol(); // Liberar memoria antes de cargar
        raiz = cargarRecursivo(archivo);
    }
    
    // Función pública para eliminar un álbum
    void eliminarAlbum(const std::string& titulo) {
        raiz = eliminar(raiz, titulo);
    }
};

#endif

