#include "vups.h"
#include "tokinizer.def.h"
//last match gets priority

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

bool one_of(char c, const char* test);

size_t is_comment_start(char* s);

size_t is_comment_end(char* s);

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
