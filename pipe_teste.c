/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_teste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluis <aluis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 00:16:33 by aluis             #+#    #+#             */
/*   Updated: 2025/11/02 00:15:07 by aluis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*int main(int ac, char *av[], char *env[])
{
    (void)ac;
    (void)av;

    int pipefd[2];
    int pid;

    char *cat_args[] = {"/bin/cat", "infile", NULL};
    char *grep_args[] = {"/usr/bin/grep", "Lausanne", NULL};

    // 1. Criar pipe
    pipe(pipefd);

    // ⭐⭐ 2. INICIALIZAR pid COM fork() ⭐⭐
    pid = fork();

    if (pid == -1) {
        // Erro no fork
        perror("fork");
        return 1;
    }
    else if (pid == 0) {
        // Processo FILHO - grep
        dup2(pipefd[0], 0);   // stdin ← pipe leitura
        close(pipefd[1]);     // fecha escrita (não usado)
        close(pipefd[0]);     // fecha após dup2

        execve("/usr/bin/grep", grep_args, env);
        perror("execve grep"); // Se execve falhar
        _exit(1);
    }
    else {
        // Processo PAI - cat
        dup2(pipefd[1], 1);   // stdout ← pipe escrita
        close(pipefd[0]);     // fecha leitura (não usado)
        close(pipefd[1]);     // fecha após dup2

        execve("/bin/cat", cat_args, env);
        perror("execve cat"); // Se execve falhar
        _exit(1);
    }

    // Código nunca alcançado devido ao execve
    return 0;
}
	*/
