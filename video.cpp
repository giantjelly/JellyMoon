#include "video.h"

#include <iostream>
#include <SDL_image.h>

void videoEnableTextures(bool enable) {

	if (enable) glEnable(GL_TEXTURE_2D);
	else glDisable(GL_TEXTURE_2D);
}

void videoClear() {

	glClear(GL_COLOR_BUFFER_BIT);
}

void videoPush() {

	glPushMatrix();
}

void videoPop() {

	glPopMatrix();
}

void videoTranslate(double x, double y, double z) {

	glTranslated(x, y, z);
}

void videoRotate(double angle) {

	glRotated(angle, 0.0, 0.0, 1.0);
}

void videoColor(double r, double g, double b, double a) {

	glColor4f(r, g, b, a);
}

void videoRenderQuad(double x, double y, double width, double height) {

	glBegin(GL_QUADS);

	glVertex3d(x, y, 0);
	glVertex3d(x + width, y, 0);
	glVertex3d(x + width, y + height, 0);
	glVertex3d(x, y + height, 0);

	glEnd();
}

void videoRenderSprite(GLuint texture, double offsetX, double offsetY, double offsetWidth, double offsetHeight, double x, double y, double scale) {

	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);

	int tw;
	int th;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &tw);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &th);

	double xStart = offsetX / tw;
	double xEnd = (offsetX+offsetWidth) / tw;
	double yStart = offsetY / th;
	double yEnd = (offsetY + offsetHeight) / th;
	double width = offsetWidth*scale;
	double height = offsetHeight*scale;

	glBegin(GL_QUADS);

	glTexCoord2d(xStart, yStart);
	glVertex3f(x, y, 0);

	glTexCoord2d(xEnd, yStart);
	glVertex3f(x + width, y, 0);

	glTexCoord2d(xEnd, yEnd);
	glVertex3f(x + width, y + height, 0);

	glTexCoord2d(xStart, yEnd);
	glVertex3f(x, y + height, 0);

	glEnd();
}

void videoRenderCircle(double x, double y, double radius, double detailScale) {

	int detail = 50*detailScale;

	glBegin(GL_TRIANGLE_FAN);

	for (int i = 0; i < detail; i++) {

		double rad = (((double)i/(double)detail)*360)*(3.14159 / 180.0);
		glVertex3d( x+(cos(rad)*radius), y+(sin(rad)*radius), 0 );
	}

	glEnd();
}

GLuint videoLoadTexture(std::string file) {

	SDL_Surface *surface = IMG_Load(file.c_str());
	if (surface == nullptr) {
		std::cout << "Bitmap load error: " << SDL_GetError() << std::endl;
		return NULL;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int mode = GL_RGB;
	if (surface->format->BytesPerPixel == 4) mode = GL_RGBA;

	glTexImage2D(
		GL_TEXTURE_2D, 0, mode,
		surface->w, surface->h,
		0,
		mode, GL_UNSIGNED_BYTE, surface->pixels
	);

	SDL_FreeSurface(surface);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return texture;
}

void videoLoadIdentity() {

	glLoadIdentity();
}

void videoRotate(double x, double y, double angle) {

	videoTranslate(x, y, 0);
	videoRotate(angle);
	videoTranslate(-x, -y, 0);
}