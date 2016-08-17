#include "shared.h"

int main(int argc, char **argv)
{
	spatium * universe;
	vector<body> coetus;
	
	universe = new spatium(1e1, 1e-2);
	
	initialize(coetus, universe);	

	universe->set_globi(coetus);

	universe->run(argc, argv);

	return 0;
}

void initialize(vector<body>& cavea, spatium * u)
{
	body * thing;
	audax<double> * location;
	audax<double> * vel;
		
	double m;	
	double density;
	
	density = 50;
	u->set_sf(3e0);	
	u->set_tf(1e2);	
	
	m = 100.0;	
	thing    = new body();
	location = new audax<double>();
	vel      = new audax<double>();		
	(*location)[0] = -1;
	(*location)[1] = 5;
	(*location)[2] = 0;
	(*vel)[0]      = 0;						
	(*vel)[1]      = 0;						
	(*vel)[2]      = 0;						
	thing->setpos(*location);				
	thing->setvel(*vel);
	thing->setmass(m);
	thing->setdensity(density);
	cavea.push_back(*thing);				
}
