class body
{
	private:
		color col;
		color specular;		
		GLfloat shine;
		double mass; 	 // kg
		double density;  // kg m-3				
		audax <double> velocity; // m s-1
		audax <double> position;			
		
	public:
		body(color, color, GLfloat, double, double, audax<double>&, audax<double>&);
		body();
		~body();
		void display(int, double);
		void set_color(color);		
		color getcol();
		color getspec();
		GLfloat getshine();
		audax <double> getpos();
		double getmass();
		audax <double> getvel();
		void setvel(audax <double>);
		void setpos(audax <double>);
		void setdensity(double);
		double getradius();
		void setmass(double);
		bool touching(body&);
		bool buffer_zone(body &);
		bool is_moving_towards(body &);
		int colliding;		
		audax <double> cvelocity; // m s-1
};

