# Minishell

[https://peoriou.gitbook.io/minishell](https://peoriou.gitbook.io/minishell)

[ ] mettre le heredoc dans /tmp/heredoc < !!!!!!!!!  >
[ ] Demander a Thomas comment gerer les '.'
[ ] mkdir a  /  mkdir a/b  /  cd a/b  /  rm ./../../a  / PWD<--- (POSIX OR NOT?)
[ ] isatty ?
[ ] et le gcc?
[ ] free(entry.str) ?
[ ] valgrind --trace-children=yes --track-fds=yes --show-leak-kinds=all --leak-check=full --suppressions=suppression.txt ./minishell
[ ] cat /dev/urandom | valgrind --trace-children=yes --track-fds=yes --show-leak-kinds=all --leak-check=full --suppressions=suppression.txt ./minishell

[x] les pipes sans rien derriere
[x] le outfile efface dans 'cat infile > outfile > ok'
[x] gestion des erreurs malloc dans subshells
[x] $$
[x] ${HOME}${PATH
[x] ?
[x] $"$ "
[x] $!LANG
[x] $"$hello"
[x] retirer les entry dans exec subshell et execute command (param)
[x] retirer token dans exec subshell (param)
[x] "bash" in error messages of exit builtins
[x] alphanum + '_' and not only alpha + '_' in expansions
[x] declare -x lang (call only "export" in bash)
[x] handle_cd_in_subshell

[x] ?$HOME
[x] export HOLA="   -n bonjour   "
[x] export HOLA="bonjour    "/
[x] export HOLA="  bonjour  hey  "
[x] unset PATH ... ls
[x] unset PATH ... cat Makefile
[x] exit -9223372036854775808
[x] cat Makefile |
[x] whereis grep > Docs/bonjour
[x] KEEP QUOTED TYPE OF NEXT NODE IF NECESSARY FOR HERE_DOC DELIMIMTER
	Forgot everything?
	Try : cat << EOF | cat << 'EOF' | cat << ho"la" | cat << "'EOF'"
	with extensions as inputs
