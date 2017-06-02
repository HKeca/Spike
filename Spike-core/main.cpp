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

#include <time.h>

int main()
{
	//ewwww
	using namespace spike;
	using namespace graphics;
	using namespace maths;


	Window window("Spike Engine -- Test 2D", 960, 540);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);


	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);


	std::vector<Renderable2D*> sprites;
	srand(time(NULL));


	Sprite sprite(5 + 4, 5 + 3, 4, 4, maths::vec4(1, 0, 1, 1));
	Sprite sprite2(7 + 4, 1 + 3, 2, 3, maths::vec4(0.2f, 0, 1, 1));
	BatchRenderer2D renderer;

	for (float y = 0; y < 9.0f; y += 1)
	{
		for (float x = 0; x < 16.0f; x += 1)
		{
			sprites.push_back(new Sprite(x, y, 2.0f, 2.0f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}

	shader.setUniform2f("light_pos", vec2(8.0f, 4.5f));
	shader.setUniform4f("custom_color", vec4(0.2f, 0.3f, 0.8f, 1.0f));
	

	Timer time;
	float timer = 0;
	unsigned int frames = 0;

	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(y * 9.0f / 540.0f)));
		renderer.begin();

		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.submit(sprites[i]);
		}
		
		renderer.end();
		renderer.flush();
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