#include<iostream>
#include"usuario.h"
#include"usuario-registrado.h"
#include"director.h"

//FUNCIONES


bool CompruebaDni(std::string dni){
    int tm_dni=dni.size();
    std::string letras;

    letras="TRWAGMYFPDXBNJZSQVHLCKE";
    std::string num_dni;
    if(tm_dni!=9) {
        return false;
    }
    for(int i=0;i<8; i++){
        if(isdigit(dni[i])){num_dni+=dni[i];}
        else {return false;} 
    }

    int numero_dni=stoi(num_dni);

    char letra=letras[numero_dni % 23]; 
    if(dni[8]==letra||dni[8]==tolower(letra)){}
    else{
        return false; 
    }

    return true;
}

bool ContieneDominio(std::string email) {
    size_t encontradoUco = email.find("@uco.es");
    size_t encontradoGmail = email.find("@gmail.com");
    
    return (encontradoUco != std::string::npos || encontradoGmail != std::string::npos);
}

bool EsFechaValida(int dia, int mes, int anio) {
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


//FUNCIONES

int main(){

    int opcion, modo, opcion2, dia, mes, anio, asistencia;
    std::string nombre, apellido, dni, contrasena, email, contrasenaDirector;
    std::string nombreActividad;

    std::cout<<"Introduzca su nombre y su primer apellido para poder acceder al sistema: "<<std::endl;
    std::cin>>nombre;
    std::cin>>apellido;

    Usuario u(nombre, apellido);
    //UsuarioRegistrado ur(dni, nombre, apellido, contrasena, email, dia, mes, anio);
    //Director d(dni, nombre, apellido, contrasenaDirector, email, contrasena, dia, mes, anio);

    do{
    
    
        std::cout<<"=============================================================="<<std::endl;
        std::cout<<" BIENVENIDO A NUESTRO SISTEMA DE GESTION DE ACTIVIDADES 404  "<<std::endl;
        std::cout<<"=============================================================="<<std::endl;
        std::cout<<"1-. Iniciar Sesion.  "<<std::endl;
        std::cout<<"2-. Registrarse.  "<<std::endl;
        std::cout<<"3-. Visualizar actividades academicas.  "<<std::endl;
        std::cout<<"4-. Salir.  "<<std::endl;
        std::cout<<"=============================================================="<<std::endl;
        std::cin>>opcion;

        switch (opcion)
        {
        case 1: // INICIAR SESIÓN

            modo=0;
            
            while(modo!=1 && modo!=2){ //COMPROBAMOS QUE SE ELIJA UN MODO VALIDO DE INICIO

                std::cout<<"=============================================================="<<std::endl;
                std::cout<<"1-. Acceder como estudiante."<<std::endl;
                std::cout<<"2-. Acceder como director."<<std::endl;
                std::cout<<"Seleccione el modo:"<<std::endl;
                std::cout<<"=============================================================="<<std::endl;
                std::cin>>modo;

                if(modo!=1 && modo!=2){
                    std::cout<<"Seleccione un modo valido:"<<std::endl;
                }
            }

            std::cout<<"Introduzca su DNI: "<<std::endl;
            std::cin>>dni;
            
            std::cout<<"Introduzca su Contrasena: "<<std::endl;
            std::cin>>contrasena;


            if(modo==2){ // DIRECTOR
                
                std::cout<<"Introduzca su Contrasena de Director: "<<std::endl;
                std::cin>>contrasenaDirector;

                Director d(dni, nombre, apellido, contrasena, contrasenaDirector, email, dia, mes, anio); // Asumimos que email/fecha no se usan

                if(u.IniciarSesion(dni, contrasena, contrasenaDirector)){

                    do{
                        std::cout<<"========================================================================"<<std::endl;
                        std::cout<<" BIENVENIDO DIRECTOR !!!"<<std::endl;
                        std::cout<<"======================================================================== "<<std::endl;
                        std::cout<<"1-. Publicar una actividad."<<std::endl;
                        std::cout<<"2-. Modificar una actividad académica."<<std::endl;
                        std::cout<<"3-. Visualizar la asistencia a una actividad."<<std::endl;
                        std::cout<<"4-. Expulsar alumno de una actividad."<<std::endl;
                        std::cout<<"5-. Visualizar la cola de una actividad."<<std::endl;
                        std::cout<<"6-. Visualizar actividades disponibles."<<std::endl;
                        std::cout<<"7-. Cerrar sesión."<<std::endl;
                        std::cout<<"========================================================================"<<std::endl;
                        std::cin>>opcion2;

                        switch (opcion2)
                        {
                        case 1:

                            if(!d.PublicarActividad()){
                                std::cout<<"Se ha producido un error al publicar la actividad. "<<std::endl;
                            }
                            else{
                                std::cout<<"La actividad ha sido publicada con exito. "<<std::endl;    
                            }

                            break;
                        
                        case 2:

                            std::cin.ignore();
                            std::cout<<"Introduce el nombre de la actividad que desea modificar"<<std::endl;
                            std::getline(std::cin,nombreActividad);

                            if(!d.ModificarActividad(nombreActividad)){
                                std::cout<<"Se ha producido un error al modificar la actividad. "<<std::endl;
                            }
                            else{
                                std::cout<<"La actividad ha sido modificada con exito. "<<std::endl;    
                            }

                            break;
                        
                        case 3:

                            std::cin.ignore();
                            std::cout<<"Introduce el nombre de la actividad que desea ver su asistencia"<<std::endl;
                            std::getline(std::cin,nombreActividad);

                            asistencia = d.VerAsistencia(nombreActividad);

                            if(asistencia == -1){
                                std::cout<<"Se ha producido un error al mostrar la asistencia de su actividad. "<<std::endl;
                            }
                            else{
                                std::cout<<"La asistencia actual de su actividad es:"<<asistencia<<std::endl;    
                            }

                            break;
                        
                        case 4:
                            
                            std::cout<<"Introduce el dni del alumno que desea expulsar"<<std::endl;
                            std::cin>>dni;

                            std::cin.ignore();
                            std::cout<<"Introduce el nombre de la actividad a la que pertenece"<<std::endl;
                            std::getline(std::cin,nombreActividad);

                            if(!d.ExpulsarAlumno(nombreActividad, dni)){
                                std::cout<<"Se ha producido un error al expulsar el alumno de su actividad. "<<std::endl;
                            }
                            else{
                                std::cout<<"El alumno ha sido expulsado con exito. "<<std::endl;    
                            }
                            
                            break;
                        
                        case 5:
                            
                            if(!d.VerCola()){
                                std::cout<<"Se ha producido un error al mostrar la cola de su actividad. "<<std::endl;
                            }
                            else{
                                std::cout<<"La cola ha sido mostrada con exito. "<<std::endl;    
                            }
                            
                            break;
                        
                        case 6:
                            
                            if(!d.VisualizarActividades()){
                                std::cout<<"Se ha producido un error al mostrar las actividades. "<<std::endl;
                            }
                            
                            break;
                        
                        case 7:

                            std::cout<<"=============================================================="<<std::endl;
                            std::cout<<"CERRANDO SESION."<<std::endl;
                            std::cout<<"=============================================================="<<std::endl;

                            break;

                        default:
                            std::cout<<"Seleccione una opcion valida."<<std::endl;
                            break;
                        }
                    
                    
                    }while(opcion2 != 7);


                }
                else{
                    std::cout<<"=============================================================="<<std::endl;
                    std::cout<<"Parece ser que no ha iniciado sesion correctamente como director"<<std::endl;
                    std::cout<<"Intentelo de nuevo o registrese si aun no lo ha hecho"<<std::endl;
                    std::cout<<"=============================================================="<<std::endl;
                }

            }
            else{ // ESTUDIANTE

                contrasenaDirector="empty";

                if(u.IniciarSesion(dni, contrasena, contrasenaDirector)){

                    UsuarioRegistrado ur(dni, nombre, apellido, contrasena, email, dia, mes, anio);    

                    do{
                        
                        std::cout<<"=============================================================="<<std::endl;
                        std::cout<<"  BIENVENIDO A NUESTRO SISTEMA DE GESTION DE ACTIVIDADES    "<<std::endl;
                        std::cout<<"=============================================================="<<std::endl;
                        std::cout<<"1-. Visualizar actividades disponibles.  "<<std::endl;
                        std::cout<<"2-. Preinscribirse a una actividad.  "<<std::endl;
                        std::cout<<"3-. Anular una preinscripción.  "<<std::endl;
                        std::cout<<"4-. Cerrar sesión.  "<<std::endl;
                        std::cout<<"=============================================================="<<std::endl;
                        std::cin>>opcion2;

                        switch (opcion2)
                        {
                        case 1:

                            if(!ur.VisualizarActividades()){
                                std::cout<<"Error al visualizar las actividades disponibles"<<std::endl;
                            }

                            break;
                        
                        case 2:

                            std::cin.ignore();

                            std::cout<<"Introduzca el nombre de la actividad a la que desea preinscribirse: "<<std::endl;
                            std::getline(std::cin,nombreActividad);


                            if(!ur.Preinscribirse(nombreActividad)){
                                std::cout<<"Error al realizar la preinscripcion"<<std::endl;
                                return false;
                            }

                            break;
                        
                        case 3:
                        
                            std::cin.ignore();
                            
                            std::cout<<"Introduzca el nombre de la actividad a la que se preinscribio: "<<std::endl;
                            std::getline(std::cin,nombreActividad);

                            std::cout<<"Introduzca el dni que introdujo en su preinscripcion: "<<std::endl;
                            std::cin>>dni;
                         

                            if(!ur.AnularPreinscripcion(nombreActividad, dni)){
                                std::cout<<"Error al anular la preinscripcion"<<std::endl;
                                return false;
                            }

                            break;
                        
                        case 4:

                            std::cout<<"=============================================================="<<std::endl;
                            std::cout<<"CERRANDO SESION."<<std::endl;
                            std::cout<<"=============================================================="<<std::endl;

                            break;

                        default:
                            std::cout<<"Seleccione una opcion valida."<<std::endl;
                        }
                    
                    }while(opcion2 != 4);

                }
                else{

                    std::cout<<"=============================================================="<<std::endl;
                    std::cout<<"Parece ser que no ha iniciado sesion correctamente como usuario"<<std::endl;
                    std::cout<<"Intentelo de nuevo o registrese si aun no lo ha hecho"<<std::endl;
                    std::cout<<"=============================================================="<<std::endl;}
            }

            break;
        case 2: // REGISTRARSE

            modo=0;

            while(modo!=1 && modo!=2){ //COMPROBAMOS QUE SE ELIJA UN MODO VALIDO DE INICIO

                std::cout<<"=============================================================="<<std::endl;
                std::cout<<"1-. Acceder como estudiante."<<std::endl;
                std::cout<<"2-. Acceder como director."<<std::endl;
                std::cout<<"Seleccione el modo:"<<std::endl;
                std::cout<<"=============================================================="<<std::endl;
                std::cin>>modo;

                if(modo!=1 && modo!=2){
                    std::cout<<"Seleccione un modo valido."<<std::endl;
                }
            }

            std::cout<<"Introduzca su DNI: "<<std::endl;
            std::cin>>dni;

            if(!CompruebaDni(dni)){
                std::cout<<"Dni incorrecto"<<std::endl;
                break;
            }

            std::cout<<"Introduzca su Fecha de Nacimiento 'DD MM YYYY': "<<std::endl;
            std::cin>>dia>>mes>>anio;

            if(!EsFechaValida(dia,mes,anio)){
                std::cout<<"Introduce una fecha de nacimiento valida."<<std::endl;
                break;
            }

            std::cout<<"Introduzca su email: "<<std::endl;
            std::cin>>email;

            if(!ContieneDominio(email)){
                std::cout<<"Introduzca un correo finalizado en @uco.es o en su defecto @gmail.com"<<std::endl;
                break;
            }
            
            std::cout<<"Introduzca su Contrasena: "<<std::endl;
            std::cin>>contrasena;


            if(modo==2){ // DIRECTOR
                
                std::cout<<"Introduzca su Contrasena de Director: "<<std::endl;
                std::cin>>contrasenaDirector;

                if(u.Registrarse(nombre, apellido, dni, dia, mes, anio, email, contrasena, contrasenaDirector)){
                    
                    Director d(dni, nombre, apellido, contrasena, contrasenaDirector, email, dia, mes, anio);

                    do{
                        std::cout<<"========================================================================"<<std::endl;
                        std::cout<<" BIENVENIDO DIRECTOR !!!"<<std::endl;
                        std::cout<<"======================================================================== "<<std::endl;
                        std::cout<<"1-. Publicar una actividad."<<std::endl;
                        std::cout<<"2-. Modificar una actividad académica."<<std::endl;
                        std::cout<<"3-. Visualizar la asistencia a una actividad."<<std::endl;
                        std::cout<<"4-. Expulsar alumno de una actividad."<<std::endl;
                        std::cout<<"5-. Visualizar la cola de una actividad."<<std::endl;
                        std::cout<<"6-. Visualizar actividades disponibles."<<std::endl;
                        std::cout<<"7-. Cerrar sesión."<<std::endl;
                        std::cout<<"========================================================================"<<std::endl;
                        std::cin>>opcion2;

                        switch (opcion2)
                        {
                        case 1:

                            if(!d.PublicarActividad()){
                                std::cout<<"Se ha producido un error al publicar la actividad. "<<std::endl;
                            }
                            else{
                                std::cout<<"La actividad ha sido publicada con exito. "<<std::endl;    
                            }

                            break;
                        
                        case 2:

                            std::cin.ignore();
                            std::cout<<"Introduce el nombre de la actividad que desea modificar"<<std::endl;
                            std::getline(std::cin,nombreActividad);
                        
                            if(!d.ModificarActividad(nombreActividad)){
                                std::cout<<"Se ha producido un error al modificar la actividad. "<<std::endl;
                            }
                            else{
                                std::cout<<"La actividad ha sido modificada con exito. "<<std::endl;    
                            }

                            break;
                        
                        case 3:

                            std::cin.ignore();
                            std::cout<<"Introduce el nombre de la actividad que desea modificar"<<std::endl;
                            std::getline(std::cin,nombreActividad);
                            
                            asistencia = d.VerAsistencia(nombreActividad);

                            if(asistencia == -1){
                                std::cout<<"Se ha producido un error al mostrar la asistencia de su actividad. "<<std::endl;
                            }
                            else{
                                std::cout<<"La asistencia actual de su actividad es:"<<asistencia<<std::endl;    
                            }

                            break;
                        
                        case 4:

                            std::cout<<"Introduce el dni del alumno que desea expulsar"<<std::endl;
                            std::cin>>dni;

                            std::cin.ignore();
                            std::cout<<"Introduce el nombre de la actividad que desea modificar"<<std::endl;
                            std::getline(std::cin,nombreActividad);
                            
                            if(!d.ExpulsarAlumno(nombreActividad, dni)){
                                std::cout<<"Se ha producido un error al expulsar el alumno de su actividad. "<<std::endl;
                            }
                            else{
                                std::cout<<"El alumno ha sido expulsado con exito. "<<std::endl;    
                            }
                            
                            break;
                        
                        case 5:
                            
                            if(!d.VerCola()){
                                std::cout<<"Se ha producido un error al mostrar la cola de su actividad. "<<std::endl;
                            }
                            else{
                                std::cout<<"La cola ha sido mostrada con exito. "<<std::endl;    
                            }
                            
                            break;
                        
                        case 6:
                            
                            if(!d.VisualizarActividades()){
                                std::cout<<"Se ha producido un error al mostrar las actividades. "<<std::endl;
                            }
                            else{
                                std::cout<<"Las actividades han sido mostradas con exito. "<<std::endl;    
                            }
                            
                            break;
                        
                        case 7:

                            std::cout<<"=============================================================="<<std::endl;
                            std::cout<<"CERRANDO SESION."<<std::endl;
                            std::cout<<"=============================================================="<<std::endl;

                            break;

                        default:
                            std::cout<<"Seleccione una opcion valida."<<std::endl;
                            break;
                        }
                    
                    
                    
                    
                    }while(opcion2 != 7);
                }
                else{
                    std::cout<<"=============================================================="<<std::endl;
                    std::cout<<"Parece ser que no se ha registrado correctamente como director."<<std::endl;
                    std::cout<<"Intentelo de nuevo si asi lo desea."<<std::endl;
                    std::cout<<"=============================================================="<<std::endl;
                }

            }
            else{ // ESTUDIANTE

                contrasenaDirector="empty";

                if(u.Registrarse(nombre, apellido, dni, dia, mes, anio, email, contrasena, contrasenaDirector)){
                    
                    UsuarioRegistrado ur(dni, nombre, apellido, contrasena, email, dia, mes, anio);

                    do{
                        
                        std::cout<<"=============================================================="<<std::endl;
                        std::cout<<"  BIENVENIDO A NUESTRO SISTEMA DE GESTION DE ACTIVIDADES    "<<std::endl;
                        std::cout<<"=============================================================="<<std::endl;
                        std::cout<<"1-. Visualizar actividades disponibles.  "<<std::endl;
                        std::cout<<"2-. Preinscribirse a una actividad.  "<<std::endl;
                        std::cout<<"3-. Anular una preinscripción.  "<<std::endl;
                        std::cout<<"4-. Cerrar sesión.  "<<std::endl;
                        std::cout<<"=============================================================="<<std::endl;
                        std::cin>>opcion2;

                        switch (opcion2)
                        {
                        case 1:

                            if(!ur.VisualizarActividades()){
                                std::cout<<"Error al visualizar las actividades disponibles"<<std::endl;
                            }

                            break;
                        
                        case 2:

                            std::cin.ignore();
                            std::cout<<"Introduzca el nombre de la actividad a la que desea preinscribirse: "<<std::endl;
                            std::getline(std::cin,nombreActividad);


                            if(!ur.Preinscribirse(nombreActividad)){
                                std::cout<<"Error al realizar la preinscripcion"<<std::endl;
                                return false;
                            }

                            break;
                        
                        case 3:
                        
                            std::cin.ignore();
                            std::cout<<"Introduzca el nombre de la actividad a la que se preinscribio: "<<std::endl;
                            std::getline(std::cin,nombreActividad);

                            std::cout<<"Introduzca el dni que introdujo en su preinscripcion: "<<std::endl;
                            std::cin>>dni;
                         

                            if(!ur.AnularPreinscripcion(nombreActividad, dni)){
                                std::cout<<"Error al anular la preinscripcion"<<std::endl;
                                return false;
                            }

                            break;
                        
                        case 4:

                            std::cout<<"=============================================================="<<std::endl;
                            std::cout<<"CERRANDO SESION."<<std::endl;
                            std::cout<<"=============================================================="<<std::endl;

                            break;

                        default:
                            std::cout<<"Seleccione una opcion valida."<<std::endl;
                        }
                    
                    }while(opcion2 != 4);
                }
                else{

                    std::cout<<"=============================================================="<<std::endl;
                    std::cout<<"Parece ser que no se ha registrado correctamente como usuario."<<std::endl;
                    std::cout<<"Intentelo de nuevo si asi lo desea."<<std::endl;
                    std::cout<<"=============================================================="<<std::endl;
                }
            }
 
            break;
        case 3:

            if(!u.VisualizarActividades()){

                std::cout<<"Se ha producido un error al intentar visualizar las actividades"<<std::endl;
            
            }

            break;
        case 4:

            std::cout<<"=============================================================="<<std::endl;
            std::cout<<"GRACIAS POR SU VISITA, NOS VEMOS PRONTO !!    "<<std::endl;
            std::cout<<"=============================================================="<<std::endl;

            break;
        default:
            std::cout<<"Seleccione una de las 4 opciones mostradas"<<std::endl;
        }
    
    }while(opcion!=4);



    return 0;
}



