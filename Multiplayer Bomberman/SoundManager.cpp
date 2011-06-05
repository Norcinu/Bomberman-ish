#include "SoundManager.h"

#pragma warning(disable:4018)

//---------------------
void ERRCHECK(FMOD_RESULT result_)
{
	if (result_ != FMOD_OK)
		printf("FMOD error! (%d) %s\n", result_);
}
//--------------------

SoundManager::SoundManager(void)
{
}


SoundManager::~SoundManager(void)
{
	if (!sounds.empty())
	{
		for (sound_itor it=sounds.begin(); it != sounds.end(); it++)
			delete (*it);

		sounds.clear();
	}
}

bool SoundManager::Initialise()
{
	result = FMOD::System_Create(&system);
	if (result != FMOD_OK)
	{
		printf ("Failed to create sound system.\n");
		return false;
	}

	result = system->getVersion(&version);
	ERRCHECK(result);
	
	if (version < FMOD_VERSION)
	{
		printf("Error! You are using an old version of FMOD %08x. You need version %08x",
			version, FMOD_VERSION);
		return false;
	}

	result = system->getNumDrivers(&numdrivers);
	ERRCHECK(result);

	if (numdrivers == 0)
	{
		result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		ERRCHECK(result);
	}
	else
	{
		result = system->getDriverCaps(0, &caps, 0, 0, &speakermode);
		ERRCHECK(result);

		if (caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			result = system->setDSPBufferSize(1024, 10);
			ERRCHECK(result);
		}

		result = system->getDriverInfo(0, name, 256, 0);
		ERRCHECK(result);

		if (strstr(name, "SigmaTel"))
		{
			result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, 
				FMOD_DSP_RESAMPLER_LINEAR);
			ERRCHECK(result);
		}
	}

	result = system->init(100, FMOD_INIT_NORMAL, 0);
	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		ERRCHECK(result);

		result = system->init(100, FMOD_INIT_NORMAL, 0);
		ERRCHECK(result);
	}
	return true;
}

bool SoundManager::AddSound(const std::string& filename, int * id, bool is_stream)
{
	sound_t *s = new sound_t;
	
	result = !is_stream ? system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &s->data) :
		system->createStream(filename.c_str(), FMOD_DEFAULT, 0, &s->data);
	
	ERRCHECK (result);

	if (result != FMOD_OK) 
	{
		delete s;
		return false;
	}

	s->state_flags = STOPPED;
	sounds.push_back(s);
	*id = sounds.size() - 1;
	
	//result = system->createStream(createSound(filename.c_str(), FMOD_DEFAULT, 0, &s->data);
	ERRCHECK(result);

	if (result != FMOD_OK) 
	{
		delete s;
		return false;
	}

	s->state_flags = STOPPED;
	sounds.push_back(s);
	*id = sounds.size() - 1;
	

	return true;
}

void SoundManager::PlaySound(const int id)
{
	if (id >= 0 && id < sounds.size()-1) 
	{
		bool is_looping = sounds[id]->state_flags & LOOPED ? true : false;
		FMOD::Channel *channel;
		result = system->playSound(FMOD_CHANNEL_FREE, sounds[id]->data, is_looping, &channel);
		ERRCHECK(result);
	}
	else
	{
		printf ("Error playing sound with id : %d", id);
	}
}

void SoundManager::StreamSound(const int id)
{
	if (id >= 0 && id < sounds.size()-1)
	{
		bool is_looping = sounds[id]->state_flags & LOOPED ? true : false;
		FMOD::Channel *channel;
		//result = system->playSound
	}
}

void SoundManager::RemoveSound(const int id)
{
	//delete sounds.at(id);
}

void SoundManager::PauseSound(const int id)
{

}