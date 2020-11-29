#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

#include "professores.c"

#pragma pack(1)

struct webnario
{
    int id; //identificador do webnário
    char titulo[40],url[20];
    int dia,mes,ano,hora,minuto;
    int qtdProfs; //quantidade de professores que vão participar do webnário
    int matriculaProf[3]; //matriculas dos professores que vão participar do webnário
};

struct webnarioLista
{
    int id;
    char titulo[40], url[20];
    int dia, mes, ano, hora, minuto;
    int quantidade_professores;
    int matricula_professores[3];
    int posicao;
    struct webnarioLista *anterior, *proximo;
};

struct webnarioLista *CriarListaWebinario();
struct webnarioLista *CriarwebnarioWebinario(int id, char titulo[], char url[], int dia, int mes, int ano,
                                                int hora, int minuto, int qtdProfs, int matriculaProf[]);
struct webnarioLista *BuscarWebnario(struct webnarioLista *lista, int id);
bool InserirFinalWebnario(struct professorLista *lista_prof, struct webnarioLista *lista, int id, char titulo[], char url[], 
                            int dia, int mes, int ano, int hora, int minuto, int qtdProfs, int matriculaProf[]);
struct webnarioLista *DestruirListaWebinario(struct webnarioLista *lista);


struct webnarioLista *CopiarArquivoWebnario(struct webnarioLista *lista, char nome_arquivo[]);
void AtualizarArquivo(struct webnarioLista *lista, char nome_arquivo[]);





struct webnarioLista *CriarListaWebinario()
{
    struct webnarioLista *sentinela = (struct webnarioLista *) malloc(sizeof(struct webnarioLista));
    sentinela->proximo = sentinela;
    sentinela->anterior = sentinela;
    sentinela->posicao = -1;
    return sentinela;
}

struct webnarioLista *CriarwebnarioWebinario(int id, char titulo[], char url[], int dia, int mes, int ano,
                                                int hora, int minuto, int qtdProfs, int matriculaProf[])
{
    struct webnarioLista *webnario = (struct webnarioLista*) malloc(sizeof(struct webnarioLista));
    webnario->id = id;
    strcpy(webnario->titulo, titulo);
    strcpy(webnario->url, url);
    webnario->dia = dia;
    webnario->mes = mes;
    webnario->ano = ano;
    webnario->hora = hora;
    webnario->minuto = minuto;
    webnario->posicao = webnario->anterior->posicao + 1;
    webnario->anterior = NULL;
    webnario->proximo = NULL;
    return webnario;
}

struct webnarioLista *BuscarWebnario(struct webnarioLista *lista, int id)
{
    struct webnarioLista *auxiliar = lista->proximo;
    while(auxiliar != lista)
    {
        if(auxiliar->id == id)
        {
            return auxiliar;
        }
        auxiliar = auxiliar->proximo;
    }
    return NULL;
}

bool InserirFinalWebnario(struct professorLista *lista_prof, struct webnarioLista *lista, int id, char titulo[], char url[], 
                            int dia, int mes, int ano, int hora, int minuto, int qtdProfs, int matriculaProf[])
{
    if(BuscarWebnario(lista, id) != NULL || sizeof(matriculaProf) / sizeof(matriculaProf[0]) == 0)
    {
        return false;
    }
    else
    {
        int i;
        for(i = 0; i < sizeof(matriculaProf) / sizeof(matriculaProf[0]); i++)
        {
            if(BuscarProfessor(lista_prof, matriculaProf[i]) == NULL)
            {
                return false;
            }
        }
        
        struct webnarioLista *novo = CriarwebnarioWebinario(id, titulo, url, dia, mes, ano, hora, minuto, qtdProfs, matriculaProf);
        novo->proximo = lista;
        novo->anterior = lista->anterior;
        lista->anterior->proximo = novo;
        lista->anterior = novo;
    }
    return true;
}

