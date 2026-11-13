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

void test_ascension()
{
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
}
