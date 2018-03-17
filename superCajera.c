/* Caballero porfa no compactas tanto las cosas */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define TRUE 0 == 0
#define FALSE 0 == 1

typedef struct prod{

    int num; // El numero del producto
    char name[15]; // Nombre del Producto
    int size; // tamano del producto
    int complex; // complejidad

}Producto;

int countlines(char *filename){

    FILE *fp;
    int count = 0;  // contador de lineas
    char c;  // To store a character read from file

    // Open the file
    fp = fopen(filename, "r");

    // chequea si el archivo existe
    if(fp == NULL)
    {
        printf("Could not open file %s", filename);

        return 0;
    }

    // Extract characters from file and store in character c
    for(c = getc(fp); c != EOF; c = getc(fp))
    {
        if(c == '\n')
        {
            count = count + 1;
        }
    }

    // Close the file
    fclose(fp);
    //printf("The file %s has %d lines\n ", filename, count);

    return count;
};

Producto *readd(int numLines, char *filename, int *capacidadMaxBanda, int *capacidadMaxAreaEmbolsado){

    Producto *arrayP = malloc(numLines * sizeof(Producto));
    Producto *InicioArray = arrayP;
    int character, whitespace = 0;
    char *line = NULL;
    //char *line2 = NULL;
    size_t len = 0;
    ssize_t read;
    char *token;
    int contador = 0;
    int numero = 0; // numero del producto

    FILE *file = fopen ( filename, "r" );

    if(file == NULL)
    {
		exit(EXIT_FAILURE);
    }

	while((read = getline(&line, &len, file)) != -1)
    {
		//printf("Retrieved line of length %zu :\n", read);
		//printf("%s", line);
        // contamos la cantidad de tabs en la linea
        /* get the first token */
        Producto newProduct;
        token = strtok(line,"\t");

        /* iteramos sobre los otros token */
        while(token != NULL)
        {
            if(contador == 0)
            {
                numero = numero + 1;
                newProduct.num = numero; // es un producto nuevo, le registramos su numero
                strcpy(newProduct.name,token);
                //printf("NUMERO %d\n", newProduct.num);
                //printf("NOMBRE %s\n", newProduct.name);
            }

            if(contador == 1)
            {
                newProduct.size = atoi(token);

                /* para fijar el tamao maximo de la banda al del objeto mas grande, para evitar rollos */

                if(newProduct.size > *capacidadMaxBanda)
                {
                    *capacidadMaxBanda = newProduct.size;
                }

                if(newProduct.size > *capacidadMaxAreaEmbolsado)
                {
                    *capacidadMaxAreaEmbolsado = newProduct.size;
                }
                //printf("TAMANO %d\n",newProduct.size);
            }

            if(contador == 2)
            {
                newProduct.complex = atoi(token);
                //printf("COMPLEX %d\n",newProduct.complex);
                *arrayP = newProduct;
                arrayP++;
            }

            //printf("contador %d\n", contador );
            //printf( "token %s\n", token );
            token = strtok(NULL,"\t");
            contador++;
        }

        contador = 0; // restablecemos el contador para la siguiente linea
    }

	free(line);
	fclose(file);

    return InicioArray;

}

typedef struct node_{

    Producto product;
    struct node_ *next;

}node;

// ----------------------------------------------------------------- SORTED LIST

node *createList()
{
	node *l = NULL;
	return l;
}

/* Pone nod en list según el orden alfabetico del campo dato.name */
void put(node **list, node* nod){

    if(*list == NULL || (nod->product.size - (*list)->product.size) >= 0)
    {
        nod->next = *list;
        *list = nod;
    }

    else
    {
        node *p = *list;

        while(p->next != NULL && (nod->product.size - p->next->product.size) < 0)
        {
            p = p->next;
        }

        nod->next = p->next;
        p->next = nod;
    }
}


 //devuelve 1 si se insert con éxito y 0 si no.
