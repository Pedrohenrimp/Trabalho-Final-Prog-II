#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

#pragma pack(1)

struct professor
{
    int matricula; //identificador do professor
    char nome[40], departamento[20];
};

struct professorLista
{
    int matricula;
    char nome[40], departamento[20];
    int posicao;
    struct professorLista *anterior, *proximo;
};

struct professorLista *CriarListaProfessor();
struct professorLista *CriarProfessor(int matricula, char nome[], char departamento[]);
struct professorLista *BuscarProfessor(struct professorLista *lista, int matricula);
bool InserirFinalProfessor(struct professorLista *lista, int matricula, char nome[], char departamento[]);
struct professorLista *DestruirListaProfessor(struct professorLista *lista);

struct professorLista *CopiarArquivoProfessor(struct professorLista *lista, char nome_arquivo[]);
void AtualizarArquivoProfessor(struct professorLista *lista, char nome_arquivo[]);




struct professorLista *CriarListaProfessor()
{
    struct professorLista *sentinela = (struct professorLista *) malloc(sizeof(struct professorLista));
    sentinela->proximo = sentinela;
    sentinela->anterior = sentinela;
    sentinela->posicao = -1;
    return sentinela;
}

struct professorLista *CriarProfessor(int matricula, char nome[], char departamento[])
{
    struct professorLista *professor = (struct professorLista*) malloc(sizeof(struct professorLista));
    professor->matricula = matricula;
    strcpy(professor->nome, nome);
    strcpy(professor->departamento, departamento);
    professor->posicao = professor->anterior->posicao + 1;
    professor->anterior = NULL;
    professor->proximo = NULL;
    return professor;
}

struct professorLista *BuscarProfessor(struct professorLista *lista, int matricula)
{
    struct professorLista *auxiliar = lista->proximo;
    while(auxiliar != lista)
    {
        if(auxiliar->matricula == matricula)
        {
            return auxiliar;
        }
        auxiliar = auxiliar->proximo;
    }
    return NULL;
}

bool InserirFinalProfessor(struct professorLista *lista, int matricula, char nome[], char departamento[])
{
    if(BuscarProfessor(lista, matricula) != NULL)
    {
        return false;
    }
    else
    {
        struct professorLista *novo = CriarProfessor(matricula, nome, departamento);
        novo->proximo = lista;
        novo->anterior = lista->anterior;
        lista->anterior->proximo = novo;
        lista->anterior = novo;
    }
    return true;
}

struct professorLista *DestruirListaProfessor(struct professorLista *lista)
{
    struct professorLista *auxiliar = lista;
    lista->anterior->proximo = NULL;
    while(auxiliar != NULL)
    {
        lista = lista->proximo;
        free(auxiliar);
        auxiliar = lista;
    }
    return NULL;
}

struct professorLista *CopiarArquivoProfessor(struct professorLista *lista, char nome_arquivo[])
{
    FILE *arquivo;
    arquivo = fopen(nome_arquivo, "rb");

    int tamanho_dados = sizeof(struct professor);
    fseek(arquivo, 0, SEEK_END);
    int tamanho_arquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET); 
    struct professor *ponteiro;
    ponteiro = (struct professor *) malloc(tamanho_arquivo);

    struct professorLista *auxiliar = lista->proximo;

    int i;
    for(i = 0; i < tamanho_arquivo / tamanho_dados; i++)
    {
        fread(&ponteiro[i], tamanho_dados, 1, arquivo);
        struct professorLista *novo = CriarProfessor(ponteiro[i].matricula, ponteiro[i].nome, ponteiro[i].departamento);
        novo->proximo = auxiliar;
        novo->anterior = auxiliar->anterior;
        auxiliar->anterior->proximo = novo;
        auxiliar->anterior = novo;
    }

    fclose(arquivo);
    free(ponteiro);

    return lista;
}

void AtualizarArquivoProfessor(struct professorLista *lista, char nome_arquivo[])
{
    int tamanho_lista = lista->anterior->posicao + 1;
    struct professorLista *auxiliar = lista->proximo;
    struct professor *ponteiro = (struct professor *) malloc(sizeof(struct professor) * tamanho_lista);
    int i;
    for(i = 0; i < tamanho_lista; i++)
    {
        ponteiro[i].matricula = auxiliar->matricula;
        strcpy(ponteiro[i].nome, auxiliar->nome);
        strcpy(ponteiro[i].departamento, auxiliar->departamento);

        auxiliar = auxiliar->proximo;
    }
    FILE *arquivo;
    arquivo = fopen(nome_arquivo, "wb");
    int tamanho_dados = sizeof(struct professor);
    fwrite(ponteiro, tamanho_dados, (_msize(ponteiro) / tamanho_dados), arquivo);
    fclose(arquivo);
    free(ponteiro);
}