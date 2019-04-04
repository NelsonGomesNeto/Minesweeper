//Header de Perdeu
int perdeu()
{
  //Desenha o PLano de Fundo
  al_draw_bitmap(backgr, 0,0, 0);
  al_draw_bitmap(bombaBG, LARGURA_TELA,ALTURA_TELA , 0);
  //Carregando sons
  al_stop_sample(id_music);
  game_over = al_load_sample("songs/game_over.wav");
  music = 1;
  id_game_over = malloc(sizeof(ALLEGRO_SAMPLE_ID));
  al_play_sample(game_over, 0.7, 0, 1, ALLEGRO_PLAYMODE_LOOP, id_game_over);
  //Definindo o Bitmaps
  ALLEGRO_BITMAP *area_voltar = 0, *area_menu_fundo = 0;
  area_voltar = al_create_bitmap(360, 72);
  area_menu_fundo = al_create_bitmap(360, 72);
  int na_area_voltar = 0;
  //Carregando eventos
  ALLEGRO_EVENT_QUEUE *backpress = al_create_event_queue();
  al_register_event_source(backpress, al_get_display_event_source(janela));
  al_register_event_source(backpress, al_get_mouse_event_source());
  al_register_event_source(backpress, al_get_keyboard_event_source());
  //Variáveis de controle
  int voltar = 0;
  int done = 0;
  float altura = 2.1;
  float distancia = 72;
  //Inicia o loop de eventos
  while(!done)
  {
    al_wait_for_event(backpress, &eventback); //Espera por algum evento
    al_get_mouse_state(&state);
    mousex = state.x; //Pega a posição do mouse
    mousey = state.y; //Pega a posição do mouse
    if(eventback.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || eventback.type == ALLEGRO_EVENT_KEY_DOWN) //Ao clicar
    {
      //Clique em "Voltar"
      if((400 < mousex) && (mousex < LARGURA_TELA / 1.7 + 65)
      && (mousey > ALTURA_TELA / 1.8) && (mousey < ALTURA_TELA / 1.8 + 72))
      {
        al_play_sample(clique_jogo, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
        al_stop_sample(id_game_over);
        done = 1; //Acaba com o loop
      }
    }
    else if (eventback.type == ALLEGRO_EVENT_MOUSE_AXES) //Apontando para
    {
      //Sobre "Voltar"
      if((400 < mousex) && (mousex < LARGURA_TELA / 1.7 + 65) && (mousey > ALTURA_TELA / 1.8) && (mousey < ALTURA_TELA / 1.8 + 72))
        na_area_voltar = 1;
      else
        na_area_voltar = 0;
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
      Branco2 = al_map_rgb(255,255,255);
    }
    else
    {
      al_clear_to_color(al_map_rgba_f(0.2, 0.2, 0.2, 0.5));
      Branco2 = al_map_rgb(255,229,32);
    }
    //Usando a tela
    al_set_target_bitmap(al_get_backbuffer(janela));
    //Desenha os elementos na tela
    al_draw_bitmap(area_menu_fundo, LARGURA_TELA / 2.8  , ALTURA_TELA / 1.8 , 0.5);
    al_draw_rectangle(LARGURA_TELA/2 - 180, ALTURA_TELA / 1.8, LARGURA_TELA/2 + 180, ALTURA_TELA / 1.8 + 72, al_map_rgb(255, 255, 255), 6.0);
    al_draw_rectangle(LARGURA_TELA/2 - 186, ALTURA_TELA / 1.8 - 6, LARGURA_TELA/2 + 186, ALTURA_TELA / 1.8 + 78, al_map_rgb(0, 0, 0), 6.0);
    al_draw_bitmap(area_voltar, LARGURA_TELA/2.8  , ALTURA_TELA / 2.2 + distancia, 0.5);

    al_draw_text(font1,al_map_rgb(250,31,3),LARGURA_TELA/2,ALTURA_TELA/4 - 100,ALLEGRO_ALIGN_CENTRE,"VOCE PERDEU");

    al_draw_text(font2, Branco2, LARGURA_TELA/2, ALTURA_TELA/altura + distancia, ALLEGRO_ALIGN_CENTER, "VOLTAR AO MENU");
    //Atualiza o frame
    al_flip_display();
  }
  //Limpa a memória RAM
  free(id_game_over);
  al_destroy_bitmap(area_voltar);
  al_destroy_bitmap(area_menu_fundo);
  al_destroy_sample(game_over);
  al_destroy_event_queue(backpress);
}
