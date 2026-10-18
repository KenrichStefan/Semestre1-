#include <iostream>
#include <string>
#include <vector>

using namespace std;
 struct Alumno   { string nombre; string matricula; float calif[3]; int grupo; float promedio; };
struct Maestro  { string nombre; string materia; };
struct Grupo    { string nombre; string carrera; int numerodegrupo; };

string leerLinea(const string& mensaje) {
    string texto;
    cout << mensaje;
    getline(cin >> ws, texto);   
    return texto;
}

int main(){
    
 int AlumnosCantidad = 0;
int GrupoCantidad = 0;
int MaestroCantidad = 0;
float MejorPromedio = 0;
int Z = 0;
string MejorAlumno;
    int n = 0;
    int M = 0;
    bool S = true;
   vector <Alumno> Alumnos;
   vector <Maestro> Maestros;
   vector <Grupo> Grupos;


    do {

        cout << "Menú" << endl << "1. Capturar N alumnos" << endl << "2. Capturar grupos y carreras" << endl << "3. Capturar maestros" << endl << "4. Mostrar reportes" << endl << "5. Salir" << endl << "Ingrese su opción" << endl;
        cin >> n;
        switch (n) {
            case 1:
             if (GrupoCantidad == 0){
                cout << "Se necesitan grupos para capturar los alumnos"<< endl;
             }
             else {
                    cout << "Elige el numero de alumnos que deseas ingresar"<< endl;
                    cin >> AlumnosCantidad;
                    if (AlumnosCantidad < 1) {
                    cout << "Numero no valido, ingrese otro numero"<< endl;
                    break;
                    } else {
                    Alumnos.resize(AlumnosCantidad);
                    for (int i = 0; i < AlumnosCantidad; i++) {
                        Alumnos[i].nombre = leerLinea("Nombre del alumno " + to_string(i + 1) + ": ");
                        cout << "Ingrese la matricula del alumno " << Alumnos[i].nombre << ": "<< endl;
                        cin >> Alumnos[i].matricula;
                        cout << "Eliga el numero del grupo donde estara el alumno " << Alumnos[i].nombre << ": "<< endl; 
                        for (int k = 0; k < GrupoCantidad; k++) {
                        cout << "Grupo " << k + 1 << " " << Grupos[k].nombre << " " << Grupos[k].carrera << endl;
                        }
                       cin >> Z;
                       while (Z < 1 || Z > GrupoCantidad) {
                     cout << "Grupo no valido, elige otro: " << endl;
                     cin >> Z;
                    }
                            Alumnos[i].grupo = Z - 1;
                        
                        cout << "Ingrese las calificaciones del alumno " << Alumnos[i].nombre << ": "<< endl;
                        for (int j = 0; j < 3; j++) {
                            cin >> Alumnos[i].calif[j];
                            while (Alumnos[i].calif[j] <= 0 || Alumnos[i].calif[j] > 10) {
                                cout << "Calificacion no valida, ingrese otra: ";
                                cin >> Alumnos[i].calif[j];
                            }
                        }
                    }
                }
            }
                S = true;
                break;
            

            case 2:{
            GrupoCantidad = 0;
cout << "Ingrese la cantidad de grupos a crear" << endl;
cin >> GrupoCantidad;
if  (GrupoCantidad < 1) {
    cout << "Numero no valido, ingrese otro" << endl;
}
else {
Grupos.resize(GrupoCantidad);
 for (int k = 0; k < GrupoCantidad; k++) {
    Grupos[k].nombre  = leerLinea("Nombre del grupo " + to_string(k + 1) + ": ");
Grupos[k].carrera = leerLinea("Carrera del grupo " + to_string(k + 1) + ": ");
Grupos[k].numerodegrupo = k;
 }
}
                break;
}
            case 3:{
MaestroCantidad = 0;
                cout << "Ingrese la cantidad de maestros"<< endl;
                cin >> MaestroCantidad;
if  (MaestroCantidad < 1) {
    cout << "Numero no valido, ingrese otro" << endl;
}
else {
Maestros.resize(MaestroCantidad);
for (int p = 0; p < MaestroCantidad; p++) {
    Maestros[p].nombre  = leerLinea("Nombre del maestro " + to_string(p + 1) + ": ");
Maestros[p].materia = leerLinea("Materia que imparte el maestro " + to_string(p + 1) + ": ");
}
}

S = true;
            
                break;
            }
            case 4:
            {
                if (GrupoCantidad == 0 || AlumnosCantidad == 0) {
                    cout << "Faltan datos para poder escribir el reporte" << endl;
                } else {
                    cout << "Mostrando reporte" << endl;
                    cout << "Promedio de los alumnos" << endl;
                    for (int i = 0; i < AlumnosCantidad; i++) {
                        Alumnos[i].promedio = (Alumnos[i].calif[0] + Alumnos[i].calif[1] + Alumnos[i].calif[2]) / 3;
                    cout << "El alumno " << Alumnos[i].nombre << " promedio: " << Alumnos[i].promedio << endl;
                    }

                    cout << "Mejor promedio por grupo" << endl;
                    for (int k = 0; k < GrupoCantidad; k++){
                        M = 0;
                        MejorPromedio = 0;
                        MejorAlumno = "";
                     for (int i = 0; i < AlumnosCantidad; i++){
                     if (Alumnos[i].grupo == k){
                        M = M + 1;
                      if (MejorPromedio < Alumnos[i].promedio){
                      MejorPromedio = Alumnos[i].promedio;
                      MejorAlumno = Alumnos[i].nombre;
                      }
                     }
                    }
                         cout <<"Para el grupo " << Grupos[k].nombre << ", el mejor promedio es " << MejorPromedio << " del alumno " << MejorAlumno << endl;
                         cout << "En la carrera de " << Grupos[k].carrera << ", la cantidad de alumnos es " << M << endl;
                }
                }
                S = true;
                break;
            
            }
            case 5:
                cout << "Saliendo del programa";
                S = false;
                break;

            default:
                cout << "Por favor ingrese un numero del 1 al 5";
                S = true;
                break;
        }
    } while (S == true);

    return 0;
}
