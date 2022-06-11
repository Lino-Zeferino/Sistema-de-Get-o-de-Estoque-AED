#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Responsavel pelo Tratamento de String

//estrutura de um tipo de dado produto
typedef struct{
	int id; //identificador unico para cada produto
	char nome[30];
	float preco;
	int quantidade;//quantidade do produto

}Produto;
//estrutura do no
typedef struct no{
	Produto dados;
	struct no* prox;
}No;
//estrutura da lista
typedef struct{
	No* cabeca;
	int qtd;
}Lista;



//////////////////////////////////////////////////////////////////////////////////
//Prototipos das Funcoes

void menu_produto (Lista *lista);
Lista * criarLista();
Produto criarProduto (int id, char nome [30], float preco,int qtd);
No *criarNoProduto(Produto produto);
int isVazia_Lista (Lista lista);
int iserir_produto(Lista *lista, No *no);
int iserir_produto_temporaria(Lista *lista, No *no);
No* anterior(Lista* lista, No*no);
int remover_produto(Lista *lista, int id);
void mostra_produto(Produto produto);
void listar_produto(Lista lista);
No* pesquisar_produto(Lista*lista, int id);
int iserir_produto_pos(Lista*lista, No*no,int id);
int guardarListaEleitorA( Lista* lista);
int regarregarListaEleitorA(Lista* lista);
/////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) 
{

	Lista* lista = criarLista();
	regarregarListaEleitorA(lista);
	
	
	 menu_produto (lista);
	
	system("pause");	
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////
//funcao que Aloca espaço da Memoria da lista
Lista * criarLista(){
	Lista* li= (Lista*) malloc(sizeof(Lista));// Aloca um espaço na memoria do computador
	li->cabeca = NULL;
	li->qtd = 0;
	return li;
}

//FUNCOA QUE FAZ A LEITURA DOS DADOS DE UM Produto
Produto criarProduto (int id, char nome [30], float preco,int qtd) {
	Produto p;
	p.id = id;
	strcpy (p.nome, nome);// copia a string da variavel nome para o nome da estrutura
	p.preco = preco;
	p.quantidade = qtd;
	return p;
}//FIM DA FUNCAO
//FUNCOA QUERESPONSAVEL POR CRIAR UM NO E  ADICIONAR UM Produto
No *criarNoProduto(Produto produto) {
	No *no = (No*) malloc(sizeof(No));// Reserva espaço na memoria do computador para o no
	no->dados = produto;
	no->prox = NULL;
	return no;
}//FIM DA FUNCAO
// FUNCAO QUE VERIFIACA SE A LISTA DE Produto ESTA VAZIA
int isVazia_Lista (Lista lista) {
	return lista.cabeca == NULL;// retorna 1 se estiver vazia caso não retorna 0
}//FIM DA FUNCAO

// FUNCAO RESPONSAVEL POR ADICIONAR UM PRODUTO NA LISTA
int iserir_produto(Lista *lista, No *no) {
	if (isVazia_Lista(*lista)) {
		lista->cabeca = no;
		lista->qtd++;
		return 1;
	}
	No *aux = lista->cabeca;
	while (aux->prox != NULL){
		aux = aux->prox;
	}
	aux->prox = no;
	lista->qtd++;
	return 1;
}//FIM DA FUNCAO

// FUNCOA RESPONSAVEL POR ADICIONAR UM PRODUTO NA LISTA
int iserir_produto_temporaria(Lista *lista, No *no) {
	if (isVazia_Lista(*lista)) {
		lista->cabeca = no;
		return 1;
	}
	No *aux = lista->cabeca;
	while (aux->prox != NULL){
		aux = aux->prox;
	}
	aux->prox = no;

	return 1;
}//FIM DA FUNCAO
//FUNCAO AUXILIAR QUE RETORNA UM PRODUTO ANTERIOR
No* anterior(Lista* lista, No*no){
	if(no == lista->cabeca) return NULL;
	No* aux = lista->cabeca;
	while(aux != NULL){
		if(aux->prox == no){
			return aux;
		}
		aux = aux->prox;
	}
	return NULL;
}
// FUNCAO QUE REMOVE UM PRODUTO DA LISTA

int remover_produto(Lista *lista, int id) {
	
	if(isVazia_Lista(*lista)){
		return 0;
	}
	
		if(id > 0 && id <= lista->qtd){
			No* aux = lista->cabeca;
			while(aux != NULL && aux->dados.id != id){
				aux = aux->prox;
			}if(aux != NULL){
				if(aux == lista->cabeca){
					lista->cabeca = aux->prox;
					free(aux);
					return 1;
		 		}
					anterior(lista, aux)->prox = aux->prox;
					free(aux);
				
					return 1;
			
			
		}
		
	}
	return -1;
}//FIM DA FUNCAO

// FUNCAO RESPONSAVEL POR MOSTRAR UM DETERMINADO PRODUTO

void mostra_produto(Produto produto) {
	printf("::::::::::::::::**PRODUTO**::::::::::::::::::::::\n");
	printf ("Id: %d\n", produto.id);
	printf ("Nome: %s\n", produto.nome);
	printf ("Preco: %.2f\n", produto.preco);
	printf ("Quantidade: %d\n", produto.quantidade);
	puts (":::::::::::::::::::::::::::::::::::\n");
}//FIM DA FUNCAO
// FUNCAO RESPONSAVEL POR LISTAR TODOS OS PRODUTOS DO SISTEMA
void listar_produto(Lista lista) {
	if (isVazia_Lista(lista)) {
		puts (" Lista Vazia !!!");
	}
	No *aux = lista.cabeca;
	while (aux != NULL) {
		mostra_produto (aux->dados);
		aux = aux->prox;
	}
}//FIM DA FUNCAO
// FUNCAO RESPONSAVEL POR FAZER A PESQUISA DE UM PRODUTO
No* pesquisar_produto(Lista*lista, int id){
		if(isVazia_Lista(*lista)){
			return NULL;
		}
		//porque nao temos na lista um produto com id negativo e nem igual a zero e um id maior que a quantidade
		if(id > 0 && id <= lista->qtd){
			No* aux = lista->cabeca;
			while(aux != NULL && aux->dados.id != id){
				aux = aux->prox;
			}if(aux == NULL){
		 		return NULL;
			}
				return aux;
			
		}
		return NULL;
}
// FUNCAO RESPONSAVEL POR ADICIONAR UM PRODUTO NUMA DETERMINADA POSICAO
int iserir_produto_pos(Lista*lista, No*no, int id){
		if(isVazia_Lista(*lista)){
			lista->cabeca = no;
			return 1;
		}
		
		int i = 1;
			No* aux = lista->cabeca;
			while(aux != NULL && i < id){
				i++;
				aux = aux->prox;
			}if(aux != NULL){
				if(anterior(lista,aux)== NULL){
					no->prox = aux;
					lista->cabeca = no;
					return 1;
				}
				no->prox = aux;
				anterior(lista,aux)->prox = no;
				return 1;
			}
			iserir_produto_temporaria(lista,no); 
	
}
// GUARDAR ELEITOR NO ARQUIVO
int guardarListaEleitorA( Lista* lista){
	FILE* file = fopen("Arquivo Produtos.txt", "w");// CRAR UM ARQUIVO
	if(lista == NULL) return -1; //lista inexistente
	if(isVazia_Lista(*lista)) return 0;// Lista sem Eleitor para guardar
	No* no = lista->cabeca;
	
	while(no != NULL){
			fprintf(file, "%d\n", no->dados.id);// PERMITE ESCREVER NO ARQUIVO
			fprintf(file, "%s\n", no->dados.nome);
			fprintf(file, "%f\n", no->dados.preco);
			fprintf(file, "%d\n", no->dados.quantidade);
			fprintf(file, "%s\n",".");	
		no = no->prox;
	}
	fclose(file);
	return 1;
}/*concluido*/	
////////////////////////////////////////////////
// FUNCAO  RESPONSAVEL POR TRAZER OS DADOS DO SISTEMA PARA AS LISTAS
int regarregarListaEleitorA(Lista* lista){
	FILE* file;
	
file = fopen("Arquivo Produtos.txt", "r"); // LEITURA DO ARQUIVO
	 Produto e;
	
	int ax = 0;

	if(file != NULL){
		int i;
			char linha[50];
			while(!feof(file)){
				i = 0;
				for(i = 0; i <=4; i++){
					fscanf(file,"%s",linha);
					if(strcmp(linha,".")!= 0){
					switch(i){
						case 0:
						ax = atoi(linha);
						e.id = ax;
						break;
						case 1:
								strcpy(e.nome, linha);
						break;
						case 2:
							ax = atoi(linha);
							e.preco = ax;
						
						break;
					
						case 3:
							ax = atoi(linha);
							e.quantidade = ax;
							iserir_produto(lista, criarNoProduto(criarProduto (e.id,e.nome,e.preco,e.quantidade)));
						break;
								
					}
			}else{
				break;
			}
				}
			
			}
	
	}
	
return 0;
}//fim da funcao

// FUNCAO RESPONSAVEL POR MOSTRAR UM SUB-MENU RELACIONADO AO PRODUTO
void menu_produto (Lista *lista) {
	
	int id, numero;

	char nome [30];
	int quantidade;
	float preco;
	
	int op;
	do {
		puts (":::::::::::::::***MENU DO SISTEMA DE GESTAO DE ESTOQUE***::::::::::::::::::::\n");
	
		puts ("1- Cadastro de Produto para Lista");
		puts ("2- Visualizacao de Estoque  (Listar Produtos do Sistema)");
		puts ("3- Pesquisar(consultar) Produto do sitema");
		puts ("4- Acerto(Editar)de Produto do Sistema");
		puts ("5- Remover(eliminar) um Produto do Sistema");
		puts ("6- Entrada(Guardar) de Produto no sistema ");
		puts ("0- Sair");
		printf ("Informe a opcao: ");
		scanf ("%d", &op);
		system ("cls || clear");//FUNCAO QUE LIMPA A TELA
		switch (op) {
			case 1:
					puts ("******Cadastrando Produto******\n");
				printf ("\nNome: ");
				fflush (stdin);
				scanf("%s",nome);
				printf ("Preco: ");
				scanf("%f",&preco);
				printf ("Quantidade: ");
				scanf ("%d", &quantidade);
				lista->qtd++;
				if(iserir_produto_temporaria(lista, criarNoProduto(criarProduto (lista->qtd, nome,preco, quantidade)))){
					puts("Produto cadastrado com sucesso!!!");
					system ("pause"); system ("cls || clear");
				}else{
						puts("Erro ao cadastrar o Produto!!");
						system ("pause"); system ("cls || clear");
					
					}
				break;
			case 2:
					system ("pause"); system ("cls || clear");
						listar_produto(*lista);
				
				
			
			break;
			case 3: 
				printf("Informe o Id do Produto");
				scanf("%d",&id);
				if(pesquisar_produto(lista, id)== NULL){
					puts("Nenhum Produto encontrado");
					system ("pause"); system ("cls || clear");
				}else{
					mostra_produto(pesquisar_produto(lista, id)->dados);
					system ("pause"); system ("cls || clear");
				}
				
			break;		
			case 4:
				printf("Informe o Id do Produto");
					scanf("%d",&id);
				No*aux = pesquisar_produto(lista,  id);
				if(aux == NULL){
					puts("Nenhum Produto encontrado com este Id");
					system ("pause"); system ("cls || clear");
				}else{
					int n = aux->dados.id;
					puts (":::::::::: Alterando dados do Produto ::::::::::\n");
					mostra_produto(aux->dados);
					
				printf ("\n Novo nome:\n");
				fflush (stdin);
				scanf("%s",nome);
				printf ("Novo preco:\n");
					scanf("%f",&preco);
				printf ("Nova quantidade: ");
				
				scanf ("%d", &quantidade);
					remover_produto(lista, id);
				if(iserir_produto_pos(lista, criarNoProduto(criarProduto (n, nome,preco,quantidade)),id)){
					puts("Produto Alterado com Sucesso.");
					system ("pause"); system ("cls || clear");	
				}else{
					puts("Erro na Alteracao do Produto.");
					system ("pause"); system ("cls || clear");
				}
			}	
		
				
				
			break;
			case 5:
				printf("Informe o Id do Produto");
				scanf("%d",&id);
				if(remover_produto(lista, id)){
					puts("Produto Eliminado com sucesso!!!");
					system ("pause"); system ("cls || clear");
				}else{
					puts("Erro na eliminacao do Produto.");
					system ("pause"); system ("cls || clear");
				}	
	
			break;
			case 6:
				if(guardarListaEleitorA(lista)){
					printf("Dados Salvos no Sistema\n");
					system ("pause"); system ("cls || clear");
				}else{
					printf("Erro Nao salvou!!!!\n");
					system ("pause"); system ("cls || clear");
				
				}
				
			break;
			case 0:
				
				printf("Deseja Quardar no Sitema as Ultimas Alteracoes? 1-Sim\t0-Nao\n");
				
				scanf("%d",&numero);
				if(numero == 1){
					if(guardarListaEleitorA(lista)){
						printf("Dados Salvos no Sistema\n");
					
					op = -1;
				}else{
					printf("Nao salvou!!!!\n");
				
					op = -1;
				}
				
			break;
			default:
					printf("Opcao Invalida!!!!\n");
				
								
		}
	  }
	} while (op != -1);
}//FIM DA FUNCAO




