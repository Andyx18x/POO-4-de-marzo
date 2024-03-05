#ifndef BALL_H
#define BALL_H
#include "Object.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Ball : public Object{
public:
	Ball();
	void Update();
	void Rebotar(const FloatRect& playerBounds);
	void Rebotar();
	void IncrementarVelocidad(int speed);
	void Play();
	void setBallMoving(bool moving);
	int ball_speed();
	bool PasoLimites();
private:
	Vector2f m_speed;
	float velocity;
	
	float MAX_SPEED_X = 3.0f;
	bool ball_moving; bool paso_limites;
	
	SoundBuffer bordes_pelota; Sound sonido_b;
	
};

#endif

