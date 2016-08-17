#include "shared.h"

color::color(GLfloat r, GLfloat g, GLfloat b)
{	
	rgb = audax<GLfloat>(r,g,b);		
};

color::color()
{
	rgb = audax<GLfloat>(0,0,0);	
};
		
color::~color()
{	
};

GLfloat color::getred()
{
	return (rgb.getvec())[0];
}

GLfloat color::getgreen()
{
	return rgb.getvec()[1];
}

GLfloat color::getblue()
{
	return rgb.getvec()[2];
}
