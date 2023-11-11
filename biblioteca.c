// A biblioteca padrão de entrada e saída em C.
#include <stdio.h>
// A biblioteca de manipulação de strings em C.
#include <string.h>
// Inclui o cabeçalho personalizado "biblioteca.h", que contém declarações específicas.
#include "biblioteca.h"



// Esta função carrega as tarefas armazenadas em um arquivo chamado "tarefas.txt"
// para um array de estruturas Tarefa e atualiza o contador de tarefas.
// A função recebe um array de tarefas e um ponteiro para o contador de tarefas.
void carregarTarefas(struct Tarefa tarefas[], int *contador) {
    // Abre o arquivo "tarefas.txt" no modo de leitura.
    FILE *arquivo = fopen("tarefas.txt", "r");

    // Verifica se o arquivo foi aberto corretamente.
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo 'tarefas.txt'\n");
    } else {
        // Enquanto a leitura da estrutura Tarefa do arquivo for bem-sucedida,
        // incrementa o contador e continua lendo até o final do arquivo.
        while (fread(&tarefas[*contador], sizeof(struct Tarefa), 1, arquivo) == 1) {
            (*contador)++;
        }

        // Fecha o arquivo após a leitura.
        fclose(arquivo);
    }
}

// Esta função salva as tarefas de um array de estruturas Tarefa em um arquivo chamado "tarefas.txt".

// A função recebe um array de tarefas e o número total de tarefas a serem salvas.
void salvarTarefas(struct Tarefa tarefas[], int contador) {
    // Abre o arquivo "tarefas.txt" no modo de escrita.
    FILE *arquivo = fopen("tarefas.txt", "w");

    // Verifica se o arquivo foi aberto corretamente.
    if (arquivo) {
        // Loop para escrever cada tarefa no arquivo.
        for (int i = 0; i < contador; i++) {
            // Escreve a estrutura Tarefa no arquivo.
            fwrite(&tarefas[i], sizeof(struct Tarefa), 1, arquivo);
        }

        // Fecha o arquivo após a escrita.
        fclose(arquivo);
    }
}



// Esta função permite o cadastro de uma nova tarefa no array de estruturas Tarefa.

// A função recebe um array de tarefas e um ponteiro para o contador de tarefas.
void cadastrarTarefa(struct Tarefa tarefas[], int *contador) {
    // Verifica se o número de tarefas atingiu o limite máximo (100).
    if (*contador >= 100) {
        printf("Opa! Você já tem muitas tarefas! Não é possível adicionar mais.\n");
        return; // Retorna da função se o limite foi atingido.
    }

    // Declaração de uma nova tarefa.
    struct Tarefa novaTarefa;

    // Solicita ao usuário informações sobre a nova tarefa.
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

    // Adiciona a nova tarefa ao array de tarefas.
    tarefas[*contador] = novaTarefa;

    // Incrementa o contador de tarefas.
    (*contador)++;

    // Mensagem indicando que a tarefa foi adicionada com sucesso.
    printf("Tarefa adicionada com sucesso! Mais uma para a lista!\n");
}

// Esta função lista todas as tarefas armazenadas no array de estruturas Tarefa.

// A função recebe um array de tarefas e o número total de tarefas.
void listarTarefas(struct Tarefa tarefas[], int contador) {
    // Variável para contar tarefas existentes.
    int tarefasExistentes = 0;

    // Verifica se não há tarefas cadastradas.
    if (contador == 0) {
        printf("Nenhuma tarefa encontrada.\n");
        return;
    }

    // Itera sobre o array de tarefas e imprime informações de cada tarefa.
    printf("Aqui está a lista de todas as suas tarefas:\n");
    for (int i = 0; i < contador; i++) {
        // Verifica se o título da tarefa é não vazio.
        if (strlen(tarefas[i].titulo) > 0) {
            // Incrementa o contador de tarefas existentes.
            tarefasExistentes++;

            // Imprime informações da tarefa.
            printf("%d - Título: %s\n", tarefasExistentes, tarefas[i].titulo);
            printf("   Prioridade: %d\n", tarefas[i].prioridade);
            printf("   Descrição: %s\n", tarefas[i].descricao);
            printf("   Categoria: %s\n", tarefas[i].categoria);
            printf("   Estado: %d\n", tarefas[i].estado);
        }
    }

    // Se não houver tarefas, imprime mensagem indicando a ausência.
    if (tarefasExistentes == 0) {
        printf("Nenhuma tarefa encontrada.\n");
    }
}

// Esta função remove uma tarefa com base no título fornecido.

