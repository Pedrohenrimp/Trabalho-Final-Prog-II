#include <stdio.h>
#include <stdlib.h>
#include "mostrarWebnarios.c"


int main(void)
{
    char nome_arquivo_prof[] = "professores.bin";
    struct professorLista *lista_professores = CriarListaProfessor();
    lista_professores = CopiarArquivoProfessor(lista_professores, nome_arquivo_prof);

    char nome_arquivo_webnarios[] = "webnarios.bin";
    struct webnarioLista *lista_webnarios = CriarListaWebnario();
    lista_webnarios = CopiarArquivoWebnario(lista_webnarios, nome_arquivo_webnarios);

    while (1)
    {
        int indice_menu;
        printf("\n----------   MENU   ----------\n\n");
        printf("1. Cadastrar Professor\n");
        printf("2. Cadastrar Webnario\n");
        printf("3. Alterar Webnario\n");
        printf("4. Encerrar Programa\n\n");
        scanf(" %d", &indice_menu);
        if(indice_menu == 1)
        {
            char nome[40], departamento[20];
            int matricula;
            printf("Digite a matricula do professor:\n");
            scanf(" %d", &matricula);
            printf("Digite o nome do professor:\n");
            scanf(" %s", nome);
            printf("Digite o departamento do professor:\n");
            scanf(" %s", departamento);
            bool inserir = InserirFinalProfessor(lista_professores, matricula, nome, departamento);
            if(!inserir)
            {
                printf("Professor ja cadastrado!\n");
            }
            else
            {
                printf("Professor cadastrado com sucesso!\n");
            }
        }
        else if(indice_menu == 2)
        {
            char titulo[40], url[20], matriculaProf[3];
            int id, dia, mes, ano, hora, minuto, qtdProfs;
            printf("Digite o ID do Webnario:\n");
            scanf(" %d", &id);
            printf("Digite o Titulo do Webnario:\n");
            scanf(" %s", titulo);
            printf("Digite o url do Webnario:\nhttp://");
            scanf(" %s", url);
            printf("Digite o ano que sera realizado o Webnario:\n");
            scanf(" %d", &ano);
            printf("Digite o numero correspondente ao mes que o Webinar sera realizado:\n");
            scanf(" %d", &mes);
            printf("Digite o dia do mes que o Webnario sera realizado:\n");
            scanf(" %d", &dia);
            printf("Digite o numero (0 - 24) correspondente a hora que o Webnario sera realizado");
            scanf(" %d", &hora);
            printf("Digite a partir de qual minuto das %dh o Webnario sera realizado:\n", hora);
            scanf(" %d", &minuto);
            printf("Digite a quantidade de professores do Webnario:\n");
            scanf(" %d", &qtdProfs);
            int i, matricula;
            bool inserir = false;
            if(qtdProfs <= 3 && qtdProfs > 0)
            {
                for(i = 0; i < qtdProfs; i++)
                {
                    printf("Digite a matricula do professor 0%d:\n", i + 1);
                    scanf(" %d", matricula);
                    matriculaProf[i] = matricula;
                }
                inserir = InserirFinalWebnario(lista_professores, lista_webnarios, id, titulo, url,
                                                    dia, mes, ano, hora, minuto, qtdProfs, matriculaProf);
            }
            if(!inserir)
            {
                if(BuscarWebnario(lista_webnarios, id))
                {
                    printf("Webnario já Cadastrado!\n");
                }
                else
                {
                    printf("O Webnario deve conter no minimo 1 professor e no maximo 3 professores cadastrados!\n");
                }      
            }
            else
            {
                printf("Webnario Cadastrado com Sucesso!\n");
            }
        }
        else if(indice_menu == 3)
        {

        }
        else if(indice_menu == 4)
        {
            break;
        }
    }

    struct webnarioVetor *vetor_webnarios = VetorWebnarios(lista_webnarios);
    MostrarWebnarios(vetor_webnarios, lista_professores);

    DestruirListaProfessor(lista_professores);
    DestruirListaWebnario(lista_webnarios);
    free(vetor_webnarios);
}

