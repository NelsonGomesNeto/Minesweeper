// Os arquivos de cabeÃ§alho
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

typedef struct ALLEGRO_MOUSE_STATE ALLEGRO_MOUSE_STATE;

// Atributos da tela
const int LARGURA_TELA = 1280;
const int ALTURA_TELA = 720;
int largura, altura, bombas, compensacao;
int **tabuleiro;
char **tabuleiro2;
FILE *campo;
const int FRAMES_POR_SEGUNDO = 60;
double tempoInicial = 0;
int distanciax;
int distanciay;
float multiplicador_tamanho;
int firstI = -1, firstJ = -1;
int win, lose;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_BITMAP *botao_sair = NULL;
ALLEGRO_BITMAP *imagem = NULL, *vazio = NULL, *um = NULL, *dois = NULL, *tres = NULL;
ALLEGRO_BITMAP *quatro = NULL, *cinco = NULL, *seis = NULL, *sete = NULL, *oito = NULL;
ALLEGRO_BITMAP *bomba = NULL, *flag = NULL;
ALLEGRO_MOUSE_STATE state;

void load_images()
{
	imagem = al_load_bitmap("img/bl.png");
	vazio = al_load_bitmap("img/vazio.png");
	um = al_load_bitmap("img/1.png");
	dois = al_load_bitmap("img/2.png");
	tres = al_load_bitmap("img/3.png");
	quatro = al_load_bitmap("img/4.png");
	cinco = al_load_bitmap("img/5.png");
	seis = al_load_bitmap("img/6.png");
	sete = al_load_bitmap("img/7.png");
	oito = al_load_bitmap("img/8.png");
	bomba = al_load_bitmap("img/bomba.png");
	flag = al_load_bitmap("img/flag.png");
}

int** alocaMatriz(){
	int i;
	int** matriz = (int**)calloc(altura, sizeof(int*));
	for (i = 0; i < altura; i++){
		matriz[i] = (int*)calloc(largura, sizeof(int));
	}
	return matriz;
}

char** alocaMatrizChar(){
  int i;
  char** matriz = (char**)calloc(altura, sizeof(char*));
  for (i = 0; i < altura; i++){
    matriz[i] = (char*)calloc(largura, sizeof(char));
  }
  return matriz;
}

