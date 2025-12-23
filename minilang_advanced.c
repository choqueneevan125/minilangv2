#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Types de tokens
typedef enum {
    TOKEN_INT, TOKEN_FLOAT, TOKEN_STR,
    TOKEN_IDENTIFIER, TOKEN_NUMBER, TOKEN_STRING,
    TOKEN_ASSIGN, TOKEN_PRINT, TOKEN_LPAREN, TOKEN_RPAREN,
    TOKEN_SEMICOLON, TOKEN_EOF, TOKEN_COMMA,
    TOKEN_PLUS, TOKEN_MINUS, TOKEN_MULT, TOKEN_DIV, TOKEN_MOD,
    TOKEN_EQ, TOKEN_NEQ, TOKEN_LT, TOKEN_GT, TOKEN_LTE, TOKEN_GTE,
    TOKEN_AND, TOKEN_OR, TOKEN_NOT,
    TOKEN_IF, TOKEN_ELSE, TOKEN_WHILE, TOKEN_FOR,
    TOKEN_LBRACE, TOKEN_RBRACE, TOKEN_LBRACKET, TOKEN_RBRACKET,
    TOKEN_FUNC, TOKEN_RETURN
} TokenType;

// Structure Token
typedef struct {
    TokenType type;
    char *value;
    int line;
} Token;

// Types de variables
typedef enum {
    VAR_INT, VAR_FLOAT, VAR_STRING, VAR_ARRAY
} VarType;

// Structure pour tableaux
typedef struct {
    int *int_array;
    float *float_array;
    char **str_array;
    int size;
    VarType elem_type;
} Array;

// Structure Variable
typedef struct Variable {
    char *name;
    VarType type;
    union {
        int int_val;
        float float_val;
        char *str_val;
        Array array_val;
    } value;
    struct Variable *next;
} Variable;

// Structure pour les résultats d'expressions
typedef struct {
    VarType type;
    union {
        int int_val;
        float float_val;
        char *str_val;
    } value;
} ExprResult;

// Structure pour les fonctions
typedef struct Function {
    char *name;
    char **params;
    int param_count;
    int body_start;
    int body_end;
    struct Function *next;
} Function;

// Variables globales
Variable *variables = NULL;
Function *functions = NULL;
Token *tokens = NULL;
int token_count = 0;
int current_token = 0;
int current_line = 1;

// Stack pour les scopes de variables
typedef struct VarScope {
    Variable *vars;
    struct VarScope *parent;
} VarScope;

VarScope *current_scope = NULL;

// Prototypes
void lexer(const char *source);
void parser();
void parse_statement();
void parse_block();
Variable *find_variable(const char *name);
void add_variable(const char *name, VarType type);
void push_scope();
void pop_scope();
void free_tokens();
void free_variables();
ExprResult evaluate_expression();
ExprResult evaluate_comparison();
ExprResult evaluate_logical();
ExprResult parse_term();
ExprResult parse_factor();
bool is_true(ExprResult result);

// Fonction pour créer un token
Token create_token(TokenType type, const char *value, int line) {
    Token token;
    token.type = type;
    token.value = strdup(value);
    token.line = line;
    return token;
}

// Push un nouveau scope
void push_scope() {
    VarScope *new_scope = malloc(sizeof(VarScope));
    new_scope->vars = NULL;
    new_scope->parent = current_scope;
    current_scope = new_scope;
}

// Pop le scope actuel
void pop_scope() {
    if (current_scope == NULL) return;
    
    // Libérer les variables du scope
    Variable *current = current_scope->vars;
    while (current != NULL) {
        Variable *next = current->next;
        free(current->name);
        if (current->type == VAR_STRING) {
            free(current->value.str_val);
        }
        free(current);
        current = next;
    }
    
    VarScope *parent = current_scope->parent;
    free(current_scope);
    current_scope = parent;
}

