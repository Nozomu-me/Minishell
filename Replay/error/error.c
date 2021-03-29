#include "../parsing.h"


void	ft_error(char *str, char *first_color, char *second_color, int *error)
{
	ft_putstr_fd(first_color, 1);
	ft_putendl_fd(str, 1);
	ft_putstr_fd(second_color, 1);
	*error = 1;
}

/* void	ft_splited(char *line)
{

}

int main()
{

}
 */
