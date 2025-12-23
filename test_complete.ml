/*
 * Programme complet MiniLang
 * Démonstration de toutes les fonctionnalités
 */

print("=== PROGRAMME COMPLET ===");

// Variables
int n = 10;
int compteur = 0;

// Calcul avec if
print("--- Nombres pairs de 0 à 10 ---");
for (int i = 0; i <= n; i = i + 1) {
    if (i % 2 == 0) {
        print(i);
        compteur = compteur + 1;
    }
}
print("Nombre de pairs trouvés:");
print(compteur);

// Tableau et recherche
print("--- Recherche dans un tableau ---");
int nombres[5];
nombres[0] = 3;
nombres[1] = 7;
nombres[2] = 12;
nombres[3] = 8;
nombres[4] = 15;

int cherche = 12;
int trouve = 0;
int position = -1;

for (int j = 0; j < 5; j = j + 1) {
    if (nombres[j] == cherche) {
        trouve = 1;
        position = j;
    }
}

if (trouve) {
    print("Nombre trouvé à la position:");
    print(position);
} else {
    print("Nombre non trouvé");
}

// Maximum d'un tableau
print("--- Maximum d'un tableau ---");
int valeurs[5];
valeurs[0] = 23;
valeurs[1] = 45;
valeurs[2] = 12;
valeurs[3] = 67;
valeurs[4] = 34;

int max = valeurs[0];
for (int k = 1; k < 5; k = k + 1) {
    if (valeurs[k] > max) {
        max = valeurs[k];
    }
}
print("Maximum:");
print(max);

// Factorielle avec while
print("--- Factorielle de 5 ---");
int fact = 5;
int resultat = 1;
int temp = fact;
while (temp > 0) {
    resultat = resultat * temp;
    temp = temp - 1;
}
print(resultat);

// Suite de Fibonacci
print("--- Suite de Fibonacci (10 premiers) ---");
int fib[10];
fib[0] = 0;
fib[1] = 1;

for (int m = 2; m < 10; m = m + 1) {
    fib[m] = fib[m - 1] + fib[m - 2];
}

for (int p = 0; p < 10; p = p + 1) {
    print(fib[p]);
}

// Tri simple (bubble sort partiel)
print("--- Tri d'un petit tableau ---");
int arr[3];
arr[0] = 30;
arr[1] = 10;
arr[2] = 20;

print("Avant tri:");
print(arr[0]);
print(arr[1]);
print(arr[2]);

// Tri
if (arr[0] > arr[1]) {
    int tmp = arr[0];
    arr[0] = arr[1];
    arr[1] = tmp;
}
if (arr[1] > arr[2]) {
    int tmp2 = arr[1];
    arr[1] = arr[2];
    arr[2] = tmp2;
}
if (arr[0] > arr[1]) {
    int tmp3 = arr[0];
    arr[0] = arr[1];
    arr[1] = tmp3;
}

print("Après tri:");
print(arr[0]);
print(arr[1]);
print(arr[2]);

// Calculs avec float
print("--- Calculs géométriques ---");
float pi = 3.14159;
float rayon = 5.0;
float circonference = 2.0 * pi * rayon;
float aire = pi * rayon * rayon;

print("Pour un cercle de rayon 5:");
print(circonference);
print(aire);

print("=== FIN DU PROGRAMME ===");
