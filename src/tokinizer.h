#include "vups.h"
//last match gets priority
#define                        STATIC_TOKENS(T)   \
  T(TOKEN_VARIABLE,            "var"            ) \
  T(TOKEN_RETURN,              "return"         ) \
  T(TOKEN_FUNCTION,            "fn"             ) \
  T(TOKEN_BRACKET_OPEN,        "("              ) \
  T(TOKEN_BRACKET_CLOSE,       ")"              ) \
  T(TOKEN_CURLY_BRACKET_OPEN,  "{"              ) \
  T(TOKEN_CURLY_BRACKET_CLOSE, "}"              ) \
  T(TOKEN_COLUMN,              ":"              ) \
  T(TOKEN_SEMICOLUMN,          ";"              ) \
  T(TOKEN_EQUALS,              "="              ) \
  T(TOKEN_EQUALS_EQUALS,       "=="             ) \
  T(TOKEN_PLUS,                "+"              ) \
  T(TOKEN_MINUS,               "-"              ) \
  T(TOKEN_FORWARD_SLASH,       "/"              ) \
  T(TOKEN_BACKWARD_SLASH,      "\\"             ) \

#define                        TOKENS(T)          \
  T(TOKEN_NOT_IMPORTANT,       "$NOT_IMPORTANT" ) \
  STATIC_TOKENS(T)                                \
  T(TOKEN_IDENTIFIER,          "$ID"            ) \
  T(TOKEN_NUMBER,              "$0"             ) \
  T(TOKEN_STRING,              "$<str>"         ) \
  T(TOKEN_COMMENT,             "$`"             ) \
  T(TOKEN_END,                 "$end"           ) \

#define TOK_ENUM_FIELD(TOKEN,_) TOKEN,
typedef enum {
  TOKENS(TOK_ENUM_FIELD)
} Token;
bool token_important(Token token);
void token_print(Token token);
char* token_str(Token token);
char* token_incode_str(Token token);
typedef struct Token_Extra {
  Token token;
  size_t token_step;
} Token_Extra;
typedef struct Tokenizer {
  String_Variable_Slice svs;
  size_t position;
} Tokenizer;
Token t_current(Tokenizer* t);

bool one_of(char c, char* test);

bool is_comment_start(char c);

bool is_comment_end(char c);

bool is_string_start(char c);
bool is_string_end(char c);
bool is_num_part(char c);
bool is_num_start(char c);
bool is_id_part(char c);
bool is_id_start(char c);
bool starts_with(Tokenizer* t, char* str);
char t_cur_char(Tokenizer* t);
char* t_cur_ptr(Tokenizer* t);
Token_Extra t_current_ex(Tokenizer* t);
Token t_current(Tokenizer* t);
Token t_next(Tokenizer* t);
size_t t_to_y(Tokenizer* t);
size_t t_to_x(Tokenizer* t);
