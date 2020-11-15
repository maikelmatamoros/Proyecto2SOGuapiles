#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "Marco.h"
#include "IntInput.h"
#define TAM 48


void ingresarPalabras();

void seleccionTipoCarga();

void cargarEnMP();

void dividirFrase(char *frase);

void limpiar(char *cadena);

int existeElem(int v[TAM], int longi, int num);

void generarAleatorio(int v[TAM]);

int existeElem(int v[], int longi, int num);

void cargarPalabras(int v[TAM]);

Lista memoriaSecundaria = NULL;

Lista memoriaPrincipal = NULL;

int cantPalabras = 0;

char *palabrasFrase[100];

int flagA = 0;

int marcosDePaginaPrincipal = 0;

int v[TAM];

int main()
{
    
     seleccionTipoCarga();
     ingresarPalabras();

    return 0;
}

void limpiar(char *cadena)
{
    char *p;
    p = strchr(cadena, '\n');
    if (p)
        *p = '\0';
}

void cargarPalabras(int v[TAM])
{
    char delimitador[] = ",";
    int letra = 97;
    char letraC = letra;
    char linea[2048];
    FILE *fich;
    int fila = 0;

    fich = fopen("Palabras.txt", "r");
    int ak = 0;
    Marco *mAuxiliar;

    while (fgets(linea, 2048, (FILE *)fich))
    {
        int contPalabras = 0;
        int aux = 0;
        generarAleatorio(v);
        int cont = 1;
        char *token = strtok(linea, delimitador);

        mAuxiliar = crearContenedorMarco(letraC, ak);

        if (token != NULL)
        {
            while (token != NULL && aux < 6)
            {

                if (existeElem(v, TAM, contPalabras))
                {

                    mAuxiliar->pagina->palabras[cont - 1] = calloc(sizeof(char), 200);

                    strcpy(mAuxiliar->pagina->palabras[cont - 1], token);

                    if (cont == 6)
                    {

                        aux++;
                        cont = 1;
                        insertar(&memoriaSecundaria, &*mAuxiliar, ak);
                        ak++;
                        //printf("MARCO: %d LETRA: %d\n",ak,letraC);
                        mAuxiliar = crearContenedorMarco(letra, ak);
                    }
                    else
                    {
                        cont++;
                    }
                }
                contPalabras++;
                token = strtok(NULL, delimitador);
            }
        }
        
            letra++;
            letraC = letra;

        
    }
    fclose(fich);
}

void dividirFrase(char *frase)
{
    
    flagA = 0;
    cantPalabras = 0;
    char *cosa[100];
    char delimitador[] = " ";
    char *token = strtok(frase, delimitador);
    if (token != NULL)
    {
        while (token != NULL)
        {
            cosa[cantPalabras] = token;
            char *pal = cosa[cantPalabras];
            for (int i = 0; pal[i]; i++)
            {
                pal[i] = tolower(pal[i]);
            }
            cantPalabras++;
            token = strtok(NULL, delimitador);
        }
    }

    if (cantPalabras < 1)
    {
        printf("ERROR, MINIMO DE PALABRAS NO CUMPLIDO\n");
    }
    else
    {
        char letra;

        // printf("%s", cosa[0]);
        for (int i = 0; i < cantPalabras; i++)
        {
            letra = cosa[i][0];
            int cant = 1;
            for (int j = 0; j < cantPalabras; j++)
            {
                if (j != i)
                {
                    //printf("LETRA A:%c LETRA B: %c \n",letra,cosa[j][0]);
                    if (cosa[j][0] == letra)
                    {
                        cant++;
                    }
                }
            }
            if (cant > 2)
            {
                printf("MAXIMO 2 PALABRAS POR LETRA: %d\n", cant);
                i = 100000;
                flagA = 1;
            }
        }
        if (flagA < 1)
        {
            printf("NUMERO DE PALABRAS ESCRITAS :%d\n", cantPalabras);
            for (int i = 0; i < cantPalabras; i++)
            {
                
                palabrasFrase[i] = cosa[i];
                printf("PALABRA:%s\n",palabrasFrase[i]);
            }
        }
    }
}

