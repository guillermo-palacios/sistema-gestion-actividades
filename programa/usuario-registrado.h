#ifndef USUARIO_REGISTRADO_H
#define USUARIO_REGISTRADO_H

#include<iostream>
#include "usuario.h"
#include "actividad.h"

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
        
        bool Preinscribirse(std::string actividad);
        bool AnularPreinscripcion(std::string actividad, std::string dni);
    
        std::string GetDni(){return dni_;}
        void SetDni(std::string dni){dni_=dni;}
    
        std::string GetEmail(){return email_;}
        void SetEmail(std::string email){email_=email;}
    
        std::string GetContrasena(){return contrasena_;}
        void SetContrasena(std::string contrasena){contrasena_=contrasena;}
    
        int GetDia(){return dia_;}
        void SetDia(int dia){dia_=dia;}
    
        int GetMes(){return mes_;}
        void SetMes(int mes){mes_=mes;}
        
        int GetAnio(){return anio_;}
        void SetAnio(int anio){anio_=anio;}
    





};



#endif
