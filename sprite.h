#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <vector>
#include "texture.h"

class Sprite {
	public:
		Sprite();

		~Sprite();

		// loads specified number of frames from starting x y position of file
		// and creates desired number of clip
		bool loadFromFile(int x, int y, std::string path, int width, int height, int frames);

		void free();

		int getFrames() { return frames; }

		int getWidth() { return width; }

		int getHeight() { return height; }

		int frames;

		int currentFrame;

		Texture spriteTexture;

		// Defines SDL_Rects for frames
		std::vector<SDL_Rect> clips;

		// just increments the frame count when called
		void updateFrame();
		


		// renders current frame at x,y in the renderer
		bool renderCurrentFrame( int x, int y);

	private:
		int width;

		int height;





};

#endif 
