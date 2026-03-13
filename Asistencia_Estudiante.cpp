#include <iostream>
#include <string>
#include <cctype>       // para toupper, tolower
#include <limits>       // para limpiar buffer

using namespace std;

const int MAX_REGISTROS = 50;  // Tamano maximo del arreglo

void limpiarCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//CLASE BASE: PERSONA
class Persona {
    protected:
        int id;
        string nombre, apellido;   
    public:
        Persona(int i, string nom, string ape = "")
            : id(i), nombre(nom), apellido(ape) {}

        virtual void registrarAsistencia() = 0;
        int getId() { return id; }
        string getNombre() { return nombre + " " + apellido; }
};

//CLASE ESTUDIANTE (SIN matricula)
class Estudiante : public Persona {
    private:
        string carrera;
        int semestre;
    public:
        Estudiante(int i, int sem, string nom, string ape, string carr = "")
            : Persona(i, nom, ape), carrera(carr), semestre(sem) {}

        void registrarAsistencia() override {
            cout << "Asistencia registrada para estudiante: " << getNombre() << endl;
        }
};

//ESTRUCTURA REGISTRO 
struct Registro {
    int    idPersona;
    string nombre;
    string apellido;
    string carrera;
    int    semestre;
    string fecha;
    string estado;    // "Presente" / "Ausente" / "Tarde"
};

//CLASE LISTA DE ASISTENCIA
class ListaAsistencia {
    private:
        Registro registros[MAX_REGISTROS];
        int cantidad;
        int contadorID;  // Contador automatico 

        bool estadoValido(const string &estado) {
            return (estado == "Presente" || estado == "Ausente" || estado == "Tarde" ||
                    estado == "presente" || estado == "ausente" || estado == "tarde");
        }

    public:
        ListaAsistencia() {
            cantidad = 0;
            contadorID = 1;  // Inicia en 1
        }

        // INSERTAR
        bool insertar(string nombre, string apellido, string carrera, 
                      int semestre, string fecha, string estado) {
            
            if (cantidad >= MAX_REGISTROS) {
                cout << "Error: Lista llena.\n";
                return false;
            }

            if (contadorID > 50) {
                cout << "Error: Se alcanzo el limite de IDs (1-50).\n";
                return false;
            }

            if (!estadoValido(estado)) {
                cout << "Estado invalido. Use: Presente, Ausente o Tarde.\n";
                return false;
            }

            // Asignar ID 
            registros[cantidad].idPersona = contadorID;
            registros[cantidad].nombre    = nombre;
            registros[cantidad].apellido  = apellido;
            registros[cantidad].carrera   = carrera;
            registros[cantidad].semestre  = semestre;
            registros[cantidad].fecha     = fecha;
            registros[cantidad].estado    = estado;
            
            cout << "Registro insertado correctamente con ID: " << contadorID << "\n";
            contadorID++;
            cantidad++;
            return true;
        }

        // INSERTAR EN POSICION ESPECIFICA
        bool insertarEnPosicion(int pos, string nombre, string apellido, 
                                string carrera, int semestre, string fecha, string estado) {
            
            if (cantidad >= MAX_REGISTROS) {
                cout << "Error: Lista llena.\n";
                return false;
            }
            if (pos < 0 || pos > cantidad) {
                cout << "Error: Posicion invalida.\n";
                return false;
            }
            if (contadorID > 50) {
                cout << "Error: Se alcanzo el limite de IDs (1-50).\n";
                return false;
            }

            if (!estadoValido(estado)) {
                cout << "Estado invalido.\n";
                return false;
            }

            // Mover elementos a la derecha
            for (int i = cantidad; i > pos; i--) {
                registros[i] = registros[i - 1];
            }

            registros[pos].idPersona = contadorID;
            registros[pos].nombre    = nombre;
            registros[pos].apellido  = apellido;
            registros[pos].carrera   = carrera;
            registros[pos].semestre   = semestre;
            registros[pos].fecha      = fecha;
            registros[pos].estado     = estado;

            cout << "Registro insertado en posicion " << pos << " con ID: " << contadorID << "\n";
            contadorID++;
            cantidad++;
            return true;
        }

