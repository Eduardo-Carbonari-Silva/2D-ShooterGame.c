#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#define TF 20

// GROUP: EDUARDO, IGOR, VINICIUS

struct TpElemento{
	char simbolo;
	int cor, pontos, x, y;
};

struct TpData{
	int d, m, a;
};

struct TpJogador{
	char Nome[30];
	TpData data; //Declarar acima se não, não enxerga
	int pontuacao;
	int chance = 20;
};

void LimpaTelaDoJogo(){
	
	for(int i=10; i<28; i++){
		gotoxy(32,i);
		printf("                                                                             ");
	}
}

void RelJog(TpJogador Jog[TF], int qtde){
	
	int a;
	int y = 10;
	
	gotoxy(32, y);
	printf("### RELATORIO DE JOGADORES ###");
	
	if(qtde == 0){
		gotoxy(32, ++y);
		printf("Nao ha jogadores!");
		getch();
	}
	
	else{
		for(a = 0; a < qtde; a++){
			gotoxy(32, ++y);
			printf("Nome: %s, Pontuacao: %d", Jog[a].Nome, Jog[a].pontuacao);
			gotoxy(32, ++y);
			printf("Data: %d/%d/%d", Jog[a].data.d, Jog[a].data.m, Jog[a].data.a);
			gotoxy(32, ++y);
			
			if(y >= 24){
				for(int j = 5; j>=0; j--){
					gotoxy(79, 27);
					printf("Proxima pagina em %d segundos!", j);
					Sleep(1000);
				}
				gotoxy(79, 27);
				printf("                              ");
				LimpaTelaDoJogo();
				y = 10;
				gotoxy(32, y);
				printf("### RELATORIO DE JOGADORES ###");
			}
		}

		getch();
	}
}

void GerarElementos(TpElemento TabElem[TF]){
	
	int i;
	
	for(i = 0; i < TF; i++){
	
		TabElem[i].cor = rand()%14+2;
		TabElem[i].simbolo = rand()%4+3;
		TabElem[i].x = rand()%77+32;
		TabElem[i].y = rand()%17+10;
		TabElem[i].pontos = (rand()%3+1)*10;
	}
}

int BuscaNomeJogador(TpJogador TabJog[TF], int TL, char NOME[30]){
	
	int i = 0;
	while (i < TL && stricmp(TabJog[i].Nome, NOME) != 0)
		i++;
	
	if(i < TL)
		return i;
	else
		return -1;
}

void Exclusao(TpJogador TabJog[TF], int &TL){
	
	int pos;
	char AuxNome[30], p;
	int y = 10;
	
	gotoxy(32, y);
	printf("## EXCLUSAO DE JOGADORES ##");
	
	if (TL == 0){
		gotoxy(32, ++y);
		printf("Nenhum jogador cadastrado!");
		getch();
	}
	
	else{
		gotoxy(32, ++y);
		printf("Nome a Excluir: ");
		fflush(stdin);
		gets(AuxNome);
		
		while(TL > 0 && strcmp(AuxNome, "\0") != 0){
			
			pos = BuscaNomeJogador(TabJog, TL, AuxNome);
			
			if(pos == -1){
				gotoxy(32, ++y);
				printf("Nome nao cadastrado!");
				gotoxy(32, ++y);
				getch();
				LimpaTelaDoJogo();
				y = 10;
				gotoxy(32, y);
				printf("## EXCLUSAO DE JOGADORES ##");
			}
			
			else{
				gotoxy(32, ++y);
				printf("## Dados do Jogador ##");
				gotoxy(32, ++y);
				printf("Nome: %s", TabJog[pos].Nome);
				gotoxy(32, ++y);
				printf("Data: %d/%d/%d", TabJog[pos].data.d, TabJog[pos].data.m, TabJog[pos].data.a);
				gotoxy(32, ++y);
				printf("Pontuacao: %d", TabJog[pos].pontuacao);
				gotoxy(32, ++y);
				printf("Confirma Exclusao (S/N)? ");
				
				if(toupper(getche())=='S'){
					
					for(; pos<TL-1; pos++)
						TabJog[pos] = TabJog[pos+1];
					
					TL--;
					gotoxy(32, ++y);
					printf("Jogador Excluido!");
					gotoxy(32, ++y);
					getch();
					LimpaTelaDoJogo();
					y = 10;
					gotoxy(32, y);
					printf("## EXCLUSAO DE JOGADORES ##");
				}
			}
			
			gotoxy(32, ++y);
			printf("Nome a Excluir: ");
			fflush(stdin);
			gets(AuxNome);
			
		}
	}
}
void MostrarElementos(TpElemento TabElem[TF]){
	
	int i;
	
	for(i=0; i<TF; i++){
		
		gotoxy(TabElem[i].x, TabElem[i].y);
		textcolor(TabElem[i].cor);
		printf("%c", TabElem[i].simbolo);
	}
	
	textcolor(7);
}

