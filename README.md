# Minishell

[https://peoriou.gitbook.io/minishell](https://peoriou.gitbook.io/minishell)

[ ] mettre le heredoc dans /tmp/heredoc < !!!!!!!!!  >
[ ] Demander a Thomas comment gerer les '.'
[ ] mkdir a  /  mkdir a/b  /  cd a/b  /  rm ./../../a  / PWD<--- (POSIX OR NOT?)
[ ] isatty ?
[ ] et le gcc?
[ ] free(entry.str) ?
[ ] make && valgrind --trace-children=yes --track-fds=yes --show-leak-kinds=all --leak-check=full --suppressions=suppression.txt ./minishell
[ ] cat /dev/urandom | valgrind --trace-children=yes --track-fds=yes --show-leak-kinds=all --leak-check=full --suppressions=suppression.txt ./minishell
[ ] enlever g3 avant push final
[ ] verifier si on a toujours besoin de termios.h
[ ] ???if (exe.blocks > 1)
		wait_for_child(entry, exe, status, i);

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

[x] Appuyer sur entree ne doit pas renvoyer 0 mais le dernier code erreur (comme les espaces et les tabs)
[x] echo sans argument doit juste ecrire un saut de ligne
[ ] <> devrait renvoyer "syntax error near unexpected token `newline'"
Nous renvoyons "syntax error near unexpected token `>'" Il faut d'abord parse > puis < dans un second temps pour obtenir le message exact, mais est-ce que ca vaut le coup ?
[ ] echo $UID a l'air de trouver une valeur qui correspond, mais qui n'est pas dans une variable d'environnement. A prendre en compte ?
[x] echo $9HOME devrait renvoyer HOME et non $9HOME
[x] faut-il mettre les chaines vides dans l'history ?
[ ] cat | rev suivi de ctrl + C devrait quand meme aller a la ligne
[x] export -HOLA=bonjour renvoie "export: -H: invalid option" avec un statut d'erreur 2
[x] echo wesh$""HOLA doit renvoyer weshHOLA
[x] $> export HOLA=bonjour
	$> export HOLA=" hola et $HOLA"
	$> echo $HOLA
		===> segfault + verifier ctrl + C
			===> disparu sans rien faire le lendemain
[x] ls apres unset PATH renvoie "command not found" au lieu de "No such file or directory"
			===> modification du message dans check path si path est nul
[ ] pwd -p renvoie en theorie "Invalid option"
[x] $> unset HOME
	$> export HOME
	$> cd
		===> pour une raison que j'ignore, "cd" renvoie "No such file or directory"
			===> disparu sans rien faire le lendemain
[x] $> mkdir a
	$> mkdir a/b
	$> cd a/b
	$> rm -r ../../a
	$> pwd
		===> "getcwd: No such file or directory"
			===> rejouter la condition si getcwd ne marche pas dans handle pwd (verifier si d'autres tests ne deviennent pas faux)
[x] Si on fait une commande suite a ce test, on quitte le shell !!! Peut-etre a cause du get files fd

[x] Unlink le heredoc quand on sort avec un signal
			===> rajouter unlink dans go heredoc
[ ] $> env -i ./minishell
	$> env
		===> ??????
[x] $> env -i ./minishell
	$> export
		===> SEGFAULT !!!
			===>rajouter la protection
			proteger exists in env
			paaser l'adreese de env comme argument a export variable
[x] exit -4 renvoie 4 au lieu de 252 (valable pour tous les negatifs) et reflechir peut-etre de nouveau au min -9223372036854775808
			===> rajouter le signe et rajouter les conditions pour sortir
			recalculer res
[x] whereis grep > Docs/bonjour resolu en initialisant msg, data, status dans la condition
[ ] $> export HOLA="bonjour hello"
	$> >$HOLA
	$> ls
		===> Mais que se passe-t-il ?
[ ] minishell > << $"hola"$"b"
> holab
> $hola$b
> $holab
		===> devrait s'arreter a holab
[ ] minishell > << $"$hola"$$"b"
> $hola$$b
> $$hola$$b
> $$hola$b
> $$$b 
> $"$hola"$$"b"
> $$b
		===> devrait s'arreter a $hola$$b
[ ] Meme chose pour ca : << ho$la$"$a"$$"b"
		===> devrait s'arreter a ho$la$a$$b
