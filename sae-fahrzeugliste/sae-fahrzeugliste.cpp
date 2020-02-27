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
	char kennzeichen[11];
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
	Pkw(char *kennzeichen, int jahr, int hubraum, int leistung, short schadstoffklasse = 0) : Fahrzeug(kennzeichen, erstzulassung), hubraum(hubraum), leistung(leistung), schadstoffklasse(schadstoffklasse) {};
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
	Motorrad(char *kennzeichen, int jahr, int hubraum) : Fahrzeug(kennzeichen, jahr), hubraum(hubraum) {};
	Motorrad();
	virtual void Print();
	virtual Fahrzeug *Copy();
};
#pragma endregion

// Deklaration von Klasse Node
// Node ist die Liste in der das entsprechende Objekt gespeichert wird
// Ebenfalls wird der Vor- und Nachfolger des Objektes gespeichert
#pragma region Klase Node
class Node
{
private:
	Fahrzeug *object; // Das zu speichernde Objekt
	Node *left, *right; // Vor- und Nachfolger
	int CmpNode(Node *); // Vergleichen des Objektes

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
	// Konstruktor mit Parametern
	strcpy_s(kennzeichen, k);
	erstzulassung = j;
}

Fahrzeug::Fahrzeug()
{
	// Konstruktor ohne Parameter
	// Erstellen eines neuen Objektes mit der Angabe eines Kennzeichens 
	// im Format Stadt-Initialen-Nummer[1-4] (z.B. WN-TH-1996) 
	// und dem Jahr der Erstzulassung im Format JJJJ
	cout << "Kennzeichen: ";
	cin >> kennzeichen;
	cout << "Jahr der Erstzulassung: ";
	cin >> erstzulassung;
}

void Fahrzeug::Print()
{
	// Wird bei der Ausgabe eines bestimmten Fahrzeugs oder aller aufgerufen
	// gibt die Grundangaben eines Fahrzeugs, wie Kennzeichen und die Erstzulassung aus
	// danach folgt die objektspezifische Ausgabe
	cout << endl
		<< kennzeichen << endl;
	cout << "Erstzulassung: \t\t" << erstzulassung << endl;
}
#pragma endregion

#pragma region Methoden PKW
Pkw::Pkw()
{
	// Konstruktor ohne Parameter
	// Hinzufügen von weiteren Attributen bei einem neuen Objekt
	// Wurde ein PKW ausgewählt, werden erst die allgemeinen Infos abgefragt
	// dann wird der Benutzer aufgefordert die PKW spezifischen Infos wie 
	// Hubraum, Leistung oder die Schadstoffklasse anzugeben
	cout << "Humbraum:\t\t";
	cin >> hubraum;
	cout << "Leistung:\t\t";
	cin >> leistung;
	cout << "Schadstoffklasse:[0..2]\t";
	cin >> schadstoffklasse;
}

void Pkw::Print()
{
	// Ausgabe der PKW spezifischen Attribute
	// Wird aufgerufen, wenn ein PKW per Suche gefunden wurde
	// oder alle Fahrzeuge ausgegeben werden sollen

	// Die Schadstoffklasse wird jeweils der Nummer zugeordnet
	// 0=Sauber, 1=Dreckschleuder, 2=Diesel
	const char *Klassen[3] = { "Sauber", "Dreckschleuder", "Diesel" };

	// Ausgabe der Infos der Basisklasse Fahrzeug
	// Erst werden die Infos der Basisklasse Fahrzeug ausgegeben, dann die des PKWs
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
	// Ausgabe der Infos der Basisklasse Fahrzeug
	// Gleiche wie beim PKW
	Fahrzeug::Print();
	cout << "Typ:\t\t\tMotorrad\n";
	cout << "Hubraum:\t\t" << hubraum << endl;
}

Fahrzeug *Motorrad::Copy()
{
	// liefert identische Kopie des aktuellen Objekts
	return new Motorrad(*this);
}
#pragma endregion

#pragma region Liste
inline int Node::CmpNode(Node *node2)
{
	// Das Objekt wird mit einem bereits in der Liste gespeicherten Objekt vergleichen
	// um zu entscheiden ob es davor oder danach abgespeichert werden muss
	return strcmp(object->Kennzeichen(), node2->object->Kennzeichen());
}

Node *Node::AddObject(Fahrzeug *obj)
{
	Node *root = this; // aktuelle Liste
	int inserted = 0; // Abgleich ob Objekt nun gespeichert wurde
	Node *newnode = new Node(obj);
	// Erzeugen eines neuen Knotens mit einer identischen Kopie
	// des angegebenen Objekts
	// ruft automatisch die jeweilige Copy-Funktion auf, siehe Konstruktor von Node

	if (root == NULL) // Es ex. noch kein Objekt in der Liste!
	{
		return newnode;
	}
	do
	{
		if (root->CmpNode(newnode) > 0)
		{
			// Gehört das neue Objekt in den linken oder rechten Teil der Liste?
			if (root->left == NULL)
			{
				// Knotenpunkt gefunden?
				root->left = newnode;
				inserted = 1;
			}
			else
				root = root->left;
		}
		// Gehört das neue Objekt in den rechten Teil der Liste, wird es hier eingefügt
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
	Node *Start = this; // Aktuelles Objekt

	// Solange das aktuelle Objekt nicht leer ist und der Suchstatus ungleich 0, 
	// suche nach dem Objekt in der Liste
	while (Start != NULL && suchstatus != 0)
	{
		// Vergleiche Such-Kennzeichen mit Objekt Kennzeichen
		// Stimmen beide Kennzeichen überein, wird suchstatus auf 0 gesetzt
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
		return NULL; // Kennzeichen konnte nicht gefunden werden
	}
	else
	{
		return Start->object; // Objekt mit dem gesuchten Kennzeichen wird zurückgegeben
	}
}

void Node::Print()
{
	if (left != NULL)
		left->Print(); // Daten des li. Teilbaums ausgeben
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
	cout << "7 = Programm beenden" << endl;

	cout << "\nIhre Wahl: ";
}

int main()
{
	int eingabe;
	Node* root = NULL;

	do
	{
		AusgabeMenu();
		cin >> eingabe;

		switch (eingabe)
		{
		case 1:
			// Neuen PKW anlegen
			root = root->AddObject(new Pkw);
			cout << "\nEs wurde erfolgreich ein neuer PKW angelegt" << endl;
			break;
		case 2:
			// Neues Motorrad anlegen
			root = root->AddObject(new Motorrad);
			cout << "\nEs wurde erfolgreich ein neues Motorrad angelegt" << endl;
			break;
		case 3:
			// Suche nach Kennzeichen und deren Ausgabe
			char kennzeichen[11];
			Fahrzeug* Fz;
			cout << "Kennzeichen: ";
			cin >> kennzeichen;
			Fz = root->Suchen(kennzeichen);
			if (Fz != NULL)
			{
				Fz->Print();
			}
			else
			{
				cout << "\nEs konnte leider kein Fahrzeug mit dem gewünschten Kennzeichen gefunden werden!\n";
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
		case 7:
			delete root;
			break;
		}
	} while (eingabe != NULL && eingabe != 7);
	system("pause");
}