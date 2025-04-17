#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 30

struct{
    int tareaID; // numero autoincremental comenzando en mil
    char *descripcion;
    int duracion; //entre 10  100
} typedef st_tarea;

struct{
    st_tarea T;
    struct st_nodo *siguiente;
} typedef st_nodo;

st_nodo *nodoVacio();
st_nodo *crearNodo(int cargarID, int cargarDuracion, char cargarDescripcion[MAX]);
void insertarNodo(st_nodo **start, int cargarID, int cargarDuracion, char cargarDescripcion[MAX]);

int main()
{
    int cargarId , cargarDuracion, anterior = 0, cargar = 1;
    char cargarDescripcion[MAX];
    st_nodo *realizadas;

    st_nodo *start = nodoVacio();

    while(cargar == 1)
    {
        printf("\nIngrese la descripcion de la tarea: ");
        gets(cargarDescripcion);

        cargarId = 1000 + rand() % (9999 - 1000 + 1);
        while(cargarId < anterior)
        {
            cargarId = 1000 + rand() % (9999 - 1000 + 1);
        }
        anterior = cargarId;

        printf("\nIngrese la duracion de la tarea(entre 10y100): ");
        scanf("%d", &cargarDuracion);
        while(getchar() != '\n'); //LIMPIAR BUFFER


        while(cargarDuracion < 10 || cargarDuracion > 100)
        {
            printf("\nIngrese la duracion de la tarea(entre 10y100): ");
            scanf("%d", &cargarDuracion);
            while(getchar() != '\n');
        }

        insertarNodo(&start, cargarId, cargarDuracion, cargarDescripcion);

        printf("\nCargar otra tarea?");
        printf("\n1)SI");
        printf("\n2)NO\n");
        scanf("%d", &cargar);
        
        while(getchar() != '\n');
    }

    return 0;
}

st_nodo *nodoVacio()
{
    return NULL;
}

st_nodo *crearNodo(int cargarID, int cargarDuracion, char cargarDescripcion[MAX])
{
    int longitudDescripcion = strlen(cargarDescripcion) + 1;

    st_nodo *pendientes = (st_nodo *)malloc(sizeof(st_nodo)); //Reservo memoria dinamica para el nodo
    pendientes->T.duracion = cargarDuracion;
    pendientes->T.tareaID = cargarID;

    pendientes->T.descripcion = (char *)malloc(sizeof(char) * longitudDescripcion);
    strcpy(pendientes->T.descripcion, cargarDescripcion); //cargo los campos de informacion
    pendientes->siguiente = NULL; //Indico que se ha llegado al final de la lista

    return pendientes;
}

void insertarNodo(st_nodo **start, int cargarID, int cargarDuracion, char cargarDescripcion[MAX])
{
    st_nodo *pendientes = crearNodo(cargarID, cargarDuracion, cargarDescripcion);//Creo el nodo

    pendientes->siguiente = *start;  //Hago que el nodo apunte al nodo que se encuentra
                                // al comienzo de la lista enlazada

    *start = pendientes; // elpuntero principal de la lista apunta ahora al nuevo nodo
                    // el nodo recien creado se convierte en el inicio de la lista
}