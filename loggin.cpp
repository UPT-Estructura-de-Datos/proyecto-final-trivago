#include <iostream>
#include <string>
#include <conio.h> // Para _getch()

using namespace std;

// Función para ocultar la entrada de la contraseña
// Esta función captura caracteres sin mostrarlos en pantalla
// y devuelve la contraseña ingresada como una cadena.
string obtener_contrasena() {
    string contrasena;
    char caracter;

    while (true) {
        caracter = _getch(); // Captura el carácter sin mostrarlo en la consola

        if (caracter == '\r') { // Si se presiona Enter
            break; // Salir del bucle
        } else if (caracter == '\b') { // Si se presiona Backspace
            if (!contrasena.empty()) {
                contrasena.pop_back(); // Eliminar el último carácter
                cout << "\b \b"; // Mover el cursor hacia atrás y borrar el asterisco
            }
        } else {
            contrasena += caracter; // Agregar el carácter a la contraseña
            cout << '*'; // Mostrar un asterisco
        }
    }

    return contrasena; // Retornar la contraseña ingresada
}

// Función principal del programa
// Esta función gestiona el proceso de login para vendedor y administrador.
int main() {
    const string USUARIO_VENDEDOR = "vendedor";
    const string CONTRASENA_VENDEDOR = "vendedor123";
    const string USUARIO_ADMIN = "admin";
    const string CONTRASENA_ADMIN = "admin123";

    string usuario;
    string contrasena;
    int intentos = 0; // Contador de intentos

    while (intentos < 3) { // Permitir hasta 3 intentos
        cout << "Ingrese su nombre de usuario: ";
        cin >> usuario;

        cout << "Ingrese su contraseña: ";
        contrasena = obtener_contrasena();
        cout << endl; // Para una mejor visualización

        // Verificar credenciales ingresadas
        if ((usuario == USUARIO_VENDEDOR && contrasena == CONTRASENA_VENDEDOR) ||
            (usuario == USUARIO_ADMIN && contrasena == CONTRASENA_ADMIN)) {
            cout << "Acceso concedido." << endl;
            return 0; // Salir del programa si las credenciales son correctas
        } else {
            intentos++; // Incrementar el contador de intentos
            cout << "Acceso denegado. Usuario o contraseña incorrectos." << endl;
            cout << "Intentos restantes: " << (3 - intentos) << endl;
        }
    }

    cout << "Número máximo de intentos alcanzado. El programa finalizará." << endl;
    return 1; // Salir del programa con un código de error
}
