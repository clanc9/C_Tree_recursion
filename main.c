#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// characters that will be printed
#define TREE '*'
#define TRUNK '|'
#define SPACE ' '

void my_putchar(char c)
{
  write(1, &c, 1);
}

void print_tree(int size, int max_star)
{
  int i, j, k, m, n_space, x;
  int seg, start, a, tmp, n_lines, val, end;
  x = 1;
  seg = 1;
  start = 1;
  a = 0;
  while (seg <= size)  {
      n_lines = seg + 3;
      val = start;
      // draw each segment.
      // Variable n_space decreases, variable val increases
      for (j = 0; j < (n_lines); j++) {
        n_space = (max_star / 2) - (val / 2);
        while (n_space > 0) {
          my_putchar(SPACE);
          n_space--;
        }
        tmp = val;
        while (tmp > 0) {
          my_putchar(TREE);
          tmp--;
        }
        val = val + 2;
        my_putchar('\n');
      }
      val = val - 2;
      a = (seg+1) / 2;
      // defines the width of the first branch of the next segment
      start = val - (a * 2);
      seg++;
   }
}

void print_trunk(int size, int max_star)
{
  int i, k, m, n_space, n_trunk;
  i = 0;
  n_trunk = ((size / 2) * 2) + 1;
  n_space = (max_star / 2) - (n_trunk / 2);

  while (i < size) {
        for (k = 0; k < n_space; k++)
            my_putchar(SPACE);
        for (m = 0; m < n_trunk; m++)
            my_putchar(TRUNK);
        my_putchar('\n');
  i++;
  }
}

int compute_max_star(int size, int counter, int nb_lines, int max, int i)
{
    // recursive function to compute the width of the lowermost branch
    // variable counter = which branch in the segment?
    while (nb_lines > 0) {
            if (counter == size + 3) {
                  counter = 1;
                  size--;
                  i++;
                  // increase in max at each segment change
                  max = max - (2 * ((i/2) + 1));
            }
            else {
              counter++;
            }
            // max increases by 2 for each branch within a given segment
            max = max + 2;
            nb_lines--;
            // recursion
            return(compute_max_star(size, counter, nb_lines, max, i));
    }
    return(max);
}

void sapin(int size)
{
    int max_tree;
    int i, j, start, nb_lines, seg, val, end;
    nb_lines = 0;
    for (i = 0; i<size; i++)
        nb_lines = nb_lines + (i+4);
    // begins by computing the width of the lowermost branch
    // this is the recursive function
    end = compute_max_star(size, 1, nb_lines, 1, 0);
    // outputs the tree corresponding to size=number of
    // segments and end=width of last branch
    print_tree(size, end);
    print_trunk(size, end);
}

int main(int argc, char **argv)
{
  // validates that an argument is passed and
  // that this argument is higher than 0
  if (argc < 2 || atoi(argv[1]) < 1)
      return(0);
  sapin(atoi(argv[1]));
  return(0);
}
