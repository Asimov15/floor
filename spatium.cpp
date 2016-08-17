#include "shared.h"

spatium* spatium_global::current_spatium;

spatium::spatium(audax<double>& av, audax<double>& ap, vector<double>& cp, vector<double>& la, 
				 vector<body>& g, double s, double t) :
				 angular_velocity(av), angular_position(ap), campos(cp), lookat(la), globi(g), 
				 space_factor(s), time_factor(t), turn(0)
{	
};

spatium::spatium(double s, double t)
{
	int i;	
	angular_velocity = audax<double>();
	angular_position = audax<double>();
	for (i = 0; i < 3; i++)
	{		
		lookat.push_back(0);
		campos.push_back(0);
	}
	
	campos[2] = 10;
	turn = 0;	
	spatium();
	space_factor = s;
	time_factor  = t;	
}

spatium::spatium()
{
	int i;
	
	angular_velocity = audax<double>();
	angular_position = audax<double>();
	for (i = 0; i < 3; i++)
	{		
		lookat.push_back(0);
		campos.push_back(0);
	}
	
	campos[2] = 10;
	turn = 0;	
	space_factor = 1e8;
	time_factor = 1e-3;
}

spatium::~spatium()
{}

void spatium::set_globi(vector<body>&g)
{
	globi = g;
}

void spatium::display()
{
	unsigned int i,j;
	GLfloat ref[1];	
	glEnable(GL_BLEND); // Enable the OpenGL Blending functionality  
	 // Set the blend mode to blend our current RGBA with what is already in the buffer  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	glClearColor(0.0, 0.0, 0.0, 1.0); 						//clear the screen to black	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 	//clear the color buffer and the depth buffer	
	
	glLoadIdentity();
	GLfloat diffuse[4];
	GLfloat highlight[4];	
	
	//camera position, x,y,z, looking at x,y,z, Up Positions of the camera    	    	    
	gluLookAt(campos.at(0), campos.at(1), campos.at(2), 
	          lookat.at(0), lookat.at(1), lookat.at(2), 0.0, 1.0, 0.0); 
	          	
	angular_position += angular_velocity;

	glRotatef(angular_position[0], 1.0f, 0.0f, 0.0f);
	glRotatef(angular_position[1], 0.0f, 1.0f, 0.0f);
	glRotatef(angular_position[2], 0.0f, 0.0f, 1.0f);
	
	// render each body to the screen
	for (i = 0; i < globi.size(); i++)
	{		
		for (j = 0; j < 3; j++)
		{
			diffuse[j]   = globi[i].getcol().rgb.getvec()[j];
			highlight[j] = globi[i].getspec().rgb.getvec()[j];
		}
		
		diffuse[3] = 0.5; 
		highlight[3] = 1.0;
		
		ref[0] = globi[i].getshine();
		
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, highlight);
		
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, ref);
		
		glTranslatef(globi[i].getpos()[0]/space_factor, globi[i].getpos()[1]/space_factor, 
		             globi[i].getpos()[2]/space_factor);
		
		glutSolidSphere(globi[i].getradius()/space_factor, 37, 37);
	
		glTranslatef(-1 * globi[i].getpos()[0]/space_factor, -1 * globi[i].getpos()[1]/space_factor, 
		             -1 * globi[i].getpos()[2]/space_factor);		
	}
	if (bounding_box)
		render_bounding_box();
		
	glRotatef(-1 * angular_position[0], 1.0f, 0.0f, 0.0f);
	glRotatef(-1 * angular_position[1], 0.0f, 1.0f, 0.0f);
	glRotatef(-1 * angular_position[2], 0.0f, 0.0f, 1.0f);
	
	glutSwapBuffers(); //swap the buffers     
}

void spatium::initglut(int argc, char **argv)
{		
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH); //set the display to Double buffer, with depth	
	glutInitWindowSize(2000, 1000); //set the window size	
	glutInitWindowPosition(0, 0); //set the position of the window	
	glutCreateWindow("Newtonian Mechanics Simulation"); //the caption of the window	
	glutDisplayFunc(spatium_global::simulate); //use the display function to draw everything	
	glutIdleFunc(spatium_global::simulate); //update any variables in display, display can be changed to anyhing, as long as you move the variables to be updated, in this case, angle++;
	glutReshapeFunc(spatium_global::reshape); //reshape the window accordingly
	glutKeyboardFunc(spatium_global::keyboard); //check the keyboard
}

void spatium::initgraphics()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	
	GLfloat whiteLight[] = { 1.0, 1.0, 1.0 }; 			//set the diffuse light to white

	glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteLight);	
}

void spatium::simulate()
{		
	unsigned int i;
	double time_inc;
	//double time;
	audax<double> down(0, -1, 0);
	time_inc = 1.0 / time_factor;
	
	//time = turn * time_inc;	
	//cout << totalke() << "," << getgpe() << "," << getgpe() + totalke() << "," << 
	//        globi[0].getvel()[1] << "," << globi[0].getpos()[1]<< "," << time << endl;
	if (bounding_box)
		box_wall();
		
	if (gravity)
		apply_gravity();		
	
	//get and set new position
	for (i = 0; i < globi.size(); i++)
	{		
		if (globi[i].colliding == 0)
		{
			//p(n+1) = p(n) + vt/2;
			globi[i].setpos( globi[i].getpos() + 
			globi[i].getvel() * time_inc - down * 9.8 * time_inc * 0.5 * time_inc);
		}
	}	        
	
	display();
	
	turn++;  // universal clock tick 
}

