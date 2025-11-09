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
    int modo = 0;
    std::string dni, email, contrasena, contrasenaDirector;
    int dia, mes, anio;

    std::cout << "--- Registrarse ---" << std::endl;

    while (modo != 1 && modo != 2) {
        std::cout << "==============================================================" << std::endl;
        std::cout << "1-. Registrarse como estudiante." << std::endl;
        std::cout << "2-. Registrarse como director." << std::endl;
        std::cout << "Seleccione el modo:" << std::endl;
        std::cout << "==============================================================" << std::endl;
        std::cin >> modo;
        if (modo != 1 && modo != 2) {
            std::cout << "Seleccione un modo valido." << std::endl;
        }
    }

    // --- 1. Pedir y Validar DNI ---
    std::cout << "Introduzca su DNI: " << std::endl;
    std::cin >> dni;
    if (!SistemaGestion::compruebaDni(dni)) {
        std::cout << "DNI incorrecto o con formato inválido." << std::endl;
        return false;
    }

    // --- 2. Comprobar Duplicados ---
    // (Buscamos en ambos vectores para asegurar que el DNI es único)
    for (const auto& usr : usuarios_) {
        if (usr.GetDni() == dni) {
            std::cout << "Ya existe un usuario registrado con ese DNI." << std::endl;
            return false;
        }
    }
    for (const auto& dir : directores_) {
        if (dir.GetDni() == dni) {
            std::cout << "Ya existe un director registrado con ese DNI." << std::endl;
            return false;
        }
    }

    // --- 3. Pedir y Validar Resto de Datos ---
    std::cout << "Introduzca su Fecha de Nacimiento 'DD MM YYYY': " << std::endl;
    std::cin >> dia >> mes >> anio;
    if (!SistemaGestion::esFechaValida(dia, mes, anio)) {
        std::cout << "Introduce una fecha de nacimiento valida." << std::endl;
        return false;
    }

    std::cout << "Introduzca su email: " << std::endl;
    std::cin >> email;
    if (!SistemaGestion::contieneDominio(email)) {
        std::cout << "Introduzca un correo finalizado en @uco.es o en su defecto @gmail.com" << std::endl;
        return false;
    }

    std::cout << "Introduzca su Contrasena: " << std::endl;
    std::cin >> contrasena;

    // --- 4. Añadir al Vector correspondiente ---
    if (modo == 2) { // REGISTRO DIRECTOR
        std::cout << "Introduzca su Contrasena de Director: " << std::endl;
        std::cin >> contrasenaDirector;
        
        // (Aquí puedes añadir una validación para la contrasenaDirector si quieres)
        // if (contrasenaDirector != "986532") { ... }

        // Creamos el nuevo Director
        Director nuevoDirector(dni, nombre_, apellido_, contrasena, contrasenaDirector, email, dia, mes, anio);
        // Lo añadimos al vector de directores en memoria
        directores_.push_back(nuevoDirector);
        std::cout << "Director registrado con éxito." << std::endl;

    } else { // REGISTRO ESTUDIANTE
        
        // Creamos el nuevo UsuarioRegistrado
        UsuarioRegistrado nuevoUsuario(dni, nombre_, apellido_, contrasena, email, dia, mes, anio);
        // Lo añadimos al vector de usuarios en memoria
        usuarios_.push_back(nuevoUsuario);
        std::cout << "Usuario registrado con éxito." << std::endl;
    }

    return true; // ¡El registro fue exitoso!
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


// --- Métodos de Carga/Guardado ---

