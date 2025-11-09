#include "usuario-registrado.h"
#include<fstream>
#include<vector>
#include<regex>

bool EsDigito(char c) {
    return (c >= '0' && c <= '9');
}

bool EsLetraMayuscula(char c) {
    return (c >= 'A' && c <= 'Z');
}

bool EsIBANValido(const std::string& iban) {
    // Verificar la longitud mínima
    if (iban.length() < 4) {
        return false;
    }

    // Verificar que los primeros dos caracteres sean letras
    if (!EsLetraMayuscula(iban[0]) || !EsLetraMayuscula(iban[1])) {
        return false;
    }

    // Verificar que los siguientes dos caracteres sean dígitos
    if (!EsDigito(iban[2]) || !EsDigito(iban[3])) {
        return false;
    }

    // Obtener el código de país y su longitud
    std::string codigoPais = iban.substr(0, 2);
    int longitudCodigoPais = std::stoi(iban.substr(2, 2));

    // Verificar que la longitud del IBAN sea correcta
    if (iban.length() != 4 + longitudCodigoPais) {
        return false;
    }

    // Verificar que el IBAN contenga solo dígitos y letras
    std::regex formatoValido("[A-Z0-9]+");
    if (!std::regex_match(iban, formatoValido)) {
        return false;
    }

    // Realizar otras verificaciones según tus requisitos específicos

    // Aquí puedes agregar más validaciones, como la verificación del dígito de control

    // Si todas las verificaciones han pasado, el IBAN es válido
    return true;
}

bool compruebadni(std::string dni){
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

bool contieneDominio(std::string email) {
    size_t encontradoUco = email.find("@uco.es");
    size_t encontradoGmail = email.find("@gmail.com");
    
    return (encontradoUco != std::string::npos || encontradoGmail != std::string::npos);
}

bool esFechaValida(int dia, int mes, int anio) {
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

bool UsuarioRegistrado::Preinscribirse(std::string nombreActividad){

    std::string nombre, apellido, dni, email, direccion;
    int dia, mes, anio;

    std::cout<<"Introduzca su Nombre: "<<std::endl;
    std::cin>>nombre;

    std::cout<<"Introduzca su Apellido: "<<std::endl;
    std::cin>>apellido;

    std::cout<<"Introduzca su DNI: "<<std::endl;
    std::cin>>dni;

    if(!compruebadni(dni)){
        std::cout<<"Dni incorrecto"<<std::endl;
        return false;
    }

    std::cout<<"Introduzca su Fecha de Nacimiento 'DD MM YYYY': "<<std::endl;
    std::cin>>dia>>mes>>anio;

    if(!esFechaValida(dia,mes,anio)){
        std::cout<<"Introduce una fecha de nacimiento valida."<<std::endl;
        return false;
    }

    std::cout<<"Introduzca su email '@uco.es' o '@gmail.com': "<<std::endl;
    std::cin>>email;

    if(!contieneDominio(email)){
        std::cout<<"Introduzca un correo finalizado en @uco.es o en su defecto @gmail.com"<<std::endl;
        return false;
    }

    std::cin.ignore();
    std::cout<<"Introduzca su direccion de domicilio 'Ciudad Calle Numero': "<<std::endl;
    std::getline(std::cin, direccion);

    std::ifstream fichero("Preinscripciones.txt");

    if (fichero.is_open()) {
        std::string preinscripcion;

        while (std::getline(fichero, preinscripcion)) {
            size_t encontrado = preinscripcion.find(dni);
            size_t encontrado2 = preinscripcion.find(nombreActividad);

            if (encontrado != std::string::npos && encontrado2 != std::string::npos) {
                fichero.close();
                std::cout << "Ya estás preinscrito en esta actividad.\n";
                return false;
            }
        }

        fichero.close();  // Cierra el archivo después de leer todas las líneas

        std::string IBAN;
        std::cout<<"=============================================================="<<std::endl;

        std::cout<<"A continuacion se realizara el pago de dicha actividad:"<<std::endl;
        std::cout<<"Introduzca el IBAN de su cuenta bancaria: "<<std::endl;
        std::cin>>IBAN;
        
        if (EsIBANValido(IBAN)) {
            std::cout << "El IBAN es válido." << std::endl;
        } else {
            std::cout << "El IBAN no es válido." << std::endl;
        }
        
        std::cout<<"=============================================================="<<std::endl;

        std::cout<<"El pago correspondiente a dicha actividad sera solicitado a su cuenta bancaria proximamente. "<<std::endl;
        
        std::ofstream fichero_adicion("Preinscripciones.txt", std::ios::app);

        if (fichero_adicion.is_open()) {
            std::string nuevaPreinscripcion = nombreActividad + " " + nombre + " " + apellido + " " + dni + " " + std::to_string(dia) + "/" + std::to_string(mes) + "/" + std::to_string(anio) + " " + email + " " + direccion;

            fichero_adicion << nuevaPreinscripcion << std::endl;

            fichero_adicion.close();
        } else {
            std::cout << "Error al abrir el fichero para añadir datos.\n";
            return false;
        }
    } else {
        std::cout << "Error al abrir el fichero de preinscripciones.\n";
        return false;
    }


    return true;
}


bool UsuarioRegistrado::AnularPreinscripcion(std::string actividad, std::string dni){
    
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

    std::cout<<"============================================================================="<<std::endl;
    std::cout << "Preinscripcion anulada con exito." << std::endl;

    return true;
}