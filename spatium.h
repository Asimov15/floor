class spatium
{
	private:		
		// camera
		audax <double> angular_velocity;
		audax <double> angular_position;
		vector <double> campos;
		vector <double> lookat;	
		vector <body>   globi;	
		double space_factor;  // bigger the number the more space can be seen
		double time_factor;   // smaller the number the faster is goes
		int turn;
		const double gravc	= 6.67384e-11;
		const double boxsize = 8;
		const double wall_thickness = 0.5;
		void apply_gravity();
		void collisions();		
		void box_wall();
		const bool gravity = true;
		double totalke();
		double getgpe();
		const bool bounding_box = true;
		void render_bounding_box();
		
	public:
		spatium(audax<double>&, audax<double>&, vector<double>&, vector<double>&, vector<body>&,
		        double, double);
		spatium();
		spatium(double, double);
		~spatium();	
		int run(int, char **);					
		void simulate();
		void reshape(int, int);
		void keyboard(unsigned char, int, int);
		void initglut(int, char **);
		void initgraphics();		
		void display();
		void set_globi(vector<body>&);
		void set_tf(double);		
		void set_sf(double);		
};

class spatium_global 
{
public:
	static spatium* current_spatium;

	static void simulate() 
	{
		current_spatium->simulate();
	}

	static void reshape(int w, int h)
	{
		current_spatium->reshape(w, h);
	}

	static void keyboard(unsigned char key, int x, int y)
	{
		current_spatium->keyboard(key, x, y);
	}
};


