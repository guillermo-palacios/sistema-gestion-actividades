#include "SistemaGestion.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

// --- Constructor ---
SistemaGestion::SistemaGestion() {
    usuarioActual_ = nullptr; 
    salirDelPrograma_ = false;
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
        
    } while (!salirDelPrograma_);
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
            salirDelPrograma_ = true;
            break;
        default:
            std::cout<<"Seleccione una de las 4 opciones mostradas"<<std::endl;
    }
}

// --- Métodos de Lógica (Aún vacíos) ---

bool SistemaGestion::manejarLogin() {
    int modo = 0;
    std::string dni, contrasena, contrasenaDirector;

    std::cout << "--- Iniciar Sesión ---" << std::endl;

    while (modo != 1 && modo != 2) {
        std::cout << "==============================================================" << std::endl;
        std::cout << "1-. Acceder como estudiante." << std::endl;
        std::cout << "2-. Acceder como director." << std::endl;
        std::cout << "Seleccione el modo:" << std::endl;
        std::cout << "==============================================================" << std::endl;
        std::cin >> modo;
        if (modo != 1 && modo != 2) {
            std::cout << "Seleccione un modo valido." << std::endl;
        }
    }

    std::cout << "Introduzca su DNI: " << std::endl;
    std::cin >> dni;
    std::cout << "Introduzca su Contrasena: " << std::endl;
    std::cin >> contrasena;

    // --- 1. Limpiamos cualquier sesión anterior ---
    // (Esto es por seguridad, por si 'cerrarSesion' no se llamó)
    if (usuarioActual_ != nullptr) {
        delete usuarioActual_;
        usuarioActual_ = nullptr;
    }

    // --- 2. Lógica de Login ---
    if (modo == 2) { // INTENTO DE LOGIN COMO DIRECTOR
        std::cout << "Introduzca su Contrasena de Director: " << std::endl;
        std::cin >> contrasenaDirector;

        // Buscamos en el vector de directores
        for (const Director& director : directores_) {
            if (director.GetDni() == dni && 
                director.GetContrasena() == contrasena &&
                director.GetContrasenaDirector() == contrasenaDirector) 
            {
                // ¡Coincidencia! Creamos un NUEVO objeto Director en el puntero
                // (Usamos el constructor de copia de la clase)
                usuarioActual_ = new Director(director); 
                return true; // Login exitoso
            }
        }
        
        // Si sale del bucle, no lo ha encontrado
        std::cout << "Error: DNI, contraseña o clave de director incorrectos." << std::endl;
        return false;

    } else { // INTENTO DE LOGIN COMO ESTUDIANTE
        
        // Buscamos en el vector de usuarios
        for (const UsuarioRegistrado& usuario : usuarios_) {
            if (usuario.GetDni() == dni && usuario.GetContrasena() == contrasena) 
            {
                // ¡Coincidencia! Creamos un NUEVO objeto UsuarioRegistrado
                usuarioActual_ = new UsuarioRegistrado(usuario);
                return true; // Login exitoso
            }
        }

        // Si sale del bucle, no lo ha encontrado
        std::cout << "Error: DNI o contraseña incorrectos." << std::endl;
        return false;
    }
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
    std::cout << "--- Visualizar Actividades Disponibles ---" << std::endl;
    std::cout << "===============================================================" << std::endl;

    if (actividades_.empty()) {
        std::cout << "No hay actividades disponibles en este momento." << std::endl;
    } else {
        // Recorremos el vector de actividades
        for (const Actividad& actividad : actividades_) {
            // Imprimimos los datos usando los Getters
            std::cout << "Nombre: " << actividad.GetNombreActividad() << std::endl;
            std::cout << "  Fecha: " << actividad.GetDia() << "/"
                      << actividad.GetMes() << "/" << actividad.GetAnio() << std::endl;
            std::cout << "  Precio: " << actividad.GetPrecio() << " EUR" << std::endl;
            std::cout << "---------------------------------------------------" << std::endl;
        }
    }
    std::cout << "===============================================================" << std::endl;    
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
    int opcion2;
    std::cout << "==============================================================" << std::endl;
    std::cout << "  BIENVENIDO, " << usuarioActual_->GetNombre() << " (Usuario) " << std::endl; // ¡Mejora!
    std::cout << "==============================================================" << std::endl;
    std::cout << "1-. Visualizar actividades disponibles." << std::endl;
    std::cout << "2-. Preinscribirse a una actividad." << std::endl;
    std::cout << "3-. Anular una preinscripción." << std::endl;
    std::cout << "4-. Cerrar sesión." << std::endl;
    std::cout << "==============================================================" << std::endl;
    std::cin >> opcion2;

    switch (opcion2) {
    case 1:
        visualizarActividadesUsuario();
        break;
    case 2:
        if (!manejarPreinscripcion()) {
            std::cout << "Error al realizar la preinscripcion." << std::endl;
        }
        break;
    case 3:
        if (!manejarAnulacion()) {
            std::cout << "Error al anular la preinscripcion." << std::endl;
        }
        break;
    case 4:
        std::cout << "==============================================================" << std::endl;
        std::cout << "CERRANDO SESION." << std::endl;
        std::cout << "==============================================================" << std::endl;
        cerrarSesion(); // Llama a la función de cerrar sesión
        break;
    default:
        std::cout << "Seleccione una opcion valida." << std::endl;
    }
}

