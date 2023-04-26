#include "listas-estudiantes.h"

int main(){
    alumNodo* listaAlumnos = listaAlumnosVacia();
    alumNodo* alumNuevo;
    Alumno aux;

    for(int i = 0; i < 3; i++){
        fflush(stdin);
        aux.apellido = (char*)malloc(50);
        aux.nombre = (char*)malloc(50);
        printf("\nIngrese el apellido y nombre del alumno %d: ", i + 1);
        printf("\nApellido: ");
        gets(aux.apellido);
        fflush(stdin);
        printf("Nombre: ");
        gets(aux.nombre);
        printf("Nota final: ");
        scanf("%f", &aux.nota);
        alumNuevo = crearAlumNodo(aux);
        insertarAlumNodo(&listaAlumnos, alumNuevo);
        free(aux.apellido);
        free(aux.nombre);
    }

    puts("\n=======LISTA DE ALUMNOS=====\n");
    mostrarListaAlumnos(listaAlumnos);

    return 0;
}