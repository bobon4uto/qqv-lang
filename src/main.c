#include "tokinizer.h"
#include <stdio.h>
#define VUPS_IMPLEMENTATION
#include "vups.h"
#if false
fn main () : int {

var a : int = 0;
a = a+1;
//print("qq!!");
123
}
#endif

void l_error_unexpected_expected(Tokenizer * t,Token unexpected,Token expected) {
  printf("examples/hello.qq:%zu:%zu: expected %s, found %s\n", t_to_y(t), t_to_x(t), token_incode_str(expected),token_incode_str(unexpected));
  exit(1);
}
int main(int argc, char **argv) {
  (void)(argc);
  (void)(argv);
  PTR(String_Holder, sh);
  read_file(sh, argv[1]);
  String_Variable_Slice svs_src = svs_link_full(sh);
  (void)svs_src;
  // String_Variable_Slice_Vector svs_v = svs_split( svs_link_full(sh), '\n');
  // for (size_t i = 0; i< svs_v.count; ++i) {
  //   printf("[");
  //   svs_print(svs_v.items[i]);
  //   printf("]\n");
  // }
  // v_free(&svs_v);
  PTR(Tokenizer, t);
  t->svs = svs_src;
  Token token = TOKEN_END;
  Token prev_token = TOKEN_END;
  do {
    token = t_current(t);
    if (prev_token== TOKEN_FUNCTION) {
      if (token != TOKEN_IDENTIFIER) {
        l_error_unexpected_expected(t, token, TOKEN_FUNCTION);
      }
    }
    //printf("examples/hello.qq:%zu:%zu: %s\n", t_to_y(t), t_to_x(t),
    //       token_str(token));
    printf("%s", token_incode_str(token));
    t_next(t);
    prev_token = token;
  } while (token != TOKEN_END);
  return 0;
}
