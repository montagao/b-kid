#include "sprite.h"

Sprite::Sprite(){
	// default constructor
	currentFrame = 0;

}

Sprite::~Sprite(){
	free();
}


bool Sprite::loadFromFile(int x, int y, std::string path, int width, int height, int frames){
	if (! spriteTexture.loadFromFile( path)){
		printf("Unable to load spriteSheet!\n");
		return false;
	}
	
	this->frames = frames;

	for (int i = 0; i < frames; i++ ){
		SDL_Rect a = { x + i*width, y, width, height };
		clips.push_back(a);
	}
	return true;
}


void Sprite::free() {
	spriteTexture.free();
	clips.clear();
}

void Sprite::updateFrame() {
	currentFrame++;
}

bool Sprite::renderCurrentFrame(int x, int y) {

	if (currentFrame == getFrames() )
		currentFrame = 0;

	spriteTexture.render(x,y, &clips[currentFrame]);
}




