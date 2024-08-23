#include <stdio.h>
#include <string.h>

int	is_space(char c)
{
	if (c == '\t')
	{
		return 1;
	}
	return 0;
}
int main()
{
	int i = 0;
	int count = i;
	char *str= "				    ";
	while (str[i])
	{
		if (is_space(str[i]))
			count++;
		i++;
	}
	printf("count is: %lu and %d\n", strlen(str) , count);
}