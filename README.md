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
[ ] et le gcc?
[ ] mettre le heredoc dans /tmp/heredoc


/*
	KEEP QUOTED TYPE OF NEXT NODE IF NECESSARY FOR HERE_DOC DELIMIMTER
	Forgot everything?
	Try : cat << EOF | cat << 'EOF' | cat << ho"la" | cat << "'EOF'"
	with extensions as inputs
*/
