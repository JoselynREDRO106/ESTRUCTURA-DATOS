#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // para transform (normalizar texto)
#include <limits>     // para limpiar buffer de cin

using namespace std;

// --- Utilidades ---------------------------------------------------------------

// Convierte un string a formato "Capitalized" (ej: "presente" ? "Presente")
string capitalizar(string s) {
    if (s.empty()) return s;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    s[0] = toupper(s[0]);
    return s;
}

// Limpia el buffer de cin y evita loops infinitos con entradas inválidas
void limpiarCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// --- CLASE BASE: PERSONA -------------------------------------------------------

class Persona {
    protected:
        int id;
        string nombre, apellido;   
    public:
        Persona(int i, string nom, string ape= "")
            : id(i), nombre(nom), apellido(ape){}

        // Método abstracto (polimorfismo puro)
        virtual void registrarAsistencia() = 0;

        int getId() { return id; }

        string getNombre() { return nombre + " " + apellido; }
};

// --- CLASE ESTUDIANTE ----------------------------------------------------------

class Estudiante : public Persona {
    private:
        string matricula, carrera;
        int semestre;
    public:
        Estudiante(int i, int sem , string nom, string ape, string matri, string carr= "")
            : Persona(i, nom, ape), matricula(matri), carrera(carr), semestre(sem) {}

        void registrarAsistencia() override {
            cout << "Asistencia registrada para estudiante: " << getNombre() << endl;
        }
};

//ESTRUCTURA REGISTRO

struct Registro {
    int    idPersona;
    string nombre;
    string apellido;
    string email;
    string carrera;
    int    semestre;
    string fecha;
    string estado;    // Siempre guardado como "Presente" / "Ausente" / "Tarde"
};

// CLASE LISTA DE ASISTENCIA 

class ListaAsistencia {
    private:
        vector<Registro> registros;

        // Valida que el estado sea uno de los tres valores permitidos
        bool estadoValido(const string &estado) {
            return (estado == "Presente" || estado == "Ausente" || estado == "Tarde");
        }

    public:
        // Insertar un nuevo registro
        void insertar(int id, string nombre, string apellido, string carrera, int semestre, string fecha, string estado) {
            estado = capitalizar(estado);
            if (!estadoValido(estado)) {
                cout << "Estado inválido. Use: Presente, Ausente o Tarde.\n";
                return;
            }
            Registro r;
            r.idPersona = id;
            r.nombre    = nombre;
            r.apellido  = apellido;
            r.carrera   = carrera;
            r.semestre  = semestre;
            r.fecha     = fecha;
            r.estado    = estado;
            registros.push_back(r);
            cout << "Registro insertado correctamente.\n";
        }

        // Mostrar todos los registros
        void mostrar() {
            if (registros.empty()) {
                cout << "\nNo hay registros cargados.\n";
                return;
            }
            cout << "\n=== Todos los registros ===\n";
            for (auto &r : registros) {
                cout << "ID: "        << r.idPersona
                     << " | Nombre: "  << r.nombre << " " << r.apellido
                     << " | Carrera: " << r.carrera
                     << " | Sem: "     << r.semestre
                     << " | Fecha: "   << r.fecha
                     << " | Estado: "  << r.estado << "\n";
            }
        }

        // Buscar registros por ID (puede haber varios del mismo ID en fechas distintas)
        void buscar(int id) {
            bool encontrado = false;
            for (auto &r : registros) {
                if (r.idPersona == id) {
                    cout << "Registro encontrado ->"
                         << " ID: "       << r.idPersona
                         << " | Nombre: "  << r.nombre << " " << r.apellido
                         << " | Carrera: " << r.carrera
                         << " | Sem: "     << r.semestre
                         << " | Fecha: "   << r.fecha
                         << " | Estado: "  << r.estado << "\n";
                    encontrado = true;
                }
            }
            if (!encontrado) cout << "No se encontró el registro.\n";
        }

        // Modificar el estado del primer registro que coincida con el ID
        void modificar(int id, string nuevoEstado) {
            nuevoEstado = capitalizar(nuevoEstado);
            if (!estadoValido(nuevoEstado)) {
                cout << "Estado inválido. Use: Presente, Ausente o Tarde.\n";
                return;
            }
            for (auto &r : registros) {
                if (r.idPersona == id) {
                    r.estado = nuevoEstado;
                    cout << "Registro modificado correctamente.\n";
                    return;
                }
            }
            cout << "No se encontró el registro.\n";
        }

        // Eliminar el primer registro que coincida con el ID
        void eliminar(int id) {
            for (size_t i = 0; i < registros.size(); i++) {
                if (registros[i].idPersona == id) {
                    registros.erase(registros.begin() + i);
                    cout << "Registro eliminado correctamente.\n";
                    return;
                }
            }
            cout << "No se encontró el registro.\n";
        }

