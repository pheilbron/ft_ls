
#include "ft_ls_options.h"

int	set_long_form_option(t_options *ops)
{
	return (ops->long_form = 1);
}

int	set_rev_option(t_options *ops)
{
	return (ops->rev = 1);
}

int	set_rec_option(t_options *ops)
{
	return (ops->rec = 1);
}

int	set_all_option(t_options *ops)
{
	return (ops->all = 1);
}

int	set_by_time_option(t_options *ops)
{
	return (ops->by_time = 1);
}
