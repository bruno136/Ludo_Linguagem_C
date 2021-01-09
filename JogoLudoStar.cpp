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


//Prototipo da fun��o op��es do menu 
void menu();

//Prototipo da fun��o regras do jogo
void regras();

//Prototipo da fun��o para gerar o dado
int dado();

//Prototipo para nome dos jogadores
void nome_jogadores(int quant_jogadores,jogadores_ludo *jogadores);

//Prototipo para zerar todas as casas dos jogadores
void zera_casas(jogadores_ludo *jogadores,int quant_jogadores);

//Mostra jogada dos jogadores
void mostra_jogada(int jogou,int dado,jogadores_ludo *jogadores);

//Prototipo para jogador escolher pe�o
void escolhe_peao(int *op);

//Prototipo Func�o para somar pe�as automatico se tiver uma peca s�
void soma_pecas_automatico(int jogou,int *somar,jogadores_ludo *jogadores);

//Prototipo fun��o quando sai duas vezes seis no dado
void dois_seis(int jogou,int valor,jogadores_ludo *jogadores);

//Prototipo fun��o quando sai uma vez seis no dado
void um_seis(int jogou,int valor,jogadores_ludo *jogadores);

//Prototipo fun��o pra alternar jogadores quando eles entrarem no jogo
void jogando(int jogou,int *jogar);

//Prototipo fun��o para ver o ganhador do jogo ludo
void ganhador(int jogou,jogadores_ludo *jogadores);

//Prototipo fun��o para somar automatico os valores 
void soma_automatico(int jogou,int valor,jogadores_ludo *jogadores);

//Prototipo fun��o para soma de jogadores
int peao_soma(int jogou,jogadores_ludo *jogadores);

//Prototipo fun��o para limite onde peao nunca podera ultrapassar
int peao_limite(int jogou,jogadores_ludo *jogadores);

//Prototipo fun��o para soma nunca passar de 57
void ajuste_casas(int jogou,int valor,int op,jogadores_ludo *jogadores);

int main(){
	
	//biblioteca para poder Digitar caracteres
	setlocale(LC_ALL,"Portuguese");
	
	//N�o gerar numeros repetidos todas as vezes que lan�ar o dado
	srand ((unsigned)time(NULL));
	
	//alocacao dinamica para nomes dos jogadores
	jogadores_ludo *jogadores = NULL;
	
	//Variaveis para utiliza��o do jogo
	int opcao = 3,ignorar=1,quant_jogadores=0,i=0,tot=0,val=0,valor=0,cont=0,parar=0,jogou=1,seis_dado=0,op,aux,aux1;
	int jogar[4],peoes=0,*somar = &peoes,some=0;
	jogar[0] = 0;	
	jogar[1] = 0;
	jogar[2] = 0;	
	jogar[3] = 0;
	
	//Cria��o do arquivo para salvar os valores do dado
	FILE *arquivo;
	arquivo = fopen("jogoludo.txt","w+");
	
	do{
		//Menu opcao ja come�a com 3 para entar no menu direto
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
			
			//Trecho de c�digo para entrar somente uma vez quando comecar o jogo
			if(ignorar == 1){	
				do{
					printf("\n\nEscolha a quatidade de jogadores 2 ou 4: ");
					scanf("%d",&quant_jogadores);
						if(quant_jogadores != 2 && quant_jogadores != 4){
							printf("\nOp��o Inv�lida escolha uma op��o v�lida!!!");
						}
				}while(quant_jogadores != 2 && quant_jogadores != 4);
				
				//Trecho da criacao da aloca��o din�mica
					jogadores = (jogadores_ludo*) malloc(quant_jogadores*sizeof(jogadores_ludo));
				
					nome_jogadores(quant_jogadores,jogadores);
					i = 0;
					
					//Todas as casas dos jogadores come�ar com zero
					zera_casas(jogadores,quant_jogadores);
			}
			
			//Lan�amento do dado
					tot = dado();
					//variaveis aux para armazenar result dado
					val = tot;
					//variaveis aux para armazenar result dado
					valor = tot;
					
					//Essa opcao para sempre ignorar a parte da cria��o da alocac��o din�mica
					ignorar=0;
					
					//Essa opcao para sempre entar no jogo
					opcao = 1;
					
					//Esse trecho para mostrar a vez do jogador e o numero que o dado sorteou a variavel jogou vale 1 pelo fato de ser o primeiro jogador
					printf("\n\nJogador %d:\n\nValor dado: %d\n\n",jogou,val);
					
					//Trecho que salva c�digo no arquivo
					fprintf(arquivo,"\n\nJogador %d:\n\nValor dado: %d\n\n",jogou,valor);
					
					//Vari�vel contadora para ajudar a contar a vez no dado
					cont++;
					
					//Variavel para interronper o loop
					parar++;
					
					///Quando ele tirar 6 no dado entra nesse if e volta para cima de novo
					if(tot == 6){
						opcao = 1;
						ignorar = 0;
						seis_dado++;
					}
					
					//Depois que os dois jogadores come�arem o jogo
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
						
						
					
					//Trecho caso na primeira jogada do jogo o jogador n�o tire 6
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
													
					//Trecho para parar o jogo para n�o ficar no loop infinito
					if(parar == 15){
							opcao = 0;
							break;
					}	
		}
		
	}while(opcao !=0 );
	
	return 0;
}