        // Reporte final de conteos
        void reporte() {
            if (registros.empty()) {
                cout << "\nNo hay registros para reportar.\n";
                return;
            }
            int presentes = 0, ausentes = 0, tarde = 0;
            for (auto &r : registros) {
                if (r.estado == "Presente") presentes++;
                else if (r.estado == "Ausente") ausentes++;
                else if (r.estado == "Tarde")   tarde++;
            }
            cout << "\n=== Reporte Final ===\n";
            cout << "Total registros : " << registros.size() << "\n";
            cout << "Presentes       : " << presentes << "\n";
            cout << "Ausentes        : " << ausentes  << "\n";
            cout << "Tarde           : " << tarde     << "\n";
        }
};

// --- FUNCIÓN PRINCIPAL ---------------------------------------------------------

int main() {
    ListaAsistencia lista;

    // 10 registros iniciales
    lista.insertar(1,  "Ana",    "Torres",    "Sistemas",    3, "12/03/2026", "Presente");
    lista.insertar(2,  "Luis",   "Mendoza",   "Civil",       5, "12/03/2026", "Tarde");
    lista.insertar(3,  "Maria",  "Lopez",  "Medicina",    2, "12/03/2026", "Ausente");
    lista.insertar(4,  "Pedro",  "Guzman",  "Derecho",     4, "12/03/2026", "Presente");
    lista.insertar(5,  "Sofia",  "Ramirez",  "Sistemas",    1, "12/03/2026", "Presente");
    lista.insertar(6,  "Carlos", "Vega", "Industrial",  6, "12/03/2026", "Tarde");
    lista.insertar(7,  "Laura",  "Diaz",  "Arquitectura",3, "12/03/2026", "Ausente");
    lista.insertar(8,  "Jorge",  "Castro",  "Electronica", 2, "12/03/2026", "Presente");
    lista.insertar(9,  "Elena",  "Mora",  "Sistemas",    4, "12/03/2026", "Presente");
    lista.insertar(10, "Diego",  "Paredes",  "Civil",       7, "12/03/2026", "Tarde");

    int opcion;
    do {
        cout << "\n=== Menú Interactivo ===\n"
             << "1. Registrar datos\n"
             << "2. Mostrar todos los registros\n"
             << "3. Buscar un registro\n"
             << "4. Modificar un registro\n"
             << "5. Eliminar un registro\n"
             << "6. Generar reporte final\n"
             << "7. Salir\n"
             << "Seleccione una opción: ";

        // -- Validación de entrada del menú --
        if (!(cin >> opcion)) {
            cout << "Entrada inválida. Ingrese un número del 1 al 7.\n";
            limpiarCin();
            opcion = 0;   // fuerza que el do-while continúe
            continue;
        }

        switch (opcion) {
            case 1: {
                int id, semestre;
                string nombre, apellido, email, carrera, fecha, estado;
                cout << "Ingrese ID: ";
                if (!(cin >> id)) { cout << "ID inválido.\n"; limpiarCin(); break; }
                cout << "Ingrese nombre: ";
                cin >> nombre;
                cout << "Ingrese apellido: ";
                cin >> apellido;
                cout << "Ingrese carrera: ";
                cin >> carrera;
                cout << "Ingrese semestre: ";
                if (!(cin >> semestre)) { cout << "Semestre inválido.\n"; limpiarCin(); break; }
                cout << "Ingrese fecha (DD/MM/AAAA): ";
                cin >> fecha;
                cout << "Ingrese estado (Presente / Ausente / Tarde): ";
                cin >> estado;
                lista.insertar(id, nombre, apellido, carrera, semestre, fecha, estado);
                break;
            }
            case 2:
                lista.mostrar();
                break;
            case 3: {
                int id;
                cout << "Ingrese ID a buscar: ";
                if (!(cin >> id)) { cout << "ID inválido.\n"; limpiarCin(); break; }
                lista.buscar(id);
                break;
            }
            case 4: {
                int id;
                string nuevoEstado;
                cout << "Ingrese ID a modificar: ";
                if (!(cin >> id)) { cout << "ID inválido.\n"; limpiarCin(); break; }
                cout << "Ingrese nuevo estado (Presente / Ausente / Tarde): ";
                cin >> nuevoEstado;
                lista.modificar(id, nuevoEstado);
                break;
            }
            case 5: {
                int id;
                cout << "Ingrese ID a eliminar: ";
                if (!(cin >> id)) { cout << "ID inválido.\n"; limpiarCin(); break; }
                lista.eliminar(id);
                break;
            }
            case 6:
                lista.reporte();
                break;
            case 7:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opción inválida. Ingrese un número del 1 al 7.\n";
        }
    } while (opcion != 7);

    return 0;
}

