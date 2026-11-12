/*
Auteur(s):
Date:

Ce module contient les implementations des fonctions d'analyse de traces GPS

*/

#define _CRT_SECURE_NO_WARNINGS

// Librairies standard
#include <stdio.h>
#include <math.h>

#include "config.h"
#include "matrac_lib.h"

int lire_donnees_gps(char nom_fichier[],
	                 double tab_latitudes[],
	                 double tab_longitudes[],
	                 double tab_altitudes[],
	                 int taille_max) {
	int nb_point = 0;						            // nombre de points trouves
	char ligne[LONGUEUR_MAX_LIGNE];			            // chaine de caractere contenant la balise
	FILE* fp;								            // pointeur au fichier a lire
	int no, an, mois, jour, heure, minute, seconde;		// informations lues du fichier
	double latitude, longitude, altitude;

	// ouverture du fichier et verification du succes de l'ouverture
	fp = fopen(nom_fichier, "r"); // en mode lecture seulement

	if (fp == NULL) {
		nb_point = -1;
	} else {
		// sauter l'en-tete
		if (fgets(ligne, LONGUEUR_MAX_LIGNE - 1, fp) == NULL) {
			nb_point = -1;

			// continuer la lecture si fichier n'est pas vide
		} else {

			// boucle de lecture principale de chaque point (un par ligne)
			while ((fgets(ligne, LONGUEUR_MAX_LIGNE - 1, fp) != NULL) && (nb_point < taille_max)) {
				// lecture d'un point et identification des 10 champs attendus:
				// No,Latitude,Longitude,Altitude,Date(a/m/j),Time(h:m:s)
				if (sscanf(ligne, "%d,%lf,%lf,%lf,%d/%d/%d,%d:%d:%d", &no,
				                                                      &latitude,
				                                                      &longitude,
				                                                      &altitude,
				                                                      &an,
				                                                      &mois,
				                                                      &jour,
				                                                      &heure,
				                                                      &minute,
				                                                      &seconde) == 10){

					//si decodage correct,mise en memoire de la latitude, longitude,altitude
					tab_latitudes[nb_point] = latitude;
					tab_longitudes[nb_point] = longitude;
					tab_altitudes[nb_point] = altitude;

					// incrementer le nombre de points correctement lus
					nb_point++;
				}
			}
		}
		// fermeture du fichier
		fclose(fp);
	}

	if (nb_point >= 0) {
		printf("\n...%d points lus\n", nb_point);
	}else {
		printf("\n...probleme de lecture du fichier\n");
	}
	//renvoi du nombre de points trouves
	return nb_point;

}

// implementations des fonctions de matrac_lib (c.f. prototype et doc dans matrac_lib.h)
double convertir_en_radian(double angle) {
	return angle * PI / 180.0;
}

double distance_entre_2_points(double latitude1,
							   double longitude1,
							   double latitude2,
							   double longitude2,
							   double altidute1,
							   double altidute2) {

	// Convertir les mesures brutes en radians et kilomètres
	double latitude1_rad = convertir_en_radian(latitude1);
	double longitude1_rad = convertir_en_radian(longitude1);
	double altitude1_km = altidute1 / 1000.0;

	double latitude2_rad = convertir_en_radian(latitude2);
	double longitude2_rad = convertir_en_radian(longitude2);
	double altitude2_km = altidute2 / 1000.0;

	// Calculer la distance sans prendre en compte l'altitude
	double d = RAYON_TERRE * 2 * asin(sqrt(pow(sin((latitude1_rad - latitude2_rad)/2), 2) + cos(latitude1_rad) * cos(latitude2_rad) * pow(sin((longitude1_rad - longitude2_rad)/2), 2)));

	// Ajouter l'influence de l'altitude
	double d_totale = sqrt(pow(d, 2) + pow(altitude2_km - altitude1_km, 2));

	return d_totale;
}

void afficher_tableau(double tableau[], int nb_valeurs) {
	// Obligatoire pour respecter l'énoncé
	if (nb_valeurs <= 0) {
		return;
	}

	for (int i = 0; i < nb_valeurs; i++) {
		printf("%f\n", tableau[i]);
	}
}

double ascension(double tab_altitudes[], int taille)
{
	double total;       // Total des montees
	double difference;  // Difference entre deux altitudes
	int i;              // Compteur pour parcourir le tableau

	total = 0;          // Initialiser le total a 0

	if(taille <= 0)     // Verifier si la taille est nulle ou negative
	{
		return 0;       // Retourner 0 si la taille est invalide
	}

	for(i = 1; i < taille; i++) // Parcourir les altitudes
	{
		difference = tab_altitudes[i] - tab_altitudes[i - 1]; // Calculer la difference

		if(difference > 0) // Verifier si c'est une montee
		{
			total = total + difference; // Ajouter la montee au total
		}
	}

	return total; // Retourner le total des montees en metres
}