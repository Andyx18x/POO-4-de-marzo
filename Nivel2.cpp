#include "Nivel2.h"
#include "Game.h"
#include "Menu.h"
#include "Nivel3.h"
#include "GameOver.h"
#include "Nivel1.h"
#include "Nivel4.h"
#include <iostream>
using namespace std;

Nivel2::Nivel2() {
	
	m_ball.IncrementarVelocidad(++incremento_velocidad);
	m_stats.IncrementarNivel();
	
	
	/// Escalera
	for (int i = 0; i < rowCount; ++i) {
		for (int j = 0; j <= i; ++j) {   /// El número de bloques en cada fila aumenta gradualmente a medida que avanzamos hacia abajo en la escalera
			float x = j * (blockWidth + 6.f) + 5.f;
			float y = i * (blockHeight + 6.f) + 5.f;
			
			
			bool isSpecial = (rand () % 70 == 0); /// Probabilidad de 1 / 70 de ser especial el bloque nivel (Saltea 1)
			bool isSpecial_puntos = (rand()% 40 == 0); /// Probabilidad de 1 / 40 de ser especial  el bloque puntos
			bool isSpecial_nivel_d = (rand () % 110 == 0); /// Probabilidad 1 / 110 de ser especial el bloque Nivel (saltea 2)
			bool isSpecial_menospts = (rand () % 40 == 0); /// Probabilidad 1 / 40 de ser especial el bloque puntos (resta 100 y 1 vida)
			
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
						if(isSpecial_menospts){
							m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color::Blue,false,false,false,true);
							contador_bloques_special++;
						}else{
							m_blocks.emplace_back(x, y, blockWidth, blockHeight, Color::White);
						}
					}
				}
			}
		}
	}
	
	bloques_totales = m_blocks.size();
	
}

void Nivel2::Update(Game &g){
	
	
	this->ManejoInput(g); /// Manejo de  todos los Inputs de el Juego
	
	
	this->ManejoPelota(); /// Manejo de colisiones pelota - paleta y tema limites
	
	this->ColisionesPelotaLadrillo(g); /// Manejo de Colisiones pelota - ladrillo y bloques especiales
	
	this->ChequeoTransicion(g); /// Manejo de transicion, si se gana, se pasa de nivel
	
	this->ManejoGameOver(g); /// Manejo de vidas y escena gameover
	
	
	m_stats.actualizarStats();
	m_ball.Update();
	m_player.Update();
	
	
}

void Nivel2::ChequeoTransicion(Game &g){
	if(m_blocks.empty() or contador_bloques_normales ==  (bloques_totales - contador_bloques_special)){ /// EL nivel termina cuando no hay bloques, o cuando se rompen todos los bloques normales
		g.SetScene(new Nivel3());
	}
}

void Nivel2::ColisionesPelotaLadrillo (Game &g){
	
	for (auto it = m_blocks.begin(); it != m_blocks.end(); ){
		if (m_ball.Colisiona(*it)) {
			if (it->isSpecialNivel()) { /// Bloque especial de Nivel (Saltea 1)
				g.SetScene(new Nivel3());
				bl_pl.play();
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
				m_stats.aumentarpuntaje(200);
				bl_pl.play();
				m_stats.IncrementarNivel();
				g.SetScene(new Nivel4());
				m_ball.Rebotar();
				it = m_blocks.erase(it); /// Eliminar bloque especial
				continue; /// Continuar con el siguiente bloque
			} 
			
			/// Bloque especial de puntos (resta 100)
			if(it->isSpecialPts()){
				bl_pl.play();
				m_stats.restarpuntaje(100);
				m_ball.Rebotar();
				m_stats.DecrementarVida();
				it = m_blocks.erase(it); /// Eliminar bloque especial
				continue; /// Continuar con el siguiente bloque
			} 
			
			/// Si no es especial el bloque pasa esto..
			bl_pl.play();
			contador_bloques_normales++;
			m_stats.aumentarpuntaje(25);
			m_ball.Rebotar();
			it = m_blocks.erase(it); /// Avanza el iterador después de eliminar el bloque no especial
		} else {
			++it; /// Avanza al siguiente bloque si no hay colisión
		}
	}
}



void Nivel2::Draw(RenderWindow &w){
	w.clear({20,20,20});
	m_ball.Draw(w);
	m_player.Draw(w);
	
	m_stats.DrawStats(w);
	
	for(auto &bloque : m_blocks){
		bloque.Draw(w);
	}
}

