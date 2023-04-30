#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    char *apellido;
    char *nombre;
    char DNI[10];
    int montoOtorgado;
    int gastos[7];
}usuario;

typedef struct nodoUsuario{
    usuario datos;
    struct nodoUsuario *siguiente;
}nodoUsuario;

nodoUsuario * listaUsuariosVacia();
usuario registrarUsuario();
nodoUsuario * crearNodoUsuario(usuario usuarioRegistrado);
void insertarNodoUsuario(nodoUsuario **listaUsuarios, nodoUsuario *usuarioNodoRegistrado);
void mostrarUsuarios(nodoUsuario *listaUsuarios);
int estaConDeuda(int gastos[], int montoOtorgado);
nodoUsuario * buscarUsuarioPorDNI(nodoUsuario *listaUsuarios, char *DNI);
nodoUsuario * desvincularUsuario(nodoUsuario **usuariosConDeuda, char *DNI);
void eliminarLista(nodoUsuario **listaUsuarios);


int main(){
    //Creando las listas de usuarios con y sin deuda vacías
    nodoUsuario *usuariosSinDeuda = listaUsuariosVacia();
    nodoUsuario *usuariosConDeuda = listaUsuariosVacia();
    nodoUsuario *usuarioAEnlistar, *usuarioEncontrado;
    int seguir, opcion, mostrarLista, gastoTotal, confirmar;
    usuario aux;
    char *dni;
    srand(time(NULL));

    printf("\n==========CONTROLADOR DE GASTOS DE USUARIOS==========\n");
    //Ingresar los nombres de los usuarios del banco
    do{
        aux = registrarUsuario();
        usuarioAEnlistar = crearNodoUsuario(aux);
        if(estaConDeuda(usuarioAEnlistar->datos.gastos, usuarioAEnlistar->datos.montoOtorgado)){
            insertarNodoUsuario(&usuariosConDeuda, usuarioAEnlistar);
        } else{
            insertarNodoUsuario(&usuariosSinDeuda, usuarioAEnlistar);
        }
        free(aux.apellido);
        free(aux.nombre);
        printf("\nVa a seguir registrando a otro usuario? Si(1) / No(0): ");
        scanf("%d", &seguir);
    }while(seguir);

    //Interfaz de usuario
    do{
        puts("\n**********MENU PRINCIPAL*************\n");
        puts("\n1- Mostrar usuarios del banco");
        puts("2- Consultar informacion de un usuario");
        puts("3- Salir\n");
        printf("\nElija una opcion: ");
        scanf("%d", &opcion);

        if(opcion == 1){
            do{
                printf("\nQue lista de usuarios quiere que se muestre?\n");
                puts("\n1- Todos los usuarios");
                puts("2- Usuarios endeudados");
                puts("3- Usuarios desendeudados");
                puts("4- Ninguna\n");
                printf("\nLista a elegir: ");
                scanf("%d", &mostrarLista);
                if(mostrarLista == 1){
                    puts("\n**********LISTA DE TODOS LOS USUARIOS*********\n");
                    mostrarUsuarios(usuariosConDeuda);
                    mostrarUsuarios(usuariosSinDeuda);
                } else{
                    if(mostrarLista == 2){
                        puts("\n**********LISTA DE TODOS LOS USUARIOS CON DEUDA*********\n");
                        mostrarUsuarios(usuariosConDeuda);
                    } else{
                        if(mostrarLista == 3){
                            puts("\n**********LISTA DE TODOS LOS USUARIOS SIN DEUDA*********\n");
                            mostrarUsuarios(usuariosSinDeuda);
                        }
                    }
                } 
            }while(mostrarLista != 4);
        } else{
            if(opcion == 2){
                gastoTotal = 0;
                dni = (char *)malloc(10);
                fflush(stdin);
                printf("\nIndique el DNI del usuario a buscar: ");
                gets(dni);

                if(buscarUsuarioPorDNI(usuariosConDeuda, dni)){
                    usuarioEncontrado = buscarUsuarioPorDNI(usuariosConDeuda, dni);
                    puts("\n**********USUARIO ENCONTRADO**********\n");
                    printf("\nApellido: %s\n", usuarioEncontrado->datos.apellido);
                    printf("Nombre: %s\n", usuarioEncontrado->datos.nombre);
                    printf("DNI: %s\n", usuarioEncontrado->datos.DNI);
                    printf("Monto otorgado: %d\n", usuarioEncontrado->datos.montoOtorgado);
                    for(int i = 0; i < 7; i++){
                        gastoTotal += usuarioEncontrado->datos.gastos[i];
                    }
                    printf("Gasto total en la semana: %d\n", gastoTotal);
                    printf("Estado: Endeudado\n");
                    printf("El usuario va a saldar su deuda? Si(1) / No(0): ");
                    scanf("%d", &confirmar);
                    if(confirmar) insertarNodoUsuario(&usuariosSinDeuda, desvincularUsuario(&usuariosConDeuda, usuarioEncontrado->datos.DNI));
                } else{
                    if(buscarUsuarioPorDNI(usuariosSinDeuda, dni)){
                        usuarioEncontrado = buscarUsuarioPorDNI(usuariosSinDeuda, dni);
                        puts("\n**********USUARIO ENCONTRADO**********\n");
                        printf("\nApellido: %s\n", usuarioEncontrado->datos.apellido);
                        printf("Nombre: %s\n", usuarioEncontrado->datos.nombre);
                        printf("DNI: %s\n", usuarioEncontrado->datos.DNI);
                        printf("Monto otorgado: %d\n", usuarioEncontrado->datos.montoOtorgado);
                        for(int i = 0; i < 7; i++){
                            gastoTotal += usuarioEncontrado->datos.gastos[i];
                        }
                        printf("Gasto total en la semana: %d\n", gastoTotal);
                        printf("Estado: Desendeudado\n");
                    } else{
                        printf("\nEl usuario no existe\n");
                    }
                }

                free(dni);
            }
        }
    }while(opcion != 3);

    eliminarLista(&usuariosConDeuda);
    eliminarLista(&usuariosSinDeuda);
    
    return 0;
}

