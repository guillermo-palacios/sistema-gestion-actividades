#ifndef USUARIO_H
#define USUARIO_H

#include<iostream>

class Usuario{

    private:
        std::string nombre_;
        std::string apellido_;


    public:
    Usuario(std::string nombre, std::string apellido){
        nombre_=nombre; 
        apellido_=apellido; 
    }

    virtual ~Usuario() = default; // <-- Esto hace la clase polimórfica

    bool IniciarSesion(std::string dni, std::string contrasena, std::string contrasenaDirector);
    bool Registrarse(std::string nombre, std::string apellido, std::string dni, int dia, int mes, int anio, std::string email, std::string contrasena, std::string contrasenaDirector);

    bool VisualizarActividades();
    std::string GetNombre(){return nombre_;}
    void SetNombre(std::string nombre){nombre_ = nombre;}

    std::string GetApellido(){return apellido_;}
    void SetApellido(std::string apellido){apellido_ = apellido;}

    


};

#endif
