# MiniLang - Langage de programmation complet

## 🎉 Fonctionnalités complètes

### ✨ Types de données
- `int` - Entiers
- `float` - Nombres décimaux
- `str` - Chaînes de caractères
- Tableaux pour int et float

### 🔢 Opérateurs arithmétiques
- `+` Addition
- `-` Soustraction
- `*` Multiplication
- `/` Division
- `%` Modulo

### 🔍 Opérateurs de comparaison
- `==` Égal
- `!=` Différent
- `<` Plus petit
- `>` Plus grand
- `<=` Plus petit ou égal
- `>=` Plus grand ou égal

### 🧠 Opérateurs logiques
- `&&` ET logique
- `||` OU logique
- `!` NOT logique

### 🎛️ Structures de contrôle
- `if` / `else` - Conditions
- `while` - Boucle tant que
- `for` - Boucle avec compteur

### 📊 Tableaux
- Déclaration: `int arr[10];`
- Accès: `arr[0] = 5;`
- Support pour int et float

### 💬 Commentaires
- `//` Commentaire sur une ligne
- `/* ... */` Commentaire multiligne

---

## 📖 Guide de syntaxe

### Variables

```c
int age = 25;
float prix = 19.99;
str nom = "Alice";
```

### Tableaux

```c
// Déclaration
int nombres[5];
float temperatures[10];

// Utilisation
nombres[0] = 10;
nombres[1] = 20;

int valeur = nombres[0];
print(nombres[1]);
```

### Opérateurs de comparaison

```c
int a = 10;
int b = 20;

if (a == 10) { print("a vaut 10"); }
if (a != b) { print("a différent de b"); }
if (a < b) { print("a plus petit"); }
if (a > 5) { print("a plus grand que 5"); }
if (a <= 10) { print("a inférieur ou égal"); }
if (b >= 20) { print("b supérieur ou égal"); }
```

### Opérateurs logiques

```c
int x = 5;
int y = 10;

// ET logique
if (x > 0 && y > 0) {
    print("Les deux positifs");
}

// OU logique
if (x == 5 || y == 5) {
    print("Au moins un vaut 5");
}

// NOT logique
if (!x) {
    print("x est faux");
}

// Expressions complexes
if ((x > 0 && y > 0) || x == 10) {
    print("Condition complexe");
}
```

### Structures if/else

```c
// If simple
if (age >= 18) {
    print("Majeur");
}

// If/else
if (score >= 50) {
    print("Réussi");
} else {
    print("Échoué");
}

// If imbriqués
if (note >= 90) {
    print("Excellent");
} else {
    if (note >= 75) {
        print("Bien");
    } else {
        print("Passable");
    }
}
```

### Boucle while

```c
int i = 0;
while (i < 10) {
    print(i);
    i = i + 1;
}

// Avec condition complexe
int x = 0;
int y = 10;
while (x < 5 && y > 0) {
    x = x + 1;
    y = y - 1;
}
```

### Boucle for

```c
// Boucle simple
for (int i = 0; i < 10; i = i + 1) {
    print(i);
}

// Compte à rebours
for (int j = 10; j > 0; j = j - 1) {
    print(j);
}

// Nombres pairs
for (int k = 0; k <= 20; k = k + 2) {
    print(k);
}

// Avec tableaux
int arr[5];
for (int m = 0; m < 5; m = m + 1) {
    arr[m] = m * m;
}
```

### Commentaires

```c
// Commentaire sur une ligne

/*
   Commentaire
   sur plusieurs
   lignes
*/

int x = 5;  // Commentaire en fin de ligne
```

---

## 🎯 Exemples complets

### Exemple 1: Recherche dans un tableau

```c
int nombres[5];
nombres[0] = 10;
nombres[1] = 25;
nombres[2] = 30;
nombres[3] = 15;
nombres[4] = 40;

int cherche = 30;
int trouve = 0;
int position = -1;

for (int i = 0; i < 5; i = i + 1) {
    if (nombres[i] == cherche) {
        trouve = 1;
        position = i;
    }
}

if (trouve) {
    print("Trouvé à la position:");
    print(position);
} else {
    print("Non trouvé");
}
```

### Exemple 2: Calcul du maximum

```c
int valeurs[5];
valeurs[0] = 23;
valeurs[1] = 45;
valeurs[2] = 12;
valeurs[3] = 67;
valeurs[4] = 34;

int max = valeurs[0];
for (int i = 1; i < 5; i = i + 1) {
    if (valeurs[i] > max) {
        max = valeurs[i];
    }
}

print("Maximum:");
print(max);
```

### Exemple 3: Factorielle

```c
int n = 5;
int resultat = 1;
int i = n;

while (i > 0) {
    resultat = resultat * i;
    i = i - 1;
}

print("Factorielle de 5:");
print(resultat);
```

### Exemple 4: Suite de Fibonacci

```c
int n = 10;
int fib[10];
fib[0] = 0;
fib[1] = 1;

for (int i = 2; i < n; i = i + 1) {
    fib[i] = fib[i - 1] + fib[i - 2];
}

print("Suite de Fibonacci:");
for (int j = 0; j < n; j = j + 1) {
    print(fib[j]);
}
```

