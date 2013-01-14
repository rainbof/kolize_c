#include "allegro.h"

#define SCR_W 800
#define SCR_H 600

BITMAP *buffer; //obrazovy buffer
BITMAP *obr; //kdovico
//BITMAP *obr2;

const int POCET_NEPRATEL  =  50;
bool colision  = false; 
int  col = 0; 

struct Enemy {

	bool akt; // je objekt viditelny ?
	int x; // souøadnice 
	int y; // souøadnice 
	int speed; // rychlost 
	int w;  // výška spritu 
	int h;  // šíøka spritu 


}PocetNepratel[POCET_NEPRATEL];

//
// doprovodne funkce
//

/*string convertInt(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}
*/
//
// hlavni funkce
//

void InitDoubleBuffering(){//init grafickeho rezimu

	// obrazovy buffer
	buffer = create_bitmap(SCR_W,SCR_H);

	// Pokud se buffer navytvoøí ,vypíšeme hlášku a ukonèíme program 
	if(buffer == NULL)
	{
		set_gfx_mode(GFX_TEXT,0,0,0,0);
		allegro_message("Could not create buffer!");
		exit(EXIT_FAILURE);
	}
}

void DrawBuffer()
{ //vykresleni obsahu bufferu na obrazovku
	blit(buffer, screen,0,0,0,0,SCR_W,SCR_H);
}

void DrawEnemy()
{ //vykreslovani nepratel
	for(int i = 0; i < POCET_NEPRATEL;i++)
	{
		if (PocetNepratel[i].akt) { //pouze pokud je objekt aktivni
			masked_blit(obr,buffer,0,0,PocetNepratel[i].x,PocetNepratel[i].y,obr->w,obr->h);
		}
		//rectfill(screen, 0,0,PocetNepratel[i].x,PocetNepratel[i].y,makecol(0,255,255));
	}

}
void Draw()
{// napise jen kydy o kolizi zato ale hned
	if(colision == true)
	{
		textprintf_ex(screen,font,0,40, makecol(255,255,255),0, "Colize",0);
		allegro_message("colision");
	}
	else
	{// pokud se o kolizi nejednalo nic nedelej.
		// textprintf_ex(screen,font,0,40, makecol(255,255,255),0,
		// "NOT Colize",0);
	}
}

void Posun()
{ // posouvani objekty smerem dolu
	for(int i = 0; i < POCET_NEPRATEL ; i++)
	{
		PocetNepratel[i].y += PocetNepratel[i].speed; // cim rychleji tim objekt skace o vice pixelu

		if (PocetNepratel[i].y > 760) { PocetNepratel[i].y = -100; }
	}
}