// Lexer - Analyse lexicale avec support des commentaires
void lexer(const char *source) {
    int len = strlen(source);
    int capacity = 100;
    tokens = malloc(capacity * sizeof(Token));
    token_count = 0;
    int line = 1;
    
    int i = 0;
    while (i < len) {
        // Commentaires
        if (source[i] == '/' && i + 1 < len && source[i + 1] == '/') {
            // Commentaire jusqu'à la fin de la ligne
            while (i < len && source[i] != '\n') {
                i++;
            }
            if (i < len && source[i] == '\n') {
                line++;
                i++;
            }
            continue;
        }
        
        if (source[i] == '/' && i + 1 < len && source[i + 1] == '*') {
            // Commentaire multilignes
            i += 2;
            while (i + 1 < len && !(source[i] == '*' && source[i + 1] == '/')) {
                if (source[i] == '\n') line++;
                i++;
            }
            i += 2;
            continue;
        }
        
        // Ignorer les espaces
        if (isspace(source[i])) {
            if (source[i] == '\n') line++;
            i++;
            continue;
        }
        
        // Redimensionner si nécessaire
        if (token_count >= capacity) {
            capacity *= 2;
            tokens = realloc(tokens, capacity * sizeof(Token));
        }
        
        // Mots-clés et identifiants
        if (isalpha(source[i])) {
            int start = i;
            while (i < len && (isalnum(source[i]) || source[i] == '_')) {
                i++;
            }
            char *word = strndup(source + start, i - start);
            
            if (strcmp(word, "int") == 0) {
                tokens[token_count++] = create_token(TOKEN_INT, word, line);
            } else if (strcmp(word, "float") == 0) {
                tokens[token_count++] = create_token(TOKEN_FLOAT, word, line);
            } else if (strcmp(word, "str") == 0) {
                tokens[token_count++] = create_token(TOKEN_STR, word, line);
            } else if (strcmp(word, "print") == 0) {
                tokens[token_count++] = create_token(TOKEN_PRINT, word, line);
            } else if (strcmp(word, "if") == 0) {
                tokens[token_count++] = create_token(TOKEN_IF, word, line);
            } else if (strcmp(word, "else") == 0) {
                tokens[token_count++] = create_token(TOKEN_ELSE, word, line);
            } else if (strcmp(word, "while") == 0) {
                tokens[token_count++] = create_token(TOKEN_WHILE, word, line);
            } else if (strcmp(word, "for") == 0) {
                tokens[token_count++] = create_token(TOKEN_FOR, word, line);
            } else if (strcmp(word, "func") == 0) {
                tokens[token_count++] = create_token(TOKEN_FUNC, word, line);
            } else if (strcmp(word, "return") == 0) {
                tokens[token_count++] = create_token(TOKEN_RETURN, word, line);
            } else {
                tokens[token_count++] = create_token(TOKEN_IDENTIFIER, word, line);
            }
            free(word);
            continue;
        }
        
        // Nombres (int et float)
        if (isdigit(source[i])) {
            int start = i;
            while (i < len && (isdigit(source[i]) || source[i] == '.')) {
                i++;
            }
            char *num = strndup(source + start, i - start);
            tokens[token_count++] = create_token(TOKEN_NUMBER, num, line);
            free(num);
            continue;
        }
        
        // Chaînes de caractères
        if (source[i] == '"') {
            i++; // Skip opening quote
            int start = i;
            while (i < len && source[i] != '"') {
                if (source[i] == '\n') line++;
                i++;
            }
            char *str = strndup(source + start, i - start);
            tokens[token_count++] = create_token(TOKEN_STRING, str, line);
            free(str);
            i++; // Skip closing quote
            continue;
        }
        
        // Opérateurs et symboles
        if (source[i] == '=' && i + 1 < len && source[i + 1] == '=') {
            tokens[token_count++] = create_token(TOKEN_EQ, "==", line);
            i += 2;
        } else if (source[i] == '!' && i + 1 < len && source[i + 1] == '=') {
            tokens[token_count++] = create_token(TOKEN_NEQ, "!=", line);
            i += 2;
        } else if (source[i] == '<' && i + 1 < len && source[i + 1] == '=') {
            tokens[token_count++] = create_token(TOKEN_LTE, "<=", line);
            i += 2;
        } else if (source[i] == '>' && i + 1 < len && source[i + 1] == '=') {
            tokens[token_count++] = create_token(TOKEN_GTE, ">=", line);
            i += 2;
        } else if (source[i] == '&' && i + 1 < len && source[i + 1] == '&') {
            tokens[token_count++] = create_token(TOKEN_AND, "&&", line);
            i += 2;
        } else if (source[i] == '|' && i + 1 < len && source[i + 1] == '|') {
            tokens[token_count++] = create_token(TOKEN_OR, "||", line);
            i += 2;
        } else {
            switch (source[i]) {
                case '=':
                    tokens[token_count++] = create_token(TOKEN_ASSIGN, "=", line);
                    break;
                case '(':
                    tokens[token_count++] = create_token(TOKEN_LPAREN, "(", line);
                    break;
                case ')':
                    tokens[token_count++] = create_token(TOKEN_RPAREN, ")", line);
                    break;
                case '{':
                    tokens[token_count++] = create_token(TOKEN_LBRACE, "{", line);
                    break;
                case '}':
                    tokens[token_count++] = create_token(TOKEN_RBRACE, "}", line);
                    break;
                case '[':
                    tokens[token_count++] = create_token(TOKEN_LBRACKET, "[", line);
                    break;
                case ']':
                    tokens[token_count++] = create_token(TOKEN_RBRACKET, "]", line);
                    break;
                case ';':
                    tokens[token_count++] = create_token(TOKEN_SEMICOLON, ";", line);
                    break;
                case ',':
                    tokens[token_count++] = create_token(TOKEN_COMMA, ",", line);
                    break;
                case '+':
                    tokens[token_count++] = create_token(TOKEN_PLUS, "+", line);
                    break;
                case '-':
                    tokens[token_count++] = create_token(TOKEN_MINUS, "-", line);
                    break;
                case '*':
                    tokens[token_count++] = create_token(TOKEN_MULT, "*", line);
                    break;
                case '/':
                    tokens[token_count++] = create_token(TOKEN_DIV, "/", line);
                    break;
                case '%':
                    tokens[token_count++] = create_token(TOKEN_MOD, "%", line);
                    break;
                case '<':
                    tokens[token_count++] = create_token(TOKEN_LT, "<", line);
                    break;
                case '>':
                    tokens[token_count++] = create_token(TOKEN_GT, ">", line);
                    break;
                case '!':
                    tokens[token_count++] = create_token(TOKEN_NOT, "!", line);
                    break;
            }
            i++;
        }
    }
    
    tokens[token_count++] = create_token(TOKEN_EOF, "", line);
}