// A função recebe um array de tarefas e um ponteiro para o contador de tarefas.
void removerTarefa(struct Tarefa tarefas[], int *contador) {
    // Verifica se não há tarefas cadastradas.
    if (*contador == 0) {
        printf("Nenhuma tarefa para remover.\n");
        return;
    }

    // Título da tarefa a ser removida.
    char titulo[100];
    printf("Digite o título da tarefa que deseja remover: ");
    scanf(" %99[^\n]", titulo);

    // Variável para indicar se a tarefa foi encontrada.
    int encontrou = 0;

    // Itera sobre o array de tarefas para encontrar a tarefa com o título fornecido.
    for (int i = 0; i < *contador; i++) {
        if (strcmp(tarefas[i].titulo, titulo) == 0) {
            // Move as tarefas subsequentes uma posição para trás para "remover" a tarefa.
            for (int j = i; j < (*contador - 1); j++) {
                tarefas[j] = tarefas[j + 1];
            }

            // Decrementa o contador de tarefas.
            (*contador)--;

            // Indica que a tarefa foi encontrada e removida com sucesso.
            encontrou = 1;
            printf("Tarefa removida com sucesso! Mais tempo para você.\n");
            break;
        }
    }

    // Se a tarefa não foi encontrada, imprime mensagem indicando isso.
    if (!encontrou) {
        printf("A tarefa com título '%s' não foi encontrada.\n", titulo);
    }
}


// Esta função permite a alteração de uma tarefa específica no array de estruturas Tarefa.

// A função recebe um array de tarefas e um ponteiro para o contador de tarefas.
void alterarTarefa(struct Tarefa tarefas[], int *contador) {
    // Verifica se não há tarefas cadastradas.
    if (*contador == 0) {
        printf("Nenhuma tarefa para alterar.\n");
        return;
    }

    // Exibe a lista de tarefas existentes.
    printf("Aqui está a lista de todas as suas tarefas:\n");
    int tarefasExistentes = 0; // Variável para rastrear o número de tarefas existentes

    // Itera sobre o array de tarefas e imprime os títulos das tarefas existentes.
    for (int i = 0; i < *contador; i++) {
        if (strlen(tarefas[i].titulo) > 0) {
            // Se o título da tarefa não estiver vazio, a tarefa ainda existe
            tarefasExistentes++;
            printf("%d - Título: %s\n", tarefasExistentes, tarefas[i].titulo);
        }
    }

    // Se não houver tarefas, imprime mensagem indicando isso.
    if (tarefasExistentes == 0) {
        printf("Nenhuma tarefa para alterar.\n");
        return;
    }

    // Solicita ao usuário a escolha da tarefa a ser alterada.
    int escolha;
    printf("Escolha o número da tarefa que deseja alterar: ");
    scanf("%d", &escolha);

    // Verifica se a escolha é válida.
    if (escolha < 1 || escolha > tarefasExistentes) {
        printf("Número de tarefa inválido.\n");
        return;
    }

    // Obtém o índice da tarefa escolhida.
    int tarefaIndex = escolha - 1;

    // Solicita ao usuário a opção de alteração desejada.
    int opcao;
    printf("O que você deseja alterar?\n");
    printf("1 - Título\n");
    printf("2 - Prioridade\n");
    printf("3 - Descrição\n");
    printf("4 - Categoria\n");
    printf("5 - Estado\n");
    scanf("%d", &opcao);

    // Executa a alteração com base na opção escolhida.
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

    // Após a alteração, salva as tarefas no arquivo.
    salvarTarefas(tarefas, contador);

    // Mensagem indicando que a tarefa foi alterada com sucesso.
    printf("Tarefa alterada com sucesso!\n");
}


// Esta função filtra e exibe as tarefas com base na prioridade especificada.

// A função recebe um array de tarefas e o número total de tarefas.
void filtrarPorPrioridade(struct Tarefa tarefas[], int contador) {
    // Variável para armazenar a prioridade a ser filtrada.
    int prioridadeFiltrar;
    printf("Digite a prioridade para filtrar (de 0 a 10): ");
    scanf("%d", &prioridadeFiltrar);

    // Variável para contar tarefas encontradas com a prioridade especificada.
    int tarefasEncontradas = 0;

    // Exibe um cabeçalho indicando a prioridade escolhida.
    printf("Tarefas com prioridade %d:\n", prioridadeFiltrar);

    // Itera sobre o array de tarefas e imprime as informações das tarefas com a prioridade escolhida.
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

    // Se nenhuma tarefa for encontrada, imprime mensagem indicando isso.
    if (tarefasEncontradas == 0) {
        printf("Nenhuma tarefa encontrada com prioridade %d.\n", prioridadeFiltrar);
    }
}