void SistemaGestion::visualizarActividadesUsuario() {
    // Por ahora, el usuario ve lo mismo que el visitante.
    visualizarActividadesVisitante();
}

bool SistemaGestion::manejarPreinscripcion() {
    std::string nombreActividad, IBAN;
    std::cin.ignore(); // Limpiar el buffer del 'cin' anterior
    std::cout << "Introduzca el nombre de la actividad a la que desea preinscribirse: " << std::endl;
    std::getline(std::cin, nombreActividad);

    // --- 1. Obtener el DNI del usuario actual ---
    // Lo tenemos en 'usuarioActual_'
    // Necesitamos hacer un 'cast' para acceder a GetDni()
    UsuarioRegistrado* usuario = dynamic_cast<UsuarioRegistrado*>(usuarioActual_);
    if (!usuario) {
        std::cout << "Error crítico: El usuario actual no es un UsuarioRegistrado." << std::endl;
        return false;
    }
    std::string dniUsuario = usuario->GetDni();

    // --- 2. Validar que la actividad existe ---
    bool actividadEncontrada = false;
    for (const auto& act : actividades_) {
        if (act.GetNombreActividad() == nombreActividad) {
            actividadEncontrada = true;
            break;
        }
    }
    if (!actividadEncontrada) {
        std::cout << "Error: No existe ninguna actividad con ese nombre." << std::endl;
        return false;
    }

    // --- 3. Validar que no esté ya inscrito ---
    for (const auto& pre : preinscripciones_) {
        if (pre.dniUsuario == dniUsuario && pre.nombreActividad == nombreActividad) {
            std::cout << "Ya estás preinscrito en esta actividad." << std::endl;
            return false;
        }
    }

    // --- 4. Pedir y validar pago ---
    std::cout << "==============================================================" << std::endl;
    std::cout << "A continuacion se realizara el pago de dicha actividad:" << std::endl;
    std::cout << "Introduzca el IBAN de su cuenta bancaria (Formato: ES + 22 dígitos): " << std::endl;
    std::cin >> IBAN;

    if (!SistemaGestion::esIBANValido(IBAN)) {
        std::cout << "El IBAN no es válido. Debe tener el formato ES seguido de 22 dígitos." << std::endl;
        return false; // ¡Detiene el proceso!
    }
    
    std::cout << "El IBAN es válido. El pago se procesará." << std::endl;
    std::cout << "==============================================================" << std::endl;

    // --- 5. Añadir al vector de preinscripciones ---
    Preinscripcion nuevaPre;
    nuevaPre.dniUsuario = dniUsuario;
    nuevaPre.nombreActividad = nombreActividad;
    preinscripciones_.push_back(nuevaPre);

    std::cout << "¡Preinscripción realizada con éxito!" << std::endl;
    return true;
}