nodoUsuario * listaUsuariosVacia() {return NULL;}

usuario registrarUsuario(){
    usuario usuarioARegistrar;
    usuarioARegistrar.apellido = (char *)malloc(50);
    usuarioARegistrar.nombre = (char *)malloc(50);
    fflush(stdin);
    printf("\n==========DATOS DEL USUARIO==========\n");
    printf("\nApellido: ");
    gets(usuarioARegistrar.apellido);
    fflush(stdin);
    printf("Nombre: ");
    gets(usuarioARegistrar.nombre);
    fflush(stdin);
    printf("DNI: ");
    gets(usuarioARegistrar.DNI);
    usuarioARegistrar.montoOtorgado = 20000 + (rand() % 15001); // entre 20.000 a 35.000
    for(int i = 0; i < 7; i++){
        usuarioARegistrar.gastos[i] = 1000 + (rand() % 5001); //entre 1.000 a 6.000
    }
    
    return usuarioARegistrar;
}

nodoUsuario * crearNodoUsuario(usuario usuarioRegistrado){
    nodoUsuario *usuarioEnlistado = (nodoUsuario *)malloc(sizeof(nodoUsuario));
    usuarioEnlistado->datos.apellido = (char *)malloc(strlen(usuarioRegistrado.apellido) + 1);
    usuarioEnlistado->datos.nombre = (char *)malloc(strlen(usuarioRegistrado.nombre) + 1);
    strcpy(usuarioEnlistado->datos.apellido, usuarioRegistrado.apellido);
    strcpy(usuarioEnlistado->datos.nombre, usuarioRegistrado.nombre);
    strcpy(usuarioEnlistado->datos.DNI, usuarioRegistrado.DNI);
    usuarioEnlistado->datos.montoOtorgado = usuarioRegistrado.montoOtorgado;
    for(int i = 0; i < 7; i++){
        usuarioEnlistado->datos.gastos[i] = usuarioRegistrado.gastos[i];
    }
    usuarioEnlistado->siguiente = NULL;

    return usuarioEnlistado;
}

void insertarNodoUsuario(nodoUsuario **listaUsuarios, nodoUsuario *usuarioNodoRegistrado){
    usuarioNodoRegistrado->siguiente = *listaUsuarios;
    *listaUsuarios = usuarioNodoRegistrado;
}

int estaConDeuda(int gastos[], int montoOtorgado){
    int gastoEnTotal = 0;
    for(int i = 0; i < 7; i++){
        gastoEnTotal += gastos[i];
    }

    if(gastoEnTotal > montoOtorgado){
        return 1;
    } else{
        return 0;
    }
}

void mostrarUsuarios(nodoUsuario *listaUsuarios){
    int gastoTotal = 0;
    while(listaUsuarios){
        printf("\nApellido: %s\n", listaUsuarios->datos.apellido);
        printf("Nombre: %s\n", listaUsuarios->datos.nombre);
        printf("DNI: %s\n", listaUsuarios->datos.DNI);
        printf("Monto otorgado: %d\n", listaUsuarios->datos.montoOtorgado);
        for(int i = 0; i < 7; i++){
            gastoTotal += listaUsuarios->datos.gastos[i];
        }
        printf("Gasto total en la semana: %d\n", gastoTotal);
        listaUsuarios = listaUsuarios->siguiente;
    }
}

nodoUsuario * buscarUsuarioPorDNI(nodoUsuario *listaUsuarios, char *DNI){
    while(listaUsuarios && strcmp(listaUsuarios->datos.DNI, DNI) != 0){
        listaUsuarios = listaUsuarios->siguiente;
    }

    return listaUsuarios;
}

nodoUsuario * desvincularUsuario(nodoUsuario **usuariosConDeuda, char *DNI){
    nodoUsuario *antUsuario = NULL;
    nodoUsuario *auxUsuario = *usuariosConDeuda;

    while(auxUsuario && strcmp(auxUsuario->datos.DNI, DNI)){
        antUsuario = auxUsuario;
        auxUsuario = auxUsuario->siguiente;
    }

    if(auxUsuario){
        if(auxUsuario == *usuariosConDeuda){
            *usuariosConDeuda = auxUsuario->siguiente;
        } else{
            antUsuario->siguiente = auxUsuario->siguiente;
        }

        auxUsuario->siguiente = NULL;
    }

    return auxUsuario;
}

void eliminarLista(nodoUsuario **listaUsuarios){
    nodoUsuario *aux = *listaUsuarios;
    while(*listaUsuarios){
        *listaUsuarios = (*listaUsuarios)->siguiente;
        free(aux->datos.apellido);
        free(aux->datos.nombre);
        for(int i = 0; i < 7; i++){
            aux->datos.gastos[i] = NULL;
        }
        free(aux);
        aux = *listaUsuarios;
    }
    
    free(listaUsuarios);
}