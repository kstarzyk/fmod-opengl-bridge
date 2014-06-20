#ifndef GLDRAW_H_
#define GLDRAW_H_ 1

#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <list>
#include <vector>


class GLDraw
{
	protected:
		static GLDraw *instance;	
		std::vector<float> specL, specR;
		int sampleSize;
		
	public:
		GLDraw(int sampleSize) : sampleSize(sampleSize), keys() {  }
		~GLDraw( ) 
		{
			std::cout << "GLDraw destructed"; 
			delete instance;
 		}
		void start( int argc, char *argv[] );
		void init();


		void run()
		{	 
			glutMainLoopEvent();
		}
		void setInstance();

		// calling display and swapBuffers
		void displayFramework( );

		// functions that really works
		virtual void display();
		virtual void reshape( int, int );
	

		// static void functions to emulate C-style 

		static void displayWrapper();
		static void reshapeWrapper(int, int);
		static void runWrapper();
		static void idle();

		static constexpr float DEG2RAD = M_PI/180.0;

		// dataGetters
		void getData(const std::pair < std::vector <float>, std::vector <float> > );
		void getNotes( const std::list <bool> );
		
		// shape drawing
		static void drawCircle(float radius);
		static void drawTriangle(float size);

		// shape-combintations drawings
		void drawSierpinski(int depth, float size, float modifier);

		// draw-objects
		bool keys[120];
		void drawPiano();
		void drawWhite(int, bool);
		void drawBlack(int, bool);

};


#endif // GLDRAW_H_
