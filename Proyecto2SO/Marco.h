#include "Pagina.h"

typedef struct Marco
{
    int numero;
    char letra;
    int r;
    Pagina *pagina;
    struct Marco *next;
} Marco;

typedef struct tipoNodo
{
    Marco *data;
    struct tipoNodo *next;
    struct tipoNodo *prev;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;

Marco *crearContenedorMarco(char l, int n);

void insertar(Lista *lista, Marco *m, int pag)
{
    //printf("PUTA: %d\n", pag);
    pNodo nuevo, actual;

    /* Crear un nodo nuevo */
    nuevo = (pNodo)malloc(sizeof(tipoNodo));
    nuevo->data = m;

    /* Colocamos actual en la primera posición de la lista */
    actual = *lista;

    /* Si la lista está vacía o el primer miembro es mayor que el nuevo */
    if (!actual)
    {
        nuevo->next = actual;
        nuevo->prev = NULL;
        if (!*lista)
        {
            *lista = nuevo;
        }
    }
    else
    {
        while (actual->next != NULL)
        {
            actual = actual->next;
        }
        /* Insertamos el nuevo nodo después del nodo anterior */
        nuevo->next = NULL;
        nuevo->prev = actual;
        actual->next = nuevo;
    }
}

Marco *crearContenedorMarco(char l, int n)
{
    Marco *aux = calloc(sizeof(Marco), 1);
    aux->pagina = calloc(sizeof(Pagina), 1);
    aux->next = NULL;
    aux->r = -1;
    aux->numero = n;
    aux->letra = l;
    return aux;
}

void imprimirMemoriaSecundaria(Lista *l)
{
    pNodo actual = *l;
    printf("\n ------------------MEMORIA SECUNDARIA------------------- \n");
    while (actual)
    {
        printf("R:%d", actual->data->r);
        for (int i = 0; i < 6; i++)
        {
            printf("[%s]", actual->data->pagina->palabras[i]);
        }
        printf("\n");
        actual = actual->next;
    }
    printf("\n");
}

void imprimirMemoriaPrincipal(Lista *l)
{
    pNodo actual = *l;
    printf("\n ------------------MEMORIA PRINCIPAL------------------- \n");
    while (actual)
    {
        printf("R:%d", actual->data->r);
        for (int i = 0; i < 6; i++)
        {
            printf("[%s]", actual->data->pagina->palabras[i]);
        }
        printf("\n");
        actual = actual->next;
    }
    printf("\n");
}

int traerPalabraEnMemoriaSecundaria(Lista *ms, Lista *mp, char *palabra)
{
    char letra = palabra[0];
    pNodo actual = *ms;
    pNodo actualP = *mp;
    int flag = 0;
    while (actual && flag == 0)
    {
        if (letra == actual->data->letra)
        {
            for (int i = 0; i < 6; i++)
            {
                if (strcmp(palabra, actual->data->pagina->palabras[i]) == 0)
                {
                    pNodo nuevo = actual;
                    nuevo->data->r = 1;
                    actual = nuevo->prev;
                    actual->next = nuevo->next;
                    if (!actualP)
                    {
                        nuevo->next = NULL;
                        nuevo->prev = NULL;
                        *mp = nuevo;
                    }
                    else
                    {
                        while (actualP->next)
                        {
                            actualP = actualP->next;
                        }
                        
                        nuevo->next = NULL;
                        nuevo->prev = actualP;
                        actualP->next = nuevo;
                        printf("PRUEBA R: %d\n",actualP->next->data->r);
                    }
                    return 1;
                    flag = 1;
                    break;
                }
            }
        }
        actual = actual->next;
    }
    return 0;
}

int buscarPalabraEnMemoriaSecundaria(Lista *ms, char *palabra)
{
    char letra = palabra[0];
    pNodo actual = *ms;
    int flag = 0;
    while (actual && flag == 0)
    {
        if (letra == actual->data->letra)
        {
            for (int i = 0; i < 6; i++)
            {
                if (strcmp(palabra, actual->data->pagina->palabras[i]) == 0)
                {
                    return 1;
                    flag = 1;
                    break;
                }
            }
        }
        actual = actual->next;
    }
    if (flag == 0)
    {
        printf("NO ENCONTRÉ lA PALABRA: %s EN MEMORIA SECUNDARIA\n ", palabra);
    }
    return 0;
}

int buscarPalabraEnMemoriaPrincipal(Lista *mp, char *palabra)
{

    char letra = palabra[0];
    pNodo actual = *mp;
    int flag = 0;
    while (actual)
    {
        if (letra == actual->data->letra)
        {
            for (int i = 0; i < 6; i++)
            {
                if (strcmp(palabra, actual->data->pagina->palabras[i]) == 0)
                {
                    actual->data->r = 1;
                    printf("ENCONTRÉ LA PALABRA: %s \n", palabra);
                    return 1;
                }
            }
        }
        actual = actual->next;
    }
    if (flag == 0)
    {
        printf("NO ENCONTRÉ lA PALABRA: %s EN MEMORIA PRINCIPAL\n", palabra);
    }
    return 0;
}

void cargarEnMemoriaPrincipal(Lista *ms, Lista *mp, int marco)
{
    pNodo actual = *ms;
    pNodo actualP = *mp;
    int flag = 0;
    while (actual)
    {
        flag = actual->data->numero;
        if (flag == marco)
        {

            pNodo nuevo = actual;
            nuevo->data->r = 1;
            if (!actual->prev)
            {

                actual = nuevo->next;
                actual->prev = NULL;
                *ms = actual;
            }
            else
            {
                actual = nuevo->prev;
                actual->next = nuevo->next;
                actual->next->prev = nuevo->prev;
            }


            if (!actualP)
            {
                nuevo->next = NULL;
                nuevo->prev = NULL;
                *mp = nuevo;
                break;
            }
            else
            {
                while (actualP->next)
                {
                    actualP = actualP->next;
                }
                nuevo->next = NULL;
                nuevo->prev = actualP;
                actualP->next = nuevo;
            }
            break;
        }
        actual = actual->next;
    }
}

void segundaOportunidad(Lista *mp, Lista *ms)
{
    pNodo actual = *mp;
    pNodo actualS = *ms;
    int flag = 0;
    while (actual)
    {
        if (actual->data->r == 1)
        {
            //printf("r:%d Palabra[0]=[%s]\n", actual->data->r, actual->data->pagina->palabras[0]);
            pNodo nuevo = actual;
            nuevo->data->r = 0;
            if (!actual->prev)
            {
                actual = nuevo->next;
                actual->prev = NULL;
                *mp = actual;
                flag = 1;
            }
            else
            {
                actual = nuevo->prev;
                actual->next = nuevo->next;
                actual->next->prev = nuevo->prev;
            }
            
            pNodo aux = actual;
            while (aux->next)
            {
                aux = aux->next;
            }
            nuevo->next = NULL;
            nuevo->prev = aux;
            aux->next = nuevo;
        }
        else
        {
            pNodo nuevo = actual;
            nuevo->data->r = 0;
            if (!actual->prev)
            {

                actual = nuevo->next;
                actual->prev = NULL;
                *mp = actual;
            }
            else
            {
                actual = nuevo->prev;
                actual->next = nuevo->next;
                actual->next->prev = nuevo->prev;
            }

            

            while (actualS->next)
            {
                actualS = actualS->next;
            }
            nuevo->next = NULL;
            nuevo->prev = actualS;
            actualS->next = nuevo;
            break;
        }
        if (flag == 0)
        {
            actual = actual->next;
        }
        else
        {
            flag = 0;
        }
    }
}