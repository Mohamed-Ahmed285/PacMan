#include "Game.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;
GameState gState;

void OnStart()
{
	Init();
	LoadHighScore();
}
void OnQuit()
{
	SaveHighScore();
}
void LoadHighScore()
{
	std::ifstream infile;
	std::stringstream ss;
	std::string line;
	int hs = 0;
	infile.open("highscore.txt");
	if (!infile) {
		gState.high_score = 0;
		return;
	}
	getline(infile, line);
	ss << line;
	ss >> hs;

	gState.high_score = hs;
}
void SaveHighScore()
{
	std::ofstream outfile("highscore.txt");
	if (!outfile.is_open())
		printf("Cant open file!");

	outfile << gState.high_score;
	outfile.close();
}

void Init()
{
	Player* pl = new Player();
	pl->cur_dir = UP;
	pl->pos = { 14,23.5 };
	pl->stopped = true;
	gState.player = pl;

	// Ghosts init

	Ghost* temp = new Ghost();
	temp->type = RED;
	gState.ghosts.push_back(temp);

	temp = new Ghost();
	temp->type = PINK;
	gState.ghosts.push_back(temp);

	temp = new Ghost();
	temp->type = BLUE;
	gState.ghosts.push_back(temp);

	temp = new Ghost();
	temp->type = ORANGE;
	gState.ghosts.push_back(temp);

	InitBoard();


	//InitRender();
	//ResetGhostsAndPlayer();

	//InitSounds();

	SetupMenu();
	gState.game_state = MENU;
	gState.pause_time = 2000;
}

void SetupMenu()
{
	for (int i = 0; i < 4; i++) {
		gState.ghosts[i]->enable_draw = true;
		gState.ghosts[i]->pos = { 6,5.5f + i * 3.f };
		gState.ghosts[i]->cur_dir = RIGHT;
		gState.ghosts[i]->target_state = CHASE;
		gState.ghosts[i]->in_house = false;
	}
	gState.player->enable_draw = true;
	gState.player->pos = { 6,17.5f };
	gState.player->cur_dir = RIGHT;
	//SetPacManMenuFrame();
	//SetPulseFrequency(200);
}

void InitBoard()
{
	string line;
	ifstream infile("Map.txt");
	if (!infile)
		return;
	while (getline(infile, line))
	{
		gState.board.push_back(line);
	}

	infile.close();

}