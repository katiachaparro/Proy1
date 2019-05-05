#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
int destroy(int** V,int tamp){
	int a;
	for(a=0;a<tamp;a++){
		free(V[a]);
	}
	free(V);
	return FALSE;
}
int** matriz_create(int tamano){
	int a;
	int i,j;
	int cont=0;
	//creo la matriz
	int** V = (int **)malloc(sizeof(int *)*tamano);
	if(V==NULL)return FALSE;
	//reservo espacio lugar para el arreglo
	for(a=0;a<tamano;a++){
		V[a]=(int*)malloc(sizeof(int)*tamano);
		if(V[a]==NULL)return FALSE;
	}
	//inicializo la matriz
	for (i=0;i<tamano;i++){
		for (j=0;j<tamano;j++){
			V[i][j]= cont;
			cont++;
		}
	}
	return V;
}

int** matriz_create_modificado(int tamano, int escalar){
	int a;
	int** V = (int **)malloc(sizeof(int *)*tamano);
	if(V==NULL)return FALSE;

	for(a=0;a<tamano;a++){
		V[a]=(int*)malloc(sizeof(int)*tamano);
		if(V[a]==NULL)return FALSE;
	}


	int i,j;
		int cont=0;
			for (i=0;i<tamano;i++){
				for (j=0;j<tamano;j++){
					V[i][j]= cont * escalar;
					cont++;
				}
			}

	return V;

}


int** matriz_x_escalar(int tam, int escalar){
	struct timeval t1, t2;
	if((tam==NULL)||(escalar==NULL)){
		printf("No ha ingresado correctamento los parametros\n");
		return FALSE;
	}

    if((tam!=0) && (escalar!=0)){
    	int **matriz = matriz_create(tam);
    	int i,j;
    	//tomo el tiempo antes de recorrer
    	gettimeofday(&t1, NULL);
    		for (i=0;i<tam;i++){
    			for (j=0;j<tam;j++){
    				matriz[i][j]= matriz[i][j]* escalar;
    			}
    		}
		//tomo el tiempo despues de recorrer
		gettimeofday(&t2, NULL);
		double time_total=(t2.tv_sec - t1.tv_sec)+((t2.tv_usec - t1.tv_usec)/1000000.0);
		printf("Tiempo total de ejecucion = %f seg\n",time_total);
		char *archivo="result.txt";
		imprimirMatriz(archivo,matriz,tam);
		destroy(matriz,tam);
    	return matriz;
    }
        printf("Los parametros deben ser numeros.Vuelva a intentarlo\n");


        return FALSE;
}


int imprimirMatriz(char *filename, int** matriz, int tam){
	int i,j;
    FILE *archivo = fopen(filename, "w");
    if (archivo == NULL) { return FALSE; };
    if(matriz==NULL)return FALSE;
	for (i=0;i<tam;i++){
		for (j=0;j<tam;j++){
			fprintf(archivo,"%-20d",(int)matriz[i][j]);
		}
		fprintf(archivo,"\n");
	}
    fclose(archivo);
    printf("completado");
    return TRUE;
}

void print(float t){
     printf("    Tiempo tardado %f \n",t);
}


