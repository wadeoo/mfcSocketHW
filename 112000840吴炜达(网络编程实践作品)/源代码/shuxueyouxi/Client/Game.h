#pragma once

class Game
{
	public:
		int *x, *y, *answer, sec, countTasks;
		unsigned short *k;
		int points;
		int level;
		Game();
		~Game();
		void Operation(int);
		void Digits(int);
		int check(int);
		char getOperation(unsigned short);
		void setValues();
	private:
		void singleDigits();
		void twoDigitNumber();
		void threeDigitNumber();
		void PlusMinus();
		void PMTD();
};