#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

struct Tarefa {
    char titulo[100];
    int prioridade;
    char descricao[300];
    char categoria[100];
    int estado;
};

void carregarTarefas(struct Tarefa tarefas[], int *contador);
void salvarTarefas(struct Tarefa tarefas[], int contador);
void cadastrarTarefa(struct Tarefa tarefas[], int *contador);
void listarTarefas(struct Tarefa tarefas[], int contador);
void removerTarefa(struct Tarefa tarefas[], int *contador);
void alterarTarefa(struct Tarefa tarefas[], int contador);

#endif
