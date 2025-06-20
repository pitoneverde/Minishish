#ifndef SHELL_H
# define SHELL_H

typedef struct s_sh
{
	t_list *env;		// list of t_env
	int last_code;		// for $?
	int is_interactive; // set if running interactively
} t_sh;

#endif