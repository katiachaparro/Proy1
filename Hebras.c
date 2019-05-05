#include "matriz.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct thread_data
{
   int	thread_id;
   int  *filas;
   int **arreglo;
   int maximo;
   int cantidad_hilos;
   int escalar;
};

void *TrabajoHilo(void *t)
{
   int i;
   long tid;
   if(t == NULL){printf("Parametro nulo");};
   struct thread_data *my_data;
   my_data = (struct thread_data *) t;
   tid = my_data->thread_id;
   for (i=0; i<my_data->maximo ; i++)
   {
	  my_data->arreglo[my_data->thread_id][i]= my_data->arreglo[my_data->thread_id][i]* (my_data->escalar);
   }

   my_data->thread_id = my_data->thread_id + my_data->cantidad_hilos;
   if(*my_data->filas < my_data->maximo-1 && my_data->thread_id< my_data->maximo ){

	   *my_data->filas = *my_data->filas +1;
	   TrabajoHilo(t);
   }
   pthread_exit((void*) tid);
}

int** matriz_x_escalar_thread(int tamano,int escalar,int hilos){
	int **matriz = matriz_create_modificado(tamano, 1);
	struct timeval t1_t, t2_t;
	struct thread_data arreglo[hilos];
	pthread_t thread[hilos];
    pthread_attr_t attr;
    int rc;
	long t;
	void *status;

   //tomo el tiempo antes de recorrer
	gettimeofday(&t1_t, NULL);

    pthread_attr_init(&attr);
	int filas = -1;
	for(t=0; t<hilos; t++) {
	   filas = filas + 1;
	   arreglo[t].arreglo = matriz;
	   arreglo[t].maximo = tamano;
	   arreglo[t].thread_id = t;
	   arreglo[t].filas = &filas;
	   arreglo[t].cantidad_hilos = hilos;
	   arreglo[t].escalar = escalar;
	   rc = pthread_create(&thread[t], &attr, TrabajoHilo, &arreglo[t]);
	   if (rc) {
	      printf("ERROR; al crear pthread_create() is %d\n", rc);
	      exit(-1);
	   }
     }
	   pthread_attr_destroy(&attr);
	   for(t=0; t<hilos; t++) {
	      rc = pthread_join(thread[t], &status);
	      if (rc) {
	         printf("ERROR; al crear from pthread_join() is %d\n", rc);
	         exit(-1);
	         }
	      }
		//tomo el tiempo despues de recorrer

		gettimeofday(&t2_t, NULL);

		double time_total_t=(t2_t.tv_sec - t1_t.tv_sec)+((t2_t.tv_usec - t1_t.tv_usec)/1000000.0);
		printf("Tiempo total de ejecucion en thread = %f seg\n",time_total_t);

		printf("Main: Hilo principal terminado.\n");


		char *archivo="result_threads.txt";
		imprimirMatriz(archivo,arreglo[0].arreglo,tamano);
		destroy(arreglo[0].arreglo,tamano);
		return arreglo[0].arreglo;
}


/*
int main(int argc, char *argv[]){
	int tamano = 15000;
	int escalar = 4;
	char *archivo="result.txt";


	int **matriz = matriz_x_escalar(tamano,escalar);
	if(matriz == NULL){printf("matriz nula");};
	imprimirMatriz(archivo,matriz,tamano);
	destroy(matriz,tamano);

	/*************************matriz thread*********************************/
	/*int tamano_t = 15000;
	int escalar_t = 4;
	int cant_hilo = 300;
	char *archivo_t="result_threads.txt";



	int ** matriz_t = matriz_x_escalar_thread(tamano_t,escalar_t,cant_hilo );
	if(matriz_t == NULL){printf("matriz nula");};
	imprimirMatriz(archivo_t,matriz_t,tamano_t);
	destroy(matriz_t,tamano_t);

	system("PAUSE");
	return 0;*/
}

