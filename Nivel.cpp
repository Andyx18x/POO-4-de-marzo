#include "Nivel.h"
#include "Menu.h"
#include "GameOver.h"
#include "Player.h"

Nivel::Nivel() {
	bloq_pelota.loadFromFile("break.wav"); /// Musica de pelota - bloque(ladrillo)
	bl_pl.setBuffer(bloq_pelota);
	
	
	paleta_pelota.loadFromFile("bounce.wav"); /// Musica de paleta - pelota 
	pl_pe.setBuffer(paleta_pelota);
	
	
	musica_principal.openFromFile("musica.ogg"); /// Musica principal del juego
	musica_principal.play();
	musica_principal.setLoop(true);
	
}
void Nivel::ManejoInput(Game &g){
	if(Keyboard::isKeyPressed(Keyboard::Escape)){
		g.SetScene(new Menu());
		m_stats.ResetStats();
		incremento_velocidad = 0;
		
	}
	
	if(Keyboard::isKeyPressed(Keyboard::Space)){
		m_ball.setBallMoving(true);
		m_stats.CambiarColores();
		m_stats.draw_text(false);
	}
}

void Nivel::ManejoGameOver(Game &g){
	if(m_stats.VerVidas() == 0){ /// Si no hay vidas, entonces se va a la scena gameover y se guarda el puntaje en block de notas
		m_stats.GuardarScore(m_stats.obtenerpuntaje());
		m_stats.ResetStats();
		incremento_velocidad = 0;
		g.SetScene(new GameOver());
	}
}

void Nivel::ManejoPelota(){
	if(m_ball.Colisiona(m_player)){ /// Colision pelota-paleta
		pl_pe.play(); /// Musica de colision pelota-paleta
		m_ball.Rebotar(m_player.DimensionesPlayer()); 
	}
	
	if(m_ball.PasoLimites()){  /// Si se cae la pelota, 1 vida menos
		m_stats.DecrementarVida();
	}
}


int incremento_velocidad = 0;

