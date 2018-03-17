
// Conjunto de funciones y estructuras que utiliza el 

/* Estructuras */

/* Prototipos de funciones */

void Menu(int *carritos, int *cantidadMaxCarrito, int *capacidadMaxBanda,
	    int *velocidadCajera, int *velocidadEmbolsador, int *tiempoFacturacion,
	    int *capacidadMaxAreaEmbolsado, int *capacidadMaxBolsa, 
	    char *modalidad);

/* Menu de configuracion de la simulacion */
void Menu2(int **carritos, int **cantidadMaxCarrito, int **capacidadMaxBanda,
	    int **velocidadCajera, int **velocidadEmbolsador, int **tiempoFacturacion,
	    int **capacidadMaxAreaEmbolsado, int **capacidadMaxBolsa, 
	    char **modalidad);

/* Menu para cambiar algun valor de la configuracion */
void Menu3(int ***carritos, int ***cantidadMaxCarrito, int ***capacidadMaxBanda,
	    int ***velocidadCajera, int ***velocidadEmbolsador, 
	    int ***tiempoFacturacion, int ***capacidadMaxAreaEmbolsado, 
	    int ***capacidadMaxBolsa, char ***modalidad);

void Modal(char ****modalidad);

void CanCarritos(int ****carritos);

void ProducMaxCarrito(int ****cantidadMaxCarrito);

void CapMaxBanda(int ****capacidadMaxBanda);

void VeloCajera(int ****velocidadCajera);

void VeloEmbolsador(int ****velocidadEmbolsador);

void TempFacturacion(int ****tiempoFacturacion);

void CapMaxAreaEmbolsado(int ****capacidadMaxAreaEmbolsado);

void CapMaxBolsa(int ****capacidadMaxBolsa);