bool SistemaGestion::manejarAnulacion() {
    std::string nombreActividad;
    std::cin.ignore(); // Limpiar el buffer
    std::cout << "Introduzca el nombre de la actividad que desea anular: " << std::endl;
    std::getline(std::cin, nombreActividad);

    // --- 1. Obtener DNI del usuario actual ---
    UsuarioRegistrado* usuario = dynamic_cast<UsuarioRegistrado*>(usuarioActual_);
    if (!usuario) return false; // Error silencioso
    std::string dniUsuario = usuario->GetDni();

    // --- 2. Buscar y eliminar la preinscripción ---
    bool encontrado = false;
    // Usamos un iterador para poder borrar elementos mientras recorremos
    for (auto it = preinscripciones_.begin(); it != preinscripciones_.end(); ++it) {
        if (it->dniUsuario == dniUsuario && it->nombreActividad == nombreActividad) {
            // ¡Encontrado! Lo borramos del vector
            it = preinscripciones_.erase(it);
            encontrado = true;
            break; // Asumimos que solo se puede inscribir una vez
        }
    }

    if (encontrado) {
        std::cout << "Preinscripción anulada con éxito." << std::endl;
        return true;
    } else {
        std::cout << "Error: No se ha encontrado ninguna preinscripción a tu nombre para esa actividad." << std::endl;
        return false;
    }
}

void SistemaGestion::mostrarMenuDirector() {
    int opcion;
    std::cout << "========================================================================" << std::endl;
    std::cout << " BIENVENIDO, " << usuarioActual_->GetNombre() << " (Director) " << std::endl; // ¡Mejora!
    std::cout << "========================================================================" << std::endl;
    std::cout << "1-. Publicar una actividad." << std::endl;
    std::cout << "2-. Modificar una actividad académica." << std::endl;
    std::cout << "3-. Visualizar la asistencia a una actividad." << std::endl;
    std::cout << "4-. Expulsar alumno de una actividad." << std::endl;
    std::cout << "5-. Visualizar la cola de una actividad." << std::endl;
    std::cout << "6-. Visualizar actividades disponibles." << std::endl;
    std::cout << "7-. Cerrar sesión." << std::endl;
    std::cout << "========================================================================" << std::endl;
    std::cin >> opcion;

    switch (opcion) {
    case 1:
        if (manejarPublicarActividad()) {
            std::cout << "Actividad publicada con éxito." << std::endl;
        } else {
            std::cout << "Error al publicar la actividad." << std::endl;
        }
        break;
    case 2:
        if (manejarModificarActividad()) {
            std::cout << "Actividad modificada con éxito." << std::endl;
        } else {
            std::cout << "Error al modificar la actividad." << std::endl;
        }
        break;
    case 3:
        manejarVerAsistencia();
        break;
    case 4:
        if (manejarExpulsarAlumno()) {
            std::cout << "Alumno expulsado con éxito." << std::endl;
        } else {
            std::cout << "Error al expulsar al alumno." << std::endl;
        }
        break;
    case 5:
        manejarVerCola();
        break;
    case 6:
        visualizarActividadesVisitante(); // Reutilizamos la función del visitante
        break;
    case 7:
        std::cout << "Cerrando sesión de Director..." << std::endl;
        cerrarSesion();
        break;
    default:
        std::cout << "Seleccione una opcion valida." << std::endl;
    }
}

bool SistemaGestion::manejarPublicarActividad() {
    std::string nombreActividad;
    int dia, mes, anio, aforo; // (Aunque 'aforo' no lo usamos aún)
    float precio;

    std::cout << "--- Publicar Nueva Actividad ---" << std::endl;
    std::cout << "Introduce el nombre de la actividad (una sola palabra): " << std::endl;
    std::cin >> nombreActividad;

    // Validamos que la actividad no exista ya
    for (const auto& act : actividades_) {
        if (act.GetNombreActividad() == nombreActividad) {
            std::cout << "Error: Ya existe una actividad con ese nombre." << std::endl;
            return false;
        }
    }

    std::cout << "Introduzca la fecha 'DD MM YYYY': " << std::endl;
    std::cin >> dia >> mes >> anio;
    if (!SistemaGestion::esFechaValida(dia, mes, anio)) {
        std::cout << "Error: Fecha inválida." << std::endl;
        return false;
    }

    std::cout << "Introduzca el precio (ej: 50.0): " << std::endl;
    std::cin >> precio;
    if (precio < 0) {
        std::cout << "Error: El precio no puede ser negativo." << std::endl;
        return false;
    }
    
    std::cout << "Introduzca el aforo máximo: " << std::endl;
    std::cin >> aforo;

    // Creamos la actividad y la añadimos al vector en memoria
    Actividad nuevaActividad(nombreActividad, dia, mes, anio, aforo, precio);
    actividades_.push_back(nuevaActividad);

    return true; // ¡Éxito!
}

