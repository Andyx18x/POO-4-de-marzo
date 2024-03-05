#ifndef NIVEL2_H
#define NIVEL2_H
#include "Nivel1.h"
#include "Nivel.h"

class Nivel2: public Nivel {
public:
	Nivel2();
	void Draw(RenderWindow &w) override;
	void Update(Game &g) override;
	void ChequeoTransicion(Game &g) override;
	void ColisionesPelotaLadrillo (Game &g)override;
private:
};

#endif

