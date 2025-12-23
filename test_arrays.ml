print("=== Test TABLEAUX ===");

// Créer un tableau d'entiers
int nombres[5];

// Remplir le tableau
nombres[0] = 10;
nombres[1] = 20;
nombres[2] = 30;
nombres[3] = 40;
nombres[4] = 50;

// Afficher le tableau
print("Contenu du tableau:");
print(nombres[0]);
print(nombres[1]);
print(nombres[2]);
print(nombres[3]);
print(nombres[4]);

print("=== Tableau avec boucle ===");
int valeurs[10];

// Remplir avec une boucle
for (int i = 0; i < 10; i = i + 1) {
    valeurs[i] = i * i;
}

// Afficher avec une boucle
print("Carrés de 0 à 9:");
for (int j = 0; j < 10; j = j + 1) {
    print(valeurs[j]);
}

print("=== Somme d'un tableau ===");
int data[5];
data[0] = 5;
data[1] = 10;
data[2] = 15;
data[3] = 20;
data[4] = 25;

int somme = 0;
for (int k = 0; k < 5; k = k + 1) {
    somme = somme + data[k];
}
print("Somme du tableau:");
print(somme);

print("=== Tableaux de float ===");
float temperatures[3];
temperatures[0] = 20.5;
temperatures[1] = 22.3;
temperatures[2] = 19.8;

print("Températures:");
print(temperatures[0]);
print(temperatures[1]);
print(temperatures[2]);
