# Gerenciador de Tarefas (To-Do CLI) em C

Aplicação de linha de comando (CLI) desenvolvida em linguagem C para gerenciar tarefas diárias com **persistência de dados em arquivo** (`tarefas.txt`), evitando a perda das informações ao fechar o terminal.

---

## Funcionalidades

- **Adicionar tarefas** com geração automática de ID incremental
- **Listar tarefas** exibindo status de conclusão (`[ ]` ou `[X]`), ID e título
- **Marcar ou desmarcar tarefas** como concluídas
- **Remover tarefas** por ID
- **Persistência automática** em arquivo de texto estruturado (`id|concluida|titulo`)

---

## Conceitos e Boas Práticas Aplicadas

- **Alocação dinâmica de memória** com `realloc` e liberação explícita com `free`
- **Modularização** separando cabeçalhos (`include/`), implementação (`src/`) e interface CLI
- **Manipulação segura de arquivos** com `fopen`, `fgets` e `fprintf`
- **Leitura segura de entradas** no terminal com `fgets` e `strtol` (evitando problemas de buffer do `scanf`)
- **Automação de build** com `Makefile` e compilação incremental

---

## Estrutura do Projeto

```text
todo-cli-c/
├── include/
│   └── todo.h          # Definição das structs e protótipos das funções
├── src/
│   ├── main.c          # Menu interativo e tratamento de entradas do usuário
│   └── todo.c          # Lógica de negócio, memória dinâmica e persistência
├── build/              # Arquivos objeto (.o) gerados na compilação
├── Makefile            # Regras de compilação e limpeza
├── .gitignore          # Arquivos ignorados pelo Git
└── README.md           # Documentação do projeto
```

---

## Como Compilar e Executar

### Pré-requisitos
- Compilador C (`gcc` ou `clang`)
- Utilitário `make` (opcional, mas recomendado)

### Usando o `Makefile`

```bash
# Clonar o repositório
git clone [https://github.com/nicolascalegari/todo-cli-c.git](https://github.com/nicolascalegari/todo-cli-c.git)
cd todo-cli-c

# Compilar o projeto
make

# Executar o programa
./todo
```

Outros comandos úteis:
```bash
make run    # Compila (se necessário) e executa o programa
make clean  # Remove a pasta build/ e o executável gerado
```

### Compilando manualmente com `gcc`

Caso não tenha o `make` instalado:

```bash
gcc -Wall -Wextra -Werror -std=c11 -Iinclude src/main.c src/todo.c -o todo
./todo
```

---

## Exemplo de Uso

```text
=== TO-DO CLI EM C ===
1. Adicionar tarefa
2. Listar tarefas
3. Marcar/Desmarcar concluida
4. Remover tarefa
5. Sair
Escolha uma opcao: 1
Titulo da tarefa: Estudar ponteiros e alocacao dinamica
Tarefa adicionada e salva!

=== TO-DO CLI EM C ===
1. Adicionar tarefa
2. Listar tarefas
3. Marcar/Desmarcar concluida
4. Remover tarefa
5. Sair
Escolha uma opcao: 2

--- SUAS TAREFAS ---
[ ] #1 - Estudar ponteiros e alocacao dinamica
```

---