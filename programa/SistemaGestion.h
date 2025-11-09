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
    // --- Estructura de Datos Interna ---
    // Usamos un struct simple para guardar preinscripciones en memoria
    struct Preinscripcion {
        std::string nombreActividad;
        std::string dniUsuario;
        // (Podemos añadir más campos si es necesario, como el email o nombre)
    };

    struct ColaEspera {
        std::string nombreActividad;
        std::string dniUsuario;
    };

    // --- Almacenamiento de Datos en Memoria ---
    std::vector<UsuarioRegistrado> usuarios_;
    std::vector<Director> directores_;
    std::vector<Actividad> actividades_;
    std::vector<Preinscripcion> preinscripciones_;
    std::vector<ColaEspera> colas_;

    // --- Usuario Actual ---
    Usuario* usuarioActual_; // Puntero al usuario logueado

    // --- Variables de Estado y Temporales ---
    // (Estas variables ya las deberías tener de la vez anterior)
    int dia_, mes_, anio_; 
    std::string nombre_, apellido_;
    std::string dni_temp_, contrasena_temp_, email_temp_, contrasenaDirector_temp_;
    std::string nombreActividad_temp_;
    bool salirDelPrograma_;

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

    // --- Métodos de Lógica de Usuario Registrado ---
    bool manejarPreinscripcion();
    bool manejarAnulacion();
    void visualizarActividadesUsuario();

    // --- Métodos de Validación (Movidos de otros archivos) ---
    // Los hacemos 'static' porque no dependen de un objeto 'SistemaGestion'
    static bool compruebaDni(const std::string& dni);
    static bool esFechaValida(int dia, int mes, int anio);
    static bool contieneDominio(const std::string& email);
    static bool esIBANValido(const std::string& iban);

    // --- Métodos de Lógica de Director ---
    bool manejarPublicarActividad();
    bool manejarModificarActividad();
    void manejarVerAsistencia();
    bool manejarExpulsarAlumno();
    void manejarVerCola(); 

public:
    // --- Constructor y Destructor ---
    SistemaGestion();
    ~SistemaGestion();

    // --- Función Principal ---
    void Run();
};

#endif // SISTEMA_GESTION_H