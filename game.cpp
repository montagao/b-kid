#include "game.h"
#include "texture.h"
#include "player.h"
#include "sound.h"
#include "sprite.h"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Texture gPlayerTexture;
Texture gBGTexture; 
GSound gHurtSound;
Sprite *warren = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO |  SDL_INIT_AUDIO) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Beat Kid Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_mixer 
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}

		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if( !gPlayerTexture.loadFromFile( "dot.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	
	//Load palyer sprite
	warren = new Sprite();
	if( !warren->loadFromFile(0,0, "bkid_sprite.png", 35,120,4 ) )
	{
		printf( "Failed to load dot sprite!\n" );
		success = false;
	}

	//Load background texture
	if( !gBGTexture.loadFromFile( "bg.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	if ( !gHurtSound.loadFromFile( "beat_hurt.wav" ) ) 
	{
		printf( "Couldn't load hurt sound\n");
		success = false;
	}

	

	return success;
}

void close()
{
	//Free loaded images
	gPlayerTexture.free();
	gBGTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Player dot;
			dot.loadSprite(warren);
			
			int frames = 0;
			bool playerIdle = true;



			//BG color array
			Uint8 rgb[3] = {0,0,0};
			bool descendingColor = false;


			//The background scrolling offset
			int scrollingOffset = 0;

			//While application is running
			while( !quit )
			{
				playerIdle = true;
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT ) {
						quit = true; 
					} else if ( e.type == SDL_KEYDOWN ){
						if (e.key.keysym.sym == SDLK_b){
							gHurtSound.play();
						}
						playerIdle = false;
					}



					//Handle input for the dot
					dot.handleEvent( e );
				}



				//Rainbow colored bg
				if (rgb[0] == 0xFF && rgb[1] == 0xFF && rgb[2] == 0xFF){
					descendingColor = true;
				} else if (rgb[0] == 50 && rgb[1] == 50 && rgb[2] == 50) {
					descendingColor = false;
				}

				if (descendingColor){
					for (int i = 0; i < 3; i++ ){
						if (rgb[i] != 50){
							rgb[i] -= 5;
							break;
						}
					}
				} else {
					for (int i = 0; i < 3; i++){
						if (rgb[i] != 255){
							rgb[i] += 5;
							break;
						}
					}
				}


					

				//Move the dot
				dot.move();

				//Scroll background
				--scrollingOffset;
				if( scrollingOffset < -gBGTexture.getWidth() )
				{
					scrollingOffset = 0;
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render background
				gBGTexture.setColor(rgb[0],rgb[1],rgb[2]);
				gBGTexture.render( scrollingOffset, 0 );
				gBGTexture.render( scrollingOffset + gBGTexture.getWidth(), 0 );

				//Render objects
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				

				// animate warren.finish cycle
				if (!playerIdle || dot.getSprite()->currentFrame != 0){
					if (frames % 6 == 0 ){
						dot.updateFrame();
						// prevent int overflow ^^
						frames = 0;
					}
					frames++;
				}
				dot.render();
				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

