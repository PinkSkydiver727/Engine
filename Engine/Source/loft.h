#pragma once
#include "Graphics\window.h"
#include "Graphics\Layers\Layer.h"
#include "Graphics\BatchRenderer2d.h"
#include "Graphics\Sprite.h"

#include "Math\math.h"

#include "Utilities\Timer.h"
namespace loft {
	class Loft
	{
	private:
		graphics::Window* m_Window;
		Timer* m_Timer;
		int m_FramesPerSecond, m_UpdatesPerSecond;
	protected:
		Loft() 
			:m_FramesPerSecond(0), m_UpdatesPerSecond(0)
		{

		}
		virtual ~Loft()
		{
			delete m_Window;
			delete m_Timer;
		}

		graphics::Window* createWindow(const char* name, int width, int height)
		{
			m_Window = new graphics::Window(name, width, height);
			return m_Window;
		}
	public:
		void start()
		{
			init();
			run();
		}
	protected:
		//runs when 
		virtual void init() = 0;
		// once a frame
		virtual void update() {};
		// once a second
		virtual void tick() {} ;
		// runs as fast as it can
		virtual void render() = 0;

		const unsigned int getFPS() { return m_FramesPerSecond; }
		const unsigned int getUPS() { return m_UpdatesPerSecond; }

	private:
		void run()
		{
			float timer = 0;
			float updateTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;
			m_Timer = new Timer();
			unsigned int frames = 0;
			unsigned int updates = 0;
			while (!m_Window->closed())
			{
				m_Window->clear();
				if (m_Timer->elapsed() - updateTimer > updateTick)
				{
					updates++;
					update();
					updateTimer += updateTick;
				}
				render();
				
				m_Window->update();
				frames++;
				if (m_Timer->elapsed() - timer > 1.0f)
				{
					std::cout << "FPS: " << frames << std::endl;
					std::cout << "UPS:" << updates << std::endl;
					tick();
					timer += 1.0f;
					m_FramesPerSecond = frames;
					m_UpdatesPerSecond = updates;
					//printf("%d fps \n", frames);
					frames = 0;
					updates = 0;
				}
			}
		}

	};

}