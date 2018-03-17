#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(void) {

  char value, val;

  stack* pila = create_stack();

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
  jam.num= 1;
  strcpy(jam.name,"ham");
  jam.size = 10;
  jam.complex = 15;

  push(pila, cafe);
  push(pila, queso);
  push(pila, jam);

  //val = top(pila);

  //printf("TOPE %c\n", val);
  top(pila);
  pop(pila);
  top(pila);
  pop(pila);
  top(pila);
  pop(pila);
  pop(pila);

  return 0;
}

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
