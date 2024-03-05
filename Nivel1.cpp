
#include "Game.h"
#include "Menu.h"
#include "Nivel2.h"
#include "GameOver.h"
#include <cmath>
#include "Nivel3.h"
#include <iostream>
using namespace std;

Nivel1::Nivel1() {
	m_ball.IncrementarVelocidad(incremento_velocidad++);
	
	/// Piramide invertida
	for (int i = 0; i < rowCount; ++i) {
		for (int j = 0; j < columnCount - i; ++j) {   /// Ajuste en el límite de columnas
			float x = (j + 0.5f * i) * (blockWidth + 6.f) + 5.f;   /// Cada fila se desplaza un poco hacia la derecha
			float y = i * (blockHeight + 6.f) + 5.f;
			
			bool isSpecial = (rand () % 60 == 0); /// Probabilidad de 1 / 60 de ser especial el bloque nivel (Saltea 1)
			bool isSpecial_puntos = (rand()% 30 == 0); /// Probabilidad de 1 / 30 de ser especial  el bloque puntos
			bool isSpecial_nivel_d = (rand () % 110 == 0); /// Probabilidad 1 / 110 de ser especial el bloque Nivel (saltea 2)
			
			if(isSpecial){
				m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color(255,0,128),false,true);
				contador_bloques_special++;
			}else{
				if(isSpecial_puntos){
					m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color::Yellow,true,false);
					contador_bloques_special++;
				}else{
					if(isSpecial_nivel_d){
						m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color(255,165,0),false,false,true);
						contador_bloques_special++;
					}else{
						m_blocks.emplace_back(x, y, blockWidth, blockHeight, Color::White);
					}
				}
			}
		}
	}
	
	
	bloques_totales = m_blocks.size();
}
	

void Nivel1::Update(Game &g){
	
	this->ManejoInput(g); /// Manejo de  todos los Inputs de el Juego
	
	
	this->ManejoPelota(); /// Manejo de colisiones pelota - paleta y tema limites
	
	this->ColisionesPelotaLadrillo(g); /// Manejo de Colisiones pelota - ladrillo y bloques especiales
	
	this->ChequeoTransicion(g); /// Manejo de transicion, si se gana, se pasa de nivel
	
	this->ManejoGameOver(g); /// Manejo de vidas y escena gameover
	
	
	m_stats.actualizarStats();
	m_ball.Update();
	m_player.Update();
	
}

void Nivel1::ChequeoTransicion(Game &g){
	if(m_blocks.empty() or contador_bloques_normales ==  (bloques_totales - contador_bloques_special)){ /// EL nivel termina cuando no hay bloques, o cuando se rompen todos los bloques normales
		g.SetScene(new Nivel2());
	}
}

void Nivel1::ColisionesPelotaLadrillo (Game &g){
	
	for (auto it = m_blocks.begin(); it != m_blocks.end(); ){
		if (m_ball.Colisiona(*it)) {
			if (it->isSpecialNivel()) {         /// Bloque especial de Nivel
				
				bl_pl.play();		 /// Musica de choque de pelota-bloque (ladrillo)
				g.SetScene(new Nivel2());
				m_stats.aumentarpuntaje(100);
				m_ball.Rebotar();
				it = m_blocks.erase(it); /// Eliminar bloque especial
				continue; /// Continuar con el siguiente bloque
			}
			
			/// Bloque especial de puntos
			if(it->isSpecialBlock()){
				bl_pl.play();
				m_stats.aumentarpuntaje(75);
				m_stats.IncrementarVidas();
				m_ball.Rebotar();
				it = m_blocks.erase(it); /// Eliminar bloque especial
				continue; /// Continuar con el siguiente bloque
			} 
			
			/// Bloque especial Nivel (Saltea 2)
			if(it->isSpecialNivel_dos()){
				bl_pl.play();
				m_stats.aumentarpuntaje(200);
				g.SetScene(new Nivel3());
				m_ball.Rebotar();
				it = m_blocks.erase(it); /// Eliminar bloque especial
				continue; /// Continuar con el siguiente bloque
			}   
			
			/// Si no es especial el bloque pasa esto..
			bl_pl.play(); 
			m_stats.aumentarpuntaje(25);
			m_ball.Rebotar();
			it = m_blocks.erase(it); /// Avanza el iterador después de eliminar el bloque no especial
		} else {
			++it; /// Avanza al siguiente bloque si no hay colisión
		}
	}
}

void Nivel1::Draw(RenderWindow &w){
	w.clear({20,20,20});
	m_ball.Draw(w);
	m_player.Draw(w);
	m_stats.DrawStats(w);
	
	for(auto &bloque : m_blocks){
		bloque.Draw(w);
	}
}


