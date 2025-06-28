#include <iostream>
#include <fstream>
using namespace std;

struct Estudiante {
    string nombre;
    string carnet;
    int edad;
};

// Función para agregar estudiante (CREATE)
void agregarEstudiante() {
    Estudiante e;
    cout << "Nombre (sin espacios): ";
    cin >> e.nombre;
    cout << "Carnet: ";
    cin >> e.carnet;
    cout << "Edad: ";
    cin >> e.edad;

    ofstream archivo("estudiantes.txt", ios::app);
    if (archivo.is_open()) {
        archivo << e.nombre << " " << e.carnet << " " << e.edad << endl;
        archivo.close();
        cout << "Estudiante agregado correctamente.\n";
    } else {
        cout << "Error al abrir el archivo.\n";
    }
}

// Función para mostrar estudiantes (READ)
void mostrarEstudiantes() {
    ifstream archivo("estudiantes.txt");
    Estudiante e;

    if (archivo.is_open()) {
        cout << "\n--- Lista de Estudiantes ---\n";
        while (archivo >> e.nombre >> e.carnet >> e.edad) {
            cout << "Nombre: " << e.nombre 
                 << ", Carnet: " << e.carnet
                 << ", Edad: " << e.edad << endl;
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo.\n";
    }
}

// -----------------------------
// 👇 TU TAREA: Completa esta función (UPDATE)

void modificarEstudiante() {
    ifstream archivo("estudiantes.txt");    // Abrimos el archivo original en modo lectura
    ofstream temp("temp.txt");              // Creamos un archivo temporal para escribir los nuevos datos 
    Estudiante e;
    string buscado; 
    bool encontrado = false;

    cout << "Ingrese el carnet del estudiante a modificar: ";
    cin >> buscado;

    // Si ambos archivos se abrieron correctamente, seguimos
    if (archivo.is_open() && temp.is_open()) {
        // Leemos estudiante por estudiante del archivo original
        while (archivo >> e.nombre >> e.carnet >> e.edad) {
            // Aqui pongo un condicional, y si es verdadero, es porque encontramos el estudiante con el carnet que se busca
            if (e.carnet == buscado) {
                encontrado = true;

                // Pedimos los nuevos datos al usuario
                cout << "Estudiante encontrado. Ingresa los nuevos datos: " << endl;
                cout << "Nuevo nombre (sin espacios): " << endl;
                cin >> e.nombre;
                cout << "Nuevo carnet: " << endl;
                cin >> e.carnet;
                cout << "Nueva edad: " << endl;
                cin >> e.edad;

                // Escribimos el estudiante modificado en el archivo temporal
                temp << e.nombre << " " << e.carnet << " " << e.edad << endl;
            } else {
                // Si no es el estudiante a modificar, lo copiamos tal cual al archivo temporal 
                temp << e.nombre << " " << e.carnet << " " << e.edad << endl;
            }
        }

        // Cerramos ambos archivos
        archivo.close();
        temp.close();

        // Borramos el archivo original (porque ya no sirve)
        remove("estudiantes.txt");
        // Renombramos el archivo temporal como si fuera el original
        rename("temp.txt", "estudiantes.txt");

        // Mensaje final según si se encontró o no el estudiante
        if (encontrado)
            cout << "Estudiante modificado correctamente." <<endl;
        else
            cout << "Carnet no encontrado." <<endl;
    } else {
        // Si hubo problemas abriendo los archivos
        cout << "Error al abrir los archivos." <<endl;
    }
}

// -----------------------------

// Función para eliminar estudiante (DELETE)
void eliminarEstudiante() {
    ifstream archivo("estudiantes.txt");
    ofstream temp("temp.txt");
    Estudiante e;
    string buscado;
    bool eliminado = false;

    cout << "Ingrese carnet a eliminar: ";
    cin >> buscado;

    if (archivo.is_open() && temp.is_open()) {
        while (archivo >> e.nombre >> e.carnet >> e.edad) {
            if (e.carnet == buscado) {
                eliminado = true;               // No se copia: se "borra"
            } else {
                temp << e.nombre << " " << e.carnet << " " << e.edad << endl;
            }
        }
        archivo.close();
        temp.close();
        remove("estudiantes.txt");
        rename("temp.txt", "estudiantes.txt");

        if (eliminado)
            cout << "Estudiante eliminado correctamente."<<endl;
        else
            cout << "Carnet no encontrado."<<endl;
    } else {
        cout << "Error abriendo los archivos."<<endl;;
    }
}

// Menú principal
int main() {
    int opcion;
    do {
        cout << "=== CRUD de Estudiantes ==="<<endl;
        cout << "1. Agregar estudiante"<<endl;
        cout << "2. Mostrar todos"<<endl;
        cout << "3. Modificar estudiante"<<endl;
        cout << "4. Eliminar estudiante"<<endl;
        cout << "5. Salir" <<endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarEstudiante(); break;
            case 2: mostrarEstudiantes(); break;
            case 3: modificarEstudiante(); break;  // 👉 Completa aquí
            case 4: eliminarEstudiante(); break;
            case 5: cout << "Saliendo..." << endl; break;
            default: cout << "Opción inválida." <<endl;
        }

    } while (opcion != 5);

    return 0;
}