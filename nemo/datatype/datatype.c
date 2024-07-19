#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_command
{
    char                **cmd;

    int                 input;
    int                 output;
	int					type;

    struct s_command   *prev;
    struct s_command   *next;
}   t_command;

// Function to create a new command node
t_command *create_command_node(char **cmd, int input, int output, int type) {
    t_command *new_node = (t_command *)malloc(sizeof(t_command));
    if (!new_node) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    
    new_node->cmd = cmd;
    new_node->input = input;
    new_node->output = output;
    new_node->type = type;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}

// Function to append a command node to the list
void append_command(t_command **head, t_command *new_node) {
    if (!*head) {
        *head = new_node;
        return;
    }

    t_command *temp = *head;
    while (temp->next) {
        temp = temp->next;
    }

    temp->next = new_node;
    new_node->prev = temp;
}

// Function to print the command list
void print_command_list(t_command *head) {
    t_command *temp = head;
    while (temp) {
        printf("Command: ");
        for (char **arg = temp->cmd; *arg; ++arg) {
            printf("%s ", *arg);
        }
        printf("\nInput: %d, Output: %d, Type: %d\n", temp->input, temp->output, temp->type);
        temp = temp->next;
    }
}

int	datatype(t_command *command_list)
{
	t_command *temp = command_list;

    while (temp)
	{
		if (temp->type == 0)
		{
			if (temp->cmd[0] == ">" || temp->cmd[0] == ">>" || temp->cmd[0] == "<" || temp->cmd[0] == "<<")
			{
				if (temp->next == NULL) // si le suivant est null il y a erreur
					return (0);
				temp->type = 1;			// type 1 correspond au token
				temp->next->type = 2;	// type 2 au fichier il est forcement precedé d un type 1
			}
			else if (temp->cmd[0] == "|")
			{
				if (temp->next == NULL || temp->prev == NULL)
					return (0);
				temp->type = 3;			// type 3 correspond au pipe
			}
			else
				temp->type = 4;			// type 4 correspond a une cmd
		}
		temp = temp->next;
	}
	return (1);
}
t_command* find_command_backward(t_command *node)
{
    while (node->prev != NULL && node->prev->type != 3)
	{
		printf("%s\n", node->cmd[0]);
        node = node->prev;
        if (node->type == 4)
            return node;
    }
    return NULL;
}

t_command* find_command_forward(t_command *node)
{
    while (node->next != NULL && node->next->type != 3)
	{
		printf("%s\n", node->cmd[0]);
        node = node->next;
        if (node->type == 4)
            return node;
    }
    return NULL;
}

