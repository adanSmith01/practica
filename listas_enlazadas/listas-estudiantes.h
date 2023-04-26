#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char* nombre;
    char* apellido;
    float nota;
}Alumno;

typedef struct alumNodo{
    Alumno estudiante;
    struct alumNodo* sig;
}alumNodo;

alumNodo* listaAlumnosVacia(){return NULL;}

alumNodo* crearAlumNodo(Alumno alum){
    alumNodo* nuevoAlum = (alumNodo*)malloc(sizeof(alumNodo));
    nuevoAlum->estudiante.apellido = (char*)malloc(strlen(alum.apellido) + 1);
    strcpy(nuevoAlum->estudiante.apellido, alum.apellido);
    nuevoAlum->estudiante.nombre = (char*)malloc(sizeof(alum.nombre) + 1);
    strcpy(nuevoAlum->estudiante.nombre, alum.nombre);
    nuevoAlum->estudiante.nota = alum.nota;
    nuevoAlum->sig = NULL;
    return nuevoAlum;
}

void insertarAlumNodo(alumNodo** listaAlum, alumNodo* nuevoAlum){
    nuevoAlum->sig = *listaAlum;
    *listaAlum = nuevoAlum;
}

void mostrarListaAlumnos(alumNodo* alum){
    alumNodo* auxAlum = alum;

    if(auxAlum){
        while(auxAlum){
            printf("\nApellido: %s\n", auxAlum->estudiante.apellido);
            printf("Nombre: %s\n", auxAlum->estudiante.nombre);
            printf("Nota final: %.2f\n", auxAlum->estudiante.nota);
            auxAlum = auxAlum->sig;
        }
    } else{
        printf("\nNo hay alumnos registrados.\n");
    }
}
