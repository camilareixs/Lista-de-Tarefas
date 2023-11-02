#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

struct Tarefa {
    char titulo[100];
    int prioridade;
    char descricao[300];
    char categoria[100];
};

void cadastrarTarefa(struct Tarefa tarefas[], int *contador);
void listarTarefas(struct Tarefa tarefas[], int contador);
void removerTarefa(struct Tarefa tarefas[], int *contador);

#endif
