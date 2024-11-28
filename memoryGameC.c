// Bibliotecas:
#include <stdio.h> // Biblioteca para o printf e scanf.
#include <stdlib.h> // Biblioteca para o rand() e system cls.
#include <time.h> // Biblioteca para o srand().
#include <locale.h> // Biblioteca para a regionalizacao.
#include <windows.h> // Biblioteca para o sleep.

//Tabuleiro:
#define N 4 // Largura do Tabuleiro (Linhas).
#define M 4 // Comprimento do Tabuleiro (Colunas).
#define P 8 // Quantidade de Cartas Diferentes (Metade do Total).
// Struct com as variï¿½veis que serï¿½o usadas nos usuï¿½rios.
typedef struct {
	char usuario[100];
	int pontuacao;
}ranking;
ranking user, user2; //Declaraï¿½ï¿½o dos dois usuï¿½rios possï¿½veis.
// Variaveis Globais
struct {
	char GAB [N][M]; // Tabuleiro Gabarito.
	char TAB [N][M];// Tabuleiro
	char CAR [P];  // Tabuleiro Apresentado.
	int COL [M]; // Numero de Colunas.
	int ponto1, ponto2; // Pontuacao.
	int acao; // Acoes.
	int jogadores; // Numero de jogadores.
	int vez; // Para indicar qual jogador estï¿½ na vez.
}global;
//Funï¿½ï¿½es utilizadas no cï¿½digo.
void menu();
void esconder();
void inicializacao();
void embaralhar ();
void telajogo (int acao);
void atualizartela(int acao);
void umjogador();
void doisjogadores();
void jogar (int acao);
void ordem();
void usuario();
void instrucoes();
void creditos();
void rank();
void saida();
//funcï¿½o principal.
int main() {
	system("MODE con cols=80 lines=20 ");// Comando para alterar o tamanho da janela.
	char CAR[P] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
	// Comando de Regionalizacao:
	setlocale(LC_ALL, "Portuguese");
	// Titulo do Programa:
	SetConsoleTitle("Jogo da Memoria");
	// Ordem de Execucao:
	ordem();
	return 0;
}
// Funï¿½ï¿½o do menu
void menu(){
	do{
		system("color 0f");
		printf("\t****************************************************************\n"); 
		printf("\t****************************************************************\n");
	    printf("\t**                     Jogo da Memoria                        **\n");
		printf("\t****************************************************************\n"); 
		printf("\t****************************************************************\n");
		printf("\n\t\t\tSELECIONE UMA OPCAO:\n");
		printf("\t\t\t1 - INICIAR\n");
		printf("\t\t\t2 - INSTRUCOES\n");
		printf("\t\t\t3 - CREDITOS\n");
		printf("\t\t\t4 - RANKING\n");
		printf("\t\t\t5 - SAIR\n");
		printf("\t\t\tOpcao selecionada: ");
		scanf("%d", &global.acao);
		system("cls");
		switch(global.acao){
		case 1:
			break;	
		case 2:	
			instrucoes();
			break;
		case 3: 
			creditos();
			break;
		case 4:
			rank();
			break;
		case 5:
			saida();
			break;
		default:
			system("cls");
			printf("\n\n\n\n\n\n\n");
			printf("\tVOCE DIGITOU UMA OPCAO INVALIDA, TENTE NOVAMENTE.\n\n");
			sleep(2);
			system("cls");
			break;
		}
	}while(global.acao != 1);
}
// Funcao para Esconder as Cartas:
void esconder() {
	int i, j;
	usuario();// Pergunta qual o usuario antes de esconder as cartas.
	global.vez = 1; // Indica qual jogador vai comecar.
	// Loop para atrubuir o valor '*' na matriz do tabuleiro e esconder as cartas.
	for (i = 0; i < N; i++) 
		for (j  = 0; j < M; j++)
			global.TAB[i][j] = '*';
}
// Funco para Inicializar o Tabuleiro:
void inicializacao() {
	// Valores que estao disponiveis para criar os pares a serem encontrados(Os valores serao usados duas vezes)
	char CAR[P] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
	int i, j, k = 0;
	for (i = 0; i < N; i++)//Loop que cria os pares
		for (j = 0; j < M; j++){
			global.GAB[i][j]=CAR[k];
			if (k < P-1)//Se k for menor que a quantidade de cartas(p),que vai de 0 a 7(p-1), ele incrementa o k.
				k++;
				else 
					k = 0;// Se k for maior que a quantidade de cartas(p), ele recebe 0 pra ser contado novamente e formar os pares.
		}
	esconder();// Chama a funcao esconder para substituir os valores por '*'.
}
// Funcao para Embaralhar Cartas:
void embaralhar () {
	int i, j, x, y;
	char aux;
	srand(time(NULL)); // Gerador de Numeros Aleatorios.
	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++){
			x = rand()%N; // Gera Valores Aleatorios de 0 ate N(4).
			y = rand()%M; // Gera Valores Aleatorios de 0 ate M(4).
			aux = global.GAB[i][j];// Variï¿½vel auxiliar para receber os valores do gabarito.
			global.GAB[i][j] = global.GAB[x][y];// O gabarito das posicoes i e j recebem os valores das posices x e y que foram sorteadas.
			global.GAB[x][y] = aux;// O gabarito das posices x e y recebem o valor de aux(Gabarito de i e j)que ja teve seu valor escolhido.
		}	
}
// Funcao para Mostrar Tela de Jogo
void telajogo (int acao) {
	int i, j, k = 0;
	
	if (global.acao == 1){// Se no menu for selecionado 1, ele ira mostrar na tela do jogo o placar e as intrucoes de sair.
		printf ("\n Para Sair, digite: 5 e 5 \n\n");
		printf("\t%s : %d pontos.\n\n ", user.usuario, global.ponto1);
		if(global.jogadores == 2){// Se estiver selecionado a opcao multiplayer(2), ele ira mostrar o placar do segundo jogador.
		printf("\t%s : %d pontos. \n\n",  user2.usuario, global.ponto2);
		}
		printf ("\tVez de: ");
		if (global.vez == 1){// Mostra de quem a vez.
			printf("%s\n\n\t",user.usuario);
		}
		else{
			printf("%s\n\n\t",user2.usuario);
		}
		
		for (i = 0; i < M; i++){//loop para imprimir os numeros das colunas na tela do jogo.
			global.COL[i] = i;
			printf (" %d\t", global.COL[i] + 1);
		}
		printf ("\n");
		for (i = 0; i < N; i++) {//loop para imprimir os numeros das linhas na tela do jogo. 
			printf ("\t%d", i + 1);
			for (j = 0; j < M; j++)// loop para imprimir as cartas escondidas ([*]) nas linhas.
				printf ("[%c]\t", global.TAB[i][j]);
			printf ("\n\n");
		}
	}
	k = 0;	
}
// Funcao para atualizar a tela.
void atualizartela(int acao) {
	Sleep (1000); // Para o Programa por 1 Segundo (1000ms).
	system ("cls");
	telajogo(global.acao);//Depois de apagar tudo na tela, mostra novamente a tela do jogo.
}
void umjogador(){//Caso escolhido a opcao um jogador, o codigo ira salvar as pontuacoes somente em um usuario.
	int i, j, x, y, virar = 0, checar = 1;
	global.vez = 1;// Nesta funcao sempre sera a vez do jogador um, para poder mostrar a sua vez na funcao tela do jogo.
	while (global.ponto1 < 8 || global.acao == 1){ 
		if(global.ponto1 == 8){// O jogo termina quando faz 8 pontos.
			printf("\n\nParabens, voce ganhou.");
			sleep(2);
			break;
		}
		do {//loop para escolher a primeira carta.	
			printf ("\n> Informe as Coordenadas (Linha Coluna) da 1 Carta: ");
			scanf ("%d %d", &i, &j);
			if (i == 5 && j == 5){
				global.acao=-1;// Nescessario para sair do jogo e voltar para o menu (Vai ser usado mais abaixo).
				break;
			}
			// Diminui - 1 das coordenadas para poder ficar mais legï¿½vel na hora de escolher a carta(posicao 1 1 no jogo equivale a 0 0 no codigo). 
			i--;
			j--; 
			if ((i >= N || j >= M ) || (i < 0 || j < 0)){// Informa que a opcao esta invalida.
				printf ("Coordenada Invalida!");
				checar = 0;//guarda 0 pra simular valor invalido.
				atualizartela(global.acao);// volta a mostrar a tela do jogo.
			}
			else 
				checar = 1;// guarda 1 para simular valor valido.
			if (global.TAB[i][j] == '*' && checar == 1){//Se selecionar uma coordenada valida e que seu valor na matriz seja '*', a coordenada recebe o gabarito.
				global.TAB[i][j] = global.GAB[i][j];
				system ("cls");
				telajogo(global.acao);
				virar++;
			}
			else if (checar == 1){//Caso a coordenada ja tenha receido o gabarito, o if anterior vai dar falso e esse if imprime carta escolhida.
					printf ("Esta carta ja foi escolhida!");
					atualizartela(global.acao);// Volta a mostrar a tela do jogo.
			}
		} while (virar < 1);//Quando a coordenada for vï¿½lida, o loop vai fechar e entrar no loop da proxima carta.	
		if (global.acao < 0)// Caso seja digitado os valores "5  5" a acï¿½o recebe um valor negativo no if mais acima.
			break;
		do{//loop para escolher a segunda carta.
			printf ("\n> Informe as Coordenadas (Linha Coluna) da 2 Carta: ");
			scanf ("%d %d", &x, &y);	
			if ((x == 5 && y == 5) || global.ponto1 == 8){// O jogo termina quando faz 8 pontos ou "5 5" digitado.
				global.acao = -1;// Nescessario para sair do jogo e voltar para o menu (Vai ser usado mais abaixo).
			}
			// Diminui - 1 das coordenadas para poder ficar mais legivel na hora de escolher a carta(posicao 1 1 no jogo equivale a 0 0 no codigo). 
			x--;
			y--;
			if ((x >= N || y >= M ) || (x < 0 || y < 0)){// Informa que a opcao esta invalida.
				printf ("Coordenada Invalida!"); 
				checar = 0;//guarda 0 pra simular valor invalido.
				atualizartela(global.acao);//Volta a mostrar a tela do jogo.
			}
			else 
				checar = 1; //guarda 1 pra simular valor valido.
			if (global.TAB[x][y] == '*' && checar == 1){//Se selecionar uma coordenada valida e que seu valor na matriz seja '*', a coordenada recebe o gabarito.
				global.TAB[x][y] = global.GAB[x][y];
				system ("cls");
				telajogo(global.acao);
				virar++;
			}
			else 
				if (checar==1){//Caso a coordenada ja tenha receido o gabarito, o if anterior vai dar falso e esse if imprime carta escolhida.
					printf ("Esta carta ja foi escolhida!");
					atualizartela(global.acao);	
				}
	}while(virar < 2);//Quando a coordenada for valida, o loop vai fechar e retornar se acertou ou nï¿½o.	
		if (global.acao < 0)// Caso seja digitado os valores "5  5" a acao recebe um valor negativo no if mais acima.
			break;
		if (global.TAB[i][j] == global.TAB[x][y]){//Compara os valores escolhidos, se iguais, o usuario achou um par de cartas.
			virar = 0;// Recebe valor 0 para retornar ao loop da primeira carta.
			global.ponto1++;//O jogador recebe mais um ponto.
			printf ("\n\t\t\t\t  ACERTOOOOOOU!");
			Sleep (500); // Para o Programa por Meio Segundo (500ms).
		}
			else { 
				global.TAB[i][j] = '*'; // Caso as cartas selecionadas nao sejam par, os valores voltam a ser [*].
				global.TAB[x][y] = '*';	// Caso as cartas selecionadas nao sejam par, os valores voltam a ser [*].
				virar=0; //Recebe valor - para retornar ao loop da primeira carta.
				printf ("\n\t\t\t\t  ERROOOOOOU!");
				Sleep (300); // Para o Programa por 0.3 Segundos (300ms).
			}
		atualizartela(global.acao);
	}
	if(global.ponto1 > 0){ //Entra neste codigo apenas se tiver pontuado algo.
		FILE  * arquivo = NULL;
		char * usr, * svit; //Variaveis ponteiros auxiliares para organizar a gravacao do ranking.
		int vit = 0;
		char texto[100];
		arquivo = fopen("ranking.bin", "ab");// Acessa o arquivo.
		user.pontuacao = global.ponto1;// O struct do ranking recebe os pontos conseguidos no jogo.
		fprintf(arquivo, "%s ,%d\n",user.usuario,user.pontuacao);//Grava no arquivo o usuario e a pontuacao.
		fflush(arquivo);//Limpa o buffer.
		fclose(arquivo);//Fecha o arquivo.
		system("cls");
	}
	//Essas variaveis recebem 0 ao fim do jogo para poder iniciar um novo jogo.
	global.acao = 0;
	global.ponto1 = 0;
	system("cls");
	ordem();
}

