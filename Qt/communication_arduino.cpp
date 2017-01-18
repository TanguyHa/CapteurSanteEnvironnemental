#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include <string>
#include <fstream>

using namespace std;
bool return_fin(){
	


	return true;
}
int main(){
	cout<<"Initianilisation du programme\n";
	ifstream fichier("/dev/ttyACM1");
	while(return_fin()){
		if(fichier){
			string texte;
			texte+=fichier.get();
			cout<<"texte: "<<texte;
			sleep(1);
		}
		else{
//			cout<<"impossible d'ouvrir le fichier\n";
		}
	}	
	fichier.close();

	return 0;
}
