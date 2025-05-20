#include "minishell.h"

int main(void)
{
	const char *input = "echo hello world";
	t_list *tokens = tokenize(input);
	t_list *tmp = tokens;

	while (tmp)
	{
		printf("token: [%s]\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	free_raw_tokens(&tokens);
	return 0;
}