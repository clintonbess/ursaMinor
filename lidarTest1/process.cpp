#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

#define PI 3.14159265

using namespace std;

double roundUp(double numToRound, int multiple);

int main(){

	string line;
	ifstream myFile ("test.txt");

	vector<float> angles, xValue, yValue;
	vector<int> distances;

	int temp_distance, temp_calc;
	float temp_angle;
	// open file and parse it
	if (myFile.is_open()){
		while( getline (myFile, line) ){
			// cout << line << '\n';
			string delimiter = ", ";
			size_t pos = 0;
			string token;
			while ((pos = line.find(delimiter)) != string::npos) {

			    token = line.substr(0, pos);

			    // convert the string to a c_string so we can use atof
				char * cstr = new char [token.length()+1];
				strcpy (cstr, token.c_str());

			    temp_angle = atof(cstr);
			    angles.push_back(temp_angle);
			    line.erase(0, pos + delimiter.length());
			    // free memory of cstr
			    delete[] cstr;
			}
			// convert the string to a c_string so we can use atoi
			char * cstr = new char [line.length()+1];
			strcpy (cstr, line.c_str());
			temp_distance = atoi (cstr);
			distances.push_back(temp_distance);
			
			// free memory of cstr
			delete[] cstr;
		}
		// close file
		myFile.close();

		int roundValue = 2;
		int angle_offset = 12;

		// convert polar data into cartesian coordianates
		// and place them into their vectors
		for(int i = 0; i < angles.size(); i++){
			xValue.push_back ( roundUp(distances[i] * cos( (angles[i] - angle_offset) * PI / 180.0), roundValue) );
			yValue.push_back ( roundUp (distances[i] * sin( (angles[i] - angle_offset) * PI / 180.0), roundValue) );
		}
		
		// TODO: write to file
		// display the cartesian coordiantes
		for(int i = 0; i < xValue.size(); i++){
			cout <<  xValue[i] << ", " << yValue[i] << '\n';
		}
	}
	else cout << "Cannot find file" << '\n';

	return 0;
}

double roundUp(double numToRound, int multiple){
    if (multiple == 0)
        return numToRound;

    int remainder = (int) abs(numToRound) % multiple;
    if (remainder == 0)
        return (int) numToRound;

    if (numToRound < 0)
        return (int)-(abs(numToRound) - remainder);
    else
        return (int) numToRound + multiple - remainder;
}