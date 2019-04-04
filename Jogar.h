void jogar()
{
  //stuct do score atual para ser salvo no ranking
	score atual;
  double cronometroInicial, cronometroFinal;
	first = 0; lose = 0; win = 1;

  //limpar a tela e desenhar o background
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_bitmap(backgr, 0, 0, 0);
  al_draw_bitmap(bombaBG, LARGURA_TELA / 2 - 256, ALTURA_TELA / 2 - 256, 0);

	//Configura as dificuldades
  setDificuldade();
  //Carrega as imagens
  load_images();
	//Carrega os sons
  load_sounds();

  int i, j, temp;
  //Desenha o tabuleiro com animação
	for (i = -1; i <= altura; i ++)
	{
		for (j = -1; j <= largura; j ++)
		{
			iniciarTimer();
      if (i < 0 || j < 0 || i == altura || j == largura)
        al_draw_bitmap(bomba, (distanciax + j * 25) * multiplicador_tamanho, (distanciay + i * 25) * multiplicador_tamanho, 0);
      else
        al_draw_bitmap(imagem, (distanciax + j * 25) * multiplicador_tamanho, (distanciay + i * 25) * multiplicador_tamanho, 0);
			controlFPS
			al_flip_display();
		}
	}
  FRAMES_POR_SEGUNDO = backUpFPS;

  al_play_sample(inicio, 1.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);

  //desenhar os retangulos da parte esquerda da tela do jogo
  Branco1 = al_map_rgb(255,255,255);
  al_draw_rectangle(20 - 20, -10, 305 - 20, 805, al_map_rgb(0, 0, 0), 7.0);
  al_draw_rectangle(22 - 20, -10, 303 - 20, 803, al_map_rgb(253, 152, 0), 7.0);
  al_draw_filled_rectangle(25 - 20, -10, 300 - 20, 800, al_map_rgba_f(0, 0, 0, 0.5));
  al_draw_text(font2, Branco1, 160 - 20, 500, ALLEGRO_ALIGN_CENTER, "Reiniciar");
  al_draw_text(font2, Branco1, 160 - 20, 600, ALLEGRO_ALIGN_CENTER, "Voltar");

  //declarar a struct explosao carregar a imagem e inicializar a explosao
  struct Explosion explosions[NUM_EXPLOSIONS];
  InitExplosions(explosions, NUM_EXPLOSIONS, expImage);

  al_flush_event_queue(fila_eventos); //Limpa a fila de eventos

  int sair = 0;
  while (!sair)
  {
    iniciarTimer(); //Timer do controle de FPS
    if (lose == 1) //Se perdeu
    {
      explodir_tudo(i, j, fila_eventos);
      FRAMES_POR_SEGUNDO = 120;
      al_rest(0.6);
      al_destroy_event_queue(fila_eventos);
      perdeu();
      fila_eventos = al_create_event_queue();
      sair = 1; continue;
    }

    if (win == 0) //Se ganhou
    {
      cronometroFinal = al_get_time() - cronometroInicial;
      atual.tempo = cronometroFinal;
      al_clear_to_color(al_map_rgb(255,255,255));
      al_destroy_event_queue(fila_eventos);
      ganhou(atual);
      fila_eventos = al_create_event_queue();
      sair = 1; continue;
    }

    //enquanto tiver eventos na fila de eventos
    while (!al_is_event_queue_empty(fila_eventos))
    {
      al_wait_for_event(fila_eventos, &evento);

      if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || evento.type == ALLEGRO_EVENT_KEY_DOWN)
      {
				al_get_mouse_state(&state);
				mousex = state.x;
				mousey = state.y;

        //caso o jogador clique em reiniciar
				if((25 < mousex) && (mousex < 290) && (mousey > 490) && (mousey < 550))
        {
          al_play_sample(clique_jogo, 1.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
          clean //Limpa memória RAM
          jogar(backgr, bombaBG);
          return;
        }

        //caso o jogador clique em voltar ao menu
        if((25 < mousex) && (mousex < 290) && (mousey > 575) && (mousey < 660))
        {
          al_play_sample(clique_jogo, 1.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
          sair = 1; continue;
        }

        //calculo para identificar em qual lugar da matriz o jogador clicou
				temp = mousex - LARGURA_TELA/2 + compensacao;
				j = temp / 50;
				temp = mousey - ALTURA_TELA/2 + compensacao;
				i = temp / 50;

				//se for o botao esquerdo ele vai revelar a casa
				if ((state.buttons & 1) || (evento.keyboard.keycode == 24))
				{
					if(i >= 0 && i < altura && j >= 0 && j < largura)
					{
            /*FEATURE!!!!!!!!!!!!!!
            O mapa só é gerado depois do primeiro clique,
            e ele é gerado de forma que nunca mate você no começo!
            */
						if (first == 0)
						{
							aux = bombas;
							first = 1; firstI = i; firstJ = j;
							GdT();
							campo = fopen("campo.txt", "r");
							tabuleiro = alocaMatriz();
							tabuleiro2 = alocaMatrizChar();
							leMatriz();
							gerarTabuleiro();
							bombas = aux; flags = bombas;
							cronometroInicial = al_get_time();
							newTempo = al_get_time();
						}
						if (tabuleiro2[i][j] == '#')
						{
							jogada(i, j);
						}
						else if (tabuleiro2[i][j] != '/' && tabuleiro2[i][j] != 'f')
						{
              contorno(i, j);
						}
					}
				}
				//se for o botao direito o jogador vai tirar ou colocar uma flag
				if ((state.buttons & 2) || (evento.keyboard.keycode == 26))
				{
					if(i >= 0 && i < altura && j >= 0 && j < largura && first == 1)
					{
						if (tabuleiro2[i][j] == '#')
						{
              al_play_sample(set_flag, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
							tabuleiro2[i][j] = 'f';
							flags --;
							drawCampo(tabuleiro2[i][j], i, j);
						}
						else if (tabuleiro2[i][j] == 'f')
						{
              al_play_sample(take_flag, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
							tabuleiro2[i][j] = '#';
							flags ++;
							drawCampo(tabuleiro2[i][j], i, j);
						}
					}
          else
          {
            al_play_sample(take_flag, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
          }
				}
			}
		}

    if (first != 0) //Inicia o cronômetro
			drawTempo();

    // Atualiza a tela
    controlFPS
		al_flip_display();
  }
  clean //Limpa memória RAM
  return;
}
