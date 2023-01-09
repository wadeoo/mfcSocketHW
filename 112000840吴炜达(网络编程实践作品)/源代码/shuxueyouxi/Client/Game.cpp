#include "StdAfx.h"
#include "Game.h"
#include <ctime>

Game::Game()
{
	countTasks = 3;
	x = new int[countTasks];
	y = new int[countTasks];
	answer = new int[countTasks];
	k = new unsigned short[countTasks];
	level = 0;
	points = 0;
	srand(time(NULL));
}

Game::~Game()
{
	delete x, y, answer, k;
}

void Game::singleDigits()
{
	for (int i = 0; i < countTasks; i++){
		x[i] = rand() % 10;
		y[i] = rand() % 10;
	}
}

void Game::Digits(int i)
{
	switch (level)
	{
		case 1:
			x[i] = rand() % 10;
			y[i] = rand() % 10;
			break;
		case 2:
			x[i] = rand() % 10;
			y[i] = rand() % 10;
			break;
		case 3:
			x[i] = rand() % 90 + 10;
			y[i] = rand() % 90 + 10;
			break;
		case 4:
			x[i] = rand() % 90 + 10;
			y[i] = rand() % 90 + 10;
			break;
		case 5:
			x[i] = rand() % 900 + 100;
			y[i] = rand() % 900 + 100;
			break;
	}
}


void Game::twoDigitNumber()
{
	for (int i = 0; i < countTasks; i++){
		x[i] = rand() % 90 + 10;
		y[i] = rand() % 90 +10;
	}
}

void Game::threeDigitNumber()
{
	for (int i = 0; i < countTasks; i++){
		x[i] = rand() % 900 + 100;
		y[i] = rand() % 900 + 100;
	}
}

void Game::PlusMinus()
{
	for (int i = 0; i < countTasks; i++){
		k[i] = rand() % 2;
		if (k[i] == 0) answer[i] = (x[i] + y[i]);
		else answer[i] = (x[i] - y[i]);
	}
}

void Game::Operation(int i)
{
	switch (level)
	{
		case 1:
			k[i] = rand() % 2;
			if (k[i] == 0) answer[i] = (x[i] + y[i]);
			else answer[i] = (x[i] - y[i]);
			break;
		case 2:
			k[i] = rand() % 4;
			switch (k[i]){
				case 0: answer[i] = (x[i] + y[i]); break;
				case 1: answer[i] = (x[i] - y[i]); break;
				case 2: answer[i] = (x[i] * y[i]); break;
				//case 3: answer[i] = (x[i] / y[i]); break;
			}
			break;
		case 3:
			k[i] = rand() % 2;
			if (k[i] == 0) answer[i] = (x[i] + y[i]);
			else answer[i] = (x[i] - y[i]);
			break;
		case 4:
			k[i] = rand() % 4;
			switch (k[i]){
				case 0: answer[i] = (x[i] + y[i]); break;
				case 1: answer[i] = (x[i] - y[i]); break;
				case 2: answer[i] = (x[i] * y[i]); break;
				//case 3: answer[i] = (x[i] / y[i]); break;
			}
			break;
		case 5:
			k[i] = rand() % 4;
			switch (k[i]){
				case 0: answer[i] = (x[i] + y[i]); break;
				case 1: answer[i] = (x[i] - y[i]); break;
				case 2: answer[i] = (x[i] * y[i]); break;
			}
			break;
	}

}

void Game::PMTD()
{
	for (int i = 0; i < countTasks; i++){
		k[i] = rand() % 4;
		switch (k[i])
		{
			case 0: answer[i] = (x[i] + y[i]); break;
			case 1: answer[i] = (x[i] - y[i]); break;
			case 2: answer[i] = (x[i] * y[i]); break;
			//case 3: answer[i] = (x[i] / y[i]); break;
			default: answer[i] = (x[i] + y[i]); break;
		}
	}
}

int Game::check(int buf)
{
	for (int i = 0; i < countTasks; i++)
		if (answer[i] == buf) return i+1; 
	return 0;
}

char Game::getOperation(unsigned short i)
{
	switch (i)
	{
		case 0: return '+';
		case 1: return '-';
		case 2: return '*';
		//case 3: return '/';
		default: return '+';
	}
}

void Game::setValues()
{
	switch (level)
	{
	case 1:
		singleDigits();
		PlusMinus();
		break;
	case 2:
		singleDigits();
		PMTD();
		break;
	case 3:
		twoDigitNumber();
		PlusMinus();
		break;
	case 4:
		twoDigitNumber();
		PMTD();
		break;
	case 5:
		threeDigitNumber();
		PMTD();
		break;
	}
}