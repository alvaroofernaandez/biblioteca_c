#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define maximolibros 100

// ESTRUCTURAS
struct categoria {
    char nombre[100];
};

struct autor {
    char nombre[100];
};

typedef struct {
    char titulo[100];
    int ano_publicacion;
    struct categoria Categoria;
    struct autor Autor;
    int tiempo_prestamo;
    char disponibilidad[50];
} biblioteca;





//DECLARACIÓN DE VARIABLES
void menu(biblioteca libros[], int cantidad);
void consultalibros(int cantidad, biblioteca libros[]);
void finprograma();
void cantidadlibros(int *cantidad);
void almacenarinfo(int cantidad, biblioteca libros[]);
void limpiarbuffer_entrada();
int mostrar_disponibilidad(biblioteca libro);
void consulta_titulo(int cantidad, biblioteca libros[]);
void info_libros(int cantidad, biblioteca libros[]);
void solicitud_prestamo(int cantidad, biblioteca libros[]);
void devolver_libro_prestado(int cantidad, biblioteca libros[]);





//FUNCIÓN MAIN O PRINCIPAL.
int main() {
    int cantidad, contador = 0;

    cantidadlibros(&cantidad);

    biblioteca libros[maximolibros];

    almacenarinfo(cantidad, libros);

    menu(libros, cantidad);

    return 0;
}





// ---------------------------------------------------FUNCIONES----------------------------------------------------------





//FUNCIÓN PARA LIMPIAR EL BUFFER DE ENTRADA.
void limpiarbuffer_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}





//FUNCIÓN MENÚ.
void menu(biblioteca libros[], int cantidad) {
    int opcion;

    do {
        printf("---------------------BIENVENIDO A BIBLIOTECA ALVARO---------------------\n\n");
        printf("1. Consultar libros disponibles actualmente.\n\n");
        printf("2. Consultar libros segun su titulo.\n\n");
        printf("3. Mostrar un libro y su info.\n\n");
        printf("4. Solicitar prestamo de libro.\n\n");
        printf("5. Devolver un libro prestado.\n\n\n\n");
        printf("0. Salir del programa.\n\n");
        printf("--> Ingrese el valor segun la opcion que desee realizar: ");
        scanf("%d", &opcion);

        limpiarbuffer_entrada();

        switch (opcion) {
        case 1:
            consultalibros(cantidad, libros);
            break;
        case 2:
            consulta_titulo(cantidad, libros);
            break;
        case 3:
            info_libros(cantidad, libros);
            break;
        case 4:
            solicitud_prestamo(cantidad, libros);
            break;
        case 5:
            devolver_libro_prestado(cantidad, libros);
            break;
        case 0:
            finprograma();
            break;
        default:
            printf("Ingrese una opcion correcta!!!!");
            printf("\n\n\n-----------------------------------------------------------------------\n\n\n");
        }
    } while (opcion != 0);
}





//FUNCIÓN PARA ELEGIR LA CANTIDAD DE LIBROS A INTRODUCIR
void cantidadlibros(int *cantidad) {
    printf("Elige la cantidad de libros a introducir: ");
    scanf("%d", cantidad);

    printf("--------------------------------------------------------------------------------\n\n");
}





//FUNCIÓN PARA ALMACENAR LA INFORMACIÓN DE CADA LIBRO.
void almacenarinfo(int cantidad, biblioteca libros[]) {
    int contador = 0;

    for (int i = 0; i < cantidad; i++) {
        contador++;

        printf("\nIntroduce el ano de publicacion del libro %d: ", contador);
        scanf("%d", &libros[i].ano_publicacion);

        limpiarbuffer_entrada();

        printf("\nIntroduce el titulo del libro %d: ", contador);
        fgets(libros[i].titulo, sizeof(libros->titulo), stdin);

        printf("\nIntroduce al autor del libro %d: ", contador);
        fgets(libros[i].Autor.nombre, sizeof(libros->Autor.nombre), stdin);

        printf("\nIntroduce la categoria del libro %d: ", contador);
        fgets(libros[i].Categoria.nombre, sizeof(libros->Categoria.nombre), stdin);

        printf("\nIntroduce (s/n) en funcion de la disponibilidad que haya: \n");
        fgets(libros[i].disponibilidad, sizeof(libros->disponibilidad), stdin);

        if (mostrar_disponibilidad(libros[i])) {
            libros[i].disponibilidad[0] = 's';
        } else {
            libros[i].disponibilidad[0] = 'n';
        }

        limpiarbuffer_entrada();

        printf("--------------------------------------------------------------------------------\n\n");
    }
}





