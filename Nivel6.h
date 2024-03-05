#ifndef NIVEL6_H
#define NIVEL6_H
#include "Game.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Nivel.h"

class Nivel6 : public Nivel{
public:
	Nivel6();
	void Update(Game &g) override;
	void Draw(RenderWindow &w) override;
	void ChequeoTransicion(Game &g) override;
	void ColisionesPelotaLadrillo (Game &g)override;
private:
};

#endif

