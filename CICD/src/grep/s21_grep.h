#ifndef S21_GREP_H
#define S21_GREP_H

struct flags {
  unsigned int e : 1;
  unsigned int i : 1;
  unsigned int v : 1;
  unsigned int c : 1;
  unsigned int l : 1;
  unsigned int n : 1;
  unsigned int s : 1;
  unsigned int h : 1;
};

int getoptions(int argcp, char **argvp, char **patternp, int *how_many_strings,
               char **textp, int *how_many_files, struct flags *flagp);

int file_scaner(char *filename, char **patterns, int how_many_strings,
                struct flags *flag);

void comp_find(char *buffer, char **patterns, int how_many_strings,
               int *strnumber, int *check, struct flags *flagp);

void c_flag_format(struct flags *flagp, int compare_count, int strnumber,
                   char *filename);

#endif