void spatium::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(29, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void spatium::keyboard(unsigned char key, int x, int y)
{	
	if (key == 'a')
	{
		angular_velocity[0] += 0.1;
	}

	if (key == 's')
	{
		angular_velocity[0] -= 0.1;
	}

	if (key == 'd')
	{
		angular_velocity[1] += 0.1;
	}

	if (key == 'f')
	{
		angular_velocity[1] -= 0.1;
	}
	if (key == 'g')
	{
		angular_velocity[2] += 0.1;
	}

	if (key == 'h')
	{
		angular_velocity[2] -= 0.1;
	}

	if (key == 'k')
	{		
		campos[2] += 1.0;
	}

	if (key == 'j')
	{
		campos[2] -= 1.0;
	}

	if (key == 'z')
	{
		angular_velocity.clear();
	}
	if (key == 27)
	{
		glutLeaveMainLoop();		
	}
	return;
}

int spatium::run(int argc, char **argv)
{
	spatium_global::current_spatium = this;	
	initglut(argc, argv);
	initgraphics();		
	glutMainLoop(); //call the main loop
	
	return 0;
}

void spatium::set_tf(double x)
{
	time_factor = x;
}

void spatium::set_sf(double x)
{
	space_factor = x;
}

void spatium::apply_gravity()
{
	double time_inc;
	unsigned int i;	

	audax<double> newv          = audax<double>();
	audax<double> deltav        = audax<double>();	
	audax<double> down          = audax<double>(0,-1,0);	
	
	time_inc = 1 / time_factor;		
			
	for (i = 0; i < globi.size(); i++)
	{		
		
		if (globi[i].colliding == 0)
		{
			deltav = down * 9.8 * time_inc; 												
			globi[i].setvel(globi[i].getvel() + deltav);		
		}
	}	
}

void spatium::box_wall()
{
	unsigned int i;
	audax<double> u = audax<double>();	
	audax<double> v = audax<double>(0,0,0);	
	for (i = 0; i < globi.size(); i++)		
	{		
		u = globi[i].getvel();
		if 	(
				(
					globi[i].getpos())[1] <= (boxsize / -2 + wall_thickness / 2 + globi[i].getradius()
				) 
				&& (u[1] < 0) && globi[i].colliding == 0
			)
		{			
			u[1] *= -1;
			globi[i].cvelocity = u;
			globi[i].setvel(v);
			globi[i].colliding++;
		}
		else if (globi[i].colliding == 1)
		{
			globi[i].setvel(globi[i].cvelocity);
			globi[i].colliding++;
		}
		else if (globi[i].colliding == 2)
		{
			globi[i].setvel(globi[i].cvelocity);
			globi[i].colliding = 0;
		}
	}
}

double spatium::totalke()
{
	unsigned int i;
	double ke;
	ke = 0;
	for (i = 0; i < globi.size(); i++)
	{
		ke += 0.5 * globi[i].getmass() * pow( (globi[i].getvel()).magnitude(), 2);
	}
	return ke;
}

void spatium::render_bounding_box()
{
	unsigned int i,j, bricks;
	GLfloat wdiffuse[4];
	GLfloat whighlight[4];
	GLfloat wref[1];	
	
	wdiffuse[0] = 0.0;
	wdiffuse[1] = 1.0;
	wdiffuse[2] = 0.0;
	wdiffuse[3] = 0.2;
	
	whighlight[0] = 0.0;
	whighlight[1] = 0.0;
	whighlight[2] = 0.0;
	whighlight[3] = 0.0; 
	
	wref[0] = 0.0;
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wdiffuse);
		
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whighlight);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, wref);
	
	bricks = boxsize / wall_thickness;
	
	for (i = 0; i <= bricks; i++)
	{
		for (j = 0; j <= bricks; j++)
		{   
			// bottom wall
			glTranslatef(((-1 * boxsize / 2 ) + i * wall_thickness) / space_factor,
						   -1 * boxsize / (2 * space_factor), 
						 ((-1 * boxsize / 2 ) + j * wall_thickness) / space_factor);
						
			glutSolidCube(wall_thickness / space_factor);
			
			glTranslatef(((-1 * boxsize / 2 ) + i * wall_thickness) / -space_factor,
								boxsize / (2 * space_factor),
						 ((-1 * boxsize / 2 ) + j * wall_thickness) / -space_factor);						
	
		}
	}	
}

double spatium::getgpe()
{	
	double gpe;			
	gpe = globi[0].getmass() * 9.8 * (globi[0].getpos()[1] - 
			   (-1 * boxsize / 2 ) +  wall_thickness / 2 + globi[0].getradius());
	
	return gpe;
}
