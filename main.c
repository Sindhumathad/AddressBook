#include "contact.h"
int main()
{
    AddressBook addressBook;  // Corrected variable name to match the structure name

    // Call the init function to load dummy contacts
    initialize(&addressBook);
    //all function calls should be inside the main 
    for (int i = 0; i < addressBook.contactCount; i++) 
    {
        printf("Name: %s, Phone: %s, Email: %s\n", 
               addressBook.contacts[i].name, 
               addressBook.contacts[i].phone, 
               addressBook.contacts[i].email);
    }
    while (1) {
        // Display the menu inside the main function
        printf("\nAddress Book Menu:\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. List Contacts\n");
        printf("6. Exit\n");
        printf("Choose an option (1-6): ");

        int option;
        scanf("%d", &option);  // Read option from the user

        switch (option) {
            case 1:
                addContact(&addressBook);  // Add a contact
                break;
            case 2:
                searchContact(&addressBook);  // Search for a contact
                break;
            case 3:
                editContact(&addressBook);  // Edit a contact
                break;
            case 4:
                deleteContact(&addressBook);  // Delete a contact
                break;
            case 5:
                listContacts(&addressBook);  // List all contacts
                break;
            case 6:
                printf("Exiting the program...\n");
                return 0;  // Exit the program
            default:
                printf("Invalid option! Please choose a valid option (1-6).\n");
                break;
        }
    }
    return 0;
}


