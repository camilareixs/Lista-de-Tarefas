#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

// Estrutura que representa uma tarefa
struct Tarefa {
    char titulo[100];
    int prioridade;
    char descricao[300];
    char categoria[100];
    int estado;
};

// Protótipos das funções declaradas na biblioteca

// Carrega as tarefas do arquivo para a memória
void carregarTarefas(struct Tarefa tarefas[], int *contador);

// Salva as tarefas da memória para o arquivo
void salvarTarefas(struct Tarefa tarefas[], int contador);

// Cadastra uma nova tarefa
void cadastrarTarefa(struct Tarefa tarefas[], int *contador);

// Lista todas as tarefas cadastradas
void listarTarefas(struct Tarefa tarefas[], int contador);

// Remove uma tarefa com base no título
void removerTarefa(struct Tarefa tarefas[], int *contador);

// Altera os detalhes de uma tarefa existente
void alterarTarefa(struct Tarefa tarefas[], int *contador);

// Filtra as tarefas por prioridade
void filtrarPorPrioridade(struct Tarefa tarefas[], int contador);

// Filtra as tarefas por estado
void filtrarPorEstado(struct Tarefa tarefas[], int contador);

// Filtra as tarefas por categoria e prioridade
void filtrarPorCategoriaPrioridade(struct Tarefa tarefas[], int contador, char categoriaFiltrar[]);

// Filtra as tarefas por prioridade e categoria
void filtrarPorPrioridadeECategoria(struct Tarefa tarefas[], int contador, char categoriaFiltrar[], int prioridadeFiltrar);

// Exporta as tarefas com uma determinada prioridade para um arquivo
void exportarPorPrioridade(struct Tarefa tarefas[], int contador, int prioridadeExportar);

// Exporta as tarefas com uma determinada categoria para um arquivo
void exportarPorCategoria(struct Tarefa tarefas[], int contador, char categoriaExportar[]);

// Exporta as tarefas com uma determinada prioridade e categoria para um arquivo
void exportarPorPrioridadeECategoria(struct Tarefa tarefas[], int contador, int prioridadeExportar, char categoriaExportar[]);

#endif