void OrdenarJogador(TpJogador TabJog[TF], int TL){
	
	int a, b;
	TpJogador aux;
	
	for(a=0; a<TL; a++)
		for(b=a+1; b<TL; b++)
			if(TabJog[a].pontuacao < TabJog[b].pontuacao){
				
				aux = TabJog[a];
				TabJog[a] = TabJog[b];
				TabJog[b] = aux;
			}
}

void ConsultaJogador(TpJogador TabJog[TF], int TLJ){
	
	int pos;
	char NOME[30];
	int y = 10;
	
	gotoxy(32, y);
	printf("# # # CONSULTA DE JOGADORES # # #");
	
	if (TLJ == 0){
		gotoxy(32, ++y);
		printf("Nenhum jogador cadastrado!");
		getch();
	}
	
	else{
		gotoxy(32, ++y);
		printf("Digite o nome que deseja encontrar: ");
		gotoxy(32, ++y);
		gets(NOME);
		
		while(TLJ < TF && strcmp(NOME, "\0") != 0){
			
			pos = BuscaNomeJogador(TabJog, TLJ, NOME);
			
			if(pos != -1){
				
				gotoxy(32, ++y);
				printf("Nome encontrado!!!\n");
				gotoxy(32, ++y);
				printf("## Dados do Jogador ##");
				gotoxy(32, ++y);
				printf("Nome: %s\n", TabJog[pos].Nome);
				gotoxy(32, ++y);
				printf("Data: %d/%d/%d\n", TabJog[pos].data.d, TabJog[pos].data.m, TabJog[pos].data.a);
				gotoxy(32, ++y);
				printf("Pontuacao: %d\n", TabJog[pos].pontuacao);
				gotoxy(32, ++y);
				getch();
				LimpaTelaDoJogo();
				y = 10;
				gotoxy(32, y);
				printf("# # # CONSULTA DE JOGADORES # # #");
			}
			
			else{
				gotoxy(32, ++y);
				printf("Nome nao encontrado!\n");
				gotoxy(32, ++y);
				getch();
				LimpaTelaDoJogo();
				y = 10;
				gotoxy(32, y);
				printf("# # # CONSULTA DE JOGADORES # # #");
			}
			
			gotoxy(32, ++y);
			printf("Digite o nome que deseja encontrar: ");
			fflush(stdin);
			gets(NOME);
		}
	}
}

void Ranking(TpJogador TabJog[TF], int TLJ){
	
	int y = 10;
	
	gotoxy(32, y);
	printf("### RANKING ###");
	
	if (TLJ == 0){
		gotoxy(32, ++y);
		printf("Nenhum jogador cadastrado!");
		getch();
	}
	
	else{
		OrdenarJogador(TabJog, TLJ);
		
		for(int i=0; i<TLJ; i++){
			gotoxy(32, ++y);
			printf("Nome: %s, Data: %d/%d/%d", TabJog[i].Nome, TabJog[i].data.d, TabJog[i].data.m, TabJog[i].data.a);
			gotoxy(32, ++y);
			printf("Pontuacao: %d", TabJog[i].pontuacao);
			y++;
			
			if(y >= 24){
					for(int j = 5; j>=0; j--){
						gotoxy(79, 27);
						printf("Proxima pagina em %d segundos!", j);
						Sleep(1000);
					}
					gotoxy(79, 27);
					printf("                              ");
					LimpaTelaDoJogo();
					y = 10;
					gotoxy(32, y);
					printf("### RANKING ###");
			}
		}
		
		gotoxy(32, ++y);
		getche();
	}
}

