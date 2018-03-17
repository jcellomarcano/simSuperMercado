#include <stdio.h>
#include "supermercado.h"

int main(){
	
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

	Menu(&carritos, &cantidadMaxCarrito, &capacidadMaxBanda,
				      &velocidadCajera, &velocidadEmbolsador, 
				      &tiempoFacturacion, &capacidadMaxAreaEmbolsado, 
				      &capacidadMaxBolsa, &modalidad);

}