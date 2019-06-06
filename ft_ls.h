

#ifndef FT_LS
# define FT_LS

# include "ft_ls_options.h"
# include "vector.h"

void	parse_input(char *options, t_options *ops);
void	print_col(t_vector **tab, int len, int max_word, int row_len);

#endif
