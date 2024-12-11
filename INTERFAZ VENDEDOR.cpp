#include <iostream>
#include <string>
#include <cstdlib>  // Para generar números aleatorios
#include <ctime>    // Para obtener una fecha aleatoria dentro de un rango
#include <queue>    // Para la cola de instrumentos

using namespace std;

// Estructura para almacenar la información de un instrumento
struct Instrumento {
    string nombre;
    string marca;
    string categoria;
    double precio;
};

// Nodo de la lista enlazada
struct Nodo {
    Instrumento instrumento;
    Nodo* siguiente;
};

// Estructura para gestionar instrumentos fuera de inventario
struct InstrumentoFueraStock {
    string nombre;
    double precio;
    string tiempoEntrega;
};

// Cola de instrumentos seleccionados por el usuario
queue<Instrumento> colaDeCompra;

// Base de datos simulada para instrumentos fuera de inventario
InstrumentoFueraStock dropshippingDB[] = {
    {"Arpa", 1200.00, "7 dias"},
    {"Trompeta", 300.00, "5 dias"},
    {"Gaita", 600.00, "10 dias"}
};

int dropshippingDBSize = sizeof(dropshippingDB) / sizeof(dropshippingDB[0]);

// Función para generar un precio aleatorio entre 200 y 500
double generarPrecioAleatorio() {
    return 200.0 + rand() % 301;  // Precio entre 200 y 500
}

// Función para generar una fecha de entrega aleatoria entre 2 y 7 días
string generarFechaDeEntrega() {
    int dias = 2 + rand() % 6;  // Entre 2 y 7 días
    return to_string(dias) + " días";
}

// Función para agregar un instrumento a una lista enlazada (inventario por categoría)
void agregarInstrumento(Nodo*& cabeza, const Instrumento& instrumento) {
    Nodo* nuevoNodo = new Nodo{instrumento, nullptr};
    if (!cabeza) {
        cabeza = nuevoNodo;
    } else {
        Nodo* temp = cabeza;
        while (temp->siguiente) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
    }
}

// Función para mostrar todos los instrumentos en una lista
void mostrarInstrumentos(Nodo* cabeza) {
    if (!cabeza) {
        cout << "No hay instrumentos disponibles en esta categoria." << endl;
        return;
    }
    Nodo* actual = cabeza;
    while (actual) {
        cout << "Nombre: " << actual->instrumento.nombre
             << ", Marca: " << actual->instrumento.marca
             << ", Precio: $" << actual->instrumento.precio << endl;
        actual = actual->siguiente;
    }
}

// Función para solicitar un instrumento fuera de stock
void solicitarInstrumentoFueraDeStock() {
    string nombreInstrumento;
    cout << "\nIngrese el nombre del instrumento que desea solicitar (o escriba 'volver' para regresar): ";
    cin.ignore();
    getline(cin, nombreInstrumento);

    if (nombreInstrumento == "volver") {
        return;
    }

    // Generar precio aleatorio y fecha de entrega aleatoria
    double precio = generarPrecioAleatorio();
    string fechaEntrega = generarFechaDeEntrega();

    // Mostrar detalles del instrumento solicitado
    cout << "\nInstrumento solicitado: " << nombreInstrumento << endl;
    cout << "Precio de importación: $" << precio << endl;
    cout << "Tiempo estimado de llegada: " << fechaEntrega << endl;

    // Crear instrumento fuera de stock para agregar a la cola
    Instrumento instrumentoFueraStock = {nombreInstrumento, "Desconocida", "Fuera de Stock", precio};
    colaDeCompra.push(instrumentoFueraStock);  // Agregar a la cola

    // Formulario de compra
    string nombreCliente, direccion, correo;
    cout << "\n--- Formulario de Compra ---" << endl;
    cout << "Nombre del cliente: ";
    getline(cin, nombreCliente);
    cout << "Correo: ";
    getline(cin, correo);
    cout << "Direccion: ";
    getline(cin, direccion);

    // Confirmación
    cout << "\n--- Pedido Confirmado ---" << endl;
    cout << "Cliente: " << nombreCliente << endl;
    cout << "Instrumento: " << nombreInstrumento << endl;
    cout << "Precio: $" << precio << endl;
    cout << "Tiempo estimado de llegada: " << fechaEntrega << endl;
    cout << "Se enviará un correo de confirmación a " << correo << endl;
}

// Función para agregar un instrumento a la cola de compra
void agregarInstrumentoACola(Nodo* inventario) {
    int seleccion;
    cout << "Seleccione el número del instrumento a agregar a la cola de compra: ";
    cin >> seleccion;
    
    Nodo* actual = inventario;
    int i = 1;
    while (actual) {
        if (i == seleccion) {
            colaDeCompra.push(actual->instrumento);
            cout << actual->instrumento.nombre << " agregado a la cola de compra." << endl;
            return;
        }
        actual = actual->siguiente;
        i++;
    }
    cout << "Selección no válida." << endl;
}