void drawCampo(char espaco, int j, int i)
{
	if (espaco == '0' || espaco == '9')
	{
		al_draw_bitmap(vazio, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	}
	else if (espaco == '1')
	{
		al_draw_bitmap(um, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	}
	else if (espaco == '2')
	{
		al_draw_bitmap(dois, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	}
	else if (espaco == '3')
	{
		al_draw_bitmap(tres, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	}
	else if (espaco == '4')
	{
		al_draw_bitmap(quatro, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	}
	else if (espaco == '5')
	{
		al_draw_bitmap(cinco, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	}
	else if (espaco == '6')
	{
		al_draw_bitmap(seis, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	}
	else if (espaco == '7')
	{
		al_draw_bitmap(sete, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	}
	else if (espaco == '8')
	{
		al_draw_bitmap(oito, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	}
	else if (espaco == '/')
	{
		al_draw_bitmap(bomba, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	}
	else if (espaco == 'f')
	{
		al_draw_bitmap(flag, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	}
	else
	{
		al_draw_bitmap(imagem, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	}
	al_flip_display();
}

void floodfill(int jogada_linha, int jogada_coluna)
{
  if(tabuleiro[jogada_linha][jogada_coluna] == 0)
  {
    tabuleiro[jogada_linha][jogada_coluna] = 9;
    tabuleiro2[jogada_linha][jogada_coluna] = '0';

		win --;

		al_draw_bitmap(vazio, (distanciax + jogada_coluna * 25) * multiplicador_tamanho, (distanciay + jogada_linha * 25) * multiplicador_tamanho, 0);
		al_flip_display();

    if(jogada_linha > 0 && jogada_coluna > 0)
      floodfill(jogada_linha - 1, jogada_coluna - 1);

    if(jogada_linha > 0 && jogada_coluna < largura - 1)
      floodfill(jogada_linha - 1, jogada_coluna + 1);

    if(jogada_linha < altura - 1 && jogada_coluna > 0)
      floodfill(jogada_linha + 1, jogada_coluna - 1);

    if(jogada_linha > 0 && jogada_coluna < largura - 1)
      floodfill(jogada_linha - 1, jogada_coluna + 1);

    if(jogada_linha < altura - 1)
      floodfill(jogada_linha + 1, jogada_coluna);

    if(jogada_coluna < largura - 1)
      floodfill(jogada_linha, jogada_coluna + 1);

    if(jogada_linha > 0)
      floodfill(jogada_linha - 1, jogada_coluna);

    if(jogada_coluna > 0)
      floodfill(jogada_linha , jogada_coluna - 1);
  }
  else {
    return;
  }
}

void completarFloodfill()
{
  int i;
  int j;
  for(i = 0; i < altura; i++)
  {
    for(j = 0; j < largura; j++)
    {
      if(tabuleiro2[i][j] == '0')
      {
        if(i > 0 && j > 0 && tabuleiro2[i - 1][j - 1] == '#')
        {
        	tabuleiro2[i - 1][j - 1] = '0' + tabuleiro[i - 1][j - 1];
					drawCampo(tabuleiro2[i - 1][j - 1], i - 1, j - 1);
					win --;
        }
        if(i > 0 && tabuleiro2[i - 1][j] == '#')
        {
          tabuleiro2[i - 1][j] = '0' + tabuleiro[i - 1][j];
					drawCampo(tabuleiro2[i - 1][j], i - 1, j);
					win --;
        }
        if(i > 0 && j < largura - 1 && tabuleiro2[i - 1][j + 1] == '#')
        {
          tabuleiro2[i - 1][j + 1] = '0' + tabuleiro[i - 1][j + 1];
					drawCampo(tabuleiro2[i - 1][j + 1], i - 1, j + 1);
					win --;
        }


        if(j > 0 && tabuleiro2[i][j - 1] == '#')
        {
          tabuleiro2[i][j - 1] = '0' + tabuleiro[i][j - 1];
					drawCampo(tabuleiro2[i][j - 1], i, j - 1);
					win --;
        }
        if(j < altura - 1 && tabuleiro2[i][j + 1] == '#')
        {
          tabuleiro2[i][j + 1] = '0' + tabuleiro[i][j + 1];
					drawCampo(tabuleiro2[i][j + 1], i, j + 1);
					win --;
        }


        if(i < altura - 1 && j > 0 && tabuleiro2[i + 1][j - 1] == '#')
        {
          tabuleiro2[i + 1][j - 1] = '0' + tabuleiro[i + 1][j - 1];
					drawCampo(tabuleiro2[i + 1][j - 1], i + 1, j - 1);
					win --;
        }
        if(i < altura - 1 && tabuleiro2[i + 1][j] == '#')
        {
          tabuleiro2[i + 1][j] = '0' + tabuleiro[i + 1][j];
					drawCampo(tabuleiro2[i + 1][j], i + 1, j);
					win --;
        }
        if(i < altura - 1 && j < largura - 1 && tabuleiro2[i + 1][j + 1] == '#')
        {
          tabuleiro2[i + 1][j + 1] = tabuleiro[i + 1][j + 1] + '0';
					drawCampo(tabuleiro2[i + 1][j + 1], i + 1, j + 1);
					win --;
        }
			}
    }
  }
}

void contorno(int jogada_linha, int jogada_coluna)
{
	int i, j;
	for (i = jogada_linha - 1; i < jogada_linha + 2; i ++)
	{
		for (j = jogada_coluna - 1; j < jogada_coluna + 2; j ++)
		{
			if (i >= 0 && j >= 0 && i < altura && j < largura && tabuleiro2[i][j] == '#')
			{
				jogada(i, j);
			}
		}
	}
}

/*void printaMatriz(int n, int m){
  int i, j;
  for (i = 0; i < n; i++){
    for (j = 0; j < m; j++){
      if (tabuleiro[i][j] >= 0)
      {
        //printf(" ");
      }
      //printf("%d ", tabuleiro[i][j]);
    }
    //printf("\n");
  }
  //printf("\n\n");
}*/

/*void printarTabuleiro(int n, int m){
  int i, j;
  for (i = 0; i < n; i++){
    for (j = 0; j < m; j++){
      //printf("%c ", tabuleiro2[i][j]);
    }
    //printf("\n");
  }
  //printf("\n\n");
}*/

void gerarTabuleiro()
{
  int i, j;
  for(i = 0; i < altura; i++)
  {
    for(j = 0; j < largura; j++)
    {
      tabuleiro2[i][j] = '#';
    }
  }
}

void jogada(int jogada_linha, int jogada_coluna){
  tabuleiro2[jogada_linha][jogada_coluna] = '0' + tabuleiro[jogada_linha][jogada_coluna];
	drawCampo(tabuleiro2[jogada_linha][jogada_coluna], jogada_linha, jogada_coluna);
  if(tabuleiro[jogada_linha][jogada_coluna] == -1)
  {
    lose ++;
    //printaMatriz(l, c);
  // printarTabuleiro(l, c);
  }
  else if(tabuleiro[jogada_linha][jogada_coluna] == 0)
  {
    floodfill(jogada_linha, jogada_coluna);
    completarFloodfill();
    //printarTabuleiro(l, c);
  }
  else
  {
		win --;
  // printaMatriz(l, c);
    //printarTabuleiro(l, c);
  }
}

void liberaMatriz(){
	int i;
	for (i = 0; i < altura; i++){
		free(tabuleiro[i]);
	}
	free(tabuleiro);
}

void fprintaMatriz(){
	int i, j;
	for (i = 0; i < altura; i++){
		for (j = 0; j < largura; j++){
			if (tabuleiro[i][j] >= 0){
				fprintf(campo, " ");
			}
			fprintf(campo, "%d ", tabuleiro[i][j]);
		}
		fprintf(campo, "\n");
	}
	fprintf(campo, "\n");
}

int EstaNoCampo(int x, int y){
	if (x >= 0 && x < altura){
		if (y >= 0 && y < largura){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		return 0;
	}
}

void Checar(int x, int y){
	int aux = 0, i, j;
	for (i = x - 1; i <= x + 1; i++){
		for (j = y - 1; j <= y + 1; j++){
			if (EstaNoCampo(i, j)){
				if (tabuleiro[i][j] == -1){
					aux++;
				}
			}

		}
	}
	tabuleiro[x][y] = aux;
}

void fazerTabuleiro(){
	int x, y, random = 1, i, j;
	if (!bombas){
		for (i = 0; i < altura; i++){
			for (j = 0; j < largura; j++){
				if (tabuleiro[i][j] == 0){
					Checar(i, j);
				}
			}
		}
		fprintaMatriz();
		for (i = 0; i < altura; i++){
			for (j = 0; j < largura; j++){
				if (tabuleiro[i][j] > 0){
					tabuleiro[i][j] = 0;
				}
			}
		}
	}
	else{
		srand((time(NULL)) / bombas);
		while(random){
			y = rand() % largura;
			x = rand() % altura;
			random--;
			if (tabuleiro[x][y] == -1 || (x == firstI && y == firstJ)){
				random++;
			}
		}
		tabuleiro[x][y] = -1;
		bombas --;
		fazerTabuleiro();
	}
}

int GdT(){
	//int l = atoi(argv[1]), c = atoi(argv[2]), q = atoi(argv[3]), seed = atoi(argv[4]);
	tabuleiro = alocaMatriz();
	campo = fopen("campo.txt", "w");
	fazerTabuleiro();
	liberaMatriz();
	fclose(campo);
	return 0;
}

void leMatriz(){
	int i, j;
	for (i = 0; i < altura; i++){
		for (j = 0; j < largura; j++){
			fscanf(campo, "%d", &tabuleiro[i][j]);
		}
	}
}

void iniciarTimer()
{
  tempoInicial = al_get_time();
}

double obterTempoTimer()
{
  return al_get_time() - tempoInicial;
}

int main(void)
{
	int i, j;
  int frame = 0;
  bool limitado = true;
  int dificuldade = 0;
  scanf("%d", &dificuldade);
	int temp, mousex, mousey;
	lose = 0;
  if (dificuldade == 1)
  {
    largura = 10; altura = 8; bombas = 10;
		distanciax = 220;
		distanciay = 80;
		multiplicador_tamanho = 2;
		compensacao = 200;
  }
  else if (dificuldade == 2)
  {
    largura = 10; altura = 10; bombas = 99;
		distanciax = 195;
		distanciay = 55;
		multiplicador_tamanho = 2;
		compensacao = 250;
  }
  else
  {
    largura = 14; altura = 12; bombas = 5;
		distanciax = 170;
		distanciay = 30;
		multiplicador_tamanho = 2;
		compensacao = 300;
  }
	win  = (largura * altura) - bombas;
  // Flag que condicionarÃ¡ nosso looping
  int sair = 0;

  if (!al_init())
  {
    fprintf(stderr, "Falha ao inicializar a Allegro.\n");
    return -1;
  }

	al_init_image_addon();
	al_init_primitives_addon();

	load_images();

  janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
  if (!janela)
  {
    fprintf(stderr, "Falha ao criar janela.\n");
    return -1;
  }

  // Configura o tÃ­tulo da janela
  al_set_window_title(janela, "Minesweeper");

  // Torna apto o uso de mouse na aplicaÃ§Ã£o
  if (!al_install_mouse())
  {
    fprintf(stderr, "Falha ao inicializar o mouse.\n");
    al_destroy_display(janela);
    return -1;
  }

  // Atribui o cursor padrÃ£o do sistema para ser usado
  if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
  {
    fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
    al_destroy_display(janela);
    return -1;
  }


  fila_eventos = al_create_event_queue();
  if (!fila_eventos)
  {
    fprintf(stderr, "Falha ao inicializar o fila de eventos.\n");
    al_destroy_display(janela);
    return -1;
  }

  // Dizemos que vamos tratar os eventos vindos do mouse
  al_register_event_source(fila_eventos, al_get_mouse_event_source());

	for (i = 0; i < altura; i ++)
	{
		for (j = 0; j < largura; j ++)
		{
			al_draw_bitmap(imagem, (distanciax + j * 25) * multiplicador_tamanho, (distanciay + i * 25) * multiplicador_tamanho, 0);
			al_flip_display();
		}
	}

	int first = 0;

  while (!sair)
  {
    iniciarTimer();
		if (win == 0)
		{
			printf("Ganhou, poarr\n");
			sair = 1; continue;
		}
		if (lose == 1)
		{
			printf("Perdeu, poarr\n");
			sair = 1; continue;
		}
    // Verificamos se hÃ¡ eventos na fila
    while (!al_is_event_queue_empty(fila_eventos))
    {
      ALLEGRO_EVENT evento;
      al_wait_for_event(fila_eventos, &evento);

      if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
      {
				al_get_mouse_state(&state);
				mousex = evento.mouse.x;
				mousey = evento.mouse.y;
				temp = mousex - LARGURA_TELA/2 + compensacao;
				j = temp / 50;
				temp = mousey - ALTURA_TELA/2 + compensacao;
				i = temp / 50;
				if (state.buttons & 1)
				{
					if(i >= 0 && i < altura && j >= 0 && j < largura)
					{
						if (first == 0)
						{
							first = 1; firstI = i; firstJ = j;
							GdT();
							campo = fopen("campo.txt", "r");
							tabuleiro = alocaMatriz();
							tabuleiro2 = alocaMatrizChar();
							leMatriz();
							gerarTabuleiro();
						}
						if (tabuleiro2[i][j] == '#')
						{
							jogada(i, j);
						}
						else if (tabuleiro2[i][j] != '/')
						{
							contorno(i, j);
						}
						//printf("%d %d\n", i, j);
						printf("%d\n", win);
					}
				}
				if (state.buttons & 2)
				{
					if(i >= 0 && i < altura && j >= 0 && j < largura)
					{
						if (tabuleiro2[i][j] == '#')
						{
							tabuleiro2[i][j] = 'f';
							drawCampo(tabuleiro2[i][j], i, j);
						}
						else if (tabuleiro2[i][j] == 'f')
						{
							tabuleiro2[i][j] = '#';
							drawCampo(tabuleiro2[i][j], i, j);
						}
					}
				}
			}
		}

    // Atualiza a tela
    frame++;
    if (limitado && (obterTempoTimer() < 1.0 / FRAMES_POR_SEGUNDO))
    {
    	al_rest((1.0 / FRAMES_POR_SEGUNDO) - obterTempoTimer());
    }
  }

  // Desaloca os recursos utilizados na aplicaÃ§Ã£o
  al_destroy_display(janela);
  al_destroy_event_queue(fila_eventos);

  return 0;
}
