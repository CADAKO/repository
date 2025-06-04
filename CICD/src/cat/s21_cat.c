#include "s21_cat.h"

#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc > 1) {
    char *short_flags = "beEnstTv";
    struct option long_flags[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                  {"number", no_argument, NULL, 'n'},
                                  {"squeeze-blank", no_argument, NULL, 's'},
                                  {NULL, 0, NULL, 0}};
    int opt = 0;
    while ((opt = getopt_long(argc, argv, short_flags, long_flags, NULL)) !=
           -1) {
      if (opt == 'b') flag.b = 1;
      if (opt == 'v') flag.v = 1;
      if (opt == 'e') {
        flag.e = 1;
        flag.v = 1;
      }
      if (opt == 'E') flag.e = 1;
      if (opt == 'n') flag.n = 1;
      if (opt == 's') flag.s = 1;
      if (opt == 't') {
        flag.t = 1;
        flag.v = 1;
      }
      if (opt == 'T') flag.t = 1;
    }

    int now_filename_index = optind;
    int line_counter = 1;
    int blank_line = 0;
    while (now_filename_index < argc) {
      reader(now_filename_index, argv, &flag, &line_counter, &blank_line);
      now_filename_index++;
    }
  }
  return (0);
}

void flag_s_format(int current_char, int last_char, int **blank_line,
                   int *skip_print_flag) {
  if (current_char == 10 && (last_char == 10 || last_char == EOF)) {
    (**blank_line)++;
  } else {
    **blank_line = 0;
  }
  if (**blank_line > 1) {
    *skip_print_flag = 1;
  }
}

void flag_b_format(int current_char, int last_char, int **line_counter) {
  if ((**line_counter == 1) && (current_char != 10)) {
    printf("%6d\t", **line_counter);
    (**line_counter)++;
  } else if ((current_char != 10) && (last_char == 10)) {
    printf("%6d\t", **line_counter);
    (**line_counter)++;
  }
}

void flag_v_format(int current_char, int last_char, int *skip_print_flag) {
  if (current_char >= 0 && current_char < 32 && current_char != 10 &&
      current_char != 9 && current_char != EOF) {
    *skip_print_flag = 1;
  }
  if (last_char >= 0 && last_char < 32 && last_char != 10 && last_char != 9 &&
      last_char != EOF) {
    printf("^%c", last_char + 64);
  }
  if (current_char == 127) {
    *skip_print_flag = 1;
  }
  if (last_char == 127) {
    printf("^%c", 63);
  }
}

void flag_n_format(int last_char, int **blank_line, int **line_counter) {
  if (((**line_counter == 1) || (last_char == 10) ||
       (**line_counter != 1 && last_char == EOF)) &&
      **blank_line <= 1) {
    printf("%6d\t", **line_counter);
    (**line_counter)++;
  }
}

int reader(int filename_index, char **argv1, struct flags *flag,
           int *line_counter, int *blank_line) {
  int err = 0;
  FILE *fp;
  fp = fopen(argv1[filename_index], "r");
  if (fp == NULL) {
    fprintf(stderr, "cat: %s: No such file or directory\n",
            argv1[filename_index]);
    err = -1;
  }
  if (err == 0) {
#ifdef __APPLE__
    *line_counter = 1;
#endif
    int last_char;
    int current_char;
#ifdef __APPLE__
    *blank_line = 0;
#endif
    current_char = fgetc(fp);
    last_char = EOF;
    while (current_char != EOF) {
      int skip_print_flag = 0;
      if (flag->s == 1) {
        flag_s_format(current_char, last_char, &blank_line, &skip_print_flag);
      }
      if (flag->b == 1) {
        flag_b_format(current_char, last_char, &line_counter);
      } else if (flag->n == 1) {
        flag_n_format(last_char, &blank_line, &line_counter);
      }
      if (flag->t == 1) {
        if (current_char == 9) {
          printf("%c", 94);
          printf("%c", 73);
          skip_print_flag = 1;
        }
      }
      if (flag->e == 1) {
        if (current_char == 10 && (*blank_line) < 2) printf("$");
      }
      if (flag->v == 1) {
        flag_v_format(current_char, last_char, &skip_print_flag);
      }
      last_char = current_char;
      current_char = fgetc(fp);
      if (skip_print_flag == 0) printf("%c", last_char);
    }
    fclose(fp);
  }
  return err;
}