#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *nombreCompleto;
    float notaPrimParcial;
    float notaSegParcial;
    float promedio;
}alumno;

alumno datosAlumno();
void cargarDatos(alumno **listaAprobados, alumno **listaDesaprobados, int cant);
void mostrarAlumnos(alumno **listaAlumnos, int cant);

int main(){
    int cantAlumnos;
    printf("Ingrese el numero de alumnos: ");
    scanf("%d", &cantAlumnos);

    alumno **listaAprobados = (alumno **)malloc(sizeof(alumno *)*cantAlumnos);
    alumno **listaDesaprobados = (alumno **)malloc(sizeof(alumno *)*cantAlumnos);

    //Inicialización de los arreglos
    for(int i = 0; i < cantAlumnos; i++){
        listaAprobados[i] = NULL;
        listaDesaprobados[i] = NULL;
    }

    cargarDatos(listaAprobados, listaDesaprobados, cantAlumnos);
    puts("\n===========LISTA DE ALUMNOS APROBADOS============\n");
    mostrarAlumnos(listaAprobados, cantAlumnos);
    puts("\n===========LISTA DE ALUMNOS DESAPROBADOS============\n");
    mostrarAlumnos(listaDesaprobados, cantAlumnos);

    return 0;
}

alumno datosAlumno(){
    alumno alum;
    fflush(stdin);
    alum.nombreCompleto = (char *)malloc(50);
    printf("\nNombre completo: ");
    gets(alum.nombreCompleto);
    printf("Nota primer parcial: ");
    scanf("%f", &alum.notaPrimParcial);
    printf("Nota segundo parcial: ");
    scanf("%f", &alum.notaSegParcial);
    alum.promedio = (float)(alum.notaPrimParcial + alum.notaSegParcial) / 2;

    return alum;
}

void cargarDatos(alumno **listaAprobados, alumno **listaDesaprobados, int cant){
    alumno aux;
    for(int i = 0; i < cant; i++){
        printf("\n***********ALUMNO 0%d**********\n", i + 1);
        aux = datosAlumno();
        if(aux.promedio < 7){
            listaDesaprobados[i] = (alumno *)malloc(sizeof(alumno));
            listaDesaprobados[i]->nombreCompleto = (char *)malloc(strlen(aux.nombreCompleto) + 1);
            strcpy(listaDesaprobados[i]->nombreCompleto, aux.nombreCompleto);
            listaDesaprobados[i]->notaPrimParcial = aux.notaPrimParcial;
            listaDesaprobados[i]->notaSegParcial = aux.notaSegParcial;
            listaDesaprobados[i]->promedio = aux.promedio;
        } else{
            listaAprobados[i] = (alumno *)malloc(sizeof(alumno));
            listaAprobados[i]->nombreCompleto = (char *)malloc(strlen(aux.nombreCompleto) + 1);
            strcpy(listaAprobados[i]->nombreCompleto, aux.nombreCompleto);
            listaAprobados[i]->notaPrimParcial = aux.notaPrimParcial;
            listaAprobados[i]->notaSegParcial = aux.notaSegParcial;
            listaAprobados[i]->promedio = aux.promedio;
        }
        free(aux.nombreCompleto);
    }
}

void mostrarAlumnos(alumno **listaAlumnos, int cant){
    for(int i = 0; i < cant; i++){
        if(listaAlumnos[i]){
            printf("- %s  PROMEDIO: %.2f\n", listaAlumnos[i]->nombreCompleto, listaAlumnos[i]->promedio);
        }
    }
}