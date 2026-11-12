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
    double altitudes1[] = {65.0, 65.0, 65.5, 65.5, 67.0, 67.0, 67.0, 66.5, 66.5, 66.5}; // test1.txt
    double altitudes2[] = {794.7, 794.2, 794.2, 794.2, 793.2, 792.7, 792.7, 792.7, 792.7, 792.7}; // test2.txt

    assert(ascension(altitudes1, 10) == 2); // Verifie une ascension de 2 metres
    assert(ascension(altitudes2, 10) == 0); // Verifie une ascension de 0 metre

    assert(ascension(altitudes1, 0) == 0); // Verifie les tailles nulles
    assert(ascension(altitudes1, -2) == 0); // Verifie les tailles négatives
}
