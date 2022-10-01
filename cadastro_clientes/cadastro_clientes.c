/*
Autor: Michel Macena
Programa simples para exemplificar um cadastro de clientes.
Versão simplificada do exercício do professor Newton C.
link: https://sites.google.com/site/profnewtonc/trabalhoav1

para compilar: gcc -Wall cadastro_clientes.c -o cadastro_clientes


*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define MAXIMO_CLIENTES 1000
#define VERDADEIRO  	1
#define FALSO 			0



typedef struct Cliente
{
	int  	codigo;
	char 	nome[200];
	char 	cpf[15];
	char 	telefone[10];
	float 	credito;
	float 	divida;
	char 	obs[300];

}Cliente;


void le_entrada(char *string, int numero_caracteres)
{

	fgets(string, numero_caracteres, stdin);

	//Retira a quebra de linha da string
	string[strcspn(string, "\n")] = '\0';

}



void imprime_cliente(Cliente cliente)
{
	printf("\n----------------\n");
	printf("Nome: %s\n", cliente.nome);
	printf("Código: %d\n", cliente.codigo);
	printf("Cpf: %s\n", cliente.cpf);
	printf("Telefone: %s\n", cliente.telefone);
	printf("Crédito: %f\n", cliente.credito);
	printf("Dívida: %f\n", cliente.divida);
	printf("Observação: %s\n", cliente.obs);

}

int busca_cliente(Cliente *clientes, int codigo_busca)
{
	
	int i;

	for(i = 0; i < MAXIMO_CLIENTES; i++)
	{

		if(codigo_busca == clientes[i].codigo)
		{

			//Se encontrar o cliente retorna o índice do mesmo
			return i;
		}
	}

	//Cliente não encontrado!
	return -1;
}


int main()
{
	
	Cliente clientes[MAXIMO_CLIENTES];

	int i;

	int saida = FALSO;
	int opcao;
	int n_clientes_cadastrados = 0;
	int codigo_busca;
	int indice_cliente;
	int codigo_escolhido;
	int codigo_valido = FALSO;	
	int opcao_lista;
	char alteracao;
	float registro_divida_pag;


	//-1 indica uma ficha disponível, isto é não está com
	//cliente cadastrado ou o cliente da ficha foi excluído do sistema.
	//No começo do programa todas as fichas estão disponíveis.
	for(i = 0; i < MAXIMO_CLIENTES; i++)
	{
		clientes[i].codigo = -1;
	}


	while(!saida)
	{

		printf("\n==CADASTRO DE CLIENTES==\n"
			"Clientes cadastrados: %d\n"
			"Menu principal\n"
			"------------------\n"
			"[1] - Cadastrar cliente\n"
			"[2] - Consultar  cliente\n"
			"[3] - Alterar cliente\n"
			"[4] - Excluir cliente\n"
			"[5] - Registrar dívida/pagamento\n"
			"[6] - Listar clientes/devedores\n"
			"[0] - Sai do programa\n", n_clientes_cadastrados);

		scanf("%d", &opcao);

		
		switch(opcao)
		{
			

			case 0:

				saida = VERDADEIRO;

			break;

			case 1:
				
				//Pede código do cliente e verifica se já está em uso
				do
				{
					printf("Insira o código do cliente: ");
					scanf("%d", &codigo_escolhido);
					getchar();

					if(busca_cliente(clientes, codigo_escolhido) >= 0)
					{
						printf("Código já escolhido!\n");
						codigo_valido = FALSO;
					}
					else
					{
						codigo_valido = VERDADEIRO;
					}

				}while(!codigo_valido);


				//Busca primeira ficha disponível
				i = 0;
				while(clientes[i].codigo >= 0)
				{
					i++;
				}

				//Assim que verificou o código e achou uma ficha disponível,
				//armazena o código.
				clientes[i].codigo = codigo_escolhido;
				
				printf("Insira nome do cliente: ");
				le_entrada(clientes[i].nome, 200);

				printf("Insira o CPF do cliente: ");
				le_entrada(clientes[i].cpf, 15);

				printf("Insira o telefone do cliente: ");
				le_entrada(clientes[i].telefone, 10);

				printf("Insira o crédito do cliente: ");
				scanf("%f", &clientes[i].credito);

				printf("Insira a dívida do cliente: ");
				scanf("%f", &clientes[i].divida);

				getchar();
				
				printf("Alguma observação para o cliente?  ");
				le_entrada(clientes[i].obs, 300);
				
				printf("[A:] Cliente cadastrado!\n");

				n_clientes_cadastrados++;
			
			break;

			case 2:

				printf("Insira o código do cliente para busca:\n");

				scanf("%d", &codigo_busca);

				indice_cliente = busca_cliente(clientes, codigo_busca);

				//Verifica se cliente está cadastrado
				if(indice_cliente >= 0)
				{
					imprime_cliente(clientes[indice_cliente]);

				}
				else
				{
					printf("[A:] Cliente não encontrado!\n");
				}

			break;

			case 3:

				printf("Insira o código do cliente para alteração:\n");

				scanf("%d", &codigo_busca);

				getchar();

				indice_cliente = busca_cliente(clientes, codigo_busca);

				if(indice_cliente >=0)
				{
					imprime_cliente(clientes[indice_cliente]);

					printf("\nDeseja alterar o nome do cliente? digite 's' para sim ou 'n' para não!");
					scanf("%c", &alteracao);
					getchar();

					if(alteracao == 's')
					{
						printf("Insira o novo nome do cliente: ");
						le_entrada(clientes[i].nome, 200);
					}
					printf("\nDeseja alterar o CPF do cliente? digite 's' para sim ou 'n' para não!");
					scanf("%c", &alteracao);
					getchar();
					if(alteracao == 's')
					{
						printf("Insira o novo CPF do cliente: ");
						le_entrada(clientes[i].cpf, 15);

					}

					printf("\nDeseja alterar o telefone do cliente? digite 's' para sim ou 'n' para não!");
					scanf("%c", &alteracao);
					getchar();
					if(alteracao == 's')
					{
						printf("Insira o novo telefone do cliente: ");
						le_entrada(clientes[i].telefone, 10);

					}

					printf("\nDeseja alterar o crédito do cliente? digite 's' para sim ou 'n' para não!");
					scanf("%c", &alteracao);
					getchar();
					if(alteracao == 's')
					{
						printf("Insira o novo crédito do cliente: ");
						scanf("%f", &clientes[indice_cliente].credito);
						getchar();
					}

					printf("\nDeseja alterar a dívida do cliente? digite 's' para sim ou 'n' para não!");
					scanf("%c", &alteracao);
					getchar();
					if(alteracao == 's')
					{
						printf("Insira o novo valor da dívida do cliente: ");
						scanf("%f", &clientes[indice_cliente].divida);
						getchar();
					}

					printf("\nDeseja alterar a observação para o cliente? digite 's' para sim ou 'n' para não!");
					scanf("%c", &alteracao);
					getchar();
					if(alteracao == 's')
					{
						printf("Insira a nova observação para o cliente: ");
						le_entrada(clientes[i].obs, 300);
					}

					printf("[A:] Alterações feitas!\n");
					
				}
				else
				{
					printf("[A:] Cliente não encontrado!\n");
				}


			break;

			case 4:

				printf("Insira o código do cliente para exclusão: ");

				scanf("%d", &codigo_busca);

				indice_cliente = busca_cliente(clientes, codigo_busca);

				if(indice_cliente >=0)
				{
					clientes[i].codigo = -1;

					n_clientes_cadastrados--;

					printf("[A:] Cliente excluído!\n");
				}
				else
				{
					printf("[A:] Cliente não encontrado!\n");
				}

			break;

			case 5:
				printf("Insira o código do cliente para registrar dívida ou pagamento do cliente:\n");

				scanf("%d", &codigo_busca);

				indice_cliente = busca_cliente(clientes, codigo_busca);

				if(indice_cliente >= 0)
				{
					printf("Insira o valor da dívida ou pagamento."
					    "\nPara dívida insira um valor negativo! ");

					scanf("%f", &registro_divida_pag);

					
					//Como o valor inserido de dívida é negativo, a dívida aumenta (menos com menos dá mais!)
					//Quando o valor inserido é pagamento é positivo, portanto a dívida diminui.
					if(clientes[indice_cliente].divida - registro_divida_pag > clientes[indice_cliente].credito)
					{
						printf("[A:] Crédito insuficiente! dívida não pode ser registrada!\n");
					}
					else if(clientes[indice_cliente].divida - registro_divida_pag < 0.0)
					{
						
						clientes[indice_cliente].credito += -1*(clientes[indice_cliente].divida - registro_divida_pag);

						clientes[indice_cliente].divida = 0.0;

						printf("[A:] Dívida quitada! O saldo restante será acrescentado ao crédito\n");
					}
					else
					{
						clientes[indice_cliente].divida -= registro_divida_pag;
					}
					

				}
				else
				{
					printf("[A:] Cliente não encontrado!\n");
				}


			break;
			
			case 6:

				if(n_clientes_cadastrados > 0)
				{
					printf("[0] - Listar todos os clientes\n"
					   	   "[1] - Listar somentes os clientes devedores\n"
					   	   "Para desistir insira qualquer outro caracter\n");

					scanf("%d", &opcao_lista);

					switch(opcao_lista)
					{
						case 0:
							printf("--TODOS OS CLIENTES--\n\n");

							for(i = 0; i < MAXIMO_CLIENTES; i++)
							{
								if(clientes[i].codigo > -1)
								{
									imprime_cliente(clientes[i]);
								}
							}

							printf("\n--FIM DA LISTA--\n");
						break;

						case 1:
							printf("--SOMENTE OS DEVEDORES--\n\n");

							for(i = 0; i < MAXIMO_CLIENTES; i++)
							{
								if(clientes[i].codigo > -1 && clientes[i].divida > 0.0)
								{
									imprime_cliente(clientes[i]);
								}
							}

							printf("\n--FIM DA LISTA--\n");
						break;

						default:
							//Nada
						break;
					}

				}
				else
				{
					printf("[A:] Nenhum cliente cadastrado ainda!\n");
				}

				


			break;

			default:

				printf("[A:] Opção não reconhecida!\n");

			break;

		}// Switch

	}//While



	printf("Obrigado e até a próxima!\n");
	
	return 0;


}