void doisjogadores(){
	int i, j, x, y, virar = 0, checar = 1;
	global.vez = 1; // Variavel para indicar de quem é a vez, iniciando pelo jogador 1.
		
	while (global.ponto1 < 8 || global.acao == 1){ 
		if(global.ponto1 == 8 || global.ponto2 == 8){ //Se um dos jogadores chegar a 8 pontos o jogo acaba.
			printf("\n\nParabens, voce ganhou.");
			sleep(2);
			break;
		}
		do {   			
			printf ("\n> Informe as Coordenadas (Linha Coluna) da 1 Carta: ");
			scanf ("%d %d", &i, &j);
			if (i == 5 && j == 5){ // Nescessario para sair do jogo e voltar para o menu (Vai ser usado mais abaixo).
				global.acao = -1;
				break;
			}
			// Diminui - 1 das coordenadas para poder ficar mais legivel na hora de escolher a carta(posicao 1 1 no jogo equivale a 0 0 no codigo). 
			i--;
			j--; 
			if ((i >= N || j >= M ) || (i < 0 || j < 0)){ // Informa que a opcao esta invalida.
				printf ("Coordenada Invalida!");
				checar=0; //Guarda 0 para simular valor invalido.
				atualizartela(global.acao); //Volta a mostrar a tela do jogo.
			}
				else 
					checar=1; //Guarda 0 para simular valor valido.	
			if (global.TAB[i][j] =='*' && checar == 1){ //Se selecionar uma coordenada valida e que seu valor na matriz seja '*', a coordenada recebe o gabarito. 
				global.TAB[i][j] = global.GAB[i][j];
				system ("cls");
				telajogo(global.acao);
				virar++;
			}
				else if (checar==1){ //Caso a coordenada ja tenha receido o gabarito, o if anterior vai dar falso e esse if imprime carta escolhida.
						printf ("Esta carta ja foi escolhida!");
						atualizartela(global.acao);
				}
		} 
		while (virar < 1); //Quando a coordenada for valida, o loop vai fechar e entrar no loop da proxima carta.
		if (global.acao<0) // Caso seja digitado os valores "5  5" a acao recebe um valor negativo no if mais acima.
			break;
		do{
			printf ("\n> Informe as Coordenadas (Linha Coluna) da 2 Carta: ");
			scanf ("%d %d", &x, &y);	

			if ((x == 5 && y == 5) || global.ponto1 == 8){ // Nescessario para sair do jogo e voltar para o menu (Vai ser usado mais abaixo).
				global.acao=-1;
		
			}
			// Diminui - 1 das coordenadas para poder ficar mais legivel na hora de escolher a carta(posicao 1 1 no jogo equivale a 0 0 no codigo).
			x--;
			y--;
			if ((x >= N || y >= M ) || (x < 0 || y < 0)){
				printf ("Coordenada Invalida!"); // Informa que a opcao esta invalida.
				checar = 0; //Guarda 0 para simular valor invalido.
				atualizartela(global.acao); //Volta a mostrar a tela do jogo.
			}
			else 
				checar=1;
			if (global.TAB[x][y] == '*' && checar==1){ //Se selecionar uma coordenada valida e que seu valor na matriz seja '*', a coordenada recebe o gabarito. 
				global.TAB[x][y] = global.GAB[x][y];
				system ("cls");
				telajogo(global.acao);
				virar++;
			}
			else 
				if (checar==1){ //Caso a coordenada ja tenha receido o gabarito, o if anterior vai dar falso e esse if imprime carta escolhida.
					printf ("Esta carta ja foi escolhida!");
					atualizartela(global.acao);	
				}
	}while(virar<2); //Quando a coordenada for valida, o loop vai fechar e retornar se acertou ou nao.

	
		if (global.acao<0) // Caso seja digitado os valores "5  5" a acao recebe um valor negativo no if mais acima.
			break;
		if (global.TAB[i][j] == global.TAB[x][y]){ //Compara os valores escolhidos, se iguais, o usuario achou um par de cartas.
			virar = 0; //Recebe valor 0 para voltar ao loop da primeira carta
			if (global.vez == 1){ //Pontuacao para caso seja a vez do primeiro usuario.
					global.ponto1 = global.ponto1 + 2; //No modo multiplayer(2) a pontuacao recebe um valor dobrado, devido a serem dois jogadores.
			printf ("\n\t\t\t\t%s  ACERTOOOOOOU!", user.usuario);
			Sleep (500); // Para o Programa por Meio Segundo (500ms).
			}
			else if (global.vez == 2){//Pontuacao para caso seja a vez do segundo usuario.
					global.ponto2 = global.ponto2 + 2;//No modo multiplayer(2) a pontuacao recebe um valor dobrado, devido a serem dois jogadores.
			printf ("\n\t\t\t\t%s  ACERTOOOOOOU!", user2.usuario);
			Sleep (500); // Para o Programa por Meio Segundo (500ms).
			}
		}
			else { 
				global.TAB[i][j] = '*';// Caso as cartas selecionadas nao sejam par, o valores voltam a ser [*].
				global.TAB[x][y] = '*';// Caso as cartas selecionadas nao sejam par, o valores voltam a ser [*].
				virar=0; // Recebe valor 0 para voltar ao loop da primeira carta.
				printf ("\n\t\t\t\t  ERROOOOOOU!");
				if (global.vez == 2){ // Caso o segundo jogador nao encontre um par de cartas, ira retornar a tentativa ao primeiro jogador.
					global.vez = 1;
				}
				else{
					global.vez++; // Caso o primeiro jogador nao encontre um par de cartas, ira passar a tentativa ao segundo jogador. 
				}
				Sleep (300); // Para o Programa por 0.3 Segundos (300ms).
			}
		atualizartela(global.acao);
		
	}

	if(global.ponto1 > 0 || global.ponto2 > 0){ //Entra neste codigo apenas se tiver pontuado algo. 
		FILE  * arquivo = NULL; 
		char * usr, * svit; // Variaveis ponteiros auxiliares para organizar a gravacao do ranking.
		int vit = 0;
		char texto[100];
		arquivo = fopen("ranking.bin", "ab");// Acessar o arquivo.
		user.pontuacao = global.ponto1; // O struct do ranking do usuario um recebe os pontos conseguidos no jogo.
		user2.pontuacao = global.ponto2; // O struct do ranking do usuario dois recebe os pontos conseguidos no jogo.
		fprintf(arquivo, "%s ,%d\n",user.usuario,user.pontuacao); //Grava no arquivo o primeiro usuï¿½rio e a sua pontuacao.
		fflush(arquivo); // limpar o buffer.
		fprintf(arquivo, "%s ,%d\n",user2.usuario,user2.pontuacao); //Grava no arquivo o segundo usuï¿½rio e a sua pontuacao.
		fflush(arquivo); // limpar o buffer.
		fclose(arquivo); // Fechar arquivo
		system("cls");
	}
	//Essas variaveis recebem 0 ao fim do jogo para poder iniciar um novo jogo.
	global.acao = 0;
	global.ponto1 = 0;
	global.ponto2 = 0;
	system("cls");
	ordem();
}
// Funcao para execucao do Jogo.
void jogar (int acao) { 

	if(global.jogadores == 1){ // Caso o usuario selecione a opcao singleplayer(1), ira retornar a funcao umjogador.
		umjogador();
	}
	if(global.jogadores == 2){ // Caso o usuario selecione a opcao multiplayer(2), ira retornar a funcao doisjogareos.
		doisjogadores();
	}
}
		

