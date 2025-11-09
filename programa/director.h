#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <string>
#include "usuario-registrado.h"

class Director : public UsuarioRegistrado {

private:
    std::string contrasena_director_;

public:
    Director(std::string dni, std::string nombre, std::string apellido, std::string contrasena, std::string contrasena_director, std::string email = "empty", int dia = 0, int mes = 0, int anio = 0)
        : UsuarioRegistrado(dni, nombre, apellido, contrasena, email, dia, mes, anio) {
        contrasena_director_ = contrasena_director;
    }

    virtual ~Director() = default; 

    // --- Getter ---
    std::string GetContrasenaDirector() const { return contrasena_director_; }

    // --- Setter ---
    void SetContrasenaDirector(std::string contrasena_director) { contrasena_director_ = contrasena_director; }
    
};

#endif