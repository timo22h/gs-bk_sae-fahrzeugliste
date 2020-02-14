// sae-fahrzeugliste.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Einbinden von Systembibliotheken
#include "stdafx.h"
#include <iostream>
#include <cmath>
#include "string.h"
using namespace std;

// Deklaration der globalen Methoden
void AusgabeMenu();

int main()
{
	AusgabeMenu();
}

//Funktion um das Menu initial auszugeben
void AusgabeMenu()
{
	cout << "\nORGANISATION DER FAHRZEUGDATEN\n" << endl;
	cout << "1 = Anlegen eines neuen Fahrzeugs" << endl;
	cout << "2 = Suchen eines bestimmten Fahrzeugs" << endl;
	cout << "3 = Ausgabe aller Fahrzeuge" << endl;
	cout << "4 = Loeschen eines Fahrzeugs" << endl;
	
	// Eventuell Berechnen von Steuern
	cout << "5 = Berechnen von Steuern für ein bestimmtes Fahrzeug" << endl;

	cout << "Ihre Wahl: ";
}
