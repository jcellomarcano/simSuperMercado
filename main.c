#include<stdio.h>
#include <string.h>
#include <stdlib.h>
# include <time.h>

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
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 0;
    }

    // Extract characters from file and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp)){
        if (c == '\n'){
            count = count + 1;
        }
    }
    // Close the file
    fclose(fp);
    //printf("The file %s has %d lines\n ", filename, count);

    return count;
};
Producto* read(int numLines, char *filename){
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

  if (file == NULL){
		exit(EXIT_FAILURE);
  }

	while ((read = getline(&line, &len, file)) != -1) {
		//printf("Retrieved line of length %zu :\n", read);
		//printf("%s", line);
    //line2 = line;
    // contamos la cantidad de tabs en la linea
    /* get the first token */
    //contador = contador+1;
    Producto newProduct;
    token = strtok(line,"\t");
    /* iteramos sobre los otros token */
    while( token != NULL ) {
      if (contador == 0) {
        numero = numero + 1;
        newProduct.num = numero; // es un producto nuevo, le registramos su numero
        strcpy(newProduct.name,token);
        //printf("NUMERO %d\n", newProduct.num);
        //printf("NOMBRE %s\n", newProduct.name);
      }
      if (contador == 1) {
        newProduct.size = atoi(token);
        //printf("TAMANO %d\n",newProduct.size);
      }
      if (contador == 2) {
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
	//exit(EXIT_SUCCESS);

}
typedef struct node_{
    Producto product;
    struct node_ *next;
}node;
// ----------------------------------------------------------------- SORTED LIST

node* createList()
{
	node *l = NULL;
	return l;
}

/* Pone nod en list según el orden alfabetico del campo dato.name */
void put( node** list, node* nod )
{
    if( *list == NULL || ( nod->product.size - (*list)->product.size ) >= 0 ){
        nod->next = *list;
        *list = nod;
    }
    else {
       node* p = *list;
       while( p->next != NULL && (nod->product.size - p->next->product.size) < 0 )
       {
           p = p->next;
        }

       nod->next = p->next;
       p->next = nod;
    }
}

/* Crea un nodo con nodo->dato == e y lo ponee en list *
 * en orden alfabetico según el campo dato.name.    *
 * Retorna 1 si se insert con éxito y 0 si no.       */
int insert( node** list, Producto p )
{
    int r; /* valor de retorno */

    /* crear nuevo nodo */
    node* pNuevo = malloc( sizeof(*pNuevo));

    /* puntero en la lista */
    if( r = pNuevo != NULL ) {
        pNuevo->product = p;
        put( list, pNuevo );
    }

    return r;
}

void printList( node* pActual )
{

   /* Mientras no sea el final de la lista */
   while ( pActual != NULL ) {
      printf("Nombre: %s  size %d complex %d num %d\n",pActual->product.name,pActual->product.size,pActual->product.complex,pActual->product.num);
      pActual = pActual->next;
   }
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ PILA
typedef struct stack_{
    unsigned int size;
    node* head;
}stack;

stack* create_stack(){ //initializes the stack

    stack* pila = malloc (sizeof(stack));

    pila->size = 0;
    pila->head = NULL;

    return pila;

}

void push(stack* s, Producto pro) {

    node* temp = (node*)malloc(sizeof(node)); //allocates

    if ( temp == NULL ) {
        printf("No se puede asignar el espacio de memoria solicitado\n");
    }

    else{
        temp->next = s->head;
        temp->product = pro;
        s->head = temp;
        s->size = (s->size) + 1; //bumps the counter for how many elements are in the stack
    }

}

Producto* pop(stack* s) {

    if ((s->size) == 0) {
      printf("La pila esta vacia \n");
      return NULL;
    }
    else{
      node* temp;
      node* temp2;

      temp = s->head;
      s->head = temp->next;
      s->size = (s->size) - 1; //subtracts from counter
      temp2 = temp;
      //printf("%p\n", &(temp2->product));
      //Producto casa = (temp2->product);
      //printf("%s\n", casa.name);
      free(temp);
      //printf("%s\n", casa.name);
      //printf("%p\n",&(temp2->product) );
      return &(temp2->product);
    }


}

void top(stack* s) {
  if ((s->size) == 0) {
    printf("La pila esta vacia \n");
  }

  else{
    node* temp = s->head;

    Producto value = temp->product;
    printf("%s\n",value.name );
  }
}


// ---------------------------------------------------- COLA DE PILAS (CARRITOS)
typedef struct NODE_{
    stack* pila;
    struct NODE_ *next;
    struct NODE_ *prev;
}NODE;

typedef struct queue_{
    unsigned int size;
    NODE* head;
    NODE* tail;
}queue;

queue* create_queue(){ //initializes the queue

    queue* cola = malloc (sizeof(queue));

    cola->size = 0;
    cola->head = NULL;
    cola->tail = NULL;

    return cola;

}

void enqueue(queue* q, stack* pila) {

    NODE* temp = (NODE*)malloc(sizeof(NODE)); //allocates

    if ( temp == NULL ) {
        printf("Unable to allocate memory\n");
    }
    else if ((q->size) == 0) {
      temp->next = q->head;
      temp->pila = pila;
      //printf("POINTER INTERNO 1%p\n",temp->pila );
      //(temp->next)->prev = temp;
      q->head = temp;
      q->head->next = NULL;
      q->tail = temp;
      q->tail->next = NULL;
      q->size = (q->size) + 1; //bumps the counter for how many elements are in the queue
    }
    else{
      temp->next = q->tail;
      q->tail->prev = temp;
      temp->pila = pila;
      q->tail = temp;
      q->size = (q->size) + 1; //bumps the counter for how many elements are in the queue
    }

}

stack* dequeue(queue* q) {
  int salida = 0;
    if ((q->size) == 0) {
      printf("La cola esta vacia \n");
      return NULL;
    }
    else{
      NODE* temp;
      stack* temp2;

      temp = q->head;
      temp2 = temp->pila;
      //printf("APUUUUNTAAA %p\n",temp2);
      q->head = q->head->prev;
      //printf("%p\n", &(temp2->pila));
      //stack casa = (temp2->pila);
      //printf("----%s\n", casa.name);
      //q->head = temp->next;
      free(temp);
      q->size = (q->size) - 1; //subtracts from counter
      return temp2;
    }
}

void main(int argc, char *argv[])
{
  Producto* arrayProductos; // Apunta al inicio del arreglo
  Producto* copiaArrayProductos; // Copia de la direccion en donde comienza la lista de productos
  int lines;
  // lines contiene el numero de lineas en el archivo
  lines = countlines(argv[1]);
  printf("LINES: %d\n",lines);
  printf("Lineas \n");
  // Recibimos la direccion donde comienza el arreglo
  arrayProductos = read(lines,argv[1]);
  //printf("-----%d\n",(*arrayProductos).size );
  copiaArrayProductos = arrayProductos;
  //printf("-----%s\n",(*copiaArrayProductos).name);

  int carritos = 3;
  int CantidadMaxCarrito = 5;
  int random; // cantidad de productos que vamos a agarrar por cada carrito
  int random2; // producto a agarrar por cada iteracion
  srand(time(NULL));
  queue* cola = create_queue(); // creamos la cola donde guardamos todas las pilas de carros
  for(int i = 0; i < carritos;i++){ // iteramos por cada  carrito de cada cliente
    random = (rand() % CantidadMaxCarrito) + 1; // seleccionamos al azar la cantidad de productos que va a tener el carrito de cada cliente
    printf("RANDOM 1: %d\n",random );
    printf("LISTA %d------------------\n",i+1 );
    node *lista = createList();
    for (int j = 0; j < random; j++) {
      random2 = (rand() % lines) + 1; // escogemos de manera al azar los productos que va a tener cada carrito
      //printf("RANDOM 2 :%d\n",random2 );
      arrayProductos = copiaArrayProductos;
      for (int k = 0; k < lines; k++) {
        // metemos los productos en la lista ordenada
        if ((*arrayProductos).num == random2) {
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

    stack* pila = create_stack();

    while ( lista != NULL ) {
       printf("Nombre: %s  size %d complex %d num %d\n",lista->product.name,lista->product.size,lista->product.complex,lista->product.num);
       push(pila, lista->product); // empilamos los productos al carrito
       lista = lista->next;
       //printf("SIZE %d\n", pila->size );
    }
    // ponemos al cliente a hacer la cola de la caja de acuerdo al orden de llegada

    enqueue(cola, pila); // le pasamos el apuntador a la pila, no el apuntador del apuntador a la pila
    //printf("SIZE DE LA COLA %d\n", cola->size );
  }

}
