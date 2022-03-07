#include "pendu.h"

void	ep_putchar(char c)
{
	write(1, &c, 1);
}