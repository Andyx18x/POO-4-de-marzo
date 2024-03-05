#include "Nivel5.h"
#include "Stats.h"
#include "Menu.h"
#include "GameOver.h"
#include "Nivel6.h"
Nivel5::Nivel5() {
	m_ball.IncrementarVelocidad(incremento_velocidad++);
	
	m_stats.IncrementarNivel();
	
	m_player.CambiarDimensiones(60,20);
	
	
	/// Bloques aleatorios
	
	srand(time(nullptr));   /// Inicializa la semilla para generar números aleatorios
	int minHeight = 3;
	int maxHeight = 20;
	int minWidth = 20;
	int maxWidth = 50;
	
	for (int i = 0; i < rowCount; ++i) {
		for (int j = 0; j < columnCount; ++j) {
			float x = j * (blockWidth + 6.f) + 5.f;
			float y = i * (blockHeight + 10.f) + 5.f;
			float height = (rand() % maxHeight) + minHeight; /// Altura aleatoria entre minHeight y maxHeight
			float Width = (rand() % maxWidth) + minWidth; /// Anchura aleatoria entre minWidtht y maxWidth
			
			bool isSpecial_puntos = (rand()% 30 == 0); /// Probabilidad de 1 / 30 de ser especial  el bloque puntos
			bool isSpecial_menospts = (rand () % 40 == 0); /// Probabilidad 1 / 40 de ser especial el bloque puntos (resta 100 y 1 vida)
			
			
			if(isSpecial_puntos){
				m_blocks.emplace_back(x,y,Width,height,Color::Yellow,true,false);
				contador_bloques_special++;
			}else{
				if(isSpecial_menospts){
					m_blocks.emplace_back(x,y,Width,height,Color::Blue,false,false,false,true);
					contador_bloques_special++;
				}else{
					m_blocks.emplace_back(x, y, Width, height, Color::White);
				}
			}
		}
	}
	
	bloques_totales = m_blocks.size();
}

void Nivel5::Update(Game &g){
	this->ManejoInput(g); /// Manejo de  todos los Inputs de el Juego
	
	this->ManejoPelota(); /// Manejo de colisiones pelota - paleta y tema limites
	
	this->ColisionesPelotaLadrillo(g); /// Manejo de Colisiones pelota - ladrillo y bloques especiales
	
	this->ChequeoTransicion(g); /// Manejo de transicion, si se gana, se pasa de nivel
	
	this->ManejoGameOver(g); /// Manejo de vidas y escena gameover
	
	
	m_stats.actualizarStats();
	m_ball.Update();
	m_player.Update();
	
}

void Nivel5::ChequeoTransicion(Game &g){
	if(m_blocks.empty() or contador_bloques_normales ==  (bloques_totales - contador_bloques_special)){ /// EL nivel termina cuando no hay bloques, o cuando se rompen todos los bloques normales
		g.SetScene(new Nivel6());
	}
}


void Nivel5::ColisionesPelotaLadrillo (Game &g){
	
	for (auto it = m_blocks.begin(); it != m_blocks.end(); ){
		if (m_ball.Colisiona(*it)) {
			if(it->isSpecialBlock()){     /// Bloque especial de puntos
				bl_pl.play();
				m_stats.aumentarpuntaje(75);
				m_stats.IncrementarVidas();
				m_ball.Rebotar();
				it = m_blocks.erase(it); /// Eliminar bloque especial
				continue; /// Continuar con el siguiente bloque
			} 
			
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

void Nivel5::Draw(RenderWindow &w){
	w.clear({20,20,20});
	m_ball.Draw(w);
	m_player.Draw(w);
	
	m_stats.DrawStats(w);
	
	for(auto &bloque : m_blocks){
		bloque.Draw(w);
	}
}
