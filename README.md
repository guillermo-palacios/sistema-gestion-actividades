FUNCIONAMIENTO DE NUESTRO PROGRAMA:


Tendremos una clase Usuario Visitante inicialmente que se le pedirá un Nombre para crear su clase "Usuario", dependiente del tipo de login que haga el usuario tendrá un rol(Lo buscaremos en nuestros ficheros(Uno para los directores y otro para los usuarios registrados)),en el caso de que no inicie sesión unicamente podrá visualizar las actividades disponibles, es decir, se mostraría lo siguiente por pantalla:

=================================================
BIENVENIDO A …			                   
=================================================
1-. Iniciar sesión.                                               
2-. Registrarse.                                                  
3-. Visualizar actividades académicas.              
4-. Salir.                                                              
=================================================



1-. En el caso de elegir la opción 1, se le pedirá al usuario lo siguiente:
DNI
Contraseña

(Dichos datos recibidos servirán para buscar si existe en nuestro fichero “UsuariosRegistrados.txt” 
un usuario con ese DNI, en caso de no encontrarse se mostrará un error y se volverá a mostrar el menú de inicio.
La contraseña servirá para verificar el acceso al sistema con seguridad.
)



2-. En el caso de elegir la opción 2, se le pedirá al usuario lo siguiente:
Nombre completo.
DNI.
Dirección de correo.
Contraseña.
Contraseña director.

(Dichos datos se escribirán en el fichero “UsuariosRegistrados.txt” para que el usuario quede registrado 
y una vez inicie sesión se le mostrará el siguiente menú:


==================================================
BIENVENIDO !!				      
==================================================
1-. Preinscribirse a una actividad.                      
2-. Anular una preinscripción.		      
3-. Visualizar actividades disponibles.	      
4-. Cerrar sesión. 				      
==================================================


1-. En el caso de elegir la opción 1 se le pedirá al usuario lo siguiente:
Nombre completo
DNI
Correo electrónico
Dirección de domicilio
Nombre de la actividad
Fecha

Posteriormente, si los datos han sido introducidos con éxito se almacenarán en el fichero “Preinscripciones.txt”,
se actualizará la asistencia a ese curso y se le pedirá que realice el pago pidiendo lo siguiente:
Nº Tarjeta
Fecha de caducidad
Nombre del titular
CVC

Posteriormente se actualizará el saldo del Director académico correspondiente.


2-. En el caso de elegir la opción 2 se le pedirá al usuario que introduzca su DNI y el nombre de la actividad
a la que desea inscribirse, el programa lo buscará en el fichero “Preinscripciones.txt” y lo eliminará en el caso de que exista.

Posteriormente, se actualizará la asistencia de dicho curso.

3-. En el caso de elegir la opción 3 se imprimirá por pantalla el contenido del fichero “ActividadesDisponibles.txt”.


4-. En el caso de elegir la opción 4 se devolverá al usuario al menú de inicio

)


(Dichos datos se escribirán en el fichero “DirectoresAcadémicos.txt” en el caso de que la “contraseña_director” 
se haya escrito correctamente, pudiendo acceder así a las funcionalidades de un Director Académico quedando así registrado
y una vez inicie sesión se le mostrará el siguiente menú:


=================================================
BIENVENIDO DIRECTOR !!!			        
================================================= 
1-. Publicar una actividad.     		                    
2-. Modificar una actividad académica.	        
3-. Visualizar la asistencia a una actividad.	        
4-. Expulsar alumno de una actividad.	        
5-. Visualizar la cola de una actividad.	        
6-. Visualizar actividades disponibles.	        
7-. Cerrar sesión. 				        
=================================================

1-. En el caso de elegir la opción 1 se le pedirá al usuario que introduzca lo siguiente:
Nombre de la actividad
Fecha de inicio
Aforo máximo
Precio
Una vez introducidos los datos correctamente se guardarán los datos en el fichero “ActividadesDisponibles.txt”

2-. En el caso de elegir la opción 2 se le pedirá al usuario que introduzca el nombre de la actividad a modificar, 
si no se encuentra se notifica del error, en caso de que exista se le pedirán de nuevo los datos de dicha actividad, es decir:
Nombre de la actividad
Fecha de inicio
Aforo máximo
Precio
Y se guardan de nuevo en el fichero, eliminando los anteriores



3-. En el caso de elegir la opción 3 se le pedirá al usuario que introduzca el nombre de la actividad la cual quiere
ver su asistencia, si no existe se notifica del error, si existe se muestra por pantalla la asistencia a dicho curso(Se imprime el fichero ”Preinscripciones.txt”)

4-. En el caso de elegir la opción 4 se le pide al usuario que introduzca el DNI de la persona que quiere expulsar, 
si no existe se notifica del error, si existe se elimina dicho alumno del fichero “Preinscripciones.txt”.

5-. En el caso de elegir la opción 5 se imprimirá por pantalla la cola que tenemos en una actividad, almacenada 
en la variable private de la clase “Actividad”.

6-. En el caso de elegir la opción 6 se imprimirá por pantalla el contenido del fichero “ActividadesDisponibles.txt”.

7-. En el caso de elegir la opción 7 se devolverá al usuario al menú de inicio.

)

3-. En el caso de elegir la opción 3 se imprimirá por pantalla el contenido del fichero “ActividadesDisponibles.txt”.


4-. En el caso de elegir la opción 4 se cerrará el programa y mostrará por pantalla el siguiente mensaje:


=================================================
GRACIAS POR SU VISITA, NOS VEMOS PRONTO !!    
=================================================



