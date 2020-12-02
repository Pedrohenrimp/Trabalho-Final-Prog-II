#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include "mostrarWebnarios.c"

int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    struct webnario{
        char titulo [40], url [20];
        int id, qtd_prof;
        int dia, mes, ano, hora, minuto;
        int matricula_prof[3];
    };

//iniciar arquivos - professores.bin  e webnarios.bin
char nome_arquivo_prof[] = "professores.bin";
struct professorLista *lista_professores = CriarListaProfessor();
lista_professores = CopiarArquivoProfessor(lista_professores, nome_arquivo_prof);

char nome_arquivo_webnarios[] = "webnarios.bin";
struct webnarioLista *lista_webnarios = CriarListaWebnario();
lista_webnarios = CopiarArquivoWebnario(lista_webnarios, nome_arquivo_webnarios);

char universidade[30];
int opcao=0;

printf("Digite a sua universidade: ");
gets (universidade);

printf("\n------ Bem vindo ao gerenciador de Webnário da  %s ------\n", universidade);
printf("Selecione a ação desejada de acordo com o menu abaixo: \n");

   while (opcao!=6){
   menu:
        printf("\n 1 - Inclusão de professor.");
        printf("\n 2 - Inclusão de webnário.");
        printf("\n 3 - Acrescentar professor(es) em um webnário.");
        printf("\n 4 - Retirar professor(es) de um webnário.");
        printf("\n 5 - Mostrar os webnários programados.");
        printf("\n 6 - Encerrar programa.");

    printf("\n\n Digite sua opção: ");
    scanf("%d", &opcao);

    switch(opcao){

    case 1: //inclusão professor
    {
        char nome[50], departamento[20];
        int matricula;
        printf("\n -- Cadastro professor -- \n");
        printf("\n Nome: ");
        scanf("%s", nome);
        printf("\n Matrícula: ");
        scanf("%d", matricula);
        printf("\n Departamento: ");
        scanf("%s", departamento);
        bool inserir = InserirFinalProfessor(lista_professores, matricula, nome, departamento);
            if(!inserir)
                printf("Professor já cadastrado.");
            else
                printf("Professor cadastrado com sucesso.");
        break;
    }

    case 2: //inclusão webnário
    {
        struct webnario webnario;
        int i, matricula;
        bool inserir = false;

        printf("\n -- Cadastro Webnário -- \n");
        printf("\n ID: ");
        scanf("%d", &webnario.id);
        printf("\n Título: ");
        scanf("%s", &webnario.titulo);
        printf("\n Url: ");
        scanf("%s", &webnario.url);
        printf("\n Ano: ");
        scanf("%d", &webnario.ano);
        printf("\n Mês: ");
        scanf("%d", &webnario.mes);
        printf("\n Dia (0-24): ");
        scanf("%d", &webnario.dia);
        printf("\n Hora: ");
        scanf("%d", &webnario.hora);
        printf("\n Minuto:");
        scanf("%d", &webnario.minuto);
        printf("\n Quantidade de professores participantes: ");
        scanf("%d", &webnario.qtd_prof);

            if(webnario.qtd_prof <= 3 && webnario.qtd_prof > 0){
                for (i=0; i < webnario.qtd_prof; i++){
                    printf("\n Digite a matrícula do professor:");
                    scanf("%d", matricula);
                    webnario.matricula_prof[i] = matricula;
                }
                inserir = InserirFinalWebnario(lista_professores, lista_webnarios, webnario.id, webnario.titulo, webnario.url, webnario.dia, webnario.mes, webnario.ano, webnario.hora, webnario.minuto, webnario.qtd_prof, webnario.matricula_prof);
            }

            if(!inserir)
            {
                if(BuscarWebnario(lista_webnarios, webnario.id) != NULL){
                    printf("\n Webnário já cadastrado.");
                }
                else {
                    printf("\n O webnário deve ter de 1 à 3 professores cadastrados. Tente novamente.");
                }
            }
            else{
                printf("\n O webnário foi cadastrado com sucesso!");
            }
        break;
    }

    case 3: //Acrescentar professor no webnário
    {
        int id, matricula;
        printf("\n -- Acrescentar professor em um webnário -- \n");
        printf("\n Digite o ID do webnário: ");
        scanf("%d", &id);
        printf("\n Digite a matrícula do professor: ");
        scanf("%d", &matricula);

        if(BuscarWebnario(lista_webnarios, id) != NULL){
            if(BuscarProfessor(lista_professores, matricula) != NULL){
                bool incluir = IncluirProfessor(lista_professores, lista_webnarios, BuscarWebnario(lista_webnarios, id), matricula);
                if(!incluir){
                    printf("Webnário com número máximo de professores cadastrados!\n");
                }
            }
            else{
                printf("Matrícula inválida! Não foi possível incluir professor!\n");
            }
        }
        else{
            printf("ID inválido! Não foi possivel finalizar!\n");
        }
        break;
    }

    case 4: // retirar professor em um webnário
    {
        int id, matricula;
        printf("\n -- Retirar professor de um webnário -- \n");
        printf("\n Digite o ID do webnário: ");
        scanf("%d", &id);
        printf("\n Digite a matrícula do professor: ");
        scanf("%d", &matricula);

        if(BuscarWebnario(lista_webnarios, id) != NULL){
            if(BuscarProfessor(lista_professores, matricula) != NULL){
                bool retirar = RetirarProfessor(lista_professores, lista_webnarios, BuscarWebnario(lista_webnarios, id), matricula);
                if(!retirar){
                    printf(" Webnário com número máximo de professores cadastrados!\n");
                }
            }
            else{
                printf("Matricula do Professor Invalida! Nao foi possivel Incluir Professor!\n");
            }
        }
        else{
            printf("ID do Webnario Invalido! Nao foi possivel finalizar!\n");
        }
        break;
    }

    case 5:
    {
        struct webnarioVetor *vetor_webnarios = VetorWebnarios(lista_webnarios);
        MostrarWebnarios(vetor_webnarios, lista_professores);
        break;
    }

    case 6:
    {
        printf("\n Atualização dos arquivos realizada. Encerrando o programa!");
        DestruirListaProfessor(lista_professores);
        DestruirListaWebnario(lista_webnarios);
        free(vetor_webnarios);
        break;
    }

    default:
       printf("\n Nenhuma opção válida foi escolhida!");
       printf("\n Tente Novamente\n");
       goto menu;
       break;
    };

    }
    return 0;
}
