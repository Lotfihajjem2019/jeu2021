#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

int main ( int argc, char* argv )
{


    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // initialize SDL video
    

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(612, 380,32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    SDL_Surface* img = IMG_Load("BatmanSuperman.jpg");
    if (!img)
    {
        printf("Unable to load png: %s\n", SDL_GetError());
        return 1;
    }
	SDL_Surface* couleur = IMG_Load("color.jpg");
    if (!couleur)
    {
        printf("Unable to load png: %s\n", SDL_GetError());
        return 1;
    }
	SDL_Surface* superman=IMG_Load("Superman.png");
	
	if (superman == NULL) {
		printf("Unable to load png: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Surface* batman=IMG_Load("Batman.png");
	if (batman == NULL) {
		printf("Unable to load png: %s\n", SDL_GetError());
		return 1;
	}
				// Son
Mix_Chunk *musique;
if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) ==-1) //Initialisation de l'API Mixer

    {
        printf("%s", Mix_GetError());
    }
musique = Mix_LoadWAV("son.wav");
   				 // Texte
	if ( TTF_Init() == -1 )
    {
        printf( "Unable to init TTF: %s\n", TTF_GetError() );
        return 1;
    }
    SDL_Color couleurNoire = {0, 0, 0};
    TTF_Font* police;
    police  = TTF_OpenFont("times.ttf", 25);
    if(!police)
    {
        printf("Unable to load police %s\n", TTF_GetError());
        return 1;
    }
    
    SDL_Surface* vert = TTF_RenderText_Blended(police, "GREEN", couleurNoire);
    SDL_Surface* violet = TTF_RenderText_Blended(police, "PURPLE", couleurNoire);
    SDL_Surface* texte = TTF_RenderText_Blended(police, "Bonjour", couleurNoire);
    

    // position des images
    SDL_Rect posScreen; //position background
    SDL_Rect positionbatman;
    SDL_Rect positionsuperman;
    SDL_Rect positionecran;
    SDL_Rect postext;
    posScreen.x = 0;
    posScreen.y = 0;
    posScreen.w = img->w;
    posScreen.h = img->h;
    positionbatman.x = 0;
    positionbatman.y =0;
    positionsuperman.x = 484;
    positionsuperman.y = 0;
    // position du texte
    SDL_Rect posP, posG;    
    posG.x = 100;
    posG.y = 252;
    posP.x = 22;
    posP.y = 110;
    postext.x=img->w/2-texte->w/2;
    postext.y=img->h/2-texte->h/2;
	
    SDL_Event event;
    int done = 1;
    int coul = 0;
    int affich=0;
    while(done)
    {
        SDL_BlitSurface(img, NULL, screen, &posScreen);
	SDL_BlitSurface(superman, NULL, screen, &positionsuperman);
	SDL_BlitSurface(batman, NULL, screen, &positionbatman);

        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            // exit if the window is closed
            case SDL_QUIT:
                done = 0;
                break;

            // évenement touches claviers
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    done = 0;
                    break;

                 case SDLK_g:
                    coul =1;
                    break;

                case SDLK_p:
                    coul =2;
                    break;               
                }
//évenement curseur souris
		case SDL_MOUSEMOTION: 
		{				
		if(event.motion.x>positionbatman.x&&event.motion.x<positionbatman.x+batman->w&&event.motion.y>positionbatman.y&&event.motion.y<positionbatman.y+batman->h)
		{
		  Mix_PlayChannel(-1,musique,0);
		
		SDL_Flip(screen);//rafraichir la fenetre
		//SDL_Delay(30);
		}	
		break;
		}
//évenement clic souris
	case SDL_MOUSEBUTTONUP:
	if(event.button.button == SDL_BUTTON_LEFT)
	{

	if(event.button.x > positionsuperman.x && event.button.x < positionsuperman.x+superman->w && event.button.y > positionsuperman.y && event.button.y < positionsuperman.y+superman->h )
	{
		affich=1;
         
	}
else
	affich=0;

	}
	break;
            }
        }
       
       
        if (coul == 1)
        {
            //SDL_BlitSurface(img, NULL, screen, &posScreen);
            SDL_BlitSurface(vert, NULL, screen, &posG);
        }

        if (coul == 2)
        {
            //SDL_BlitSurface(img, NULL, screen, &posScreen);
            SDL_BlitSurface(violet, NULL, screen, &posP);
        }

if (affich==1)
{
SDL_BlitSurface(texte, NULL, screen, &postext);
         SDL_Flip(screen);
}
       
        SDL_Flip(screen);

    }
    // free loaded bitmap
    SDL_FreeSurface(img);
    SDL_FreeSurface(vert);
    SDL_FreeSurface(violet);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();

    return 0;

}

