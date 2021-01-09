#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>
#include<string.h>

//Struct para  jogadores
typedef struct nomes{
	char nome[50];
	int peao[4];										
}jogadores_ludo;


//Prototipo da função opções do menu 
void menu();

//Prototipo da função regras do jogo
void regras();

//Prototipo da função para gerar o dado
int dado();

//Prototipo para nome dos jogadores
void nome_jogadores(int quant_jogadores,jogadores_ludo *jogadores);

//Prototipo para zerar todas as casas dos jogadores
void zera_casas(jogadores_ludo *jogadores,int quant_jogadores);

//Mostra jogada dos jogadores
void mostra_jogada(int jogou,int dado,jogadores_ludo *jogadores);

//Prototipo para jogador escolher peão
void escolhe_peao(int *op);

//Prototipo Funcão para somar peças automatico se tiver uma peca só
void soma_pecas_automatico(int jogou,int *somar,jogadores_ludo *jogadores);

//Prototipo função quando sai duas vezes seis no dado
void dois_seis(int jogou,int valor,jogadores_ludo *jogadores);

//Prototipo função quando sai uma vez seis no dado
void um_seis(int jogou,int valor,jogadores_ludo *jogadores);

//Prototipo função pra alternar jogadores quando eles entrarem no jogo
void jogando(int jogou,int *jogar);

//Prototipo função para ver o ganhador do jogo ludo
void ganhador(int jogou,jogadores_ludo *jogadores);

//Prototipo função para somar automatico os valores 
void soma_automatico(int jogou,int valor,jogadores_ludo *jogadores);

//Prototipo função para soma de jogadores
int peao_soma(int jogou,jogadores_ludo *jogadores);

//Prototipo função para limite onde peao nunca podera ultrapassar
int peao_limite(int jogou,jogadores_ludo *jogadores);

//Prototipo função para soma nunca passar de 57
void ajuste_casas(int jogou,int valor,int op,jogadores_ludo *jogadores);

