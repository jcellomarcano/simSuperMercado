#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Cola de pilas

typedef struct prod{
   int num; // El numero del producto
   char name[15]; // Nombre del Producto
   int size; // tamano del producto
   int complex; // complejidad
}Producto;


typedef struct node_{
    Producto product;
    struct node_ *next;
}node;

typedef struct stack_{
    unsigned int size;
    node* head;
}stack;

stack* create_stack();
void push(stack* s, Producto val);
void top(stack* s);
Producto* pop(stack*s);


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

queue* create_queue();
void enqueue(queue* q, stack* val);
//void top(queue* q);
stack* dequeue(queue*q);

int main(void) {
  Producto queso;
  queso.num= 1;
  strcpy(queso.name,"queso");
  queso.size = 10;
  queso.complex = 15;

  Producto cafe;
  cafe.num= 0;
  strcpy(cafe.name,"cafe");
  cafe.size = 5;
  cafe.complex = 10;

  Producto pan;
  pan.num= 3;
  strcpy(pan.name,"pan");
  pan.size = 12;
  pan.complex = 20;

  stack* p = create_stack();
  stack* pi = create_stack();
  stack* pil = create_stack();
  printf("POINTER %p\n",p );
  push(p,queso);
  push(p,pan);
  push(pi,cafe);
  push(pil,pan);

  top(p);
  top(pi);
  top(pil);

  queue* c = create_queue();
  queue* co = create_queue();
  queue* cola = create_queue();

  enqueue(c,p);
  enqueue(co,pi);
  enqueue(cola,pil);

  stack* s;
  stack* st;
  stack* sta;

  s = dequeue(c);
  //printf("POINTER 2 %p\n",s );
  top(s);


/*
  char value, val;

  queue* cola = create_queue();

  stack cafe;
  cafe.num= 0;
  strcpy(cafe.name,"cafe");
  cafe.size = 5;
  cafe.complex = 10;

  stack queso;
  queso.num= 1;
  strcpy(queso.name,"queso");
  queso.size = 10;
  queso.complex = 15;

  stack jam;
  jam.num = 2;
  strcpy(jam.name,"jamon");
  jam.size = 10;
  jam.complex = 15;

  stack pan;
  pan.num= 3;
  strcpy(pan.name,"pan");
  pan.size = 12;
  pan.complex = 20;

  stack cacao;
  cacao.num= 4;
  strcpy(cacao.name,"cacao");
  cacao.size = 15;
  cacao.complex = 21;

  enqueue(cola, cafe);
  enqueue(cola, queso);
  enqueue(cola, jam);
  enqueue(cola, pan);
  enqueue(cola, cacao);

  //val = top(cola);

  //printf("TOPE %c\n", val);

  top(cola);
  dequeue(cola);
  top(cola);
  dequeue(cola);
  top(cola);
  dequeue(cola);
  top(cola);
  dequeue(cola);
  top(cola);
  dequeue(cola);
  dequeue(cola);
*/
  return 0;
}

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
      printf("POINTER INTERNO 1%p\n",temp->pila );
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
      printf("APUUUUNTAAA %p\n",temp2);
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

/*void top(queue* q) {
    if ((q->size) == 0) {
      printf("La cola esta vacia \n");
    }

    NODE* temp = q->head;

    stack value = temp->pila;
    //printf("%s\n",value.name );

}*/
