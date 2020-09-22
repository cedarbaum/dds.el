#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "emacs-module.h"
#include "dds/include/dll.h"

int plugin_is_GPL_compatible;

int maxThreadsSet = 0;

int main() {
#if defined(__linux) || defined(__APPLE__)
   SetMaxThreads(0);
#endif

   struct ddTableDealPBN tableDealPBN = { "N:4.KJ32.842.AQ743 JT987.Q876.AK5.2 AK532.T.JT6.T985 Q6.A954.Q973.KJ6" };

   struct ddTableResults table;
   int res = CalcDDtablePBN(tableDealPBN, &table);

   if (res != RETURN_NO_FAULT) {
     char line[80];
     ErrorMessage(res, line);
     printf("DDS error: %s\n", line);
   }

   // Print results
   char suitNames[][80] = { "S", "H", "D", "C", "NT" };
   printf("     N    E    S    W\n");
   for (int suitId = 0; suitId < 5; suitId++) {
     printf("%2s | %02d | %02d | %02d | %02d |\n",
            suitNames[suitId],
            table.resTable[suitId][0],
            table.resTable[suitId][1],
            table.resTable[suitId][2],
            table.resTable[suitId][3]);
   }

   return 0;
}

emacs_value dds_calc_dd_table_pbn(emacs_env *env, ptrdiff_t nargs, emacs_value *args, void *data) {
  char *buffer;
  size_t size;
  copy_string_contents(env, args[0], &buffer, &size);

#if defined(__linux) || defined(__APPLE__)
  if (!maxThreadsSet) {
    // BUG: Weird behavior where setting this more than once causes a crash.
    SetMaxThreads(0);
    maxThreadsSet = 1;
  }
#endif

  struct ddTableDealPBN tableDealPBN;
  strcpy(tableDealPBN.cards, buffer);

  // For testing:
  /* struct ddTableDealPBN tableDealPBN = { "N:4.KJ32.842.AQ743 JT987.Q876.AK5.2 AK532.T.JT6.T985 Q6.A954.Q973.KJ6" }; */

  struct ddTableResults table;
  int res = CalcDDtablePBN(tableDealPBN, &table);

  if (res != RETURN_NO_FAULT) {
    // Should probably do something here...
    char line[80];
    ErrorMessage(res, line);
    printf("DDS error: %s\n", line);
    return NULL;
  }

  return make_dds_solution_table(env, table.resTable, 5, 4);
}


int emacs_module_init(struct emacs_runtime *ert) {
  emacs_env *env = ert->get_environment(ert);

  DEFUN(
        "dds-calc-dd-table-pbn",
        dds_calc_dd_table_pbn,
        1,
        1,
        "Calculate maximum score for each declarer and each trump suit",
        NULL);
  provide(env, "dds");

  return 0;
}