void SistemaGestion::manejarVerAsistencia() {
    std::string nombreActividad;
    std::cin.ignore(); // Limpiar buffer
    std::cout << "Introduce el nombre de la actividad para ver su asistencia: " << std::endl;
    std::getline(std::cin, nombreActividad);

    int contador = 0;
    std::cout << "--- Lista de Asistencia para '" << nombreActividad << "' ---" << std::endl;
    
    // Recorremos el vector de preinscripciones buscando coincidencias
    for (const auto& pre : preinscripciones_) {
        if (pre.nombreActividad == nombreActividad) {
            // ¡Coincidencia! Buscamos el nombre del usuario
            std::string nombreUsuario = "DNI: " + pre.dniUsuario; // Default
            for(const auto& usr : usuarios_) {
                if(usr.GetDni() == pre.dniUsuario) {
                    nombreUsuario = usr.GetNombre() + " " + usr.GetApellido() + " (" + usr.GetEmail() + ")";
                    break;
                }
            }
            std::cout << "- " << nombreUsuario << std::endl;
            contador++;
        }
    }

    if (contador == 0) {
        std::cout << "No hay ningún alumno inscrito en esta actividad." << std::endl;
    } else {
        std::cout << "Total: " << contador << " alumnos inscritos." << std::endl;
    }
    std::cout << "========================================" << std::endl;
}

bool SistemaGestion::manejarExpulsarAlumno() {
    std::string nombreActividad, dniAlumno;
    
    std::cout << "Introduce el DNI del alumno a expulsar: " << std::endl;
    std::cin >> dniAlumno;
    
    std::cin.ignore(); // Limpiar buffer
    std::cout << "Introduce el nombre de la actividad de la que será expulsado: " << std::endl;
    std::getline(std::cin, nombreActividad);

    // Reutilizamos la lógica de 'manejarAnulacion'
    // Buscamos y borramos la preinscripción
    bool encontrado = false;
    for (auto it = preinscripciones_.begin(); it != preinscripciones_.end(); ++it) {
        if (it->dniUsuario == dniAlumno && it->nombreActividad == nombreActividad) {
            it = preinscripciones_.erase(it);
            encontrado = true;
            break;
        }
    }

    return encontrado;
}

// --- (Funciones pendientes) ---

bool SistemaGestion::manejarModificarActividad() {
    std::string nombreActividad;
    std::cin.ignore(); // Limpiar buffer
    std::cout << "Introduce el nombre de la actividad que deseas modificar: " << std::endl;
    std::getline(std::cin, nombreActividad);

    // --- 1. Buscar la actividad ---
    // ¡OJO! Necesitamos un iterador, no un 'const'
    for (auto it = actividades_.begin(); it != actividades_.end(); ++it) {
        if (it->GetNombreActividad() == nombreActividad) {
            // ¡La encontramos! 'it' apunta a la actividad en el vector
            
            std::cout << "Actividad encontrada. Introduce los nuevos datos." << std::endl;
            
            // --- 2. Pedir y Validar Nuevos Datos ---
            std::string nuevoNombre;
            int nuevoDia, nuevoMes, nuevoAnio, nuevoAforo;
            float nuevoPrecio;

            std::cout << "Introduce el NUEVO nombre (o el mismo): " << std::endl;
            std::cin >> nuevoNombre;

            // Validamos que el NUEVO nombre no exista (excepto en esta misma actividad)
            for (const auto& otraAct : actividades_) {
                if (otraAct.GetNombreActividad() == nuevoNombre && otraAct.GetNombreActividad() != nombreActividad) {
                    std::cout << "Error: Ya existe OTRA actividad con ese nuevo nombre." << std::endl;
                    return false;
                }
            }

            std::cout << "Introduce la NUEVA fecha 'DD MM YYYY': " << std::endl;
            std::cin >> nuevoDia >> nuevoMes >> nuevoAnio;
            if (!SistemaGestion::esFechaValida(nuevoDia, nuevoMes, nuevoAnio)) {
                std::cout << "Error: Fecha inválida." << std::endl;
                return false;
            }

            std::cout << "Introduce el NUEVO precio: " << std::endl;
            std::cin >> nuevoPrecio;
            
            std::cout << "Introduce el NUEVO aforo: " << std::endl;
            std::cin >> nuevoAforo;

            // --- 3. Actualizar el objeto usando los Setters ---
            it->SetNombreActividad(nuevoNombre);
            it->SetFecha(nuevoDia, nuevoMes, nuevoAnio);
            it->SetPrecio(nuevoPrecio);
            it->SetAforo(nuevoAforo);

            return true; // ¡Éxito!
        }
    }

    // Si el bucle termina, no se encontró la actividad
    std::cout << "Error: No se ha encontrado ninguna actividad con ese nombre." << std::endl;
    return false;
}