void generarAleatorio(int v[TAM])
{

    int i, j, num, longi = TAM;
    srand(time(NULL));

    for (i = 0; i < longi; i++)
    {
        while (existeElem(v, longi, num = rand() % 60))
            ;
        v[i] = num;
    }
}

int existeElem(int v[TAM], int longi, int num)
{
    int i, enc = 0;
    longi = TAM;

    for (i = 0; i < longi && !enc; i++)
    {
        if (v[i] == num)
            enc = 1;
    }

    return enc;
}

void cargarEnMP()
{
    int aux = 0;

    for (int i = 0; i < 156; i++)
    {
        if (aux < 2)
        {

            cargarEnMemoriaPrincipal(&memoriaSecundaria, &memoriaPrincipal, i);
        }
        if (aux < 5)
        {
            aux++;
        }
        else
        {
            aux = 0;
        }
    }
    marcosDePaginaPrincipal=52;
}

void seleccionTipoCarga()
{
    int flag = 0;
    while (flag == 0)
    {
        printf("Elija una opción de carga de palabras:\n");
        printf("1.Cargar todo en Memoria Secundaria\n");
        printf("2.Cargar en Memoria Principal y Secundaria\n");
        printf("Opción:");
        int opcion;

	    getIntegerFromStdin(&opcion);
        if (opcion == 1)
        {
            cargarPalabras(v);
            imprimirMemoriaPrincipal(&memoriaPrincipal);
            flag = 1;
        }
        else if (opcion == 2)
        {
            cargarPalabras(v);
            cargarEnMP();
            imprimirMemoriaPrincipal(&memoriaPrincipal);
            flag = 1;
        }
        else
        {
            printf("Seleccione una opción válida\n");
        }
    }
}

void ingresarPalabras()
{
    int flag = 0;
    while (flag == 0)
    {
        printf("Ingrese una de las siguientes opciones:\n");
        printf("1.Ingresar una frase\n");
        printf("2.Salir\nOpcion:");

        int opcion;
        getIntegerFromStdin(&opcion);
        if (opcion == 1)
        {
            imprimirMemoriaPrincipal(&memoriaPrincipal);
            imprimirMemoriaSecundaria(&memoriaSecundaria);
            printf("\nIngrese palabras separadas por espacio:");
            char frase[100];
            fflush(stdin);
            fflush(stdout);
            fgets(frase, 100, stdin);
            limpiar(frase);
            dividirFrase(frase);
            if (flagA < 1)
            {

                for (int i = 0; i < cantPalabras; i++)
                {
                    printf("PALABRA A BUSCAR: %s \n", palabrasFrase[i]);
                    int secundaria = buscarPalabraEnMemoriaPrincipal(&memoriaPrincipal, palabrasFrase[i]);
                    if (secundaria == 0)
                    {
                        if(marcosDePaginaPrincipal==52){
                            int result = buscarPalabraEnMemoriaSecundaria(&memoriaSecundaria, palabrasFrase[i]);
                            if (result == 1)
                            {
                                segundaOportunidad(&memoriaPrincipal,&memoriaSecundaria);
                                traerPalabraEnMemoriaSecundaria(&memoriaSecundaria, &memoriaPrincipal, palabrasFrase[i]);
                            }
                            
                        }else{
                            int result = buscarPalabraEnMemoriaSecundaria(&memoriaSecundaria, palabrasFrase[i]);
                            if (result == 1)
                            {
                                traerPalabraEnMemoriaSecundaria(&memoriaSecundaria, &memoriaPrincipal, palabrasFrase[i]);
                                marcosDePaginaPrincipal++;
                            }
                        }

                        
                    }
                    
                }
                imprimirMemoriaPrincipal(&memoriaPrincipal);
                imprimirMemoriaSecundaria(&memoriaSecundaria);
            }
        }
        else
        {
            printf("Seleccionó Salir\n");
            break;
        }
    }
}