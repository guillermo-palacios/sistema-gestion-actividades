#include "director.h"
#include<fstream>
#include<vector>


bool EsFechaCorrecta(int dia, int mes, int anio) {
    // Verificar el año
    if (anio < 0) {
        return false;
    }

    // Verificar el mes
    if (mes < 1 || mes > 12) {
        return false;
    }

    // Verificar el día
    int diasEnMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Ajustar días en febrero para años bisiestos
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {
        diasEnMes[2] = 29;
    }

    if (dia < 1 || dia > diasEnMes[mes]) {
        return false;
    }

    // Si pasa todas las verificaciones, la fecha es válida
    return true;
}

bool Director::PublicarActividad(){

    

    std::string nombreActividad;
    int dia, mes, anio, aforo;
    float precio;
    
    std::cout<<"Introduzca la fecha en que iniciara su actividad 'DD MM YYYY': "<<std::endl;
    std::cin>>dia>>mes>>anio;

    if(!EsFechaCorrecta(dia,mes,anio)){
        std::cout<<"Introduce una fecha de nacimiento valida."<<std::endl;
        return false;
    }

    std::cin.ignore();
    
    std::cout<<"Introduce el nombre de su actividad"<<std::endl;
    std::getline(std::cin, nombreActividad);


    std::cout<<"Introduzca el numero maximo de personas permitido en su actividad: "<<std::endl;
    std::cin>>aforo;
    
    std::cout<<"Introduzca el precio que tendra su actividad"<<std::endl;
    std::cin>>precio;

    std::ofstream fichero("Actividades.txt", std::ios::app); 
    
    if(fichero.is_open()){

        std::string nuevaActividad= nombreActividad + " " + std::to_string(dia) + "/" + std::to_string(mes) + "/" + std::to_string(anio) + " " + std::to_string(precio);  

        fichero<< nuevaActividad <<std::endl;
            
        fichero.close();
    }
    else{
        std::cout<<"Error en la apertura del fichero\n";
        return false;
    }

    return true;
}


bool Director::ModificarActividad(std::string nombreActividad){
    
    //ELIMINAMOS LA ACTIVIDAD ANTERIOR

    // Abrir el archivo en modo lectura
    std::ifstream fichero("Actividades.txt");
    
    // Verificar si el archivo se abrió correctamente
    if (!fichero.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return false;
    }

    // Crear un vector para almacenar las líneas que no deben ser eliminadas
    std::vector<std::string> lineas;

    // Leer el archivo línea por línea
    std::string linea;
    while (std::getline(fichero, linea)) {
        // Verificar si la línea contiene ambas palabras
        if (linea.find(nombreActividad) != std::string::npos) {
            // La línea contiene ambas palabras, no la almacenamos en el vector
            continue;
        }

        // Almacenar la línea en el vector
        lineas.push_back(linea);
    }

    // Cerrar el archivo de entrada
    fichero.close();

    // Abrir el archivo en modo escritura, eliminando el contenido existente
    std::ofstream archivoSalida("Actividades.txt", std::ios::trunc);

    // Verificar si el archivo se abrió correctamente
    if (!archivoSalida.is_open()) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return false;
    }

    // Escribir las líneas no eliminadas en el archivo
    for (const auto& linea : lineas) {
        archivoSalida << linea << std::endl;
    }

    // Cerrar el archivo de salida
    archivoSalida.close();

    //AÑADIMOS LA NUEVA ACTIVIDAD

    int dia, mes, anio, aforo;
    float precio;

    std::cout<<"Introduce los datos actualizados de su actividad"<<std::endl;


    std::cout<<"Introduce el nombre de su actividad"<<std::endl;
    std::getline(std::cin, nombreActividad);

    std::cout<<"Introduzca la fecha en que iniciara su actividad 'DD MM YYYY': "<<std::endl;
    std::cin>>dia>>mes>>anio;

    if(!EsFechaCorrecta(dia,mes,anio)){
        std::cout<<"Introduce una fecha de nacimiento valida."<<std::endl;
        return false;
    }

    std::cout<<"Introduzca el aforo maximo permitido en su actividad: "<<std::endl;
    std::cin>>aforo;
    
    std::cout<<"Introduzca el precio que tendra su actividad"<<std::endl;
    std::cin>>precio;

    //Escribimos en el fichero la actividad ya modificada

    std::ofstream fichero2("Actividades.txt", std::ios::app); 
    
    if(fichero2.is_open()){

        std::string nuevaActividad= nombreActividad + " " + std::to_string(dia) + "/" + std::to_string(mes) + "/" + std::to_string(anio) + " " + std::to_string(precio);  

        fichero2<< nuevaActividad <<std::endl;
            
        fichero2.close();
    }
    else{
        std::cout<<"Error en la apertura del fichero\n";
        return false;
    }

    return true;
}


int Director::VerAsistencia(std::string nombreActividad){

    std::ifstream fichero("Preinscripciones.txt");
    std::string linea;
    int contador = 0;

    if (!fichero.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return -1; // Retorna -1 en caso de error al abrir el archivo
    }

    while (std::getline(fichero, linea)) {
        if (linea.find(nombreActividad) != std::string::npos) {
            contador++;
        }
    }

    fichero.close();
    return contador;
}



bool Director::ExpulsarAlumno(std::string actividad, std::string dni){

        // Abrir el archivo en modo lectura
    std::ifstream fichero("Preinscripciones.txt");
    
    // Verificar si el archivo se abrió correctamente
    if (!fichero.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return false;
    }

    // Crear un vector para almacenar las líneas que no deben ser eliminadas
    std::vector<std::string> lineas;

    // Leer el archivo línea por línea
    std::string linea;
    while (std::getline(fichero, linea)) {
        // Verificar si la línea contiene ambas palabras
        if (linea.find(actividad) != std::string::npos && linea.find(dni) != std::string::npos) {
            // La línea contiene ambas palabras, no la almacenamos en el vector
            continue;
        }

        // Almacenar la línea en el vector
        lineas.push_back(linea);
    }

    // Cerrar el archivo de entrada
    fichero.close();

    // Abrir el archivo en modo escritura, eliminando el contenido existente
    std::ofstream archivoSalida("Preinscripciones.txt", std::ios::trunc);

    // Verificar si el archivo se abrió correctamente
    if (!archivoSalida.is_open()) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return false;
    }

    // Escribir las líneas no eliminadas en el archivo
    for (const auto& linea : lineas) {
        archivoSalida << linea << std::endl;
    }

    // Cerrar el archivo de salida
    archivoSalida.close();

    return true;
}

bool Director::VerCola(){

    std::ifstream actividades("Colas.txt");
    std::cout<<"==============================================================="<<std::endl;
    std::cout<<"MOSTRANDO LAS COLAS DE ESPERA:"<<std::endl;
    std::cout<<"==============================================================="<<std::endl;

    if(actividades.is_open()){

        std::string linea;
        while(std::getline(actividades, linea)){
            std::cout<< linea <<std::endl;
        }
        actividades.close();
    }

    else{
        std::cout<<"Error en la apertura del fichero\n";
        return false;
    }

    return true;
}