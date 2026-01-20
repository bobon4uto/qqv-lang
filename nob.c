#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

#define FAIL do { \
  printf("%s:%d: \n", __FILE__, __LINE__);       \
  exit(1); } while(0)

Cmd cmd0 = {0};
Cmd *cmd = &cmd0;

void cc() {
  nob_cc(cmd);
  cmd_append(cmd, "-g");
  nob_cc_flags(cmd);
}
void cc_o();
typedef void (*fn_t)();
bool exe(const char* in, const char* out, fn_t extra);
bool o(const char* in, const char* out, fn_t extra);
bool run(const char* exe_file);
void build_nobo() {
  cmd_append(cmd, "-x");
  cmd_append(cmd, "c");
}
void add_nobo() {
  nob_cc_inputs(cmd, "build/obj/nob.o");
}
void add_tokinizer() {
  nob_cc_inputs(cmd, "build/obj/tokinizer.o");
}
int main(int argc, char **argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);
  mkdir_if_not_exists("build/");
  mkdir_if_not_exists("build/obj");
  o("nob.h", "build/obj/nob.o", build_nobo);
  o("src/tokinizer.c", "build/obj/tokinizer.o", NULL);
  exe("src/main.c", "build/qqvc",add_tokinizer);
  cmd_append(cmd, "build/qqvc");
  cmd_append(cmd, "examples/hello.qq");
  cmd_run(cmd);
    //cmd_append(cmd, "valgrind", "--leak-check=full", "build/qqvc", "examples/hello.qq");
    //cmd_run(cmd);
  return 0;
}
void cc_o() {
  cmd_append(cmd, "-c");
}
bool exe(const char* in, const char* out, fn_t extra) {
  cc();
  if (extra) {
    extra();
  }
  nob_cc_inputs(cmd, in);
  nob_cc_output(cmd, out);
  return cmd_run(cmd);
}
bool o(const char* in, const char* out, fn_t extra) {
  cc();
  if (extra) {
    extra();
  }
  cc_o();
  nob_cc_inputs(cmd, in);
  nob_cc_output(cmd, out);
  return cmd_run(cmd);
}
bool run(const char* exe_file) {
  cmd_append(cmd, exe_file);
  return cmd_run(cmd);
}