void DesmarcarWebnario(struct webnarioLista *lista_web, struct webnarioLista *webnario)
{
    struct webnarioLista *auxiliar = BuscarWebnario(lista_web, webnario->id);
    if(auxiliar != NULL)
    {
        auxiliar->proximo->anterior = auxiliar->anterior;
        auxiliar->anterior->proximo = auxiliar->proximo;
        free(auxiliar);
    }
}

bool IncluirProfessor(struct webnarioLista *lista_web, struct professorLista *lista_prof, struct webnarioLista *webnario, int matricula)
{
    if(BuscarProfessor(lista_prof, matricula) == NULL || BuscarWebnario(lista_web, webnario->id) == NULL)
    {
        return false;
    }
    else if(sizeof(webnario->matricula_professores) / sizeof(webnario->matricula_professores[0]) == 3)
    {
        return false;
    }
    else
    {
        int i;
        for(i = 0; i < 3; i++)
        {
            if(webnario->matricula_professores[i] == '\0')
            {
                webnario->matricula_professores[i] = matricula;
                return true;
            }
        }
    }
    
}

bool RetirarProfessor(struct webnarioLista *lista_web, struct professorLista *lista_prof, struct webnarioLista *webnario, int matricula)
{
    if(BuscarProfessor(lista_prof, matricula) == NULL || BuscarWebnario(lista_web, webnario->id) == NULL)
    {
        return false;
    }
    else
    {
        int i;
        for(i = 0; i < 3; i++)
        {
            if(webnario->matricula_professores[i] == matricula)
            {
                webnario->matricula_professores[i] = '\0';
                if(sizeof(webnario->matricula_professores) / sizeof(webnario->matricula_professores[0]) == 0)
                {
                    DesmarcarWebnario(lista_web, webnario);
                }
                return true;
            }
        }
    }
    return false;
}


struct webnarioLista *DestruirListaWebinario(struct webnarioLista *lista)
{
    struct webnarioLista *auxiliar = lista;
    lista->anterior->proximo = NULL;
    while(auxiliar != NULL)
    {
        lista = lista->proximo;
        free(auxiliar);
        auxiliar = lista;
    }
    return NULL;
}

struct webnarioLista *CopiarArquivoWebnario(struct webnarioLista *lista, char nome_arquivo[])
{
    FILE *arquivo;
    arquivo = fopen(nome_arquivo, "rb");

    int tamanho_dados = sizeof(struct webnario);
    fseek(arquivo, 0, SEEK_END);
    int tamanho_arquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET); 
    struct webnario *ponteiro;
    ponteiro = (struct webnario *) malloc(tamanho_arquivo);

    struct webnarioLista *auxiliar = lista->proximo;

    int i;
    for(i = 0; i < tamanho_arquivo / tamanho_dados; i++)
    {
        fread(&ponteiro[i], tamanho_dados, 1, arquivo);
        struct webnarioLista *novo = CriarwebnarioWebnario(ponteiro[i].id, ponteiro[i].titulo, ponteiro[i].url, ponteiro[i].dia,
                                                ponteiro[i].mes, ponteiro[i].ano, ponteiro[i].hora, ponteiro[i].minuto,
                                                     ponteiro[i].qtdProfs, ponteiro[i].matriculaProf);
        novo->proximo = auxiliar;
        novo->anterior = auxiliar->anterior;
        auxiliar->anterior->proximo = novo;
        auxiliar->anterior = novo;
    }

    fclose(arquivo);
    free(ponteiro);

    return lista;
}

void AtualizarArquivo(struct webnarioLista *lista, char nome_arquivo[])
{
    int tamanho_lista = lista->anterior->posicao - 1;
    struct webnarioLista *auxiliar = lista->proximo;
    struct webnario *ponteiro = (int *) malloc(sizeof(struct webnario) * tamanho_lista);
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

        auxiliar = auxiliar->proximo;
    }
    FILE *arquivo;
    arquivo = fopen(nome_arquivo, "wb");
    int tamanho_dados = sizeof(struct webnario);
    fwrite(ponteiro, tamanho_dados, (_msize(ponteiro) / tamanho_dados), arquivo);
    fclose(arquivo);
    free(ponteiro);
}