// Trouver une variable dans les scopes
Variable *find_variable(const char *name) {
    VarScope *scope = current_scope;
    while (scope != NULL) {
        Variable *current = scope->vars;
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                return current;
            }
            current = current->next;
        }
        scope = scope->parent;
    }
    return NULL;
}

// Ajouter ou modifier une variable dans le scope actuel
void add_variable(const char *name, VarType type) {
    if (current_scope == NULL) {
        push_scope();
    }
    
    // Chercher dans le scope actuel seulement
    Variable *current = current_scope->vars;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            current->type = type;
            return;
        }
        current = current->next;
    }
    
    // Créer nouvelle variable
    Variable *var = malloc(sizeof(Variable));
    var->name = strdup(name);
    var->type = type;
    var->next = current_scope->vars;
    current_scope->vars = var;
}

// Vérifier si le résultat est vrai
bool is_true(ExprResult result) {
    if (result.type == VAR_INT) {
        return result.value.int_val != 0;
    } else if (result.type == VAR_FLOAT) {
        return result.value.float_val != 0.0;
    }
    return false;
}

// Parser un facteur (nombre, variable ou expression entre parenthèses)
ExprResult parse_factor() {
    ExprResult result;
    result.type = VAR_INT;
    result.value.int_val = 0;
    
    Token token = tokens[current_token];
    
    // NOT logique
    if (token.type == TOKEN_NOT) {
        current_token++;
        ExprResult expr = parse_factor();
        result.type = VAR_INT;
        result.value.int_val = !is_true(expr);
        return result;
    }
    
    // Parenthèses
    if (token.type == TOKEN_LPAREN) {
        current_token++;
        result = evaluate_logical();
        if (tokens[current_token].type == TOKEN_RPAREN) {
            current_token++;
        }
        return result;
    }
    
    // Nombre
    if (token.type == TOKEN_NUMBER) {
        if (strchr(token.value, '.') != NULL) {
            result.type = VAR_FLOAT;
            result.value.float_val = atof(token.value);
        } else {
            result.type = VAR_INT;
            result.value.int_val = atoi(token.value);
        }
        current_token++;
        return result;
    }
    
    // Variable ou accès tableau
    if (token.type == TOKEN_IDENTIFIER) {
        Variable *var = find_variable(token.value);
        current_token++;
        
        if (var != NULL) {
            // Accès tableau
            if (tokens[current_token].type == TOKEN_LBRACKET) {
                current_token++;
                ExprResult index = evaluate_expression();
                if (tokens[current_token].type == TOKEN_RBRACKET) {
                    current_token++;
                }
                
                int idx = index.value.int_val;
                if (var->type == VAR_ARRAY && idx >= 0 && idx < var->value.array_val.size) {
                    result.type = var->value.array_val.elem_type;
                    if (var->value.array_val.elem_type == VAR_INT) {
                        result.value.int_val = var->value.array_val.int_array[idx];
                    } else if (var->value.array_val.elem_type == VAR_FLOAT) {
                        result.value.float_val = var->value.array_val.float_array[idx];
                    }
                }
                return result;
            }
            
            result.type = var->type;
            if (var->type == VAR_INT) {
                result.value.int_val = var->value.int_val;
            } else if (var->type == VAR_FLOAT) {
                result.value.float_val = var->value.float_val;
            }
        }
        return result;
    }
    
    return result;
}

