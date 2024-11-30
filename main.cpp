#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#define NUM_FOTOGRAMAS 100  // Número de fotogramas en el video
#define NUM_ARTICULACIONES 15  // Número de articulaciones por fotograma
#define TAM_POBLACION 10  // Número de individuos en la población
#define NUM_ITERACIONES 50  // Número de iteraciones del algoritmo genético
#define TASA_MUTACION 0.1  // Tasa de mutación
#define TASA_CRUZAMIENTO 0.8  // Tasa de cruzamiento

using namespace std;

// Estructura que representa un fotograma
struct Fotograma {
    vector<vector<double>> articulaciones; // Cada articulación tiene coordenadas (x, y, z)
};

// Generar un fotograma aleatorio (datos simulados)
Fotograma generarFotograma() {
    Fotograma fotograma;
    for (int i = 0; i < NUM_ARTICULACIONES; ++i) {
        fotograma.articulaciones.push_back({
            rand() % 100 / 10.0, 
            rand() % 100 / 10.0, 
            rand() % 100 / 10.0
        });
    }
    return fotograma;
}

// Calcular el ajuste (fitness) de un fotograma comparado con el objetivo
double calcularAjuste(const Fotograma& individuo, const Fotograma& objetivo) {
    double ajuste = 0.0;
    for (int i = 0; i < NUM_ARTICULACIONES; ++i) {
        double dx = individuo.articulaciones[i][0] - objetivo.articulaciones[i][0];
        double dy = individuo.articulaciones[i][1] - objetivo.articulaciones[i][1];
        double dz = individuo.articulaciones[i][2] - objetivo.articulaciones[i][2];
        ajuste += sqrt(dx * dx + dy * dy + dz * dz);
    }
    return 1.0 / (1.0 + ajuste); // Ajuste inversamente proporcional al error
}

// Mutar un individuo
void mutar(Fotograma& individuo) {
    for (int i = 0; i < NUM_ARTICULACIONES; ++i) {
        if ((rand() % 100) / 100.0 < TASA_MUTACION) {
            individuo.articulaciones[i][0] += (rand() % 10 - 5) / 10.0;
            individuo.articulaciones[i][1] += (rand() % 10 - 5) / 10.0;
            individuo.articulaciones[i][2] += (rand() % 10 - 5) / 10.0;
        }
    }
}

// Cruzar dos individuos
Fotograma cruzar(const Fotograma& padre1, const Fotograma& padre2) {
    Fotograma hijo;
    for (int i = 0; i < NUM_ARTICULACIONES; ++i) {
        if ((rand() % 100) / 100.0 < TASA_CRUZAMIENTO) {
            hijo.articulaciones.push_back(padre1.articulaciones[i]);
        } else {
            hijo.articulaciones.push_back(padre2.articulaciones[i]);
        }
    }
    return hijo;
}

// Mostrar la población
void mostrarPoblacion(const vector<Fotograma>& poblacion, const Fotograma& objetivo) {
    for (int i = 0; i < poblacion.size(); ++i) {
        cout << "Individuo " << i + 1 
             << " Ajuste: " << calcularAjuste(poblacion[i], objetivo) 
             << endl;
    }
}


int main() {
    srand(time(0));

    // Generar los datos objetivo (fotogramas ideales)
    vector<Fotograma> fotogramasObjetivo;
    for (int i = 0; i < NUM_FOTOGRAMAS; ++i) {
        fotogramasObjetivo.push_back(generarFotograma());
    }

    // Generar la población inicial
    vector<Fotograma> poblacion;
    for (int i = 0; i < TAM_POBLACION; ++i) {
        poblacion.push_back(generarFotograma());
    }

    // Algoritmo genético
    for (int iteracion = 0; iteracion < NUM_ITERACIONES; ++iteracion) {
        cout << "Iteración " << iteracion + 1 << endl;

        // Evaluar la población
        mostrarPoblacion(poblacion, fotogramasObjetivo[iteracion % NUM_FOTOGRAMAS]);

        // Crear nueva población
        vector<Fotograma> nuevaPoblacion;
        for (int i = 0; i < TAM_POBLACION; ++i) {
            int padre1 = rand() % TAM_POBLACION;
            int padre2 = rand() % TAM_POBLACION;
            Fotograma hijo = cruzar(poblacion[padre1], poblacion[padre2]);
            mutar(hijo);
            nuevaPoblacion.push_back(hijo);
        }
        poblacion = nuevaPoblacion;
    }

    cout << "Optimización completada." << endl;
    return 0;
}