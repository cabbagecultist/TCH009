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

double distance_totale(double tab_latitudes[], double tab_longitudes[], double tab_altitudes[], int taille, int debut, int fin) {

	double d_tot = 0;

	// Si valeurs négatives, programme s'arrête
	if (debut < 0 || fin < 0) {
		return 0;
	}
	// Sinon si valeurs ne se retrouvent pas dans la taille, programme s'arrête
	else if (debut >= taille || fin >= taille) {
		return 0;
	}
	// Sinon si début = fin ou début > fin, distance totale = 0 automatiquement
	else if (debut == fin || debut > fin) {
		d_tot = 0;

    // Sinon, procéder pour trouver la distance totale
	} else {
		// Parcourir tous les points se situant entre début et fin
		for (int i = debut; i < fin; i++) {

			// Distance totale = somme totale de chaque segment de 2 points
			d_tot = d_tot + distance_entre_2_points(tab_latitudes[i], tab_longitudes[i], tab_latitudes[i+1], tab_longitudes[i+1], tab_altitudes[i], tab_altitudes[i+1]);
		}
	}
	return d_tot;
}

double pente_maximale(double tab_latitudes[], double tab_longitudes[], double tab_altitudes[], int taille, int taille_fenetre) {

	double h;                  // Fluctuation de l'altitude (delta h)
	double d;                 // Distance accomplie (delta d)
	double pente;            // Pente de chaque point
	double pente_max = 0;   // Pente maximale

	// Si la taille fenêtre est plus petite ou égale à 0, il n'est pas possible de calculer la pente, donc programme s'arrête
	if (taille_fenetre <= 0) {
		return 0;
	}
	// Sinon, si pas assez de points pour calculer la pente, programme s'arrête
	else if (taille <= 2 * taille_fenetre) {
		return 0;
	}
	// Sinon, procéder pour trouver la pente maximale
	else {
		// Parcourir tous les points se trouvant dans l'intervalle de la taille fenêtre
		for (int i = taille_fenetre; i <= taille - taille_fenetre - 1; i++) {
			// Point final de la fenêtre - point initial de la fenêtre
			h = tab_altitudes[i + taille_fenetre] - tab_altitudes[i - taille_fenetre];

			// Appel de la fonction distance_totale pour calculer la distance totale entre un point de début et un point de fin
			d = distance_totale(tab_latitudes, tab_longitudes, tab_altitudes, taille, i - taille_fenetre, i + taille_fenetre);

			// Convertir d en mètres, car la distance totale donne des kilomètres
			d = d * 1000;

			// Si la distance = 0, la pente = 0 automatiquement pour éviter la division par 0
			if (d == 0) {
				pente = 0;
			}
			// Sinon, procéder avec le calcul de la pente
			else {
				pente = h / d;
			}
			// Pour trouver la pente maximale
			if (pente > pente_max) {
				pente_max = pente;
			}

		}
		// Convertir pente maximale en pourcentage
		pente_max = pente_max * 100;

		return pente_max;
	}
}

void calculer(double tab_latitudes[], double tab_longitudes[], double tab_altitudes[], int taille, int taille_fenetre) {

	printf("Nombre de points pour le calcul de la pente : ");  // Demander à l'utilisateur d'entrer une taille fenêtre
	scanf("%d", &taille_fenetre);                             // Lire la taille fenêtre

	// Appel de la fonction pente_maximale pour calculer la pente maximale
	double p_max = pente_maximale(tab_latitudes, tab_longitudes, tab_altitudes, taille, taille_fenetre);

	// Afficher la pente maximale
	printf("%.3lf %%\n", p_max);
}
