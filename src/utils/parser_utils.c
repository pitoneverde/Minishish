#include "minishell.h"

void advance(t_parser *p)
{
	if (!p->tokens)
	{
		p->current = NULL;
		return ;
	}
	p->tokens = p->tokens->next;
	if (p->tokens)
		p->current = (t_token *)p->tokens->content;
	else
		p->current = NULL;
}

t_token *peek(t_parser *p)
{
	return p->current;
}

int match(t_parser *p, t_token_type type)
{
	if (p->current && p->current->type == type)
		return (advance(p), 1);
	return 0;
}
