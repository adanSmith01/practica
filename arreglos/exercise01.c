#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *nombreProducto;
    int cantidad;
}Producto;

void cargarProductos(Producto **productos, int cant);
void moverProductos(Producto **productos, Producto **prodReclamar, int cant);
void mostrarNombProductos(Producto **productos, int cant);

int main(){
    int cantProductos;
    printf("Ingrese la cantidad de productos a registrar: ");
    scanf("%d", &cantProductos);
    Producto **productosAVender = (Producto **)malloc(sizeof(Producto *)*cantProductos);
    Producto **productosAReclamar = (Producto **)malloc(sizeof(Producto *)*cantProductos);

    //Inicializando los arreglos
    for(int i = 0; i < cantProductos; i++){
        productosAVender[i] = NULL;
        productosAReclamar[i] = NULL;
    }

    cargarProductos(productosAVender, cantProductos);
    moverProductos(productosAVender, productosAReclamar, cantProductos);

    puts("\n======LISTA DE NOMBRES DE PRODUCTOS A VENDER SIN RECLAMAR======\n");
    mostrarNombProductos(productosAVender, cantProductos);
    puts("\n======LISTA DE NOMBRES DE PRODUCTOS A RECLAMAR======\n");
    mostrarNombProductos(productosAReclamar, cantProductos);

    eliminacionLista(productosAVender, cantProductos);
    eliminacionLista(productosAReclamar, cantProductos);
    
    return 0;
}

void cargarProductos(Producto **productos, int cant){
    char *buffer;
    for(int i = 0; i < cant; i++){
        buffer = (char *)malloc(50);
        printf("\n***********PRODUCTO 0%d*********\n", i + 1);
        productos[i] = (Producto *)malloc(sizeof(Producto));
        fflush(stdin);
        printf("Nombre: ");
        gets(buffer);
        productos[i]->nombreProducto = (char *)malloc(strlen(buffer) + 1);
        strcpy(productos[i]->nombreProducto, buffer);
        printf("Cantidad: ");
        scanf("%d", &productos[i]->cantidad);
        free(buffer);
    }
}

void moverProductos(Producto **productos, Producto **prodReclamar, int cant){
    for(int i = 0; i < cant; i++){
        if(productos[i]->cantidad < 20000){
            prodReclamar[i] = productos[i];
            productos[i] = NULL;
        }
    }
}

void mostrarNombProductos(Producto **productos, int cant){
    for(int i = 0; i < cant; i++){
        if(productos[i]) {
            printf("- %s\n", productos[i]->nombreProducto);
        }
    }
}

void eliminacionLista(Producto **productos, int cantProductos){
    for(int i = 0; i < cantProductos; i++){
        free(productos[i]->nombreProducto);
        free(productos[i]);
    }
    free(productos);
}