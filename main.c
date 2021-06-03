////////////////////////////////////////
/*
	FileName: main.c
	FileType: C source file
	Author: Sandoval Pérez, Michael Eduardo
	Created on: 02/06/2021
	Description: Creación de un arreglo dinámico donde cada uno de sus elementos contendrá una lista de matrices la cual contendrá una 
				 matriz y a su vez contendrá una matriz para cadenas de caracteres.
*/
////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MatrizCadena
{
	int x;		// Longitud Fila
	int y;		// Longitud Columna
	char ***matriz;  // Puntero que apunta a un arreglo de punteros que apuntan a cadenas de caracteres
};

typedef struct
{
	struct MatrizCadena matrizCadena;
}ListaMatrices;		// Contiene matrices de cadenas de caracteres

typedef struct
{
	ListaMatrices *listaMatrices;
}ArrayMatricesCadenas;		// Objeto que almacenará ListaMatrices

ListaMatrices *insertarDatos(int, int); //
void mostrarDatos(ListaMatrices*);

ArrayMatricesCadenas **crearArray(int); 	/* Función que devuelve un array de ArrayMatricesCadenas la cual recibe como parametro el 
											   tamaño del array. En C es imposible crear funciones que devuelvan arrays tipo 
											   corchetes [] por lo que es necesario el uso de punteros dobles ** los cuales apuntaran 
											   a un arreglo y nos permiten devolver arreglos. */

void mostrarArray(ArrayMatricesCadenas**, int);		/* Función que recibe un puntero doble (el cual recibe a un arreglo de 
													   tipo ArrayMatricesCadenas) el cual se encargará de imprimir los valores de cada
													   elemento del array, donde cada elemento contiene una matriz de cadenas de 
													   caracteres, es necesario especificar el tamaño del array. */
int main(int argc, char *argv[])
{
	int tam; 

	printf("Tamano del array: ");
	scanf("%d", &tam);

	ArrayMatricesCadenas **(*ptrCrearArray)(int) = &crearArray; 	// Puntero que apunta hacia la funcion crearArray

	ArrayMatricesCadenas **array = crearArray(tam);		// Creamos un puntero doble que almacenará un array de tipo ArrayMatricesCadenas
	mostrarArray(array, tam);	// Mostramos

	return 0;
}

ListaMatrices *insertarDatos(int _x, int _y)
{
	ListaMatrices *(lista) = (ListaMatrices*)malloc(sizeof(ListaMatrices)); // Reservamos memoria para un puntero tipo ListaMatrices
	
	(*lista).matrizCadena.x = _x;		// Almacenamos el tamaño de las filas
	(*lista).matrizCadena.y = _y;		// Almacenamos el tamaño de las columnas
	
	(*lista).matrizCadena.matriz = calloc((*lista).matrizCadena.x, sizeof(char**));		/* Reservamos memoria para la matriz o el puntero
																						   que apunta a un array de punteros (char**), en
																						   este caso reservamos un tamaño x (para las filas)*/
	for(int i = 0; i < (*lista).matrizCadena.x; i++) // Iteramos las filas
	{
		*((*lista).matrizCadena.matriz + i) = calloc((*lista).matrizCadena.y, sizeof(char*));  /* Reservamos memoria para cada matriz[i] en
																								  sus columnas de tamaño "y", en mejores 
																								  terminos, a cada puntero o elemento del 
																								  array de punteros se le esta reservando
																								  memoria  para almacenar "y" cantidad de
																								  cadenas de caracteres */					 	
		for(int j = 0; j < (*lista).matrizCadena.y; j++)	// Iteramos las columnas
		{
			*( *( (*lista).matrizCadena.matriz + i) + j ) = malloc( sizeof(char) * ( (*lista).matrizCadena.x * (*lista).matrizCadena.y) );
			/*
			   Reservamos memoria para cada cadena de caracteres de cada columna de las "y" columnas pertenecientes a cada fila "x" 
			   las cuales serán de ("x" * "y) caracteres. 
			*/
			printf("Dato [%d][%d]: ", i, j);
			getchar();
			scanf("%30[0-9a-zA-Z ]", *(*((*lista).matrizCadena.matriz + i) + j));		/* Insertamos un dato tipo cadena a matriz[i][j] 
																						   pero no sin antes validar una expresión 
																						   regular que nos permitirá mas que 
																						   nada insertar una cadena de longitud 30 la cual
																						   puede contener números y espacios en blanco,
																						   poner unicamente el %s podria provocar errores 
																						   lógicos */
		}
	}

	return lista; 	// Retornamos una ListaMatrices
}

