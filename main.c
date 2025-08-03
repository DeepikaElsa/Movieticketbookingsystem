#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_TICKETS 100

// Structure to represent an invoice
typedef struct {
  int customer_id;
  int movie_number;
  int tickets_purchased;
} Invoice;

int tickets_available[5] = {NUM_TICKETS, NUM_TICKETS, NUM_TICKETS, NUM_TICKETS, NUM_TICKETS};
pthread_mutex_t ticket_mutex;

// Function to get the movie name based on its number
const char* get_movie_name(int movie_number) {
  switch (movie_number) {
    case 1:
      return "Leo";
    case 2:
      return "Frozen";
    case 3:
      return "Loki";
    case 4:
      return "One Piece";
    case 5:
      return "Home Alone";
    default:
      return "Unknown Movie";
  }
}

void* customer_thread(void* arg) {
  Invoice* invoice = (Invoice*)arg;
  int tickets_to_purchase;

  printf("Customer %d is buying how many tickets for %s\n", invoice->customer_id, get_movie_name(invoice->movie_number));

  // Read the number of tickets and clear the input buffer
  scanf("%d", &tickets_to_purchase);
  fflush(stdin); // Clear the input buffer

  pthread_mutex_lock(&ticket_mutex);

  if (tickets_available[invoice->movie_number - 1] >= tickets_to_purchase) {
    tickets_available[invoice->movie_number - 1] -= tickets_to_purchase;
    printf("Customer %d successfully purchased %d tickets for %s. %d tickets remaining\n",
          invoice->customer_id, tickets_to_purchase, get_movie_name(invoice->movie_number), tickets_available[invoice->movie_number - 1]);
  } else {
    printf("Customer %d couldn't purchase %d tickets for %s. Only %d tickets remaining\n",
          invoice->customer_id, tickets_to_purchase, get_movie_name(invoice->movie_number), tickets_available[invoice->movie_number - 1]);
  }

  pthread_mutex_unlock(&ticket_mutex);

  // Update the invoice with purchase details
  invoice->tickets_purchased = tickets_to_purchase;

  return NULL;
}

int main() {
  pthread_t customers[100];
  Invoice invoices[100];
  pthread_mutex_init(&ticket_mutex, NULL);
  int i, a;

  printf("Enter the number of customers in line: ");
  scanf("%d", &a);

  for (i = 0; i < a; i++) {
    int movie_number, customer_id = i + 1;

    printf("Enter the movie number (1-5) for customer %d: ", customer_id);
    scanf("%d", &movie_number);
    fflush(stdin); // Clear the input buffer

    if (movie_number >= 1 && movie_number <= 5) {
      invoices[i].customer_id = customer_id;
      invoices[i].movie_number = movie_number;

      pthread_create(&customers[i], NULL, customer_thread, &invoices[i]);
      pthread_join(customers[i], NULL);
    } else {
      printf("Invalid movie number. Please enter a number between 1 and 5.\n");
      i--; // Decrement the loop variable to repeat the iteration for the same customer.
    }
  }

  // Display invoice details
  for (int k = 0; k < a; k++) {
    printf("Invoice for Customer %d:\n", invoices[k].customer_id);
    printf("Movie: %s\n", get_movie_name(invoices[k].movie_number));
    printf("Tickets Purchased: %d\n", invoices[k].tickets_purchased);
    printf("\n");
  }

  pthread_mutex_destroy(&ticket_mutex);
  return 0;
}

