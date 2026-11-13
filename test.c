#define _CRT_SECURE_NO_WARNINGS
#include "test.h"
#include "matrac_lib.h"
#include <stdio.h>
#include <assert.h>
#include "config.h"

// Vous coderez ici vos fonctions de test
#define TOLERANCE 0.01
void test_convertir_en_radian() {
    assert((convertir_en_radian(180) >= 3.14 - TOLERANCE) && (convertir_en_radian(180) <= 3.14 + TOLERANCE));
    assert((convertir_en_radian(0) >= 0 - TOLERANCE) && (convertir_en_radian(0) <= 0 + TOLERANCE));
    assert((convertir_en_radian(90) >= 1.57 - TOLERANCE) && (convertir_en_radian(90) <= 1.57 + TOLERANCE));
}

void test_distance_entre_2_points() {
    assert((distance_entre_2_points(45.37,75.80,45.38, 75.80,100,100) >= 1.11 - TOLERANCE)
        && (distance_entre_2_points(45.37,75.80,45.38, 75.80,100,100) <= 1.11 + TOLERANCE));

    assert((distance_entre_2_points(45.37,75.80,45.37, 75.81,100,100) >= 0.78 - TOLERANCE)
        && (distance_entre_2_points(45.37,75.80,45.37, 75.81,100,100) <= 0.78 + TOLERANCE));

    assert((distance_entre_2_points(45.37,75.80,45.37, 75.80,100,1000) >= 0.90 - TOLERANCE)
        && (distance_entre_2_points(45.37,75.80,45.37, 75.80,100,1000) <= 0.90 + TOLERANCE));

    assert((distance_entre_2_points(45.37,75.80,45.38, 75.81,100,1000) >= 1.63 - TOLERANCE)
        && (distance_entre_2_points(45.37,75.80,45.38, 75.81,100,1000) <= 1.63 + TOLERANCE));
}

void test_afficher_afficher_tableau() {
    // Impossible de (facilement) tester une fonction qui ne fait qu'afficher
    double tableau[] = {1, 2, 3, 4, 5};
    printf("test::test_afficher_afficher_tableau()\n");
    afficher_tableau(tableau, 5);
    printf("\n");
    afficher_tableau(tableau, 3);
    printf("\n");
    afficher_tableau(tableau, 0);
    printf("\n");
    afficher_tableau(tableau, -1);
    printf("fin test::test_afficher_afficher_tableau()\n");
}

