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

// Funci�n para liberar memoria de la lista
void liberar_lista(nodo*& cabeza) {
    while (cabeza) {
        nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

// Funci�n para agregar un instrumento al inventario
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

// Funci�n para mostrar el inventario
void mostrar_inventario(nodo* cabeza) {
    if (!cabeza) {
        cout << "No hay instrumentos disponibles en el inventario." << endl;
        return;
    }
    nodo* actual = cabeza;
    while (actual) {
        cout << "Nombre: " << actual->instrumento.nombre
             << ", Marca: " << actual->instrumento.marca
             << ", Categor�a: " << actual->instrumento.categoria
             << ", Precio: $" << fixed << actual->instrumento.precio << endl;
        actual = actual->siguiente;
    }
}

// Funci�n para calcular el total de una venta con impuestos y descuento
double calcular_total_con_descuento(double precio, double descuento) {
    const double impuesto = 0.18;
    double precio_con_impuesto = precio + (precio * impuesto);
    return precio_con_impuesto - (precio_con_impuesto * descuento);
}

// Funci�n para registrar una venta
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
            // Aplicar descuentos seg�n el total gastado
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

// Funci�n para mostrar todas las ventas registradas
void mostrar_ventas() {
    if (ventas.empty()) {
        cout << "No se han registrado ventas a�n." << endl;
        return;
    }
    cout << "\n--- Ventas Registradas ---" << endl;
    for (const auto& venta : ventas) {
        cout << "Instrumento: " << venta.instrumento
             << ", Precio: $" << fixed << venta.precio
             << ", Fecha: " << venta.fecha << endl;
    }
}

// Funci�n para mostrar estad�sticas de ventas
void mostrar_estadisticas() {
    if (ventas.empty()) {
        cout << "No se han realizado ventas a�n." << endl;
        return;
    }

    map<string, double> ingresos_por_instrumento;
    map<string, int> cantidad_por_instrumento;

    // Agrupar las ventas por instrumento
    for (const auto& venta : ventas) {
        ingresos_por_instrumento[venta.instrumento] += venta.precio;
        cantidad_por_instrumento[venta.instrumento]++;
    }

    cout << "\n--- Estad�sticas de Ventas ---" << endl;
    for (const auto& entry : ingresos_por_instrumento) {
        cout << "Instrumento: " << entry.first
             << ", Ingresos: $" << fixed << entry.second
             << ", Unidades Vendidas: " << cantidad_por_instrumento[entry.first] << endl;
    }
}

// Funci�n para mostrar los descuentos aplicados a los clientes
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

// Funci�n principal para el men�
int main() {
    nodo* inventario_cuerdas = nullptr;
    nodo* inventario_teclados = nullptr;
    nodo* inventario_percusion = nullptr;
    int opcion;

    // Agregar algunos instrumentos predefinidos
    agregar_instrumento(inventario_cuerdas, {"Guitarra Acustica", "Yamaha", "Cuerdas", 200.00});
    agregar_instrumento(inventario_cuerdas, {"Bajo Electrico", "Fender", "Cuerdas", 450.00});
    agregar_instrumento(inventario_teclados, {"Piano Digital", "Casio", "Teclado", 500.00});
    agregar_instrumento(inventario_percusion, {"Bater�a Electr�nica", "Roland", "Percusi�n", 800.00});

    // Nuevos instrumentos a agregar
    agregar_instrumento(inventario_cuerdas, {"Guitarra Fender", "Fender", "Cuerdas", 800.00});
    agregar_instrumento(inventario_cuerdas, {"Guitarra Alhambra", "Alhambra", "Cuerdas", 1000.00});
    agregar_instrumento(inventario_cuerdas, {"Guitarra C�rdoba", "C�rdoba", "Cuerdas", 800.00});
    agregar_instrumento(inventario_cuerdas, {"Guitarra Fernandez", "Fernandez", "Cuerdas", 700.00});

    agregar_instrumento(inventario_teclados, {"Piano Casio", "Casio", "Teclado", 600.00});
    agregar_instrumento(inventario_teclados, {"Teclado Yamaha", "Yamaha", "Teclado", 800.00});
    agregar_instrumento(inventario_teclados, {"Teclado Korg", "Korg", "Teclado", 1200.00});

    agregar_instrumento(inventario_percusion, {"Caj�n", "Varios", "Percusi�n", 200.00});
    agregar_instrumento(inventario_percusion, {"Yemb�", "Varios", "Percusi�n", 250.00});
    agregar_instrumento(inventario_percusion, {"Redoblante", "Varios", "Percusi�n", 250.00});
    agregar_instrumento(inventario_percusion, {"Casta�uelas", "Varios", "Percusi�n", 50.00});
    agregar_instrumento(inventario_percusion, {"Bongos", "Varios", "Percusi�n", 350.00});
    agregar_instrumento(inventario_percusion, {"Congas", "Varios", "Percusi�n", 100.00});
    agregar_instrumento(inventario_percusion, {"Bater�a Electr�nica", "Roland", "Percusi�n", 1500.00});

    do {
        cout << "\n--- Menu de Administrador ---" << endl;
        cout << "1. Ver Inventario" << endl;
        cout << "2. Agregar Instrumento al Inventario" << endl;
        cout << "3. Ver Estad�sticas de Ventas" << endl;
        cout << "4. Ver Ventas Registradas" << endl;
        cout << "5. Mostrar Descuentos Aplicados" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opci�n: ";
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
                cout << "Ingrese la categor�a del instrumento (Cuerdas, Teclado, Percusi�n): ";
                getline(cin, categoria_str);
                cout << "Ingrese el precio del instrumento: $";
                cin >> precio;

                // Asignar el instrumento a la categor�a correspondiente
                instrumento nuevo_instrumento = {nombre, marca, categoria_str, precio};
                if (categoria_str == "Cuerdas") {
                    agregar_instrumento(inventario_cuerdas, nuevo_instrumento);
                } else if (categoria_str == "Teclado") {
                    agregar_instrumento(inventario_teclados, nuevo_instrumento);
                } else if (categoria_str == "Percusi�n") {
                    agregar_instrumento(inventario_percusion, nuevo_instrumento);
                } else {
                    cout << "Categor�a no v�lida." << endl;
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
                cout << "Saliendo del sistema de administraci�n..." << endl;
                break;
            default:
                cout << "Opci�n no v�lida. Intente de nuevo." << endl;
        }
    } while (opcion != 6);
    
    // Liberar memoria de las listas
    liberar_lista(inventario_cuerdas);
    liberar_lista(inventario_teclados);
    liberar_lista(inventario_percusion);

    return 0;
}

