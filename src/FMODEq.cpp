#include <fmodex/fmod.hpp>
#include "../include/FMODEq.hpp"
#include <iostream>
#include <algorithm> 
#include <list>
#include <vector>

std::string FMODEq::note[] = 
{
    "C 0", "C#0", "D 0", "D#0", "E 0", "F 0", "F#0", "G 0", "G#0", "A 0", "A#0", "B 0",  
    "C 1", "C#1", "D 1", "D#1", "E 1", "F 1", "F#1", "G 1", "G#1", "A 1", "A#1", "B 1",  
    "C 2", "C#2", "D 2", "D#2", "E 2", "F 2", "F#2", "G 2", "G#2", "A 2", "A#2", "B 2",  
    "C 3", "C#3", "D 3", "D#3", "E 3", "F 3", "F#3", "G 3", "G#3", "A 3", "A#3", "B 3",  
    "C 4", "C#4", "D 4", "D#4", "E 4", "F 4", "F#4", "G 4", "G#4", "A 4", "A#4", "B 4",  
    "C 5", "C#5", "D 5", "D#5", "E 5", "F 5", "F#5", "G 5", "G#5", "A 5", "A#5", "B 5",  
    "C 6", "C#6", "D 6", "D#6", "E 6", "F 6", "F#6", "G 6", "G#6", "A 6", "A#6", "B 6",  
    "C 7", "C#7", "D 7", "D#7", "E 7", "F 7", "F#7", "G 7", "G#7", "A 7", "A#7", "B 7",  
    "C 8", "C#8", "D 8", "D#8", "E 8", "F 8", "F#8", "G 8", "G#8", "A 8", "A#8", "B 8",  
    "C 9", "C#9", "D 9", "D#9", "E 9", "F 9", "F#9", "G 9", "G#9", "A 9", "A#9", "B 9"
};

float FMODEq::freq[] =
{
      16.35f,   17.32f,   18.35f,   19.45f,    20.60f,    21.83f,    23.12f,    24.50f,    25.96f,    27.50f,    29.14f,    30.87f, 
      32.70f,   34.65f,   36.71f,   38.89f,    41.20f,    43.65f,    46.25f,    49.00f,    51.91f,    55.00f,    58.27f,    61.74f, 
      65.41f,   69.30f,   73.42f,   77.78f,    82.41f,    87.31f,    92.50f,    98.00f,   103.83f,   110.00f,   116.54f,   123.47f, 
     130.81f,  138.59f,  146.83f,  155.56f,   164.81f,   174.61f,   185.00f,   196.00f,   207.65f,   220.00f,   233.08f,   246.94f, 
     261.63f,  277.18f,  293.66f,  311.13f,   329.63f,   349.23f,   369.99f,   392.00f,   415.30f,   440.00f,   466.16f,   493.88f, 
     523.25f,  554.37f,  587.33f,  622.25f,   659.26f,   698.46f,   739.99f,   783.99f,   830.61f,   880.00f,   932.33f,   987.77f, 
    1046.50f, 1108.73f, 1174.66f, 1244.51f,  1318.51f,  1396.91f,  1479.98f,  1567.98f,  1661.22f,  1760.00f,  1864.66f,  1975.53f, 
    2093.00f, 2217.46f, 2349.32f, 2489.02f,  2637.02f,  2793.83f,  2959.96f,  3135.96f,  3322.44f,  3520.00f,  3729.31f,  3951.07f, 
    4186.01f, 4434.92f, 4698.64f, 4978.03f,  5274.04f,  5587.65f,  5919.91f,  6271.92f,  6644.87f,  7040.00f,  7458.62f,  7902.13f, 
    8372.01f, 8869.84f, 9397.27f, 9956.06f, 10548.08f, 11175.30f, 11839.82f, 12543.85f, 13289.75f, 14080.00f, 14917.24f, 15804.26f
};
bool FMODEq::init()
{
	result = FMOD::System_Create(&system);     // Create the main system object.
	if (result != FMOD_OK)
	{
			std::cout << "FMOD error! (%d) %s\n" <<result;// << FMOD_ErrorString(result);
			return false;
	}
	 
	result = system->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.
			 
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (%d) %s\n" << result;// << FMOD_ErrorString(result);
		return false;
	}

	return true;
}

