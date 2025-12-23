print("=== Test IF/ELSE ===");

int age = 18;

// If simple
if (age >= 18) {
    print("Vous êtes majeur");
}

// If/else
int score = 75;
if (score >= 60) {
    print("Vous avez réussi");
} else {
    print("Vous avez échoué");
}

// If/else imbriqués
int note = 85;
if (note >= 90) {
    print("Excellent");
} else {
    if (note >= 75) {
        print("Bien");
    } else {
        print("Peut mieux faire");
    }
}

// Avec opérateurs logiques
int x = 10;
int y = 20;

if (x > 0 && y > 0) {
    print("Les deux sont positifs");
} else {
    print("Au moins un est négatif");
}

// Comparaisons multiples
int temperature = 25;

if (temperature > 30) {
    print("Il fait chaud");
} else {
    if (temperature > 20) {
        print("Il fait bon");
    } else {
        print("Il fait frais");
    }
}
