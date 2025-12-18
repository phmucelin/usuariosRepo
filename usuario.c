#include "usuario.h"
#include <stdlib.h>
#include <string.h>


Usuario* cria_usuario(char* login, char* senha){
    Usuario *u = (Usuario*)malloc(sizeof(Usuario));
    strcpy(u->login, login);
    strcpy(u->senha, senha);
    u->tentativas = 0;
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
    if (buscar_usuario(*primeiro, login) != NULL) 
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

int remover_usuario(Usuario** primeiro, char* login){
    if(primeiro == NULL || *primeiro == NULL || login == NULL || strlen(login) == 0 ){
        return 0;
    }
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

int login_usuario(Usuario* primeiro, char* login, char* senha){
    
    if(primeiro == NULL || login == NULL || strlen(login) == 0 || senha == NULL || strlen(senha) == 0){
        return 0;
    }

    Usuario* destV = busca_usuario(primeiro, login);
    if(destV == NULL){
        return 0;
    }else{
        if(strcmp(destV->senha, senha) == 0){
            return 1;
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