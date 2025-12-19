#ifndef USUARIO_H
#define USUARIO_H

typedef struct Usuario Usuario; 

Usuario* cria_usuario(char* login, char* senha);
Usuario* cria_admin(char* login, char* senha);
void libera_usuario(Usuario* lista);
int cadastrar_usuario(Usuario** lista, char* login, char* senha);
Usuario* busca_usuario(Usuario* lista, char* login);
int remover_usuario(Usuario** lista, char* login);
int remover_total_sistema_usuario(Usuario** primeiro, char* login);
int login_usuario(Usuario* lista, char* login, char* senha);
void listar_usuarios(Usuario* lista);
int verifica_status(Usuario* lista, char* login);
int valida_user_admin(Usuario* lista, char* login);
int desbloqueia_usuario(Usuario* primeiro, char* login);
int altera_senha_usuario(Usuario* primeiro, char* login, char* senha, char* nova_senha);
#endif