void Colision()
{ //detekce kolize; zde to moc nefunguje    
	colision = false;

	for (int xx1=0; xx1<POCET_NEPRATEL;xx1++)
	{ // pro vsechy nepratele
		for (int xx2=0; xx2<POCET_NEPRATEL;xx2++)
		{
			if (((PocetNepratel[xx1].x>=PocetNepratel[xx2].x) && (PocetNepratel[xx1].x<=PocetNepratel[xx2].x+PocetNepratel[xx2].h)) &&
				((PocetNepratel[xx1].y>=PocetNepratel[xx2].y) && (PocetNepratel[xx1].y<=PocetNepratel[xx2].y+PocetNepratel[xx2].w)) &&
				(xx1<xx2) && // pouze 1/2 vseho
				(PocetNepratel[xx1].akt) && (PocetNepratel[xx2].akt)) // jsou aktivni
			{
				//textprintf_ex(screen,font,0,40, makecol(255,255,255),0, "kolize",0);
				PocetNepratel[xx1].akt = false; // vypnout objekt1
				PocetNepratel[xx2].akt = false; // vypnout objekt2
				circle(screen,PocetNepratel[xx1].x, PocetNepratel[xx1].y,3,makecol(255,255,250));
				//allegro_message("kolize " + convertInt(PocetNepratel[xx1].x));
			}
		}
   }


/*
	for(int i = 0; i < POCET_NEPRATEL ; i++)
	{
		if(PocetNepratel[i].y > 0 )  // Pokud už je na obrazovce
		{
			if(PocetNepratel[i].akt)
			{

				    int pos_x = PocetNepratel[i].x;
					int pos_y = PocetNepratel[i].y;

					if(( PocetNepratel[i].x > pos_x - 20)&&
						( PocetNepratel[i].x < pos_x + 20)&&
						( PocetNepratel[i].x > pos_y - 20)&&
						( PocetNepratel[i].x < pos_y + 20))
					{
						PocetNepratel[i].akt = false;

						colision = true;
						circle(screen,PocetNepratel[i].x, PocetNepratel[i].y,3,makecol(255,255,255));
						break;
						//return true;
					}
					else{ 
					}
					
					
			}     
			
		}

	} 

*/
}
void Init()
{ // konstruktor

	srand((unsigned)time(0)); 

	for (int i=0; i<POCET_NEPRATEL; i++)
	{  
		PocetNepratel[i].x =(rand()% (SCREEN_W/30))*30;
		//PocetNepratel[i].x = 
		PocetNepratel[i].y = (-(rand()% SCREEN_H));
		//		PocetNepratel[i].y = 1;
		PocetNepratel[i].speed = (rand()% 3 );
		PocetNepratel[i].akt = true;
		PocetNepratel[i].w = obr->w; 
		PocetNepratel[i].h = obr->h;
		//PocetNepratel[i].bitmap_x = PocetNepratel[i].w / 2;
		//PocetNepratel[i].bitmap_y = PocetNepratel[i].h / 2;

	}
}
int main(void)
{

	// Nastavíme pozici ètvercù 
	//int pos_x = 10;
	//int pos_y = 10;
	//int pos_x2 = 100;
	//int pos_y2 = 100;
	//------------------------

	// Nastavíme barvu ètvercù r,g,b
	//int r = 0;
	//int g = 255;
	//int b = 0;
	//-------------------------

	allegro_init();	 // inicializace allegra
	install_keyboard(); // inicializace klavesnice
	obr = load_bitmap("obr.bmp",NULL);
	//obr2 = load_bitmap("obr2.bmp",NULL);

	set_color_depth(8); // Nastavíme hloubku , Grafický mod ,a výšku a šíøku obrazovky
	if (set_gfx_mode(GFX_AUTODETECT|GFX_AUTODETECT_WINDOWED, SCR_W ,SCR_H, 0, 0)) 
	{
		set_color_depth(24);
		if (set_gfx_mode(GFX_AUTODETECT|GFX_AUTODETECT_WINDOWED, SCR_W , SCR_H, 0, 0)) 
		{
			set_color_depth(16);
			if (set_gfx_mode(GFX_AUTODETECT|GFX_AUTODETECT_WINDOWED, SCR_W , SCR_H , 0, 0)) 
			{
				set_color_depth(15);
				if (set_gfx_mode(GFX_AUTODETECT|GFX_AUTODETECT_WINDOWED, SCR_W , SCR_H, 0, 0)) 
				{
					allegro_message("Video Error: %s.\n", allegro_error);
					return 1;
				}
			}
		}
	}
	InitDoubleBuffering();
	Init();              

	while (!key[KEY_ESC])
	{

       /* if(key[KEY_UP])
		{ pos_y -= 1;}
		if(key[KEY_DOWN])
		{ pos_y += 1;}
		if(key[KEY_RIGHT])
		{ pos_x += 1;}
		if(key[KEY_LEFT])
		{ pos_x -= 1;}

		if(key[KEY_W])
		{ pos_y2 -= 1;}
		if(key[KEY_S])
		{ pos_y2 += 1;}
		if(key[KEY_D])
		{ pos_x2 += 1;}
		if(key[KEY_A])
		{ pos_x2 -= 1;}

		if((pos_x > pos_x2 - 20) && ( pos_x < pos_x2 + 20) && (pos_y > pos_y2 - 20 ) && (pos_y < pos_y2 + 20)){}
		else{}
		*/
		
		Posun();
		DrawEnemy();
//		Draw();
		DrawBuffer();
		Colision();
		clear_bitmap(buffer);
		rest(10); //jinak tez wait()

	}
	destroy_bitmap(obr);
	return 0;
}
END_OF_MAIN()