### Exemple 5: Tri simple

```c
int arr[3];
arr[0] = 30;
arr[1] = 10;
arr[2] = 20;

// Tri bubble sort simplifié
if (arr[0] > arr[1]) {
    int tmp = arr[0];
    arr[0] = arr[1];
    arr[1] = tmp;
}
if (arr[1] > arr[2]) {
    int tmp = arr[1];
    arr[1] = arr[2];
    arr[2] = tmp;
}
if (arr[0] > arr[1]) {
    int tmp = arr[0];
    arr[0] = arr[1];
    arr[1] = tmp;
}

print(arr[0]);
print(arr[1]);
print(arr[2]);
```

---

## 🔧 Compilation et exécution

### Compilation

```bash
gcc -std=gnu99 minilang_advanced.c -o minilang
```

### Exécution

```bash
./minilang mon_programme.ml
```

### Avec Make

```bash
make
make test-all
```

---

## 📊 Priorité des opérateurs

1. **Parenthèses** `()` - Plus haute priorité
2. **NOT logique** `!`
3. **Multiplication, Division, Modulo** `*`, `/`, `%`
4. **Addition, Soustraction** `+`, `-`
5. **Comparaisons** `<`, `>`, `<=`, `>=`
6. **Égalité** `==`, `!=`
7. **ET logique** `&&`
8. **OU logique** `||` - Plus basse priorité

---

## 📝 Règles importantes

### Syntaxe
- Chaque instruction se termine par `;`
- Les blocs sont délimités par `{` et `}`
- Les tableaux utilisent `[` et `]`
- Les chaînes sont entre guillemets `"..."`

### Types
- Conversion automatique int ↔ float
- Les tableaux peuvent contenir int ou float
- Pas de mélange de types dans un tableau

### Portée (Scope)
- Les variables sont locales au bloc `{}` où elles sont déclarées
- Les variables d'une boucle `for` sont locales à cette boucle

---

## 🎓 Fichiers d'exemple fournis

- `test_comparisons.ml` - Opérateurs de comparaison et logiques
- `test_if_else.ml` - Structures conditionnelles
- `test_while.ml` - Boucles while
- `test_for.ml` - Boucles for
- `test_arrays.ml` - Manipulation de tableaux
- `test_complete.ml` - Programme complet combinant tout

---

## 🚀 Fonctionnalités avancées

### Scopes et portée

```c
int x = 10;  // Variable globale

if (x > 5) {
    int y = 20;  // Variable locale au if
    print(y);
}
// y n'existe plus ici

for (int i = 0; i < 5; i = i + 1) {
    // i est local à la boucle
}
// i n'existe plus ici
```

### Conditions complexes

```c
// Conditions imbriquées avec opérateurs logiques
if ((x > 0 && y > 0) || (x < 0 && y < 0)) {
    print("Même signe");
}

// Multiples conditions
if (age >= 18 && age < 65 && actif) {
    print("Adulte actif");
}
```

### Boucles imbriquées

```c
// Table de multiplication
for (int i = 1; i <= 5; i = i + 1) {
    for (int j = 1; j <= 5; j = j + 1) {
        int resultat = i * j;
        print(resultat);
    }
}
```

---

## 💡 Astuces et bonnes pratiques

1. **Commentez votre code** - Utilisez `//` et `/* */`
2. **Indentez correctement** - Pour la lisibilité
3. **Nommez bien vos variables** - `age` plutôt que `x`
4. **Initialisez vos variables** - Toujours donner une valeur
5. **Vérifiez les indices** - Avant d'accéder aux tableaux
6. **Utilisez des parenthèses** - Pour clarifier les conditions

---

## 🐛 Débogage

### Erreurs courantes

**"Erreur: nom de variable attendu"**
- Vérifiez la syntaxe de déclaration
- Exemple correct: `int x = 5;`

**"Erreur: '(' attendu"**
- Vérifiez les parenthèses dans if, while, for

**Résultats incorrects**
- Vérifiez les indices de tableaux (0 à n-1)
- Vérifiez la priorité des opérateurs
- Utilisez des parenthèses pour clarifier

### Tips de débogage

```c
// Ajouter des print pour déboguer
print("Valeur de x:");
print(x);

// Vérifier les conditions
if (condition) {
    print("Condition vraie");
} else {
    print("Condition fausse");
}
```

---

## 📦 Structure du projet

```
minilang_advanced.c    - Code source complet (~1500 lignes)
test_comparisons.ml    - Tests comparaisons et logique
test_if_else.ml        - Tests if/else
test_while.ml          - Tests boucles while
test_for.ml            - Tests boucles for
test_arrays.ml         - Tests tableaux
test_complete.ml       - Programme complet
README.md              - Cette documentation
Makefile               - Compilation automatisée
```

---

## 🎉 Félicitations !

Vous disposez maintenant d'un langage de programmation complet avec :
- ✅ 3 types de données + tableaux
- ✅ Tous les opérateurs (arithmétiques, comparaison, logiques)
- ✅ Structures de contrôle (if/else, while, for)
- ✅ Tableaux dynamiques
- ✅ Commentaires
- ✅ Portée des variables (scopes)

MiniLang est maintenant un vrai langage de programmation impératif !
