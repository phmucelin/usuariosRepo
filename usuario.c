#include "usuario.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum {
    USUARIO_ATIVO, // 0
    USUARIO_BLOQUEADO, // 1
    USUARIO_EXCLUIDO // 2
} StatusUsuario;

typedef enum {
    USER_COMUM,
    ADMIN
} Role;

typedef struct Usuario{
    char* login;
    char* senha;
    int tentativas;
    StatusUsuario status;
    Role role;
    Usuario* prox;
} Usuario;

#define MAX_TENTATIVAS 3

Usuario* cria_usuario(char* login, char* senha){

    Usuario *u = (Usuario*)malloc(sizeof(Usuario));
    u->login = malloc(strlen(login) + 1);
    u->senha = malloc(strlen(senha) + 1);
    strcpy(u->login, login);
    strcpy(u->senha, senha);
    u->tentativas = 0;
    u->status = USUARIO_ATIVO;
    u->role = USER_COMUM;
    u->prox = NULL;
    return u;

}

Usuario* cria_admin(char* login, char* senha){

    Usuario *u = (Usuario*)malloc(sizeof(Usuario));
    u->login = malloc(strlen(login) + 1);
    u->senha = malloc(strlen(senha) + 1);
    strcpy(u->login, login);
    strcpy(u->senha, senha);
    u->tentativas = 0;
    u->status = USUARIO_ATIVO;
    u->role = ADMIN;
    u->prox = NULL;
    return u;

}

void libera_usuario(Usuario* lista){
    Usuario* p = lista;
    while(p!=NULL){
        Usuario* prox = p->prox;
        free(p->login);
        free(p->senha);
        free(p);
        p = prox;
    }
}

int cadastrar_usuario(Usuario** primeiro, char* login, char* senha){
    if (login == NULL || senha == NULL) return 0;
    if (strlen(login) == 0 || strlen(senha) == 0) return 0;
    if (busca_usuario(*primeiro, login) != NULL) 
    {
        return 0;
    }

    Usuario* u = malloc(sizeof(Usuario));
    if(u == NULL)
    {
        return 0;
    }
    
    u->login = malloc(strlen(login) + 1);
    u->senha = malloc(strlen(senha) + 1);
    
    strcpy(u->login, login);
    strcpy(u->senha, senha);

    u->status = USUARIO_ATIVO;
    u->tentativas = 0;
    u->prox = *primeiro;
    *primeiro = u;
    return 1;
}

Usuario* busca_usuario(Usuario* lista, char* login){
    if(lista == NULL || login == NULL) return NULL;
    Usuario* p = lista;
    while(p != NULL){
        if(strcmp(p->login, login) == 0){
            return p;
}
        p = p->prox;
    }
    return NULL;
}

int remover_total_sistema_usuario(Usuario** primeiro, char* login){
    if(primeiro == NULL || *primeiro == NULL || login == NULL || strlen(login) == 0 ){
        return 0;
    }
    /*Vou chamar a function de busca aqui dentro, mas acredito que poderia otimizar esse while com ela..*/
    
    /*nao permito apagar admin*/
    Usuario* destino = busca_usuario((*primeiro), login);
    if(destino->role == ADMIN) return 0;
    Usuario* p = *primeiro;
    Usuario* anterior = NULL;
    while(p!=NULL){
        if(strcmp(p->login, login) == 0){
            if(anterior == NULL){
                *primeiro = p->prox;
            }else { 
                anterior->prox  = p->prox;
            }
            free(p->login);
            free(p->senha);
            free(p);
            return 1;
        }
        anterior = p;
        p = p->prox;
    }
    return 0;
}

int remove_usuario_parcial(Usuario* lista, char* login){
    if(lista == NULL || login == NULL || strlen(login) == 0) {
        return 0;
    }
    Usuario* dest = busca_usuario(lista, login);
    if(dest == NULL) return 0;
    dest->status = USUARIO_EXCLUIDO;
    return 1;
}

int bloqueia_usuario(Usuario* lista, char* login){
    if(lista == NULL || login == NULL || strlen(login) == 0) 
        {
            return 0;
        }
    Usuario* dest = busca_usuario(lista, login);
    if(dest->role == ADMIN || dest->status == USUARIO_BLOQUEADO || dest->status == USUARIO_EXCLUIDO) return 0;
    if(dest == NULL) return 0;
    dest->status = USUARIO_BLOQUEADO;
    return 1;
}

int login_usuario(Usuario* primeiro, char* login, char* senha){
    
    if(primeiro == NULL || login == NULL || strlen(login) == 0 || senha == NULL || strlen(senha) == 0){
        return 0;
    }

    Usuario* destV = busca_usuario(primeiro, login);
    if(destV == NULL){
        return 0;
    }else{
        if(strcmp(destV->senha, senha) == 0 && destV->status == USUARIO_ATIVO){
            return 1;
        }else{
            if(destV->tentativas < MAX_TENTATIVAS) destV->tentativas++;
            else{
                destV->status = USUARIO_BLOQUEADO;
            }
        }
    }
    return 0;
}

void listar_usuarios(Usuario* lista){
    if(lista == NULL){
        return;
    }
    int i = 1;
    for(Usuario* p = lista; p != NULL; p = p->prox){
        printf("User %d: %s\n", i, p->login);
        i++;
    }
}

int verifica_status(Usuario* lista, char* login){
    if(lista == NULL || login == NULL || strlen(login) == 0) return 0;
    Usuario* destino = busca_usuario(lista, login);
    if(destino == NULL) return 0;
    if(destino->status == USUARIO_ATIVO)
        {
           return 1;
        }
        else
            {
                return 0;
            }

    return 0;
}

/*Sempre antes de chamar funcoes de manipulacao de usuarios, necessario chamar essa para validar a role*/
int valida_user_admin(Usuario* lista, char* login){
    if(lista == NULL || login == NULL || strlen(login) == 0) return 0;
    Usuario* verifica = busca(lista, login);
    if(verifica == NULL) return 0;
    if(verifica->role == ADMIN) return 1;
    else return 0;
    return 0;
}