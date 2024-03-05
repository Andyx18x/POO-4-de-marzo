#ifndef GAMEOVER_H
#define GAMEOVER_H
#include "Scene.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Window/Event.hpp>
using namespace std;

class GameOver : public Scene {
public:
	GameOver();
	void Update(Game &g) override;
	void Draw(RenderWindow &window) override;
void ProcesarEventos(Game &g, Event &ev)override;
	void MoveUp() override;
	void MoveDown()override;
private:
	Text game_overtxt; Font m_font; 
	
	
	SoundBuffer sonido_perder;
	Sound perder;
	
	
	Text scoretxt; int m_score;
	vector<Text>option;
	int Max_Items_Menu = 2;
	int selectItem;
};

#endif

