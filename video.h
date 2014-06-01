#include <glew.h>
#include <string>

void videoEnableTextures(bool enable);
void videoClear();
void videoPush();
void videoPop();
void videoTranslate(double x, double y, double z);
void videoRotate(double angle);
void videoColor(double r, double g, double b, double a);
void videoRenderQuad(double left, double top, double right, double bottom);
void videoRenderSprite(GLuint texture, double offsetX, double offsetY, double offsetWidth, double offsetHeight, double x, double y, double scale);
void videoRenderCircle(double x, double y, double radius, double detailScale);
GLuint videoLoadTexture(std::string file);

void videoLoadIdentity();
void videoRotate(double x, double y, double angle);