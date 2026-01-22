#ifdef TOKENIZER_INTERNAL
static const char *TOKEN_COMMENT_starts[] = {"//" , "/*" , NULL};
static const char *TOKEN_COMMENT_ends[]   = {"\n" , "*/" , NULL};
static const char *TOKEN_STRING_starts[]  = {"\"" , "<"  , NULL};
static const char *TOKEN_STRING_ends[]    = {"\"" , ">"  , NULL};
#define NUMBERS "1234567890"
#define ABC "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm"
static const char* num_starts = NUMBERS;
static const char* num_parts  = NUMBERS ".";
static const char* id_starts  = "_" ABC;
static const char* id_parts   = "_" ABC NUMBERS;
// it is possible to support widechars with approach similar to string and comment, but then arrays look ugly


//static const char *string_starts[] = {"\"","<", NULL};
//static const char *string_ends[] = {"\"",">", NULL};
#endif // TOKENIZER_INTERNAL
#define                        STATIC_TOKENS(T)   \
  T(TOKEN_TYPEDEF,             "type"           ) \
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

#define                        VARIABLED_TOKENS(T)          \
  T(TOKEN_COMMENT,             "$`"             )           \
  T(TOKEN_STRING,        "$<str>"         )                 \

#define                  TOKENS(T)        \
  T(TOKEN_NOT_IMPORTANT, "$NOT_IMPORTANT" ) \
  STATIC_TOKENS(T)                          \
  T(TOKEN_IDENTIFIER,    "$ID"            ) \
  T(TOKEN_NUMBER,        "$0"             ) \
  VARIABLED_TOKENS(T)                       \
  T(TOKEN_END,           "$end"           ) \

//for thouse tokens second parameter is only for visualization
