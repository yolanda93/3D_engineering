
#include <iostream>
#include <vector>
#include <cstring>


#include "types.h"
#include "cloud_segmentation.h"
#include "Visualization_Tools.h"



int main(int argc, char **argv)
{
	

// -------  Loading data and structure initialization -------//
// ----------------------------------------------------------//
Cloud_segmentation C;


if( !load_polyhedron( C.mesh , argv[1]) )  return 0;
C.init();

// ----------------------------------------------------------//
// ----------------------------------------------------------//




bool redo=true;

while(redo){

	double beta;
	cout<<endl<<"Give value for beta: ";
	std::cin>>beta;
	cout<<endl;

	//Labeling
	C.labeling(beta);
	C.save_result();

	cout<<endl<<"Relaunch ? (yes=1, no=0): ";
	std::cin>>redo;
}

redo = true;

while (redo){

	double max_angle, min_size;
	cout << endl << "Give value for max angle: ";
	std::cin >> max_angle;
	cout << endl << "Give value for minimum size: ";
	std::cin >> min_size;
	cout << endl;

	//Plane extraction
	C.plane_extraction(max_angle, min_size);
	C.save_result2();

	cout << endl << "Relaunch ? (yes=1, no=0): ";
	std::cin >> redo;
}


cout << endl<< "END" << endl;

return 0;
}