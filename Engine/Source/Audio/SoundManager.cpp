#include "SoundManager.h"

namespace loft { namespace audio {

	ISoundEngine* SoundManager::m_Engine = nullptr;
	std::vector<Sound*> SoundManager::m_Sounds;
	void SoundManager::init()
	{
		m_Engine = createIrrKlangDevice();
		if (!m_Engine)
		{
			printf("Could not startup sound engine\n");
			//return; // error starting up the engine
		}
	}

	void SoundManager::add(Sound* sound)
	{
		m_Sounds.push_back(sound);
	}

	Sound* SoundManager::get(const std::string& name)
	{
		for (Sound* s : m_Sounds)
		{
			if (s->getName() == name)
			{
				return s;
			}
		}
	}

	void SoundManager::clean()
	{
		for (int i = 0; i < m_Sounds.size(); i++)
		{
			delete m_Sounds[i];
		}
	}

} }