#include "shared.h"

body::body(color c, color s, GLfloat sh, double m, double d, audax<double>& v, audax<double>& p) : col(c), 
		   specular(s), shine(sh), mass(m), density(d), velocity(v), position(p), colliding(0)
{
	
};

body::body()
{	
	col        = color((GLfloat)0.0,(GLfloat)0.0,(GLfloat)1.0);
	specular   = color ((GLfloat)1.0, (GLfloat)1.0, (GLfloat)1.0);
	shine      = 128;
	mass       = 1000; //kg
	density    = 25000; //kg/m3	 
	
	position = audax<double>();
	velocity = audax<double>();
	
	colliding = 0;
}

body::~body()
{	
}

double body::getradius()
{
    double exp = 1.0 / 3.0;
	
	return pow((3.0 * mass) / (4.0 * M_PI * density), exp);
}

color body::getcol()
{
	return col;
}

color body::getspec()
{
	return specular;
}

GLfloat body::getshine()
{
	return shine;
}

audax <double> body::getpos()
{		
	return position;
}

double body::getmass()
{
	return mass;
}

audax <double> body::getvel()
{	
	return velocity;
}

void body::setvel(audax <double> v)
{
	velocity = v;
}

void body::setpos(audax <double> p)
{
	position = p;
}

void body::setmass(double m)
{
	mass = m;
}

void body::setdensity(double d)
{
	density = d;
}

bool body::touching(body &b)
{
	if ( (position - b.getpos()).magnitude() <= ( this->getradius() + b.getradius() ) )
		return true;
	else
		return false;
}

bool body::buffer_zone(body &b)
{
	if ((position - b.getpos()).magnitude() <= 5 * (this->getradius() + b.getradius()))
		return true;
	else
		return false;
}

bool body::is_moving_towards(body &b)
{	
	audax<double> relvel = this->getvel() - b.getvel();
	audax<double> relpos = this->getpos() - b.getpos();
	
	if (relvel.dot_product(relpos) > 0) 
	{
		return true;
	}
	else
	{
		return false;
	}
}
	
	