void test_ascension() {
    // Inutiles pour ce test
    double tab_latitudes[NB_MAX_POINT];
    double tab_longitudes[NB_MAX_POINT];

    double altitudes1[NB_MAX_POINT];
    double altitudes2[NB_MAX_POINT];

    lire_donnees_gps("test1.txt", tab_latitudes, tab_longitudes, altitudes1, NB_MAX_POINT); // test1.txt
    lire_donnees_gps("test2.txt", tab_latitudes, tab_longitudes, altitudes2, NB_MAX_POINT); // test2.txt

    assert((ascension(altitudes1, 10) >= 2 - TOLERANCE)
        && (ascension(altitudes1, 10) <= 2 + TOLERANCE)); // Verifie une ascension de 2 metres

    assert((ascension(altitudes1, 0) >= 0 - TOLERANCE)
        && (ascension(altitudes1, 0) <= 0 + TOLERANCE)); // Verifie les tailles nulles

    assert((ascension(altitudes1, -2) >= 0 - TOLERANCE)
        && (ascension(altitudes1, -2) <= 0 + TOLERANCE)); // Verifie les tailles négatives

    assert((ascension(altitudes2, 2482) >= 1368.8 - TOLERANCE)
        && (ascension(altitudes2, 2482) <= 1368.8 + TOLERANCE)); // Verifie une ascension de 0 metre

void test_distance_totale() {
    // Appel de la fonction lire_donnees_gps pour charger test 1
    double tab_latitudes[NB_MAX_POINT];
    double tab_longitudes[NB_MAX_POINT];
    double tab_altitudes[NB_MAX_POINT];

    int taille = lire_donnees_gps("test1.txt", tab_latitudes, tab_longitudes, tab_altitudes, NB_MAX_POINT);

    assert((distance_totale(tab_latitudes, tab_longitudes, tab_altitudes, taille, 0, 9)) >= 0.45 - TOLERANCE
        && (distance_totale(tab_latitudes, tab_longitudes, tab_altitudes, taille, 0, 9)) <= 0.45 + TOLERANCE);

    assert((distance_totale(tab_latitudes, tab_longitudes, tab_altitudes, taille, 3, 6)) >= 0.2 - TOLERANCE
        && (distance_totale(tab_latitudes, tab_longitudes, tab_altitudes, taille, 3, 6)) <= 0.2 + TOLERANCE);

    assert((distance_totale(tab_latitudes, tab_longitudes, tab_altitudes, taille, 6, 3)) >= 0 - TOLERANCE
        && (distance_totale(tab_latitudes, tab_longitudes, tab_altitudes, taille, 6, 3)) <= 0 + TOLERANCE);

    assert((distance_totale(tab_latitudes, tab_longitudes, tab_altitudes, taille, -1, 6)) >= 0 - TOLERANCE
        && (distance_totale(tab_latitudes, tab_longitudes, tab_altitudes, taille, -1, 6)) <= 0 + TOLERANCE);

    assert((distance_totale(tab_latitudes, tab_longitudes, tab_altitudes, taille, 20, 6)) >= 0 - TOLERANCE
        && (distance_totale(tab_latitudes, tab_longitudes, tab_altitudes, taille, 20, 6)) <= 0 + TOLERANCE);

    assert((distance_totale(tab_latitudes, tab_longitudes, tab_altitudes, taille, 3, 16)) >= 0 - TOLERANCE
        && (distance_totale(tab_latitudes, tab_longitudes, tab_altitudes, taille, 3, 16)) <= 0 + TOLERANCE);

    assert((distance_totale(tab_latitudes, tab_longitudes, tab_altitudes, taille, 3, -1)) >= 0 - TOLERANCE
        && (distance_totale(tab_latitudes, tab_longitudes, tab_altitudes, taille, 3, -1)) <= 0 + TOLERANCE);

    // Appel de la fonction lire_donnees_gps pour charger test 2
    taille = lire_donnees_gps("test2.txt", tab_latitudes, tab_longitudes, tab_altitudes, NB_MAX_POINT);

    assert((distance_totale(tab_latitudes, tab_longitudes, tab_altitudes, taille, 100, 1000)) >= 36.35 - TOLERANCE
        && (distance_totale(tab_latitudes, tab_longitudes, tab_altitudes, taille, 100, 1000)) <= 36.35 + TOLERANCE);
}

void test_pente_maximale() {
    // Appel de la fonction lire_donnees_gps pour charger test 1
    double tab_latitudes[NB_MAX_POINT];
    double tab_longitudes[NB_MAX_POINT];
    double tab_altitudes[NB_MAX_POINT];

    lire_donnees_gps("test1.txt", tab_latitudes, tab_longitudes, tab_altitudes, NB_MAX_POINT);

    assert((pente_maximale(tab_latitudes, tab_longitudes, tab_altitudes, 10, 3)) >= 0.599 - TOLERANCE
        && (pente_maximale(tab_latitudes, tab_longitudes, tab_altitudes, 10, 3)) <= 0.599 + TOLERANCE);

    assert((pente_maximale(tab_latitudes,tab_longitudes, tab_altitudes, 10, 1)) >= 1.194 - TOLERANCE
        && (pente_maximale(tab_latitudes, tab_longitudes, tab_altitudes, 10, 1)) <= 1.194 + TOLERANCE);

    assert((pente_maximale(tab_latitudes, tab_longitudes, tab_altitudes, 10, 10)) >= 0 - TOLERANCE
        && (pente_maximale(tab_latitudes, tab_longitudes, tab_altitudes, 10, 10)) <= 0 + TOLERANCE);

    assert((pente_maximale(tab_latitudes, tab_longitudes, tab_altitudes, 10, -2)) >= 0 - TOLERANCE
        && (pente_maximale(tab_latitudes, tab_longitudes, tab_altitudes, 10, -2)) <= 0 + TOLERANCE);

    assert((pente_maximale(tab_latitudes, tab_longitudes, tab_altitudes, 10, 0)) >= 0 - TOLERANCE
        && (pente_maximale(tab_latitudes, tab_longitudes, tab_altitudes, 10, 0)) <= 0 + TOLERANCE);

    // Appel de la fonction lire_donnees_gps pour charger test 2
    lire_donnees_gps("test2.txt", tab_latitudes, tab_longitudes, tab_altitudes, NB_MAX_POINT);

    assert((pente_maximale(tab_latitudes, tab_longitudes, tab_altitudes, 2482, 50)) >= 6.116 - TOLERANCE
        && (pente_maximale(tab_latitudes, tab_longitudes, tab_altitudes, 2482, 50)) <= 6.116 + TOLERANCE);
}
