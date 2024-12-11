#include <iostream>
#include <string>
#include <conio.h> // Para _getch()

using namespace std;

// Funci�n para ocultar la entrada de la contrase�a
// Esta funci�n captura caracteres sin mostrarlos en pantalla
// y devuelve la contrase�a ingresada como una cadena.
string obtener_contrasena() {
    string contrasena;
    char caracter;

    while (true) {
        caracter = _getch(); // Captura el car�cter sin mostrarlo en la consola

        if (caracter == '\r') { // Si se presiona Enter
            break; // Salir del bucle
        } else if (caracter == '\b') { // Si se presiona Backspace
            if (!contrasena.empty()) {
                contrasena.pop_back(); // Eliminar el �ltimo car�cter
                cout << "\b \b"; // Mover el cursor hacia atr�s y borrar el asterisco
            }
        } else {
            contrasena += caracter; // Agregar el car�cter a la contrase�a
            cout << '*'; // Mostrar un asterisco
        }
    }

    return contrasena; // Retornar la contrase�a ingresada
}

// Funci�n principal del programa
// Esta funci�n gestiona el proceso de login para vendedor y administrador.
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

        cout << "Ingrese su contrase�a: ";
        contrasena = obtener_contrasena();
        cout << endl; // Para una mejor visualizaci�n

        // Verificar credenciales ingresadas
        if ((usuario == USUARIO_VENDEDOR && contrasena == CONTRASENA_VENDEDOR) ||
            (usuario == USUARIO_ADMIN && contrasena == CONTRASENA_ADMIN)) {
            cout << "Acceso concedido." << endl;
            return 0; // Salir del programa si las credenciales son correctas
        } else {
            intentos++; // Incrementar el contador de intentos
            cout << "Acceso denegado. Usuario o contrase�a incorrectos." << endl;
            cout << "Intentos restantes: " << (3 - intentos) << endl;
        }
    }

    cout << "N�mero m�ximo de intentos alcanzado. El programa finalizar�." << endl;
    return 1; // Salir del programa con un c�digo de error
}
