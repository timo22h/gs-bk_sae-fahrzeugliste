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
class Fahrzeug
{
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
	Pkw(char *kennzeichen, int jahr, int hubraum, int leistung, short schadstoffklasse = 0) : Fahrzeug(kennzeichen, erstzulassung), hubraum(hubraum), leistung(leistung), schadstoffklasse(schadstoffklasse){};
	Pkw();
	virtual void Print();
	virtual Fahrzeug *Copy();
};
#pragma endregion

// Deklaration der Klasse Motorrad - abgeleitet von der Klasse Fahrzeug
#pragma region Klasse Motorrad
class Motorrad : public Fahrzeug
{
private:
	int hubraum;

public:
	Motorrad(char *kennzeichen, int jahr, int hubraum) : Fahrzeug(kennzeichen, jahr), hubraum(hubraum){};
	Motorrad();
	virtual void Print();
	virtual Fahrzeug *Copy();
};
#pragma endregion

// Deklaration von Klasse Node
#pragma region Klase Node
class Node
{
private:
	Fahrzeug *object;
	Node *left, *right;
	int CmpNode(Node *);

public:
	Node(Fahrzeug *obj)
	{
		object = obj->Copy();
		left = right = NULL;
	}
	void Print();
	Fahrzeug *Suchen(char *kennzeichen);
	Node *AddObject(Fahrzeug *obj);
};
#pragma endregion

// Deklaration der Methoden
#pragma region Methoden Fahrzeug
inline Fahrzeug::Fahrzeug(char *k, int j)
{
	strcpy_s(kennzeichen, k);
	erstzulassung = j;
}

Fahrzeug::Fahrzeug()
{
	cout << "Kennzeichen: ";
	cin >> kennzeichen;
	cout << "Jahr der Erstzulassung: ";
	cin >> erstzulassung;
}

void Fahrzeug::Print()
{
	cout << endl
		 << kennzeichen << endl;
	cout << "Erstzulassung: \t\t" << erstzulassung << endl;
}
#pragma endregion

#pragma region Methoden PKW
Pkw::Pkw()
{
	cout << "Humbraum:\t\t";
	cin >> hubraum;
	cout << "Leistung:\t\t";
	cin >> leistung;
	cout << "Schadstoffklasse:[0..2]\t";
	cin >> schadstoffklasse;
}

void Pkw::Print()
{
	const char *Klassen[3] = {"Sauber", "Dreckschleuder", "Diesel"};

	// Ausgabe der Infos der Basisklasse Fahrzeug - ist unbedingt notwendig!
	Fahrzeug::Print();

	cout << "Typ: \t\t\tPKW\n";
	cout << "Humbraum:\t\t" << hubraum << endl;
	cout << "Leistung:\t\t" << leistung << endl;
	cout << "Schadstoffklasse:[0..2]\t" << Klassen[schadstoffklasse] << endl;
}

Fahrzeug *Pkw::Copy()
{
	// liefert identische Kopie des aktuellen Objekts
	return new Pkw(*this);
}
#pragma endregion

#pragma region Methoden Motorrad
Motorrad::Motorrad()
{
	// Konstruktor ohne Parameter
	cout << "Hubraum:\t\t";
	cin >> hubraum;
}

void Motorrad::Print()
{
	// Ausgabe der Infos der Basisklasse Fahrzeug - ist unbedingt notwendig!
	Fahrzeug::Print();
	cout << "Typ:\t\t\tMotorrad\n";
	cout << "Hubraum:\t\t" << hubraum << endl;
}

Fahrzeug *Motorrad::Copy()
{
	return new Motorrad(*this);
}
#pragma endregion

#pragma region binaerer Baum
inline int Node::CmpNode(Node *node2)
{
	return strcmp(object->Kennzeichen(), node2->object->Kennzeichen());
}

Node *Node::AddObject(Fahrzeug *obj)
{
	Node *root = this;
	int inserted = 0;
	Node *newnode = new Node(obj);
	// Erzeugen eines neuen Knotens mit einer identischen Kopie
	// des angegebenen Objekts; ruft automatisch die jeweilige
	// Copy-Funktion auf, siehe Konstruktor von Node

	if (root == NULL) // Es ex. noch keine Wurzel des Baums!
	{
		return newnode;
	}
	do
	{
		if (root->CmpNode(newnode) > 0)
		{
			// Gehört der neue Knoten in den linken oder rechten Teilbaum?
			if (root->left == NULL)
			{
				// Blattkonten gefunden?
				root->left = newnode;
				inserted = 1;
			}
			else
				root = root->left;
		}
		else if (root->right == NULL)
		{
			root->right = newnode;
			inserted = 1;
		}
		else
			root = root->right;
	} while (inserted == 0);
	return this;
}

Fahrzeug *Node::Suchen(char *kennzeichen)
{
	int suchstatus = 1;
	Node *Start = this;

	while (Start!=NULL && suchstatus!=0)
	{
		suchstatus = strcmp(kennzeichen, Start->object->Kennzeichen());
		if (suchstatus != 0) // Suche fotsetzen?
		{
			if (suchstatus < 0) // Kennzeichen kleiner
			{
				Start = Start->left;
			}
			else // Kennzeichen größer
			{
				Start = Start->right;
			}
		}
	}
	if (suchstatus != 0)
	{
		return NULL;
	}
	else
	{
		return Start->object;
	}
	
}

void Node::Print()
{
	if (left != NULL)
		left->Print(); // Daten des li. Teilbaums ausgeben . Teilbaums ausgeben
	object->Print();   // Ausgeben der Objektdaten
	if (right != NULL)
		right->Print(); // Daten des re. Teilbaums ausgeben
}
#pragma endregio

//Funktion um das Menu initial auszugeben
void AusgabeMenu()
{
	cout << "\nORGANISATION DER FAHRZEUGDATEN\n"
		 << endl;
	cout << "1 = Anlegen eines neuen PKWs" << endl;
	cout << "2 = Anlegen eines neuen Motorrads" << endl;
	cout << "3 = Suchen eines bestimmten Fahrzeugs" << endl;
	cout << "4 = Ausgabe aller Fahrzeuge" << endl;
	cout << "5 = Loeschen eines Fahrzeugs" << endl;

	// Eventuell Berechnen von Steuern
	cout << "6 = Berechnen von Steuern fuer ein bestimmtes Fahrzeug" << endl;

	cout << "Ihre Wahl: ";
}

int main()
{
	int eingabe;
	Node *root = NULL;

	do
	{
		AusgabeMenu();
		cin >> eingabe;

		switch (eingabe)
		{
		case 1:
			// Neuen PKW anlegen
			root = root->AddObject(new Pkw);
			break;
		case 2:
			// Neues Motorrad anlegen
			root = root->AddObject(new Motorrad);
			break;
		case 3:
			// Suche nach Kennzeichen
			char kennzeichen[10];
			Fahrzeug *Fz;
			cin >> kennzeichen;
			Fz = root->Suchen(kennzeichen);
			if (Fz != NULL)
			{
				Fz->Print();
			}
			break;
		case 4:
			// Ausgabe aller eingetragenen Fahrzeuge
			root->Print();
			break;
		case 5:
			// Löschen eines bestimmten Fahrzeugs anhand des Kennzeichens
			break;
		case 6:
			break;
		}
	} while (eingabe != 'x');
	system("cls");
	system("pause");
}