void SistemaGestion::manejarVerCola() {
    std::cout << "¡Función 'Ver Cola' aún no implementada!" << std::endl;
}

// --- Métodos de Carga/Guardado ---

void SistemaGestion::cargarDatos() {
    std::ifstream fichero;
    std::string linea;

    // --- 1. Cargar Usuarios ---
    fichero.open("UsuariosRegistrados.txt");
    if (!fichero.is_open()) {
        std::cout << "Advertencia: No se pudo abrir 'UsuariosRegistrados.txt'." << std::endl;
    } else {
        while (std::getline(fichero, linea)) {
            if (linea.empty() || linea[0] == '#') continue; 
            std::stringstream ss(linea);
            std::string nombre, apellido, dni, email, contrasena;
            int dia = 0, mes = 0, anio = 0; char barra;
            ss >> nombre >> apellido >> dni >> dia >> barra >> mes >> barra >> anio >> email >> contrasena;
            usuarios_.push_back(UsuarioRegistrado(dni, nombre, apellido, contrasena, email, dia, mes, anio));
        }
        fichero.close();
        std::cout << "Cargados " << usuarios_.size() << " usuarios." << std::endl;
    }

    // --- 2. Cargar Directores ---
    fichero.open("Directores.txt");
    if (!fichero.is_open()) {
        std::cout << "Advertencia: No se pudo abrir 'Directores.txt'." << std::endl;
    } else {
        while (std::getline(fichero, linea)) {
            if (linea.empty() || linea[0] == '#') continue;
            std::stringstream ss(linea);
            std::string nombre, apellido, dni, email, contrasena, contrasenaDir;
            int dia = 0, mes = 0, anio = 0; char barra;
            ss >> nombre >> apellido >> dni >> dia >> barra >> mes >> barra >> anio >> email >> contrasena >> contrasenaDir;
            directores_.push_back(Director(dni, nombre, apellido, contrasena, contrasenaDir, email, dia, mes, anio));
        }
        fichero.close();
        std::cout << "Cargados " << directores_.size() << " directores." << std::endl;
    }

    // --- 3. Cargar Actividades ---
    fichero.open("Actividades.txt");
    if (!fichero.is_open()) {
        std::cout << "Advertencia: No se pudo abrir 'Actividades.txt'." << std::endl;
    } else {
        while (std::getline(fichero, linea)) {
            if (linea.empty() || linea[0] == '#') continue;
            std::stringstream ss(linea);
            std::string nombreActividad;
            float precio; int dia = 0, mes = 0, anio = 0; char barra;
            ss >> nombreActividad >> dia >> barra >> mes >> barra >> anio >> precio;
            actividades_.push_back(Actividad(nombreActividad, dia, mes, anio, 0, precio));
        }
        fichero.close();
        std::cout << "Cargadas " << actividades_.size() << " actividades." << std::endl;
    }

    // --- 4. Cargar Preinscripciones ---
    fichero.open("Preinscripciones.txt");
    if (!fichero.is_open()) {
        std::cout << "Advertencia: No se pudo abrir 'Preinscripciones.txt'." << std::endl;
    } else {
        while (std::getline(fichero, linea)) {
            if (linea.empty() || linea[0] == '#') continue;
            std::stringstream ss(linea);
            Preinscripcion pre;
            // Formato: DNI_Usuario Nombre_Actividad (simple)
            ss >> pre.dniUsuario >> pre.nombreActividad; 
            preinscripciones_.push_back(pre);
        }
        fichero.close();
        std::cout << "Cargadas " << preinscripciones_.size() << " preinscripciones." << std::endl;
    }}

