#include "DossierProfesseur.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>

DossierProfesseur::DossierProfesseur() : tete(nullptr) {
    
}

DossierProfesseur::~DossierProfesseur() 
{
    Professeur* courantProf = tete;
    while (courantProf != nullptr) {

        // Supprimer tous les cours du professeur courant
        Cours* courantCours = courantProf->listeCours;
        while (courantCours != nullptr) {
            Cours* tempCours = courantCours;
            courantCours = courantCours->suivant;
            //std::cout << "Cours libéré : "<< tempCours->sigle << std::endl;
            delete tempCours; // Libérer la mémoire du cours
        }
        
        // Supprimer tous les étudiants du professeur courant
        Etudiant* courantEtudiant = courantProf->listeEtudiants;
        while (courantEtudiant != nullptr) {
            Etudiant* tempEtudiant = courantEtudiant;
            courantEtudiant = courantEtudiant->suivant;
            //std::cout << "Etudiant libéré : "<< tempEtudiant->nom << std::endl;
            delete tempEtudiant;
        }
        
        Professeur* tempProf = courantProf;
        courantProf = courantProf->suivant;
        delete tempProf;
        
    }
    std::cout << "Deconstructeur ..." << std::endl;
    std::cout << "DossierProfesseur libere"<< std::endl;
}


void DossierProfesseur::chargerProfesseurs()
{
    std::ifstream fichier("donnees.txt");
    std::string ligne;
    Professeur* dernierProf = nullptr;

    if (!fichier.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier de données." << std::endl;
        return;
    }

    while (getline(fichier, ligne)) {
        if (ligne.empty()) continue; // Sauter les lignes vides

        Professeur* prof = new Professeur();
        prof->id = std::stoi(ligne); // ID du professeur

        getline(fichier, prof->nom); // Nom
        getline(fichier, prof->prenom); // Prénom

        // Lecture et ajout direct des cours
        Cours* dernierCours = nullptr;
        while (getline(fichier, ligne) && ligne != "#") {
            Cours* cours = new Cours();
            cours->sigle = ligne;
            if (dernierCours == nullptr) {
                prof->listeCours = cours;
            }
            else {
                dernierCours->suivant = cours;
            }
            dernierCours = cours;
        }

        // Lecture et ajout direct des étudiants
        Etudiant* dernierEtudiant = nullptr;
        while (getline(fichier, ligne) && ligne != "#") {
            Etudiant* etudiant = new Etudiant();
            etudiant->nom = ligne;
            if (dernierEtudiant == nullptr) {
                prof->listeEtudiants = etudiant;
            }
            else {
                dernierEtudiant->suivant = etudiant;
            }
            dernierEtudiant = etudiant;
        }

        // Ajout du professeur à la liste chaînée
        if (dernierProf == nullptr) {
            tete = prof;
        }
        else {
            dernierProf->suivant = prof;
        }
        dernierProf = prof;
    }

    fichier.close();
}

void DossierProfesseur::supprimer(int id) {
    Professeur* courantProf = tete;
    Professeur* prevProf = nullptr; // Pour garder la trace du professeur précédent

    while (courantProf != nullptr) {
        if (courantProf->id == id) {
            if (prevProf == nullptr) {
                tete = courantProf->suivant;
            }
            else {
                prevProf->suivant = courantProf->suivant;
            }

            // Libérer la mémoire associée au professeur à supprimer
            delete courantProf;
            std::cout << "" << std::endl;
            std::cout << "Professeur avec l'ID " << id << " supprime." << std::endl;
            std::cout << "" << std::endl;
            return; 
        }

        prevProf = courantProf;
        courantProf = courantProf->suivant;
    }

    std::cout << "Professeur avec l'ID " << id << " non trouve." << std::endl;
}

void DossierProfesseur::profil(int id) const {
    Professeur* courantProf = tete;

    // Parcourir la liste pour trouver le professeur avec l'ID donné
    while (courantProf != nullptr) {
        if (courantProf->id == id) {
            // Professeur trouvé, afficher ses informations
            std::cout << "" << std::endl;
            std::cout << "Profil -> " << "ID : " << courantProf->id << std::endl;
            std::cout << "Prenom / Nom : " << courantProf->prenom << " " << courantProf->nom << std::endl;

            std::cout << "" << std::endl;

            // Afficher les cours enseignés par le professeur
            std::cout << "Cours enseignes: " << std::endl;
            Cours* courantCours = courantProf->listeCours;
            while (courantCours != nullptr) {
                std::cout << "\t" << courantCours->sigle << std::endl;
                courantCours = courantCours->suivant;
            }
            std::cout << "" << std::endl;

            // Afficher les étudiants dirigés par le professeur
            std::cout << "Etudiants diriges: " << std::endl;
            Etudiant* courantEtudiant = courantProf->listeEtudiants;
            while (courantEtudiant != nullptr) {
                std::cout << "\t" << courantEtudiant->nom << std::endl;
                courantEtudiant = courantEtudiant->suivant;
            }

            std::cout << "" << std::endl;

            return;
        }
        courantProf = courantProf->suivant;
    }

    std::cout << "Professeur avec l'ID " << id << " non trouve." << std::endl;
}


void DossierProfesseur::afficherProfPlusEtudiants() const {
    std::vector<const Professeur*> profsMaxEtudiants;
    int maxEtudiants = 0;

    for (Professeur* courant = tete; courant != nullptr; courant = courant->suivant) {
        int count = 0;
        for (Etudiant* etudiant = courant->listeEtudiants; etudiant != nullptr; etudiant = etudiant->suivant) {
            ++count;
        }
        if (count > maxEtudiants) {
            maxEtudiants = count;
            profsMaxEtudiants.clear();
            profsMaxEtudiants.push_back(courant);
        }
        else if (count == maxEtudiants) {
            profsMaxEtudiants.push_back(courant);
        }
    }

    std::cout << "" << std::endl;
    if (!profsMaxEtudiants.empty()) {
        std::cout << "Professeur(s) avec le plus d'etudiants (" << maxEtudiants << " etudiants) :" << std::endl;
        for (const Professeur* prof : profsMaxEtudiants) {
            std::cout << prof->nom << " " << prof->prenom << std::endl;
        }
    }
    else {
        std::cout << "Aucun professeur trouve." << std::endl;
    }
    std::cout << "" << std::endl;
}

void DossierProfesseur::afficherCoursPlusDemande() const {
    std::map<std::string, int> compteurCours;

    for (Professeur* courant = tete; courant != nullptr; courant = courant->suivant) {
        for (Cours* cours = courant->listeCours; cours != nullptr; cours = cours->suivant) {
            compteurCours[cours->sigle]++;
        }
    }

    std::vector<std::string> coursMaxDemande;
    int maxDemande = 0;

    for (const auto& pair : compteurCours) {
        if (pair.second > maxDemande) {
            maxDemande = pair.second;
            coursMaxDemande.clear();
            coursMaxDemande.push_back(pair.first);
        }
        else if (pair.second == maxDemande) {
            coursMaxDemande.push_back(pair.first);
        }
    }
    std::cout << "" << std::endl;
    if (!coursMaxDemande.empty()) {
        std::cout << "Cours le(s) plus demande(s) (" << maxDemande << " demandes) :" << std::endl;
        for (const std::string& cours : coursMaxDemande) {
            std::cout << cours << std::endl;
        }
    }
    else {
        std::cout << "Aucun cours trouve." << std::endl;
    }
    std::cout << "" << std::endl;
}