//Fun��o para o menu
void menu(){
	printf("\n0 - Sair");
	printf("\n1 - Jogar");
	printf("\n2 - Regras");
	printf("\nOpcao: ");
	return;
}

//Fun��o para regras do jogo
void regras(){
	printf("\n\n\t\t\tDescri��o das Regras: \n\n");
	printf("Ludo � jogado de 2 a 4 jogadores. Cada jogador possui 4 pe�es.\n\n");
	printf("Cada jogador possui 4 pe�es. Aquele que levar os 4 pe�es at� o final (tri�ngulo) primeiro, ser� declarado o vencedor.\n\n");
	printf("O pe�o s� pode ser movido para o in�cio da corrida, na casa de sua respectiva cor,quando um jogador lan�ar um 6 no dado.\n\n");
	printf("Ap�s colocar um pe�o no in�cio do tabuleiro o jogador ter� um novo lan�amento dado.\n\n");
	printf("Se um jogador tirar 3 vezes seis em sequ�ncia deve-se passar a vez.\n\n");
	printf("Para chegar � casa final (tri�ngulo), deve-se tirar o valor exato remanescente e ter� direito a outra rodada no dado.\n");
	printf("Se n�o for o caso, ele dever� mover outra pe�a, se n�o for poss�vel deve-se passar a vez\n\n");
	printf("Se um pe�o chegar ao ponto de origem, o jogador pode lan�ar o dado mais uma vez\n\n");
	printf("As 4 casas que possuem estrelas s�o consideradas pontos seguros onde os pe�es advers�rios n�o podem ser capturados\n\n");
	printf("As 4 casas que possuem cor s�o consideradas pontos seguros onde os pe�es advers�rios n�o podem ser capturados\n\n");
	printf("Os pe�es devem se mover e viajar contornando o tabuleiro at� chegar na �ltima casa\n");
	printf("A cada rodada do dado o jogador deve-se movimentar, ou seja, n�o � permitido abdicar do movimentosalve casos onde o movimento � ilegal\n\n");			
	return ;
}

//Fun��o para nomes dos jogadores
void nome_jogadores(int quant_jogadores,jogadores_ludo *jogadores){
	int i=0;
	for(i=0;i<quant_jogadores;i++){
		printf("\nDigite o nome do %d� Jogador: ",i+1);
		setbuf(stdin,NULL);
		gets(jogadores[i].nome);
	}
}

//Fun��o do dado
int dado(){
	int num;
	num = 1 + rand() % 6;	
	return num;
}

//Fun��o para zerar todas as casas dos jogadores
void zera_casas(jogadores_ludo *jogadores,int quant_jogadores){
	int i,j;
	for(j=0;j<quant_jogadores;j++){
		for(i=0;i<4;i++){
			jogadores[j].peao[i] = 0;
		}
	}	
}

//Fun��o que mostra jogada dos jogadores
void mostra_jogada(int jogou,int dado,jogadores_ludo *jogadores){
	printf("\n\nJogador %d",jogou+1);
	int j;
	printf("\n\nCasas: \n\n");
	for(j=0;j<4;j++){	
		printf("Pe�o %d:  %d\n",j+1,jogadores[jogou].peao[j]);
	}
	printf("\nValor dado: %d",dado);
	return;	
}

//Fun��o para soma de jogadores
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


//Fun��o para lime onde peao nunca podera ultrapassar
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

//Fun��o para jogador escolher pe�o
void escolhe_peao(int *op){
	int opc;
	printf("\n\nEscolha o pe�o para andar: ");
	scanf("%d",&opc);
	*op = opc;
	return ;
}

//Func�o para somar pe�as automatico se tiver uma peca s� preenchida
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


//Fun��o joga quando caiu duas vezes o numero seis no dado
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
					printf("\nOp��o Inv�lida!!!Escolha o peao%d ou o peao%d",aux,aux1);
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

//Fun��o joga quando caiu uma vez o numero seis no dado e depois diferente de seis
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

//Fun��o para alternar jogadores
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

//Fun��o para ver quem � o ganhador do jogo
void ganhador(int jogou,jogadores_ludo *jogadores){
	int total=0;
	total = peao_limite(jogou,jogadores);
	if(jogadores[jogou].peao[0] == total && jogadores[jogou].peao[1] == total && jogadores[jogou].peao[2] == total && jogadores[jogou].peao[3] == total){
		printf("Parab�ns %s voc� ganhou o jogo ludo!!!!",jogadores[jogou].nome);
	}
	return ;
}

//Fun��o para somar automatico
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

//Fun��o para soma nunca passar de determinada casa
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
