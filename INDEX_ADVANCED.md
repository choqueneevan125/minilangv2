# 🎉 MiniLang - Langage de Programmation Complet

## 📦 Contenu du Projet

### 📄 Code Source
- **minilang_advanced.c** - Interpréteur complet (~1500 lignes)
  - Lexer avec support des commentaires
  - Parser avec scopes
  - Évaluateur d'expressions
  - Gestion de la mémoire

### 📚 Documentation
- **README_ADVANCED.md** - Documentation complète détaillée
- **QUICK_REFERENCE.md** - Guide de référence rapide

### 🔧 Build
- **Makefile_advanced** - Compilation et tests automatisés

### 🎯 Exemples de code (.ml)

#### test_comparisons.ml
Tests des opérateurs de comparaison et logiques :
- `==`, `!=`, `<`, `>`, `<=`, `>=`
- `&&`, `||`, `!`
- Expressions complexes

#### test_if_else.ml
Tests des structures conditionnelles :
- If simple
- If/else
- If/else imbriqués
- Conditions avec opérateurs logiques

#### test_while.ml
Tests des boucles while :
- Boucles simples
- Compte à rebours
- Calcul de sommes
- Tables de multiplication

#### test_for.ml
Tests des boucles for :
- Boucles simples
- Compte à rebours
- Nombres pairs
- Calcul de carrés
- Sommes

#### test_arrays.ml
Tests des tableaux :
- Déclaration et initialisation
- Remplissage avec boucles
- Lecture et écriture
- Tableaux d'int et float

#### test_complete.ml
Programme complet démontrant :
- Nombres pairs avec modulo
- Recherche dans un tableau
- Calcul du maximum
- Factorielle
- Suite de Fibonacci
- Tri simple
- Calculs géométriques

---

## ✨ Fonctionnalités Complètes

### Types de données
- ✅ `int` - Entiers
- ✅ `float` - Nombres décimaux
- ✅ `str` - Chaînes de caractères
- ✅ Tableaux `int[]` et `float[]`

### Opérateurs

#### Arithmétiques
- ✅ `+` `-` `*` `/` `%`

#### Comparaison
- ✅ `==` `!=` `<` `>` `<=` `>=`

#### Logiques
- ✅ `&&` `||` `!`

### Structures de contrôle
- ✅ `if` / `else` - Conditions
- ✅ `while` - Boucle tant que
- ✅ `for` - Boucle avec initialisation, condition, incrément

### Autres fonctionnalités
- ✅ Commentaires `//` et `/* */`
- ✅ Tableaux dynamiques
- ✅ Scopes de variables
- ✅ Priorité des opérateurs
- ✅ Conversion automatique de types
- ✅ Fonction `print()`

---

## 🚀 Démarrage Rapide

### Installation (30 secondes)

```bash
# 1. Compiler
gcc -std=gnu99 minilang_advanced.c -o minilang

# 2. Créer un fichier test.ml
cat > test.ml << 'EOF'
print("Hello MiniLang!");

for (int i = 1; i <= 5; i = i + 1) {
    print(i * i);
}
EOF

# 3. Exécuter
./minilang test.ml
```

### Ou avec Make

```bash
make                    # Compiler
make test-all           # Tous les tests
make test-complete      # Programme complet
make help              # Aide
```

---

## 📖 Exemple Rapide

```c
// Calcul de la moyenne d'un tableau
int notes[5];
notes[0] = 15;
notes[1] = 18;
notes[2] = 12;
notes[3] = 16;
notes[4] = 14;

int somme = 0;
for (int i = 0; i < 5; i = i + 1) {
    somme = somme + notes[i];
}

int moyenne = somme / 5;
print("Moyenne:");
print(moyenne);
```

---

## 📊 Comparaison des versions

| Fonctionnalité | V1 | V2 (Actuelle) |
|----------------|-----|---------------|
| Types de base | ✅ | ✅ |
| Arithmétique | ✅ | ✅ |
| Comparaisons | ❌ | ✅ |
| Logique | ❌ | ✅ |
| if/else | ❌ | ✅ |
| while | ❌ | ✅ |
| for | ❌ | ✅ |
| Tableaux | ❌ | ✅ |
| Commentaires | ❌ | ✅ |
| Scopes | ❌ | ✅ |

---

## 🎓 Pour Apprendre

1. **Débutants** → Commencer par `QUICK_REFERENCE.md`
2. **Exemples** → Ouvrir et exécuter les fichiers `test_*.ml`
3. **Complet** → Lire `README_ADVANCED.md`
4. **Code source** → Explorer `minilang_advanced.c`

---

## 🏆 Programmes Intéressants à Essayer

### Nombres premiers
```c
int n = 20;
for (int i = 2; i <= n; i = i + 1) {
    int premier = 1;
    for (int j = 2; j < i; j = j + 1) {
        if (i % j == 0) {
            premier = 0;
        }
    }
    if (premier) {
        print(i);
    }
}
```

### PGCD (Plus Grand Commun Diviseur)
```c
int a = 48;
int b = 18;
while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
}
print("PGCD:");
print(a);
```

### Triangle de Pascal (première ligne)
```c
int n = 5;
int coef = 1;
for (int i = 0; i <= n; i = i + 1) {
    print(coef);
    coef = coef * (n - i) / (i + 1);
}
```

---

## 🔍 Architecture du Code

```
minilang_advanced.c (1500 lignes)
├── Structures de données (100 lignes)
│   ├── Token
│   ├── Variable
│   ├── Array
│   └── Scope
├── Lexer (250 lignes)
│   ├── Tokenisation
│   ├── Commentaires
│   └── Mots-clés
├── Parser (900 lignes)
│   ├── Expressions
│   ├── Statements
│   └── Blocs
└── Runtime (250 lignes)
    ├── Variables
    ├── Scopes
    └── Mémoire
```

---

## 💡 Ce que vous pouvez faire maintenant

- ✅ Écrire des algorithmes de tri
- ✅ Implémenter des jeux simples
- ✅ Calculer des séquences mathématiques
- ✅ Résoudre des problèmes algorithmiques
- ✅ Apprendre les bases de la programmation
- ✅ Expérimenter avec les structures de données

---

## 🎯 Prochaines Étapes Possibles

Pour aller encore plus loin, on pourrait ajouter :
- 📝 Fonctions définies par l'utilisateur avec `func`
- 🔁 `break` et `continue` dans les boucles
- 📋 Chaînes de caractères modifiables
- 🔢 Opérateurs `++` et `--`
- 📚 Plus de types (bool, char)
- 🎨 Meilleurs messages d'erreur
- 🚀 Optimisations de performance

---

## 📝 Notes Importantes

- Les tableaux sont à taille fixe
- Les indices commencent à 0
- Division entière pour int/int
- Pas de récursion pour l'instant
- Scopes limités aux blocs `{}`

---

## 🎊 Félicitations !

Vous avez maintenant un **vrai langage de programmation** avec :
- Parser complet
- Évaluateur d'expressions
- Structures de contrôle
- Tableaux
- Et bien plus !

**MiniLang peut maintenant résoudre de vrais problèmes algorithmiques !** 🚀