//FUNCIÓN PARA MOSTRAR LA DISPONIBILIDAD DE LOS LIBROS.
int mostrar_disponibilidad(biblioteca libro) {
    size_t len = strlen(libro.disponibilidad);
    if (len > 0 && libro.disponibilidad[len - 1] == '\n') {
        libro.disponibilidad[len - 1] = '\0';
    }

    if (strcmp(libro.disponibilidad, "s") == 0) {
        return 1;
    } else {
        return 0;
    }
}





//FUNCIÓN PARA MOSTRAR LOS LIBROS QUE SE ENCUENTRAN DENTRO DE LA BIBLIOTECA.
void consultalibros(int cantidad, biblioteca libros[]) {
    printf("\n\n\n-----------------------------------------------------------------------\n");

    printf("Estos son los libros que se encuentran en nuestra biblioteca: \n\n");

    for (int i = 0; i < cantidad; i++) {
        if (mostrar_disponibilidad(libros[i]) == 1) {
            printf("- %s\n", libros[i].titulo);
        } else if (mostrar_disponibilidad(libros[i]) == 0) {
            printf("- %s  (NO DISPONIBLE) \n", libros[i].titulo);
        }
    }

    system("pause");
}





//FUNCIÓN PARA CONSULTAR UN LIBRO SEGÚN SU TÍTULO.
void consulta_titulo(int cantidad, biblioteca libros[]) {

    printf("\n\n\n-----------------------------------------------------------------------\n");

    char r[100];
    int libro = -1;

        do{
           printf("Introduce el titulo del libro que quieras buscar (debes escribirlo tal y como lo introduciste): ");
           fgets(r, sizeof(r), stdin);

           int encontrado=0;

           for (int i = 0; i < cantidad; i++) {
                if (strcmp(r, libros[i].titulo) == 0) {
                    printf("\nTitulo del libro correcto");
                    libro=i;
                    encontrado=1;
                    break;
                }
           }

        if (!encontrado) {
            printf("\n El libro no esta disponible. Prueba de nuevo. \n");
        }

    } while (libro == -1);

    if (mostrar_disponibilidad(libros[libro]) == 1){
        printf("\nLibro disponible en nuestra biblioteca. \n\n");
        printf("DETALLES: \n");
        printf("-Titulo: %s", libros[libro].titulo);
        printf("-Publicado en el %d\n", libros[libro].ano_publicacion);
        printf("-Autor: %s", libros[libro].Autor.nombre);
        printf("-Categoria: %s\n\n", libros[libro].Categoria.nombre);
    } else {
        printf("\nLibro no disponible en nuestra biblioteca.\n\n");
        printf("DETALLES: \n");
        printf("-Titulo: %s", libros[libro].titulo);
        printf("-Publicado en el %d\n", libros[libro].ano_publicacion);
        printf("-Autor: %s", libros[libro].Autor.nombre);
        printf("-Categoria: %s\n\n", libros[libro].Categoria.nombre);
    }

    system("pause");
}





//FUNCIÓN PARA MOSTRAR LA INFORMACIÓN DE UN LIBRO.
 void info_libros(int cantidad, biblioteca libros[]) {

    printf("\n\n\n-----------------------------------------------------------------------\n");
    printf("--------------------------LIBROS------------------------------\n\n\n");
    for (int i = 0; i < cantidad; i++) {
        if (mostrar_disponibilidad(libros[i]) == 1) {
            printf("- %s\n", libros[i].titulo);
        }
    }
    char eleccion[100];
    int libro=-1;

        do{
           printf("Introduce el titulo del libro que desees: ");
           fgets(eleccion, sizeof(eleccion), stdin);

           int encontrado=0;

           for (int i = 0; i < cantidad; i++) {
                if (strcmp(eleccion, libros[i].titulo) == 0) {
                    printf("\nLibro encontrado!");
                    libro=i;
                    encontrado=1;
                    break;
                }
           }

        if (!encontrado) {
            printf("\nEse libro no es correcto. \n");
        }

    } while (libro == -1);

    if (mostrar_disponibilidad(libros[libro]) == 1){
        printf("\nDETALLES: \n");
        printf("-Titulo: %s", libros[libro].titulo);
        printf("-Publicado en el %d\n", libros[libro].ano_publicacion);
        printf("-Autor: %s", libros[libro].Autor.nombre);
        printf("-Categoria: %s\n\n", libros[libro].Categoria.nombre);
    }

    system("pause");
}





