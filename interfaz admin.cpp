#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <map>
using namespace std;

struct instrumento {
    string nombre;
    string marca;
    string categoria;
    double precio;
};

struct nodo {
    instrumento instrumento;
    nodo* siguiente;
};

struct venta {
    string instrumento;
    double precio;
    string fecha;
};

struct cliente {
    string nombre;
    double total_gastado;
    bool es_exclusivo;
    double descuento; // Nuevo campo para descuento
};

// Lista de ventas global (almacena las ventas realizadas)
vector<venta> ventas;
vector<cliente> clientes;

// Función para liberar memoria de la lista
void liberar_lista(nodo*& cabeza) {
    while (cabeza) {
        nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

// Función para agregar un instrumento al inventario
void agregar_instrumento(nodo*& cabeza, const instrumento& instrumento) {
    nodo* nuevo_nodo = new nodo{instrumento, nullptr};
    if (!cabeza) {
        cabeza = nuevo_nodo;
    } else {
        nodo* temp = cabeza;
        while (temp->siguiente) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo_nodo;
    }
}

// Función para mostrar el inventario
void mostrar_inventario(nodo* cabeza) {
    if (!cabeza) {
        cout << "No hay instrumentos disponibles en el inventario." << endl;
        return;
    }
    nodo* actual = cabeza;
    while (actual) {
        cout << "Nombre: " << actual->instrumento.nombre
             << ", Marca: " << actual->instrumento.marca
             << ", Categoría: " << actual->instrumento.categoria
             << ", Precio: $" << fixed << actual->instrumento.precio << endl;
        actual = actual->siguiente;
    }
}

// Función para calcular el total de una venta con impuestos y descuento
double calcular_total_con_descuento(double precio, double descuento) {
    const double impuesto = 0.18;
    double precio_con_impuesto = precio + (precio * impuesto);
    return precio_con_impuesto - (precio_con_impuesto * descuento);
}

// Función para registrar una venta
void registrar_venta(const string& nombre_cliente, const string& instrumento, double precio) {
    // Obtener la fecha actual
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string fecha = to_string(ltm->tm_mday) + "/" + to_string(ltm->tm_mon + 1) + "/" + to_string(1900 + ltm->tm_year);

    // Registrar la venta
    ventas.push_back({instrumento, precio, fecha});
    
    // Actualizar el total gastado del cliente
    bool cliente_existente = false;
    for (auto& cliente : clientes) {
        if (cliente.nombre == nombre_cliente) {
            cliente_existente = true;
            cliente.total_gastado += precio;
            // Aplicar descuentos según el total gastado
            if (cliente.total_gastado > 3000) {
                cliente.descuento = 0.07; // 7% de descuento
            } else if (cliente.total_gastado > 1500) {
                cliente.descuento = 0.03; // 3% de descuento
            }
            break;
        }
    }

    // Si el cliente no existe, crearlo
    if (!cliente_existente) {
        clientes.push_back({nombre_cliente, precio, false, 0.0});
    }

    cout << "Venta registrada para " << nombre_cliente << ": " << instrumento << " - Precio: $"
         << fixed << precio << " - Fecha: " << fecha << endl;
}

// Función para mostrar todas las ventas registradas
void mostrar_ventas() {
    if (ventas.empty()) {
        cout << "No se han registrado ventas aún." << endl;
        return;
    }
    cout << "\n--- Ventas Registradas ---" << endl;
    for (const auto& venta : ventas) {
        cout << "Instrumento: " << venta.instrumento
             << ", Precio: $" << fixed << venta.precio
             << ", Fecha: " << venta.fecha << endl;
    }
}

// Función para mostrar estadísticas de ventas
void mostrar_estadisticas() {
    if (ventas.empty()) {
        cout << "No se han realizado ventas aún." << endl;
        return;
    }

    map<string, double> ingresos_por_instrumento;
    map<string, int> cantidad_por_instrumento;

    // Agrupar las ventas por instrumento
    for (const auto& venta : ventas) {
        ingresos_por_instrumento[venta.instrumento] += venta.precio;
        cantidad_por_instrumento[venta.instrumento]++;
    }

    cout << "\n--- Estadísticas de Ventas ---" << endl;
    for (const auto& entry : ingresos_por_instrumento) {
        cout << "Instrumento: " << entry.first
             << ", Ingresos: $" << fixed << entry.second
             << ", Unidades Vendidas: " << cantidad_por_instrumento[entry.first] << endl;
    }
}

// Función para mostrar los descuentos aplicados a los clientes
void mostrar_descuentos() {
    cout << "\n--- Descuentos Aplicados a Clientes ---" << endl;
    for (const auto& cliente : clientes) {
        if (cliente.descuento > 0) {
            cout << "Cliente: " << cliente.nombre
                 << ", Total Gastado: $" << fixed << cliente.total_gastado
                 << ", Descuento: " << (cliente.descuento * 100) << "%" << endl;
        }
    }
}

// Función principal para el menú
int main() {
    nodo* inventario_cuerdas = nullptr;
    nodo* inventario_teclados = nullptr;
    nodo* inventario_percusion = nullptr;
    int opcion;

    // Agregar algunos instrumentos predefinidos
    agregar_instrumento(inventario_cuerdas, {"Guitarra Acustica", "Yamaha", "Cuerdas", 200.00});
    agregar_instrumento(inventario_cuerdas, {"Bajo Electrico", "Fender", "Cuerdas", 450.00});
    agregar_instrumento(inventario_teclados, {"Piano Digital", "Casio", "Teclado", 500.00});
    agregar_instrumento(inventario_percusion, {"Batería Electrónica", "Roland", "Percusión", 800.00});

    // Nuevos instrumentos a agregar
    agregar_instrumento(inventario_cuerdas, {"Guitarra Fender", "Fender", "Cuerdas", 800.00});
    agregar_instrumento(inventario_cuerdas, {"Guitarra Alhambra", "Alhambra", "Cuerdas", 1000.00});
    agregar_instrumento(inventario_cuerdas, {"Guitarra Córdoba", "Córdoba", "Cuerdas", 800.00});
    agregar_instrumento(inventario_cuerdas, {"Guitarra Fernandez", "Fernandez", "Cuerdas", 700.00});

    agregar_instrumento(inventario_teclados, {"Piano Casio", "Casio", "Teclado", 600.00});
    agregar_instrumento(inventario_teclados, {"Teclado Yamaha", "Yamaha", "Teclado", 800.00});
    agregar_instrumento(inventario_teclados, {"Teclado Korg", "Korg", "Teclado", 1200.00});

    agregar_instrumento(inventario_percusion, {"Cajón", "Varios", "Percusión", 200.00});
    agregar_instrumento(inventario_percusion, {"Yembé", "Varios", "Percusión", 250.00});
    agregar_instrumento(inventario_percusion, {"Redoblante", "Varios", "Percusión", 250.00});
    agregar_instrumento(inventario_percusion, {"Castañuelas", "Varios", "Percusión", 50.00});
    agregar_instrumento(inventario_percusion, {"Bongos", "Varios", "Percusión", 350.00});
    agregar_instrumento(inventario_percusion, {"Congas", "Varios", "Percusión", 100.00});
    agregar_instrumento(inventario_percusion, {"Batería Electrónica", "Roland", "Percusión", 1500.00});

    do {
        cout << "\n--- Menu de Administrador ---" << endl;
        cout << "1. Ver Inventario" << endl;
        cout << "2. Agregar Instrumento al Inventario" << endl;
        cout << "3. Ver Estadísticas de Ventas" << endl;
        cout << "4. Ver Ventas Registradas" << endl;
        cout << "5. Mostrar Descuentos Aplicados" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << "\n--- Inventario ---" << endl;
                mostrar_inventario(inventario_cuerdas);
                mostrar_inventario(inventario_teclados);
                mostrar_inventario(inventario_percusion);
                break;
            }
            case 2: {
                string nombre, marca, categoria_str;
                double precio;
                cout << "Ingrese el nombre del instrumento: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese la marca del instrumento: ";
                getline(cin, marca);
                cout << "Ingrese la categoría del instrumento (Cuerdas, Teclado, Percusión): ";
                getline(cin, categoria_str);
                cout << "Ingrese el precio del instrumento: $";
                cin >> precio;

                // Asignar el instrumento a la categoría correspondiente
                instrumento nuevo_instrumento = {nombre, marca, categoria_str, precio};
                if (categoria_str == "Cuerdas") {
                    agregar_instrumento(inventario_cuerdas, nuevo_instrumento);
                } else if (categoria_str == "Teclado") {
                    agregar_instrumento(inventario_teclados, nuevo_instrumento);
                } else if (categoria_str == "Percusión") {
                    agregar_instrumento(inventario_percusion, nuevo_instrumento);
                } else {
                    cout << "Categoría no válida." << endl;
                }
                break;
            }
            case 3: {
                mostrar_estadisticas();
                break;
            }
            case 4: {
                mostrar_ventas();
                break;
            }
            case 5: {
                mostrar_descuentos();
                break;
            }
            case 6:
                cout << "Saliendo del sistema de administración..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != 6);
    
    // Liberar memoria de las listas
    liberar_lista(inventario_cuerdas);
    liberar_lista(inventario_teclados);
    liberar_lista(inventario_percusion);

    return 0;
}