//Funcao para ordenar o programa.
void ordem(){
	
	menu();	
    inicializacao();
	embaralhar();
	telajogo(global.acao);
	jogar(global.acao);	
}
//Funcao p/ salvar o nome dos jogadores
void usuario(){
	system("color 0f");
	printf("Selecione o modo de jogo:\n");
	printf("1- Singleplayer(1 Jogador) \n2- Multiplayer(2 Jogadores).\n");
	printf("> "); // Pede ao usuurio para selecionar o modo que ele deseja jogar.
	scanf("%d",&global.jogadores);
	fflush(stdin);//limpar o buffer.
	system("cls");
	if(global.jogadores == 1){ // Caso ele selecione a opcao singleplayer.
	
	printf("Digite o nome do Jogador 1: "); // Recebe o nome de apenas um usuurio.
	fflush(stdin);
	gets(user.usuario);
	fflush(stdin);
	system("cls");
	}
	else if(global.jogadores == 2){ // Caso ele selecione a opcao multiplayer.
	
	printf("Digite o nome do Jogador 1: "); // Recebe o nome de dois usuarios.
	fflush(stdin);
	gets(user.usuario);
	fflush(stdin);
	printf("Digite o nome do Jogador 2: ");
	fflush(stdin);
	gets(user2.usuario);
	fflush(stdin);
	system("cls");
	}
	else{ // Caso selecione algo que fuja do esperado(opcao 1 ou opcao 2), imprime que opcao selecionada Ã© invalida.
		printf("\tOpcao invalida.\n");
		sleep(2);
		system("cls");
		esconder();//retorna a funcao esconder.
		
	}
}
//Funcao que mostra as instrucoes.
void instrucoes(){	
	system("cls");
	system("MODE con cols=90 lines=20 ");

	printf("\n\n");
	printf("\t****************************************************************************\n");
	printf("\t**                          O QUE Ã‰ O JOGO?                               **\n");
	printf("\t**          O jogo da memoria e constituido por uma matriz 4x4            **\n");
	printf("\t**                    Dividido em 8 letras de A-H                         **\n");
	printf("\t****************************************************************************\n");
	printf("\t**                      O OBEJTIVO DO JOGO?                               **\n");
	printf("\t**      Decorar onde estao as letras e achar seus pares                   **\n");
	printf("\t**                Quantos mais acertos, mais pontos!                      **\n");
	printf("\t****************************************************************************\n");
	printf("\t**                      COMO ENTRAR NO RANKING?                           **\n");
	printf("\t**             Sua pontuacao no jogo deve ser maior que 0.                **\n");
	printf("\t**             A pontuacaoo maxima possivel de 8 pontos.                 **\n");
	printf("\t****************************************************************************\n");
	sleep(2);
	printf("\n\n");
	system("pause");
	system("cls");
}
//Funcao para mostrar os creditos.
void creditos() {
	system("MODE con cols=100 lines=20 ");
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\t****************************************************************************\n");
	printf("\t**	Desenvolvido por: Maria Fernanda, Pedro, Victor e Davi.                       **\n");
	printf("\t****************************************************************************\n");
	printf("\t**	Jogo da memoria com fins totalmente educativos.                   **\n");
	printf("\t****************************************************************************\n");
	sleep(2);
	printf("\n\n");
	system("pause");
	system("cls");	
}
//Funcao para mostrar o sistema de ranking
void rank() {
	system("cls");
	FILE  * arquivo = NULL;
	char * user, * spontos;
	int pontos = 0;
	char texto[100];
	arquivo = fopen("ranking.bin","rb");// Abre o arquivo.
	if(!arquivo){ // Se o arquivo nao estiver disponivel, ele imprime uma mensagem diferente.
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n");
		printf("\t*********************************************************\n");
		printf("\t**  Nao ha ninguem no ranking ainda, jogue e entre!    **\n");
		printf("\t*********************************************************\n");
		printf("\n\n");
		sleep(2);
		system("pause");
		system("cls");
	}
	else{
	fflush(arquivo);
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\t*****************************************************\n");
	printf("\t**                   Ranking:                      **\n");
	printf("\t*****************************************************\n");
	while(fgets(texto,100,arquivo) != NULL) {
		user = strtok(texto, ","); // Guarda todo conteudo antes da virgula na variavel spontos.
		pontos = atoi(spontos);// atoi transforma o conteudo de string para int.
		printf("\tUsuario: %s, Pontos: %d\n",user, pontos);
	}
	fclose(arquivo);// Fecha o arquivo.
	sleep(2);
	printf("\n\n");
	system("pause");
	system("cls");
	}
}
//Funcao para saida do programa.
void saida() {
	system ("cls");
	if ( global.ponto1 == 0){ // Caso saia sem realizar nenhum ponto, imprimir apenas.
	printf("\n\n");
	printf("\t*****************************************************\n");
	printf("\t**             Jogo encerrado!                     **\n");
	printf("\t*****************************************************\n");	
	exit(0);
	}
}