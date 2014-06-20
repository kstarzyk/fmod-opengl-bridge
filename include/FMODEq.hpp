#ifndef FMODEQ_H_
#define FMODEQ_H_ 1
#include <iostream>
#include <list>
#include <vector>
#include <array>
#include <fmodex/fmod.hpp>
class FMODEq 
{
	public:
		FMODEq(int sSize) : system(nullptr), specLeft(new float[sSize]), specRight(new float[sSize]), spec(new float[sSize]), sampleSize(sSize), keys()
		{
			hz = 48400.0/(2.0* static_cast<float>(sampleSize) );
		}

		~FMODEq() 
		{

			delete channel;
			delete sound;
			delete system;
			delete specLeft;
			delete specRight;
			delete spec;
		}
		int sampleSize;
		bool send;
		float *specLeft, *specRight, *spec;
		bool keys[120];

		bool init( );
		void run( );

		bool loadMusic( const std::string& );
		bool setChannel( );

		const std::pair < std::vector<float>, std::vector <float> > getSpects();
		const std::list <bool> getKeys();
		
		float hz;

		static float freq[];
		static std::string note[];

		//MODES
		void analyseNotes( int, float);


	protected:
		FMOD::System *system;
		FMOD_RESULT result;

		FMOD::Sound *sound; 
		FMOD::Channel *channel;
	
	private:
		std::string filepath;

};

#endif // FMODEQ_H_
