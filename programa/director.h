#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <stdio.h>
#include "usuario-registrado.h"

class Director : public UsuarioRegistrado{

    private:

        std::string contrasena_director_;

    public:
    Director(std::string dni, std::string nombre, std::string apellido, std::string contrasena, std::string contrasena_director, std::string email = "empty", int dia = 0, int mes = 0, int anio = 0):UsuarioRegistrado(dni, nombre, apellido, email, contrasena, dia, mes ,anio){
        contrasena_director_=contrasena_director;
    }
   
    bool PublicarActividad();
    bool ModificarActividad(std::string nombreActividad);
    int VerAsistencia(std::string nombreActividad);
    bool ExpulsarAlumno(std::string actividad, std::string dni);
    bool VerCola();
    void SetContrasenaDirector(std::string contrasena_director){contrasena_director_=contrasena_director;}
    std::string GetContrasenaDirector(){return contrasena_director_;}
    //AÑADIR LOS GET Y SET

};


#endif