class color
{
	private:		

	public:
		audax<GLfloat> rgb;	
		color(GLfloat, GLfloat, GLfloat);
		color();				
		~color();
		GLfloat getred();
		GLfloat getgreen();
		GLfloat getblue();
};
