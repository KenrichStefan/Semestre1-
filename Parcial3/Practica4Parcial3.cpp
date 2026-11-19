#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Alumno {
    string nombre;
    string matricula;
    float calificacion[3];
};

void escribirString(ofstream& out, const string& s) {
    size_t len = s.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(s.data(), len);
}
    
int main() {
    Alumno alumnos[5];
    ofstream archivo("alumnosBinario.bin", ios::binary);
     if (!archivo) {
        cout << "Error al crear el archivo." << endl;
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        cout << "Ingrese el nombre del alumno: ";
        cin >> alumnos[i].nombre;

        cout << "Ingrese su matricula: ";
        cin >> alumnos[i].matricula;

        cout << "Ingrese sus calificaciones: ";
        for (int j = 0; j < 3; j++) {
            cin >> alumnos[i].calificacion[j];
            if (alumnos[i].calificacion[j] < 0 || alumnos[i].calificacion[j] > 10) {
                cout << "Error: la calificación debe estar entre 0 y 10." << endl;
                archivo.close();
                return 1;

            }
        }
        escribirString(archivo, alumnos[i].nombre);
        escribirString(archivo, alumnos[i].matricula);
        archivo.write(reinterpret_cast<const char*>(alumnos[i].calificacion),
                      sizeof(alumnos[i].calificacion));

    }
 archivo.close();
    cout << "Se guardaron 5 alumnos en alumnosBinario.bin" << endl;
    return 0;
}