// Esta função filtra e exibe as tarefas com base no estado especificado.

// A função recebe um array de tarefas e o número total de tarefas.
void filtrarPorEstado(struct Tarefa tarefas[], int contador) {
    // Variável para armazenar o estado a ser filtrado.
    int estadoFiltrar;
    printf("Digite o estado para filtrar (1 - Completo, 2 - Em andamento, 3 - Não iniciado): ");
    scanf("%d", &estadoFiltrar);

    // Variável para contar tarefas encontradas com o estado especificado.
    int tarefasEncontradas = 0;

    // Exibe um cabeçalho indicando o estado escolhido.
    printf("Tarefas com estado %d:\n", estadoFiltrar);

    // Itera sobre o array de tarefas e imprime as informações das tarefas com o estado escolhido.
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

    // Se nenhuma tarefa for encontrada, imprime mensagem indicando isso.
    if (tarefasEncontradas == 0) {
        printf("Nenhuma tarefa encontrada com estado %d.\n", estadoFiltrar);
    }
}

// Esta função filtra e exibe as tarefas em uma categoria específica, ordenadas por prioridade de maior para menor.

// A função recebe um array de tarefas, o número total de tarefas e a categoria para filtrar.
void filtrarPorCategoriaPrioridade(struct Tarefa tarefas[], int contador, char categoriaFiltrar[]) {
    // Variável para contar tarefas encontradas na categoria especificada.
    int tarefasEncontradas = 0;

    // Exibe um cabeçalho indicando a categoria escolhida e a ordenação por prioridade.
    printf("Tarefas na categoria '%s' com prioridade ordenada da maior para a menor:\n", categoriaFiltrar);

    // Algoritmo de ordenação (Bubble Sort) para ordenar as tarefas por prioridade de maior para menor.
    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - i - 1; j++) {
            if (tarefas[j].prioridade < tarefas[j + 1].prioridade) {
                struct Tarefa temp = tarefas[j];
                tarefas[j] = tarefas[j + 1];
                tarefas[j + 1] = temp;
            }
        }
    }

    // Itera sobre o array de tarefas e imprime as informações das tarefas na categoria escolhida.
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

    // Se nenhuma tarefa for encontrada, imprime mensagem indicando isso.
    if (tarefasEncontradas == 0) {
        printf("Nenhuma tarefa encontrada na categoria '%s'.\n", categoriaFiltrar);
    }
}

// Esta função filtra e exibe as tarefas em uma categoria específica com uma determinada prioridade.

// A função recebe um array de tarefas, o número total de tarefas, a categoria e a prioridade para filtrar.
void filtrarPorPrioridadeECategoria(struct Tarefa tarefas[], int contador, char categoriaFiltrar[], int prioridadeFiltrar) {
    // Variável para contar tarefas encontradas na categoria e com a prioridade especificadas.
    int tarefasEncontradas = 0;

    // Exibe um cabeçalho indicando a categoria e a prioridade escolhidas.
    printf("Tarefas na categoria '%s' e com prioridade %d:\n", categoriaFiltrar, prioridadeFiltrar);

    // Itera sobre o array de tarefas e imprime as informações das tarefas na categoria e com a prioridade escolhidas.
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

    // Se nenhuma tarefa for encontrada, imprime mensagem indicando isso.
    if (tarefasEncontradas == 0) {
        printf("Nenhuma tarefa encontrada na categoria '%s' com prioridade %d.\n", categoriaFiltrar, prioridadeFiltrar);
    }
}

// Esta função exporta as tarefas com uma prioridade específica para um arquivo.