// Función para eliminar un instrumento de la cola de compra
void eliminarInstrumentoDeCola() {
    if (colaDeCompra.empty()) {
        cout << "No hay instrumentos en la cola para eliminar." << endl;
        return;
    }

    cout << "\n--- Instrumentos en la cola ---" << endl;
    queue<Instrumento> tempCola = colaDeCompra; // Hacemos una copia temporal para mostrar
    int i = 1;
    while (!tempCola.empty()) {
        Instrumento instrumento = tempCola.front();
        cout << i++ << ". " << instrumento.nombre << " - $" << instrumento.precio << endl;
        tempCola.pop();
    }

    int seleccion;
    cout << "\nSeleccione el número del instrumento a eliminar de la cola: ";
    cin >> seleccion;

    // Crear una nueva cola sin el elemento seleccionado
    queue<Instrumento> nuevaCola;
    i = 1;
    while (!colaDeCompra.empty()) {
        if (i != seleccion) {
            nuevaCola.push(colaDeCompra.front());
        }
        colaDeCompra.pop();
        i++;
    }

    colaDeCompra = nuevaCola;  // Actualizamos la cola de compra
    cout << "Instrumento eliminado de la cola." << endl;
}

// Función para ver la cola de compras y realizar el pago
void verColaYRealizarCompra() {
    if (colaDeCompra.empty()) {
        cout << "No hay instrumentos en la cola de compra." << endl;
        return;
    }

    double totalCompra = 0;
    cout << "\n--- Instrumentos en la cola de compra ---" << endl;
    queue<Instrumento> tempCola = colaDeCompra; // Copia temporal para mostrar sin alterar la original
    int i = 1;
    while (!tempCola.empty()) {
        Instrumento instrumento = tempCola.front();
        totalCompra += instrumento.precio;
        cout << i++ << ". " << instrumento.nombre << " - $" << instrumento.precio << endl;
        tempCola.pop();
    }

    cout << "\nTotal de la compra: $" << totalCompra << endl;
    char pago;
    cout << "¿Desea realizar el pago? (s/n): ";
    cin >> pago;
    if (pago == 's' || pago == 'S') {
        cout << "Compra realizada con éxito. ¡Gracias por su compra!" << endl;
    } else {
        cout << "Compra cancelada. Los instrumentos permanecen en la cola." << endl;
        // No vaciar la cola, solo regresar al menú anterior
    }
}

// Función principal con menú interactivo
int main() {
    srand(time(0)); // Inicializar generador de números aleatorios

    Nodo* inventarioCuerdas = nullptr;
    Nodo* inventarioTeclados = nullptr;
    Nodo* inventarioPercusion = nullptr;
    int categoria;

    // Agregamos algunos instrumentos por categoría
    agregarInstrumento(inventarioCuerdas, {"Guitarra Acustica", "Yamaha", "Cuerdas", 200.00});
    agregarInstrumento(inventarioTeclados, {"Piano Digital", "Casio", "Teclado", 500.00});
    agregarInstrumento(inventarioPercusion, {"Bateria Electronica", "Roland", "Percusion", 800.00});

    do {
        cout << "\n--- Seleccione Categoria ---" << endl;
        cout << "1. Cuerdas" << endl;
        cout << "2. Teclados" << endl;
        cout << "3. Percusion" << endl;
        cout << "4. Solicitar Instrumento Fuera de Stock" << endl;
        cout << "5. Ver Cola y Realizar Compra" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una categoria: ";
        cin >> categoria;

        switch (categoria) {
            case 1:
                cout << "\n--- Inventario de Cuerdas ---" << endl;
                mostrarInstrumentos(inventarioCuerdas);
                agregarInstrumentoACola(inventarioCuerdas);
                break;
            case 2:
                cout << "\n--- Inventario de Teclados ---" << endl;
                mostrarInstrumentos(inventarioTeclados);
                agregarInstrumentoACola(inventarioTeclados);
                break;
            case 3:
                cout << "\n--- Inventario de Percusion ---" << endl;
                mostrarInstrumentos(inventarioPercusion);
                agregarInstrumentoACola(inventarioPercusion);
                break;
            case 4:
                solicitarInstrumentoFueraDeStock();
                break;
            case 5:
                verColaYRealizarCompra();
                eliminarInstrumentoDeCola();
                break;
            case 6:
                cout << "Saliendo de la tienda..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while (categoria != 6);

    return 0;
}
