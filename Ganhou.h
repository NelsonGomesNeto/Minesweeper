//Header de Ganhou
int ganhou(score atual)
{
  //Desenha o Plano de Fundo
  al_draw_bitmap(backgr, 0, 0, 0);
  al_draw_bitmap(bombaBG, LARGURA_TELA, ALTURA_TELA, 0);
  //Carrega sons
  al_stop_sample(id_music);
  victory = al_load_sample("songs/victory.wav");
  music = 1;
  id_victory = malloc(sizeof(ALLEGRO_SAMPLE_ID));
  al_play_sample(victory, 0.7, 0, 1, ALLEGRO_PLAYMODE_LOOP, id_victory);
  //Definindo Bitmaps
  ALLEGRO_BITMAP *area_voltar = 0;
  area_voltar = al_create_bitmap(360, 76);
  int na_area_voltar = 0;
  //Carregando eventos
  ALLEGRO_EVENT_QUEUE *backpress = al_create_event_queue();
  al_register_event_source(backpress, al_get_display_event_source(janela));
  al_register_event_source(backpress, al_get_mouse_event_source());
  al_register_event_source(backpress, al_get_keyboard_event_source());
  //Variáveis de controle
  int done = 0;
  float altura = 2.1;
  float distancia = 72;
  int move;
  int voltar = 0; int letras = 0;
  move = 0;
  while (move < 4)
  {
    atual.nome[move] = ' ';
    move ++;
  }
  //Inicia o loop de eventos
  while(!done)
  {
    al_wait_for_event(backpress, &eventback); //Espera por algum evento
    //Eventos com o teclado
    if (eventback.type == ALLEGRO_EVENT_KEY_DOWN)
    {
      //Transformando a entrada do Allegro para string
      if (eventback.keyboard.keycode != 63)
      {
        if (eventback.keyboard.keycode < 27)
        {
          atual.nome[letras] = eventback.keyboard.keycode + 'A' - 1;
          move = letras + 1;
          while (move < 4)
          {
            atual.nome[move] = ' ';
            move ++;
          }
        }
        else
        {
          atual.nome[letras] = eventback.keyboard.keycode + 21;
        }
        letras ++;
      }
      else
      {
        atual.nome[letras] = ' ';
        letras --;
      }
      atual.nome[3] = ' ';
      if (letras < 0)
      {
        letras = 0;
      }
      if (letras >= 3)
      {
        letras = 2;
      }
    }
    //Eventos com o mouse
    mousex = eventback.mouse.x; //Pega a posição do mouse
    mousey = eventback.mouse.y; //Pega a posição do mouse
    if(eventback.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
      //Clique em "Voltar"
      if((LARGURA_TELA / 1.2 - 50 < mousex) && (mousex < LARGURA_TELA / 1.2 + 220)
      && (mousey > ALTURA_TELA / 1.2 + 10 ) && (mousey < ALTURA_TELA / 1.2  + 91))
      {
        move = letras;
        while (move < 4)
        {
          move ++;
          atual.nome[move] = '\0';
        }
        changeRankingData(atual); //Salva a pontuação
        al_stop_sample(id_victory);
        done = 1; //Acaba com o loop
      }
    }
    else if (eventback.type == ALLEGRO_EVENT_MOUSE_AXES) //Apontando para
    {
      //Sobre "Voltar"
      if((LARGURA_TELA / 1.2 - 50 < mousex) && (mousex < LARGURA_TELA / 1.2 + 220) && (mousey > ALTURA_TELA / 1.2 + 10 ) && (mousey < ALTURA_TELA / 1.2  + 91))
        na_area_voltar = 1;
      else
        na_area_voltar = 0;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0)); //Limpa a tela
    //Desenha o PLano de Fundo
    al_draw_bitmap(backgr, 0, 0, 0);
    al_draw_bitmap(bombaBG, LARGURA_TELA / 2 - 256, ALTURA_TELA / 2 - 256, 0);
    //Modificando o Bitmap "area_voltar" com o efeito "Apontar"
    al_set_target_bitmap(area_voltar);
    if (!na_area_voltar)
    {
      al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
      Branco1 = al_map_rgb(255,255,255);
    }
    else
    {
      al_clear_to_color(al_map_rgba_f(0.2, 0.2, 0.2, 0.5));
      Branco1 = al_map_rgb(255,229,32);
    }
    //Usando a tela
    al_set_target_bitmap(al_get_backbuffer(janela));
    //Desenha elementos na tela
    al_draw_bitmap(area_voltar, LARGURA_TELA / 1.2 - 50  , ALTURA_TELA / 1.2 + 13 , 0.5);

    al_draw_text(font,al_map_rgb(102,241,10),LARGURA_TELA/2,ALTURA_TELA/4 - 150,ALLEGRO_ALIGN_CENTRE,"Parabens! Voce Ganhou.");
    al_draw_text(font2,al_map_rgb(255,229,32),LARGURA_TELA/2 - 40,ALTURA_TELA/4 + 100,ALLEGRO_ALIGN_CENTRE,"Digite seu nome");
    al_draw_filled_rectangle(LARGURA_TELA/3 + 98 , ALTURA_TELA /3  + 90, LARGURA_TELA /3 + 250, ALTURA_TELA /3 + 150, al_map_rgba_f(0, 0, 0, 0.5));
    al_draw_rectangle(LARGURA_TELA /3 + 96, ALTURA_TELA / 3 + 90, LARGURA_TELA / 3 + 250, ALTURA_TELA / 3 + 150, al_map_rgb(0, 0, 0), 6.0);

    al_draw_rectangle(LARGURA_TELA / 1.2 - 50, ALTURA_TELA / 1.2 + 10, LARGURA_TELA / 1.2 + 220, ALTURA_TELA / 1.2 + 91, al_map_rgb(255, 255, 255), 6.0);
    al_draw_rectangle(LARGURA_TELA / 1.2 - 56, ALTURA_TELA / 1.2 + 4, LARGURA_TELA / 1.2 + 226, ALTURA_TELA / 1.2 + 97, al_map_rgb(0, 0, 0), 6.0);

    al_draw_text(font2, Branco1, 19*LARGURA_TELA / 20, 21*ALTURA_TELA / 24, ALLEGRO_ALIGN_RIGHT, "Voltar");

    al_draw_text(font2, Branco, LARGURA_TELA/2 + distancia - 100, ALTURA_TELA/altura, ALLEGRO_ALIGN_CENTER, atual.nome);
    //Atualiza o frame
    al_flip_display();
  }
  //Limpa a memória RAM
  free(id_victory);
  al_destroy_event_queue(backpress);
  al_destroy_bitmap(area_voltar);
  al_destroy_sample(victory);
}
