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
void alterarTarefa(struct Tarefa tarefas[], int *contador);
void filtrarPorPrioridade(struct Tarefa tarefas[], int contador);
void filtrarPorEstado(struct Tarefa tarefas[], int contador);
void filtrarPorCategoriaPrioridade(struct Tarefa tarefas[], int contador, char categoriaFiltrar[]);
void filtrarPorPrioridadeECategoria(struct Tarefa tarefas[], int contador, char categoriaFiltrar[], int prioridadeFiltrar);
void exportarPorPrioridade(struct Tarefa tarefas[], int contador, int prioridadeExportar);
void exportarPorCategoria(struct Tarefa tarefas[], int contador, char categoriaExportar[]);
void exportarPorPrioridadeECategoria(struct Tarefa tarefas[], int contador, int prioridadeExportar, char categoriaExportar[]);


#endif
