# 📖 MiniLang - Guide de Référence Rapide

## Types et Variables

```c
int x = 10;              // Entier
float y = 3.14;          // Décimal
str nom = "Alice";       // Chaîne
int arr[5];              // Tableau
```

## Opérateurs

### Arithmétiques
```c
a + b    // Addition
a - b    // Soustraction
a * b    // Multiplication
a / b    // Division
a % b    // Modulo
```

### Comparaison
```c
a == b   // Égal
a != b   // Différent
a < b    // Plus petit
a > b    // Plus grand
a <= b   // Plus petit ou égal
a >= b   // Plus grand ou égal
```

### Logiques
```c
a && b   // ET
a || b   // OU
!a       // NOT
```

## Structures de contrôle

### If/Else
```c
if (condition) {
    // code
} else {
    // code
}
```

### While
```c
while (condition) {
    // code
}
```

### For
```c
for (int i = 0; i < 10; i = i + 1) {
    // code
}
```

## Tableaux

```c
int arr[5];              // Déclaration
arr[0] = 10;             // Écriture
int x = arr[0];          // Lecture
print(arr[2]);           // Affichage
```

## Commentaires

```c
// Une ligne

/* Plusieurs
   lignes */
```

## Fonction print()

```c
print("texte");          // Chaîne
print(variable);         // Variable
print(expression);       // Expression
print(arr[i]);           // Élément tableau
```

## Exemples Express

### Boucle simple
```c
for (int i = 0; i < 5; i = i + 1) {
    print(i);
}
```

### Maximum
```c
int max = arr[0];
for (int i = 1; i < n; i = i + 1) {
    if (arr[i] > max) {
        max = arr[i];
    }
}
```

### Somme
```c
int somme = 0;
for (int i = 0; i < n; i = i + 1) {
    somme = somme + arr[i];
}
```

### Factorielle
```c
int fact = 1;
while (n > 0) {
    fact = fact * n;
    n = n - 1;
}
```

## Compilation

```bash
gcc -std=gnu99 minilang_advanced.c -o minilang
./minilang programme.ml
```

## Priorité des opérateurs

1. `()` Parenthèses
2. `!` NOT
3. `*` `/` `%` Mult/Div/Mod
4. `+` `-` Add/Sub
5. `<` `>` `<=` `>=` Comparaisons
6. `==` `!=` Égalité
7. `&&` ET
8. `||` OU