int handle_redirection_output(t_command *temp)
{
	int fd;
	t_command *browse;

	fd = open(temp->next->cmd[0], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (0);
	browse = find_command_backward(temp);
	if (!browse)
		browse = find_command_forward(temp->next);
	if (browse)
		browse->output = fd;
	else
		return (0);
	return (1);
}

int handle_redirection_input(t_command *temp)
{
	t_command	*browse;
	int			fd;

	fd = open(temp->next->cmd[0], O_RDONLY);
	if (fd == -1)
		return (0);
	browse = find_command_backward(temp);
	if (!browse) 
		browse = find_command_forward(temp->next);
	if (browse) 
		browse->input = fd;
	else
		return (0);
	return (1);
}

int handle_pipe(t_command *temp)
{
    int 		tube[2];
	t_command 	*browse;

    pipe(tube);
    temp->input = tube[1];
    temp->output = tube[0];
    browse = find_command_backward(temp);
    if (browse)
        browse->output = temp->input;
    else
        return (0);
    browse = find_command_forward(temp);
    if (browse)
        browse->input = temp->output;
    else
        return (0);
    return (1);
}

int setup_in_out(t_command *command_list)
{
    t_command *temp;

	temp = command_list;
    while (temp) 
	{
        if (temp->cmd[0] == ">" || temp->cmd[0] == ">>")
        {
            if (!handle_redirection_output(temp))
                return (0);
        } 
        else if (temp->cmd[0] == "<" || temp->cmd[0] == "<<")
        {
            if (!handle_redirection_input(temp))
                return (0);
        } 
        else if (temp->cmd[0] == "|") 
        {
            if (!handle_pipe(temp))
                return (0);
        }
        temp = temp->next;
    }
    return (1);
}

// int	setup_in_out(t_command *command_list)
// {
// 	t_command	*temp = command_list;
// 	int			fd;
// 	t_command	*browse;
// 	int			tube[2];

// 	while (temp)
// 	{
		
// 		if (temp->cmd[0] == ">" || temp->cmd[0] == ">>")
// 		{
// 			fd = open(temp->next->cmd[0], O_WRONLY | O_TRUNC | O_CREAT, 0644); 	// ouvre le fd du fichier du node suivant
// 			if (fd == -1)
// 				return (0);
// 			browse = temp;
// 			while (browse->prev != NULL && browse->prev->type != 3)			// remonte dans la liste jusqua arriver au debut ou a un pipe
// 			{
// 				browse = browse->prev;
// 				if (browse->type == 4)										// si la commande est trouver change son input
// 				{
// 					browse->output = fd;
// 					break;
// 				}
// 			}
// 			if (browse->type != 4)											// si la commande n'est pas trouver en remontant la chaine
// 			{
// 				browse = temp->next;										// on parcours la liste en partant du node suivant le token
// 				while (browse->next != NULL && browse->next->type != 3)		// parcours la liste jusqua arriver a la fin ou a un pipe
// 				{
// 					browse = browse->next;
// 					if (browse->type == 4)									// si la commande est trouver change son input
// 					{
// 						browse->output = fd;
// 						break;
// 					}
// 				}
// 			}
// 			if (browse->type != 4)											// si la commande n'est pas trouver il y a une erreur dans l'input du programme
// 				return (0);
// 		}

// 		else if (temp->cmd[0] == "<" || temp->cmd[0] == "<<")
// 		{
// 			fd = open(temp->next->cmd[0], O_RDONLY); 						// ouvre le fd du fichier du node suivant
// 			if (fd == -1)
// 				return (0);
// 			browse = temp;
// 			while (browse->prev != NULL && browse->prev->type != 3)			// remonte dans la liste jusqua arriver au debut ou a un pipe
// 			{
// 				browse = browse->prev;
// 				if (browse->type == 4)										// si la commande est trouver change son input
// 				{
// 					browse->input = fd;
// 					break;
// 				}
// 			}
// 			if (browse->type != 4)											// si la commande n'est pas trouver en remontant la chaine
// 			{
// 				browse = temp->next;										// on parcours la liste en partant du node suivant le token
// 				while (browse->next != NULL && browse->next->type != 3)		// parcours la liste jusqua arriver a la fin ou a un pipe
// 				{
// 					browse = browse->next;
// 					if (browse->type == 4)									// si la commande est trouver change son input
// 					{
// 						browse->input = fd;
// 						break;
// 					}
// 				}
// 			}
// 			if (browse->type != 4)											// si la commande n'est pas trouver il y a une erreur dans l'input du programme
// 				return (0);
// 		}

// 		else if (temp->cmd[0] == "|")
// 		{
// 			pipe(tube);
// 			temp->input = tube[1];
// 			temp->output = tube[0];
// 			browse = temp;
// 			while (browse->prev != NULL && browse->prev->type != 3)			// remonte dans la liste jusqua arriver au debut ou a un pipe
// 			{
// 				browse = browse->prev;
// 				if (browse->type == 4)										// si la commande est trouver change son input
// 				{
// 					browse->output = temp->input;
// 					break;
// 				}
// 			}
// 			if (browse->type != 4)											// si la commande n'est pas trouver il y a une erreur dans l'input du programme
// 				return (0);
// 			browse = temp;
// 			while (browse->next != NULL && browse->next->type != 3)			// parcours la liste jusqua arriver a la fin ou a un pipe
// 				{
// 					browse = browse->next;
// 					if (browse->type == 4)									// si la commande est trouver change son input
// 					{
// 						browse->input = temp->output;
// 						break;
// 					}
// 				}
// 				if (browse->type != 4)											// si la commande n'est pas trouver il y a une erreur dans l'input du programme
// 					return (0);
// 		}
// 		temp = temp->next;
// 	}
// 	return (1);
// }
// sort < input.txt > sorted_output.txt
// sort < input.txt sort |  tr 'a-z' 'A-Z' |  ls > sorted_output.txt
// < input.txt sort | sort > sorted_output.txt
int main() {
    // Define commands
    char *cmd2[] = {"file1.txt", NULL};
    char *cmd1[] = {"<<", NULL};
    char *cmd3[] = {"cmd1", NULL};
    char *cmd4[] = {"|", NULL};
    char *cmd7[] = {"cmd2", NULL};
    char *cmd5[] = {">>", NULL};
    char *cmd6[] = {"file2.txt", NULL};

    // Create command nodes with input, output, and type as NULL
    t_command *command1 = create_command_node(cmd1, 0, 0, 0);
    t_command *command2 = create_command_node(cmd2, 0, 0, 0);
    t_command *command3 = create_command_node(cmd3, 0, 0, 0);
    t_command *command4 = create_command_node(cmd4, 0, 0, 0);
    t_command *command5 = create_command_node(cmd5, 0, 0, 0);
    t_command *command6 = create_command_node(cmd6, 0, 0, 0);
    t_command *command7 = create_command_node(cmd7, 0, 0, 0);

    // Create the command list and append the nodes
    t_command *command_list = NULL;
    append_command(&command_list, command1);
    append_command(&command_list, command2);
    append_command(&command_list, command3);
    append_command(&command_list, command4);
    append_command(&command_list, command5);
    append_command(&command_list, command6);
    append_command(&command_list, command7);

	datatype(command_list);
	setup_in_out(command_list);

    // Print the command list
    print_command_list(command_list);

    // Free the command list
    t_command *temp;
    while (command_list) {
        temp = command_list;
        command_list = command_list->next;
        free(temp);
    }

    return 0;
}