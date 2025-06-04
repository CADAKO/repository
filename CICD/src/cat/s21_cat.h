#ifndef S21_CAT_H
#define S21_CAT_h

struct flags {
  unsigned int b : 1;
  unsigned int e : 1;
  unsigned int n : 1;
  unsigned int s : 1;
  unsigned int t : 1;
  unsigned int v : 1;
} flag;
int reader(int filename_index, char **argv1, struct flags *flag,
           int *line_counter, int *blank_line);
void flag_b_format(int current_char, int last_char, int **line_counter);
void flag_n_format(int last_char, int **blank_line, int **line_counter);
void flag_s_format(int current_char, int last_char, int **blank_line,
                   int *skip_print_flag);
void flag_v_format(int current_char, int last_char, int *skip_print_flag);

#endif