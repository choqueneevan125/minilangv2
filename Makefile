CC = gcc
CFLAGS = -std=gnu99 -Wall -O2
TARGET = minilang
SOURCE = minilang_advanced.c

all: $(TARGET)
	@echo "✓ MiniLang compilé avec succès"

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

clean:
	rm -f $(TARGET)
	@echo "✓ Nettoyage effectué"

# Tests individuels
test-comparisons: $(TARGET)
	@echo "=== Test: Comparaisons et opérateurs logiques ==="
	./$(TARGET) test_comparisons.ml

test-if-else: $(TARGET)
	@echo "=== Test: Structures if/else ==="
	./$(TARGET) test_if_else.ml

test-while: $(TARGET)
	@echo "=== Test: Boucles while ==="
	./$(TARGET) test_while.ml

test-for: $(TARGET)
	@echo "=== Test: Boucles for ==="
	./$(TARGET) test_for.ml

test-arrays: $(TARGET)
	@echo "=== Test: Tableaux ==="
	./$(TARGET) test_arrays.ml

test-complete: $(TARGET)
	@echo "=== Test: Programme complet ==="
	./$(TARGET) test_complete.ml

# Tous les tests
test-all: $(TARGET)
	@echo "╔══════════════════════════════════════╗"
	@echo "║   Tests complets de MiniLang        ║"
	@echo "╚══════════════════════════════════════╝"
	@echo ""
	@echo "┌─ Test 1: Comparaisons ─────────────────┐"
	@./$(TARGET) test_comparisons.ml
	@echo "└─────────────────────────────────────────┘"
	@echo ""
	@echo "┌─ Test 2: If/Else ──────────────────────┐"
	@./$(TARGET) test_if_else.ml
	@echo "└─────────────────────────────────────────┘"
	@echo ""
	@echo "┌─ Test 3: While ────────────────────────┐"
	@./$(TARGET) test_while.ml
	@echo "└─────────────────────────────────────────┘"
	@echo ""
	@echo "┌─ Test 4: For ──────────────────────────┐"
	@./$(TARGET) test_for.ml
	@echo "└─────────────────────────────────────────┘"
	@echo ""
	@echo "┌─ Test 5: Tableaux ─────────────────────┐"
	@./$(TARGET) test_arrays.ml
	@echo "└─────────────────────────────────────────┘"
	@echo ""
	@echo "┌─ Test 6: Programme complet ────────────┐"
	@./$(TARGET) test_complete.ml
	@echo "└─────────────────────────────────────────┘"
	@echo ""
	@echo "✅ Tous les tests terminés avec succès!"

# Tests rapides
quick-test: $(TARGET)
	@./$(TARGET) test_complete.ml

help:
	@echo "Cibles disponibles:"
	@echo "  make              - Compiler MiniLang"
	@echo "  make all          - Compiler MiniLang"
	@echo "  make clean        - Supprimer l'exécutable"
	@echo ""
	@echo "Tests individuels:"
	@echo "  make test-comparisons  - Tester comparaisons et logique"
	@echo "  make test-if-else      - Tester if/else"
	@echo "  make test-while        - Tester boucles while"
	@echo "  make test-for          - Tester boucles for"
	@echo "  make test-arrays       - Tester tableaux"
	@echo "  make test-complete     - Tester programme complet"
	@echo ""
	@echo "Tests groupés:"
	@echo "  make test-all     - Exécuter tous les tests"
	@echo "  make quick-test   - Test rapide (complet seulement)"
	@echo ""
	@echo "  make help         - Afficher cette aide"

.PHONY: all clean test-comparisons test-if-else test-while test-for test-arrays test-complete test-all quick-test help
