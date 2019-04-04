#define clean \
  free(tabuleiro);\
  free(tabuleiro2);\
  free(explosions);\
  al_destroy_sample(clique_menu);\
  al_destroy_sample(explosao);\
  al_destroy_sample(floodfill_som);\
  al_destroy_sample(inicio);\
  al_destroy_sample(set_flag);\
  al_destroy_sample(take_flag);\
  al_destroy_bitmap(imagem);\
  al_destroy_bitmap(vazio);\
  al_destroy_bitmap(um);\
  al_destroy_bitmap(dois);\
  al_destroy_bitmap(tres);\
  al_destroy_bitmap(quatro);\
  al_destroy_bitmap(cinco);\
  al_destroy_bitmap(seis);\
  al_destroy_bitmap(sete);\
  al_destroy_bitmap(oito);\
  al_destroy_bitmap(flag);\
  al_destroy_bitmap(expImage);\
  al_flush_event_queue(fila_eventos);\


#define controlFPS \
  if ((obterTempoTimer() < 1.0 / FRAMES_POR_SEGUNDO))\
  {\
    al_rest((1.0 / FRAMES_POR_SEGUNDO) - obterTempoTimer());\
  }\


void contornoDaBomba(); void jogada();

void setDificuldade()
{
  if (dificuldade == 1)
  {
    largura = 8; altura = 8; bombas = bombFacil;
		distanciax = 220;
		distanciay = 80;
		multiplicador_tamanho = 2;
		compensacao = 200;
    FRAMES_POR_SEGUNDO = 300;
  }
  else if (dificuldade == 2)
  {
    largura = 11; altura = 11; bombas = bombMedio;
		distanciax = 195;
		distanciay = 55;
		multiplicador_tamanho = 2;
		compensacao = 250;
    FRAMES_POR_SEGUNDO = 500;
  }
  else
  {
    largura = 16; altura = 12; bombas = bombDificil;
		distanciax = 170;
		distanciay = 30;
		multiplicador_tamanho = 2;
		compensacao = 300;
    FRAMES_POR_SEGUNDO = 700;
  }
  //calculo para quantos blocos voce ter� que revelar para ganhar
	win = (largura * altura) - bombas;
}

//Fun�oes auxiliares para limitar o fps
void iniciarTimer()
{
  tempoInicial = al_get_time();
}

double obterTempoTimer()
{
  return al_get_time() - tempoInicial;
}

void drawTempo() //Função para desenhar o cronometro
{
	cronometro = al_get_time() - newTempo;
	sprintf(stringTempo, "%.3lf", cronometro);
  al_draw_filled_rectangle(25 - 20, 170, 300 - 20, 266, al_map_rgba_f(0, 0, 0, 1));
  al_draw_filled_rectangle(25 - 20, 290, 300 - 20, 386, al_map_rgba_f(0, 0, 0, 1));
	al_draw_text(font2, branco, 160 - 20, 180, ALLEGRO_ALIGN_CENTER, "TEMPO:");
	al_draw_text(font2, branco, 160 - 20, 230, ALLEGRO_ALIGN_CENTER, stringTempo);
	sprintf(stringFlags, "%d", flags);
	al_draw_text(font2, branco, 160 - 20, 300, ALLEGRO_ALIGN_CENTER, "BOMBAS:");
	al_draw_text(font2, branco, 160 - 20, 350, ALLEGRO_ALIGN_CENTER, stringFlags);
}

void load_images()
{
	imagem = al_load_bitmap("imgs/bl.png");
	vazio = al_load_bitmap("imgs/vazio.png");
	um = al_load_bitmap("imgs/1.png");
	dois = al_load_bitmap("imgs/2.png");
	tres = al_load_bitmap("imgs/3.png");
	quatro = al_load_bitmap("imgs/4.png");
	cinco = al_load_bitmap("imgs/5.png");
	seis = al_load_bitmap("imgs/6.png");
	sete = al_load_bitmap("imgs/7.png");
	oito = al_load_bitmap("imgs/8.png");
	bomba = al_load_bitmap("imgs/bomba.png");
	flag = al_load_bitmap("imgs/flag.png");
  expImage = al_load_bitmap("imgs/explosion.png");
}