// A função recebe um array de tarefas, o número total de tarefas e a prioridade para exportar.
void exportarPorPrioridade(struct Tarefa tarefas[], int contador, int prioridadeExportar) {
    // Variável para armazenar o nome do arquivo de exportação.
    char nomeArquivoExportacao[100];
    printf("Digite o nome do arquivo para exportar: ");
    scanf(" %99[^\n]", nomeArquivoExportacao);

    // Abre o arquivo de exportação para escrita.
    FILE *arquivoExportacao = fopen(nomeArquivoExportacao, "w");

    // Verifica se houve erro ao abrir o arquivo.
    if (arquivoExportacao == NULL) {
        printf("Erro ao criar o arquivo de exportação.\n");
        return;
    }

    // Escreve o cabeçalho no arquivo.
    fprintf(arquivoExportacao, "Prioridade | Categoria | Estado | Descrição\n");

    // Itera sobre o array de tarefas e escreve no arquivo apenas as tarefas com a prioridade especificada.
    for (int i = 0; i < contador; i++) {
        if (tarefas[i].prioridade == prioridadeExportar) {
            fprintf(arquivoExportacao, "%d | %s | %d | %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].estado, tarefas[i].descricao);
        }
    }

    // Fecha o arquivo de exportação.
    fclose(arquivoExportacao);
    printf("Tarefas exportadas com sucesso para o arquivo '%s'.\n", nomeArquivoExportacao);
}

// Esta função exporta as tarefas em uma categoria específica para um arquivo.

// A função recebe um array de tarefas, o número total de tarefas e a categoria para exportar.
void exportarPorCategoria(struct Tarefa tarefas[], int contador, char categoriaExportar[]) {
    // Variável para armazenar o nome do arquivo de exportação.
    char nomeArquivoExportacao[100];
    printf("Digite o nome do arquivo para exportar: ");
    scanf(" %99[^\n]", nomeArquivoExportacao);

    // Abre o arquivo de exportação para escrita.
    FILE *arquivoExportacao = fopen(nomeArquivoExportacao, "w");

    // Verifica se houve erro ao abrir o arquivo.
    if (arquivoExportacao == NULL) {
        printf("Erro ao criar o arquivo de exportação.\n");
        return;
    }

    // Ordena as tarefas por prioridade antes de exportar (Bubble Sort).
    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - i - 1; j++) {
            if (tarefas[j].prioridade < tarefas[j + 1].prioridade) {
                // Troca as posições se a prioridade for maior.
                struct Tarefa temp = tarefas[j];
                tarefas[j] = tarefas[j + 1];
                tarefas[j + 1] = temp;
            }
        }
    }

    // Escreve o cabeçalho no arquivo.
    fprintf(arquivoExportacao, "Prioridade | Categoria | Estado | Descrição\n");

    // Itera sobre o array de tarefas e escreve no arquivo apenas as tarefas na categoria especificada.
    for (int i = 0; i < contador; i++) {
        if (strcmp(tarefas[i].categoria, categoriaExportar) == 0) {
            fprintf(arquivoExportacao, "%d | %s | %d | %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].estado, tarefas[i].descricao);
        }
    }

    // Fecha o arquivo de exportação.
    fclose(arquivoExportacao);
    printf("Tarefas exportadas com sucesso para o arquivo '%s'.\n", nomeArquivoExportacao);
}


// Esta função exporta as tarefas com uma determinada prioridade e categoria para um arquivo.

// A função recebe um array de tarefas, o número total de tarefas, a prioridade e a categoria para exportar.
void exportarPorPrioridadeECategoria(struct Tarefa tarefas[], int contador, int prioridadeExportar, char categoriaExportar[]) {
    // Variável para armazenar o nome do arquivo de exportação.
    char nomeArquivoExportacao[100];
    printf("Digite o nome do arquivo para exportar: ");
    scanf(" %99[^\n]", nomeArquivoExportacao);

    // Abre o arquivo de exportação para escrita.
    FILE *arquivoExportacao = fopen(nomeArquivoExportacao, "w");

    // Verifica se houve erro ao abrir o arquivo.
    if (arquivoExportacao == NULL) {
        printf("Erro ao criar o arquivo de exportação.\n");
        return;
    }

    // Ordena as tarefas por prioridade antes de exportar (Bubble Sort).
    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - i - 1; j++) {
            if (tarefas[j].prioridade < tarefas[j + 1].prioridade) {
                // Troca as posições se a prioridade for maior.
                struct Tarefa temp = tarefas[j];
                tarefas[j] = tarefas[j + 1];
                tarefas[j + 1] = temp;
            }
        }
    }

    // Escreve o cabeçalho no arquivo.
    fprintf(arquivoExportacao, "Prioridade | Categoria | Estado | Descrição\n");

    // Itera sobre o array de tarefas e escreve no arquivo apenas as tarefas na categoria e com a prioridade especificadas.
    for (int i = 0; i < contador; i++) {
        if (strcmp(tarefas[i].categoria, categoriaExportar) == 0 && tarefas[i].prioridade == prioridadeExportar) {
            fprintf(arquivoExportacao, "%d | %s | %d | %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].estado, tarefas[i].descricao);
        }
    }

    // Fecha o arquivo de exportação.
    fclose(arquivoExportacao);
    printf("Tarefas exportadas com sucesso para o arquivo '%s'.\n", nomeArquivoExportacao);
}
