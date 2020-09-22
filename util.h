#include "emacs-module.h"

bool copy_string_contents (emacs_env *env, emacs_value value, char **buffer, size_t *size);

emacs_value make_dds_solution_table(emacs_env *env, int values[5][4], int numRows, int numCols);

// From: https://github.com/syohex/emacs-lua/blob/master/lua-core.c
#define DEFUN(lsym, csym, amin, amax, doc, data) \
    bind_function (env, lsym, env->make_function(env, amin, amax, csym, doc, data))
void bind_function(emacs_env *env, const char *name, emacs_value Sfun);

void provide(emacs_env *env, const char *feature);
