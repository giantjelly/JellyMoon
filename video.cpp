/*#include "lib.h"
#include "video.h"

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

void videoRenderSprite(GLuint texture, double x, double y, double width, double height) {

	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);

	glTexCoord2d(0, 0);
	glVertex3f(x, y, 0);

	glTexCoord2d(1, 0);
	glVertex3f(x + width, y, 0);

	glTexCoord2d(1, 1);
	glVertex3f(x + width, y + height, 0);

	glTexCoord2d(0, 1);
	glVertex3f(x, y + height, 0);

	glEnd();
}

GLuint videoLoadTexture(string file) {

	SDL_Surface *surface = IMG_Load(file.c_str());
	if (surface == nullptr) {
		cout << "Bitmap load error: " << SDL_GetError() << endl;
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
}*/