void SistemaGestion::cargarDatos() {
    std::ifstream fichero;
    std::string linea;

    // --- 1. Cargar Usuarios Registrados ---
    fichero.open("UsuariosRegistrados.txt");
    if (!fichero.is_open()) {
        std::cout << "Advertencia: No se pudo abrir 'UsuariosRegistrados.txt'. Creando uno nuevo." << std::endl;
    } else {
        while (std::getline(fichero, linea)) {
            if (linea.empty() || linea[0] == '#') continue; // Ignorar líneas vacías o comentarios

            std::stringstream ss(linea);
            std::string nombre, apellido, dni, fechaStr, email, contrasena;
            int dia = 0, mes = 0, anio = 0;
            char barra; // Para consumir el '/' en la fecha

            // Formato: Nombre Apellido DNI DD/MM/YYYY Email Contrasena
            ss >> nombre >> apellido >> dni >> dia >> barra >> mes >> barra >> anio >> email >> contrasena;

            // Creamos un nuevo objeto UsuarioRegistrado con los datos leídos
            UsuarioRegistrado nuevoUsuario(dni, nombre, apellido, contrasena, email, dia, mes, anio);
            
            // Añadimos el nuevo usuario a nuestro vector en memoria
            usuarios_.push_back(nuevoUsuario);
        }
        fichero.close();
        std::cout << "Cargados " << usuarios_.size() << " usuarios." << std::endl;
    }

    // --- 2. Cargar Directores ---
    fichero.open("Directores.txt");
    if (!fichero.is_open()) {
        std::cout << "Advertencia: No se pudo abrir 'Directores.txt'. Creando uno nuevo." << std::endl;
    } else {
        while (std::getline(fichero, linea)) {
            if (linea.empty() || linea[0] == '#') continue; 

            std::stringstream ss(linea);
            std::string nombre, apellido, dni, fechaStr, email, contrasena, contrasenaDir;
            int dia = 0, mes = 0, anio = 0;
            char barra; 

            // Formato: Nombre Apellido DNI DD/MM/YYYY Email Contrasena ContrasenaDirector
            ss >> nombre >> apellido >> dni >> dia >> barra >> mes >> barra >> anio >> email >> contrasena >> contrasenaDir;

            Director nuevoDirector(dni, nombre, apellido, contrasena, contrasenaDir, email, dia, mes, anio);
            directores_.push_back(nuevoDirector);
        }
        fichero.close();
        std::cout << "Cargados " << directores_.size() << " directores." << std::endl;
    }

    // --- 3. Cargar Actividades ---
    fichero.open("Actividades.txt");
    if (!fichero.is_open()) {
        std::cout << "Advertencia: No se pudo abrir 'Actividades.txt'. Creando uno nuevo." << std::endl;
    } else {
        while (std::getline(fichero, linea)) {
            if (linea.empty() || linea[0] == '#') continue;

            std::stringstream ss(linea);
            std::string nombreActividad, fechaStr;
            float precio;
            int dia = 0, mes = 0, anio = 0;
            char barra;

            // Formato: NombreDeLaActividad (puede tener espacios) DD/MM/YYYY Precio
            // Leer hasta la fecha es más complicado si el nombre tiene espacios.
            // Por ahora, asumimos que el nombre NO tiene espacios para simplificar.
            // Si tu nombre tiene espacios, necesitaremos un parseo más avanzado.
            
            // Formato (simple): NombreActividad DD/MM/YYYY Precio
            ss >> nombreActividad >> dia >> barra >> mes >> barra >> anio >> precio;

            // (Nota: Faltan Aforo en el .txt y en la clase Actividad)
            Actividad nuevaActividad(nombreActividad, dia, mes, anio, 0 /*aforo*/, precio);
            actividades_.push_back(nuevaActividad);
        }
        fichero.close();
        std::cout << "Cargadas " << actividades_.size() << " actividades." << std::endl;
    }

    // (Aún no cargamos Preinscripciones ni Colas, lo haremos después)
}

void SistemaGestion::guardarDatos() {
    // Abrimos los ficheros en modo 'trunc' (truncar), que borra
    // el contenido anterior antes de escribir el nuevo.
    std::ofstream ficheroUsuarios("UsuariosRegistrados.txt", std::ios::trunc);
    std::ofstream ficheroDirectores("Directores.txt", std::ios::trunc);
    std::ofstream ficheroActividades("Actividades.txt", std::ios::trunc);

    // --- 1. Guardar Usuarios Registrados ---
    if (!ficheroUsuarios.is_open()) {
        std::cerr << "Error crítico: No se pudo abrir 'UsuariosRegistrados.txt' para guardar." << std::endl;
    } else {
        // Escribimos la cabecera (buena práctica)
        ficheroUsuarios << "# Formato: Nombre Apellido DNI DD/MM/YYYY Email Contrasena" << std::endl;
        
        // Recorremos el vector de usuarios
        for (const UsuarioRegistrado& usuario : usuarios_) {
            // Escribimos los datos de cada usuario en una nueva línea
            ficheroUsuarios << usuario.GetNombre() << " "
                            << usuario.GetApellido() << " "
                            << usuario.GetDni() << " "
                            << usuario.GetDia() << "/"
                            << usuario.GetMes() << "/"
                            << usuario.GetAnio() << " "
                            << usuario.GetEmail() << " "
                            << usuario.GetContrasena() << std::endl;
        }
        ficheroUsuarios.close();
        std::cout << "Guardados " << usuarios_.size() << " usuarios." << std::endl;
    }

    // --- 2. Guardar Directores ---
    if (!ficheroDirectores.is_open()) {
        std::cerr << "Error crítico: No se pudo abrir 'Directores.txt' para guardar." << std::endl;
    } else {
        ficheroDirectores << "# Formato: Nombre Apellido DNI DD/MM/YYYY Email Contrasena ContrasenaDirector" << std::endl;
        
        for (const Director& director : directores_) {
            ficheroDirectores << director.GetNombre() << " "
                              << director.GetApellido() << " "
                              << director.GetDni() << " "
                              << director.GetDia() << "/"
                              << director.GetMes() << "/"
                              << director.GetAnio() << " "
                              << director.GetEmail() << " "
                              << director.GetContrasena() << " "
                              << director.GetContrasenaDirector() << std::endl;
        }
        ficheroDirectores.close();
        std::cout << "Guardados " << directores_.size() << " directores." << std::endl;
    }

    // --- 3. Guardar Actividades ---
    if (!ficheroActividades.is_open()) {
        std::cerr << "Error crítico: No se pudo abrir 'Actividades.txt' para guardar." << std::endl;
    } else {
        ficheroActividades << "# Formato: NombreActividad DD/MM/YYYY Precio" << std::endl;
        
        for (const Actividad& actividad : actividades_) {
            // Asumimos que la clase Actividad tiene Getters para estos datos
            // ¡Tendremos que añadirlos si faltan!
            // ... (reemplaza la línea vieja) ...
            ficheroActividades << actividad.GetNombreActividad() << " "
                               << actividad.GetDia() << "/"
                               << actividad.GetMes() << "/"
                               << actividad.GetAnio() << " "
                               << actividad.GetPrecio() << std::endl;    
        
        }
        ficheroActividades.close();
        std::cout << "Guardadas " << actividades_.size() << " actividades." << std::endl;
    }

    // (Aún no guardamos Preinscripciones ni Colas)
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