void mostrarDatos(ListaMatrices* lista)		// Recibe la ListaMatrices creada en insertarDatos
{
	for(int i = 0; i < (*lista).matrizCadena.x; i++)		// Itera las filas
	{
		printf("|");		// Delimitador improvisado 
		for(int j = 0; j < (*lista).matrizCadena.y; j++)	// Itera las columnas
		{
			printf(" %s |", *( *( (*lista).matrizCadena.matriz + i) + j) );		// Imprime matriz[i][j]
		}	
		printf("\n");
		free(*((*lista).matrizCadena.matriz + i));	// Liberamos la memoria reservada para matriz[i] o para cada puntero del array de punteros
	}
	printf("\n");

	free((*lista).matrizCadena.matriz);		// Liberamos la memoria reservaada para el puntero que apuntaba al array de punteros
	free(lista);		// Liberamos la memoria reservada para la ListaMatrices
}

ArrayMatricesCadenas **crearArray(int n)
{
	int posX, posY, i = 0;

	ArrayMatricesCadenas **(array);		// Creamos el array puntero doble o arreglo de ArrayMatricesCadenas
	ListaMatrices *(*ptrInsertarDatos)(int, int) = &insertarDatos; // Creamos un puntero para la función insertarDatos

	printf("\n\nInsertando matrices al array.\n");

	array = calloc(n, sizeof(ArrayMatricesCadenas*));	/* Reservamos memoria para el array de las matrices que tendra n elementos,
														   cada elemento del arreglo apuntara a una ListaMatrices*/
	while(i < n)		
	{
		*(array + i) = malloc(sizeof(ArrayMatricesCadenas));	/* Reserva memoria para cada array[i] o cada puntero de ArrayMatricesCadenas,
																   cada puntero apuntará a una ListaMatrices, cada puntero ListaMatrices
																   apuntará a una MatrizCadena y esta almacenara una matriz de cadenas de
																   caracteres. */ 
		printf("\nMatriz [%d]: \n", i);
		printf("Ingresa la cantidad de filas: ");
		scanf("%d", &posX);		// Insertamos "x" 
		printf("Ingresa la cantidad de columnas: ");
		scanf("%d", &posY);		// Insertamos "y"
		
		(*array[i]).listaMatrices = ptrInsertarDatos(posX, posY); /* Insertamos una listaMatrices en el elemento[posición i],
																	 al mismo tiempo llamamos a ptrInsertarDatos el cual creara
																	 la ListaMatrices y a su vez a cada matriz, reservando la
																	 respectiva memoria de ambas. */
		i++;
	}

	return array;	// Retornamos el arreglo con sus elementos
}

void mostrarArray(ArrayMatricesCadenas** array, int n)	// Recibimos un arreglo tipo ArrayMatricesCadenas y el tamaño n
{
	printf("\n\nArray de matrices\n");

	int i = 0;
	while(i < n)
	{
		printf("\nMatriz [%d]\n", i);
		mostrarDatos((*array[i]).listaMatrices);	/* Imprime los datos y a su vez liberará la memoria de cada listaMatrices 
													   y a su vez de cada una de las matrices. */
		free(*(array + i));			// Liberamos la memoria reservada para cada puntero o elemento del array[i]
		i++;
	}
	free(array);	// Liberamos la memoria reservada para el arreglo ArrayMatricesCadenas
}
