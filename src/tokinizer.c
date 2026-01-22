#define TOKENIZER_INTERNAL
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

bool one_of(char c, const char* test) {
  bool ret = false;
  for (size_t i = 0; test[i]!='\0'; ++i ) {
    ret = ret || (c == test[i]);
  }
  return ret;
}
bool one_of_str(char* s, char** test) {
  bool ret = false;
  for (size_t i = 0; test[i]!=NULL; ++i ) {
    ret = ret || ( !strncmp(s, test[i], strlen(test[i])) );
  }
  return ret;
}
size_t which_of_str(char* s, char** test) {
  for (size_t i = 0; test[i]!=NULL; ++i ) {
    if ( !strncmp(s, test[i], strlen(test[i])) ) return i+1;
  }
  return 0;
}
size_t find_str_get_len(char* s, char** test) {
  size_t i = which_of_str(s, test);
  if (i>0) {
    size_t slen = strlen(test[i-1]);
    return slen;
  }
  return 0; // didn't find
}
size_t is_some_end(char* s, char** some,  size_t type_index) {
  if ( !strncmp(s, some[type_index], strlen(some[type_index])) ) {
    return strlen(some[type_index]);
  } else {
    return 0;
  }
}
bool is_string_start(char c) {
  return one_of(c, "\"");
}
bool is_string_end(char c) {
  return one_of(c, "\"");
}
bool is_num_part(char c) {
  return one_of(c, num_parts);
}
bool is_num_start(char c) {
  return one_of(c, num_starts);
}
bool is_id_part(char c) {
  return one_of(c, id_parts );
}
bool is_id_start(char c) {
  return one_of(c, id_starts );
}
bool is_static_word(Tokenizer* t, char* str) {
  return !strncmp(svs_ptr_at(t->svs, t->position), str, strlen(str));
}
char t_cur_char(Tokenizer* t) {
  return svs_char_at(t->svs, t->position);
}
char* t_cur_ptr(Tokenizer* t) {
  return svs_ptr_at(t->svs, t->position);
}
size_t get_some_len(char* s, const char** some) {
  for (size_t i = 0; some[i]!=NULL; ++i ) {
    if ( !strncmp(s, some[i], strlen(some[i])) ) return (strlen(some[i]));
  }
  return 0;
}
size_t get_exact_len(char* s, const char* exact) {
  if ( !strncmp(s, exact, strlen(exact)) ) return (strlen(exact));
  return 0;
}
size_t get_some_type(char* s, const char** some) {
  for (size_t i = 0; some[i]!=NULL; ++i ) {
    if ( !strncmp(s, some[i], strlen(some[i])) ) return (i);
  }
  return 0;
}
Token_Extra test_some(Tokenizer *t, const char** some_start,const char** some_end, Token token) {
  Token_Extra ret = {0};
  size_t start_len = get_some_len(t_cur_ptr(t), some_start);
  if (start_len > 0) {
    ret.token = token;
    size_t start_type = get_some_type(t_cur_ptr(t), some_start);
    t->position += start_len;
    ret.token_step += start_len;
    size_t end_len =
        get_exact_len(t_cur_ptr(t), some_end[start_type]);
    for (; end_len == 0; t->position++) {
      if (t->position >= t->svs.len) {
        end_len = 0;
        break;
      }
      end_len = get_exact_len(t_cur_ptr(t), some_end[start_type]);
      if (end_len) break;
      ret.token_step += 1;

    }
    ret.token_step += end_len;
  }
  return ret;
}


Token_Extra t_current_ex(Tokenizer* t) {
  (void)t;
  Token_Extra ret = {0};
  ret.token = TOKEN_NOT_IMPORTANT;
  size_t oldp = t->position;
  if (t->position < t->svs.len) {

#define T_VARIABLED_DEF(TOKEN, STR)                                            \
  if (!token_important(ret.token)) {                                           \
      ret = test_some(t, TOKEN##_starts, TOKEN##_ends, TOKEN);                 \
  }

      VARIABLED_TOKENS(T_VARIABLED_DEF)

    bool was_word = false;

      if (!token_important(ret.token)) {

#define T_STATIC_DEF(TOKEN, STR)                                               \
  if (is_static_word(t, STR)) {                                                \
    ret.token = TOKEN;                                                         \
    ret.token_step = strlen(STR);                                              \
    was_word = true; \
  }

      STATIC_TOKENS(T_STATIC_DEF)
    }
    if ( !token_important(ret.token) || ( was_word && is_id_part(svs_char_at(t->svs, t->position+ret.token_step)  ) ) ) {
      //TOKEN_IDENTIFIER
      if (is_id_start(t_cur_char(t))) { 
        ret.token_step = 0;
        for (;is_id_part(t_cur_char(t));t->position++) {
          ret.token = TOKEN_IDENTIFIER; ret.token_step += 1;
        }
      }
    }
    if (!token_important(ret.token)) {
      //TOKEN_NUMBER
      if (is_num_start(t_cur_char(t))) {
        for (;is_num_part(t_cur_char(t));t->position++) {
          ret.token = TOKEN_NUMBER; ret.token_step += 1;
        }
      }
    }
    //
    //
    //
    //
  //TOKEN_NOT_IMPORTANT
    if ( ret.token_step == 0 ) {
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
  while (true) {
    res = t_current_ex(t);
    if (token_important(res.token)) break;
    t->position+=res.token_step;
  }
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
