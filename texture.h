#ifndef TEXTURE_H 
#define TEXTURE_H

#include <cstdint>
#include <SDL2/SDL.h>


class Texture
{
	public:
		//Initalizes variables;
		Texture();

		//Deallocates memory
		~Texture();

		//Loads image at specified path
		bool loadFromFile( std::string path );

		#ifdef _SDL_TTF_H
		//Creates imager from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		// Deallocates texture
		void free();

		// Set color modulation
		void setColor ( Uint8 red, Uint8 green, Uint8 blue);

		// set blending
		void setBlendMode (SDL_BlendMode blending);

		// set alpha modulation
		void setAlpha( Uint8 alpha);
		
		// renders texture ata   given point
		void render (int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		// Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		// THe actual hardware texture;
		SDL_Texture* mTexture;

		// Image dimensions
		int mWidth;
		int mHeight;
};



#endif
