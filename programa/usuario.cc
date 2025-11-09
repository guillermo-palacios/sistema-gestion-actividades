#include "usuario.h"
#include <fstream>
#include <sstream>
#include <vector>

/*
bool Usuario::IniciarSesion(std::string dni, std::string contrasena, std::string contrasenaDirector){
    
    // Verificación de la contraseña del director
    if (contrasenaDirector != "986532" && contrasenaDirector != "empty") {
        std::cout << "Introduce una contraseña de director válida." << std::endl;
        return false;
    }

    // Verificación del archivo de usuarios
    if (contrasenaDirector == "empty") { // INICIO SESIÓN USUARIO
        std::ifstream fichero("UsuariosRegistrados.txt");
        if (!fichero.is_open()) {
            std::cout << "Error en la apertura del fichero" << std::endl;
            return false;
        }

        std::string linea;
        bool encontrado = false;

        while (std::getline(fichero, linea)) {
            std::stringstream ss(linea);
            std::string token;
            std::vector<std::string> tokens;
            while(ss >> token){
                tokens.push_back(token);
            }

            // Asumiendo el formato de Registrarse:
            // [0]Nombre [1]Apellido [2]DNI [3]Fecha [4]Email [5]Contrasena
            if (tokens.size() >= 6) {
                std::string dniFichero = tokens[2];
                std::string contrasenaFichero = tokens[5];

                if (dniFichero == dni && contrasenaFichero == contrasena) {
                    encontrado = true;
                    break;
                }
            }
        }
        fichero.close();

        if (encontrado) {
            return true;
        } else {
            std::cout << "Error al iniciar sesión como usuario (DNI o contraseña incorrectos)" << std::endl;
            return false;
        }
    } else { // INICIO SESIÓN DIRECTOR
        std::ifstream ficheroDir("Directores.txt");
        if (!ficheroDir.is_open()) {
            std::cout << "Error en la apertura del fichero" << std::endl;
            return false;
        }

        std::string linea;
        bool encontrado = false;

        while (std::getline(ficheroDir, linea)) {
             std::stringstream ss(linea);
            std::string token;
            std::vector<std::string> tokens;
            while(ss >> token){
                tokens.push_back(token);
            }

            // Asumiendo el formato de Registrarse:
            // [0]Nombre [1]Apellido [2]DNI [3]Fecha [4]Email [5]Contrasena [6]ContrasenaDir
            if (tokens.size() >= 7) {
                std::string dniFichero = tokens[2];
                std::string contrasenaFichero = tokens[5];
                // ¡Añade también la comprobación de la pass de director!
                std::string contrasenaDirFichero = tokens[6]; 

                if (dniFichero == dni && contrasenaFichero == contrasena && contrasenaDirFichero == contrasenaDirector) {
                    encontrado = true; // <-- BUG CORREGIDO (antes ponía false)
                    break;
                }
            }
        }
        ficheroDir.close();

        if (encontrado) { // <-- BUG CORREGIDO (antes ponía !encontrado)
            return true;
        } else {
            std::cout << "Error al iniciar sesión como director (Datos incorrectos)" << std::endl;
            return false;
        }
    }
}


bool Usuario::Registrarse(std::string nombre, std::string apellido, std::string dni, int dia, int mes, int anio, std::string email, std::string contrasena, std::string contrasenaDirector){

    
    if(contrasenaDirector != "986532" && contrasenaDirector != "empty"){
        return false;
    }

    //REGISTRAMOS A LOS USUARIOS

    if(contrasenaDirector == "empty"){

        //COMPROBAMOS LA EXISTENCIA DE UNA PERSONA CON ESE DNI 

    std::ifstream comprobarExistencia("UsuariosRegistrados.txt");
        
    if(comprobarExistencia.is_open()){

        // Bucle para leer el archivo línea por línea

        std::string usuario;
        
        while (std::getline(comprobarExistencia, usuario)) {

            // Busca la cadena dentro de la línea

            size_t encontrado = usuario.find(dni);

            // Si se encuentra la cadena, muestra la posición en la línea

            if (encontrado == std::string::npos) {
                continue;
            }
            else{
                std::cout<<"Ya existe un usuario con ese dni"<<std::endl;
                return false;
            }
        }
        comprobarExistencia.close();
    }
    else{
        std::cout<<"Error en la apertura del fichero\n";
        return false;
    }
                                                           
    //COMPROBAMOS SI LA CONTRASEÑA DEL DIRECTOR ES VALIDA 
    

        std::ofstream fichero("UsuariosRegistrados.txt", std::ios::app); 
    
        if(fichero.is_open()){

            std::string nuevoUsuario = nombre + " " + apellido + " " + dni + " " + std::to_string(dia) + "/" + std::to_string(mes) + "/" + std::to_string(anio) + " " + email + " " + contrasena;  

            fichero<< nuevoUsuario <<std::endl;
            
            fichero.close();
        }
        else{
            std::cout<<"Error en la apertura del fichero UsuariosRegistrados.txt\n";
            return false;
        }
    }

    //REGISTRAMOS A LOS DIRECTORES

    else{

        //COMPROBAMOS LA EXISTENCIA DE UNA PERSONA CON ESE DNI 

    std::ifstream comprobarExistencia("Directores.txt");
        
    if(comprobarExistencia.is_open()){

        // Bucle para leer el archivo línea por línea

        std::string usuario;
        
        while (std::getline(comprobarExistencia, usuario)) {

            // Busca la cadena dentro de la línea

            size_t encontrado = usuario.find(dni);

            // Si se encuentra la cadena, muestra la posición en la línea

            if (encontrado == std::string::npos) {
                continue;
            }
            else{
                std::cout<<"Ya existe un usuario con ese dni"<<std::endl;
                return false;
            }
        }
        comprobarExistencia.close();
    }
    else{
        std::cout<<"Error en la apertura del fichero\n";
        return false;
    }
                                                           
    //COMPROBAMOS SI LA CONTRASEÑA DEL DIRECTOR ES VALIDA 
    

        std::ofstream fichero("Directores.txt", std::ios::app); 
    
        if(fichero.is_open()){

            std::string nuevoUsuario= nombre + " " + apellido + " " + dni + " " + std::to_string(dia) + "/" + std::to_string(mes) + "/" + std::to_string(anio) + " " + email + " " + contrasena + " " + contrasenaDirector;  

            fichero<< nuevoUsuario <<std::endl;
            
            fichero.close();
        
        }
        else{
            std::cout<<"Error en la apertura del fichero Directores.txt\n";
            return false;
        }
    }
        
    return true;
}


bool Usuario::VisualizarActividades(){

    std::ifstream actividades("Actividades.txt");
    std::cout<<"==============================================================="<<std::endl;
    std::cout<<"MOSTRANDO LAS ACTIVIDADES DISPONIBLES ACTUALMENTE:"<<std::endl;
    std::cout<<"==============================================================="<<std::endl;

    if(actividades.is_open()){

        std::string linea;
        while(std::getline(actividades, linea)){
            std::cout<< linea <<"€"<<std::endl;
        }
        actividades.close();
    }

    else{
        std::cout<<"Error en la apertura del fichero\n";
        return false;
    }

    return true;
}*/