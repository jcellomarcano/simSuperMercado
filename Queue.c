#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include<sys/wait.h> // wait
//#include <unistd.h> // fork

typedef struct prod{
   int num; // El numero del producto
   char name[15]; // Nombre del Producto
   int size; // tamano del producto
   int complex; // complejidad
}Producto;

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

colaa* crecreate_queue();
void enenqueue(colaa* q, Producto val);
int tope(colaa* q);
Producto* dedequeue(colaa*q);

int main(void) {

  char value, val;

  colaa* cola = crecreate_queue();

  Producto cafe;
  cafe.num= 0;
  strcpy(cafe.name,"cafe");
  cafe.size = 5;
  cafe.complex = 10;

  Producto queso;
  queso.num= 1;
  strcpy(queso.name,"queso");
  queso.size = 10;
  queso.complex = 15;

  Producto jam;
  jam.num = 2;
  strcpy(jam.name,"jamon");
  jam.size = 10;
  jam.complex = 15;

  Producto pan;
  pan.num= 3;
  strcpy(pan.name,"pan");
  pan.size = 12;
  pan.complex = 20;

  Producto cacao;
  cacao.num= 4;
  strcpy(cacao.name,"cacao");
  cacao.size = 15;
  cacao.complex = 21;

  enenqueue(cola, cafe);
  enenqueue(cola, queso);
  enenqueue(cola, jam);
  enenqueue(cola, pan);
  enenqueue(cola, cacao);

  //val = tope(cola);

  //printf("TOPE %c\n", val);

  tope(cola);
  dedequeue(cola);
  tope(cola);
  dedequeue(cola);
  tope(cola);
  dedequeue(cola);
  tope(cola);
  dedequeue(cola);
  tope(cola);
  dedequeue(cola);
  dedequeue(cola);

  printf("OCUPADO EN LA BANDA %d\n",cola->ccEnBanda );


  return 0;
}

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
