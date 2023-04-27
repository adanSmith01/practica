/*
Un profesor de Matemáticas necesita registrar a los alumnos de su curso. Para ello, te
ha pedido ayuda para que realices un programa que cumpla lo siguiente:
- Mostrar el listado de alumnos por apellido y nombre junto con la nota del primer parcial.
- Mostrar listas de alumnos aprobados y desaprobados. Para esto se considera aprobado si la nota es mayor o igual que 5.
- Consultar los datos de un alumno en particular y su estado con respecto al parcial. Buscarlo por su nombre completo.

Realiza un menú donde el usuario seleccione una de esas opcionesincluyendo la opción de salir.

Buena suerte, :)
*/

#include "listas-estudiantes.h"

int main(){
    alumNodo* listaAlumnos = listaAlumnosVacia();
    cargarAlumnos(&listaAlumnos);
    menuPrincipal(listaAlumnos);
    return 0;
}