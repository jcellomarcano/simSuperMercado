 /*Menu*/

/* librerias */
#include <stdio.h>

/* constantes */
#define TRUE 0 == 0

/* Prototipos de funciones */

/* Menu de configuracion de la simulacion */
void Menu2(int *carritos, int *cantidadMaxCarrito, int *capacidadMaxBanda,
	    int *velocidadCajera, int *velocidadEmbolsador, int *tiempoFacturacion,
	    int *capacidadMaxAreaEmbolsado, int *capacidadMaxBolsa, 
	    char *modalidad);

/* Menu para cambiar algun valor de la configuracion */
void Menu3(int **carritos, int **cantidadMaxCarrito, int **capacidadMaxBanda,
	    int **velocidadCajera, int **velocidadEmbolsador, 
	    int **tiempoFacturacion, int **capacidadMaxAreaEmbolsado, 
	    int **capacidadMaxBolsa, char **modalidad);

void Modal(char ***modalidad);

void CanCarritos(int ***carritos);

void ProducMaxCarrito(int ***cantidadMaxCarrito);

void CapMaxBanda(int ***capacidadMaxBanda);

void VeloCajera(int ***velocidadCajera);

void VeloEmbolsador(int ***velocidadEmbolsador);

void TempFacturacion(int ***tiempoFacturacion);

void CapMaxAreaEmbolsado(int ***capacidadMaxAreaEmbolsado);

void CapMaxBolsa(int ***capacidadMaxBolsa);


/*
 * Descripcion:
 * Pre condicion:
 * Parametros:
 * Retorna:
 * Post condicion:
 */