int main(){
	
	//biblioteca para poder Digitar caracteres
	setlocale(LC_ALL,"Portuguese");
	
	//Não gerar numeros repetidos todas as vezes que lançar o dado
	srand ((unsigned)time(NULL));
	
	//alocacao dinamica para nomes dos jogadores
	jogadores_ludo *jogadores = NULL;
	
	//Variaveis para utilização do jogo
	int opcao = 3,ignorar=1,quant_jogadores=0,i=0,tot=0,val=0,valor=0,cont=0,parar=0,jogou=1,seis_dado=0,op,aux,aux1;
	int jogar[4],peoes=0,*somar = &peoes,some=0;
	jogar[0] = 0;	
	jogar[1] = 0;
	jogar[2] = 0;	
	jogar[3] = 0;
	
	//Criação do arquivo para salvar os valores do dado
	FILE *arquivo;
	arquivo = fopen("jogoludo.txt","w+");
	
	do{
		//Menu opcao ja começa com 3 para entar no menu direto
		if(opcao == 3){
			menu();
			scanf("%d",&opcao);		
		}
		
		//Regras do jogo do ludo
		if(opcao == 2){
			regras();
			opcao = 3;
		}
		
		//opcao para jogar o jogo ludo
		if(opcao == 1){
			
			//Trecho de código para entrar somente uma vez quando comecar o jogo
			if(ignorar == 1){	
				do{
					printf("\n\nEscolha a quatidade de jogadores 2 ou 4: ");
					scanf("%d",&quant_jogadores);
						if(quant_jogadores != 2 && quant_jogadores != 4){
							printf("\nOpção Inválida escolha uma opção válida!!!");
						}
				}while(quant_jogadores != 2 && quant_jogadores != 4);
				
				//Trecho da criacao da alocação dinâmica
					jogadores = (jogadores_ludo*) malloc(quant_jogadores*sizeof(jogadores_ludo));
				
					nome_jogadores(quant_jogadores,jogadores);
					i = 0;
					
					//Todas as casas dos jogadores começar com zero
					zera_casas(jogadores,quant_jogadores);
			}
			
			//Lançamento do dado
					tot = dado();
					//variaveis aux para armazenar result dado
					val = tot;
					//variaveis aux para armazenar result dado
					valor = tot;
					
					//Essa opcao para sempre ignorar a parte da criação da alocacção dinâmica
					ignorar=0;
					
					//Essa opcao para sempre entar no jogo
					opcao = 1;
					
					//Esse trecho para mostrar a vez do jogador e o numero que o dado sorteou a variavel jogou vale 1 pelo fato de ser o primeiro jogador
					printf("\n\nJogador %d:\n\nValor dado: %d\n\n",jogou,val);
					
					//Trecho que salva código no arquivo
					fprintf(arquivo,"\n\nJogador %d:\n\nValor dado: %d\n\n",jogou,valor);
					
					//Variável contadora para ajudar a contar a vez no dado
					cont++;
					
					//Variavel para interronper o loop
					parar++;
					
					///Quando ele tirar 6 no dado entra nesse if e volta para cima de novo
					if(tot == 6){
						opcao = 1;
						ignorar = 0;
						seis_dado++;
					}
					
					//Depois que os dois jogadores começarem o jogo
					if(cont == 1 && valor != 6 && jogar[jogou - 1] == 1){
						soma_automatico(jogou-1,valor,jogadores);
						ignorar = 0;
						opcao = 1;
						cont = 0;
						jogou++;
						if(jogou > quant_jogadores){
							jogou = 1;
						}
					}
					
					//Trecho caso na primeira jogada do jogo o jogador tire 6
						if(valor != 6 && cont == 2 && seis_dado == 1 && jogar[jogou - 1] == 1){	
							um_seis(jogou-1,valor,jogadores);	
							cont = 0;
							seis_dado = 0;
							ignorar = 0;
							opcao = 1;
							jogou++;
							if(jogou > quant_jogadores){
								jogou = 1;
							}	
						}
					
					//Trecho caso ele tire 3 vezes o seis no dado
					if(cont == 3 && valor == 6 && seis_dado == 3 && jogar[jogou - 1] == 1){
							mostra_jogada(jogou-1,valor,jogadores);
							ignorar=0;
							opcao = 1;
							cont = 0;
							jogou++;
							if(jogou > quant_jogadores){
								jogou = 1;
							}
							seis_dado = 0;
					}
					
					//Trecho para quando jogador tirar seis no dado duas vezes e na terceira um valor difente de seis
					if(cont == 3 && valor != 6 && seis_dado == 2 && jogar[jogou - 1] == 1){
							dois_seis(jogou-1,valor,jogadores);	
							ignorar = 0;
							opcao = 1;
							cont = 0;
							jogou++;
							if(jogou > quant_jogadores){
								jogou = 1;
							}
							seis_dado = 0;
					}
						
						
					
					//Trecho caso na primeira jogada do jogo o jogador não tire 6
					if(cont == 1 && valor != 6 && jogar[jogou - 1] == 0){
						cont = 0;
						mostra_jogada(jogou-1,valor,jogadores);
						ignorar = 0;
						opcao = 1;
						jogou++;
						if(jogou > quant_jogadores){
							jogou = 1;
						}
					}
					
					//Trecho caso ele tire 3 vezes o seis no dado
					if(cont == 3 && valor == 6 && seis_dado == 3 && jogar[jogou - 1] == 0){
							mostra_jogada(jogou-1,valor,jogadores);
							ignorar=0;
							opcao = 1;
							cont = 0;
							jogou++;
							if(jogou > quant_jogadores){
								jogou = 1;
							}
							seis_dado = 0;
					}
					
					//Trecho caso o jogador tire a primeira jogada seis e depois um valore diferente de seis
					if(cont == 2 && valor != 6 && seis_dado == 1 && jogar[jogou - 1] == 0){ 
							mostra_jogada(jogou-1,valor,jogadores);
							escolhe_peao(&op);
							some = peao_soma(jogou-1,jogadores);
							jogadores[jogou-1].peao[op-1] += some + valor;
							mostra_jogada(jogou-1,valor,jogadores);
							ignorar=0;
							opcao = 1;
							cont = 0;
							jogando(jogou,jogar);
							jogou++;
							//Trecho para nunca a variavel passar de 2 para mostrar jogadores
							if(jogou > quant_jogadores){
								jogou = 1;
							}
							seis_dado = 0;
					}
					
					
					//Trecho para quando jogador tirar seis no dado duas vezes e na terceira um valor difente de seis
					if(cont == 3 && valor != 6 && seis_dado == 2 && jogar[jogou - 1] == 0){
							dois_seis(jogou-1,valor,jogadores);	
							ignorar = 0;
							opcao = 1;
							cont = 0;
							jogando(jogou,jogar);
							jogou++;
							if(jogou > quant_jogadores){
								jogou = 1;
							}
							seis_dado = 0;
					}
					///////////////////////		
													
					//Trecho para parar o jogo para não ficar no loop infinito
					if(parar == 15){
							opcao = 0;
							break;
					}	
		}
		
	}while(opcao !=0 );
	
	return 0;
}

