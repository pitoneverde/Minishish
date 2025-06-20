# include "expansion.h"

static char *substitute_vars(const char *str, t_sb *sb, t_sh *sh);
static void handle_code(t_sb *sb, t_sh *shell);
static void handle_dollar(const char *str, size_t *i, t_sb *sb);
static void handle_var(const char *str, size_t *i, t_sb *sb, t_sh *sh);

// Expands a single token string (e.g., "hello$USER") according to quote type
char *expand_token(const char *str, t_quote_type quote, t_sh *shell)
{
	t_sb *sb;

	if (!str)
		return (NULL);
	if (quote == S_QUOTE)
		return (ft_strdup(str));
	sb = sb_create(64);
	if (!sb)
		return (NULL);
	return (substitute_vars(str, sb, shell));
}

static char *substitute_vars(const char *str, t_sb *sb, t_sh *sh)
{
	size_t i;
	char	*result;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			if (str[i++] == '?')
				handle_code(sb, sh);
			else if (ft_isalpha(str[i]) || str[i] == '_')
				handle_var(str, &i, sb, sh);
			else
				handle_dollar(str, &i, sb);
		}
		else
			sb_append_char(sb, str[i++]);
	}
	result = sb_build(sb);
	return (result);
}

static void handle_code(t_sb *sb, t_sh *sh)
{
	char	*val;

	val = ft_itoa(sh->last_code);
	if (val)
	{
		sb_append_str(sb, val);
		free(val);
	}
}

static void handle_dollar(const char *str, size_t *i, t_sb *sb)
{
	sb_append_char(sb, '$');
	sb_append_char(sb, str[*i]);
	(*i)++;
}

static void handle_var(const char *str, size_t *i, t_sb *sb, t_sh *sh)
{
	size_t	start;
	char	*key;
	char	*val;

	start = *i;
	while (str[*i] && ft_isalnum(str[*i]))
		(*i)++;
	key = ft_substr(str, start, *i - start);
	val = get_env_value(sh->env, key);
	free(key);
	if (val)
	{
		sb_append_str(sb, val);
		free(val);
	}
}
