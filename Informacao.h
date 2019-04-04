int informacao()
{
  //Desenha o PLano de Fundo
  al_draw_bitmap(backgr, 0, 0, 0);
  al_draw_bitmap(bombaBG, LARGURA_TELA, ALTURA_TELA, 0);
  //Definindo Bitmaps
  ALLEGRO_BITMAP *area_voltar = 0;
  area_voltar = al_create_bitmap(360, 76);
  int na_area_voltar = 0;
  //Carregando fontes
  /*font2 = al_load_ttf_font("fonts/retro.ttf", 35, 0);
  font0 = al_load_ttf_font("fonts/retro.ttf", 100, 0);
  font3 = al_load_ttf_font("fonts/retro.ttf", 45, 0);*/
  //Carregando eventos
  ALLEGRO_EVENT_QUEUE *backpress = al_create_event_queue();
  al_register_event_source(backpress, al_get_display_event_source(janela));
  al_register_event_source(backpress, al_get_mouse_event_source());
  al_register_event_source(backpress, al_get_keyboard_event_source());
  //Variáveis de controle
  int done = 0;
  float altura = 5;
  float distancia = 72;
  int voltar = 0;
  //Inicia o loop de eventos
  while(!done)
  {
    al_wait_for_event(backpress, &eventback); //Espera por algum evento
    al_get_mouse_state(&state);
    mousex = state.x; //Pega a posição do mouse
    mousey = state.y; //Pega a posição do mouse
    if (eventback.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || eventback.type == ALLEGRO_EVENT_KEY_DOWN) //Ao clicar
    {
      //Clique em "Voltar"
      if((LARGURA_TELA / 1.2 - 50 < mousex) && (mousex < LARGURA_TELA / 1.2 + 220) && (mousey > ALTURA_TELA / 1.2 + 10 ) && (mousey < ALTURA_TELA / 1.2  + 91))
      {
        al_play_sample(clique_jogo, 1.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
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
    //Desenha o Plano de Fundo
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
    //Desenha os elementos na tela
    al_draw_bitmap(area_voltar, LARGURA_TELA / 1.2 - 50  , ALTURA_TELA / 1.2 + 13 , 0.5);

    al_draw_text(font0,al_map_rgb(255,229,32),LARGURA_TELA/2,ALTURA_TELA/4 - 170,ALLEGRO_ALIGN_CENTRE,"INFORMACAO");

    char stringBomb[20];

    sprintf(stringBomb, "%d", bombFacil);
    al_draw_text(font2, Green, 300 , ALTURA_TELA/altura + 40, ALLEGRO_ALIGN_CENTER, "FACIL");
    al_draw_text(font2, BrightRed, 500 , ALTURA_TELA/altura+ 40 , ALLEGRO_ALIGN_CENTER, "BOMBAS");
    al_draw_text(font2, Branco, 620, ALTURA_TELA/altura+ 40 , ALLEGRO_ALIGN_CENTER, stringBomb);
    al_draw_text(font2, BrightRed, 800 , ALTURA_TELA/altura+ 40 , ALLEGRO_ALIGN_CENTER, "TAMANHO");
    al_draw_text(font2, Branco, 970 , ALTURA_TELA/altura+ 40 , ALLEGRO_ALIGN_CENTER, "8X8");

    sprintf(stringBomb, "%d", bombMedio);
    al_draw_text(font2, Yellow, 300 , ALTURA_TELA/altura + 130, ALLEGRO_ALIGN_CENTER, "MEDIO");
    al_draw_text(font2, BrightRed, 500 , ALTURA_TELA/altura+ 130 , ALLEGRO_ALIGN_CENTER, "BOMBAS");
    al_draw_text(font2, Branco, 620, ALTURA_TELA/altura+ 130 , ALLEGRO_ALIGN_CENTER, stringBomb);
    al_draw_text(font2, BrightRed, 800 , ALTURA_TELA/altura+ 130 , ALLEGRO_ALIGN_CENTER, "TAMANHO");
    al_draw_text(font2, Branco, 970 , ALTURA_TELA/altura+ 130 , ALLEGRO_ALIGN_CENTER, "11X11");

    sprintf(stringBomb, "%d", bombDificil);
    al_draw_text(font2, Red, 308 , ALTURA_TELA/altura + 220, ALLEGRO_ALIGN_CENTER, "DIFICIL");
    al_draw_text(font2, BrightRed, 500 , ALTURA_TELA/altura+ 220 , ALLEGRO_ALIGN_CENTER, "BOMBAS");
    al_draw_text(font2, Branco, 620, ALTURA_TELA/altura+ 220 , ALLEGRO_ALIGN_CENTER, stringBomb);
    al_draw_text(font2, BrightRed, 800 , ALTURA_TELA/altura+ 220 , ALLEGRO_ALIGN_CENTER, "TAMANHO");
    al_draw_text(font2, Branco, 970 , ALTURA_TELA/altura+ 220 , ALLEGRO_ALIGN_CENTER, "12X16");

    al_draw_text(font2, Green, 308 , ALTURA_TELA/altura + 310, 0,
                "CLIQUE ESQUERDO -> ABRIR LOCAL");
    al_draw_text(font2, Red, 308 , ALTURA_TELA/altura + 400, 0,
                "CLIQUE DIREITO  -> MARCAR LOCAL");

    al_draw_rectangle(LARGURA_TELA /2 - 420, 150, LARGURA_TELA /2 + 420, 240, al_map_rgba_f(0, 0, 0, 0.8), 8.0);
    al_draw_rectangle(LARGURA_TELA /2 - 420, 240, LARGURA_TELA /2 + 420, 330, al_map_rgba_f(0, 0, 0, 0.8), 8.0);
    al_draw_rectangle(LARGURA_TELA /2 - 420, 330, LARGURA_TELA /2 + 420, 420, al_map_rgba_f(0, 0, 0, 0.8), 8.0);

    al_draw_rectangle(LARGURA_TELA / 1.2 - 50, ALTURA_TELA / 1.2 + 10, LARGURA_TELA / 1.2 + 220, ALTURA_TELA / 1.2 + 91, al_map_rgb(255, 255, 255), 6.0);
    al_draw_rectangle(LARGURA_TELA / 1.2 - 56, ALTURA_TELA / 1.2 + 4, LARGURA_TELA / 1.2 + 226, ALTURA_TELA / 1.2 + 97, al_map_rgb(0, 0, 0), 6.0);

    al_draw_text(font2, Branco1, 19*LARGURA_TELA / 20, 21*ALTURA_TELA / 24, ALLEGRO_ALIGN_RIGHT, "Voltar");
    //Atualiza o frame
    al_flip_display();
  }
  //Limpa a memória RAM
  al_destroy_event_queue(backpress);
  al_destroy_bitmap(area_voltar);
}
