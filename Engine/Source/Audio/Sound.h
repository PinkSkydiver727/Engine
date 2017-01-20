#pragma once
#include <string>
#include <irrKlang.h>

#pragma comment(lib, "irrKlang.lib")

namespace loft { namespace audio {
	using namespace irrklang;
	class Sound
	{
	private:
		std::string m_Name;
		std::string m_Filepath;
		ISoundSource* m_Sound;
	public:
		Sound(const std::string& name, const std::string& filename);
		~Sound();
		void play();
		void loop();
		void pause();
		void stop();

		inline const std::string& getName() const { return m_Name; };
		inline const std::string& getFilePath() const { return m_Filepath; };
	};


} }