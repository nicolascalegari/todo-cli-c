#ifndef TODO_H
#define TODO_H

#define ARQUIVO_TAREFAS "data/tarefas.txt"
#define MAX_TITULO 120

typedef struct {
    int id;
    char titulo[MAX_TITULO];
    int concluida; // 0 = pendente, 1 = concluida
} Tarefa;

typedef struct {
    Tarefa *itens;
    int quantidade;
    int capacidade;
    int proximo_id;
} GerenciadorTarefas;

void inicializar_gerenciador(GerenciadorTarefas *g);
void liberar_gerenciador(GerenciadorTarefas *g);
int carregar_tarefas(GerenciadorTarefas *g, const char *caminho);
int salvar_tarefas(const GerenciadorTarefas *g, const char *caminho);
int adicionar_tarefa(GerenciadorTarefas *g, const char *titulo);
void listar_tarefas(const GerenciadorTarefas *g);
int alternar_concluida(GerenciadorTarefas *g, int id);
int remover_tarefa(GerenciadorTarefas *g, int id);

#endif