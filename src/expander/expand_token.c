# include "expansion.h"

// Expands a single token string (e.g., "hello$USER") according to quote type
char *expand_token(const char *str, t_quote_type quote, t_sh *shell)
{
	size_t i;
	char *val;
	char *result;
	t_strbuilder *sb;

	if (!str)
		return (NULL);
	if (quote == S_QUOTE)
		return (ft_strdup(str));
	sb = sb_create(64);
	if (!sb)
		return (NULL);

	// chunking and substitution
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			if (str[i] == '?')
			{
				val = ft_itoa(shell->last_code);
				sb_append_str(sb, val);
				free(val);
			}
			else if (ft_isalpha(str[i]) || str[i] == '_')
			{
				size_t start = i;
				while (str[i] && ft_isalnum(str[i]))
					i++;
				char *var_name = ft_substr(str, start, i - start);
				val = get_env_value(shell->env, var_name);
				free(var_name);
				if (val)
					sb_append_str(sb, val);
			}
			else
			{
				sb_append_char(sb, '$');
				sb_append_char(sb, str[i]);
				i++;
			}
		}
		else
		{
			sb_append_char(sb, str[i]);
			i++;
		}
	}
	result = sb_build(sb);
	return (result);
}