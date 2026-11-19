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
    string nombreArchivo;

    cout << "Escribe el nombre del archivo que desea buscar: ";
    getline(cin, nombreArchivo);

    ifstream archivo(nombreArchivo.c_str());
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    cout << "El archivo se ha abierto correctamente." << endl;

    archivo.close();
    return 0;
}
