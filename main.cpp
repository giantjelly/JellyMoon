#include "engine.h"

int main(int argc, char **argv) {

	/*glewInit();

	double verticies[] = {
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0
	};

	GLuint buffer = 0;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);*/
	
	Engine *engine = new Engine();
	engine->run();
	
	delete engine;
	return 1;
}