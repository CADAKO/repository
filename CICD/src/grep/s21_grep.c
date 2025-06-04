#include "s21_grep.h"

#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int err = 1;
  if (argc > 2) {
    struct flags flag = {0, 0, 0, 0, 0, 0, 0, 0};
    int how_many_file = 0;
    int how_many_string = 0;
    // char *text[argc - 1];
    // char *pattern[argc - 1];
    char **text = malloc(argc * sizeof(char *));
    char **pattern = malloc(argc * sizeof(char *));
    getoptions(argc, argv, pattern, &how_many_string, text, &how_many_file,
               &flag);

    for (int now_filename_index = 0; now_filename_index < how_many_file;
         now_filename_index++) {
      file_scaner(text[now_filename_index], pattern, how_many_string, &flag);
    }
    free(text);
    free(pattern);
    err = 0;
  }
  return err;
}

int getoptions(int argcp, char **argvp, char **patternp, int *how_many_strings,
               char **textp, int *how_many_files, struct flags *flagp) {
  int err = 0;
  int rez = 0;
  while (((rez = getopt_long(argcp, argvp, "e:ivclnsh", NULL, NULL)) != -1) &&
         err == 0) {
    if (rez == 'e') {
      flagp->e = 1;
      patternp[*how_many_strings] = optarg;
      *how_many_strings = *(how_many_strings) + 1;
    }

    if (rez == 'i') flagp->i = 1;
    if (rez == 'v') flagp->v = 1;
    if (rez == 'c') flagp->c = 1;
    if (rez == 'l') flagp->l = 1;
    if (rez == 'n') flagp->n = 1;
    if (rez == 's') flagp->s = 1;
    if (rez == 'h') flagp->h = 1;
    if (rez == '?') err = 1;
  }
  if (err == 0) {
    if (flagp->e == 0) {
      patternp[0] = argvp[optind];
      (*how_many_strings)++;
      optind++;
    }
    for (*how_many_files = 0; optind < argcp; (*how_many_files)++) {
      textp[*how_many_files] = argvp[optind];
      optind++;
    }
    if (*how_many_files == 1) flagp->h = 1;
  }
  return err;
}

void comp_find(char *buffer, char **patterns, int how_many_strings,
               int *strnumber, int *check, struct flags *flagp) {
  (*strnumber)++;
  int cflags = REG_EXTENDED | REG_NEWLINE;
  regmatch_t pmatch[1];
  const size_t nmatch = 1;
  regex_t reg;
  if (flagp->i == 1) {
    cflags = REG_EXTENDED | REG_ICASE | REG_NEWLINE;
  }
  for (int i = 0; i < how_many_strings; i++) {
    int status;
    regcomp(&reg, patterns[i], cflags);
    status = regexec(&reg, buffer, nmatch, pmatch, 0);
    if (status == 0) *check = 1;
    regfree(&reg);
  }
}

void c_flag_format(struct flags *flagp, int compare_count, int strnumber,
                   char *filename) {
  if (flagp->h == 0) printf("%s:", filename);
  if (flagp->l == 0) {
    if (flagp->v == 1) {
      printf("%d\n", strnumber - compare_count);
    } else {
      printf("%d\n", compare_count);
    }
  } else {  // flagl==1
    if (flagp->v == 1) {
      if (strnumber != compare_count)
        printf("1\n");
      else
        printf("0\n");
    } else {
      if (compare_count)
        printf("1\n");
      else
        printf("0\n");
    }
  }
}

int file_scaner(char *filename, char **patterns, int how_many_strings,
                struct flags *flagp) {
  int err = 0;
  FILE *fp;
  fp = fopen(filename, "r");
  if (fp == NULL) {
    if (flagp->s == 0) {
      fprintf(stderr, "grep: %s: No such file or directory\n", filename);
    }
    err = 1;
  }
  if (err == 0) {
    int strnumber = 0;
    int compare_count = 0;
    while (!feof(fp)) {
      char buffer[4096] = "";
      int check = 0;
      fgets(buffer, 4096, fp);
      if (buffer[0] != 0) {
        comp_find(buffer, patterns, how_many_strings, &strnumber, &check,
                  flagp);
        if (check == 1) compare_count++;
        if (flagp->v == 1) {
          if (check == 1)
            check = 0;
          else
            check = 1;
        }
        if (flagp->c == 0 && flagp->l == 0 && check == 1) {
          if (flagp->h == 0) printf("%s:", filename);
          if (flagp->n == 1) printf("%d:", strnumber);
          printf("%s", buffer);
          if (buffer[strlen(buffer) - 1] != '\n') printf("\n");
        }
      }
    }  // while
#ifdef __APPLE__
    if (flagp->c) {
      c_flag_format(flagp, compare_count, strnumber, filename);
    }
#elif __linux__
    if (flagp->c && flagp->l == 0) {
      c_flag_format(flagp, compare_count, strnumber, filename);
    }
#endif

    if (flagp->l) {
      if ((flagp->v == 0 && compare_count > 0) ||
          ((flagp->v == 1 && compare_count != strnumber)))
        printf("%s\n", filename);
    }
    fclose(fp);
  }
  return err;
}