//Função para o menu
void menu(){
	printf("\n0 - Sair");
	printf("\n1 - Jogar");
	printf("\n2 - Regras");
	printf("\nOpcao: ");
	return;
}

//Função para regras do jogo
void regras(){
	printf("\n\n\t\t\tDescrição das Regras: \n\n");
	printf("Ludo é jogado de 2 a 4 jogadores. Cada jogador possui 4 peões.\n\n");
	printf("Cada jogador possui 4 peões. Aquele que levar os 4 peões até o final (triângulo) primeiro, será declarado o vencedor.\n\n");
	printf("O peão só pode ser movido para o início da corrida, na casa de sua respectiva cor,quando um jogador lançar um 6 no dado.\n\n");
	printf("Após colocar um peão no início do tabuleiro o jogador terá um novo lançamento dado.\n\n");
	printf("Se um jogador tirar 3 vezes seis em sequência deve-se passar a vez.\n\n");
	printf("Para chegar à casa final (triângulo), deve-se tirar o valor exato remanescente e terá direito a outra rodada no dado.\n");
	printf("Se não for o caso, ele deverá mover outra peça, se não for possível deve-se passar a vez\n\n");
	printf("Se um peão chegar ao ponto de origem, o jogador pode lançar o dado mais uma vez\n\n");
	printf("As 4 casas que possuem estrelas são consideradas pontos seguros onde os peões adversários não podem ser capturados\n\n");
	printf("As 4 casas que possuem cor são consideradas pontos seguros onde os peões adversários não podem ser capturados\n\n");
	printf("Os peões devem se mover e viajar contornando o tabuleiro até chegar na última casa\n");
	printf("A cada rodada do dado o jogador deve-se movimentar, ou seja, não é permitido abdicar do movimentosalve casos onde o movimento é ilegal\n\n");			
	return ;
}

//Função para nomes dos jogadores
void nome_jogadores(int quant_jogadores,jogadores_ludo *jogadores){
	int i=0;
	for(i=0;i<quant_jogadores;i++){
		printf("\nDigite o nome do %d° Jogador: ",i+1);
		setbuf(stdin,NULL);
		gets(jogadores[i].nome);
	}
}

//Função do dado
int dado(){
	int num;
	num = 1 + rand() % 6;	
	return num;
}

//Função para zerar todas as casas dos jogadores
void zera_casas(jogadores_ludo *jogadores,int quant_jogadores){
	int i,j;
	for(j=0;j<quant_jogadores;j++){
		for(i=0;i<4;i++){
			jogadores[j].peao[i] = 0;
		}
	}	
}

