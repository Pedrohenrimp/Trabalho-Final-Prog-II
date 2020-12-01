#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "webnarios.c"

#define Troca(A,B) {struct webnarioVetor t = A; A = B; B = t;}

struct webnarioVetor
{
    int id;
    char titulo[40], url[20];
    int dia, mes, ano, hora, minuto;
    int qtdProfs;
    int matriculaProf[3];
    int tempo;
};

struct webnarioVetor *VetorWebnarios(struct webnarioLista *lista)
{
    int tamanho_lista = lista->anterior->posicao + 1;
    struct webnarioLista *auxiliar = lista->proximo;
    struct webnarioVetor *ponteiro = (int *) malloc(sizeof(struct webnarioVetor) * tamanho_lista);
    int i;
    for(i = 0; i < tamanho_lista; i++)
    {
        ponteiro[i].id = auxiliar->id;
        ponteiro[i].titulo[40] = auxiliar->titulo;
        ponteiro[i].url[20] = auxiliar->url;
        ponteiro[i].dia = auxiliar->dia;
        ponteiro[i].mes = auxiliar->mes;
        ponteiro[i].ano = auxiliar->ano;
        ponteiro[i].hora = auxiliar->hora;
        ponteiro[i].minuto = auxiliar->minuto;
        ponteiro[i].qtdProfs = auxiliar->quantidade_professores;
        ponteiro[i].matriculaProf[3] = auxiliar->matricula_professores;

        struct tm *data;
        data->tm_min = ponteiro[i].minuto;
        data->tm_hour = ponteiro[i].hora;
        data->tm_mday = ponteiro[i].dia;
        data->tm_mon = ponteiro[i].mes;
        data->tm_year = ponteiro[i].ano - 1900;
        time_t time = mktime(data);

        ponteiro[i].tempo = (int)time;

        auxiliar = auxiliar->proximo;
    }
    return ponteiro;
}

void QuickSort(struct webnarioVetor *vet, int prim, int ult)
{
    int i, j, pivo ,acabou = 0;
    if (prim < ult) 
    {
        pivo = vet[prim].tempo;
        i = prim, j = ult + 1;
        while (acabou == 0) 
        {
            do
                j--;
            while (vet[j].tempo > pivo);
            do
                i++;
            while (vet[i].tempo < pivo);

            if (i > j)
                acabou = 1;
            else Troca(vet[i], vet[j]);
        }

        Troca(vet[prim], vet[j]);
        QuickSort(vet, prim, j - 1);
        QuickSort(vet, j + 1, ult);
   }
}


void MostrarWebnarios(struct webnarioVetor *vetor, struct professorLista *professores)
{
    int tamanho_vetor = sizeof(vetor) / (sizeof(vetor[0]));
    QuickSort(vetor, 0, tamanho_vetor - 1);
    int i;
    for(i = 0; i < tamanho_vetor; i++)
    {
        printf("Webnario %i:\n\n", i + 1);
        printf("Titulo: %s\n", vetor[i].titulo);
        printf("url: %s\n", vetor[i].url);
        printf("Professores: ");
        int j;
        for(j = 0; j < vetor[i].qtdProfs; j++)
        {
            struct professorLista *professor = BuscarProfessor(professores, vetor[i].matriculaProf[j]);
            printf("    %s\n", professor->nome);
        }
        printf("Data: %d/%d/%d - %d:%d\n", vetor[i].dia, vetor[i].mes, vetor[i].ano, vetor[i].hora, vetor[i].minuto);
        printf("\n\n");

    }
}
