#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "Module.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;

class Audio : public Module
{
public:

	Audio();

	// Destructor
	virtual ~Audio();

	// Called before render is available
	bool awake(pugi::xml_node&);

	// Called before quitting
	bool cleanUp();

	// Play a music file
	bool playMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int loadFx(const char* path);

	// Play a previously loaded WAV
	bool playFx(unsigned int fx, int repeat = 0);

	// Increase volume
	void volumeUp();
	void volumeDown();

	// Load / save modules
	bool load(pugi::xml_node&);
	bool save(pugi::xml_node&) const;
	 
private:

	_Mix_Music*			music;
	DList<Mix_Chunk*>	fx;
};

#endif // __AUDIO_H__
