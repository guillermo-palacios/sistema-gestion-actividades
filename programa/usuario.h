// --- programa/usuario.h ---

#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string> 

class Usuario {
protected: 
    // 'protected' permite a las clases hijas (UsuarioRegistrado) ver estas variables
    std::string nombre_;
    std::string apellido_;

public:
    Usuario(std::string nombre, std::string apellido) {
        nombre_ = nombre;
        apellido_ = apellido;
    }

    virtual ~Usuario() = default; 

    // --- Getters ---
    std::string GetNombre() const { return nombre_; }
    std::string GetApellido() const { return apellido_; }

    // --- Setters ---
    // void SetNombre(std::string nombre){nombre_ = nombre;}
    // void SetApellido(std::string apellido){apellido_ = apellido;}
};

#endif