// Parser un terme (multiplication, division, modulo)
ExprResult parse_term() {
    ExprResult left = parse_factor();
    
    while (current_token < token_count) {
        Token token = tokens[current_token];
        
        if (token.type == TOKEN_MULT || token.type == TOKEN_DIV || token.type == TOKEN_MOD) {
            TokenType op = token.type;
            current_token++;
            ExprResult right = parse_factor();
            
            // Promotion de type
            if (left.type == VAR_FLOAT || right.type == VAR_FLOAT) {
                float left_val = (left.type == VAR_FLOAT) ? left.value.float_val : (float)left.value.int_val;
                float right_val = (right.type == VAR_FLOAT) ? right.value.float_val : (float)right.value.int_val;
                
                left.type = VAR_FLOAT;
                if (op == TOKEN_MULT) {
                    left.value.float_val = left_val * right_val;
                } else if (op == TOKEN_DIV) {
                    left.value.float_val = left_val / right_val;
                }
            } else {
                if (op == TOKEN_MULT) {
                    left.value.int_val = left.value.int_val * right.value.int_val;
                } else if (op == TOKEN_DIV) {
                    left.value.int_val = left.value.int_val / right.value.int_val;
                } else if (op == TOKEN_MOD) {
                    left.value.int_val = left.value.int_val % right.value.int_val;
                }
            }
        } else {
            break;
        }
    }
    
    return left;
}

// Évaluer une expression arithmétique (addition, soustraction)
ExprResult evaluate_expression() {
    ExprResult left = parse_term();
    
    while (current_token < token_count) {
        Token token = tokens[current_token];
        
        if (token.type == TOKEN_PLUS || token.type == TOKEN_MINUS) {
            TokenType op = token.type;
            current_token++;
            ExprResult right = parse_term();
            
            if (left.type == VAR_FLOAT || right.type == VAR_FLOAT) {
                float left_val = (left.type == VAR_FLOAT) ? left.value.float_val : (float)left.value.int_val;
                float right_val = (right.type == VAR_FLOAT) ? right.value.float_val : (float)right.value.int_val;
                
                left.type = VAR_FLOAT;
                if (op == TOKEN_PLUS) {
                    left.value.float_val = left_val + right_val;
                } else {
                    left.value.float_val = left_val - right_val;
                }
            } else {
                if (op == TOKEN_PLUS) {
                    left.value.int_val = left.value.int_val + right.value.int_val;
                } else {
                    left.value.int_val = left.value.int_val - right.value.int_val;
                }
            }
        } else {
            break;
        }
    }
    
    return left;
}

