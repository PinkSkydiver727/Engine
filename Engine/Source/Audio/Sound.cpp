#include "Sound.h"
#include "SoundManager.h"
namespace loft { namespace audio {


	Sound::Sound(const std::string& name, const std::string& filename)
		: m_Name(name), m_Filepath(filename)
	{
		m_Sound = SoundManager::m_Engine->addSoundSourceFromFile("test.wav");
	}
	Sound::~Sound()
	{
		SoundManager::m_Engine->removeSoundSource(m_Sound);
	}


	void Sound::play()
	{
		SoundManager::m_Engine->play2D(m_Sound);

	}
	void Sound::loop()
	{

	}
	void Sound::pause()
	{

	}
	void Sound::stop()
	{

	}

} }