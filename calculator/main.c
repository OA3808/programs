#include "cs136.h"

// add(m, n) adds n to m
int add(int m, int n) {
  if (m >= 0) {
    if (n <= INT_MAX - m) {
      return m + n;
    }
    printf("OVERFLOW\n");
    exit(EXIT_SUCCESS);
  } else {
    if (n >= INT_MIN - m) {
      return m + n;
    }
    printf("OVERFLOW\n");
    exit(EXIT_SUCCESS);
  }
}
// sub(m, n) finds the difference of m and n
int sub(int m, int n) {
  trace_int(n);
  if (m >= 0) {
    if (n >= -(INT_MAX - m)) {
      return m - n;
    }
    printf("OVERFLOW\n");
    exit(EXIT_SUCCESS);
  } else {
    trace_msg(sub -> m < 0);
    if (n <= -(INT_MIN - m)) {
      trace_int(m);
      trace_int(n);
      return m - n;
    }
    printf("OVERFLOW\n");
    exit(EXIT_SUCCESS);
  }
}

// mult(m, n) finds the product of m and n
int mult(int m, int n) {
  trace_int(n);
  if (m == 0 || n == 0) {
    return 0;
  } else if (m > 0) {
    trace_msg(m > 0);
    if (n > 0) {
      trace_msg(n > 0);
      if (n <= INT_MAX / m) {
        trace_msg(m * n);
        return m * n;
      }
      printf("OVERFLOW\n");
      exit(EXIT_SUCCESS);
    }
    if (n < 0) {
      trace_msg(n < 0);
      if (n >= INT_MIN / m) {
        return m * n;
      }
      printf("OVERFLOW\n");
      exit(EXIT_SUCCESS);
    }
  } else if (m < 0) {
    trace_msg(m < 0);
    if (n > 0) {
      trace_msg(n > 0);
      trace_int(m);
      trace_int(n);
      if (n <= INT_MIN / m) {
        return m * n;
      }
      printf("OVERFLOW\n");
      exit(EXIT_SUCCESS);
    }
    if (n < 0) {
      trace_msg(n < 0);
      if (n >= INT_MAX / m) {
        return m * n;
      }
      printf("OVERFLOW\n");
      exit(EXIT_SUCCESS);
    }
  }
  exit(EXIT_SUCCESS);
}

// divide(m, n) find the quotient of m divided by n
int divide(int m, int n) {
  if (n == 0) {
    printf("DIVIDE BY ZERO\n");
    exit(EXIT_SUCCESS);
  } else if (m == INT_MIN && n == -1) {
    printf("OVERFLOW\n");
    exit(EXIT_SUCCESS);
  }
  return m / n;
}

///////////////////////////////////////////////////////////////////////////// 
// Do not modify this function

// You MUST use this function to read in an int from input

// read_int_or_exit() reads in an integer from input, or exits (terminates)
//   the program if an int cannot be successfully read in
// note: terminates the program quietly with no output displayed
// effects: reads input
//          may terminate program (a rare side effect we don't normally
//                                 worry about in this course)
int read_int_or_exit(void) {
  int input = 0;
  if (scanf("%d", &input) != 1) {
    exit(EXIT_SUCCESS);
  }
  return input;
}
/////////////////////////////////////////////////////////////////////////////

int main(void) {
  int ADD = lookup_symbol("add");
  int MUL = lookup_symbol("mult");
  int SUB = lookup_symbol("sub");
  int DIV = lookup_symbol("div");
  int m = 0;
  while(1) {
    int cmd = read_symbol();
    int n = read_int_or_exit();
    trace_int(m);
    if (cmd == ADD) {
      m = add(m, n);
      printf("%d\n", m);
    } else if (cmd == MUL) {
      m = mult(m, n);
      printf("%d\n", m);
    } else if (cmd == SUB) {
      m = sub(m, n);
      printf("%d\n", m);
    } else if (cmd == DIV) {
      m = divide(m, n);
      printf("%d\n", m);
    } else {
      exit(EXIT_SUCCESS);
    }
  }
}
