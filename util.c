#include <assert.h>
#include <stdlib.h>
#import "util.h"

// From: https://github.com/syohex/emacs-lua
void bind_function(emacs_env *env, const char *name, emacs_value Sfun)
{
    emacs_value Qfset = env->intern(env, "fset");
    emacs_value Qsym = env->intern(env, name);
    emacs_value args[] = { Qsym, Sfun };

    env->funcall(env, Qfset, 2, args);
}

// From: https://github.com/syohex/emacs-lua
void provide(emacs_env *env, const char *feature)
{
    emacs_value Qfeat = env->intern(env, feature);
    emacs_value Qprovide = env->intern (env, "provide");
    emacs_value args[] = { Qfeat };

    env->funcall(env, Qprovide, 1, args);
}

// From: https://phst.eu/emacs-modules.html#copy_string_contents
bool copy_string_contents (emacs_env *env, emacs_value value, char **buffer, size_t *size) {
  ptrdiff_t buffer_size;
  if (!env->copy_string_contents (env, value, NULL, &buffer_size))
    return false;
  assert (env->non_local_exit_check (env) == emacs_funcall_exit_return);
  assert (buffer_size > 0);
  *buffer = malloc ((size_t) buffer_size);
  if (*buffer == NULL)
    {
      env->non_local_exit_signal (env, env->intern (env, "memory-full"),
                                  env->intern (env, "nil"));
      return false;
    }
  ptrdiff_t old_buffer_size = buffer_size;
  if (!env->copy_string_contents (env, value, *buffer, &buffer_size))
    {
      free (*buffer);
      *buffer = NULL;
      return false;
    }
  assert (env->non_local_exit_check (env) == emacs_funcall_exit_return);
  assert (buffer_size == old_buffer_size);
  *size = (size_t) (buffer_size - 1);
  return true;
}

emacs_value make_dds_solution_table(emacs_env *env, int values[5][4], int numRows, int numCols) {
  emacs_value* tableRows = malloc(sizeof(emacs_value) * numRows);
  for (int i = 0; i < numRows; i++) {
    emacs_value* rowCols = malloc(sizeof(emacs_value) * numCols);
    for (int j = 0; j < numCols; j++) {
      rowCols[j] = env->make_integer(env, values[i][j]);
    }

    tableRows[i] =  env->funcall(env, env->intern(env, "list"), numCols, rowCols);
    free(rowCols);
  }

  emacs_value ret =  env->funcall(env, env->intern(env, "list"), numRows, tableRows);
  free(tableRows);
  return ret;
}
