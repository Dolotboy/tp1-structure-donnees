#pragma once
#include <string>
#include "Cours.h"
#include "Etudiant.h"

class Professeur
{
public:
	int id;
	std::string nom;
	std::string prenom;
	Cours* listeCours;
	Etudiant* listeEtudiants;
	Professeur* suivant;

};

