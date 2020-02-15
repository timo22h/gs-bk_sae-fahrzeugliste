/*
						SAE Projekt
		Name: Timo Heyden
		Klasse: E2FI3
		Fachrichtung: SAE
		Lehrer: Matthias Röhrl
		Entwicklungsumgebungen:
								Visual Studio 2017
								Visual Studio Code
		Kurze Beschreibung:
							Bei diesem Projekt geht es um eine klene Verwaltung einer Fahrzeugliste.
		Ausgangssituation:  
							- Gesucht ist eine neue, übersichtliche und leicht erweiterbare Organisation
							der verschiedenen Fahrzeugdaten
							- zu erfassende Fahrzeugdaten von PKWs und Motorrädern sind unterschiedlich 
							und sollen später für die Weiterverarbeitung (z.B. Steuerberechnung) auch 
							unterschiedlich behandelt werden können.
							=> für alle Fahrzeugtypen: Kennzeichen, Jahr der Erstzulassung
							=> PKWs zusätzlich: Hubraum, Leistung, Schadstoffklasse
							=> Motorräder zusätzlich: Hubraum, Leistung
							- Entgegen dem alten System möchte man sich bei der reinen Verwaltung der Daten
							(z.B. Datenablage, Suche nach Fahrzeugen gemäß Kennzeichen, etc.) nicht mehr
							mit unterschiedlichen Fahrzeugtypen "herumschlagen"
		Source Code und weitere Informationen:
											  https://github.com/timo22h/gs-bk_sae-fahrzeugliste
*/

// Einbinden von Systembibliotheken
#include "stdafx.h"
#include <iostream>
#include <cmath>
#include "string.h"
using namespace std;

// Deklaration der globalen Methoden
void AusgabeMenu();

// Deklaration Klasse Fahrzeug
#pragma region Klasse Fahrzeug
class Fahrzeug {
protected:
	char kennzeichen[10];
	int erstzulassung;

public:
	Fahrzeug(char *kennzeichen, int jahr);
	Fahrzeug();
	virtual void Print();
	virtual Fahrzeug *Copy() = 0;
	char *Kennzeichen() { return kennzeichen; };
	//virtual double Steuer()=0;
	//virtual int TUEV()=0;
};
#pragma endregion

// Deklaration Klasse PKW - abgeleitet von der Klasse Fahrzeug
#pragma region Klasse PKW
class Pkw : public Fahrzeug
{
private:
	int hubraum;
	int leistung;
	int schadstoffklasse;

public:
	Pkw(char *kennzeichen, int jahr, int hubraum, int leistung, short schadstoffklasse = 0) :
		Fahrzeug(kennzeichen, erstzulassung), hubraum(hubraum), leistung(leistung), schadstoffklasse(schadstoffklasse) {};
	Pkw();
	virtual void Print();
	virtual Fahrzeug *Copy();
};
#pragma endregion

// Deklaration der Klasse Motorrad - abgeleitet von der Klasse Fahrzeug
#pragma region Klasse Motorrad
class Motorrad : public Fahrzeug {
private:
	int hubraum;

public:
	Motorrad(char *kennzeichen, int jahr, int hubraum) :
		Fahrzeug(kennzeichen, jahr), hubraum(hubraum) {};
	Motorrad();
	virtual void Print();
	virtual Fahrzeug *Copy();
};
#pragma endregion

// Deklaration von Klasse Node
#pragma region Klase Node
class Node {
private:
	Fahrzeug *object;
	Node *left, *right;
	int CmpNode(Node *);

public:
	Node(Fahrzeug *obj) { object = obj->Copy();
	left = right = NULL;
	}
	void Print();
	Fahrzeug *Suchen(char *kennzeichen);
	Node *AddObject(Fahrzeug *obj);
};
#pragma endregion

int main()
{
	AusgabeMenu();
}

inline Fahrzeug::Fahrzeug(char *k, int j)
{
	strcpy(kennzeichen, k);
	erstzulassung = j;
}

Fahrzeug::Fahrzeug()
{
	cout << "Kennzeichen: ";
	cin >> kennzeichen;
}

void Fahrzeug::Print()
{
	cout << endl << kennzeichen << endl;
	cout << "Erstzulassung: \t\t" <<
		erstzulassung << endl;
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
	cout << "5 = Berechnen von Steuern f�r ein bestimmtes Fahrzeug" << endl;

	cout << "Ihre Wahl: ";
}
