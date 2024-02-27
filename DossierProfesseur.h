#pragma once
#include "Professeur.h"
class DossierProfesseur
{
public:
	Professeur* tete;
	DossierProfesseur();
    ~DossierProfesseur();
	void chargerProfesseurs();
	void supprimer(int id);
	void profil(int id) const;
	void afficherProfPlusEtudiants() const;
	void afficherCoursPlusDemande() const;
};