#include "sound.h"

GSound::GSound()
{
	mixChunk == NULL;;

}

GSound::~GSound()
{
	// free mix chunk
	free();
}


void GSound::free()
{
	// Free sound effect
	Mix_FreeChunk( mixChunk );
	mixChunk = NULL;
}

// returns true if loaded succesfully, false otherwise
bool GSound::loadFromFile (std::string path)
{
	// free mix if already given
	free();
	mixChunk = Mix_LoadWAV("beat_hurt.wav");
	if ( mixChunk != NULL) {
		return true;
	} else {
		return false;
	}


}

void  GSound::play()
{
	// to-do add cooldown timer to when the clip can be played.
	if (mixChunk != NULL ){
		Mix_PlayChannel( -1, mixChunk,0);
	}
}