        // MOSTRAR TODOS
        void mostrar() {
            if (cantidad == 0) {
                cout << "\nNo hay registros cargados.\n";
                return;
            }

            cout << "\n=== Todos los registros (cantidad: " << cantidad << ") ===\n";
            for (int i = 0; i < cantidad; i++) {
                cout << "[" << i << "] "
                     << "ID: " << registros[i].idPersona
                     << " | Nombre: " << registros[i].nombre << " " << registros[i].apellido
                     << " | Carrera: " << registros[i].carrera
                     << " | Semestre: " << registros[i].semestre
                     << " | Fecha: " << registros[i].fecha
                     << " | Estado: " << registros[i].estado << "\n";
            }
        }

        // BUSCAR POR ID
        void buscar(int id) {
            if (id < 1 || id > 50) {
                cout << "ID debe estar entre 1 y 100.\n";
                return;
            }

            bool encontrado = false;
            for (int i = 0; i < cantidad; i++) {
                if (registros[i].idPersona == id) {
                    cout << "Registro encontrado en posicion [" << i << "] ->"
                         << " ID: " << registros[i].idPersona
                         << " | Nombre: " << registros[i].nombre << " " << registros[i].apellido
                         << " | Carrera: " << registros[i].carrera
                         << " | Semestre: " << registros[i].semestre
                         << " | Fecha: " << registros[i].fecha
                         << " | Estado: " << registros[i].estado << "\n";
                    encontrado = true;
                }
            }
            if (!encontrado) cout << "No se encontro el registro con ID: " << id << "\n";
        }

        // MODIFICAR ESTADO
        void modificar(int id, string nuevoEstado) {
            if (id < 1 || id > 50) {
                cout << "ID debe estar entre 1 y 100.\n";
                return;
            }

            if (!estadoValido(nuevoEstado)) {
                cout << "Estado invalido. Use: Presente, Ausente o Tarde.\n";
                return;
            }

            for (int i = 0; i < cantidad; i++) {
                if (registros[i].idPersona == id) {
                    registros[i].estado = nuevoEstado;
                    cout << "Registro modificado correctamente en posicion [" << i << "].\n";
                    return;
                }
            }
            cout << "No se encontro el registro con ID: " << id << "\n";
        }

        // ELIMINAR POR ID
        bool eliminar(int id) {
            if (id < 1 || id > 50) {
                cout << "ID debe estar entre 1 y 100.\n";
                return false;
            }

            for (int i = 0; i < cantidad; i++) {
                if (registros[i].idPersona == id) {
                    cout << "Eliminando: " << registros[i].nombre << " " << registros[i].apellido << "\n";
                    
                    // Mover elementos a la izquierda
                    for (int j = i; j < cantidad - 1; j++) {
                        registros[j] = registros[j + 1];
                    }
                    
                    cantidad--;
                    cout << "Registro eliminado correctamente.\n";
                    return true;
                }
            }
            cout << "No se encontro el registro con ID: " << id << "\n";
            return false;
        }

        // ELIMINAR POR POSICION
        bool eliminarPorPosicion(int pos) {
            if (pos < 0 || pos >= cantidad) {
                cout << "Error: Posicion invalida.\n";
                return false;
            }

            cout << "Eliminando posicion [" << pos << "]: " 
                 << registros[pos].nombre << " " << registros[pos].apellido 
                 << " (ID: " << registros[pos].idPersona << ")\n";

            for (int i = pos; i < cantidad - 1; i++) {
                registros[i] = registros[i + 1];
            }

            cantidad--;
            cout << "Registro eliminado correctamente.\n";
            return true;
        }

        // REPORTE FINAL
        void reporte() {
            if (cantidad == 0) {
                cout << "\nNo hay registros para reportar.\n";
                return;
            }

            int presentes = 0, ausentes = 0, tarde = 0;
            
            for (int i = 0; i < cantidad; i++) {
                string est = registros[i].estado;
                // Convertir a minusculas para comparar facil
                for (char &c : est) c = tolower(c);
                
                if (est == "presente") presentes++;
                else if (est == "ausente") ausentes++;
                else if (est == "tarde") tarde++;
            }

            cout << "\n=== Reporte Final ===\n";
            cout << "Total registros : " << cantidad << "\n";
            cout << "IDs utilizados  : 1 - " << contadorID - 1 << "\n";
            cout << "Presentes       : " << presentes << "\n";
            cout << "Ausentes        : " << ausentes  << "\n";
            cout << "Tarde           : " << tarde     << "\n";
        }