void Moldura(int CI, int LI, int CF, int LF, int Frente){
	
	textcolor(Frente);
	//textbackground(Fundo);
	
	gotoxy(CI,LI);
	printf("%c", 201);
	gotoxy(CF,LI);
	printf("%c", 187);
	gotoxy(CI,LF);
	printf("%c", 200);
	gotoxy(CF,LF);
	printf("%c", 188);
	
	for(int a=CI+1; a<CF; a++){
		gotoxy(a, LI);
		printf("%c", 205);
		gotoxy(a, LF);
		printf("%c", 205);
	}
	
	for(int a=LI+1; a<LF; a++){
		gotoxy(CI, a);
		printf("%c", 186);
		gotoxy(CF, a);
		printf("%c", 186);
	}
	
	textcolor(7);
	//textbackground(0);
}

void FormPrincipal(void){
	
	system("cls");
	
	Moldura(10, 5, 110, 29, 4+9); // moldura externa
	
	Moldura(11, 6, 109, 8, 10); // moldura do titulo
	gotoxy(54, 7);
	printf("### JOGO ###");
	
	Moldura(11, 9, 30, 28, 10); // moldura do menu
	
	Moldura(31, 9, 109, 28, 10); // moldura do jogo
}

void AltJog(TpJogador TabJog[TF], int TL){
	
	int y = 10, i;
	char nome[30], op;
	
	gotoxy(32, y);
	printf("### ALTERAR JOGADOR ###");
	
	if (TL == 0){
		gotoxy(32, ++y);
		printf("Nenhum jogador cadastrado!");
		getch();
	}
	
	else{
		gotoxy(32, ++y);
		printf("Digite o nome do jogador que deseja alterar os dados: ");
		gotoxy(32, ++y);
		gets(nome);
		
		i = BuscaNomeJogador(TabJog, TL, nome);
		if (i == -1){
			gotoxy(32, ++y);
			printf("Jogador nao cadastrado!");
			getch();
		}
		
		else{
			gotoxy(32, ++y);
			printf("Jogador encontrado!");
			
			do{
				
				gotoxy(32, ++y);
				printf("O que deseja alterar?");
				gotoxy(32, ++y);
				printf("[A] Nome");
				gotoxy(32, ++y);
				printf("[B] Data");
				gotoxy(32, ++y);
				printf("[ESC] Sair");
				gotoxy(32, ++y);
				op = getche();
				
				switch(toupper(op)){
				
					case 'A': gotoxy(32, ++y);
							  printf("Digite o novo nome: ");
							  gets(nome);
							  strcpy(TabJog[i].Nome, nome);
							  gotoxy(32, ++y);
							  printf("Nome Alterado!");
							  Sleep(500);
							  break;
					
					case 'B': gotoxy(32, ++y);
							  printf("Digite a nova data: ");
							  scanf("%d %d %d", &TabJog[i].data.d, &TabJog[i].data.m, &TabJog[i].data.a);
							  gotoxy(32, ++y);
							  printf("Data alterada!");
							  Sleep(500);
							  break;
				}
				
				if(y >= 23){
					LimpaTelaDoJogo();
					y = 9;
				}
				
				
			}while (op != 27);
		}
	}
}

