#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char* nombre;
    char* apellido;
    float nota;
}Alumno;

typedef struct alumNodo{
    Alumno datos;
    struct alumNodo* sig;
}alumNodo;

alumNodo* listaAlumnosVacia(){return NULL;}

alumNodo* crearAlumNodo(Alumno regAlum){
    alumNodo* alumno = (alumNodo*)malloc(sizeof(alumNodo));
    alumno->datos.apellido = (char*)malloc(strlen(regAlum.apellido) + 1);
    strcpy(alumno->datos.apellido, regAlum.apellido);
    alumno->datos.nombre = (char*)malloc(sizeof(regAlum.nombre) + 1);
    strcpy(alumno->datos.nombre, regAlum.nombre);
    alumno->datos.nota = regAlum.nota;
    alumno->sig = NULL;
    return alumno;
}

void insertarAlumNodo(alumNodo** listaAlum, alumNodo* alumno){
    alumno->sig = *listaAlum;
    *listaAlum = alumno;
}

void cargarAlumnos(alumNodo** listaAlumnos){
    int registrar;
    Alumno aux;
    alumNodo* registrarAlumno;
    puts("\n=====BIENVENIDO PROFESOR=====\n");
    do{
        puts("\n=====DATOS DEL ALUMNO/A====\n");
        fflush(stdin);
        printf("Apellido: ");
        aux.apellido = (char*)malloc(50);
        gets(aux.apellido);
        printf("Nombre: ");
        fflush(stdin);
        aux.nombre = (char*)malloc(50);
        gets(aux.nombre);
        printf("Nota del primer parcial: ");
        scanf("%f", &aux.nota);
        registrarAlumno = crearAlumNodo(aux);
        insertarAlumNodo(listaAlumnos, registrarAlumno);
        free(aux.apellido);
        free(aux.nombre);
        printf("\nQuiere ingresar los datos de otro alumno/a? Si (1) / No (0): ");
        scanf("%d", &registrar);
    }while(registrar);
}

void mostrarAlumnosAprobados(alumNodo* listaAlumnos){
    alumNodo* auxAlum = listaAlumnos;
    puts("\n=======LISTA DE ALUMNOS APROBADOS=======\n");
    while(auxAlum){
        if(auxAlum->datos.nota >= 5){
            printf("- %s, %s\n", auxAlum->datos.apellido, auxAlum->datos.nombre);
        }
        auxAlum = auxAlum->sig;
    }
}

void mostrarAlumnosDesaprobados(alumNodo* listaAlumnos){
    alumNodo* auxAlum = listaAlumnos;
    puts("\n=======LISTA DE ALUMNOS DESAPROBADOS=======\n");
    while(auxAlum){
        if(auxAlum->datos.nota < 5){
            printf("- %s, %s\n", auxAlum->datos.apellido, auxAlum->datos.nombre);
        }
        auxAlum = auxAlum->sig;
    }
}

void consultarDatosAlumno(alumNodo* listaAlumnos, char* apellidoAlum, char* nombreAlum){
    alumNodo* auxAlum = listaAlumnos;

    while(auxAlum && (strcmp(apellidoAlum, auxAlum->datos.apellido) != 0 || strcmp(nombreAlum, auxAlum->datos.nombre) != 0)){
        auxAlum = auxAlum->sig;
    }

    if(auxAlum == NULL){
        printf("\nNo se registró al alumno de apellido y nombre ingresados\n");
    } else{
        puts("\n=========DATOS DEL ALUMNO========\n");
        printf("\nApellido y Nombre: %s, %s\n", auxAlum->datos.apellido, auxAlum->datos.nombre);
        printf("Nota del primer parcial: %.2f\n", auxAlum->datos.nota);
        if(auxAlum->datos.nota >= 5){
            printf("Estado: Aprobado\n");
        }else{
            printf("Estado: Desaprobado\n");
        }
    }
}

void mostrarListaAlumnos(alumNodo* alum){
    alumNodo* auxAlum = alum;
    puts("\n===========LISTA DE ALUMNOS===========\n");
    if(auxAlum){
        while(auxAlum){
            printf("\nApellido: %s\n", auxAlum->datos.apellido);
            printf("Nombre: %s\n", auxAlum->datos.nombre);
            printf("Nota final: %.2f\n", auxAlum->datos.nota);
            auxAlum = auxAlum->sig;
        }
    } else{
        printf("\nNo hay alumnos registrados\n");
    }
}

void menuPrincipal(alumNodo* listaAlumnos){
    int opcion;
    char* apellidoAlumno;
    char* nombreAlumno;
    do{
        printf("\n*********************MENU PRINCIPAL*************************\n");
        puts("\n1- Mostrar la lista de alumnos que rindieron el parcial y sus notas");
        puts("2- Mostrar lista de alumnos aprobados y desaprobados");
        puts("3- Consultar los datos de un alumno y su estado respecto al parcial");
        puts("4- Salir");
        printf("\nElija la opcion: ");
        scanf("%d", &opcion);

        if(opcion == 1){
            mostrarListaAlumnos(listaAlumnos);
        } else{
            if(opcion == 2){
                mostrarAlumnosAprobados(listaAlumnos);
                mostrarAlumnosDesaprobados(listaAlumnos);
            } else{
                if(opcion == 3){
                    fflush(stdin);
                    apellidoAlumno = (char*)malloc(50);
                    nombreAlumno = (char*)malloc(50);
                    puts("\nIndique los datos del alumno a consultar\n");
                    printf("Apellido: ");
                    gets(apellidoAlumno);
                    fflush(stdin);
                    printf("Nombre: ");
                    gets(nombreAlumno);
                    consultarDatosAlumno(listaAlumnos, apellidoAlumno, nombreAlumno);
                    free(apellidoAlumno);
                    free(nombreAlumno);
                }
            }
        }
    }while(opcion != 4);

}

void eliminarListaAlumnos(alumNodo** listaAlumnos){
    alumNodo* aux = *listaAlumnos;
    while(*listaAlumnos){
        *listaAlumnos = (*listaAlumnos)->sig;
        free(aux->datos.apellido);
        free(aux->datos.nombre);
        free(aux);
        aux = *listaAlumnos;
    }
}