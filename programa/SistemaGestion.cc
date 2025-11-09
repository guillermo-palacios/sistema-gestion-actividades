#include "SistemaGestion.h"
#include <iostream>
#include <fstream>
#include <sstream>

// --- Constructor ---
SistemaGestion::SistemaGestion() {
    usuarioActual_ = nullptr; 
    cargarDatos();
    std::cout << "Sistema de Gestión inicializado." << std::endl;
}

// --- Destructor ---
SistemaGestion::~SistemaGestion() {
    guardarDatos();
    if (usuarioActual_ != nullptr) {
        delete usuarioActual_; // Limpiamos la memoria
    }
    std::cout << "Sistema de Gestión finalizado. Datos guardados." << std::endl;
}

// --- Función Principal (¡Ahora limpia!) ---
void SistemaGestion::Run() {
    
    // Pedimos nombre y apellido una sola vez al inicio
    std::cout<<"Introduzca su nombre y su primer apellido para poder acceder al sistema: "<<std::endl;
    std::cin >> nombre_; // Usamos la variable miembro nombre_
    std::cin >> apellido_; // Usamos la variable miembro apellido_


    bool salir = false;
    do {
        if (usuarioActual_ == nullptr) {
            // Nadie ha iniciado sesión
            mostrarMenuVisitante();
        } else if (dynamic_cast<Director*>(usuarioActual_) != nullptr) {
            // El usuario actual es un Director
            mostrarMenuDirector();
        } else {
            // El usuario actual es un UsuarioRegistrado
            mostrarMenuUsuario();
        }
        // (La variable 'salir' se controlará dentro de los menús)
        // (Por ahora, forzamos la salida para no crear un bucle infinito)
         salir = true; // <--- ¡¡BORRAREMOS ESTO PRONTO!!

    } while (!salir);
}

// --- Menú de Visitante ---
void SistemaGestion::mostrarMenuVisitante() {
    int opcion;
    std::cout<<"=============================================================="<<std::endl;
    std::cout<<" BIENVENIDO A NUESTRO SISTEMA DE GESTION DE ACTIVIDADES 404  "<<std::endl;
    std::cout<<"=============================================================="<<std::endl;
    std::cout<<"1-. Iniciar Sesion.  "<<std::endl;
    std::cout<<"2-. Registrarse.  "<<std::endl;
    std::cout<<"3-. Visualizar actividades academicas.  "<<std::endl;
    std::cout<<"4-. Salir.  "<<std::endl;
    std::cout<<"=============================================================="<<std::endl;
    std::cin>>opcion;

    switch(opcion) {
        case 1:
            if (manejarLogin()) {
                std::cout << "¡Inicio de sesión exitoso!" << std::endl;
            } else {
                std::cout << "Error en el inicio de sesión." << std::endl;
            }
            break;
        case 2:
            if (manejarRegistro()) {
                std::cout << "¡Registro exitoso! Por favor, inicie sesión." << std::endl;
            } else {
                std::cout << "Error en el registro." << std::endl;
            }
            break;
        case 3:
            visualizarActividadesVisitante();
            break;
        case 4:
            std::cout<<"=============================================================="<<std::endl;
            std::cout<<"GRACIAS POR SU VISITA, NOS VEMOS PRONTO !!    "<<std::endl;
            std::cout<<"=============================================================="<<std::endl;
            // salir = true; // <-- Esto lo implementaremos
            break;
        default:
            std::cout<<"Seleccione una de las 4 opciones mostradas"<<std::endl;
    }
}

// --- Métodos de Lógica (Aún vacíos) ---

bool SistemaGestion::manejarLogin() {
    std::cout << "--- Iniciar Sesión ---" << std::endl;
    // ... Próximamente: Lógica de pedir DNI/Pass ...
    // ... y buscar en los vectores 'usuarios_' y 'directores_' ...
    // ... Si se encuentra, 'usuarioActual_' = new UsuarioRegistrado(...) ...
    return false; // Por ahora, siempre falla
}

bool SistemaGestion::manejarRegistro() {
    std::cout << "--- Registrarse ---" << std::endl;
    // ... Próximamente: Lógica de pedir DNI/Email/Pass ...
    // ... Usar compruebaDni(), etc. para validar ...
    // ... y añadir un nuevo UsuarioRegistrado al vector 'usuarios_' ...
    return false; // Por ahora, siempre falla
}

void SistemaGestion::visualizarActividadesVisitante() {
    std::cout << "--- Visualizar Actividades ---" << std::endl;
    // ... Próximamente: Recorrer el vector 'actividades_' e imprimirlas ...
}

void SistemaGestion::cerrarSesion() {
    if (usuarioActual_ != nullptr) {
        delete usuarioActual_;
        usuarioActual_ = nullptr;
        std::cout << "Sesión cerrada." << std::endl;
    }
}

// --- Métodos de Menús de Usuario/Director (Aún vacíos) ---

void SistemaGestion::mostrarMenuUsuario() {
    std::cout << "¡¡¡MENÚ DE USUARIO AÚN NO IMPLEMENTADO!!!" << std::endl;
    cerrarSesion(); // Cerramos sesión para no bloquear el bucle
}

void SistemaGestion::mostrarMenuDirector() {
    std::cout << "¡¡¡MENÚ DE DIRECTOR AÚN NO IMPLEMENTADO!!!" << std::endl;
    cerrarSesion(); // Cerramos sesión para no bloquear el bucle
}


// --- Métodos de Carga/Guardado (Aún vacíos) ---

void SistemaGestion::cargarDatos() {
    std::cout << "Cargando datos... (Aún no implementado)" << std::endl;
}

void SistemaGestion::guardarDatos() {
    std::cout << "Guardando datos... (Aún no implementado)" << std::endl;
}


// --- Funciones de Validación (Movidas aquí) ---

bool SistemaGestion::compruebaDni(const std::string& dni) {
    int tm_dni = dni.size();
    if (tm_dni != 9) return false;

    std::string letras = "TRWAGMYFPDXBNJZSQVHLCKE";
    std::string num_dni;
    
    for(int i=0; i<8; i++){
        if(isdigit(dni[i])) { num_dni += dni[i]; }
        else { return false; } 
    }

    int numero_dni = stoi(num_dni);
    char letra = letras[numero_dni % 23]; 
    
    return (dni[8] == letra || dni[8] == tolower(letra));
}

bool SistemaGestion::esFechaValida(int dia, int mes, int anio) {
    if (anio < 0) return false;
    if (mes < 1 || mes > 12) return false;

    int diasEnMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {
        diasEnMes[2] = 29;
    }

    return !(dia < 1 || dia > diasEnMes[mes]);
}

bool SistemaGestion::contieneDominio(const std::string& email) {
    size_t encontradoUco = email.find("@uco.es");
    size_t encontradoGmail = email.find("@gmail.com");
    return (encontradoUco != std::string::npos || encontradoGmail != std::string::npos);
}