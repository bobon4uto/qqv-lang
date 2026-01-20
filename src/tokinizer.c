#include "tokinizer.h"


bool token_important(Token token) {
  return token != TOKEN_NOT_IMPORTANT;
}
void token_print(Token token) {
  //if (token == TOKEN_NOT_IMPORTANT) return;
#define TOK_PRINT(TOKEN,_) case TOKEN: printf(#TOKEN "\n"); break;
  switch (token) {
    TOKENS(TOK_PRINT)
    default: assert("IMPOSSIBLE TOKEN!!!");
  }
}
char* token_str(Token token) {
  //if (token == TOKEN_NOT_IMPORTANT) return "";
#define TOK_STR(TOKEN,_) case TOKEN: return #TOKEN;
  switch (token) {
    TOKENS(TOK_STR)
    default: assert("IMPOSSIBLE TOKEN!!!"); return "";
  }
}
char* token_incode_str(Token token) {
  //if (token == TOKEN_NOT_IMPORTANT) return "";
#define TOK_INCODE_STR(TOKEN,STR) case TOKEN: return STR;
  switch (token) {
    TOKENS(TOK_INCODE_STR)
    default: assert("IMPOSSIBLE TOKEN!!!"); return "";
  }
}

bool one_of(char c, char* test) {
  bool ret = false;
  for (size_t i = 0; test[i]!='\0'; ++i ) {
    ret = ret || (c == test[i]);
  }
  return ret;
}
bool is_comment_start(char c) {
  return one_of(c, "`");
}
bool is_comment_end(char c) {
  return one_of(c, "\n\0");
}
bool is_string_start(char c) {
  return one_of(c, "<");
}
bool is_string_end(char c) {
  return one_of(c, ">");
}
bool is_num_part(char c) {
  return one_of(c, "1234567890.");
}
bool is_num_start(char c) {
  return one_of(c, "1234567890");
}
bool is_id_part(char c) {
  return one_of(c, "_qwertyuiopasdfghjklzxcvbnm1234567890");
}
bool is_id_start(char c) {
  return one_of(c, "_qwertyuiopasdfghjklzxcvbnm");
}
bool starts_with(Tokenizer* t, char* str) {
  return !strncmp(svs_ptr_at(t->svs, t->position), str, strlen(str));
}
char t_cur_char(Tokenizer* t) {
  return svs_char_at(t->svs, t->position);
}
char* t_cur_ptr(Tokenizer* t) {
  return svs_ptr_at(t->svs, t->position);
}
Token_Extra t_current_ex(Tokenizer* t) {
  (void)t;
  Token_Extra ret = {0};
  ret.token = TOKEN_NOT_IMPORTANT;
  size_t oldp = t->position;

  if (t->position < t->svs.len) {
#define T_STATIC_DEF(TOKEN,STR) if (starts_with(t,STR)) {ret.token = TOKEN; ret.token_step = strlen(STR);}
    STATIC_TOKENS(T_STATIC_DEF)
    //if (starts_with(t,"fn")) {ret.token = TOKEN_FUNCTION; ret.token_step = 2;}
    //if (starts_with(t,"var")) {ret.token = TOKEN_VARIABLE; ret.token_step = 3;}
    //if (starts_with(t,"(")) {ret.token = TOKEN_BRACKET_OPEN; ret.token_step = 1;}
    //if (starts_with(t,")")) {ret.token = TOKEN_BRACKET_CLOSE; ret.token_step = 1;}
    //if (starts_with(t,"{")) {ret.token = TOKEN_CURLY_BRACKET_OPEN; ret.token_step = 1;}
    //if (starts_with(t,"}")) {ret.token = TOKEN_CURLY_BRACKET_CLOSE; ret.token_step = 1;}
    //if (starts_with(t,":")) {ret.token = TOKEN_COLUMN; ret.token_step = 1;}
    //if (starts_with(t,";")) {ret.token = TOKEN_SEMICOLUMN; ret.token_step = 1;}
    //if (starts_with(t,"+")) {ret.token = TOKEN_PLUS; ret.token_step = 1;}
    //if (starts_with(t,"/")) {ret.token = TOKEN_FORWARD_SLASH; ret.token_step = 1;}
    //if (starts_with(t,"\\")) {ret.token = TOKEN_BACKWARD_SLASH; ret.token_step = 1;}
    //if (starts_with(t,"-")) {ret.token = TOKEN_MINUS; ret.token_step = 1;}
    //if (starts_with(t,"\0")) {ret.token = TOKEN_END; ret.token_step = 1;}
  //TOKEN_NOT_IMPORTANT
    if (!token_important(ret.token)) {
      //TOKEN_IDENTIFIER
      if (is_id_start(t_cur_char(t))) {
        for (;is_id_part(t_cur_char(t));t->position++) {
          ret.token = TOKEN_IDENTIFIER; ret.token_step += 1;
        }
      }
      //TOKEN_NUMBER
      if (is_num_start(t_cur_char(t))) {
        for (;is_num_part(t_cur_char(t));t->position++) {
          ret.token = TOKEN_NUMBER; ret.token_step += 1;
        }
      }
      //TOKEN_STRING
      if (is_string_start(t_cur_char(t))) {
        for (;!is_string_end(t_cur_char(t));t->position++) {
          ret.token = TOKEN_STRING; ret.token_step += 1;
        }
        ret.token_step += 1;
      }
      //TOKEN_COMMENT
      if (is_comment_start(t_cur_char(t))) {
        for (;!is_comment_end(t_cur_char(t));t->position++) {
          ret.token = TOKEN_COMMENT; ret.token_step += 1;
        }
        ret.token_step += 1;
      }

    }
  //TOKEN_END


    if ( ret.token_step == 0 ) {
      //size_t curpos = t->position++;
      //t_current_ex(t);
      ret.token_step++;
      ret.token =TOKEN_NOT_IMPORTANT;
    }
    t->position = oldp;
    return ret;
  } else {
    ret.token = TOKEN_END;
    t->position = oldp;
    return ret;
  }
}
Token t_current(Tokenizer* t) {
  return t_current_ex(t).token;
}

Token t_next(Tokenizer* t) {
  Token_Extra res = t_current_ex(t);
  t->position+=res.token_step;
  return res.token;
}
size_t t_to_y(Tokenizer* t) {
  size_t y = 1;
  for (size_t i =0; i<t->position; ++i) {
    if (svs_char_at(t->svs, i)=='\n') {
      y++;
    }
  }
  return y;
}
size_t t_to_x(Tokenizer* t) {
  size_t x = 0;
  size_t i = t->position;
  while(svs_char_at(t->svs, i)!= '\n') {
    x++;
    if ( i == 0 ) break;
    i--;
  }
  return x;
}
