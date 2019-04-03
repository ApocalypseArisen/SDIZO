#pragma once
#ifndef Counter_hpp
#define Counter_hpp

using namespace std;

// Klasa obsługująca funkcje mierzenia czasu
class Counter
{
private:
	//Zmienne potrzebne do pomiaru czasu
	double PCFreq = 0.0;
	_int64 CounterStart = 0;
public:
	//Metody uruchamiające odliczanie i zwracające czas
	void StartCounter();
	void StartfileCounter();
	double GetCounter();
};
#endif