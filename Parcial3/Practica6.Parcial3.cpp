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
    float promedio;
};
int main() {

   vector <Alumno> alumnos;
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
        Alumno alumno;

        getline(ss, alumno.nombre, '|');
        getline(ss, alumno.matricula, '|');
        ss >> alumno.calificacion[0] >> sep
           >> alumno.calificacion[1] >> sep
           >> alumno.calificacion[2];
        alumno.promedio = (alumno.calificacion[0] + alumno.calificacion[1] + alumno.calificacion[2]) / 3;
        alumnos.push_back(alumno);
    }
 if (alumnos.empty()) {
    cout << "No hay alumnos en alumnos.txt." << endl;
    return 0;
}
    for (int i = 0; i < alumnos.size() - 1; i++) {
        for (int j = 0; j < alumnos.size() - 1 - i; j++) {
            if (alumnos[j].promedio < alumnos[j + 1].promedio) {
                Alumno temporal = alumnos[j];
                alumnos[j] = alumnos[j + 1];
                alumnos[j + 1] = temporal;
            }
        }
    }

    ofstream salida("Reporte.txt");
    if (!salida) {
        cout << "Error al crear el archivo." << endl;
        return 1;
    }

    for (int i = 0; i < alumnos.size(); i++) {
        salida << alumnos[i].nombre << "|"
               << alumnos[i].matricula << "|"
               << alumnos[i].calificacion[0] << "|"
               << alumnos[i].calificacion[1] << "|"
               << alumnos[i].calificacion[2] << "|"
               << alumnos[i].promedio << endl;
    }
    cout << "El reporte se ah hecho correctamente";
    return 0;
}
