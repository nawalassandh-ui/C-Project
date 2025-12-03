#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100

// Structure to store each task
typedef struct {
    char name[100];
    int isCompleted; // 0 - Pending, 1 - Done
} Task;

Task tasks[MAX_TASKS];
int taskCount = 0;
const char *FILENAME = "tasks.txt";

// Function declarations
void loadTasks();
void saveTasks();
void addTask();
void viewTasks();
void markTaskComplete();
void deleteTask();

int main() {
    int choice;
    loadTasks(); // Load existing tasks from file if present

    while (1) {
        printf("\n==== TO-DO LIST MANAGER ====\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Mark Task Complete\n");
        printf("4. Delete Task\n");
        printf("5. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markTaskComplete(); break;
            case 4: deleteTask(); break;
            case 5:
                saveTasks();
                printf("Saved Successfully! Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

// Load tasks from file
void loadTasks() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) return; // If file doesn't exist, skip loading

    taskCount = 0;
    while (fscanf(file, "%[^|]|%d\n", tasks[taskCount].name, &tasks[taskCount].isCompleted) != EOF) {
        taskCount++;
    }
    fclose(file);
}

// Save tasks to file
void saveTasks() {
    FILE *file = fopen(FILENAME, "w");
    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%s|%d\n", tasks[i].name, tasks[i].isCompleted);
    }
    fclose(file);
}

// Add new task
void addTask() {
    if (taskCount >= MAX_TASKS) {
        printf("Task List Full!\n");
        return;
    }
    printf("Enter task description: ");
    fgets(tasks[taskCount].name, sizeof(tasks[taskCount].name), stdin);

    // Remove newline char from fgets
    tasks[taskCount].name[strcspn(tasks[taskCount].name, "\n")] = '\0';

    tasks[taskCount].isCompleted = 0;
    taskCount++;
    printf("Task added successfully!\n");
}

// Display tasks
void viewTasks() {
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("\n---- Your Tasks ----\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. %s [%s]\n", i + 1, tasks[i].name,
               tasks[i].isCompleted ? "Done" : "Pending");
    }
}

// Mark a task completed
void markTaskComplete() {
    int num;
    viewTasks();
    if (taskCount == 0) return;

    printf("Enter task number to mark as completed: ");
    scanf("%d", &num);

    if (num < 1 || num > taskCount) {
        printf("Invalid task number!\n");
        return;
    }
    tasks[num - 1].isCompleted = 1;
    printf("Task marked as completed!\n");
}

// Delete a task
void deleteTask() {
    int num;
    viewTasks();
    if (taskCount == 0) return;

    printf("Enter task number to delete: ");
    scanf("%d", &num);

    if (num < 1 || num > taskCount) {
        printf("Invalid task number!\n");
        return;
    }

    for (int i = num - 1; i < taskCount - 1; i++) {
        tasks[i] = tasks[i + 1]; // Shift remaining tasks up
    }
    taskCount--;
    printf("Task deleted successfully!\n");
}
