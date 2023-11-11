#include <stdio.h>
#include <string.h>
#include "biblioteca.h"



void carregarTarefas(struct Tarefa tarefas[], int *contador) {
    FILE *arquivo = fopen("tarefas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo 'tarefas.txt'\n");
      
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
        printf("Opa! Você já tem muitas tarefas! Não é possível adicionar mais.\n");
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
    printf("Estado da tarefa:\n");
    printf("1 - Completo\n");
    printf("2 - Em andamento\n");
    printf("3 - Não iniciado\n");
    scanf("%d", &novaTarefa.estado);

    tarefas[*contador] = novaTarefa;
    (*contador)++;
    printf("Tarefa adicionada com sucesso! Mais uma para a lista!\n");
}

void listarTarefas(struct Tarefa tarefas[], int contador) {
    int tarefasExistentes = 0; 
    if (contador == 0) {
        printf("Nenhuma tarefa encontrada.\n");
        return;
    }
    printf("Aqui está a lista de todas as suas tarefas:\n");
    for (int i = 0; i < contador; i++) {
        if (strlen(tarefas[i].titulo) > 0) {
            tarefasExistentes++;
            printf("%d - Título: %s\n", tarefasExistentes, tarefas[i].titulo);
            printf("   Prioridade: %d\n", tarefas[i].prioridade);
            printf("   Descrição: %s\n", tarefas[i].descricao);
            printf("   Categoria: %s\n", tarefas[i].categoria);
            printf("   Estado: %d\n", tarefas[i].estado);
        }
    }

    if (tarefasExistentes == 0) {
        printf("Nenhuma tarefa encontrada.\n");
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

void alterarTarefa(struct Tarefa tarefas[], int *contador) {
    if (*contador == 0) {
        printf("Nenhuma tarefa para alterar.\n");
        return;
    }

    printf("Aqui está a lista de todas as suas tarefas:\n");
    int tarefasExistentes = 0; // Variável para rastrear o número de tarefas existentes

    for (int i = 0; i < *contador; i++) {
        if (strlen(tarefas[i].titulo) > 0) {
            // Se o título da tarefa não estiver vazio, a tarefa ainda existe
            tarefasExistentes++;
            printf("%d - Título: %s\n", tarefasExistentes, tarefas[i].titulo);
        }
    }

    if (tarefasExistentes == 0) {
        printf("Nenhuma tarefa para alterar.\n");
        return;
    }

    int escolha;
    printf("Escolha o número da tarefa que deseja alterar: ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > tarefasExistentes) {
        printf("Número de tarefa inválido.\n");
        return;
    }

    int tarefaIndex = escolha - 1;

    int opcao;
    printf("O que você deseja alterar?\n");
    printf("1 - Título\n");
    printf("2 - Prioridade\n");
    printf("3 - Descrição\n");
    printf("4 - Categoria\n");
    printf("5 - Estado\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Digite o novo título: ");
            scanf(" %99[^\n]", tarefas[tarefaIndex].titulo);
            break;
        case 2:
            printf("Digite a nova prioridade: ");
            scanf("%d", &tarefas[tarefaIndex].prioridade);
            break;
        case 3:
            printf("Digite a nova descrição: ");
            scanf(" %299[^\n]", tarefas[tarefaIndex].descricao);
            break;
        case 4:
            printf("Digite a nova categoria: ");
            scanf(" %99[^\n]", tarefas[tarefaIndex].categoria);
            break;
        case 5:
            printf("Digite o novo estado (1 - Completo, 2 - Em andamento, 3 - Não iniciado): ");
            scanf("%d", &tarefas[tarefaIndex].estado);
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }

    salvarTarefas(tarefas, contador);
    printf("Tarefa alterada com sucesso!\n");
}

void filtrarPorPrioridade(struct Tarefa tarefas[], int contador) {
    int prioridadeFiltrar;
    printf("Digite a prioridade para filtrar (de 0 a 10): ");
    scanf("%d", &prioridadeFiltrar);

    int tarefasEncontradas = 0;

    printf("Tarefas com prioridade %d:\n", prioridadeFiltrar);

    for (int i = 0; i < contador; i++) {
        if (tarefas[i].prioridade == prioridadeFiltrar) {
            tarefasEncontradas++;
            printf("%d - Título: %s\n", tarefasEncontradas, tarefas[i].titulo);
            printf("   Prioridade: %d\n", tarefas[i].prioridade);
            printf("   Descrição: %s\n", tarefas[i].descricao);
            printf("   Categoria: %s\n", tarefas[i].categoria);
            printf("   Estado: %d\n", tarefas[i].estado);
        }
    }

    if (tarefasEncontradas == 0) {
        printf("Nenhuma tarefa encontrada com prioridade %d.\n", prioridadeFiltrar);
    }
}

void filtrarPorEstado(struct Tarefa tarefas[], int contador) {
    int estadoFiltrar;
    printf("Digite o estado para filtrar (1 - Completo, 2 - Em andamento, 3 - Não iniciado): ");
    scanf("%d", &estadoFiltrar);

    int tarefasEncontradas = 0;

    printf("Tarefas com estado %d:\n", estadoFiltrar);

    for (int i = 0; i < contador; i++) {
        if (tarefas[i].estado == estadoFiltrar) {
            tarefasEncontradas++;
            printf("%d - Título: %s\n", tarefasEncontradas, tarefas[i].titulo);
            printf("   Prioridade: %d\n", tarefas[i].prioridade);
            printf("   Descrição: %s\n", tarefas[i].descricao);
            printf("   Categoria: %s\n", tarefas[i].categoria);
            printf("   Estado: %d\n", tarefas[i].estado);
        }
    }

    if (tarefasEncontradas == 0) {
        printf("Nenhuma tarefa encontrada com estado %d.\n", estadoFiltrar);
    }
}

void filtrarPorCategoriaPrioridade(struct Tarefa tarefas[], int contador, char categoriaFiltrar[]) {
    int tarefasEncontradas = 0;

    printf("Tarefas na categoria '%s' com prioridade ordenada da maior para a menor:\n", categoriaFiltrar);
  
    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - i - 1; j++) {
            if (tarefas[j].prioridade < tarefas[j + 1].prioridade) {
            
                struct Tarefa temp = tarefas[j];
                tarefas[j] = tarefas[j + 1];
                tarefas[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < contador; i++) {
        if (strcmp(tarefas[i].categoria, categoriaFiltrar) == 0) {
            tarefasEncontradas++;
            printf("%d - Título: %s\n", tarefasEncontradas, tarefas[i].titulo);
            printf("   Prioridade: %d\n", tarefas[i].prioridade);
            printf("   Descrição: %s\n", tarefas[i].descricao);
            printf("   Categoria: %s\n", tarefas[i].categoria);
            printf("   Estado: %d\n", tarefas[i].estado);
        }
    }

    if (tarefasEncontradas == 0) {
        printf("Nenhuma tarefa encontrada na categoria '%s'.\n", categoriaFiltrar);
    }
}

void filtrarPorPrioridadeECategoria(struct Tarefa tarefas[], int contador, char categoriaFiltrar[], int prioridadeFiltrar) {
    int tarefasEncontradas = 0;

    printf("Tarefas na categoria '%s' e com prioridade %d:\n", categoriaFiltrar, prioridadeFiltrar);

    for (int i = 0; i < contador; i++) {
        if (strcmp(tarefas[i].categoria, categoriaFiltrar) == 0 && tarefas[i].prioridade == prioridadeFiltrar) {
            tarefasEncontradas++;
            printf("%d - Título: %s\n", tarefasEncontradas, tarefas[i].titulo);
            printf("   Prioridade: %d\n", tarefas[i].prioridade);
            printf("   Descrição: %s\n", tarefas[i].descricao);
            printf("   Categoria: %s\n", tarefas[i].categoria);
            printf("   Estado: %d\n", tarefas[i].estado);
        }
    }

    if (tarefasEncontradas == 0) {
        printf("Nenhuma tarefa encontrada na categoria '%s' com prioridade %d.\n", categoriaFiltrar, prioridadeFiltrar);
    }
}

void exportarPorPrioridade(struct Tarefa tarefas[], int contador, int prioridadeExportar) {
    char nomeArquivoExportacao[100];
    printf("Digite o nome do arquivo para exportar: ");
    scanf(" %99[^\n]", nomeArquivoExportacao);

    FILE *arquivoExportacao = fopen(nomeArquivoExportacao, "w");

    if (arquivoExportacao == NULL) {
        printf("Erro ao criar o arquivo de exportação.\n");
        return;
    }

    fprintf(arquivoExportacao, "Prioridade | Categoria | Estado | Descrição\n");

    for (int i = 0; i < contador; i++) {
        if (tarefas[i].prioridade == prioridadeExportar) {
            fprintf(arquivoExportacao, "%d | %s | %d | %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].estado, tarefas[i].descricao);
        }
    }

    fclose(arquivoExportacao);
    printf("Tarefas exportadas com sucesso para o arquivo '%s'.\n", nomeArquivoExportacao);
}

void exportarPorCategoria(struct Tarefa tarefas[], int contador, char categoriaExportar[]) {
    char nomeArquivoExportacao[100];
    printf("Digite o nome do arquivo para exportar: ");
    scanf(" %99[^\n]", nomeArquivoExportacao);

    FILE *arquivoExportacao = fopen(nomeArquivoExportacao, "w");

    if (arquivoExportacao == NULL) {
        printf("Erro ao criar o arquivo de exportação.\n");
        return;
    }

    // Ordenar as tarefas por prioridade antes de exportar
    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - i - 1; j++) {
            if (tarefas[j].prioridade < tarefas[j + 1].prioridade) {
                // Trocar as posições se a prioridade for maior
                struct Tarefa temp = tarefas[j];
                tarefas[j] = tarefas[j + 1];
                tarefas[j + 1] = temp;
            }
        }
    }

    fprintf(arquivoExportacao, "Prioridade | Categoria | Estado | Descrição\n");

    for (int i = 0; i < contador; i++) {
        if (strcmp(tarefas[i].categoria, categoriaExportar) == 0) {
            fprintf(arquivoExportacao, "%d | %s | %d | %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].estado, tarefas[i].descricao);
        }
    }

    fclose(arquivoExportacao);
    printf("Tarefas exportadas com sucesso para o arquivo '%s'.\n", nomeArquivoExportacao);
}

void exportarPorPrioridadeECategoria(struct Tarefa tarefas[], int contador, int prioridadeExportar, char categoriaExportar[]) {
    char nomeArquivoExportacao[100];
    printf("Digite o nome do arquivo para exportar: ");
    scanf(" %99[^\n]", nomeArquivoExportacao);

    FILE *arquivoExportacao = fopen(nomeArquivoExportacao, "w");

    if (arquivoExportacao == NULL) {
        printf("Erro ao criar o arquivo de exportação.\n");
        return;
    }

    // Ordenar as tarefas por prioridade antes de exportar
    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - i - 1; j++) {
            if (tarefas[j].prioridade < tarefas[j + 1].prioridade) {
                // Trocar as posições se a prioridade for maior
                struct Tarefa temp = tarefas[j];
                tarefas[j] = tarefas[j + 1];
                tarefas[j + 1] = temp;
            }
        }
    }

    fprintf(arquivoExportacao, "Prioridade | Categoria | Estado | Descrição\n");

    for (int i = 0; i < contador; i++) {
        if (strcmp(tarefas[i].categoria, categoriaExportar) == 0 && tarefas[i].prioridade == prioridadeExportar) {
            fprintf(arquivoExportacao, "%d | %s | %d | %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].estado, tarefas[i].descricao);
        }
    }

    fclose(arquivoExportacao);
    printf("Tarefas exportadas com sucesso para o arquivo '%s'.\n", nomeArquivoExportacao);
}
