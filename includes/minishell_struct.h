/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 13:36:05 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/29 14:49:54 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef	struct		s_lst
{
	char			*name;
	char			*value;
	struct s_lst	*next;
}					t_lst;

enum				e_tokentype{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = 0,
	CHAR_DOBLEGREATER = '+',
	TOKEN = -1,
};

enum {
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_IN_ESCAPESEQ,
	STATE_GENERAL,
};

typedef	enum {
	NODE_PIPE = 0,
	NODE_BCKGRND = 1,
	NODE_SEQ = 2,
	NODE_REDIRECT_IN = 3,
	NODE_REDIRECT_OUT = 4,
	NODE_REDIRECT_AFTER = 8,
	NODE_CMDPATH = 5,
	NODE_ARGUMENT = 6,
	NODE_DATA = 7,
}	t_nodetype;

typedef	struct		s_ms
{
	struct s_tok	*tok;
	struct s_lexer	*lexer;
	struct s_ast	*exectree;
	struct s_cmd	*cmd;
	struct s_g_glob	*g_glob;
}					t_ms;

typedef	struct		s_tok
{
	char			*data;
	int				type;
	struct s_tok	*next;
}					t_tok;

typedef	struct		s_lexer
{
	t_tok			*llisttok;
	int				nbr_toks;
	int				i;
	int				j;
	int				state;
	int				char_type;
	t_tok			*token;
	char			*req;
	int				size;
}					t_lexer;

typedef	struct		s_cmd
{
	int				argc;
	char			**argv;
	int				pipe_in;
	int				pipe_out;
	int				fd_pipe_read;
	int				fd_pipe_write;
	char			*redirect_in;
	char			*redirect_out;
	char			*redirect_after;
}					t_cmd;

typedef	struct		s_ast
{
	int				type;
	char			*data;
	struct s_ast	*left;
	struct s_ast	*right;

}					t_ast;

typedef	struct		s_g_glob
{
	t_lst	*exp;
	t_lst	*env;
	int		ret;
	pid_t	pid;
}					t_glob;

typedef	struct		s_ce
{
	char	*tmp;
	char	**tmp_split;
	t_tok	*new;
	t_tok	*cursor;
	t_tok	*previous;
	t_tok	*save;
	int		i;
}					t_ce;

#endif