//Função que mostra jogada dos jogadores
void mostra_jogada(int jogou,int dado,jogadores_ludo *jogadores){
	printf("\n\nJogador %d",jogou+1);
	int j;
	printf("\n\nCasas: \n\n");
	for(j=0;j<4;j++){	
		printf("Peão %d:  %d\n",j+1,jogadores[jogou].peao[j]);
	}
	printf("\nValor dado: %d",dado);
	return;	
}

//Função para soma de jogadores
int peao_soma(int jogou,jogadores_ludo *jogadores){
	if(jogou == 0){
		return 1;
	}
	if(jogou == 1){
		return 14;
	}
	if(jogou == 2){
		return 27;
	}
	if(jogou == 3){
		return 40;
	}
}


//Função para lime onde peao nunca podera ultrapassar
int peao_limite(int jogou,jogadores_ludo *jogadores){
	if(jogou == 0){
		return 57;
	}
	if(jogou == 1){
		return 14;
	}
	if(jogou == 2){
		return 27;
	}
	if(jogou == 3){
		return 40;
	}
}

//Função para jogador escolher peão
void escolhe_peao(int *op){
	int opc;
	printf("\n\nEscolha o peão para andar: ");
	scanf("%d",&opc);
	*op = opc;
	return ;
}

//Funcão para somar peças automatico se tiver uma peca só preenchida
void soma_pecas_automatico(int jogou,int *somar,jogadores_ludo *jogadores){
	if(jogadores[jogou].peao[0] != 0 && jogadores[jogou].peao[1] == 0 && jogadores[jogou].peao[2] == 0 && jogadores[jogou].peao[3] == 0){
		*somar = 0;
	}
	else if(jogadores[jogou].peao[0] == 0 && jogadores[jogou].peao[1] != 0 && jogadores[jogou].peao[2] == 0 && jogadores[jogou].peao[3] == 0){
		*somar = 1;
	}
	else if(jogadores[jogou].peao[0] == 0 && jogadores[jogou].peao[1] == 0 && jogadores[jogou].peao[2] != 0 && jogadores[jogou].peao[3] == 0){
		*somar = 2;
	}
	else if(jogadores[jogou].peao[0] == 0 && jogadores[jogou].peao[1] == 0 && jogadores[jogou].peao[2] == 0 && jogadores[jogou].peao[3] != 0){
		*somar = 3;
	}
	else{
		*somar = 4;
	}
}


//Função joga quando caiu duas vezes o numero seis no dado
void dois_seis(int jogou,int valor,jogadores_ludo *jogadores){
	
	int op,aux,aux1,tot=0;
	mostra_jogada(jogou,valor,jogadores);
		escolhe_peao(&op);
		aux = op;
		tot = peao_soma(jogou,jogadores);
		jogadores[jogou].peao[op-1] += tot;
		mostra_jogada(jogou,valor,jogadores);
		escolhe_peao(&op);
		aux1 = op;
		if(aux == aux1){
			jogadores[jogou].peao[op-1] += 6 + valor;
			mostra_jogada(jogou,valor,jogadores);
		}
		else{
			tot = peao_soma(jogou,jogadores);
			jogadores[jogou].peao[op-1] += tot; 
			mostra_jogada(jogou,valor,jogadores);
			//Escolhe o peao na terceira jogada
			escolhe_peao(&op);
			if(op == aux){
				jogadores[jogou].peao[op-1] += valor;
				mostra_jogada(jogou,valor,jogadores);
			}
			if(op == aux1){
				jogadores[jogou].peao[op-1] += valor;
				mostra_jogada(jogou,valor,jogadores);
			}
			if(op != aux && op!= aux1 ){
				do{
					printf("\nOpção Inválida!!!Escolha o peao%d ou o peao%d",aux,aux1);
					escolhe_peao(&op);
					if(op == aux){
						jogadores[jogou].peao[op-1] += valor;
						mostra_jogada(jogou,valor,jogadores);
						break;
					}
					if(op == aux1){
						jogadores[jogou].peao[op-1] += valor;
						mostra_jogada(jogou,valor,jogadores);
						break;
					}			
					}while(op != aux || op != aux1);
			}
		}
		ganhador(jogou,jogadores);
		return ;	
}

