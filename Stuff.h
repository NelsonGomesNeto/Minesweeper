#define all_directions jogada_coluna >= 0 && jogada_coluna < largura && jogada_linha < altura && jogada_linha >= 0

typedef struct ALLEGRO_MOUSE_STATE ALLEGRO_MOUSE_STATE;
typedef struct ALLEGRO_FILE ALLEGRO_FILE;

//Constantes de tela
const int LARGURA_TELA = 1280;//Largura
const int ALTURA_TELA = 720;//Altura

int largura, altura, bombas, compensacao, flags; char stringFlags[100];
int bombFacil, bombMedio, bombDificil;
int **tabuleiro;
char **tabuleiro2;
FILE *campo, *config;
int FRAMES_POR_SEGUNDO, backUpFPS;
double tempoInicial = 0, cronometro, newTempo; char stringTempo[100];
int distanciax;
int distanciay;
float multiplicador_tamanho;
int firstI = -1, firstJ = -1;
int win, lose, aux;
int dificuldade, first;
int mousex, mousey;

//Declara eventos
ALLEGRO_EVENT_QUEUE *fila_eventos = 0;
ALLEGRO_EVENT evento;
ALLEGRO_EVENT eventback;
ALLEGRO_MOUSE_STATE state;

//Declara BITMAPS
//////////////////////SPRITES DAS CASAS////////////////////////////////////////
ALLEGRO_BITMAP *imagem = 0, *vazio = 0, *um = 0, *dois = 0, *tres = 0;
ALLEGRO_BITMAP *quatro = 0, *cinco = 0, *seis = 0, *sete = 0, *oito = 0;
ALLEGRO_BITMAP *bomba = 0, *flag = 0, *expImage = 0;
ALLEGRO_BITMAP *area_jogar = 0, *area_informacao = 0;
ALLEGRO_BITMAP *area_ver_recordes = 0, *area_creditos = 0;
ALLEGRO_BITMAP *area_sair_do_jogo = 0, *area_menu_fundo = 0;
ALLEGRO_BITMAP *backgr = 0, *bombaBG = 0;

//Declara fontes e cores
ALLEGRO_FONT *font;
ALLEGRO_FONT *font0;
ALLEGRO_FONT *font1;
ALLEGRO_FONT *font2;
ALLEGRO_FONT *font3;
ALLEGRO_FONT *font4, *font5, *font6;
ALLEGRO_COLOR branco;
ALLEGRO_COLOR Branco, Azul, VermelhoClaro, Preto, Cinza;
ALLEGRO_COLOR Branco1, Branco2, Branco3, Branco4, Branco5;
ALLEGRO_COLOR Electric;
ALLEGRO_COLOR Electric2;
ALLEGRO_COLOR CoolBlue;
ALLEGRO_COLOR BrightRed;
ALLEGRO_COLOR Red;
ALLEGRO_COLOR Green;
ALLEGRO_COLOR Yellow;

//Declara sons
ALLEGRO_SAMPLE *musica = 0;//Musica de fundo
ALLEGRO_SAMPLE *clique_jogo = 0;//Som de clique no menu
ALLEGRO_SAMPLE *clique_menu = 0;//Som de clique durante a gameplay
ALLEGRO_SAMPLE *explosao = 0;//Som de explosão
ALLEGRO_SAMPLE *floodfill_som = 0;//Som usado no floodfield
ALLEGRO_SAMPLE *inicio = 0;//Som de inicio
ALLEGRO_SAMPLE *set_flag = 0;//Som de colocar bandeira
ALLEGRO_SAMPLE *take_flag = 0;//Som de tirar bandeira
ALLEGRO_SAMPLE *game_over = 0;//Som de fim de jogo
ALLEGRO_SAMPLE *victory = 0;//som de vitória
ALLEGRO_SAMPLE_ID *id_music = 0;//ID da musica de fundo
ALLEGRO_SAMPLE_ID *id_game_over = 0;//ID do som de fim de jogo
ALLEGRO_SAMPLE_ID *id_victory = 0;//ID do som de vitória

//Declara a janela
ALLEGRO_DISPLAY *janela = 0;

int music = 0;
int menu = 1;

void load_fonts()
{
  font  = al_load_ttf_font("fonts/retro3d.ttf", 100, 0);
  font0 = al_load_ttf_font("fonts/retro.ttf", 100, 0);
  font1 = al_load_ttf_font("fonts/retro3d.ttf", 150, 0);
  font2 = al_load_ttf_font("fonts/retro.ttf", 35, 0);
  font3 = al_load_ttf_font("fonts/retro.ttf", 45, 0);
  font4 = al_load_ttf_font("fonts/retro.ttf", 30, 0);
  font5 = al_load_ttf_font("fonts/retro.ttf", 40, 0);
  font6 = al_load_ttf_font("fonts/retro.ttf", 110, 0);
}

void load_colors()
{
  branco 				= al_map_rgb(255, 255, 255);
  Azul 					= al_map_rgb(44,117,255);
  VermelhoClaro = al_map_rgb(250,28,3);
  Preto 				= al_map_rgb(0, 0, 0);
  Cinza		  		= al_map_rgb(172, 166, 166);
  Electric  		= al_map_rgb(255, 229, 32);
  Electric2 		= al_map_rgb(236, 242, 22);
  CoolBlue		  = al_map_rgb(168, 200, 249);
  BrightRed 		= al_map_rgb(250, 28, 3);
  Branco    		= al_map_rgb(255, 255, 255);
  Red       		= al_map_rgb(250,31,3);
  Green     		= al_map_rgb(102,241,10);
  Yellow    		= al_map_rgb(255,229,32);
}
