//Header dos Créditos
int credits()
{
  //Desenha o Plano de Fundo
  al_draw_bitmap(backgr, 0, 0, 0);
  al_draw_bitmap(bombaBG, LARGURA_TELA, ALTURA_TELA, 0);
  //Definindo Bitmaps
  ALLEGRO_BITMAP *area_voltar = 0;
  area_voltar = al_create_bitmap(360, 76);
  int na_area_voltar = 0;
  //Carregando fontes
  /*font2 = al_load_ttf_font("fonts/retro.ttf", 35, 0);
  font1 = al_load_ttf_font("fonts/retro3d.ttf", 150, 0);*/
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
      if((LARGURA_TELA / 1.2 - 50 < mousex) && (mousex < LARGURA_TELA / 1.2 + 220)
      && (mousey > ALTURA_TELA / 1.2 + 10 ) && (mousey < ALTURA_TELA / 1.2  + 91))
      {
        al_play_sample(clique_jogo, 1.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
        done = 1; //Acaba com o loop
      }
    }
    else if (eventback.type == ALLEGRO_EVENT_MOUSE_AXES) //Apontando para
    {
      //Sobre "Voltar"
      if((LARGURA_TELA / 1.2 - 50 < mousex) && (mousex < LARGURA_TELA / 1.2 + 220)
      && (mousey > ALTURA_TELA / 1.2 + 10 ) && (mousey < ALTURA_TELA / 1.2  + 91))
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
    al_draw_text(font1,al_map_rgb(255,229,32),LARGURA_TELA/2,ALTURA_TELA/4 - 100,ALLEGRO_ALIGN_CENTRE,"Creditos");
    //Nossos nomes
    al_draw_text(font2, Branco, LARGURA_TELA/2, ALTURA_TELA/altura , ALLEGRO_ALIGN_CENTER, "Cicero Rafael");
    al_draw_text(font2, Branco, LARGURA_TELA/2, ALTURA_TELA/altura + distancia, ALLEGRO_ALIGN_CENTER, "Lucas Ribeiro Raggi");
    al_draw_text(font2, Branco, LARGURA_TELA/2, ALTURA_TELA/altura + distancia*2, ALLEGRO_ALIGN_CENTER, "Nelson Gomes Neto");
    al_draw_text(font2, Branco, LARGURA_TELA/2, ALTURA_TELA/altura + distancia*3, ALLEGRO_ALIGN_CENTER, "Thiago");
    //Contorno
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
