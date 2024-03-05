#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct PlayerScore{
	char m_name[15];
	int m_puntos;
};

int main() {
	ofstream archi("Scores.dat",ios::binary);
	PlayerScore p1;
	p1.m_name[0] = 'L'; p1.m_name[1] = 'u'; p1.m_name[2] = 'a'; p1.m_name[3] = 'n'; p1.m_name[4] = 'a';  p1.m_name[5] = '\0';  
	p1.m_puntos = 4500;
	archi.write(reinterpret_cast<char*>(&p1),sizeof(PlayerScore));
	
	PlayerScore p2;
	p2.m_name[0] = 'P'; p2.m_name[1] = 'e'; p2.m_name[2] = 'd'; p2.m_name[3] = 'r'; p2.m_name[4] = 'o'; p2.m_name[5] = '\0'; 
	p2.m_puntos = 4000;
	archi.write(reinterpret_cast<char*>(&p2),sizeof(PlayerScore));
	
	PlayerScore p3;
	p3.m_name[0] = 'T'; p3.m_name[1] = 'h'; p3.m_name[2] = 'i'; p3.m_name[3] = 'a'; p3.m_name[4] = 'g'; p3.m_name[5] = 'o'; p3.m_name[6] = '\0'; 
	p3.m_puntos = 3500;
	archi.write(reinterpret_cast<char*>(&p3),sizeof(PlayerScore));
	
	PlayerScore p4;
	p4.m_name[0] = 'L'; p4.m_name[1] = 'u'; p4.m_name[2] = 'c'; p4.m_name[3] = 'a'; p4.m_name[4] = 's'; p4.m_name[5] = '\0'; 
	p4.m_puntos = 1500;
	archi.write(reinterpret_cast<char*>(&p4),sizeof(PlayerScore));
	
	PlayerScore p5;
	p5.m_name[0] = 'M'; p5.m_name[1] = 'a'; p5.m_name[2] = 'r'; p5.m_name[3] = 'i'; p5.m_name[4] = 'a'; p5.m_name[5] = '\0'; 
	p5.m_puntos = 1000;
	archi.write(reinterpret_cast<char*>(&p5),sizeof(PlayerScore));
	
	
	
	return 0;
}
