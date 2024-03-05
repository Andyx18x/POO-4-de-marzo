#include "Menu.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Window/Event.hpp>
#include "HighScores.h"
#include "Nivel1.h"
#include "Guia.h"
#include "Perfil.h"
#include <fstream>
using namespace std;

Menu::Menu() {
	t_logo.loadFromFile("logotipo.png");
	s_logo.setTexture(t_logo);
	s_logo.setPosition(190,100);
	
	m_font.loadFromFile("fuente_menu.ttf");
	
	
	int Var_y = 250;
	option.resize(Max_Items_Menu);
	
	for(int i=0;i<Max_Items_Menu;i++){
		option[i].setFont(m_font);
		option[i].setCharacterSize(24);
		option[i].setPosition(330,Var_y);
		Var_y +=70;
	}
	
	option[0].setFillColor(Color::Green);
	option[1].setFillColor(Color::White);
	option[2].setFillColor(Color::White);
	
	option[0].setString("<PLAY>");
	option[1].setString("<PERFIL>");
	option[2].setString("<SCORES>");
	option[3].setString("<GUIA>");
	option[4].setString("<EXIT>");
	
	sonido_inicio.loadFromFile("start.wav");
	sonido_i.setBuffer(sonido_inicio);
	
	sonido_i.play();
	
	
	selectItem = 0;
	
	
}

void Menu::Update(Game &g){	
	
	if((option[selectItem].getString()== option[0].getString()) and Keyboard::isKeyPressed(Keyboard::Return) and m_nombre != " " ){
		g.SetScene(new Nivel1());
	}
	
	if((option[selectItem].getString()== option[4].getString()) and Keyboard::isKeyPressed(Keyboard::Return)){
		ofstream archi_pts("puntos.txt", ios::out);
		string puntos = "0";
		archi_pts<<puntos;
		g.CloseGame();
	}
	
}


void Menu::Draw(RenderWindow &window){
	window.clear({0,0,0});
	window.draw(s_logo);
	for(int i=0;i<Max_Items_Menu;i++){
		window.draw(option[i]);
	}
}

void Menu::MoveUp(){
	if(selectItem - 1 >= 0 ){
		option[selectItem].setFillColor(Color::White);
		selectItem--;									/// Va pintando los distintos apartado de menu, dependiendo de donde nos posicionemos con las flechitas del teclado
		option[selectItem].setFillColor(Color::Green);
	}
}


void Menu::MoveDown(){
	if(selectItem + 1 < Max_Items_Menu ){
		option[selectItem].setFillColor(Color::White);
		selectItem++;									/// Va pintando los distintos apartado de menu, dependiendo de donde nos posicionemos con las flechitas del teclado
		option[selectItem].setFillColor(Color::Green);
	}
}

void Menu::ProcesarEventos(Game &g, Event &ev){
	if(ev.type== Event::KeyPressed and ev.key.code == Keyboard::Up){
		MoveUp();
	}
	if(ev.type== Event::KeyPressed and ev.key.code == Keyboard::Down){
		MoveDown();
	}
	
	if((option[selectItem].getString()== option[1].getString()) and ev.type== Event::KeyPressed and ev.key.code == Keyboard::Return){
		g.SetScene(new Perfil());
	}
	
	if((option[selectItem].getString()== option[2].getString()) and ev.type== Event::KeyPressed and ev.key.code == Keyboard::Return){
		g.SetScene(new HighScores());
	}

	if((option[selectItem].getString()== option[3].getString()) and ev.type== Event::KeyPressed and ev.key.code == Keyboard::Return){
		g.SetScene(new Guia());
	}
	
}
