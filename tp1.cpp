#include <iostream>
#include <fstream>
#include <string>
#include <fstream>
#include <sstream>
#include "DossierProfesseur.h"

void executerOperationsDepuisFichier(const std::string& cheminFichier, DossierProfesseur& dossier) {
    std::ifstream fichier(cheminFichier);
    std::string ligne;

    if (!fichier.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier " << cheminFichier << std::endl;
        return;
    }

    while (getline(fichier, ligne)) {
        std::istringstream iss(ligne);
        char operation;
        int id;

        iss >> operation;

        switch (operation) {
        case '-': // Supprimer un professeur
            if (iss >> id) {
                dossier.supprimer(id);
            }
            break;
        case '+': // Afficher le profil du professeur
            if (iss >> id) {
                dossier.profil(id);
            }
            break;
        case '>': // Ignorer le second caractère '>' et afficher le(s) professeur(s) avec le plus d'étudiants
            dossier.afficherProfPlusEtudiants();
            break;
        case '*': // Afficher le(s) cours le(s) plus demandé(s)
            dossier.afficherCoursPlusDemande();
            break;
        default:
            std::cerr << "Operation inconnue: " << operation << std::endl;
        }
    }

    fichier.close();
}

int main()
{

    DossierProfesseur dossier;
    dossier.chargerProfesseurs();
    
    executerOperationsDepuisFichier("operations.txt", dossier);
    
    //Tests 
    //dossier.supprimer(2);
    //dossier.supprimer(10);
    //dossier.supprimer(15);


    //// Parcourir et afficher la liste chaînée pour vérifier son contenu
    //Professeur* prof = dossier.tete;
    //while (prof != nullptr) {
    //    std::cout << "Professeur ID: " << prof->id << ", Nom: " << prof->nom << ", Prénom: " << prof->prenom << std::endl;

    //    // Afficher les cours du professeur
    //    Cours* cours = prof->listeCours;
    //    while (cours != nullptr) {
    //        std::cout << "\tCours: " << cours->sigle << std::endl;
    //        cours = cours->suivant;
    //    }

    //    // Afficher les étudiants du professeur
    //    Etudiant* etudiant = prof->listeEtudiants;
    //    while (etudiant != nullptr) {
    //        std::cout << "\tEtudiant: " << etudiant->nom << std::endl;
    //        etudiant = etudiant->suivant;
    //    }

    //    prof = prof->suivant; // Passer au professeur suivant dans la liste
    //    std::cout << std::endl; // Saut de ligne pour séparer les professeurs
    //}


    //dossier.afficherCoursPlusDemande();
    //dossier.afficherProfPlusEtudiants();
    //dossier.profil(3);

}

