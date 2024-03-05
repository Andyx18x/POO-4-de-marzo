#ifndef NIVEL7_H
#define NIVEL7_H
#include "Nivel.h"

class Nivel7 : public Nivel {
public:
	Nivel7();
	void Update (Game &g)override;
	void Draw (RenderWindow & window)override;
	void ChequeoTransicion(Game &g) override;
	void ColisionesPelotaLadrillo (Game &g)override;
private:
};

#endif

