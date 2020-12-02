#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

struct webnarioVetor *VetorWebnarios(struct webnarioLista *lista);
void QuickSort(struct webnarioVetor *vet, int prim, int ult);
void MostrarWebnarios(struct webnarioVetor *vetor, struct professorLista *professores);

struct webnarioVetor *VetorWebnarios(struct webnarioLista *lista)
{
    int tamanho_lista = lista->anterior->posicao + 1;
    struct webnarioLista *auxiliar = lista->proximo;
    struct webnarioVetor *ponteiro = (struct webnarioVetor *) malloc(sizeof(struct webnarioVetor) * tamanho_lista);
    int i;
    for(i = 0; i < tamanho_lista; i++)
    {
        ponteiro[i].id = auxiliar->id;
        strcpy(ponteiro[i].titulo, auxiliar->titulo);
        strcpy(ponteiro[i].url, auxiliar->url);
        ponteiro[i].dia = auxiliar->dia;
        ponteiro[i].mes = auxiliar->mes;
        ponteiro[i].ano = auxiliar->ano;
        ponteiro[i].hora = auxiliar->hora;
        ponteiro[i].minuto = auxiliar->minuto;
        ponteiro[i].qtdProfs = auxiliar->quantidade_professores;

        int j;
        for(j = 0; j < auxiliar->quantidade_professores; j++)
        {
            ponteiro[i].matriculaProf[j] = auxiliar->matricula_professores[j];
        }

        struct tm *data = (struct tm*)malloc(sizeof(struct tm));
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
    int tamanho_vetor = sizeof(vetor);
    QuickSort(vetor, 0, tamanho_vetor - 1);
    printf("\n---------------------------------------\n");
    int i;
    for(i = 0; i < tamanho_vetor; i++)
    {
        printf("\nWebnario %i:\n\n", i + 1);
        printf("Titulo: %s\n", vetor[i].titulo);
        printf("url: http://%s/\n", vetor[i].url);

        if(vetor[i].minuto < 10)
        {
            char minuto[2];
            minuto[0] = '0';
            minuto[1] = vetor[i].minuto + '0';
            printf("Data: %d/%d/%d - %d:%c%c\n", vetor[i].dia, vetor[i].mes, vetor[i].ano, vetor[i].hora, minuto[0], minuto[1]);
        }
        else
        {
            printf("Data: %d/%d/%d - %d:%d\n", vetor[i].dia, vetor[i].mes, vetor[i].ano, vetor[i].hora, vetor[i].minuto);
        }
        printf("Professores: \n");
        int j;
        for(j = 0; j < vetor[i].qtdProfs; j++)
        {
            struct professorLista *professor = BuscarProfessor(professores, vetor[i].matriculaProf[j]);
            printf("- %s\n", professor->nome);
        }
        printf("\n---------------------------------------\n");
    }
}