#include "SistemaGestion.h"
#include <iostream>

int main() {
    
    // 1. Creamos el "cerebro".
    // El constructor de SistemaGestion se llamará automáticamente y cargará los datos de los ficheros.
    SistemaGestion sistema;

    // 2. Ejecutamos el programa.
    // Llamamos a la función que tendrá el bucle principal y los menús.
    sistema.Run();

    // 3. Fin.
    // Al terminar main, se llama al destructor de 'sistema' y guardará todos los datos en los ficheros.
    
    return 0;
}