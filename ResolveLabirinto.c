#include <stdio.h>
#include <stdlib.h>

#define PAREDE 2147483647
#define LIVRE 2147483646
#define CAMINHO 2147483645

int **mapa;

typedef struct nodo
{
    int i,j;
    struct nodo*proximo;
} Nodo;

typedef struct fila
{
    Nodo *primeiro;
    Nodo *ultimo;
} Fila;

void inicializa(Fila *f)
{
    f->primeiro = NULL;
    f->ultimo = NULL;
}

void enfila (Fila *f, int i, int j)
{
    Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
    novo->proximo = NULL;
    novo->i = i;
    novo->j = j;
    if(f->primeiro != NULL)
    {
        f->ultimo->proximo = novo;
        f->ultimo = novo;
    }
    else
    {
        f->primeiro = novo;
        f->ultimo = novo;
    }
}

int desenfila (Fila *f)
{
    if(f->primeiro == NULL) return 0;
    if(f->primeiro == f->ultimo) f->ultimo = NULL;
    Nodo *tmp = f->primeiro;
    f->primeiro = f->primeiro->proximo;
    free(tmp);
    return 1;
}

int filavazia (Fila *f)
{
    if(f->primeiro == NULL) return 1;
    return 0;
}

void pegatopo(Fila *f, int *i, int *j)
{
    *i = f->primeiro->i;
    *j = f->primeiro->j;
}

void inundacao (int m, int n, int i, int j, int si, int sj)
{
    Fila fila;
    inicializa(&fila);
    int cont = 1;
    mapa[i][j] = cont++;
    while(i != si || j != sj)
    {
        if(mapa[i+1][j] == LIVRE)
        {
            mapa[i+1][j] = cont;
            enfila(&fila, i+1, j);
        }
        if(mapa[i-1][j] == LIVRE)
        {
            mapa[i-1][j] = cont;
            enfila(&fila, i-1, j);
        }
        if(mapa[i][j+1] == LIVRE)
        {
            mapa[i][j+1] = cont;
            enfila(&fila, i, j+1);
        }
        if(mapa[i][j-1] == LIVRE)
        {
            mapa[i][j-1] = cont;
            enfila(&fila, i, j-1);
        }
        pegatopo(&fila,&i,&j);
        desenfila(&fila);
        cont++;
    }
}

void caminha (int m, int n, int ei, int ej, int i, int j)
{
    int cont = mapa[i][j];
    mapa[i][j] = CAMINHO;
    while(i!= ei || j!= ej)
    {
        cont--;
        if(mapa[i+1][j] == cont) i = i+1;
        else if(mapa[i-1][j] == cont) i = i-1;
        else if(mapa[i][j+1] == cont) j = j+1;
        else if(mapa[i][j-1] == cont) j = j-1;
        mapa[i][j] = CAMINHO;
    }
    mapa[i][j] = CAMINHO;
}

int **int2Dmalloc(int M, int N)
{
    unsigned int i;
    int **A = (int **)malloc(M*sizeof(int *));
    for(i = 0; i < M; i++) A[i] = (int *)malloc(N*sizeof(int));
    return A;
}

void int2Dfree(int **A, int M)
{
    int i;
    for(i = 0; i < M; i++)
    {
        free(A[i]);
    }
    free(A);
}

int main (void)
{
    int m, n;
    int i, j, ei, ej, si, sj;
    int x;
    scanf("%d %d", &m, &n);
    printf("%d %d\n", m, n);
    mapa = int2Dmalloc(m, n);
    ei = ej = si = sj = 0;
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &x);
            if(i == 0 || j == 0 || i == (m - 1) || j == (n - 1) || x == 0)
                mapa[i][j] = PAREDE;
            else
                mapa[i][j] = LIVRE;
            if(0 < x && x <= 128)
                ei = i, ej = j;
            else if(128 < x && x < 255)
                si = i, sj = j;
        }
    }
    inundacao (m, n, ei, ej, si, sj);
    caminha (m, n, ei, ej, si, sj);
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(i == 0 || j == 0 || i == (m - 1) || j == (n - 1)) printf("0 ");
            else if(mapa[i][j] == PAREDE) printf("0 ");
            else if(mapa[i][j] == CAMINHO) printf("127 ");
            else printf("255 ");
        }
        printf("\n");
    }
    int2Dfree(mapa, m);
    return 0;
}
