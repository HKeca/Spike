#include "src\graphics\window.h"
#include "src\maths\maths.h"
#include "src\graphics\shader.h"

#include "src\graphics\buffers\buffer.h"
#include "src\graphics\buffers\indexbuffer.h"
#include "src\graphics\buffers\vertexarray.h"

#include "src\graphics\renderable2d.h"
#include "src\graphics\simple2drenderer.h"

#include "src\graphics\2dbatchrenderer.h"
#include "src\graphics\static_sprite.h"
#include "src\graphics\sprite.h"
#include "src\utils\timer.h"

#include "src\graphics\layers\tileLayer.h"

#include <time.h>

#define TEST_50k_SPRITES 0

int main()
{
	using namespace spike;
	using namespace graphics;
	using namespace maths;


	Window window("Spike Engine -- Test 2D", 1280, 720);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);


	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader* s2 = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	Shader& shader2 = *s2;

	shader.enable();
	shader2.enable();

	shader.setUniform2f("light_pos", vec2(8.0f, 4.5f));
	shader2.setUniform2f("light_pos", vec2(8.0f, 4.5f));

	TileLayer layer(&shader);
#if TEST_50k_SPRITES
	for (float y = -9.0f; y < 9.0f; y += 0.1)
	{
		for (float x = -16.0f; x < 16.0f; x += 0.1)
		{
			layer.add(new Sprite(x, y, 0.09f, 0.09f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}
#else

	layer.add(new Sprite(-15.0f, -5.0, 6, 3, maths::vec4(1, 1, 1, 1)));

#endif

	TileLayer layer2(&shader2);
	layer2.add(new Sprite(-2, -2, 4, 4, maths::vec4(0, 1, 0, 1)));


	Timer time;
	float timer = 0;
	unsigned int frames = 0;

	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
	
		shader.enable();
		shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));
		shader2.enable();
		shader2.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));

		layer.render();
		//layer2.render();

		window.update();
		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d FPS\n", frames);
			frames = 0;
		}

	}

	return 0;
}