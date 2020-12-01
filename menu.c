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

    struct webnarioVetor *vetor_webnarios = VetorWebnarios(lista_webnarios);
    MostrarWebnarios(vetor_webnarios, lista_professores);

    DestruirListaProfessor(lista_professores);
    DestruirListaWebnario(lista_webnarios);
    free(vetor_webnarios);
}