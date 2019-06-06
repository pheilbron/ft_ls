#include "libft.h"
#include "vector.h"

int		fill_in(char *s, int max_word_len, size_t word_len)
{
	int	i;

	i = 0;
	while ((int)word_len + i < max_word_len + 1)
		s[i++] = ' ';
	return (i);
}

void	print_col(t_vector	**tab, int len, int max_word, int row_len)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(sizeof(*ret) * len * (max_word + 1) + (len / row_len) +
			((len % row_len) ? 1 : 0));
	i = 0;
	j = 0;
	while (j < len)
	{
		ft_memcpy(ret + i,
				tab[(j % row_len) * (row_len - 1) + (j / row_len)]->data,
				tab[(j % row_len) * (row_len - 1) + (j / row_len)]->pos);
		i += tab[(j % row_len) * (row_len - 1) + (j / row_len)]->pos;
		if (j % row_len == row_len - 1)
			ret[i++] = '\n';
		else
			i += fill_in(ret + i, max_word,
					tab[(j % row_len) * (row_len - 1) + (j / row_len)]->pos);
		j++;
	}
	write(1, ret, i);
	free(ret);
}
