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
st_nodo *crearNodo(st_nodo *nodo, int cargarID, int cargarDuracion, char *cargarDescripcion);
void insertarNodo(st_nodo **start, int cargarID, int cargarDuracion, char *cargarDescripcion);
void mostrarNodos(st_nodo *start);
st_nodo *buscarNodo(st_nodo *start, char *descripcion);
void eliminarNodo(st_nodo *nodo);
st_nodo *quitarNodo(st_nodo **start, char *oracion);
void consultarConId(st_nodo *start, st_nodo *start2);
void consultarConNombre(st_nodo *start, st_nodo *start2);


int main()
{
    srand(time(NULL));
    int cargarId , cargarDuracion, anterior = 0, cargar = 1;
    char cargarDescripcion[MAX], *buscar;

    st_nodo *start = nodoVacio();           //lista enlazada para las tareas pendientes
    st_nodo *startRealizadas = nodoVacio(); //lista enlazada para las tareas pendientes

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

    mostrarNodos(start);

    printf("\nDesea marcar una tarea como realizada?");
    printf("\n1)SI");
    printf("\n2)NO\n");
    scanf("%d", &cargar);
    while(getchar() != '\n');//LIMPIAR EL BUFFER

    while(cargar == 1)
    {
        printf("\nIngrese la trea: ");
        gets(cargarDescripcion);
        buscar = (char*)malloc(sizeof(char) * (strlen(cargarDescripcion) + 1)  );
        strcpy(buscar, cargarDescripcion);
        st_nodo *auxiliar = buscarNodo(start, buscar); //Guardo el nodo aqui

        if(auxiliar)
        {
            cargarId = auxiliar->T.tareaID; //Guardo los datos del nodo
            cargarDuracion = auxiliar->T.duracion;
            insertarNodo(&startRealizadas, cargarId, cargarDuracion, buscar); 
            //Inserto en un nodo de la otra lista los valores del nodo encontrado
            
            st_nodo *borrar = quitarNodo(&start, buscar);
            eliminarNodo(borrar);
        }

        printf("\nDesea marcar una tarea como realizada?");
        printf("\n1)SI");
        printf("\n2)NO\n");
        scanf("%d", &cargar);
        while(getchar() != '\n');//LIMPIAR EL BUFFER

    }

    printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nTareas Pendientes: ");
    mostrarNodos(start);
    printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nTareas realizadas: ");
    mostrarNodos(startRealizadas);

    printf("\n~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nCon que metodo desea buscar la tarea");
    printf("\n1) ID");
    printf("\n2) Descripcion");
    scanf("%d", &cargar);
    while(getchar() != '\n');

    if(cargar == 1)
    {
        consultarConId(start, startRealizadas);
    } else {
        consultarConNombre(start, startRealizadas);
    }

    return 0;
}

st_nodo *nodoVacio()
{
    return NULL;
}

st_nodo *crearNodo(st_nodo *nodo, int cargarID, int cargarDuracion, char *cargarDescripcion)
{
    int longitudDescripcion = strlen(cargarDescripcion) + 1;

    nodo = (st_nodo *)malloc(sizeof(st_nodo)); //Reservo memoria dinamica para el nodo
    nodo->T.duracion = cargarDuracion;
    nodo->T.tareaID = cargarID;

    nodo->T.descripcion = (char *)malloc(sizeof(char) * longitudDescripcion);
    strcpy(nodo->T.descripcion, cargarDescripcion); //cargo los campos de informacion
    nodo->siguiente = NULL; //Indico que se ubicara al de la lista

    return nodo;
}

void insertarNodo(st_nodo **start, int cargarID, int cargarDuracion, char *cargarDescripcion)
{
    st_nodo *nodo = crearNodo(nodo, cargarID, cargarDuracion, cargarDescripcion);//Creo el nodo

    nodo->siguiente = *start;  //Hago que el nodo apunte al nodo que se encuentra
                                // al comienzo de la lista enlazada

    *start = nodo; // elpuntero principal de la lista apunta ahora al nuevo nodo
                    // el nodo recien creado se convierte en el inicio de la lista
}

