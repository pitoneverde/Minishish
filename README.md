# Minishish
mini shell bash
(bash is kept as a reference in its core function in dev)

### Run minishell
make
./minishell

### Run tests
make test

### Manual compilation of integration test
cc ./tests/integration/test_1.c ./include/minishell.h ./unity/src/unity.c -Iinclude -Ilibs/libft/include -Iunity/src
