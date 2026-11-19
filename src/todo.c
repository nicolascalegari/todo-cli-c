#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todo.h"

static int garantir_capacidade(GerenciadorTarefas *g) {
    if (g->quantidade < g->capacidade) {
        return 1;
    }
    int nova_capacidade = (g->capacidade == 0) ? 8 : g->capacidade * 2;
    Tarefa *novo_bloco = realloc(g->itens, sizeof(Tarefa) * (size_t)nova_capacidade);
    if (!novo_bloco) {
        perror("Erro ao alocar memoria");
        return 0;
    }
    g->itens = novo_bloco;
    g->capacidade = nova_capacidade;
    return 1;
}

void inicializar_gerenciador(GerenciadorTarefas *g) {
    g->itens = NULL;
    g->quantidade = 0;
    g->capacidade = 0;
    g->proximo_id = 1;
}

void liberar_gerenciador(GerenciadorTarefas *g) {
    free(g->itens);
    g->itens = NULL;
    g->quantidade = 0;
    g->capacidade = 0;
}

int carregar_tarefas(GerenciadorTarefas *g, const char *caminho) {
    FILE *fp = fopen(caminho, "r");
    if (!fp) {
        // Arquivo ainda nao existe na primeira execucao: nao e erro fatal
        return 1;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\r\n")] = '\0';
        if (linha[0] == '\0') continue;

        // Formato esperado: id|concluida|titulo
        char *tok_id = strtok(linha, "|");
        char *tok_status = strtok(NULL, "|");
        char *tok_titulo = strtok(NULL, "");

        if (!tok_id || !tok_status || !tok_titulo) continue;

        if (!garantir_capacidade(g)) {
            fclose(fp);
            return 0;
        }

        Tarefa t;
        t.id = atoi(tok_id);
        t.concluida = atoi(tok_status) ? 1 : 0;
        strncpy(t.titulo, tok_titulo, MAX_TITULO - 1);
        t.titulo[MAX_TITULO - 1] = '\0';

        g->itens[g->quantidade++] = t;
        if (t.id >= g->proximo_id) {
            g->proximo_id = t.id + 1;
        }
    }

    fclose(fp);
    return 1;
}

int salvar_tarefas(const GerenciadorTarefas *g, const char *caminho) {
    FILE *fp = fopen(caminho, "w");
    if (!fp) {
        perror("Erro ao abrir arquivo para salvar");
        return 0;
    }

    for (int i = 0; i < g->quantidade; i++) {
        fprintf(fp, "%d|%d|%s\n",
                g->itens[i].id,
                g->itens[i].concluida,
                g->itens[i].titulo);
    }

    fclose(fp);
    return 1;
}

int adicionar_tarefa(GerenciadorTarefas *g, const char *titulo) {
    if (!titulo || titulo[0] == '\0') return 0;
    if (!garantir_capacidade(g)) return 0;

    Tarefa nova;
    nova.id = g->proximo_id++;
    nova.concluida = 0;
    strncpy(nova.titulo, titulo, MAX_TITULO - 1);
    nova.titulo[MAX_TITULO - 1] = '\0';

    g->itens[g->quantidade++] = nova;
    return 1;
}

void listar_tarefas(const GerenciadorTarefas *g) {
    if (g->quantidade == 0) {
        printf("\nNenhuma tarefa cadastrada.\n");
        return;
    }

    printf("\n--- SUAS TAREFAS ---\n");
    for (int i = 0; i < g->quantidade; i++) {
        printf("[%c] #%d - %s\n",
               g->itens[i].concluida ? 'X' : ' ',
               g->itens[i].id,
               g->itens[i].titulo);
    }
}

int alternar_concluida(GerenciadorTarefas *g, int id) {
    for (int i = 0; i < g->quantidade; i++) {
        if (g->itens[i].id == id) {
            g->itens[i].concluida = !g->itens[i].concluida;
            return 1;
        }
    }
    return 0;
}

int remover_tarefa(GerenciadorTarefas *g, int id) {
    int indice = -1;
    for (int i = 0; i < g->quantidade; i++) {
        if (g->itens[i].id == id) {
            indice = i;
            break;
        }
    }

    if (indice == -1) return 0;

    for (int i = indice; i < g->quantidade - 1; i++) {
        g->itens[i] = g->itens[i + 1];
    }
    g->quantidade--;
    return 1;
}