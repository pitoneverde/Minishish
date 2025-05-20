/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:07:48 by plichota          #+#    #+#             */
/*   Updated: 2025/05/19 18:56:44 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "ast.h"

/*
GRAMMAR:
command      ::= simple_command | pipeline | compound_command
simple_command ::= WORD { WORD | redirection }
pipeline     ::= command { '|' command }
compound_command ::= command ('&&' | '||') command
redirection  ::= '<' WORD | '>' WORD | '>>' WORD | '<<' WORD

parse_command       -> simple command and args
parse_pipeline      -> command | command
parse_expression    -> full command with redirs, pipes, etc.
*/

// tokens
typedef enum e_token_type 
{
	TKN_WORD,	// done
	TKN_PIPE,
	TKN_REDIR_OUT,
	TKN_REDIR_IN,
	TKN_APPEND,
	TKN_HEREDOC,
	TKN_S_QUOTED,
	TKN_D_QUOTED,
	TKN_ERROR,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	char			*error;
}	t_token;

// tokenizer
t_list *tokenize(const char *line);	//element type char*
void free_raw_tokens(t_list **raw_tokens);
char *read_next_token(const char *line, const char **p);

// tokenizer_utils
int is_operator_char(char c);
int is_whitespace(char c);
char *read_word(const char *line, const char **p);
char *read_operator(const char *line, const char **p);
char *read_quoted(const char *line, const char **p, char quote);

// lexer
t_list *lex(t_list *raw_tokens);
void free_token(void *ptr);
void free_token_list(t_list **list);
int strip_if_quoted(t_token *token);
int check_for_errors(t_token *token);

// lexer utils
t_token_type classify_token(const char *raw_token);
int is_quoted(const char *raw_token, int len, char quote);
int is_malformed(const char *raw_token, int len);

// debugging
const char *token_type_name(t_token_type type);
void print_raw_tokens(t_list *tokens);
void print_lexed_tokens(t_list *tokens);

// parser
t_ast *parse_expression(t_list **tokens);
t_ast *parse(t_list *tokens);

#endif // !PARSER_H