char Menu(void){
	
	system("cls");
	
	FormPrincipal();
	
	gotoxy(12, 10);
	printf(" # # M E N U # #");
	gotoxy(12, 12);
	printf("[A] Cadastro");
	gotoxy(12, 13);
	printf("[B] Relatorio");
	gotoxy(12, 14);
	printf("[C] Consulta");
	gotoxy(12, 15);
	printf("[D] Exclusao");
	gotoxy(12, 16);
	printf("[E] Alteracao");
	gotoxy(12, 17);
	printf("[F] JOGAR");
	gotoxy(12, 18);
	printf("[G] Ranking");
	gotoxy(12, 19);
	printf("[ESC] Sair");
	gotoxy(12, 21);
	printf("Opcao: ");
	
	return toupper(getche());
}

void CadJog(TpJogador TabJog[TF], int &TL){
	
	char auxnome[30];
	int y = 10, i;
	
	gotoxy(32, y);
	printf("### CADASTRO DE JOGADORES ###");
	
	gotoxy(32, ++y);
	printf("Nome: ");
	fflush(stdin);
	gets(auxnome);
	
	while(TL < TF && strcmp(auxnome, "\0") != 0){
		
		i = BuscaNomeJogador(TabJog, TL, auxnome);
		while(i != -1){
			gotoxy(32, ++y);
			printf("Nome ja cadastrado!");
			gotoxy(32, ++y);
			printf("Tente um outro nome:");
			gotoxy(32, ++y);
			gets(auxnome);
			
			i = BuscaNomeJogador(TabJog, TL, auxnome);
			
			if(y >= 24){
				LimpaTelaDoJogo();
				y = 10;
				gotoxy(32, y);
				printf("CADASTRO DE JOGADORES");
			}
		}
		
		if(i == -1){
			strcpy(TabJog[TL].Nome, auxnome);
		
			TabJog[TL].pontuacao = 0;
			
			gotoxy(32, ++y);
			printf("Data [dd mm aaaa]\n");
			
			gotoxy(32, ++y);
			scanf("%d %d %d", &TabJog[TL].data.d, &TabJog[TL].data.m, &TabJog[TL].data.a);
			
			while(TabJog[TL].data.d > 30 || TabJog[TL].data.d < 0 || TabJog[TL].data.m > 12 || TabJog[TL].data.m < 0 || TabJog[TL].data.a > 2024 || TabJog[TL].data.a < 1924){
				gotoxy(32, ++y);
				printf("Data invalida, digite novamente!");
				gotoxy(32, ++y);
				printf("Data [dd mm aaaa]\n");
				gotoxy(32, ++y);
				scanf("%d %d %d", &TabJog[TL].data.d, &TabJog[TL].data.m, &TabJog[TL].data.a);
				
				if(y >= 23){
					LimpaTelaDoJogo();
					y = 10;
					gotoxy(32, y);
					printf("CADASTRO DE JOGADORES");
				}
			}
			
			TL++;
		}
		
		y++;
		
		if(y >= 24){
			LimpaTelaDoJogo();
			y = 10;
			gotoxy(32, y);
			printf("CADASTRO DE JOGADORES");
		}
		
		gotoxy(32, ++y);
		printf("Nome: ");
		fflush(stdin);
		gets(auxnome);
	}
} 

int BuscarTiro(TpJogador TabJog[TF], TpElemento TabTiro[TF], int col, int tiro, int pon){
	
	int i;
	
	for (i=0; i<TF ; i++)
		if (tiro == TabTiro[i].y && col == TabTiro[i].x){
			TabJog[pon].pontuacao += TabTiro[i].pontos;
			return i;
		}
	
	return -1;
}