// Évaluer une comparaison
ExprResult evaluate_comparison() {
    ExprResult left = evaluate_expression();
    
    Token token = tokens[current_token];
    if (token.type == TOKEN_EQ || token.type == TOKEN_NEQ ||
        token.type == TOKEN_LT || token.type == TOKEN_GT ||
        token.type == TOKEN_LTE || token.type == TOKEN_GTE) {
        
        TokenType op = token.type;
        current_token++;
        ExprResult right = evaluate_expression();
        
        ExprResult result;
        result.type = VAR_INT;
        
        float left_val = (left.type == VAR_FLOAT) ? left.value.float_val : (float)left.value.int_val;
        float right_val = (right.type == VAR_FLOAT) ? right.value.float_val : (float)right.value.int_val;
        
        switch (op) {
            case TOKEN_EQ:
                result.value.int_val = (left_val == right_val);
                break;
            case TOKEN_NEQ:
                result.value.int_val = (left_val != right_val);
                break;
            case TOKEN_LT:
                result.value.int_val = (left_val < right_val);
                break;
            case TOKEN_GT:
                result.value.int_val = (left_val > right_val);
                break;
            case TOKEN_LTE:
                result.value.int_val = (left_val <= right_val);
                break;
            case TOKEN_GTE:
                result.value.int_val = (left_val >= right_val);
                break;
            default:
                result.value.int_val = 0;
        }
        
        return result;
    }
    
    return left;
}

// Évaluer une expression logique
ExprResult evaluate_logical() {
    ExprResult left = evaluate_comparison();
    
    while (current_token < token_count) {
        Token token = tokens[current_token];
        
        if (token.type == TOKEN_AND || token.type == TOKEN_OR) {
            TokenType op = token.type;
            current_token++;
            ExprResult right = evaluate_comparison();
            
            ExprResult result;
            result.type = VAR_INT;
            
            if (op == TOKEN_AND) {
                result.value.int_val = is_true(left) && is_true(right);
            } else { // TOKEN_OR
                result.value.int_val = is_true(left) || is_true(right);
            }
            
            left = result;
        } else {
            break;
        }
    }
    
    return left;
}

// Parser un bloc entre accolades
void parse_block() {
    if (tokens[current_token].type == TOKEN_LBRACE) {
        current_token++;
    }
    
    push_scope();
    
    while (current_token < token_count && tokens[current_token].type != TOKEN_RBRACE && tokens[current_token].type != TOKEN_EOF) {
        parse_statement();
    }
    
    pop_scope();
    
    if (tokens[current_token].type == TOKEN_RBRACE) {
        current_token++;
    }
}

