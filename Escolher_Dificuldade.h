//Header de Escolher Dificuldade
int choose()
{
  //Desenha o Plano de Fundo
  al_draw_bitmap(backgr, 0,0, 0);
  al_draw_bitmap(bombaBG, LARGURA_TELA,ALTURA_TELA , 0);
  //Declarando o Bitmaps
  ALLEGRO_BITMAP *area_menu_fundo = 0, *area_voltar = 0, *area_medio = 0, *area_facil = 0, *area_dificil = 0;
  area_voltar = al_create_bitmap(360, 76);
  area_facil = al_create_bitmap(360, 72);
  area_medio = al_create_bitmap(360, 72);
  area_dificil = al_create_bitmap(360, 72);
  area_menu_fundo =   al_create_bitmap(360, 360);
  int na_area_voltar = 0, na_area_facil = 0, na_area_medio = 0, na_area_dificil = 0;
  //Carregando eventos
  ALLEGRO_EVENT_QUEUE *backpress = al_create_event_queue();
  al_register_event_source(backpress, al_get_display_event_source(janela));
  al_register_event_source(backpress, al_get_mouse_event_source());
  al_register_event_source(backpress, al_get_keyboard_event_source());
  //Variáveis de controle
  float altura = 2.1;
  float distancia = 72;
  int done = 0;
  int voltar = 0;
  //Inicia loop de eventos
  while(!done)
  {
    al_wait_for_event(backpress, &eventback); //Espera por algum evento
    al_get_mouse_state(&state);
    mousex = state.x; //Pega a posição do mouse
    mousey = state.y; //Pega a posição do mouse
    if(eventback.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || eventback.type == ALLEGRO_EVENT_KEY_DOWN) //Ao clicar
    {
      //Clique em "Voltar"
      if((LARGURA_TELA / 1.2 - 50 < mousex) && (mousex < LARGURA_TELA / 1.2 + 220)
      && (mousey > ALTURA_TELA / 1.2 + 10 ) && (mousey < ALTURA_TELA / 1.2  + 91))
      {
        al_play_sample(clique_jogo, 1.1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
        done = 1;
      }
      //Clique em "Fácil"
      if((400 < mousex) && (mousex < LARGURA_TELA / 1.7 + 65) && (mousey > ALTURA_TELA / 1.8) && (mousey < ALTURA_TELA / 1.8 + 72))
      {
        al_play_sample(clique_jogo, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
        //Limpa a memória RAM
        al_destroy_event_queue(backpress);
        al_destroy_bitmap(area_voltar);
        al_destroy_bitmap(area_facil);
        al_destroy_bitmap(area_medio);
        al_destroy_bitmap(area_dificil);
        al_destroy_bitmap(area_menu_fundo);
        return 1; //Dificuldade
      }
      //Clique em Médio
      if((400 < mousex) && (mousex < LARGURA_TELA / 1.7 + 65) && (mousey > ALTURA_TELA / 1.53) && (mousey < ALTURA_TELA /  1.53 + 72))
      {
        al_play_sample(clique_jogo, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
        //Limpa a memória RAM
        al_destroy_event_queue(backpress);
        al_destroy_bitmap(area_voltar);
        al_destroy_bitmap(area_facil);
        al_destroy_bitmap(area_medio);
        al_destroy_bitmap(area_dificil);
        al_destroy_bitmap(area_menu_fundo);
        return 2; //Dificuldade
      }
      if((400 < mousex) && (mousex< LARGURA_TELA / 1.7 + 65) && (mousey > ALTURA_TELA / 1.35 + 1) && (mousey < ALTURA_TELA / 1.35 + 72))
      {
        al_play_sample(clique_jogo, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
        //Limpa a memória RAM
        al_destroy_event_queue(backpress);
        al_destroy_bitmap(area_voltar);
        al_destroy_bitmap(area_facil);
        al_destroy_bitmap(area_medio);
        al_destroy_bitmap(area_dificil);
        al_destroy_bitmap(area_menu_fundo);
        return 3; //Dificuldade
      }
    }
    else if (eventback.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
      //Sobre "Voltar"
      if((LARGURA_TELA / 1.2 - 50 < mousex) && (mousex < LARGURA_TELA / 1.2 + 220) && (mousey > ALTURA_TELA / 1.2 + 10 ) && (mousey < ALTURA_TELA / 1.2  + 91))
        na_area_voltar = 1;
      else
        na_area_voltar = 0;
      //Sobre "Fácil"
      if((400 < mousex) && (mousex < LARGURA_TELA / 1.7 + 65) && (mousey > ALTURA_TELA / 1.8) && (mousey < ALTURA_TELA / 1.8 + 72))
        na_area_facil = 1;
      else
        na_area_facil = 0;
      //Sobre "Médio"
      if((400 < mousex) && (mousex < LARGURA_TELA / 1.7 + 65) && (mousey > ALTURA_TELA /  1.53) && (mousey < ALTURA_TELA /  1.53 + 72))
        na_area_medio = 1;
      else
        na_area_medio = 0;
      //Sobre "Difícil"
      if((400 < mousex) && (mousex< LARGURA_TELA / 1.7 + 65) && (mousey > ALTURA_TELA / 1.35 + 1) && (mousey < ALTURA_TELA / 1.35 + 72))
        na_area_dificil = 1;
      else
        na_area_dificil = 0;
    }
    al_clear_to_color(al_map_rgb(0, 0, 0)); //Limpa a tela
    //Desenha o Plano de Fundo
    al_draw_bitmap(backgr, 0, 0, 0);
    al_draw_bitmap(bombaBG, LARGURA_TELA / 2 - 256, ALTURA_TELA / 2 - 256, 0);
    al_set_target_bitmap(area_menu_fundo);
    al_clear_to_color(al_map_rgba_f(0, 0, 0, 0.5)); //Limpa a tela
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
    //Modificando o Bitmap "area_facil" com o efeito "Apontar"
    al_set_target_bitmap(area_facil);
    if (!na_area_facil)
    {
      al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
      Branco2 = al_map_rgb(255,255,255);
    }
    else
    {
      al_clear_to_color(al_map_rgba_f(0.2, 0.2, 0.2, 0.5));
      Branco2 = al_map_rgb(255,229,32);
    }
    //Modificando o Bitmap "area_medio" com o efeito "Apontar"
    al_set_target_bitmap(area_medio);
    if (!na_area_medio)
    {
      al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
      Branco3 = al_map_rgb(255,255,255);
    }
    else
    {
      al_clear_to_color(al_map_rgba_f(0.2, 0.2, 0.2, 0.5));
      Branco3 = al_map_rgb(255,229,32);
    }
    //Modificando o Bitmap "area_dificil" com o efeito "Apontar"
    al_set_target_bitmap(area_dificil);
    if (!na_area_dificil)
    {
      al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
      Branco4 = al_map_rgb(255,255,255);
    }
    else
    {
      al_clear_to_color(al_map_rgba_f(0.2, 0.2, 0.2, 0.5));
      Branco4 = al_map_rgb(255,229,32);
    }
    //Usando a tela
    al_set_target_bitmap(al_get_backbuffer(janela));
    //Desenha os elementos na tela
    al_draw_scaled_bitmap(area_menu_fundo, 0, 0,
      al_get_bitmap_width(area_menu_fundo), al_get_bitmap_height(area_menu_fundo),
      LARGURA_TELA / 2.8, ALTURA_TELA / 2.2 + 60,
      al_get_bitmap_width(area_menu_fundo), al_get_bitmap_height(area_menu_fundo) - 110, 0);
    al_draw_bitmap(area_facil, LARGURA_TELA/2.8  , ALTURA_TELA / 2.2 + distancia, 0.5);
    al_draw_bitmap(area_medio, LARGURA_TELA / 2.8  , ALTURA_TELA / 2.2 + distancia*2 , 0.5);
    al_draw_bitmap(area_dificil, LARGURA_TELA / 2.8  , ALTURA_TELA / 2.2 + distancia*3, 0.5);
    al_draw_bitmap(area_voltar, LARGURA_TELA / 1.2 - 50  , ALTURA_TELA / 1.2 + 13 , 0.5);
    al_draw_rectangle(LARGURA_TELA/2 - 180, ALTURA_TELA/altura + 45, LARGURA_TELA/2 + 180, ALTURA_TELA/altura + distancia*5 - 10 - 65, al_map_rgb(255, 255, 255), 6.0);
    al_draw_rectangle(LARGURA_TELA/2 - 186, ALTURA_TELA/altura + 39, LARGURA_TELA/2 + 186, ALTURA_TELA/altura + distancia*5 - 4 - 65, al_map_rgb(0, 0, 0), 6.0);

    al_draw_text(font1,al_map_rgb(255,229,32),LARGURA_TELA/2,ALTURA_TELA/4 - 100,ALLEGRO_ALIGN_CENTRE,"CAMPO MINADO");

    al_draw_text(font2, Branco2, LARGURA_TELA/2, ALTURA_TELA/altura + distancia, ALLEGRO_ALIGN_CENTER, "FACIL");
    al_draw_text(font2, Branco3, LARGURA_TELA/2, ALTURA_TELA/altura + distancia*2, ALLEGRO_ALIGN_CENTER, "MEDIO");
    al_draw_text(font2, Branco4, LARGURA_TELA/2, ALTURA_TELA/altura + distancia*3, ALLEGRO_ALIGN_CENTER, "DIFICIL");
    ///Contorno
    al_draw_rectangle(LARGURA_TELA / 1.2 - 50, ALTURA_TELA / 1.2 + 10, LARGURA_TELA / 1.2 + 220, ALTURA_TELA / 1.2 + 91, al_map_rgb(255, 255, 255), 6.0);
    al_draw_rectangle(LARGURA_TELA / 1.2 - 56, ALTURA_TELA / 1.2 + 4, LARGURA_TELA / 1.2 + 226, ALTURA_TELA / 1.2 + 97, al_map_rgb(0, 0, 0), 6.0);

    al_draw_text(font2, Branco1, 19*LARGURA_TELA / 20, 21*ALTURA_TELA / 24, ALLEGRO_ALIGN_RIGHT, "Voltar");
    //Atualiza o frame
    al_flip_display();
  }
  //Limpa a memória RAM
  al_destroy_event_queue(backpress);
  al_destroy_bitmap(area_voltar);
  al_destroy_bitmap(area_facil);
  al_destroy_bitmap(area_medio);
  al_destroy_bitmap(area_dificil);
  al_destroy_bitmap(area_menu_fundo);
  return -1;
}
