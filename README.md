# Minishell

[https://peoriou.gitbook.io/minishell](https://peoriou.gitbook.io/minishell)

[ ] Demander a Thomas comment gerer les '.'
[x] les pipes sans rien derriere
[x] le outfile efface dans 'cat infile > outfile > ok'
[x] gestion des erreurs malloc dans subshells
[x] $$
[x] ${HOME}${PATH
[x] ?
[x] $"$ "
[x] $!LANG
[x] $"$hello"
[ ] free(entry.str) ?
[ ] retirer les entry dans exec subshell et execute command (param)
[ ] retirer token dans exec subshell (param)
[ ] isatty ?
[ ] "bash" in error messages of exit builtins
[ ] alphanum + '_' and not only alpha + '_' in expansions
[ ] et le gcc?
[ ] mettre le heredoc dans /tmp/heredoc
[ ] declare -x lang (call only "export" in bash)
[ ] handle_cd_in_subshell

[ ] ?$HOME
[ ] export HOLA="   -n bonjour   "
[ ] export HOLA="bonjour    "/
[ ] export HOLA="  bonjour  hey  "
[ ] unset PATH ... ls
[ ] unset PATH ... cat Makefile
[ ] exit -9223372036854775808
[ ] cat Makefile |
[ ] whereis grep > Docs/bonjour


/*
	KEEP QUOTED TYPE OF NEXT NODE IF NECESSARY FOR HERE_DOC DELIMIMTER
	Forgot everything?
	Try : cat << EOF | cat << 'EOF' | cat << ho"la" | cat << "'EOF'"
	with extensions as inputs
*/