        int getCantidad() { return cantidad; }
        int getUltimoID() { return contadorID - 1; }
};

// FUNCION PRINCIPAL
int main() {
    ListaAsistencia lista;

    cout << "\n=== SISTEMA DE ASISTENCIA ===\n";

    // 5 registros iniciales
    cout << "\n--- Cargando registros ---\n";
    lista.insertar("Ana",    "Torres",    "Sistemas",    3, "12/03/2026", "Presente");
    lista.insertar("Luis",   "Mendoza",   "Civil",       5, "12/03/2026", "Tarde");
    lista.insertar("Maria",  "Lopez",     "Medicina",    2, "12/03/2026", "Ausente");
    lista.insertar("Pedro",  "Guzman",    "Derecho",     4, "12/03/2026", "Presente");
    lista.insertar("Sofia",  "Ramirez",   "Sistemas",    1, "12/03/2026", "Presente");

    int opcion;
    do {
        cout << "\n=== MENU PRINCIPAL ===\n"
             << "1. Registrar nuevo estudiante\n"
             << "2. Insertar en posicion especifica\n"
             << "3. Mostrar todos los registros\n"
             << "4. Buscar un registro por ID\n"
             << "5. Modificar estado de un registro\n"
             << "6. Eliminar un registro por ID\n"
             << "7. Eliminar por posicion\n"
             << "8. Generar reporte final\n"
             << "9. Salir\n"
             << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cout << "Entrada invalida. Ingrese un numero.\n";
            limpiarCin();
            continue;
        }

        switch (opcion) {
            case 1: {
                int semestre;
                string nombre, apellido, carrera, fecha, estado;
                cout << "Nombre: "; cin >> nombre;
                cout << "Apellido: "; cin >> apellido;
                cout << "Carrera: "; cin >> carrera;
                cout << "Semestre: "; 
                if (!(cin >> semestre)) { 
                    cout << "Semestre invalido.\n"; 
                    limpiarCin(); 
                    break; 
                }
                cout << "Fecha (DD/MM/AAAA): "; cin >> fecha;
                cout << "Estado (Presente/Ausente/Tarde): "; 
                cin >> estado;
                lista.insertar(nombre, apellido, carrera, semestre, fecha, estado);
                break;
            }
            case 2: {
                int pos, semestre;
                string nombre, apellido, carrera, fecha, estado;
                cout << "Posicion (0 - " << lista.getCantidad() << "): "; 
                if (!(cin >> pos)) { 
                    limpiarCin(); 
                    break; 
                }
                cout << "Nombre: "; cin >> nombre;
                cout << "Apellido: "; cin >> apellido;
                cout << "Carrera: "; cin >> carrera;
                cout << "Semestre: "; 
                if (!(cin >> semestre)) { 
                    limpiarCin(); 
                    break; 
                }
                cout << "Fecha: "; cin >> fecha;
                cout << "Estado: "; cin >> estado;
                lista.insertarEnPosicion(pos, nombre, apellido, carrera, semestre, fecha, estado);
                break;
            }
            case 3:
                lista.mostrar();
                break;
            case 4: {
                int id;
                cout << "ID a buscar (1-50): ";
                if (!(cin >> id)) { 
                    limpiarCin(); 
                    break; 
                }
                lista.buscar(id);
                break;
            }
            case 5: {
                int id;
                string estado;
                cout << "ID a modificar (1-50): ";
                if (!(cin >> id)) { 
                    limpiarCin(); 
                    break; 
                }
                cout << "Nuevo estado (Presente/Ausente/Tarde): ";
                cin >> estado;
                lista.modificar(id, estado);
                break;
            }
            case 6: {
                int id;
                cout << "ID a eliminar (1-50): ";
                if (!(cin >> id)) { 
                    limpiarCin(); 
                    break; 
                }
                lista.eliminar(id);
                break;
            }
            case 7: {
                int pos;
                cout << "Posicion a eliminar (0 - " << lista.getCantidad() - 1 << "): ";
                if (!(cin >> pos)) { 
                    limpiarCin(); 
                    break; 
                }
                lista.eliminarPorPosicion(pos);
                break;
            }
            case 8:
                lista.reporte();
                break;
            case 9:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opcion invalida. Ingrese 1-9.\n";
        }
    } while (opcion != 9);

    return 0;
}
