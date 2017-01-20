#pragma once
#include "Sound.h"
#include <vector>
namespace loft { namespace audio {

	class SoundManager
	{
	private:
		friend class Sound;
		static ISoundEngine* m_Engine;
		static std::vector<Sound*> m_Sounds;
	public:
		static void init();
		static void add(Sound* sound);
		static Sound* get(const std::string& name);
		//static Sound* get(const std::string& name, )
		static void clean();
		
	};


} }
