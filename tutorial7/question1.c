#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define INFILE "processes.txt"

int main(void) {
	queue *head = NULL;
	head = malloc(sizeof(node_queue));
	head->next = NULL;

	delete_pid(12235,head);
	delete_name("emacs",head);
	read_file(head);
	print_list(head);

	return 0;
}

typedef struct{
	char name[256];
    int runtime;
	int pid;
    int priority;
	
}proc;

typedef struct node{
	proc process;
	struct node *next;
}node_queue;
node_queue *queue;

void delete_pid(int pid, struct proc *process) {
	queue *current = process;
	struct queue *temp;

	while(current != NULL && current->next->process.pid != pid) {
		current = current->next; 
	}
	temp = current->next;
	 current->next = temp->next;
	free(temp);
	return; 
}

void delete_name(char* name , struct proc *process) {
	queue *current = process;
	queue *temp;
	while(current != NULL && current->next->process.name != name) {
		current = current->next;
	}
		temp = current->next;
		current->next = temp->next;
		free(temp);
		return;
	}

void push(proc new_process) {
	node_queue *current = head;
	proc process = new_process;
	
	while(current->next != NULL)
		current = current->next;
	
	current->next = malloc(sizeof(struct queue));
	current->next->process = process;
	current->next->next = NULL;
}

void process_print(struct proc *process_print) {
	struct proc* process = process_print;

	printf("Name: %s\n", process->name);
	printf("pid: %d\n", process->pid);
	printf("priority: %d\n", process->priority);
	printf("runtime: %d\n", process->runtime);
	printf("%s\n\n", "-----------------");
}

void print_list(struct queue *head) {
	struct queue* current = head;

	while(current->next != NULL) {
		struct proc process = current->process;
		process_print(&process);
		current = current->next;
	}
}

void read_file(struct queue *head) {
	FILE *fp = fopen(INFILE, "r");
	char line[255];
	char *token;
	struct proc *new_process;

	while(fgets(line, sizeof(line), fp) != NULL) {	

		// allocate new proc struct
		new_process = malloc(sizeof(struct proc));
		
		// get name
		token = strtok(line, ",");
		strcpy(new_process->name, token);
		
		// get priority
		token = strtok(NULL, ",");
		sscanf(token, "%d", &new_process->priority);

		// get pid
		token = strtok(NULL, ",");
		sscanf(token, "%d", &new_process->pid);

		// get runtime
		token = strtok(NULL, "\n");
		sscanf(token, "%d", &new_process->runtime);
		
		// add to end of linked list
		push(head, *new_process);
	}
}

