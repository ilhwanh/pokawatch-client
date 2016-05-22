//
// CNH 2016.05.20
// sprite class
//

#include "shader.h"
#include "sprite.h"
#include "lodepng.h"

void Sprite::load(const char* fn) {
	std::vector<unsigned char> png;
	std::vector<unsigned char> image;
	unsigned error;

	error = lodepng::load_file(png, fn);
	if (error) {
		std::cout << "Error " << error << " loading image " << fn << std::endl;
		return;
	}

	error = lodepng::decode(image, uw, uh, png);
	if (error) {
		std::cout << "Error " << error << " loading image " << fn << std::endl;
		return;
	}

	glGenTextures(1, &buf);
	glBindTexture(GL_TEXTURE_2D, buf);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, uw, uh, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	std::cout << "Sprite: " << fn << " is successfully loaded" << std::endl;

	w = (float)uw;
	h = (float)uh;
	ofx = w * 0.5;
	ofy = h * 0.5;
}

void Sprite::setOffset(float ofx, float ofy) {
	this->ofx = ofx;
	this->ofy = ofy;
}