void load_sounds()
{
  clique_menu = al_load_sample("songs/clique_menu.wav");
  explosao = al_load_sample("songs/explosao.wav");
  floodfill_som = al_load_sample("songs/floodfill.wav");
  inicio = al_load_sample("songs/inicio.wav");
  set_flag = al_load_sample("songs/set_flag.wav");
  take_flag = al_load_sample("songs/take_flag.wav");
}

/////Alocar o tabuleiro 1 que � o tabuleiro com o conteudo
int** alocaMatriz()
{
	int i;
	int** matriz = (int**)calloc(altura, sizeof(int*));
	for (i = 0; i < altura; i++)
  {
		matriz[i] = (int*)calloc(largura, sizeof(int));
	}
	return matriz;
}

//alocar o tabuleiro 2 que � o tabuleiro que o usuario v�
char** alocaMatrizChar()
{
  int i;
  char** matriz = (char**)calloc(altura, sizeof(char*));
  for (i = 0; i < altura; i++)
  {
    matriz[i] = (char*)calloc(largura, sizeof(char));
  }
  return matriz;
}


void drawCampo(char espaco, int j, int i)
{
	iniciarTimer();
	if (espaco == '0' || espaco == '9')
		al_draw_bitmap(vazio, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '1')
		al_draw_bitmap(um, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '2')
		al_draw_bitmap(dois, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '3')
		al_draw_bitmap(tres, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '4')
		al_draw_bitmap(quatro, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '5')
		al_draw_bitmap(cinco, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '6')
		al_draw_bitmap(seis, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '7')
		al_draw_bitmap(sete, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '8')
		al_draw_bitmap(oito, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '/')
    {
      FRAMES_POR_SEGUNDO = 350;
		  al_draw_bitmap(bomba, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
      //Animação de explosão
      al_play_sample(explosao, 0.7, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
      struct Explosion explosions[NUM_EXPLOSIONS];
      //Inicia a explosão
      InitExplosions(explosions, NUM_EXPLOSIONS, expImage);
      StartExplosions(explosions, NUM_EXPLOSIONS,(distanciax + i * 25) * multiplicador_tamanho + 20 , (distanciay + j * 25) * multiplicador_tamanho + 20) ;  ////////////EXPLOSAO//////////////
      int l;
      for(l = 0; l < 10; l++)
      {
        DrawExplosions(explosions, NUM_EXPLOSIONS);
        UpdateExplosions(explosions, NUM_EXPLOSIONS);
        al_flip_display();
        al_rest(0.01);
        contornoDaBomba(j, i);
      }
    }
	else if (espaco == 'f')
		al_draw_bitmap(flag, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else
		al_draw_bitmap(imagem, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);

  drawTempo();
    //Verifica��o para controle de fps
	controlFPS
	al_flip_display();
}

void contornoDaBomba(i, j)
{
  int iM, jM;
  for (iM = i - 1; iM < i + 2; iM ++)
  {
    for (jM = j - 1; jM < j + 2; jM ++)
    {
      if (iM >= 0 && iM < altura && jM >= 0 && jM < largura && tabuleiro2[iM][jM] != '/')
      {
        drawCampo(tabuleiro2[iM][jM], iM, jM);
      }
      else
      {
        al_draw_bitmap(bomba, (distanciax + jM * 25) * multiplicador_tamanho, (distanciay + iM * 25) * multiplicador_tamanho, 0);
      }
    }
  }
}

void floodfill(int jogada_linha, int jogada_coluna)
{
	iniciarTimer();
  if(tabuleiro[jogada_linha][jogada_coluna] == 0)
  {
    tabuleiro[jogada_linha][jogada_coluna] = 9;
    tabuleiro2[jogada_linha][jogada_coluna] = '0';

		win --;

		al_draw_bitmap(vazio, (distanciax + jogada_coluna * 25) * multiplicador_tamanho, (distanciay + jogada_linha * 25) * multiplicador_tamanho, 0);
		drawTempo();
		controlFPS
		al_flip_display();


  //verifica�oes para nao fazer o floodfill fora do tabuleiro
    if(jogada_linha > 0 && jogada_coluna > 0)
      floodfill(jogada_linha - 1, jogada_coluna - 1);

    if(jogada_linha > 0 && jogada_coluna < largura - 1)
      floodfill(jogada_linha - 1, jogada_coluna + 1);

    if(jogada_linha < altura - 1 && jogada_coluna > 0)
      floodfill(jogada_linha + 1, jogada_coluna - 1);

    if(jogada_linha < altura - 1 && jogada_coluna < largura - 1)
      floodfill(jogada_linha + 1, jogada_coluna + 1);

    if(jogada_linha < altura - 1)
      floodfill(jogada_linha + 1, jogada_coluna);

    if(jogada_coluna < largura - 1)
      floodfill(jogada_linha, jogada_coluna + 1);

    if(jogada_linha > 0)
      floodfill(jogada_linha - 1, jogada_coluna);

    if(jogada_coluna > 0)
      floodfill(jogada_linha , jogada_coluna - 1);
  }
  else
    return;
}

//Revelar os numeros em volta do floodfill para completa-lo
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
        if(j < largura - 1 && tabuleiro2[i][j + 1] == '#')
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

//revelar todas as bombas quando o usuario perder
void explodir_tudo(int jogada_linha, int jogada_coluna, ALLEGRO_EVENT_QUEUE *fila_eventos)
{
	int i, j, iFim = 2, jFim = 2;
	while (bombas > 1)
	{
    while (!al_is_event_queue_empty(fila_eventos))
    {
      al_wait_for_event(fila_eventos, &evento);
      if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || evento.type == ALLEGRO_EVENT_KEY_DOWN)
      {
        return;
      }
    }
		for (i = 1; i < iFim; i ++)
		{
			jogada_linha --;
			if (all_directions)
			{
				if (tabuleiro[jogada_linha][jogada_coluna] == -1)
				{
					bombas --;
					jogada(jogada_linha, jogada_coluna);
				}
			}
		}
		for (j = 1; j < jFim; j ++)
		{
			jogada_coluna ++;
			if (all_directions)
			{
				if (tabuleiro[jogada_linha][jogada_coluna] == -1)
				{
					bombas --;
					jogada(jogada_linha, jogada_coluna);
				}
			}
		}
		iFim ++; jFim ++;
		for (i = 1; i < iFim; i ++)
		{
			jogada_linha ++;
			if (all_directions)
			{
				if (tabuleiro[jogada_linha][jogada_coluna] == -1)
				{
					bombas --;
					jogada(jogada_linha, jogada_coluna);
				}
			}
		}
		for (j = 1; j < jFim; j ++)
		{
			jogada_coluna --;
			if (all_directions)
			{
				if (tabuleiro[jogada_linha][jogada_coluna] == -1)
				{
					bombas --;
					jogada(jogada_linha, jogada_coluna);
				}
			}
		}
		iFim ++; jFim ++;
	}
}

////////fun�ao para quando o jogador clicar em um bloco ja revelado, revelar oque esta em volta
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

void jogada(int jogada_linha, int jogada_coluna)
{
  ALLEGRO_SAMPLE_ID *id_sample = 0;
  id_sample = malloc(sizeof(ALLEGRO_SAMPLE_ID));

  //tabuleiro visivel(tabuleiro2) se torna o tabuleiro com o conteudo(tabuleiro) pois o jogador clicou nele
  tabuleiro2[jogada_linha][jogada_coluna] = '0' + tabuleiro[jogada_linha][jogada_coluna];
	drawCampo(tabuleiro2[jogada_linha][jogada_coluna], jogada_linha, jogada_coluna);

	//se for -1, o jogador perdeu
  if(tabuleiro[jogada_linha][jogada_coluna] == -1)
  {
    lose = 1;
  }
  //se for 0 o espa�o � vazio e chamara a floodfill
  else if(tabuleiro[jogada_linha][jogada_coluna] == 0)
  {
    al_play_sample(floodfill_som, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, id_sample);
    floodfill(jogada_linha, jogada_coluna);
    completarFloodfill();
    al_rest(0.01);
    al_stop_sample(id_sample);
  }
  //caso contrario, apenas revela o bloco
  else
  {
    al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		win --;
  }
  free(id_sample);
}

void liberaMatriz()
{
	int i;
	for (i = 0; i < altura; i++)
  {
		free(tabuleiro[i]);
	}
	free(tabuleiro);
}

//armazena o campo no bloco de notas
void fprintaMatriz()
{
	int i, j;
	for (i = 0; i < altura; i++)
  {
		for (j = 0; j < largura; j++)
    {
			if (tabuleiro[i][j] >= 0)
      {
				fprintf(campo, " ");
			}
			fprintf(campo, "%d ", tabuleiro[i][j]);
		}
		fprintf(campo, "\n");
	}
	fprintf(campo, "\n");
}

int EstaNoCampo(int x, int y)
{
	if (x >= 0 && x < altura)
  {
		if (y >= 0 && y < largura)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

//preencher o tabuleiro com os numeros de acordo com quantas bombas existem adjacentes
void Checar(int x, int y)
{
	int aux = 0, i, j;
	for (i = x - 1; i <= x + 1; i++)
  {
		for (j = y - 1; j <= y + 1; j++)
    {
			if (EstaNoCampo(i, j))
      {
				if (tabuleiro[i][j] == -1)
        {
					aux++;
				}
			}
		}
	}
	tabuleiro[x][y] = aux;
}

void fazerTabuleiro()
{
	int x, y, random = 1, i, j;
	if (!bombas){
		for (i = 0; i < altura; i++)
    {
			for (j = 0; j < largura; j++)
      {
				if (tabuleiro[i][j] == 0)
        {
					Checar(i, j);
				}
			}
		}
		fprintaMatriz();
		for (i = 0; i < altura; i++)
    {
			for (j = 0; j < largura; j++)
      {
				if (tabuleiro[i][j] > 0)
        {
					tabuleiro[i][j] = 0;
				}
			}
		}
	}
	else
  {
		srand((time(0)) / bombas);
		while(random)
    {
			y = rand() % largura;
			x = rand() % altura;
			random--;
      //Não preenche lugares que já têm bomba ou onde foi o primeiro clique
			if ( tabuleiro[x][y] == -1 ||
          (
            (x == firstI && y == firstJ) || (x - 1 == firstI && y == firstJ) ||
            (x == firstI && y - 1 == firstJ) || (x - 1 == firstI && y - 1 == firstJ) ||
            (x + 1 == firstI && y == firstJ) || (x + 1 == firstI && y - 1 == firstJ) ||
            (x - 1 == firstI && y + 1 == firstJ) || (x == firstI && y + 1 == firstJ) ||
            (x + 1 == firstI && y + 1 == firstJ)
          )
        )
				random++;
		}
		tabuleiro[x][y] = -1;
		bombas --;
		fazerTabuleiro();
	}
}

int GdT()
{
	tabuleiro = alocaMatriz();
	campo = fopen("campo.txt", "w");
	fazerTabuleiro();
	liberaMatriz();
	fclose(campo);
	return 0;
}

void leMatriz()
{
	int i, j;
	for (i = 0; i < altura; i++)
  {
		for (j = 0; j < largura; j++)
    {
			fscanf(campo, "%d", &tabuleiro[i][j]);
		}
	}
}
