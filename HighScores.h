#ifndef HIGHSCORES_H
#define HIGHSCORES_H
#include "Scene.h"
#include <vector>
#include <SFML/Graphics/Text.hpp>
using namespace std;

struct PlayerScore{
	char m_name[15];
	int m_puntos;
};

bool comparing_score(PlayerScore &a, PlayerScore &b);


class HighScores : public Scene{
public:
	HighScores();
	void Update(Game &g)override;
	void Draw(RenderWindow &window)override;
	void ProcesarEventos(Game &g, Event &ev)override;
	void CargarScores();
private:
	vector<Text>draw_scores; Font m_font;
	Text volver_menu;
	vector<PlayerScore>Scores;
};

#endif

