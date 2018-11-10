#include <stdio.h>
#include <stdlib.h>
#define MM 3000
#define PAREDE 2147483647
#define LIVRE 2147483646
#define CAMINHO 2147483645
int mapa[MM][MM];

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

int main (void)
{
    char p5[3];
    int m, n, k;
    int i, j, ei, ej, si, sj;
    scanf("P5\n# CREATOR: GIMP PNM Filter Version 1.1\n%d %d\n255\n", &m, &n);
    printf("P2 %d %d 255 ", m, n);
    char ima;
    k = 1;
    ei = ej = si = sj = 0;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%c", &ima);
            if(i == 0 || j == 0 || i == (n - 1) || j == (m - 1) || ima == ' ') mapa[i][j] = PAREDE;
            else mapa[i][j] = LIVRE;
            if(ima == 10) j--;
            if(!(i == 0 || j == 0 || i == (n - 1) || j == (m - 1)) && (i == 1 || j == 1 || i == (n - 2) || j == (m - 2)) && ima != ' ')
            {
                if(k) ei = i, ej = j;
                else  si = i, sj = j;
                k = 0;
            }
        }
    }
    inundacao (m, n, ei, ej, si, sj);
    caminha (m, n, ei, ej, si, sj);
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            if(i == 0 || j == 0 || i == (n - 1) || j == (m - 1)) printf("255 ");
            else if(mapa[i][j] == PAREDE) printf("0 ");
            else if(mapa[i][j] == CAMINHO) printf("127 ");
            else printf("255 ");
        }
    }
    return 0;
}
