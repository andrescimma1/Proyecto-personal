#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define TAM 20
#define TAMCOM 13

typedef struct
{
    char nombre[20];
    int edad;
    char estudiaOtrabaja[20];
    char trabaja[20];
    char menoresAcargo[20];
    char enfermedadesPatologicas[20];
    int ocupado;
    int idComida;
}eCliente;

typedef struct
{
    int id;
    char comida[20];
}eComida;

int menu();
void inicializarClientes(eCliente clientes[], int tam);
void altaCliente(eCliente clientes[], int tam, eComida comidas[], int tamcom);
int buscarDesocupado(eCliente clientes[], int tam);
void mostrarComida(eComida comidas);
void mostrarComidas(eComida comidas[], int tamcom);
void mostrarCliente(eCliente clientes, eComida comidas[], int tam);
void mostrarClientes(eCliente clientes[], int tam, eComida comidas[], int tamcom);
int obtenerComida(eComida comidas[], int tam, int idComida, char desc[]);

int main()
{
    char respuesta = 'n';
    eCliente clientes[TAM];
    inicializarClientes(clientes, TAM);
    eComida comidas[TAMCOM] = {
                         {1, "Aceites"},
                         {2, "Azucar"},
                         {3, "Carnes"},
                         {4, "Cereales"},
                         {5, "Hortalizas A"},
                         {6, "Hortalizas B"},
                         {7, "Hortalizas C"},
                         {8, "Huevo"},
                         {9, "Leche"},
                         {10, "Legumbres"},
                         {11, "Frutas"},
                         {12, "Queso"},
                         {13, "Ultraprocesados"}
                         };

    do{
    switch(menu())
    {
    case 1:
        altaCliente(clientes, TAM, comidas, TAMCOM);
        system("pause");
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        mostrarClientes(clientes, TAM, comidas, TAMCOM);
        break;
    case 6:
        printf("\n\n¿Seguro que desea salir? (s/n): ");
        fflush(stdin);
        scanf("%c", &respuesta);
        system("pause");
        break;
    default:
        printf("\n\nError, opcion no valida");
        system("pause");
        break;
    }
    }while(respuesta != 's');


    return 0;
}

int menu()
{
    int opcion;
    printf("*** Menu de opciones ***\n\n");
    printf("1_ Dar de alta un cliente\n");
    printf("2_ Dar de baja un cliente\n");
    printf("3_ Modificar un cliente\n");
    printf("4_ Borrar un cliente\n");
    printf("5_ Listar clientes\n");
    printf("6_ Salir\n\n");
    printf("Ingrese opcion: ");
    scanf("%d", &opcion);

    return opcion;
}

void inicializarClientes(eCliente clientes[], int tam)
{
    int i;
    for(i=0; i<tam; i++)
    {
        clientes[i].ocupado = 0;
    }
}

int buscarDesocupado(eCliente clientes[], int tam)
{
    int i;
    int indice = -1;
    for(i=0; i<tam; i++)
    {
        if(clientes[i].ocupado == 0)
        {
            indice = i;
        }
    }

    return indice;
}

void altaCliente(eCliente clientes[], int tam, eComida comidas[], int tamcom)
{
    int indice;

    system("cls");

    indice = buscarDesocupado(clientes, tam);

    if(indice == -1)
    {
        printf("\n\nNo hay lugar");
    }
    else
    {
        printf("\n\nIngrese nombre: ");
        fflush(stdin);
        gets(clientes[indice].nombre);

        printf("\nIngrese edad: ");
        fflush(stdin);
        scanf("%d", &clientes[indice].edad);

        printf("\nEstudia, trabaja, estudia y trabaja?: ");
        fflush(stdin);
        gets(clientes[indice].estudiaOtrabaja);

        printf("\nDe que trabaja?: ");
        fflush(stdin);
        gets(clientes[indice].trabaja);

        printf("\nMenores a cargo: ");
        fflush(stdin);
        gets(clientes[indice].menoresAcargo);

        printf("\nHay enfermedades patologicas presentes en la familia: ");
        fflush(stdin);
        gets(clientes[indice].enfermedadesPatologicas);

        mostrarComidas(comidas, tamcom);

        printf("\n\nIngrese ID de la comida: ");
        fflush(stdin);
        scanf("%d", &clientes[indice].idComida);

        clientes[indice].ocupado = 1;

        printf("\n\nDatos ingresados con exito!");
    }
}

void mostrarComida(eComida comidas)
{
    printf("%d       %s\n", comidas.id, comidas.comida);
}

void mostrarComidas(eComida comidas[], int tamcom)
{
    int i;

    system("cls");
    printf("Comidas\n");
    printf("________________________\n");
    printf("ID      COMIDA\n");

    for(i=0; i<tamcom; i++)
    {
        mostrarComida(comidas[i]);
    }
    printf("\n\n");
}

void mostrarCliente(eCliente clientes, eComida comidas[], int tam)
{
    char nombreComida[20];
    int consiguioComida;

    consiguioComida = obtenerComida(comidas, tam, clientes.idComida, nombreComida);

    if(!consiguioComida)
    {
        strcpy(nombreComida, "Sin definir");
    }

    printf("%s    %d     %s     %s    %s     %s     %s", clientes.nombre, clientes.edad, clientes.estudiaOtrabaja,
                                                                 clientes.trabaja, clientes.menoresAcargo,
                                                                 clientes.enfermedadesPatologicas, nombreComida);


}

void mostrarClientes(eCliente clientes[], int tam, eComida comidas[], int tamcom)
{
    int i;
    int cont = 0;
    system("cls");
    printf("                                CLIENTES\n");
    printf("__________________________________________________________________________\n");
    printf("Nombre    Edad    Actualmente   Trabajo   Menores   Enfermedades   Comidas\n");

    for(i=0; i<tam; i++)
    {
        if(clientes[i].ocupado == 1)
        {
            mostrarCliente(clientes[i], comidas, tam);
            cont++;
        }
    }

    if(cont == 0)
    {
        printf("\nNo hay empleados que mostrar\n\n");
    }
    printf("\n\n");
}

int obtenerComida(eComida comidas[], int tam, int idComida, char desc[])
{
    int i;
    int todoOk = 0;
    for(i=0; i<tam; i++)
    {
        if(idComida == comidas[i].id)
        {
            strcpy(desc, comidas[i].comida);
            todoOk = 1;
            break;
        }
    }
    return todoOk;
}