//FUNCIÓN PARA SOLICITAR PRESTAMOS.
void solicitud_prestamo(int cantidad, biblioteca libros[]) {
    printf("\n\n\n-----------------------------------------------------------------------\n\n");
    printf("¿Deseas solicitar un prestamo de un libro? (s/n)\n\n");

    char resp;
    scanf("%c", &resp);
    limpiarbuffer_entrada();

    if (resp == 's') {
        printf("--------------------------LIBROS DISPONIBLES PARA PRÉSTAMO------------------------------\n\n");
        for (int i = 0; i < cantidad; i++) {
            if (mostrar_disponibilidad(libros[i]) == 1) {
                printf("- %s\n", libros[i].titulo);
            }
        }

        char elec[100];
        int libro = -1;

        do {
            printf("¿Que libro deseas pedir prestado?\n");
            fgets(elec, sizeof(elec), stdin);
            limpiarbuffer_entrada();

            int encontrado = 0;

            for (int i = 0; i < cantidad; i++) {
                if (strcmp(elec, libros[i].titulo) == 0) {
                    if (mostrar_disponibilidad(libros[i]) == 1) {
                        printf("\nLibro encontrado!\n\n");
                        libro = i;
                        encontrado = 1;
                        break;
                    } else {
                        encontrado = -1;
                    }
                }
            }

            if (encontrado == 0) {
                printf("\nEse libro no esta en nuestra biblioteca.\n\n");
            } else if (encontrado == -1) {
                printf("\nEse libro no esta disponible.\n\n");
                break;
            }
        } while (libro == -1);

        if (mostrar_disponibilidad(libros[libro]) == 1) {
            printf("Prestamo realizado con exito. El libro debe ser devuelto en un maximo de 15 dias.\n\n");
            libros[libro].disponibilidad[0] = 'n';
        }

        system("pause");

    } else if (resp == 'n') {
        printf("¡Estupendo! ¡Hasta la proxima! \n");
    }
}





//FUNCIÓN PARA REALIZAR LAS DEVOLUCIONES.
void devolver_libro_prestado(int cantidad, biblioteca libros[]) {
    printf("\n\n\n-----------------------------------------------------------------------\n");
    printf("¿Deseas devolver un libro prestado? (s/n)\n\n");

    char resp;
    scanf("%c", &resp);
    limpiarbuffer_entrada();

    if (resp == 's') {
        char titulo_devolucion[100];
        int libro_prestado = -1;

        printf("Introduce el titulo del libro que deseas devolver: ");
        fgets(titulo_devolucion, sizeof(titulo_devolucion), stdin);
        limpiarbuffer_entrada();

        for (int i = 0; i < cantidad; i++) {
            if (strcmp(titulo_devolucion, libros[i].titulo) == 0) {

                if (mostrar_disponibilidad(libros[i]) == 0) {
                    printf("Devolucion realizada con exito.\n");
                    libros[i].disponibilidad[0] = 's';
                    libro_prestado = i;
                    break;
                } else {
                    printf("El libro no estaba prestado actualmente.\n");
                }
            }
        }

        if (libro_prestado == -1) {
            printf("El libro no se encuentra en nuestra biblioteca o no esta actualmente prestado.\n");
        }

        system("pause");
    } else if (resp == 'n') {
        printf("¡Entendido! Hasta la proxima.\n");
    }
}






//FUNCIÓN PARA FINALIZAR EL PROGRAMA.
void finprograma() {
    printf("\n\n\n-----------------------------------------------------------------------\n\n\n");

    printf("Saliendo del programa...");
}

