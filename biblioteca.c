#include <stdio.h>
#include <string.h>
#include "biblioteca.h"

void carregarTarefas(struct Tarefa tarefas[], int *contador) {
    FILE *arquivo = fopen("tarefas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo 'tarefas.txt'\n");
        // Adicione tratamento de erro adequado aqui, se necessário
    } else {
        while (fread(&tarefas[*contador], sizeof(struct Tarefa), 1, arquivo) == 1) {
            (*contador)++;
    }
        fclose(arquivo);
    }
}

void salvarTarefas(struct Tarefa tarefas[], int contador) {
    FILE *arquivo = fopen("tarefas.txt", "w");
    if (arquivo) {
        for (int i = 0; i < contador; i++) {
            fwrite(&tarefas[i], sizeof(struct Tarefa), 1, arquivo);
        }
        fclose(arquivo);
    }
}

void cadastrarTarefa(struct Tarefa tarefas[], int *contador) {
    if (*contador >= 100) {
        printf("Ops, você já tem muitas tarefas! Não é possível adicionar mais.\n");
        return;
    }

    struct Tarefa novaTarefa;
    printf("Digite o título da tarefa: ");
    scanf(" %99[^\n]", novaTarefa.titulo);
    printf("Qual é a prioridade desta tarefa (de 0 a 10)? ");
    scanf("%d", &novaTarefa.prioridade);
    printf("Descreva a tarefa: ");
    scanf(" %299[^\n]", novaTarefa.descricao);
    printf("Categoria: ");
    scanf(" %99[^\n]", novaTarefa.categoria);

    tarefas[*contador] = novaTarefa;
    (*contador)++;
    printf("Tarefa adicionada com sucesso! Mais uma para a lista!\n");
}

void listarTarefas(struct Tarefa tarefas[], int contador) {
    if (contador == 0) {
        printf("Nenhuma tarefa encontrada.\n");
        return;
    }

    printf("Aqui está a lista de todas as suas tarefas:\n");
    for (int i = 0; i < contador; i++) {
        printf("Título: %s\n", tarefas[i].titulo);
        printf("Prioridade: %d\n", tarefas[i].prioridade);
        printf("Descrição: %s\n", tarefas[i].descricao);
        printf("Categoria: %s\n", tarefas[i].categoria);
    }
}

void removerTarefa(struct Tarefa tarefas[], int *contador) {
    if (*contador == 0) {
        printf("Nenhuma tarefa para remover.\n");
        return;
    }

    char titulo[100];
    printf("Digite o título da tarefa que deseja remover: ");
    scanf(" %99[^\n]", titulo);

    int encontrou = 0;
    for (int i = 0; i < *contador; i++) {
        if (strcmp(tarefas[i].titulo, titulo) == 0) {
            for (int j = i; j < (*contador - 1); j++) {
                tarefas[j] = tarefas[j + 1];
            }
            (*contador)--;
            encontrou = 1;
            printf("Tarefa removida com sucesso! Mais tempo para você.\n");
            break;
        }
    }

    if (!encontrou) {
        printf("A tarefa com título '%s' não foi encontrada.\n", titulo);
    }
}
