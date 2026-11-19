#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Alumno {
    string nombre;
    string matricula;
    float calificacion[3];
};

int main() {
    vector<Alumno> alumnos;

    ifstream archivo("alumnos.txt");
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        char sep;
        Alumno a;

        getline(ss, a.nombre, '|');
        getline(ss, a.matricula, '|');
        ss >> a.calificacion[0] >> sep
           >> a.calificacion[1] >> sep
           >> a.calificacion[2];

        alumnos.push_back(a);
    }

    archivo.close();

    cout << "Alumnos leidos: " << endl;
    for (size_t i = 0; i < alumnos.size(); i++) {
        cout << alumnos[i].nombre << " | "
             << alumnos[i].matricula << " | "
             << alumnos[i].calificacion[0] << ", "
             << alumnos[i].calificacion[1] << ", "
             << alumnos[i].calificacion[2] << endl;
    }

    return 0;
}