bool FMODEq::loadMusic( const std::string &filepath )
{

	result = system->createSound(
			filepath.c_str(),
			FMOD_DEFAULT,
			0,
			&sound);

	if (result != FMOD_OK)
	{
			std::cout << "FMODasd error! (%d) %s\n" << result;
			return false;
	}
	
	return true;

}

bool FMODEq::setChannel( )
{
	system ->playSound(
		  FMOD_CHANNEL_FREE,
		  sound,
		  true,
		  &channel);
	channel->setVolume(0.5f);       // Set the volume while it is paused.
	channel->setPaused(false);

	return true;
}

void FMODEq::run( )
{
	send = false;
	system -> update();
	channel -> getSpectrum(specLeft, sampleSize, 0, FMOD_DSP_FFT_WINDOW_RECT);
	channel -> getSpectrum(specRight, sampleSize, 1, FMOD_DSP_FFT_WINDOW_RECT);

	float sum = 0.0;
	int max = 0;
	float maxf = 0.0;
	for(int j = 0; j < sampleSize; j++)
  {
		spec[j] = ( specLeft[j] + specRight[j])/2.0;
	}
	
	//analyseNotes(max, maxf);

// Find max volume
	
	auto maxIterator = std::max_element(&spec[0], &spec[sampleSize]);
	float maxVol = *maxIterator;
	//auto maxIteratorR = std::max_element(&specRight[0], &specRight[sampleSize]);
	//float maxVolL = *maxIteratorL;
	//float maxVolR = *maxIterator;

	//std::cout << maxVolR << " \n";
	

	//Normalize
	//if (maxVolL != 0 )
		//std::transform(&specLeft[0], &specLeft[sampleSize], &specLeft[0], [maxVolL] (float dB) -> float { return dB / maxVolL; });
	if ( maxVol != 0 )
		std::transform(&spec[0], &spec[sampleSize], &spec[0], [maxVol] (float dB) -> float { return dB / maxVol; });


	for(int i = 0; i < 120; i++)
	{
		keys[i] = false;
	}
	for(int i = 0; i < sampleSize; i++ )
	{
		if(spec[i] > 0.4f)
			analyseNotes(i, spec[i]);
	}

	send = true;
		
	//float hzRange = (44100.0 / 2.0) / float(sampleSize);	
	
	
}

void FMODEq::analyseNotes( int cell, float value )
{
	float dominantHZ = (float)cell * hz;
	int dominantNote = 0;
	int count;
  for (count = 0; count < 120; count++)
  	{
  	  if (dominantHZ >= freq[count] && dominantHZ < freq[count + 1])
      {

  	    if (fabs(dominantHZ - freq[count]) < fabs(dominantHZ - freq[count+1]))
				{
	        dominantNote = count;
					keys[count] = true;
				}
        else
				{
 	        dominantNote = count + 1;
					keys[count] = true;
				}
     
		   break;
      }
		
			else
				keys[count] = false;

    }
	
	
	
	
	std::cout << note[dominantNote] << " " << value << " " << dominantHZ << "\n";

	
}
const std::pair < std::vector<float>, std::vector <float> > FMODEq::getSpects()
{
	std::pair < std::vector <float>, std::vector <float>  > toReturn;

		std::vector <float> tempL(sampleSize);
		std::vector <float> tempR(sampleSize);
		for(int j = 0; j < sampleSize; j++)
		{
			tempL[j] = specLeft[j];
			tempR[j] = specRight[j];
		}

	toReturn = std::make_pair(tempL,tempR);
	return toReturn;
}

const std::list <bool> FMODEq::getKeys()
{
	std::list <bool> listKeys;
	for(int i = 0; i < 120; i++)
		listKeys.push_back(keys[i]);

	return listKeys;
}
