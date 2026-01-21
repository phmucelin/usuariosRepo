# Sistema de Controle de Usuários

Este é um sistema simples de controle de usuários implementado em C, utilizando uma **lista encadeada** como estrutura de dados principal para armazenar as informações dos usuários.

## Estrutura de Dados

A estrutura de dados utilizada é uma **lista encadeada simples**, onde cada nó representa um usuário. Cada usuário possui os seguintes atributos:
- Login (string)
- Senha (string)
- Tentativas de login (inteiro)
- Status (Ativo, Bloqueado, Excluído)
- Role (Usuário Comum ou Admin)
- Ponteiro para o próximo usuário

A lista encadeada permite operações eficientes de inserção e remoção, especialmente no início da lista. A remoção é feita de forma completa, liberando a memória alocada para login e senha.

## Arquivos do Projeto

O projeto está dividido em três arquivos principais para melhor organização e modularidade:

- **main.c**: Arquivo principal contendo a lógica do menu interativo, gerenciamento de sessões (login/logout) e interface com o usuário.
- **usuario.c**: Implementação de todas as funções relacionadas aos usuários, como criação, busca, remoção, validação, etc.
- **usuario.h**: Arquivo de cabeçalho com definições de enums (StatusUsuario, Role), struct Usuario e protótipos das funções.

Essa separação facilita a manutenção e reutilização do código.

## Funcionalidades

### Para Usuários Comuns:
- Login no sistema
- Alterar própria senha

### Para Admins:
- Todas as funcionalidades de usuário comum
- Cadastrar novos usuários
- Listar todos os usuários
- Remover usuários (exclusão total do sistema)
- Promover usuários comuns para admin
- Desbloquear usuários bloqueados
- Alterar senha de qualquer usuário (não implementado no menu, mas disponível na função)

### Sistema Geral:
- Tentativas de login limitadas (máximo 3), bloqueando o usuário após exceder
- Validação de roles para acesso a funções administrativas
- Logout para encerrar sessão
- Sair do programa

## Como Compilar e Executar

### Pré-requisitos
- Compilador C (como GCC)
- Sistema operacional compatível (testado no macOS)

### Compilação
```bash
gcc main.c usuario.c -o main
```

### Execução
```bash
./main
```

### Admin Padrão
Para acessar o sistema inicialmente, use o admin padrão:
- **Login**: admin
- **Senha**: admin

## Exemplo de Uso

1. Execute o programa: `./main`
2. Escolha "1 - Admin" e faça login com "admin"/"admin"
3. No menu admin, cadastre um novo usuário
4. Faça logout
5. Logue como usuário comum e altere a senha
6. Explore outras funcionalidades

## Observações

- As senhas são armazenadas em texto plano (não criptografadas) para simplicidade.
- A remoção de usuários é permanente e libera a memória alocada.
- O sistema utiliza `scanf` para entrada, que pode ter limitações com espaços em strings.
- Não há persistência de dados; os usuários são perdidos ao fechar o programa.

## Melhorias Futuras

- Adicionar criptografia de senhas
- Implementar persistência em arquivo
- Melhorar validação de entrada
- Adicionar mais funcionalidades, como busca por role