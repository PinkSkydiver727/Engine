#include "../Source/loft.h"
#include "../TileLayer.h"

using namespace loft;
using namespace graphics;
class Game : public Loft
{
private:
	Window* window;
	Layer* layer;

	Sprite* sprite;
public:
	Game()
	{

	}

	~Game()
	{
		delete layer;
	}

	void init() override
	{
		window = createWindow("Test Game", 960, 540);
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		
		//Shader* s = new Shader("Source/Shaders/basic.vert", "Source/Shaders/basic.frag");
		//Shader& shader = *s;
		//shader.enable();

		layer = new Layer(new BatchRenderer2D(), new Shader("Source/Shaders/basic.vert", "Source/Shaders/basic.frag"), math::Matrix4::orthographic(-16.0f, 16.0f, -9.0, 9.0f, -1.0f, 1.0f));
		sprite = new Sprite(0.0f, 0.0f, 5, 5, new Texture("ship.png"));
		layer->add(sprite);
	}

	void update() override
	{
		float speed = 1.5f;
		if (window->isKeyPressed(GLFW_KEY_UP))
		{
			sprite->position.y += speed;
		}
		else if (window->isKeyPressed(GLFW_KEY_DOWN))
		{
			sprite->position.y -= speed;
		}
		if (window->isKeyPressed(GLFW_KEY_LEFT))
		{
			sprite->position.x -= speed;
		}
		else if (window->isKeyPressed(GLFW_KEY_RIGHT))
		{
			sprite->position.x += speed;
		}
	}

	void render() override
	{
		layer->render();
	}

};

int main()
{
	Game game;
	game.start();
	return 0;
}