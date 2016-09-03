#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>
#include <string>

class GSound {
	public:
		GSound();

		// deallocates memory used
		~GSound();

		// deallocates memory used by Mix_Chunk;
		void free();

		// loads a sound file 
		bool loadFromFile( std::string path );

		// Plays the entire short sound effect
		void play();

	private:
		// actual sdl data objects
		Mix_Chunk * mixChunk;
};



#endif
