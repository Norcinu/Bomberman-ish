#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <string>
#include <vector>

//#include <fmod.hpp>

class SoundManager
{
public:
	SoundManager(void);
	~SoundManager(void);

	bool Initialise();
	bool AddSound(const std::string& filename, int * id, bool is_stream = false);
	void PlaySound(const int id);
	void StreamSound(const int id);
	void RemoveSound(const int id);
	void PauseSound(const int id);
	void PauseAll();
	void SetGlobalVolume();

	enum SoundState { PLAYING=0, STOPPED, LOOPED, PAUSED };

private:
	struct sound_t
	{
		//FMOD::Sound * data;
		unsigned int state_flags;
	};

private:
	std::vector<sound_t*> sounds;
//	FMOD::System * system;
//	FMOD_RESULT result;
	unsigned int version;
	int numdrivers;
//	FMOD_SPEAKERMODE speakermode;
//	FMOD_CAPS caps;
	char name[256];

	typedef std::vector<sound_t*>::iterator sound_itor;
};

//void ERRCHECK(FMOD_RESULT result_);

#endif