int insert(node **list, Producto p){

    int r; /* valor de retorno */

    /* crear nuevo nodo */
    node* pNuevo = malloc( sizeof(*pNuevo));

    /* puntero en la lista */
    if(r = pNuevo != NULL)
    {
        pNuevo->product = p;
        put(list, pNuevo);
    }

    return r;
}

void printList(node *pActual)
{
    /* Mientras no sea el final de la lista */
    while(pActual != NULL)
    {
        printf("Nombre: %s  size %d complex %d num %d\n",pActual->product.name,pActual->product.size,pActual->product.complex,pActual->product.num);
        pActual = pActual->next;
    }
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ PILA
typedef struct stack_{

    unsigned int size;
    int ccEnEmbolsado; // cuenta la cantidad de cc que hay en el area de embolsado
    node *head;

}stack;

stack *create_stack(){ //initializes the stack

    stack *pila = malloc (sizeof(stack));

    pila->size = 0;
    pila->ccEnEmbolsado = 0;
    pila->head = NULL;

    return pila;

}

void push(stack *s, Producto pro){

    node *temp = (node*)malloc(sizeof(node)); //allocates

    if(temp == NULL)
    {
        printf("No se puede asignar el espacio de memoria solicitado\n");
    }

    else
    {
        temp->next = s->head;
        temp->product = pro;
        s->ccEnEmbolsado = s->ccEnEmbolsado + pro.size;
        s->head = temp;
        s->size = (s->size) + 1; //bumps the counter for how many elements are in the stack
    }

}

Producto *pop(stack *s){

    if((s->size) == 0)
    {
        printf("La pila esta vacia \n");

        return NULL;
    }

    else
    {
        node *temp;
        node *temp2;

        temp = s->head;
        s->head = temp->next;
        s->size = (s->size) - 1; //subtracts from counter
        temp2 = temp;
        s->ccEnEmbolsado = s->ccEnEmbolsado - temp2->product.size;
        //printf("%p\n", &(temp2->product));
        //printf("%s\n", casa.name);
        free(temp);
        //printf("%s\n", casa.name);
        //printf("%p\n",&(temp2->product) );

        return &(temp2->product);
    }


}

int top(stack *s){

    if((s->size) == 0)
    {
        printf("La pila esta vacia \n");

        return 0;
    }

    else
    {
        node *temp = s->head;

        Producto value = temp->product;
        printf("%s\n",value.name);
        return value.size;
    }
}


// ---------------------------------------------------- COLA DE PILAS (CARRITOS)

typedef struct NODE_{

    stack *pila;
    struct NODE_ *next;
    struct NODE_ *prev;

}NODE;

typedef struct queue_{

    unsigned int size;
    NODE *head;
    NODE *tail;

}queue;

queue* create_queue(){ //initializes the queue

    queue* cola = malloc (sizeof(queue));

    cola->size = 0;
    cola->head = NULL;
    cola->tail = NULL;

    return cola;

}

void enqueue(queue *q, stack *pila) {

    NODE *temp = (NODE*)malloc(sizeof(NODE)); //allocates

    if(temp == NULL)
    {
        printf("Unable to allocate memory\n");
    }

    else if((q->size) == 0)
    {
        temp->next = q->head;
        temp->pila = pila;
        //printf("POINTER INTERNO 1%p\n",temp->pila );
        q->head = temp;
        q->head->next = NULL;
        q->tail = temp;
        q->tail->next = NULL;
        q->size = (q->size) + 1; //bumps the counter for how many elements are in the queue
    }

    else
    {
        temp->next = q->tail;
        q->tail->prev = temp;
        temp->pila = pila;
        q->tail = temp;
        q->size = (q->size) + 1; //bumps the counter for how many elements are in the queue
    }

}

stack *dequeue(queue *q){

    int salida = 0;

    if((q->size) == 0)
    {
        printf("La cola esta vacia \n");

        return NULL;
    }

    else
    {
        NODE *temp;
        stack *temp2;
        temp = q->head;
        temp2 = temp->pila;
        //printf("APUUUUNTAAA %p\n",temp2);
        q->head = q->head->prev;
        //printf("%p\n", &(temp2->pila));
        //printf("----%s\n", casa.name);
        free(temp);
        q->size = (q->size) - 1; //subtracts from counter

        return temp2;
    }
}

//------------------------------------- COLA DE PRODUCTOS/ Banda transportadora

typedef struct Node_{
    Producto product;
    struct Node_ *next;
    struct Node_ *prev;
}Node;

typedef struct Queue_{
    unsigned int size;
    int ccEnBanda; // cuenta la cantidad de cc que hay en la banda transportadora
    Node* head;
    Node* tail;
}colaa;

colaa* crecreate_queue(){ //initializes the queue

    colaa* cola = malloc (sizeof(colaa));

    cola->size = 0;
    cola->head = NULL;
    cola->tail = NULL;
    cola->ccEnBanda = 0;

    return cola;

}

void enenqueue(colaa* q, Producto pro) {

    Node* temp = (Node*)malloc(sizeof(Node)); //allocates

    if ( temp == NULL ) {
        printf("Unable to allocate memory\n");
    }
    else if ((q->size) == 0) {
      temp->next = q->head;
      temp->product = pro;
      //(temp->next)->prev = temp;
      q->head = temp;
      q->head->next = NULL;
      q->tail = temp;
      q->tail->next = NULL;
      q->size = (q->size) + 1; //bumps the counter for how many elements are in the queue
      q->ccEnBanda = q->ccEnBanda + pro.size;
    }
    else{
      temp->next = q->tail;
      q->tail->prev = temp;
      temp->product = pro;
      q->tail = temp;
      q->size = (q->size) + 1; //bumps the counter for how many elements are in the queue
      q->ccEnBanda = q->ccEnBanda + pro.size;
    }

}

Producto* dedequeue(colaa* q) {
  int salida = 0;
    if ((q->size) == 0) {
      printf("La cola esta vacia \n");
      return NULL;
    }
    else{
      Node* temp;
      Node* temp2;

      temp = q->head;
      q->head = q->head->prev;
      temp2 = temp;
      //printf("%p\n", &(temp2->product));
      //Producto casa = (temp2->product);
      //printf("----%s\n", casa.name);
      //q->head = temp->next;
      free(temp);
      q->size = (q->size) - 1; //subtracts from counter
      q->ccEnBanda = q->ccEnBanda - temp2->product.size;
      return &(temp2->product);
    }
}

int tope(colaa* q) {
    if ((q->size) == 0) {
      printf("La cola esta vacia \n");
    }

    Node* temp = q->head;

    Producto value = temp->product;
    printf("%d\n",value.size );
    return value.size;

}

void Menu(int *carritos, int *cantidadMaxCarrito, int *capacidadMaxBanda,
        int *velocidadCajera, int *velocidadEmbolsador, int *tiempoFacturacion,
        int *capacidadMaxAreaEmbolsado, int *capacidadMaxBolsa,
        char *modalidad){

    int opcion = 0;

    do{
        printf("Opciones:\n"
               "1 Ejecutar la simulacion\n"
               "2 Cambiar las opciones de la simulacion\n"
               "3 Salir del programa\n\n"
               "Seleccione una opcion:\n");

        scanf("%d", &opcion);

        fflush(stdin);

        if(!isdigit(opcion))
        {
            printf("Para ver (d, &opcion): %d\n", &opcion);
            opcion = 4;
            printf("Para ver (d, opcion): %d\n", opcion);

        }


        if(opcion == 1 || opcion == 2 || opcion == 3)
        {
            if(opcion == 2)
            {
                printf("\n");
                Menu2(&carritos, &cantidadMaxCarrito, &capacidadMaxBanda,
                      &velocidadCajera, &velocidadEmbolsador,
                      &tiempoFacturacion, &capacidadMaxAreaEmbolsado,
                      &capacidadMaxBolsa, &modalidad);
            }
        }

        else
        {
            printf("ERROR, Opcion invalida.\n"
                   "Usted escogio: %d.\n"
                   "Por favor, intente nuevamente.\n\n", opcion);
        }

        printf("\n");

    }while(opcion != 1 && opcion != 3);
}

void Menu2(int **carritos, int **cantidadMaxCarrito, int **capacidadMaxBanda,
        int **velocidadCajera, int **velocidadEmbolsador, int **tiempoFacturacion,
        int **capacidadMaxAreaEmbolsado, int **capacidadMaxBolsa,
        char **modalidad){

    int opcion = 0;

    do{
        printf("Configuracion de la simulacion.\n\n"

               "Valores actuales:\n"
               "Modalidad: %c\n"
               "Cantidad de carritos en la cola: %d\n"
               "Cantidad máxima de productos que puede tener un carrito: %d\n"
               "Capacidad máxima de la banda transportadora: %d\n"
               "Velocidad de la cajera: %d\n"
               "Velocidad del embolsador: %d\n"
               "Tiempo de facturación: %d\n"
               "Capacidad máxima del área de embolsado: %d\n"
               "Capacidad máxima de una bolsa: %d\n\n"

               "Valores por defecto: \n"
               "Modalidad: 'i' (interactiva)\n"
               "Cantidad de carritos en la cola: 3\n"
               "Cantidad máxima de productos que puede tener un carrito: 30\n"
               "Capacidad máxima de la banda transportadora: 200 (cc)\n"
               "Velocidad de la cajera: 1 (ops)\n"
               "Velocidad del embolsador: 4 (spb)\n"
               "Tiempo de facturación: 130 (s)\n"
               "Capacidad máxima del área de embolsado: 150 (cc)\n"
               "Capacidad máxima de una bolsa: 120 (cc)\n\n"

               "cc: centimetros cubicos\n"
               "ops: operaciones por segundo\n"
               "spb: segundos por bolsa\n"
               "s: segundos\n\n"

               "Opciones:\n"
               "1 Cambiar algun valor de la configuracion.\n"
               "2 Salir del menu.\n\n", **modalidad, **cantidadMaxCarrito,
                **capacidadMaxBanda, **capacidadMaxBanda, **velocidadCajera,
                **velocidadEmbolsador, **tiempoFacturacion,
                **capacidadMaxAreaEmbolsado, **capacidadMaxBolsa);

        scanf("%d", &opcion);

        fflush(stdin);

        if(opcion == 1)
        {
            printf("\n");
            Menu3(&carritos, &cantidadMaxCarrito, &capacidadMaxBanda,
                  &velocidadCajera, &velocidadEmbolsador,
                  &tiempoFacturacion, &capacidadMaxAreaEmbolsado,
                  &capacidadMaxBolsa, &modalidad);
        }

        else if(opcion != 2)
        {
            printf("ERROR, Opcion invalida.\n"
                   "Usted escogio: %d.\n"
                   "Por favor, intente nuevamente.\n\n", opcion);
        }

        printf("\n");

    }while(opcion != 2);
}

void Menu3(int ***carritos, int ***cantidadMaxCarrito, int ***capacidadMaxBanda,
        int ***velocidadCajera, int ***velocidadEmbolsador,
        int ***tiempoFacturacion, int ***capacidadMaxAreaEmbolsado,
        int ***capacidadMaxBolsa, char ***modalidad){

    int opcion = 0;

    do{

        printf("¿Que valor desea cambiar?\n\n"

               "1 Modalidad.\n"
               "2 Cantidad de carritos en la cola.\n"
               "3 Cantidad máxima de productos que puede tener un carrito.\n"
               "4 Capacidad máxima de la banda transportadora.\n"
               "5 Velocidad de la cajera.\n"
               "6 Velocidad del embolsador.\n"
               "7 Tiempo de facturación.\n"
               "8 Capacidad máxima del área de embolsado.\n"
               "9 Capacidad máxima de una bolsa.\n"
               "10 Salir del menu.\n");

        scanf("%d", &opcion);

        fflush(stdin);

        printf("\n");

        switch(opcion)
        {
            case 1:
            {
                Modal(&modalidad);
                break;
            }

            case 2:
            {
                CanCarritos(&carritos);
                break;
            }

            case 3:
            {
                ProducMaxCarrito(&cantidadMaxCarrito);
                break;
            }

            case 4:
            {
                CapMaxBanda(&capacidadMaxBanda);
                break;
            }

            case 5:
            {
                VeloCajera(&velocidadCajera);
                break;
            }

            case 6:
            {
                VeloEmbolsador(&velocidadEmbolsador);
                break;
            }

            case 7:
            {
                TempFacturacion(&tiempoFacturacion);
                break;
            }

            case 8:
            {
                CapMaxAreaEmbolsado(&capacidadMaxAreaEmbolsado);
                break;
            }

            case 9:
            {
                CapMaxBolsa(&capacidadMaxBolsa);
                break;
            }

            case 10:
            {
                return;
            }

            default:
            {
                printf("ERROR, Opcion invalida.\n"
                       "Usted escogio: %d.\n"
                       "Por favor, intente nuevamente.\n\n", opcion);
            }
        }

    }while(TRUE);
}

void Modal(char ****modalidad){

    int opcion = 0;

    do{

        printf("Cambiar modalidad:\n\n"

               "1 Interactivo.\n"
               "2 Automatico.\n\n"

               "Seleccione una opcion:\n");

        scanf("%d", &opcion);

        fflush(stdin);

        if(opcion == 1)
        {
            ****modalidad = 'i';
        }

        else if(opcion == 2)
        {
            ****modalidad = 'a';
        }

        else
        {
            printf("ERROR, Opcion invalida.\n"
                   "Usted escogio: %d.\n"
                   "Por favor, intente nuevamente.\n\n", opcion);
        }

        printf("\n");

    }while(opcion != 1 && opcion != 2);
}

void CanCarritos(int ****carritos){

    int opcion = 0;

    do{

        printf("Indique la cantidad de carritos de mercado:\n");

        scanf("%d", &opcion);

        fflush(stdin);

        if(opcion > 0)
        {
            ****carritos = opcion;
        }

        else
        {
            printf("ERROR, Valor invalido.\n"
                   "Usted ingreso: %d.\n"
                   "Por favor, intente nuevamente.\n\n", opcion);
        }

        printf("\n");

    }while(opcion < 1);
}

void ProducMaxCarrito(int ****cantidadMaxCarrito){

    int opcion = 0;

    do{

        printf("Indique la cantidad maxima de productos que puede tener un\n"
               "carrito de mercado:\n");

        scanf("%d", &opcion);

        fflush(stdin);

        if(opcion > 1)
        {
            ****cantidadMaxCarrito = opcion;
        }

        else
        {
            printf("ERROR, Valor invalido.\n"
                   "Usted ingreso: %d.\n"
                   "Por favor, intente nuevamente.\n\n", opcion);
        }

        printf("\n");

    }while(opcion < 1);
}

void CapMaxBanda(int ****capacidadMaxBanda){

    int opcion = 0;
    int temp = ****capacidadMaxBanda;

    do{

        printf("Indique la capacidad maxima de la banda transportadora.\n"
               "Debe ser un valor mayor a %d\n", temp);

        scanf("%d", &opcion);

        fflush(stdin);

        if(opcion >= temp)
        {
            ****capacidadMaxBanda = opcion;
        }

        else
        {
            printf("ERROR, Valor invalido.\n"
                   "Usted ingreso: %d.\n"
                   "Por favor, intente nuevamente.\n\n", opcion);
        }

        printf("\n");

    }while(opcion < 1);
}

void VeloCajera(int ****velocidadCajera){

    int opcion = 0;

    do{

        printf("Indique la velocidad de la cajera:\n");

        scanf("%d", &opcion);

        fflush(stdin);

        if(opcion > 1)
        {
            ****velocidadCajera = opcion;
        }

        else
        {
            printf("ERROR, Valor invalido.\n"
                   "Usted ingreso: %d.\n"
                   "Por favor, intente nuevamente.\n\n", opcion);
        }

        printf("\n");

    }while(opcion < 1);
}

void VeloEmbolsador(int ****velocidadEmbolsador){

    int opcion = 0;

    do{

        printf("Indique la velocidad del embolsador:\n");

        scanf("%d", &opcion);

        fflush(stdin);

        if(opcion > 1)
        {
            ****velocidadEmbolsador = opcion;
        }

        else
        {
            printf("ERROR, Valor invalido.\n"
                   "Usted ingreso: %d.\n"
                   "Por favor, intente nuevamente.\n\n", opcion);
        }

        printf("\n");

    }while(opcion < 1);
}

void TempFacturacion(int ****tiempoFacturacion){

    int opcion = 0;

    do{

        printf("Indique el tiempo de facturacion:\n");

        scanf("%d", &opcion);

        fflush(stdin);

        if(opcion > 1)
        {
            ****tiempoFacturacion = opcion;
        }

        else
        {
            printf("ERROR, Valor invalido.\n"
                   "Usted ingreso: %d.\n"
                   "Por favor, intente nuevamente.\n\n", opcion);
        }

        printf("\n");

    }while(opcion < 1);
}

void CapMaxAreaEmbolsado(int ****capacidadMaxAreaEmbolsado){

    int opcion = 0;

    do{

        printf("Indique la capacidad maxima del area de embolsado:\n");

        scanf("%d", &opcion);

        fflush(stdin);

        if(opcion > 1)
        {
            ****capacidadMaxAreaEmbolsado = opcion;
        }

        else
        {
            printf("ERROR, Valor invalido.\n"
                   "Usted ingreso: %d.\n"
                   "Por favor, intente nuevamente.\n\n", opcion);
        }

        printf("\n");

    }while(opcion < 1);
}

void CapMaxBolsa(int ****capacidadMaxBolsa){

    int opcion = 0;

    do{

        printf("Indique la capacidad maxima de una bolsa:\n");

        scanf("%d", &opcion);

        fflush(stdin);

        if(opcion > 1)
        {
            ****capacidadMaxBolsa = opcion;
        }

        else
        {
            printf("ERROR, Valor invalido.\n"
                   "Usted ingreso: %d.\n"
                   "Por favor, intente nuevamente.\n\n", opcion);
        }

        printf("\n");

    }while(opcion < 1);
}

int main(int argc, char *argv[]){

    char modalidad = 'i';                // cambia lo que se muestra en la consola y en el archvo final
    int velocidadCajera = 1;             // velocidad de la cajera en operaciones or segundo
    int velocidadEmbolsador = 4;         // velocidad del embolsador en segundos por bolsa
    int tiempoFacturacion = 130;         // tiempo de facturacion en segundos
    int cantidadMaxCarrito = 30;         // capacidad de almacenaje de un carrito
    int capacidadMaxAreaEmbolsado = 150; // capacidad del area de embolsado en centimetros cubicos
    int capacidadMaxBolsa = 120;         // caacidad maxima de una bolsa en centimetros cubicos
    int capacidadMaxBanda = 0;
    int carritos = 3;
    int CantidadMaxCarrito = 12;
    int instantesTiempoCliente = 0;       // Contar los instantes de tiempo por cliente
    int instantesTiempoTotal = 0;         // Contar los instantes de tiempo en total
    int lines = 0;
    int random;                          // cantidad de productos que vamos a agarrar por cada carrito
    int random2;                         // producto a agarrar por cada iteracion

    Producto *arrayProductos;            // Apunta al inicio del arreglo
    Producto *copiaArrayProductos;       // Copia de la direccion en donde comienza la lista de productos

    //queue* cola = create_queue();        // creamos la cola donde guardamos todas las pilas de carros

    /* CREO QUE ERAN DOS LOS ARGUMENTOS... CREO
       PARA VER SI ASI SE LE QUITA UN WARNING DEL CARRIZO QUE SALE DEL MAKEFILE*/
    if(argc != 2)
    {
        printf("ERROR:\nCantidad de argumentos de entrada incorrectos\n\n"
               "Deben ser 2, usted ingreso %d\n el programa se cerrara", argc);
    }

    // lines contiene el numero de lineas en el archivo
    if((lines = countlines(argv[1])) == 0)
    {
        printf("Error en la lectura\nel programa se cerrara"); //¿es mejor decir que el archivo esta vacio?

        return 0;
    }

    printf("LINES: %d\n",lines);
    printf("Lineas \n");

    // Recibimos la direccion donde comienza el arreglo
    arrayProductos = readd(lines,argv[1],capacidadMaxBanda, capacidadMaxAreaEmbolsado);
    //printf("-----%d\n",(*arrayProductos).size );
    copiaArrayProductos = arrayProductos;
    //printf("-----%s\n",(*copiaArrayProductos).name);

    Menu(&carritos, &cantidadMaxCarrito, &capacidadMaxBanda,
                      &velocidadCajera, &velocidadEmbolsador,
                      &tiempoFacturacion, &capacidadMaxAreaEmbolsado,
                      &capacidadMaxBolsa, &modalidad);

    srand(time(NULL));

    queue* cola = create_queue(); // creamos la cola donde guardamos todas las pilas de carros

    for(int i = 0; i < carritos; i++) // iteramos por cada  carrito de cada cliente
    {
        random = (rand() % CantidadMaxCarrito) + 1; // seleccionamos al azar la cantidad de productos que va a tener el carrito de cada cliente
        printf("RANDOM 1: %d\n",random );
        printf("LISTA %d------------------\n",i+1 );
        node *lista = createList();

        for(int j = 0; j < random; j++)
        {
            random2 = (rand() % lines) + 1; // escogemos de manera al azar los productos que va a tener cada carrito
            //printf("RANDOM 2 :%d\n",random2 );
            arrayProductos = copiaArrayProductos;

            for(int k = 0; k < lines; k++)
            {
                // metemos los productos en la lista ordenada
                if((*arrayProductos).num == random2)
                {
                    insert((&lista),(*arrayProductos));
                    printf("NAME %s\n",(*arrayProductos).name );
                    break;
                }

                arrayProductos++;
            }
        }

        printf("IMPRIMOS LISTA++++++++ %d\n",i+1 );
        //printList(lista);

        // los pasamos ya ordenado de mayor a menor a la pila (el carrito)

        stack *pila = create_stack();

        while(lista != NULL)
        {
            printf("Nombre: %s  size %d complex %d num %d\n",lista->product.name,lista->product.size,lista->product.complex,lista->product.num);
            push(pila, lista->product); // empilamos los productos al carrito
            lista = lista->next;
            //printf("SIZE %d\n", pila->size );
        }
        // ponemos al cliente a hacer la cola de la caja de acuerdo al orden de llegada

        enqueue(cola, pila); //guardamos la pila en la cola
        printf("SIZE DE LA COLA %d\n", cola->size );
    }

    // creamos la pila de embolsado
    stack *pilaEmbolsado;
    //pilaEmbolsado = create_stack();
    stack *pilaa;
    int finEmpaquetado = 0; // cero representa el false
    // cola de carritos != 0 y temporal del comprador != 0 y fin del empaquetado igual 1
    while((cola->size != 0) && (pilaa->size != 0) && (finEmpaquetado != 1)) // y embolsador termino de embolsar
    {
        // cola de carritos y la pila del ultimo carrito
        pilaEmbolsado = create_stack();
        pilaa = dequeue(cola); // guardamos la pila de productos del primer comprador
        int cajeraLibre = 1; // la cajera esta libre
        int tiempoFact = 0; // Tiempo que se tarda por cliente
        int embolsadorFull = 0; // el embolsador no esta full
        int finEmpaquetado = 0; // cero representa el false
        int temporalComplejidad;
        // Aqui se llena la banda cada ciclo antes de que la cajera tome el producto
        // se crea la cola de la banda transportadora
        colaa* colax = crecreate_queue();

        // atendemos a cada cliente
        while((pilaa->size != 0) && (finEmpaquetado != 1)) // y la banda transportadora este vacia
        {
            //int cantidadActualBanda = 0; // Cuenta el espacio almacenado de la banda
            //int finEmpaquetado = 0; // cero representa el false
            int llenarBanda = 0;
            int chequeo;
            Producto* produ;

            while(llenarBanda != 1)
            {
                // se llena la banda transportadora hasta su maxima capacidad posible
                chequeo = top(pilaa);
                if(((colax->ccEnBanda)+chequeo) <= capacidadMaxBanda)
                {
                    produ = pop(pilaa);
                    enenqueue(colax,*produ);
                }

                else
                {
                    llenarBanda = 1;
                }
            }
              // Si el embolsador tiene espacio, la cajera trabaja normal, en caso contrario para su trabajo
            if (embolsadorFull == 0) {
              if((cajeraLibre == 1) && (colax->size > 0))
              {
                  // procedemos a atender a la velocidad de la cajera
                  temporalComplejidad = 0;
                  produ = dedequeue(colax);
                  tiempoFact = tiempoFact + 1;

                  if(velocidadCajera < produ->complex)
                  {
                      temporalComplejidad = produ->complex - velocidadCajera;
                      cajeraLibre = 0;
                      //tiempoFact = tiempoFact + 1;
                      //usleep(velocidadCajera*1000000); // descansa un segundo o tiempo de la cajera (para 2do caso poner la variable dentro del sleep)
                      usleep(1000000);
                  }

                  else if(velocidadCajera >= produ->complex)
                  {
                      //tiempoFact = tiempoFact + (produ.complex/velocidadCajera); // ya que la cajera es mas rapida que el tiempo de complejidad
                      //tiempoFact = tiempoFact + 1;
                      cajeraLibre = 1;
                      //usleep(velocidadCajera*1000000);
                      usleep(1000000);
                      // PASAMOS PRODUCTO AL EMBOLSADOR +++++
                  }
                }
                else if(cajeraLibre == 0)
                {
                  if(velocidadCajera < temporalComplejidad)
                  {
                    temporalComplejidad = temporalComplejidad - velocidadCajera;
                    cajeraLibre = 0;
                    //usleep(velocidadCajera*1000000); // descansa un segundo o tiempo de la cajera (para 2do caso poner la variable dentro del sleep)
                    usleep(1000000);
                    // PASAMOS PRODUCTO AL EMBOLSADOR +++++
                    push(pilaEmbolsado, *produ);
                  }
                  else if(velocidadCajera >= temporalComplejidad)
                  {
                      //tiempoFact = tiempoFact + (temporalComplejidad/velocidadCajera);
                      tiempoFact = tiempoFact + 1;
                      cajeraLibre = 1;
                      //usleep(velocidadCajera*1000000);
                      usleep(1000000);
                  }
              }
              // si la cajera esta libre en este punto es porque acaba de liberar el producto

              if (cajeraLibre == 1) {
                // agregamos a la pila del embolsador si el area del embolsador no esta full
                // creamos booleano si el area de embolsado esta full para que la cajera no siga agregando
                // productos al area del embolsado
                if (((pilaEmbolsado->ccEnEmbolsado)+produ->size) <= capacidadMaxAreaEmbolsado) {
                  push(pilaEmbolsado, *produ);
                  //embolsadorFull = 0;
                }
                else{
                  embolsadorFull = 1;
                }
              }
            }
            // si el embolsador esta full la cajera espera a que habra espacio
            else{
              usleep(1000000);
            }

            /*while ((pilaEmbolsado->size)!= 0) {
            }*/
        }
      }
  }
