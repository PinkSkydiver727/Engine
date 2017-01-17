
#include "Source/Graphics/window.h"
#include "Source/Graphics/Shader.h"
#include "Source/Math/math.h"
#include "Source\Graphics\Buffers\VertexArray.h"
#include "Source\Graphics\Buffers\IndexBuffer.h"
#include "Source\Graphics\Buffers\Buffer.h"
#include "Source\Graphics\SimpleRenderer2D.h"
#include "Source\Graphics\BatchRenderer2D.h"
#include "Source\Graphics\Renderer2D.h"
#include "Source\Graphics\Layers\TileLayer.h"
#include "Source\Graphics\Layers\Group.h"

#include "Source\Graphics\Sprite.h"
#include "Source\Utilities\Timer.h"
#include <time.h>
#include <FreeImage.h>

#define TEST_50K_SPRITES 0

#if 1
int main() //I am a joke
{
	using namespace loft;
	using namespace graphics;
	using namespace math;

	Window window("Loftie!", 800, 600);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	std::cout << glGetString(GL_VERSION) << std::endl;


	Matrix4 ortho = Matrix4::orthographic(0.0, 16.0, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader* s = new Shader("Source/Shaders/basic.vert", "Source/Shaders/basic.frag");
	Shader* s2 = new Shader("Source/Shaders/basic.vert", "Source/Shaders/basic.frag");
	Shader& shader = *s;
	Shader& shader2 = *s2;
	
	shader.enable();
	shader2.enable();

	shader.setUniform2f("light_pos", Vector2(4.0f, 1.5f));
	shader2.setUniform2f("light_pos", Vector2(4.0f, 1.5f));


	TileLayer layer2(&shader);
	TileLayer layer(&shader2);
#if TEST_50K_SPRITES
	for (float y = -9.0f; y < 9.0f; y += 0.2)
	{
		for (float x = -16.0f; x < 16.0f; x += 0.2)
		{
			layer.add(new Sprite(x, y, 4.0f, 4.0f, math::Vector4((rand() % 1000 / 1000.0f), 0, 1, 1)));
		}
	}
#else
	Group* group = new Group(math::Matrix4::translation(math::Vector3(5.0f, 1.0f, 0.0f)));
	group->add(new Sprite(0, 0, 6.0f, 4.0f, math::Vector4((rand() % 1000 / 1000.0f), 0, 1, 1)));
	group->add(new Sprite(0.5, 0.5, 5.0f, 2.0f, math::Vector4((rand() % 1000 / 1000.0f), 0, 0, 1)));

		
	layer.add(group);
	
	//layer2.add(new Sprite(-2.0f, -2.0f, 4.0f, 4.0f, Vector4(1.0f, 1.0f, 1.0f, 1.0f)));



#endif
	Timer timer, time;
	float t = 0;
	unsigned int frames = 0;
	while (!window.closed())
	{
		timer.reset();
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.enable();
		shader.setUniform2f("light_pos", Vector2((float)(x * 32.0f / 800.0f - 16.0f), (float)(9.0f - y * 18.0f / 600.0f)));
		shader2.enable();
		shader2.setUniform2f("light_pos", Vector2((float)(x * 32.0f / 800.0f - 16.0f), (float)(9.0f - y * 18.0f / 600.0f)));

		layer.render();

		//layer2.render();
		window.update();
		frames++;
		if (time.elapsed() - t > 1.0f)
		{
			t += 1.0f;
			printf("%d fps \n", frames);
			frames = 0;
		}
		//printf("%f ms \n", timer.elapsed()*1000);

	}
	
	return 0;
	
}
#else

int main()
{
	const char* filename = "test.png";
	// image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	GLuint gl_texID;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		return false;

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if (!dib)
		return false;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	unsigned int bitsPerPixel = FreeImage_GetBPP(dib);

	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
		return false;

	for (int i = 0; i < width * height * 3; i += 3)
	{
		int hex = bits[i] << 16 | bits[i + 1] << 8 | bits[i + 2];
		printf("%x\n", hex);
	}
	system("PAUSE");

}


#endif