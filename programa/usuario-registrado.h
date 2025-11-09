#ifndef USUARIO_REGISTRADO_H
#define USUARIO_REGISTRADO_H

#include<iostream>
#include <string>
#include "usuario.h"

class UsuarioRegistrado : public Usuario{

    private:
        std::string dni_;
        std::string email_;
        std::string contrasena_;
        int dia_;
        int mes_;
        int anio_;


    public:
        UsuarioRegistrado(std::string dni, std::string nombre, std::string apellido, std::string contrasena, std::string email = "empty", int dia = 0, int mes = 0 , int anio = 0):Usuario(nombre, apellido){
            dni_=dni;
            email_=email;
            contrasena_=contrasena;
            dia_=dia;
            mes_=mes;
            anio_=anio;   
        }

        virtual ~UsuarioRegistrado() = default;
        
        
        // --- Getters ---
        
        std::string GetDni() const { return dni_; } 
        std::string GetEmail() const { return email_; } 
        std::string GetContrasena() const { return contrasena_; } 
        int GetDia() const { return dia_; } 
        int GetMes() const { return mes_; } 
        int GetAnio() const { return anio_; } 

};

#endif
