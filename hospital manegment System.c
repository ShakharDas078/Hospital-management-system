#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the patient structure
struct Patient {
    char name[50];
    int age;
    char gender; // 'F' for female, 'M' for male
    struct Patient* next;
};

// Define the queue structure
struct Queue {
    struct Patient* front;
    struct Patient* rear;
};

// Initialize a new queue
void initializeQueue(struct Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

// Enqueue a patient into the queue
void enqueue(struct Queue* q, struct Patient* patient) {
    if (q->rear == NULL) {
        q->front = patient;
        q->rear = patient;
    } else {
        q->rear->next = patient;
        q->rear = patient;
    }
    patient->next = NULL;
}

// Dequeue a patient from the queue
struct Patient* dequeue(struct Queue* q) {
    if (q->front == NULL) {
        return NULL; // Queue is empty
    }
    struct Patient* patient = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    return patient;
}

int main() {
    struct Queue femaleQueue, childrenQueue;
    initializeQueue(&femaleQueue);
    initializeQueue(&childrenQueue);

    int option;

    do {
        printf("\nMenu:\n");
        printf("1. Add patient\n");
        printf("2. Serve next patient (female)\n");
        printf("3. Serve next patient (children)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1: {
                struct Patient* newPatient = (struct Patient*)malloc(sizeof(struct Patient));
                printf("Enter patient name: ");
                scanf("%s", newPatient->name);
                printf("Enter patient age: ");
                scanf("%d", &newPatient->age);
                printf("Enter patient gender (F/M): ");
                scanf(" %c", &newPatient->gender);

                if (newPatient->gender == 'F') {
                    enqueue(&femaleQueue, newPatient);
                } else if (newPatient->age <= 12) {
                    enqueue(&childrenQueue, newPatient);
                } else {
                    printf("Only female or children patients are allowed in these queues.\n");
                    free(newPatient);
                }
                break;
            }
            case 2: {
                struct Patient* patient = dequeue(&femaleQueue);
                if (patient != NULL) {
                    printf("Serving next female patient: %s\n", patient->name);
                    free(patient);
                } else {
                    printf("No female patients in the queue.\n");
                }
                break;
            }
            case 3: {
                struct Patient* patient = dequeue(&childrenQueue);
                if (patient != NULL) {
                    printf("Serving next children patient: %s\n", patient->name);
                    free(patient);
                } else {
                    printf("No children patients in the queue.\n");
                }
                break;
            }
            case 4: {
                // Free the remaining patients in the queues
                struct Patient* patient;
                while ((patient = dequeue(&femaleQueue)) != NULL) {
                    free(patient);
                }
                while ((patient = dequeue(&childrenQueue)) != NULL) {
                    free(patient);
                }
                printf("Exiting the program.\n");
                break;
            }
            default:
                printf("Invalid option. Please select a valid option.\n");
        }
    } while (option != 4);

    return 0;
}