int main(){

	/* Variables */

	int opcion = 0;                      // Para  el menu
	char modalidad = 'i';                // cambia lo que se muestra en la consola y en el archvo final
	int carritos = 3;                    // cantidad  de carritos en la cola
	int cantidadMaxCarrito = 30;         // capacidad de almacenaje de un carrito
	int capacidadMaxBanda = 200;         // cantidad maxima de la banda transportadora en centimetros cubicos
	int velocidadCajera = 1;             // velocidad de la cajera en operaciones or segundo
	int velocidadEmbolsador = 4;         // velocidad del embolsador en segundos por bolsa
	int tiempoFacturacion = 130;         // tiempo de facturacion en segundos
	int capacidadMaxAreaEmbolsado = 150; // capacidad del area de embolsado en centimetros cubicos
	int capacidadMaxBolsa = 120;         // caacidad maxima de una bolsa en centimetros cubicos

	do{
		printf("Opciones:\n"
			   "1 Ejecutar la simulacion\n"
			   "2 Cambiar las opciones de la simulacion\n"
			   "3 Salir del programa\n\n"
			   "Seleccione una opcion:\n");

		scanf("%d", &opcion);

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

	return 0;

}

/*
 * Descripcion:
 * Pre condicion:
 * Parametros:
 * Retorna:
 * Post condicion:
 */

void Menu2(int *carritos, int *cantidadMaxCarrito, int *capacidadMaxBanda,
	    int *velocidadCajera, int *velocidadEmbolsador, int *tiempoFacturacion,
	    int *capacidadMaxAreaEmbolsado, int *capacidadMaxBolsa, 
	    char *modalidad){

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
			   "2 Salir del menu.\n\n", *modalidad, *cantidadMaxCarrito,
			    *capacidadMaxBanda, *capacidadMaxBanda, *velocidadCajera,
			    *velocidadEmbolsador, *tiempoFacturacion,
			    *capacidadMaxAreaEmbolsado, *capacidadMaxBolsa);

		scanf("%d", &opcion);

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

/*
 * Descripcion:
 * Pre condicion:
 * Parametros:
 * Retorna:
 * Post condicion:
 */

void Menu3(int **carritos, int **cantidadMaxCarrito, int **capacidadMaxBanda,
	    int **velocidadCajera, int **velocidadEmbolsador, 
	    int **tiempoFacturacion, int **capacidadMaxAreaEmbolsado, 
	    int **capacidadMaxBolsa, char **modalidad){

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

/*
 * Descripcion:
 * Pre condicion:
 * Parametros:
 * Retorna:
 * Post condicion:
 */

void Modal(char ***modalidad){

	int opcion = 0;

	do{

		printf("Cambiar modalidad:\n\n"

			   "1 Interactivo.\n"
			   "2 Automatico.\n\n"

			   "Seleccione una opcion:\n");

		scanf("%d", &opcion);

		if(opcion == 1)
		{
			***modalidad = 'i';
		}

		else if(opcion == 2)
		{
			***modalidad = 'a';
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

/*
 * Descripcion:
 * Pre condicion:
 * Parametros:
 * Retorna:
 * Post condicion:
 */

void CanCarritos(int ***carritos){

	int opcion = 0;

	do{

		printf("Indique la cantidad de carritos de mercado:\n");

		scanf("%d", &opcion);

		if(opcion > 0)
		{
			***carritos = opcion;
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

/*
 * Descripcion:
 * Pre condicion:
 * Parametros:
 * Retorna:
 * Post condicion:
 */

void ProducMaxCarrito(int ***cantidadMaxCarrito){

	int opcion = 0;

	do{

		printf("Indique la cantidad maxima de productos que puede tener un\n"
			   "carrito de mercado:\n");

		scanf("%d", &opcion);

		if(opcion > 1)
		{
			***cantidadMaxCarrito = opcion;
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

/*
 * Descripcion:
 * Pre condicion:
 * Parametros:
 * Retorna:
 * Post condicion:
 */

void CapMaxBanda(int ***capacidadMaxBanda){

	int opcion = 0;

	do{

		printf("Indique la capacidad maxima de la banda transportadora:\n");

		scanf("%d", &opcion);

		if(opcion > 1)
		{
			***capacidadMaxBanda = opcion;
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

/*
 * Descripcion:
 * Pre condicion:
 * Parametros:
 * Retorna:
 * Post condicion:
 */

void VeloCajera(int ***velocidadCajera){

	int opcion = 0;

	do{

		printf("Indique la velocidad de la cajera:\n");

		scanf("%d", &opcion);

		if(opcion > 1)
		{
			***velocidadCajera = opcion;
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

/*
 * Descripcion:
 * Pre condicion:
 * Parametros:
 * Retorna:
 * Post condicion:
 */

void VeloEmbolsador(int ***velocidadEmbolsador){

	int opcion = 0;

	do{

		printf("Indique la velocidad del embolsador:\n");

		scanf("%d", &opcion);

		if(opcion > 1)
		{
			***velocidadEmbolsador = opcion;
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

/*
 * Descripcion:
 * Pre condicion:
 * Parametros:
 * Retorna:
 * Post condicion:
 */

void TempFacturacion(int ***tiempoFacturacion){

	int opcion = 0;

	do{

		printf("Indique el tiempo de facturacion:\n");

		scanf("%d", &opcion);

		if(opcion > 1)
		{
			***tiempoFacturacion = opcion;
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

/*
 * Descripcion:
 * Pre condicion:
 * Parametros:
 * Retorna:
 * Post condicion:
 */

void CapMaxAreaEmbolsado(int ***capacidadMaxAreaEmbolsado){

	int opcion = 0;

	do{

		printf("Indique la capacidad maxima del area de embolsado:\n");

		scanf("%d", &opcion);

		if(opcion > 1)
		{
			***capacidadMaxAreaEmbolsado = opcion;
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

/*
 * Descripcion:
 * Pre condicion:
 * Parametros:
 * Retorna:
 * Post condicion:
 */

void CapMaxBolsa(int ***capacidadMaxBolsa){

	int opcion = 0;

	do{

		printf("Indique la capacidad maxima de una bolsa:\n");

		scanf("%d", &opcion);

		if(opcion > 1)
		{
			***capacidadMaxBolsa = opcion;
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