void SistemaGestion::guardarDatos() {
    // --- 1. Guardar Usuarios ---
    std::ofstream ficheroUsuarios("UsuariosRegistrados.txt", std::ios::trunc);
    if (!ficheroUsuarios.is_open()) {
        std::cerr << "Error: No se pudo guardar 'UsuariosRegistrados.txt'." << std::endl;
    } else {
        ficheroUsuarios << "# Formato: Nombre Apellido DNI DD/MM/YYYY Email Contrasena" << std::endl;
        for (const auto& usuario : usuarios_) {
            ficheroUsuarios << usuario.GetNombre() << " " << usuario.GetApellido() << " "
                            << usuario.GetDni() << " " << usuario.GetDia() << "/"
                            << usuario.GetMes() << "/" << usuario.GetAnio() << " "
                            << usuario.GetEmail() << " " << usuario.GetContrasena() << std::endl;
        }
        ficheroUsuarios.close();
        std::cout << "Guardados " << usuarios_.size() << " usuarios." << std::endl;
    }

    // --- 2. Guardar Directores ---
    std::ofstream ficheroDirectores("Directores.txt", std::ios::trunc);
    if (!ficheroDirectores.is_open()) {
        std::cerr << "Error: No se pudo guardar 'Directores.txt'." << std::endl;
    } else {
        ficheroDirectores << "# Formato: Nombre Apellido DNI DD/MM/YYYY Email Contrasena ContrasenaDirector" << std::endl;
        for (const auto& director : directores_) {
            ficheroDirectores << director.GetNombre() << " " << director.GetApellido() << " "
                              << director.GetDni() << " " << director.GetDia() << "/"
                              << director.GetMes() << "/" << director.GetAnio() << " "
                              << director.GetEmail() << " " << director.GetContrasena() << " "
                              << director.GetContrasenaDirector() << std::endl;
        }
        ficheroDirectores.close();
        std::cout << "Guardados " << directores_.size() << " directores." << std::endl;
    }

    // --- 3. Guardar Actividades ---
    std::ofstream ficheroActividades("Actividades.txt", std::ios::trunc);
    if (!ficheroActividades.is_open()) {
        std::cerr << "Error: No se pudo guardar 'Actividades.txt'." << std::endl;
    } else {
        ficheroActividades << "# Formato: NombreActividad DD/MM/YYYY Precio" << std::endl;
        for (const auto& actividad : actividades_) {
            ficheroActividades << actividad.GetNombreActividad() << " "
                               << actividad.GetDia() << "/" << actividad.GetMes() << "/"
                               << actividad.GetAnio() << " " << actividad.GetPrecio() << std::endl;
        }
        ficheroActividades.close();
        std::cout << "Guardadas " << actividades_.size() << " actividades." << std::endl;
    }

    // --- 4. Guardar Preinscripciones ---
    std::ofstream ficheroPreinscripciones("Preinscripciones.txt", std::ios::trunc);
    if (!ficheroPreinscripciones.is_open()) {
        std::cerr << "Error: No se pudo guardar 'Preinscripciones.txt'." << std::endl;
    } else {
        ficheroPreinscripciones << "# Formato: DNI_Usuario Nombre_Actividad" << std::endl;
        for (const auto& pre : preinscripciones_) {
            ficheroPreinscripciones << pre.dniUsuario << " " << pre.nombreActividad << std::endl;
        }
        ficheroPreinscripciones.close();
        std::cout << "Guardadas " << preinscripciones_.size() << " preinscripciones." << std::endl;
    }
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

bool SistemaGestion::esIBANValido(const std::string& iban) {
    // Usamos la validación simple de formato español (ES + 22 dígitos)
    std::regex formatoEspanol("ES[0-9]{22}");
    return std::regex_match(iban, formatoEspanol);
}