void mostrarNodos(st_nodo *start)
{
    st_nodo *auxiliar = start;
    while(auxiliar) //Mientras nuestro nodo no sea NULL, es decir, el ultimo de la lista
    {
        printf("\n~~~~~~~~~~~");
        printf("\nID de la tarea: %d", auxiliar->T.tareaID);
        printf("\nTarea: ");
        puts(auxiliar->T.descripcion);
        printf("Duracion de la tarea: %d", auxiliar->T.duracion);

        auxiliar = auxiliar->siguiente;
    }
}

st_nodo *buscarNodo(st_nodo *start, char *descripcion)
{
    st_nodo *auxiliar = start;
    while(auxiliar && strcmp(auxiliar->T.descripcion,descripcion) != 0)
    //Mientras no se llegue al final de la lista
    //y la descripcion del nodo no sea la que busco
    {
        auxiliar = auxiliar->siguiente; //Avanzo en la lista
    }
    
    return auxiliar;
}

void eliminarNodo(st_nodo *nodo)
{
    if(nodo)
    {
        free(nodo->T.descripcion);
        free(nodo);
    }
}

st_nodo *quitarNodo(st_nodo **start, char *oracion)
{
    st_nodo **auxiliar = start;
    while(*auxiliar != NULL && strcmp((*auxiliar)->T.descripcion,oracion) != 0 )
    //Mientras no se llegue al final de la lista
    //Mientras no se encuentre el nodo
    {
        auxiliar = &(*auxiliar)->siguiente; //Se pasa al siguiente
    }

    if(*auxiliar) //Si se encontro el nodo (es distinto de NULL)
    {
        st_nodo *temporal = *auxiliar;
        *auxiliar = (*auxiliar)->siguiente;
        temporal->siguiente = NULL;
        return temporal;
    }

    return NULL;

}

void consultarConId(st_nodo *start, st_nodo *start2)
{
    int id;

    printf("\nIngrese la id: ");
    scanf("%d", &id);


        st_nodo *aux = start;

        while(aux && aux->T.tareaID != id)
        {
            aux = aux->siguiente;
        }

        if(aux) //Si se encontro la tarea en pendientes
        {
            printf("\nLa tarea esta en estado pendinte");
            printf("\nID: %d", aux->T.tareaID);
            printf("\nNombre: ");
            puts(aux->T.descripcion);
            printf("\nDuracion: %d", aux->T.duracion);
        } else { //si no se encontro en pendientes, busco en realizado

            aux = start2;

            while(aux && aux->T.tareaID != id)
            {
                aux = aux->siguiente;
            }

            if(aux)//Si se encontro en tareas realizadas
            {
                printf("\nLa tarea esta en estado realizada");
                printf("\nID: %d", aux->T.tareaID);
                printf("\nNombre: ");
                puts(aux->T.descripcion);
                printf("\nDuracion: %d", aux->T.duracion);
            }
        }
    

    if(aux == NULL)
    {
        printf("\n No se a encontrado la tarea");
    }
}


void consultarConNombre(st_nodo *start, st_nodo *start2)
{
    char descripcion[MAX], *buscar;

    printf("\nIngrese la descripcion de la tarea: ");
    gets(descripcion);
    buscar = (char *)malloc(sizeof(char) * (strlen(descripcion) +1)  );
    strcpy(buscar, descripcion);


    st_nodo *aux = start;

    while(aux && strcmp(buscar,aux->T.descripcion) != 0)
    {
        aux = aux->siguiente;
    }

    if(aux) //Si se encontro la tarea en pendientes
    {
        printf("\nLa tarea esta en estado pendinte");
        printf("\nID: %d", aux->T.tareaID);
        printf("\nNombre: ");
        puts(aux->T.descripcion);
        printf("\nDuracion: %d", aux->T.duracion);
    } else { //si no se encontro en pendientes, busco en realizado

        aux = start2;

        while(aux && strcmp(buscar,aux->T.descripcion) != 0)
        {
            aux = aux->siguiente;
        }

        if(aux)//Si se encontro en tareas realizadas
        {
            printf("\nLa tarea esta en estado realizada");
            printf("\nID: %d", aux->T.tareaID);
            printf("\nNombre: ");
            puts(aux->T.descripcion);
            printf("\nDuracion: %d", aux->T.duracion);
        }
    }


if(aux == NULL)
{
    printf("\n No se a encontrado la tarea");
}

}