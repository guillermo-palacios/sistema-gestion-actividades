// --- EN PROGRAMA/ACTIVIDAD.H ---

#ifndef ACTIVIDAD_H
#define ACTIVIDAD_H

#include <iostream>

class Actividad {
private:
    std::string nombreActividad_;
    int dia_;
    int mes_;
    int anio_;
    int aforoMaximo_;
    float precio_;

public:
    // Constructor (como lo tenías)
    Actividad(std::string nombreActividad, int dia, int mes, int anio, int aforoMaximo, float precio) {
        nombreActividad_ = nombreActividad;
        dia_ = dia;
        mes_ = mes;
        anio_ = anio;
        aforoMaximo_ = aforoMaximo;
        precio_ = precio;
    }

    // --- Getters (¡Necesarios para guardarDatos!) ---
    std::string GetNombreActividad() const { return nombreActividad_; }
    int GetDia() const { return dia_; }
    int GetMes() const { return mes_; }
    int GetAnio() const { return anio_; }
    int GetAforoMaximo() const { return aforoMaximo_; }
    float GetPrecio() const { return precio_; }
    
    // --- Setters ---
    // (Necesarios para modificar la actividad)
    void SetNombreActividad(const std::string& nombre) { nombreActividad_ = nombre; }
    void SetFecha(int dia, int mes, int anio) {
        dia_ = dia;
        mes_ = mes;
        anio_ = anio;
    }
    void SetPrecio(float precio) { precio_ = precio; }
    void SetAforo(int aforo) { aforoMaximo_ = aforo; }
};

#endif