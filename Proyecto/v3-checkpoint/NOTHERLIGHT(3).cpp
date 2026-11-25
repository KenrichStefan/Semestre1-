#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include <cstdlib>

using namespace std;

const int CANTIDAD_MAXIMA = numeric_limits<int>::max();
const int CALIFICACIONES_POR_ALUMNO = 3;

struct Alumno
{
	string nombre;
	string matricula;
	float calificaciones[CALIFICACIONES_POR_ALUMNO];
	int indiceGrupo;
	float promedio;
};

struct Maestro
{
	string nombre;
	string materia;
};

struct Grupo
{
	string nombre;
	string carrera;
	int numeroDeGrupo;
};

// ---------------------------------------------------------------
// Lectura segura de datos

// Si ya no hay mas datos de entrada (Ctrl+D / Ctrl+Z), se evita un ciclo infinito.
void terminarPorFinDeEntrada()
{
	cout << endl
		 << "Se termino la entrada de datos. Saliendo del programa." << endl;
	exit(0);
}

string leerLinea(const string &mensaje)
{
	string texto;
	cout << mensaje;
	if (!getline(cin >> ws, texto))
	{
		terminarPorFinDeEntrada();
	}
	return texto;
}

// Pide un entero y repite la pregunta hasta que sea un numero dentro del rango.
int leerEntero(const string &mensaje, int minimo, int maximo)
{
	int valor;
	while (true)
	{
		cout << mensaje;
		if (cin >> valor)
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (valor >= minimo && valor <= maximo)
			{
				return valor;
			}
		}
		else
		{
			if (cin.eof())
			{
				terminarPorFinDeEntrada();
			}
			cin.clear();										 // quita el estado de error
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // descarta lo que se escribio mal
		}
		cout << "Entrada no valida. Ingresa un numero entre " << minimo << " y ";
		if (maximo == CANTIDAD_MAXIMA)
		{
			cout << "el maximo permitido." << endl;
		}
		else
		{
			cout << maximo << "." << endl;
		}
	}
}

