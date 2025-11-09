#ifndef SISTEMA_GESTION_H
#define SISTEMA_GESTION_H

#include <vector>
#include <string>
#include "usuario.h"
#include "usuario-registrado.h"
#include "director.h"
#include "actividad.h"

class SistemaGestion {
private:
    // --- Almacenamiento de Datos en Memoria ---
    std::vector<UsuarioRegistrado> usuarios_;
    std::vector<Director> directores_;
    std::vector<Actividad> actividades_;
    // (Añadiremos preinscripciones y colas más tarde)

    // --- Usuario Actual ---
    Usuario* usuarioActual_; // Puntero al usuario logueado

    // --- Variables de Estado y Temporales ---
    // (Estas variables ya las deberías tener de la vez anterior)
    int dia_, mes_, anio_; 
    std::string nombre_, apellido_;
    std::string dni_temp_, contrasena_temp_, email_temp_, contrasenaDirector_temp_;
    std::string nombreActividad_temp_;


    // --- Métodos Privados (Ayudantes) ---
    void cargarDatos();
    void guardarDatos();

    // --- Métodos de Menú ---
    void mostrarMenuVisitante();
    void mostrarMenuUsuario();
    void mostrarMenuDirector();

    // --- Métodos de Lógica ---
    bool manejarLogin();    // Contendrá la lógica de pedir DNI/Pass
    bool manejarRegistro(); // Contendrá la lógica de pedir DNI/Email/etc.
    void visualizarActividadesVisitante();
    void cerrarSesion();

    // (Añadiremos más métodos de lógica de usuario/director aquí)

    // --- Métodos de Validación (Movidos de otros archivos) ---
    // Los hacemos 'static' porque no dependen de un objeto 'SistemaGestion'
    static bool compruebaDni(const std::string& dni);
    static bool esFechaValida(int dia, int mes, int anio);
    static bool contieneDominio(const std::string& email);

public:
    // --- Constructor y Destructor ---
    SistemaGestion();
    ~SistemaGestion();

    // --- Función Principal ---
    void Run();
};

#endif // SISTEMA_GESTION_H