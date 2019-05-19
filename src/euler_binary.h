/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * euler.h
 **********************************************************************/
#include "euler.h"

bool*	binary_sequence_of(int x);
int		binary_sequence_count(int x);
bool	binary_sequence_is_palindrome(bool* b, int len);
void	binary_sequence_print(bool* b, int len);

bool*	append_bool(bool* set, bool b, int* len_ptr);
bool*	prepend_bool(bool* set, bool b, int* len_ptr);