// Igual que leerEntero, pero para numeros con decimales (calificaciones).
float leerDecimal(const string &mensaje, float minimo, float maximo)
{
	float valor;
	while (true)
	{
		cout << mensaje;
		if (cin >> valor)
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (valor >= minimo && valor <= maximo)
			{
				return valor;
			}
		}
		else
		{
			if (cin.eof())
			{
				terminarPorFinDeEntrada();
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "Entrada no valida. Ingresa un numero entre " << minimo << " y " << maximo << "." << endl;
	}
}

//----------------------------------------------------------------

// ---------------------------------------------------------------
// calculo de promedio
float calcularPromedio(const Alumno &alumno)
{
	float suma = 0;
	for (int i = 0; i < CALIFICACIONES_POR_ALUMNO; i++)
	{
		suma += alumno.calificaciones[i];
	}
	return suma / CALIFICACIONES_POR_ALUMNO;
}

// Devuelve cada carrera una sola vez, aunque tenga varios grupos.
vector<string> obtenerCarrerasUnicas(const vector<Grupo> &grupos)
{
	vector<string> carreras;
	for (const Grupo &grupo : grupos)
	{
		bool yaExiste = false;
		for (const string &carrera : carreras)
		{
			if (carrera == grupo.carrera)
			{
				yaExiste = true;
			}
		}
		if (!yaExiste)
		{
			carreras.push_back(grupo.carrera);
		}
	}
	return carreras;
}
//----------------------------------------------------------------

// ---------------------------------------------------------------
// Void de Capturas (1, 2, 3)

void capturarGrupos(vector<Grupo> &grupos)
{
	int cantidad = leerEntero("Cuantos grupos deseas agregar: ", 1, CANTIDAD_MAXIMA);

	for (int i = 0; i < cantidad; i++)
	{
		Grupo nuevoGrupo;
		nuevoGrupo.numeroDeGrupo = static_cast<int>(grupos.size()) + 1;
		nuevoGrupo.nombre = leerLinea("Nombre del grupo " + to_string(nuevoGrupo.numeroDeGrupo) + ": ");
		nuevoGrupo.carrera = leerLinea("Carrera del grupo " + to_string(nuevoGrupo.numeroDeGrupo) + ": ");
		grupos.push_back(nuevoGrupo);
	}
}

void capturarMaestros(vector<Maestro> &maestros)
{
	int cantidad = leerEntero("Cuantos maestros deseas agregar: ", 1, CANTIDAD_MAXIMA);

	for (int i = 0; i < cantidad; i++)
	{
		int numeroMaestro = static_cast<int>(maestros.size()) + 1;
		Maestro nuevoMaestro;
		nuevoMaestro.nombre = leerLinea("Nombre del maestro " + to_string(numeroMaestro) + ": ");
		nuevoMaestro.materia = leerLinea("Materia que imparte el maestro " + to_string(numeroMaestro) + ": ");
		maestros.push_back(nuevoMaestro);
	}
}

void capturarAlumnos(vector<Alumno> &alumnos, const vector<Grupo> &grupos)
{
	if (grupos.empty())
	{
		cout << "Se necesitan grupos para capturar los alumnos" << endl;
		return;
	}

	int totalGrupos = static_cast<int>(grupos.size());
	int cantidad = leerEntero("Cuantos alumnos deseas ingresar: ", 1, CANTIDAD_MAXIMA);

	for (int i = 0; i < cantidad; i++)
	{
		Alumno nuevoAlumno;

		nuevoAlumno.nombre = leerLinea("Nombre del alumno " + to_string(alumnos.size() + 1) + ": ");
		nuevoAlumno.matricula = leerLinea("Matricula del alumno " + nuevoAlumno.nombre + ": ");

		cout << "Grupos disponibles:" << endl;
		for (int g = 0; g < totalGrupos; g++)
		{
			cout << "  " << g + 1 << ". " << grupos[g].nombre << " - " << grupos[g].carrera << endl;
		}
		int numeroGrupo = leerEntero("Elige el numero del grupo para " + nuevoAlumno.nombre + ": ", 1, totalGrupos);
		nuevoAlumno.indiceGrupo = numeroGrupo - 1;

		cout << "Ingresa las calificaciones de " << nuevoAlumno.nombre << " (0 a 10):" << endl;
		for (int j = 0; j < CALIFICACIONES_POR_ALUMNO; j++)
		{
			nuevoAlumno.calificaciones[j] = leerDecimal("  Calificacion " + to_string(j + 1) + ": ", 0, 10);
		}

		nuevoAlumno.promedio = calcularPromedio(nuevoAlumno);
		alumnos.push_back(nuevoAlumno);
	}
}
//----------------------------------------------------------------

// ---------------------------------------------------------------
// Reporte

void mostrarReportes(const vector<Alumno> &alumnos, const vector<Grupo> &grupos)
{
	if (grupos.empty() || alumnos.empty())
	{
		cout << "Faltan datos para poder escribir el reporte" << endl;
		return;
	}

	cout << endl
		 << "Mostrando reporte" << endl;

	cout << endl
		 << "Promedio de los alumnos" << endl;
	for (const Alumno &alumno : alumnos)
	{
		cout << "El alumno " << alumno.nombre << " promedio: " << alumno.promedio << endl;
	}

	cout << endl
		 << "Mejor promedio por grupo" << endl;
	int totalGrupos = static_cast<int>(grupos.size());
	int totalAlumnos = static_cast<int>(alumnos.size());
	for (int g = 0; g < totalGrupos; g++)
	{
		int indiceMejorAlumno = -1; // -1 significa "todavia no hay alumnos en este grupo"

		for (int i = 0; i < totalAlumnos; i++)
		{
			if (alumnos[i].indiceGrupo == g)
			{
				if (indiceMejorAlumno == -1 || alumnos[i].promedio > alumnos[indiceMejorAlumno].promedio)
				{
					indiceMejorAlumno = i;
				}
			}
		}

		if (indiceMejorAlumno == -1)
		{
			cout << "El grupo " << grupos[g].nombre << " no tiene alumnos registrados" << endl;
		}
		else
		{
			cout << "Para el grupo " << grupos[g].nombre << ", el mejor promedio es "
				 << alumnos[indiceMejorAlumno].promedio << " del alumno "
				 << alumnos[indiceMejorAlumno].nombre << endl;
		}
	}

	cout << endl
		 << "Alumnos por carrera" << endl;
	vector<string> carreras = obtenerCarrerasUnicas(grupos);
	for (const string &carrera : carreras)
	{
		int alumnosEnCarrera = 0;
		for (const Alumno &alumno : alumnos)
		{
			if (grupos[alumno.indiceGrupo].carrera == carrera)
			{
				alumnosEnCarrera++;
			}
		}
		cout << "En la carrera de " << carrera << ", la cantidad de alumnos es " << alumnosEnCarrera << endl;
	}
}
//-----------------------------------------------------------------------
// Void de carga
void CargarDatos(vector<Alumno> &alumnos,
				 vector<Grupo> &grupos,
				 vector<Maestro> &maestros)
{
	ifstream archivoEntrada("NOTHERLIGHT-guardado.txt");
	if (!archivoEntrada)
	{
		cout << "No hay archivo guardado. Se inicia con datos vacios." << endl;
		return;
	}

	// Se limpian los vectores para no duplicar datos si se carga mas de una vez
	alumnos.clear();
	grupos.clear();
	maestros.clear();

	string linea;
	char sep;

	getline(archivoEntrada, linea); // encabezado "Maestros"
	while (getline(archivoEntrada, linea))
	{
		if (linea.empty())
			break;
		stringstream ss(linea);
		Maestro maestro;
		getline(ss, maestro.nombre, '|');
		getline(ss, maestro.materia);
		maestros.push_back(maestro);
	}

	getline(archivoEntrada, linea); // encabezado "Grupos"
	while (getline(archivoEntrada, linea))
	{
		if (linea.empty())
			break;
		stringstream ss(linea);
		Grupo grupo;
		ss >> grupo.numeroDeGrupo >> sep >> sep;
		getline(ss, grupo.nombre, '|');
		getline(ss, grupo.carrera);
		grupos.push_back(grupo);
	}

	getline(archivoEntrada, linea); // encabezado "Alumnos"
	while (getline(archivoEntrada, linea))
	{
		if (linea.empty())
			break;
		stringstream ss(linea);
		Alumno alumno;
		getline(ss, alumno.nombre, '|');
		getline(ss, alumno.matricula, '|');
		ss >> alumno.calificaciones[0] >> sep >> alumno.calificaciones[1] >> sep >> alumno.calificaciones[2] >> sep >> alumno.promedio >> sep >> alumno.indiceGrupo;
		alumno.indiceGrupo -= 1;
		if (ss.fail() || alumno.indiceGrupo < 0 ||
			alumno.indiceGrupo >= static_cast<int>(grupos.size()))
		{
			continue;
		}
		alumnos.push_back(alumno);
	}

	cout << "Datos cargados correctamente" << endl;
}
//-----------------------------------------------------------------------
// Exportación de datos (6, 7)
void GuardarDatos(const vector<Alumno> &alumnos,
				  const vector<Grupo> &grupos,
				  const vector<Maestro> &maestros)
{
	ofstream archivoSalida("NOTHERLIGHT-guardado.txt");
	if (!archivoSalida)
	{
		cout << "Error al crear el archivo." << endl;
		return;
	}
	archivoSalida << "Maestros" << endl;
	for (const Maestro &maestro : maestros)
	{
		archivoSalida << maestro.nombre << "|" << maestro.materia << endl;
	}
	archivoSalida << endl
				  << "Grupos" << endl;
	for (const Grupo &grupo : grupos)
	{
		archivoSalida << grupo.numeroDeGrupo << ".-" << grupo.nombre << "|" << grupo.carrera << endl;
	}
	archivoSalida << endl
				  << "Alumnos" << endl;
	for (const Alumno &alumno : alumnos)
	{
		archivoSalida << alumno.nombre << "|" << alumno.matricula << "|"
					  << alumno.calificaciones[0] << "|"
					  << alumno.calificaciones[1] << "|"
					  << alumno.calificaciones[2] << "|"
					  << alumno.promedio << "|";
		if (alumno.indiceGrupo >= 0 && alumno.indiceGrupo < static_cast<int>(grupos.size()))
		{
			archivoSalida << alumno.indiceGrupo + 1 << ".-" << grupos[alumno.indiceGrupo].nombre;
		}
		archivoSalida << endl;
	}
	cout << "Datos guardados en NOTHERLIGHT-guardado.txt" << endl;
}

//----------------------

void GenerarReportes(const vector<Alumno> &alumnos, const vector<Grupo> &grupos)
{
	if (grupos.empty() || alumnos.empty())
	{
		cout << "Faltan datos para poder escribir el reporte" << endl;
		return;
	}
	vector<Alumno> ordenados = alumnos;
	int total = static_cast<int>(ordenados.size());
	for (int i = 0; i < total - 1; i++)
	{
		for (int j = 0; j < total - 1 - i; j++)
		{
			if (ordenados[j].promedio < ordenados[j + 1].promedio)
			{
				Alumno temporal = ordenados[j];
				ordenados[j] = ordenados[j + 1];
				ordenados[j + 1] = temporal;
			}
		}
	}
	ofstream archivoReporte("NOTHERLIGHT-reporte.txt");
	if (!archivoReporte)
	{
		cout << "Error al crear el archivo." << endl;
		return;
	}
	archivoReporte << endl
				   << "Mostrando reporte" << endl;
	archivoReporte << endl
				   << "Promedio de los alumnos" << endl;
	for (int i = 0; i < total; i++)
	{
		archivoReporte << i + 1 << ".- El alumno " << ordenados[i].nombre << " promedio: " << ordenados[i].promedio << endl;
	}
	cout << "Reporte generado en NOTHERLIGHT-reporte.txt" << endl;
}

// ---------------------------------------------------------------
// Menu principal
// ---------------------------------------------------------------

void mostrarMenu()
{
	cout << endl;
	cout << "Menu" << endl;
	cout << "1. Capturar N alumnos" << endl;
	cout << "2. Capturar grupos y carreras" << endl;
	cout << "3. Capturar maestros" << endl;
	cout << "4. Mostrar reportes" << endl;
	cout << "5. Salir" << endl;
	cout << "6. Guardar datos" << endl;
	cout << "7. Cargar datos anteriores" << endl;
	cout << "8. Generar reporte" << endl;
}

int main()
{
	vector<Alumno> alumnos;
	vector<Maestro> maestros;
	vector<Grupo> grupos;

	int opcion;
	do
	{
		mostrarMenu();
		opcion = leerEntero("Ingrese su opcion: ", 1, 8);

		switch (opcion)
		{
		case 1:
			capturarAlumnos(alumnos, grupos);
			break;
		case 2:
			capturarGrupos(grupos);
			break;
		case 3:
			capturarMaestros(maestros);
			break;
		case 4:
			mostrarReportes(alumnos, grupos);
			break;
		case 5:
			cout << "Saliendo del programa" << endl;
			return 0;
		case 6:
			GuardarDatos(alumnos, grupos, maestros);
			break;
		case 7:
			CargarDatos(alumnos, grupos, maestros);
			break;
		case 8:
			GenerarReportes(alumnos, grupos);
			break;
		}
	} while (opcion != 5);

	return 0;
}