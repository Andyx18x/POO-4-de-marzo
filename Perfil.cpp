#include "Perfil.h"
#include "Menu.h"
#include <iostream>
using namespace std;

Perfil::Perfil() {
	t_logo.loadFromFile("logotipo.png");
	s_logo.setTexture(t_logo);
	s_logo.setPosition(190,100);
	m_font.loadFromFile("fuente_menu.ttf");
	
	
	
	m_text.setFont(m_font);   /// Texto de digitar nombre
	m_text.setFillColor(Color::White);
	m_text.setCharacterSize(24);
	m_text.setPosition(50,250);
	m_text.setString("Digite su Nombre: ");
	
	
	m_input_nombre.setFont(m_font);  /// Input text para ingreso de nombre
	m_input_nombre.setFillColor(Color::Red);
	m_input_nombre.setCharacterSize(24);
	m_input_nombre.setPosition(470,250);
	
}

void Perfil::Draw (RenderWindow & window) {
	window.clear({0,0,0});
	window.draw(m_input_nombre);
	window.draw(s_logo);
	window.draw(m_text);
}

void Perfil::Update (Game & g) {
	m_input_nombre.update();
}

void Perfil::ProcesarEventos (Game & g, Event & ev) {
	if(ev.type== Event::KeyPressed and ev.key.code == Keyboard::Return){
		m_nombre = m_input_nombre.getString(); /// Obtenemos el nombre del jugador
		g.SetScene(new Menu());
	}else{
		m_input_nombre.processEvent(ev);
	}
}

string m_nombre = " ";