//Função joga quando caiu uma vez o numero seis no dado e depois diferente de seis
void um_seis(int jogou,int valor,jogadores_ludo *jogadores){
	int op,tot=0;
	escolhe_peao(&op);
    tot = peao_soma(jogou,jogadores);
	if(jogadores[jogou].peao[op-1] != 0){
		jogadores[jogou].peao[op-1] += 6;
		mostra_jogada(jogou,valor,jogadores);
	}
	if(jogadores[jogou].peao[op-1] == 0){
		jogadores[jogou].peao[op-1] +=  tot;
		mostra_jogada(jogou,valor,jogadores);
	}
	escolhe_peao(&op);
	if(jogadores[jogou].peao[op-1] != 0){
		jogadores[jogou].peao[op-1] +=  valor;
		mostra_jogada(jogou,valor,jogadores);
	}
	ganhador(jogou,jogadores);
	return ;
}

//Função para alternar jogadores
void jogando(int jogou,int *jogar){
	if(jogou == 1){
		jogar[jogou - 1] = 1;
	}
	if(jogou == 2){
		jogar[jogou - 1] = 1;
	}
	if(jogou == 3){
		jogar[jogou - 1] = 1;
	}
	if(jogou == 4){
		jogar[jogou - 1] = 1;
	}
	return ;
}

//Função para ver quem é o ganhador do jogo
void ganhador(int jogou,jogadores_ludo *jogadores){
	int total=0;
	total = peao_limite(jogou,jogadores);
	if(jogadores[jogou].peao[0] == total && jogadores[jogou].peao[1] == total && jogadores[jogou].peao[2] == total && jogadores[jogou].peao[3] == total){
		printf("Parabéns %s você ganhou o jogo ludo!!!!",jogadores[jogou].nome);
	}
	return ;
}

//Função para somar automatico
void soma_automatico(int jogou,int valor,jogadores_ludo *jogadores){
	int peoes,*somar = &peoes,op;
	mostra_jogada(jogou,valor,jogadores);
	soma_pecas_automatico(jogou,somar,jogadores);
	if(*somar >= 0 && *somar<=3){
			jogadores[jogou].peao[*somar] += valor;
			mostra_jogada(jogou,valor,jogadores);		
	}
	else{
		escolhe_peao(&op);
		jogadores[jogou].peao[op-1] += valor;
		mostra_jogada(jogou,valor,jogadores);		
	}
	ganhador(jogou,jogadores);
	return;
}

//Função para soma nunca passar de determinada casa
void ajuste_casas(int jogou,int valor,int op,jogadores_ludo *jogadores){
	int auxiliar=0,total=0;
	if(jogou == 0){
		if(jogadores[jogou].peao[op-1] + valor > 57){
			
		}
		else{
			jogadores[jogou].peao[op-1] += valor;
		}
	}
	if(jogou == 1){
		if(jogadores[jogou].peao[op-1] + valor > 57){
			auxiliar = (jogadores[jogou].peao[op-1] + valor);
			total = auxiliar - 57;
			jogadores[jogou].peao[op-1] = total;
		}		
	}
	if(jogou == 2){
		if(jogadores[jogou].peao[op-1] + valor > 57){
			auxiliar = (jogadores[jogou].peao[op-1] + valor);
			total = auxiliar - 57;
			jogadores[jogou].peao[op-1] = total;
		}
	}
	if(jogou == 3){
		if(jogadores[jogou].peao[op-1] + valor > 57){
			auxiliar = (jogadores[jogou].peao[op-1] + valor);
			total = auxiliar - 57;
			jogadores[jogou].peao[op-1] = total;
		}
	}
		return ;
}
