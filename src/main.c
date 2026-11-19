#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todo.h"

static void limpar_nova_linha(char *str) {
    str[strcspn(str, "\r\n")] = '\0';
}

static int ler_inteiro(const char *prompt, int *valor) {
    char buffer[64];
    printf("%s", prompt);
    if (!fgets(buffer, sizeof(buffer), stdin)) return 0;

    char *fim;
    long n = strtol(buffer, &fim, 10);
    if (fim == buffer || (*fim != '\0' && *fim != '\n' && *fim != '\r')) {
        return 0;
    }
    *valor = (int)n;
    return 1;
}

static void exibir_menu(void) {
    printf("\n=== TO-DO CLI EM C ===\n");
    printf("1. Adicionar tarefa\n");
    printf("2. Listar tarefas\n");
    printf("3. Marcar/Desmarcar concluida\n");
    printf("4. Remover tarefa\n");
    printf("5. Sair\n");
}

int main(void) {
    GerenciadorTarefas app;
    inicializar_gerenciador(&app);

    if (!carregar_tarefas(&app, ARQUIVO_TAREFAS)) {
        printf("Falha ao carregar tarefas existentes.\n");
        liberar_gerenciador(&app);
        return 1;
    }

    int executando = 1;
    while (executando) {
        exibir_menu();
        int opcao = 0;
        if (!ler_inteiro("Escolha uma opcao: ", &opcao)) {
            printf("Entrada invalida. Digite um numero.\n");
            continue;
        }

        switch (opcao) {
            case 1: {
                char titulo[MAX_TITULO];
                printf("Titulo da tarefa: ");
                if (fgets(titulo, sizeof(titulo), stdin)) {
                    limpar_nova_linha(titulo);
                    if (adicionar_tarefa(&app, titulo)) {
                        salvar_tarefas(&app, ARQUIVO_TAREFAS);
                        printf("Tarefa adicionada e salva!\n");
                    } else {
                        printf("Nao foi possivel adicionar (titulo vazio ou sem memoria).\n");
                    }
                }
                break;
            }
            case 2:
                listar_tarefas(&app);
                break;
            case 3: {
                int id;
                if (ler_inteiro("ID da tarefa: ", &id)) {
                    if (alternar_concluida(&app, id)) {
                        salvar_tarefas(&app, ARQUIVO_TAREFAS);
                        printf("Status atualizado!\n");
                    } else {
                        printf("Tarefa com ID #%d nao encontrada.\n", id);
                    }
                } else {
                    printf("ID invalido.\n");
                }
                break;
            }
            case 4: {
                int id;
                if (ler_inteiro("ID da tarefa a remover: ", &id)) {
                    if (remover_tarefa(&app, id)) {
                        salvar_tarefas(&app, ARQUIVO_TAREFAS);
                        printf("Tarefa removida!\n");
                    } else {
                        printf("Tarefa com ID #%d nao encontrada.\n", id);
                    }
                } else {
                    printf("ID invalido.\n");
                }
                break;
            }
            case 5:
                salvar_tarefas(&app, ARQUIVO_TAREFAS);
                executando = 0;
                printf("Saindo... ate mais!\n");
                break;
            default:
                printf("Opcao fora do menu.\n");
                break;
        }
    }

    liberar_gerenciador(&app);
    return 0;
}