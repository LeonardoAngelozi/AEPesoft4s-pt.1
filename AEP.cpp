#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


typedef struct tipoEndereco{
	int numero;
	char logradouro,bairro,	cep, cidade,
		 estado, complemento;
}TEndereco;

typedef struct tipoNo{
	TEndereco endereco;
	struct tipoNo *esq, *dir;
}TNo;


TNo* inserir (TNo *raiz, TEndereco *endereco){
	if (raiz == NULL){
		raiz = new TNo;
		raiz->endereco.cep = endereco->cep;
		raiz->esq = NULL;
		raiz->dir = NULL;
	}else{
		if (endereco->cep < raiz->endereco.cep){
			 raiz->esq = inserir (raiz->esq, endereco);
		}
		else{
			raiz->dir = inserir (raiz->dir, endereco);
		}
	}
	return raiz;
}

void lerDados (TEndereco *endereco){
	printf("\n Informe novo valor para endereco(cep): ");
	scanf("%c", &endereco->cep);
	
	printf("\n Informe novo valor para endereco(bairro): ");
	scanf("%c", &endereco->bairro);

	printf("\n Informe novo valor para endereco(cidade): ");
	scanf("%c", &endereco->cidade);	
	
	printf("\n Informe novo valor para endereco(complemento): ");
	scanf("%c", &endereco->complemento);
	
	printf("\n Informe novo valor para endereco(estado): ");
	scanf("%c", &endereco->estado);
	
	printf("\n Informe novo valor para endereco(logradouro): ");
	scanf("%c", &endereco->logradouro);

	printf("\n Informe novo valor para endereco(numero): ");
	scanf("%d", &endereco->numero);

}

void preOrdem (TNo *raiz){
	if (raiz != NULL){
		printf("\n CEP: %c | Estado: %c | Cidade: %c | Bairro: %c | Logradouro: %c | Numero: %d | Complemento: %c", raiz->endereco.cep, raiz->endereco.estado, raiz->endereco.cidade, raiz->endereco.bairro, 
																													raiz->endereco.logradouro, raiz->endereco.numero, raiz->endereco.complemento);
		preOrdem (raiz->esq);
		preOrdem (raiz->dir);
	}
}

void emOrdem (TNo *raiz){
	if (raiz != NULL){
		emOrdem (raiz->esq);
		printf("\n CEP: %c | Estado: %c | Cidade: %c | Bairro: %c | Logradouro: %c | Numero: %d | Complemento: %c", raiz->endereco.cep, raiz->endereco.estado, raiz->endereco.cidade, raiz->endereco.bairro, 
																													raiz->endereco.logradouro, raiz->endereco.numero, raiz->endereco.complemento);
		emOrdem (raiz->dir);
	}
}

void posOrdem (TNo *raiz){
	if (raiz != NULL){
		posOrdem (raiz->esq);
		posOrdem (raiz->dir);
		printf("\n CEP: %c | Estado: %c | Cidade: %c | Bairro: %c | Logradouro: %c | Numero: %d | Complemento: %c", raiz->endereco.cep, raiz->endereco.estado, raiz->endereco.cidade, raiz->endereco.bairro, 
																													raiz->endereco.logradouro, raiz->endereco.numero, raiz->endereco.complemento);
	}
}


int consultarRecursivo (TNo *auxRaiz, int auxValor){
	if (auxRaiz == NULL){
		return 0;
	}else{
		if (auxRaiz->endereco.cep == auxValor){
			return 1;
		}else{
			if (auxValor < auxRaiz->endereco.cep){
				return consultarRecursivo (auxRaiz->esq, auxValor); 
			}else{
				return consultarRecursivo (auxRaiz->dir, auxValor); 
		}
	}
}
}

int sobeMaiorDireita (TNo *aux){
	while (aux->dir != NULL){
		aux = aux->dir;
	}
	return (aux->endereco.cep);
}


TNo* remover (TNo *raiz, int auxValor){
	if (raiz == NULL){
		printf("\n Endereco nao encontrado!");
	}else{
		if (auxValor < raiz->endereco.cep){
			raiz->esq = remover (raiz->esq, auxValor);
		}else{
			if (auxValor > raiz->endereco.cep){
				raiz->dir = remover (raiz->dir, auxValor);
			}else {
				//se o elemento nao tiver sub-arvore direita
					if (raiz->dir == NULL){
						TNo *aux;
						aux = raiz;
						raiz = raiz->esq;
						free(aux);
					}else{
						if (raiz->esq == NULL)
						{
							TNo *aux;
							aux = raiz;
							raiz = raiz->dir;
							free(aux);
						}else{
						raiz->endereco.cep = sobeMaiorDireita (raiz->esq);
						raiz->esq = remover (raiz->esq, raiz->endereco.cep);
					}
				}
			}
		}
	}
	return raiz;
}


int main(){
	TNo *raiz;
	raiz = NULL; 
	
	TEndereco endereco;
	
	int opcao;
	
	do{
		printf("\n 1 - Inserir endereco para arvore");
		printf("\n 2 - Apresentar pre-ordem");
		printf("\n 3 - Apresentar em-ordem");
		printf("\n 4 - Apresentar pos-ordem");
		printf("\n 5 - Consultar endereco");
		printf("\n 6 - Excluir endereco da arvore");
		printf("\n 0 - Sair");
		printf("\n Escolha uma opcao: ");
		scanf("%d", &opcao);
		
		switch (opcao){
			case 1:{
					lerDados(&endereco);
					raiz = inserir (raiz, &endereco); break;
				}
			case 2: {
				if (raiz == NULL){
					printf("\n Arvore vazia! \n");
				}else{
					preOrdem (raiz); break;
				}
			}
			case 3: emOrdem (raiz); break;
			case 4: posOrdem (raiz); break;
			case 5:{
					int auxValor, encontrou;
					printf("\n Informe o cep a ser consultado: ");
					scanf("%d", &auxValor);
					encontrou = consultarRecursivo(raiz, auxValor);
					if (encontrou == 1){
						printf("\n Cep Encontrado!");
					}else{
						printf("\n Cep nao encontrado!");
					}
					getch();
					break;
				}
			case 6:{
					int auxValor;
					printf("\n Informe o endereco para ser excluido");
					scanf("%d", &auxValor);
					raiz = remover (raiz, auxValor);
				}

		}
		
	}while (opcao != 0);
}


