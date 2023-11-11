#include <stdio.h>
#include "biblioteca.h"

int main() {
    // Inicialização do array de tarefas e do contador de tarefas
    struct Tarefa tarefas[100];
    int contador = 0;
    int opcao;

    // Tentativa de abrir o arquivo para leitura e escrita
    FILE *arquivo = fopen("tarefas.txt", "a+");
    if (arquivo == NULL) {
        // Se houver erro ao abrir o arquivo, exibe mensagem e encerra o programa
        printf("Erro ao criar o arquivo 'tarefas.txt'\n");
        return 1; 
    }
    fclose(arquivo);

    // Carrega as tarefas existentes do arquivo para a memória
    carregarTarefas(tarefas, &contador);

    // Loop principal do programa
    while (1) {
        // Exibe o menu de opções para o usuário
        printf("\nOlá, vamos nos organizar! O que você gostaria de fazer?\n");
        printf("1 - Adicionar nova tarefa\n");
        printf("2 - Listar todas as tarefas\n");
        printf("3 - Remover uma tarefa pelo título\n");
        printf("4 - Alterar uma tarefa\n");
        printf("5 - Filtrar por prioridade\n");
        printf("6 - Filtrar por estado\n");
        printf("7 - Filtrar por categoria\n");
        printf("8 - Filtrar por prioridade e categoria\n");
        printf("9 - Exportar tarefas por prioridade\n");
        printf("10 - Exportar tarefas por categoria\n");
        printf("11 - Exportar tarefas por prioridade e categoria\n");
        printf("12 - Sair\n");

        // Leitura da opção escolhida pelo usuário
        scanf("%d", &opcao);

        // Estrutura de switch-case para lidar com as opções do usuário
        switch (opcao) {
            case 1:
                // Adiciona uma nova tarefa
                cadastrarTarefa(tarefas, &contador);
                salvarTarefas(tarefas, contador); // Salva as alterações no arquivo
                break;
            case 2:
                // Lista todas as tarefas
                listarTarefas(tarefas, contador);
                break;
            case 3:
                // Remove uma tarefa pelo título
                removerTarefa(tarefas, &contador);
                salvarTarefas(tarefas, contador); // Salva as alterações no arquivo
                break;
            case 4:
                // Altera uma tarefa existente
                alterarTarefa(tarefas, &contador);
                salvarTarefas(tarefas, contador); // Salva as alterações no arquivo
                break;
            case 5:
                // Filtra as tarefas por prioridade
                filtrarPorPrioridade(tarefas, contador);
                break;
            case 6:
                // Filtra as tarefas por estado
                filtrarPorEstado(tarefas, contador);
                break;
            case 7:
                {
                    // Filtra as tarefas por categoria
                    char categoriaFiltrar[100];
                    printf("Qual categoria você quer filtrar?: ");
                    scanf(" %99[^\n]", categoriaFiltrar);
                    filtrarPorCategoriaPrioridade(tarefas, contador, categoriaFiltrar);
                }
                break;   
            case 8:
                {
                    // Filtra as tarefas por prioridade e categoria
                    char categoriaFiltrar[100];
                    int prioridadeFiltrar;
                    printf("Qual categoria você quer filtrar?: ");
                    scanf(" %99[^\n]", categoriaFiltrar);
                    printf("Por qual prioridade você quer filtrar? (de 0 a 10): ");
                    scanf("%d", &prioridadeFiltrar);
                    filtrarPorPrioridadeECategoria(tarefas, contador, categoriaFiltrar, prioridadeFiltrar);
                }
                break;
            case 9:
                {
                    // Exporta tarefas por prioridade
                    int prioridadeExportar;
                    printf("Digite a prioridade para exportar: ");
                    scanf("%d", &prioridadeExportar);
                    exportarPorPrioridade(tarefas, contador, prioridadeExportar);
                }
                break;
            case 10:
                {
                    // Exporta tarefas por categoria
                    char categoriaExportar[100];
                    printf("Digite a categoria para exportar: ");
                    scanf(" %99[^\n]", categoriaExportar);
                    exportarPorCategoria(tarefas, contador, categoriaExportar);
                }
                break;
            case 11:
                {
                    // Exporta tarefas por prioridade e categoria
                    int prioridadeExportar;
                    char categoriaExportar[100];
                    printf("Digite a prioridade para exportar: ");
                    scanf("%d", &prioridadeExportar);
                    printf("Digite a categoria para exportar: ");
                    scanf(" %99[^\n]", categoriaExportar);
                    exportarPorPrioridadeECategoria(tarefas, contador, prioridadeExportar, categoriaExportar);
                }
                break;
            case 12:
                // Salva as tarefas no arquivo antes de sair
                salvarTarefas(tarefas, contador);
                printf("Até logo! Não esqueça de sempre conferir as suas tarefas.\n");
                return 0; // Encerra o programa
            default:
                // Mensagem para opção inválida
                printf("Opção inválida. Por favor, escolha novamente.\n");
        }
    }

    return 0;
}
