#include "Nivel7.h"

#include "Menu.h"
#include "GameOver.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Nivel1.h"

Nivel7::Nivel7() {
	m_ball.IncrementarVelocidad(incremento_velocidad++);
	m_stats.IncrementarNivel();
	
	for (int i = 0; i < rowCount-5; ++i) { 
		if (i%2!=0){
			for (int j = 0; j < columnCount+4; ++j) {
				i--;
				float x = j * ((blockWidth-54) + 34.f) + 40.f;
				float y = i * (blockHeight + 36) + 34.f;
				i++;
				bool isSpecial_menospts = (rand () % 40 == 0); /// Probabilidad 1 / 40 de ser especial el bloque puntos (resta 100 y 1 vida)
				bool isSpecial_puntos = (rand()%40 == 0); /// Probabilidad 1 / 40 de ser especial el bloque puntos
				if(isSpecial_menospts){
					m_blocks.emplace_back(x,y,blockWidth-54,blockHeight+54,Color::Blue,false,false,false,true);
					contador_bloques_special++;
				}else{
					if(isSpecial_puntos){
						m_blocks.emplace_back(x,y,blockWidth-54,blockHeight+54,Color::Yellow,true);
						contador_bloques_special++;
					}else{
						m_blocks.emplace_back(x, y, blockWidth - 54, blockHeight + 54, Color::White);
					}
				}
			}
		}else{
			for (int j = 0; j < columnCount-3; ++j) {
				float x = j * ((blockWidth-54) + 88.f) + 40.f;
				float y = i * (blockHeight + 36) + 4.f;
				bool isSpecial_menospts = (rand () % 40 == 0); /// Probabilidad 1 / 40 de ser especial el bloque puntos (resta 100 y 1 vida)
				bool isSpecial_puntos = (rand()%40 == 0); /// Probabilidad 1 / 40 de ser especial el bloque puntos
				if(isSpecial_menospts){
					m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color::Blue,false,false,false,true);
					contador_bloques_special++;
				}else{
					if(isSpecial_puntos){
						m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color::Yellow,true);
						contador_bloques_special++;
					}else{
						m_blocks.emplace_back(x, y, blockWidth, blockHeight, Color::White);
					}
				}
			}
		}
	}
}

void Nivel7::Update (Game &g) {
	this->ManejoInput(g); /// Manejo de  todos los Inputs de el Juego
	
	this->ManejoPelota(); /// Manejo de colisiones pelota - paleta y tema limites
	
	this->ColisionesPelotaLadrillo(g); /// Manejo de Colisiones pelota - ladrillo y bloques especiales
	
	this->ChequeoTransicion(g); /// Manejo de transicion, si se gana, se pasa de nivel
	
	this->ManejoGameOver(g); /// Manejo de vidas y escena gameover
	
	
	m_stats.actualizarStats();
	m_ball.Update();
	m_player.Update();
	
}

void Nivel7::ChequeoTransicion(Game &g){
	if(m_blocks.empty()){
		g.SetScene(new Nivel1());
	}
}

void Nivel7::ColisionesPelotaLadrillo (Game &g){
	for (auto it = m_blocks.begin(); it != m_blocks.end(); ){
		if (m_ball.Colisiona(*it)) {
			
			/// Bloque especial de puntos (resta 100 y 1 vida)
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

void Nivel7::Draw (RenderWindow &w) {
	w.clear({20,20,20});
	m_ball.Draw(w);
	m_player.Draw(w);
	
	m_stats.DrawStats(w);
	
	for(auto &bloque : m_blocks){
		bloque.Draw(w);
	}
}

