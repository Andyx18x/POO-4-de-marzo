#ifndef NIVEL4_H
#define NIVEL4_H
#include "Nivel.h"
#include "Game.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Nivel4 : public Nivel {
public:
	Nivel4();
	void Update(Game &g) override;
	void Draw(RenderWindow &w) override;
	void ChequeoTransicion(Game &g) override;
	void ColisionesPelotaLadrillo (Game &g)override;
private:
};

#endif