int VerifNomePraJogar(TpJogador TabJog[TF], int TL){
	
	int y = 10, i = 0;
	char nome[30];
	
	gotoxy(32, y);
	printf("Digite o nome do jogador que deseja jogar");
	gotoxy(32, ++y);
	gets(nome);
	
	i = BuscaNomeJogador(TabJog, TL, nome);
	if(TabJog[i].chance <= 0){
		gotoxy(32, ++y);
		printf("Jogador nao tem mais chances!");
		gotoxy(32, ++y);
		printf("Tente outro nome");
		gotoxy(32, ++y);
		gets(nome);
			
		if(y >= 23){
			gotoxy(32, ++y);
			printf("Jogador nao tem mais chances!");
			Sleep(1000);
			LimpaTelaDoJogo();
			y = 10;
			gotoxy(32, y);
			printf("Digite o nome do jogador que deseja jogar");
			gotoxy(32, ++y);
			gets(nome);
		}
		
		i = BuscaNomeJogador(TabJog, TL, nome);
	}
	
	if(TabJog[i].chance > 0){
		LimpaTelaDoJogo();
		return i;
	}
		
	else{
		gotoxy(32, ++y);
		printf("Jogador nao pode jogar");
		getch();
		return -1;
	}
}

void Jogar(TpJogador Jog[TF], int TL){
	
	char SimbJog = 1, tecla, nome[30];
	int col = 40, tiro, y = 10, resultado, pontuacao;
	TpElemento TabElem[TF];
	
	if(TL == 0){
		gotoxy(32, y);
		printf("Nenhum jogador cadastrado!\n");
		gotoxy(32, ++y);
		getch();
	}
	
	else{
		pontuacao = VerifNomePraJogar(Jog, TL);
		y = 10;
	
		if(pontuacao != -1){ //conhece o nome e verifica se existe
		
			gotoxy(32, y);
			printf("                                         ");
			gotoxy(32, ++y);
			printf("                ");
				
			GerarElementos(TabElem);
			MostrarElementos(TabElem);
			
			for(int k = 10; k < 28; k++){
				gotoxy(12, k);
				printf("                  ");
			}
							
			gotoxy(12, 10);
			printf("Chances: %d", Jog[pontuacao].chance);
			
			do{
				gotoxy(col, 27);
				printf("%c", SimbJog);
				textcolor (WHITE);
				tecla = getch();
				gotoxy(col, 27);
				printf(" ");
				switch(toupper (tecla)){
						
					case 'A':
						if(col>32)
							col--;
						break;
						
					case 'D':
						if(col<108)
							col++;
						break;
							
					case ' ':
						
						Jog[pontuacao].chance -= 1;
						
						if(Jog[pontuacao].chance == 9){
							gotoxy(22, 10);
							printf(" ");
						}
						
						gotoxy(12, 10);
						printf("Chances: %d", Jog[pontuacao].chance);
						
						for (tiro = 27; tiro >= 10; tiro--){
								
							gotoxy(col, tiro);
							printf("%c", 94);
							Sleep(20);
							gotoxy(col, tiro);
							printf(" ");
								
							resultado = BuscarTiro(Jog, TabElem, col, tiro, pontuacao);
							if(resultado != -1){
								gotoxy(TabElem[resultado].x, TabElem[resultado].y);
			          			printf(" ");
			        			TabElem[resultado].x = -1;
			            		TabElem[resultado].y = -1;
			            		tiro = 9;
							}
						}
						
						if(Jog[pontuacao].chance == 0){
							gotoxy(62, 18);
							printf("### GAME OVER ###");
							Sleep(3000);
							tecla = 27;
						}
						
						break;
				}
				
			}while(tecla != 27);
		}
	}
	

}

int main(){

	system("cls");
	
	char op;
	
	TpJogador Jogador[TF];
	int TLJ = 0;
	srand(time(0));
	
	do{
		
		op = Menu();
		
		switch(toupper(op)){
			case 'A': CadJog(Jogador, TLJ);
					  break;
			
			case 'B': RelJog(Jogador, TLJ);
					  break;
			
			case 'C': ConsultaJogador(Jogador, TLJ);
					  break;
			
			case 'D': Exclusao(Jogador, TLJ);
					  break;
			
			case 'E': AltJog(Jogador, TLJ);
					  break;
			
			case 'F': Jogar(Jogador, TLJ);
					  break;
			
			case 'G': Ranking(Jogador, TLJ);
		}
		
	}while(op != 27);
	
	system("cls");
	
	return 0;
}