// Parser une instruction
void parse_statement() {
    Token token = tokens[current_token];
    
    // Déclaration de variable
    if (token.type == TOKEN_INT || token.type == TOKEN_FLOAT || token.type == TOKEN_STR) {
        VarType type = (token.type == TOKEN_INT) ? VAR_INT : 
                      (token.type == TOKEN_FLOAT) ? VAR_FLOAT : VAR_STRING;
        current_token++;
        
        if (tokens[current_token].type != TOKEN_IDENTIFIER) {
            printf("Erreur ligne %d: nom de variable attendu\n", token.line);
            return;
        }
        
        char *var_name = tokens[current_token].value;
        current_token++;
        
        // Déclaration de tableau
        if (tokens[current_token].type == TOKEN_LBRACKET) {
            current_token++;
            ExprResult size = evaluate_expression();
            if (tokens[current_token].type == TOKEN_RBRACKET) {
                current_token++;
            }
            
            Variable *var = malloc(sizeof(Variable));
            var->name = strdup(var_name);
            var->type = VAR_ARRAY;
            var->value.array_val.size = size.value.int_val;
            var->value.array_val.elem_type = type;
            
            if (type == VAR_INT) {
                var->value.array_val.int_array = calloc(size.value.int_val, sizeof(int));
            } else if (type == VAR_FLOAT) {
                var->value.array_val.float_array = calloc(size.value.int_val, sizeof(float));
            }
            
            var->next = current_scope->vars;
            current_scope->vars = var;
        } else {
            add_variable(var_name, type);
            
            if (tokens[current_token].type == TOKEN_ASSIGN) {
                current_token++;
                Variable *var = find_variable(var_name);
                
                if (tokens[current_token].type == TOKEN_STRING) {
                    if (type == VAR_STRING) {
                        var->value.str_val = strdup(tokens[current_token].value);
                    }
                    current_token++;
                } else {
                    ExprResult result = evaluate_logical();
                    
                    if (type == VAR_INT) {
                        if (result.type == VAR_FLOAT) {
                            var->value.int_val = (int)result.value.float_val;
                        } else {
                            var->value.int_val = result.value.int_val;
                        }
                    } else if (type == VAR_FLOAT) {
                        if (result.type == VAR_INT) {
                            var->value.float_val = (float)result.value.int_val;
                        } else {
                            var->value.float_val = result.value.float_val;
                        }
                    }
                }
            }
        }
        
        if (tokens[current_token].type == TOKEN_SEMICOLON) {
            current_token++;
        }
    }
    // Assignation ou accès tableau
    else if (token.type == TOKEN_IDENTIFIER) {
        char *var_name = token.value;
        current_token++;
        
        // Assignation tableau
        if (tokens[current_token].type == TOKEN_LBRACKET) {
            current_token++;
            ExprResult index = evaluate_expression();
            if (tokens[current_token].type == TOKEN_RBRACKET) {
                current_token++;
            }
            
            if (tokens[current_token].type == TOKEN_ASSIGN) {
                current_token++;
                ExprResult value = evaluate_logical();
                
                Variable *var = find_variable(var_name);
                if (var != NULL && var->type == VAR_ARRAY) {
                    int idx = index.value.int_val;
                    if (idx >= 0 && idx < var->value.array_val.size) {
                        if (var->value.array_val.elem_type == VAR_INT) {
                            var->value.array_val.int_array[idx] = value.value.int_val;
                        } else if (var->value.array_val.elem_type == VAR_FLOAT) {
                            var->value.array_val.float_array[idx] = 
                                (value.type == VAR_INT) ? (float)value.value.int_val : value.value.float_val;
                        }
                    }
                }
            }
        }
        // Assignation normale
        else if (tokens[current_token].type == TOKEN_ASSIGN) {
            current_token++;
            Variable *var = find_variable(var_name);
            
            if (var != NULL) {
                if (tokens[current_token].type == TOKEN_STRING) {
                    if (var->type == VAR_STRING) {
                        free(var->value.str_val);
                        var->value.str_val = strdup(tokens[current_token].value);
                    }
                    current_token++;
                } else {
                    ExprResult result = evaluate_logical();
                    
                    if (var->type == VAR_INT) {
                        var->value.int_val = (result.type == VAR_FLOAT) ? 
                            (int)result.value.float_val : result.value.int_val;
                    } else if (var->type == VAR_FLOAT) {
                        var->value.float_val = (result.type == VAR_INT) ? 
                            (float)result.value.int_val : result.value.float_val;
                    }
                }
            }
        }
        
        if (tokens[current_token].type == TOKEN_SEMICOLON) {
            current_token++;
        }
    }
    // Print
    else if (token.type == TOKEN_PRINT) {
        current_token++;
        
        if (tokens[current_token].type != TOKEN_LPAREN) {
            printf("Erreur ligne %d: '(' attendu\n", token.line);
            return;
        }
        current_token++;
        
        if (tokens[current_token].type == TOKEN_STRING) {
            printf("%s\n", tokens[current_token].value);
            current_token++;
        } else if (tokens[current_token].type == TOKEN_IDENTIFIER) {
            Variable *var = find_variable(tokens[current_token].value);
            current_token++;
            
            // Print tableau
            if (tokens[current_token].type == TOKEN_LBRACKET) {
                current_token++;
                ExprResult index = evaluate_expression();
                if (tokens[current_token].type == TOKEN_RBRACKET) {
                    current_token++;
                }
                
                if (var != NULL && var->type == VAR_ARRAY) {
                    int idx = index.value.int_val;
                    if (idx >= 0 && idx < var->value.array_val.size) {
                        if (var->value.array_val.elem_type == VAR_INT) {
                            printf("%d\n", var->value.array_val.int_array[idx]);
                        } else if (var->value.array_val.elem_type == VAR_FLOAT) {
                            printf("%g\n", var->value.array_val.float_array[idx]);
                        }
                    }
                }
            } else if (var != NULL) {
                switch (var->type) {
                    case VAR_INT:
                        printf("%d\n", var->value.int_val);
                        break;
                    case VAR_FLOAT:
                        printf("%g\n", var->value.float_val);
                        break;
                    case VAR_STRING:
                        printf("%s\n", var->value.str_val);
                        break;
                    default:
                        break;
                }
            }
        } else {
            ExprResult result = evaluate_logical();
            
            if (result.type == VAR_INT) {
                printf("%d\n", result.value.int_val);
            } else if (result.type == VAR_FLOAT) {
                printf("%g\n", result.value.float_val);
            }
        }
        
        if (tokens[current_token].type != TOKEN_RPAREN) {
            printf("Erreur ligne %d: ')' attendu\n", token.line);
            return;
        }
        current_token++;
        
        if (tokens[current_token].type == TOKEN_SEMICOLON) {
            current_token++;
        }
    }
    // If
    else if (token.type == TOKEN_IF) {
        current_token++;
        
        if (tokens[current_token].type != TOKEN_LPAREN) {
            printf("Erreur ligne %d: '(' attendu\n", token.line);
            return;
        }
        current_token++;
        
        ExprResult condition = evaluate_logical();
        
        if (tokens[current_token].type != TOKEN_RPAREN) {
            printf("Erreur ligne %d: ')' attendu\n", token.line);
            return;
        }
        current_token++;
        
        // Sauvegarder la position
        int then_pos = current_token;
        
        // Sauter le bloc then pour trouver le else
        int brace_count = 0;
        int else_pos = -1;
        int temp_token = current_token;
        
        if (tokens[temp_token].type == TOKEN_LBRACE) {
            brace_count = 1;
            temp_token++;
            while (temp_token < token_count && brace_count > 0) {
                if (tokens[temp_token].type == TOKEN_LBRACE) brace_count++;
                if (tokens[temp_token].type == TOKEN_RBRACE) brace_count--;
                temp_token++;
            }
        } else {
            // Instruction simple
            while (temp_token < token_count && tokens[temp_token].type != TOKEN_SEMICOLON) {
                temp_token++;
            }
            temp_token++;
        }
        
        if (tokens[temp_token].type == TOKEN_ELSE) {
            else_pos = temp_token + 1;
        }
        
        if (is_true(condition)) {
            // Exécuter le bloc then
            current_token = then_pos;
            if (tokens[current_token].type == TOKEN_LBRACE) {
                parse_block();
            } else {
                parse_statement();
            }
            
            // Sauter le else si présent
            if (else_pos != -1) {
                current_token = else_pos;
                if (tokens[current_token].type == TOKEN_LBRACE) {
                    int brace = 1;
                    current_token++;
                    while (current_token < token_count && brace > 0) {
                        if (tokens[current_token].type == TOKEN_LBRACE) brace++;
                        if (tokens[current_token].type == TOKEN_RBRACE) brace--;
                        current_token++;
                    }
                } else {
                    while (current_token < token_count && tokens[current_token].type != TOKEN_SEMICOLON) {
                        current_token++;
                    }
                    if (tokens[current_token].type == TOKEN_SEMICOLON) {
                        current_token++;
                    }
                }
            }
        } else {
            // Sauter le bloc then
            current_token = temp_token;
            
            // Exécuter le else si présent
            if (else_pos != -1 && tokens[else_pos - 1].type == TOKEN_ELSE) {
                current_token = else_pos;
                if (tokens[current_token].type == TOKEN_LBRACE) {
                    parse_block();
                } else {
                    parse_statement();
                }
            }
        }
    }
    // While
    else if (token.type == TOKEN_WHILE) {
        int loop_start = current_token;
        current_token++;
        
        if (tokens[current_token].type != TOKEN_LPAREN) {
            printf("Erreur ligne %d: '(' attendu\n", token.line);
            return;
        }
        current_token++;
        
        int condition_start = current_token;
        ExprResult condition = evaluate_logical();
        int condition_end = current_token;
        
        if (tokens[current_token].type != TOKEN_RPAREN) {
            printf("Erreur ligne %d: ')' attendu\n", token.line);
            return;
        }
        current_token++;
        
        int body_start = current_token;
        
        while (is_true(condition)) {
            current_token = body_start;
            
            if (tokens[current_token].type == TOKEN_LBRACE) {
                parse_block();
            } else {
                parse_statement();
            }
            
            // Réévaluer la condition
            current_token = condition_start;
            condition = evaluate_logical();
            current_token = condition_end;
            
            if (tokens[current_token].type == TOKEN_RPAREN) {
                current_token++;
            }
        }
        
        // Sauter le corps de la boucle
        current_token = body_start;
        if (tokens[current_token].type == TOKEN_LBRACE) {
            int brace_count = 1;
            current_token++;
            while (current_token < token_count && brace_count > 0) {
                if (tokens[current_token].type == TOKEN_LBRACE) brace_count++;
                if (tokens[current_token].type == TOKEN_RBRACE) brace_count--;
                current_token++;
            }
        } else {
            while (current_token < token_count && tokens[current_token].type != TOKEN_SEMICOLON) {
                current_token++;
            }
            if (tokens[current_token].type == TOKEN_SEMICOLON) {
                current_token++;
            }
        }
    }
    // For
    else if (token.type == TOKEN_FOR) {
        current_token++;
        
        if (tokens[current_token].type != TOKEN_LPAREN) {
            printf("Erreur ligne %d: '(' attendu\n", token.line);
            return;
        }
        current_token++;
        
        push_scope();
        
        // Initialisation
        parse_statement();
        
        int condition_start = current_token;
        ExprResult condition = evaluate_logical();
        int condition_end = current_token;
        
        if (tokens[current_token].type != TOKEN_SEMICOLON) {
            printf("Erreur ligne %d: ';' attendu\n", token.line);
            pop_scope();
            return;
        }
        current_token++;
        
        int increment_start = current_token;
        
        // Trouver la fin de l'incrément
        while (current_token < token_count && tokens[current_token].type != TOKEN_RPAREN) {
            current_token++;
        }
        int increment_end = current_token;
        
        if (tokens[current_token].type != TOKEN_RPAREN) {
            printf("Erreur ligne %d: ')' attendu\n", token.line);
            pop_scope();
            return;
        }
        current_token++;
        
        int body_start = current_token;
        
        while (is_true(condition)) {
            current_token = body_start;
            
            if (tokens[current_token].type == TOKEN_LBRACE) {
                parse_block();
            } else {
                parse_statement();
            }
            
            // Exécuter l'incrément
            current_token = increment_start;
            while (current_token < increment_end && tokens[current_token].type != TOKEN_RPAREN) {
                if (tokens[current_token].type == TOKEN_IDENTIFIER) {
                    parse_statement();
                    break;
                }
                current_token++;
            }
            
            // Réévaluer la condition
            current_token = condition_start;
            condition = evaluate_logical();
        }
        
        pop_scope();
        
        // Sauter le corps
        current_token = body_start;
        if (tokens[current_token].type == TOKEN_LBRACE) {
            int brace_count = 1;
            current_token++;
            while (current_token < token_count && brace_count > 0) {
                if (tokens[current_token].type == TOKEN_LBRACE) brace_count++;
                if (tokens[current_token].type == TOKEN_RBRACE) brace_count--;
                current_token++;
            }
        } else {
            while (current_token < token_count && tokens[current_token].type != TOKEN_SEMICOLON) {
                current_token++;
            }
            if (tokens[current_token].type == TOKEN_SEMICOLON) {
                current_token++;
            }
        }
    }
    else {
        current_token++;
    }
}

// Parser principal
void parser() {
    push_scope();
    
    while (current_token < token_count && tokens[current_token].type != TOKEN_EOF) {
        parse_statement();
    }
    
    pop_scope();
}

// Libérer la mémoire
void free_tokens() {
    for (int i = 0; i < token_count; i++) {
        free(tokens[i].value);
    }
    free(tokens);
}

void free_variables() {
    while (current_scope != NULL) {
        pop_scope();
    }
}

// Fonction principale
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <fichier.ml>\n", argv[0]);
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Erreur: impossible d'ouvrir le fichier %s\n", argv[1]);
        return 1;
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *source = malloc(size + 1);
    size_t read_size = fread(source, 1, size, file);
    source[read_size] = '\0';
    fclose(file);
    
    lexer(source);
    parser();
    
    free(source);
    free_tokens();
    free_variables();
    
    return 0;
}
