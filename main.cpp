#include <iostream>
#include <chrono>

#include "include/GLDraw.hpp" // opengl drawing class
#include "include/FMODEq.hpp" // class analysis freqs from music 
#include <cmath>
#include <cstdio>
/********************
	FModeq(x) - x is number of frequency cells, each with range 48000/(2*x) hz


****/


int main(int argc, char** argv)
{

		int r = static_cast<int>( pow(2,13) );
		FMODEq analyse(r);
		if( !analyse. init() )
			std::cout << "ERRsOR";
		if( !analyse. loadMusic("resources/wave.mp3") )
			std::cout << "MusicERROR";
		if( !analyse. setChannel() )
			std::cout << "ChannelERROR";

		GLDraw visual(r);
		visual. start(argc, argv);

		while(true)
		{		
			analyse. run( );
			visual. getData( analyse. getSpects( ) );
			if( analyse. send )
				visual. getNotes( analyse. getKeys() );
  		visual. run( );
						
		}

		
}


