#ifndef ACTIVIDAD_H
#define ACTIVIDAD_H

#include<iostream>

class Actividad{

    private:
        std::string nombreActividad_;
        int dia_;
        int mes_;
        int anio_;
        int aforoMaximo_;
        float precio_;
        
  
    public:

        //REALIZAR EL CONSTRUCTOR, LOS GETS Y SETS
        Actividad(std::string nombreActividad,int dia, int mes, int anio, int aforoMaximo,float precio){
            nombreActividad_=nombreActividad;
            dia_=dia;
            mes_=mes;
            anio_=anio;
            aforoMaximo_=aforoMaximo;
            precio_=precio;
        }
        std::string GetNombreActividad(){return nombreActividad_;}
        void SetNombreActividad(std::string nombreActividad){nombreActividad_=nombreActividad;}
        int GetAforoMaximo(){return aforoMaximo_;}
        void SetAforoMaximo(int aforoMaximo){aforoMaximo_=aforoMaximo;}
        int GetPrecio(){return precio_;}
        void SetPrecio(int precio){precio_=precio;}
        

};


#endif