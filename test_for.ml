print("=== Test FOR ===");

// Boucle for simple
for (int i = 0; i < 5; i = i + 1) {
    print(i);
}

print("=== Compte de 10 à 1 ===");
for (int j = 10; j > 0; j = j - 1) {
    print(j);
}

print("=== Nombres pairs ===");
for (int k = 0; k <= 10; k = k + 2) {
    print(k);
}

print("=== Carrés ===");
for (int n = 1; n <= 5; n = n + 1) {
    int carre = n * n;
    print(carre);
}

print("=== Somme avec for ===");
int total = 0;
for (int m = 1; m <= 100; m = m + 1) {
    total = total + m;
}
print("Somme de 1 à 100:");
print(total);
