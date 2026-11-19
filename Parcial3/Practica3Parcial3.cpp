#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Alumno {
    string nombre;
    string matricula;
    float calificacion[3];
};

int main() {
    Alumno nuevo;
   
    cout << "Ingrese el nombre del alumno: ";
    cin >> nuevo.nombre;

    cout << "Ingrese su matricula: ";
    cin >> nuevo.matricula;
    
    cout << "Ingrese sus calificaciones: ";
    for (int j = 0; j < 3; j++) {
        cin >> nuevo.calificacion[j];
        if (nuevo.calificacion[j] < 0 || nuevo.calificacion[j] > 10) {
            cout << "Error: la calificación debe estar entre 0 y 10." << endl;
            return 1;
        }
    }

    ofstream archivo("alumnos.txt", ios::app);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    archivo << nuevo.nombre << "|"
            << nuevo.matricula << "|"
            << nuevo.calificacion[0] << "|"
            << nuevo.calificacion[1] << "|"
            << nuevo.calificacion[2] << endl;

    archivo.close();
    cout << "Alumno agregado. Los registros anteriores se conservan." << endl;
    return 0;
}