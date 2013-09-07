#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayArray (char** in, size_t size) {
  size_t c;
  printf ("\n\rArray contents:\n\r");
  for (c = 0; c < size; c++)
    printf ("\n\rString %i: %s", c+1, in[c]);
}

void fillArray (char** out, size_t size) {
  size_t c;
  for (c = 0; c < size; c++) {
    char tmp[15];
    fflush (stdin);
    printf ("\n\rInput string %i: ", c+1);
    fgets (tmp, 15, stdin);
    out[c] = strdup(tmp);
  }
}

void freeArray (char** in, size_t size) {
  size_t c;
  for (c = 0; c < size; c++) {
    free (in[c]);
    in[c] = 0;
  }
}

int main()
{
  char** p;
  size_t size = 0;
  size_t c;

  printf ("Enter number of strings: ");
  scanf ("%i", &size);

  p = (char**) malloc (sizeof (char*) * size);
  if (!p)
    return EXIT_FAILURE;

  fillArray (p, size);
  displayArray (p, size);
  freeArray (p, size);
  free (p);

  system ("pause");
  return EXIT_SUCCESS;
}