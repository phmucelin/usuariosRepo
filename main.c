#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "usuario.h"

int main(){
    Usuario* lista = NULL;
    // Criar admin padrão
    lista = cria_admin("admin", "admin");
    int chose = 0;
    char current_login[100] = "";
    int is_logged_in = 0;
    int is_admin = 0;
    while(1)
    {
        if(!is_logged_in){
            printf("----- Bem vindo ao sistema de controle -----\n");
            printf("-> Voce e um usuario ou admin? \n 0 - Usuario\n 1 - Admin\n 2 - Sair\n Sua escolha: ");
            scanf("%d", &chose);
            if(chose == 0){
                // User login
                char login[100], senha[100];
                printf("Login: ");
                scanf("%s", login);
                printf("Senha: ");
                scanf("%s", senha);
                if(login_usuario(lista, login, senha)){
                    printf("Login successful!\n");
                    sleep(1);
                    strcpy(current_login, login);
                    is_logged_in = 1;
                    is_admin = 0;
                } else {
                    printf("Login failed\n");
                    sleep(1);
                }
            }else if(chose == 1){
                // Admin login
                char login[100], senha[100];
                printf("Admin Login: ");
                scanf("%s", login);
                printf("Senha: ");
                scanf("%s", senha);
                if(login_usuario(lista, login, senha) && valida_user_admin(lista, login)){
                    printf("Admin login successful!\n");
                    sleep(1);
                    strcpy(current_login, login);
                    is_logged_in = 1;
                    is_admin = 1;
                } else {
                    printf("Admin login failed\n");
                    sleep(1);
                }
            } else if(chose == 2){
                printf("Saindo...\n");
                sleep(1);
                break;
            } else {
                printf("Opcao invalida\n");
            }
        } else {
            // Logged in menu
            if(is_admin){
                printf("----- Menu Admin -----\n");
                printf("1 - Cadastrar usuario\n2 - Listar usuarios\n3 - Remover usuario\n4 - Promover usuario\n5 - Logout\nSua escolha: ");
                int op;
                scanf("%d", &op);
                if(op == 1){
                    char new_login[100], new_senha[100];
                    printf("Novo login: ");
                    scanf("%s", new_login);
                    printf("Nova senha: ");
                    scanf("%s", new_senha);
                    if(cadastrar_usuario(&lista, new_login, new_senha)){
                        printf("Usuario cadastrado!\n");
                    } else {
                        printf("Erro ao cadastrar\n");
                    }
                } else if(op == 2){
                    sleep(1);
                    listar_usuarios(lista);
                } else if(op == 3){
                    char rem_login[100];
                    printf("Login a remover: ");
                    scanf("%s", rem_login);
                    if(remover_total_sistema_usuario(&lista, rem_login)){
                        sleep(1);
                        printf("Usuario removido!\n");
                    } else {
                        printf("Erro ao remover\n");
                    }
                } else if(op == 4){
                    char prom_login[100];
                    printf("Login a promover: ");
                    scanf("%s", prom_login);
                    if(promove_usuario_para_admin(lista, prom_login)){
                        printf("Usuario promovido!\n");
                    } else {
                        printf("Erro ao promover\n");
                    }
                } else if(op == 5){
                    is_logged_in = 0;
                    current_login[0] = '\0';
                    printf("Logout realizado\n");
                    sleep(1);
                } else {
                    printf("Opcao invalida\n");
                }
            } else {
                // User menu
                printf("----- Menu Usuario -----\n");
                printf("1 - Alterar senha\n2 - Logout\n");
                int op;
                scanf("%d", &op);
                if(op == 1){
                    char senha[100], nova_senha[100];
                    printf("Senha atual: ");
                    scanf("%s", senha);
                    printf("Nova senha: ");
                    scanf("%s", nova_senha);
                    if(altera_senha_usuario(lista, current_login, senha, nova_senha)){
                        printf("Senha alterada!\n");
                    } else {
                        printf("Erro ao alterar senha\n");
                    }
                } else if(op == 2){
                    is_logged_in = 0;
                    current_login[0] = '\0';
                    printf("Logout realizado\n");
                    sleep(1);
                } else {
                    printf("Opcao invalida\n");
                }
            }
        }
    }
    libera_usuario(lista);
    return 0;
}