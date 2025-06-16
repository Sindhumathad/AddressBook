#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

void listContacts(AddressBook *addressBook) {
    if (addressBook->contactCount == 0) {
        printf("No contacts available.\n");
        return;
    }

    printf("Here is the list of contacts:\n");
    printf("%-3s %-20s %-15s %-30s\n", "No.", "Name", "Phone No.", "Mail ID"); // Header
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("%-3d %-20s %-15s %-30s\n", i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
}

void addContact(AddressBook *addressBook) {
    if (addressBook->contactCount >= MAX_CONTACTS) {
        printf("Address book is full! Cannot add more contacts.\n");
        return;
    }

    int numberOfContacts;
    printf("How many contacts do you want to create? ");
    scanf("%d", &numberOfContacts);
    getchar(); // To consume the leftover newline after scanf

    if (numberOfContacts + addressBook->contactCount > MAX_CONTACTS) {
        printf("Cannot add that many contacts. You can add up to %d more contacts.\n", MAX_CONTACTS - addressBook->contactCount);
        return;
    }

    for (int i = 0; i < numberOfContacts; i++) {
        Contact newContact;
        int isDuplicate;

        // Input for name with uniqueness check
        do {
            isDuplicate = 0;
            printf("Enter name for contact %d: ", i + 1);
            fgets(newContact.name, sizeof(newContact.name), stdin);
            newContact.name[strcspn(newContact.name, "\n")] = 0;  // Remove the newline character

            // Check for duplicate name
            for (int j = 0; j < addressBook->contactCount; j++) {
                if (strcmp(addressBook->contacts[j].name, newContact.name) == 0) {
                    printf("Contact with name '%s' already exists! Please enter a different name.\n", newContact.name);
                    isDuplicate = 1;
                    break;
                }
            }
        } while (isDuplicate);

        // Input for phone number with uniqueness check
        int isValidPhone;
        do {
            isDuplicate = 0;
            isValidPhone = 0;

            printf("Enter phone for contact %d (10 digits): ", i + 1);
            scanf("%19s", newContact.phone);
            getchar(); // Consume the leftover newline

            // Check for exactly 10 digits and that all characters are digits
            if (strlen(newContact.phone) == 10) {
                isValidPhone = 1; // Assume valid until proven otherwise
                for (int k = 0; k < 10; k++) {
                    if (!isdigit(newContact.phone[k])) {
                        isValidPhone = 0; // Not valid if any character is not a digit
                        printf("Phone number must be exactly 10 digits. Please try again.\n");
                        break;
                    }
                }
            }
            else {
                printf("Phone number must be exactly 10 digits. Please try again.\n");
            }

            // Check for duplicate phone
            if (isValidPhone) {
                for (int j = 0; j < addressBook->contactCount; j++) {
                    if (strcmp(addressBook->contacts[j].phone, newContact.phone) == 0) {
                        printf("Contact with phone number '%s' already exists! Please enter a different phone number.\n", newContact.phone);
                        isDuplicate = 1;
                        break;
                    }
                }
            }
        } while (isDuplicate || !isValidPhone);

        // Input for email with uniqueness check and @gmail.com validation
        int isValidEmail;
        do {
            isDuplicate = 0;
            isValidEmail = 0;
            printf("Enter email for contact %d : ", i + 1);
            fgets(newContact.email, sizeof(newContact.email), stdin);
            newContact.email[strcspn(newContact.email, "\n")] = 0; // Remove newline

            // Check if email ends with @gmail.com
            if (strstr(newContact.email, "@gmail.com") == newContact.email + strlen(newContact.email) - 10) {
                isValidEmail = 1;
            } else {
                printf("Email must end with '@gmail.com'. Please try again.\n");
            }

            // Check for duplicate email
            if (isValidEmail) {
                for (int j = 0; j < addressBook->contactCount; j++) {
                    if (strcmp(addressBook->contacts[j].email, newContact.email) == 0) {
                        printf("Contact with email '%s' already exists! Please enter a different email.\n", newContact.email);
                        isDuplicate = 1;
                        break;
                    }
                }
            }
        } while (isDuplicate || !isValidEmail);

        // Add the new contact to the address book
        addressBook->contacts[addressBook->contactCount++] = newContact;
        printf("Contact %d added successfully!\n", i + 1);
    }
}

void searchContact(AddressBook *addressBook) {
    char searchName[50];
    printf("Enter name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;  // Remove newline character
    int found = 0;

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, searchName) == 0) {
            printf("Found Contact: Name: %s, Phone: %s, Email: %s\n",
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            found = 1;
            break; // Exit the loop if the contact is found
        }
    }

    if (!found) {
        printf("Contact not found.\n");
    }
}

void editContact(AddressBook *addressBook) {
    char editName[50];
    printf("Enter the name of the contact to edit: ");
    fgets(editName, sizeof(editName), stdin);
    editName[strcspn(editName, "\n")] = 0;  // Remove newline character

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, editName) == 0) {
            printf("Editing Contact: %s\n", addressBook->contacts[i].name);
            printf("Enter new phone: ");
            fgets(addressBook->contacts[i].phone, sizeof(addressBook->contacts[i].phone), stdin);
            addressBook->contacts[i].phone[strcspn(addressBook->contacts[i].phone, "\n")] = 0;  // Remove newline

            printf("Enter new email: ");
            fgets(addressBook->contacts[i].email, sizeof(addressBook->contacts[i].email), stdin);
            addressBook->contacts[i].email[strcspn(addressBook->contacts[i].email, "\n")] = 0;  // Remove newline

            printf("Contact updated successfully!\n");
            return;
        }
    }
    printf("Contact '%s' not found.\n", editName);
}

void deleteContact(AddressBook *addressBook) {
    char deleteName[50];
    printf("Enter the name of the contact to delete: ");
    fgets(deleteName, sizeof(deleteName), stdin);
    deleteName[strcspn(deleteName, "\n")] = 0; // Remove newline character

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, deleteName) == 0) {
            for (int j = i; j < addressBook->contactCount - 1; j++) {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            addressBook->contactCount--;
            printf("Contact '%s' deleted successfully!\n", deleteName);
            return;
        }
    }
    printf("Contact '%s' not found.\n", deleteName);
}

void saveContacts(AddressBook *addressBook) {
    FILE *file = fopen("contact.txt", "a+"); // Open file in append mode for adding contacts

    if (!file) {
        printf("Failed to open the file for saving contacts.\n");
        return;
    }

    // Loop through the contacts and add them if not already in the file
    for (int i = 0; i < addressBook->contactCount; i++) {
        int isDuplicate = 0;

        // Check if this contact is already in the file
        fseek(file, 0, SEEK_SET); // Move the file pointer to the beginning
        char line[150];
        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, addressBook->contacts[i].name) || 
                strstr(line, addressBook->contacts[i].phone) || 
                strstr(line, addressBook->contacts[i].email)) {
                isDuplicate = 1;
                break;
            }
        }

        // If no duplicate, write to the file
        if (!isDuplicate) {
            fprintf(file, "%s,%s,%s\n",
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
        }
    }

    fclose(file);
    printf("Contacts saved successfully!\n");
}


void initialize(AddressBook *addressBook) {
    FILE *file = fopen("contact.txt", "r");
    if (!file) {
        printf("Could not open contact.txt for reading.\n");
        return;
    }

    char temp[100];
    while (fscanf(file, "%99[^\n]\n", temp) != EOF) {
        Contact newContact;
        char *token = strtok(temp, ",");
        strcpy(newContact.name, token);
        token = strtok(NULL, ",");
        strcpy(newContact.phone, token);
        token = strtok(NULL, ",");
        strcpy(newContact.email, token);

        // Check for duplicate contact before adding to the address book
        int isDuplicate = 0;
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].name, newContact.name) == 0 || 
                strcmp(addressBook->contacts[i].phone, newContact.phone) == 0 || 
                strcmp(addressBook->contacts[i].email, newContact.email) == 0) {
                isDuplicate = 1;
                break;
            }
        }

        // If it's not a duplicate, add to the address book
        if (!isDuplicate) {
            addressBook->contacts[addressBook->contactCount++] = newContact;
        }
    }

    fclose(file);
}


void promptSaveBeforeExit(AddressBook *addressBook) {
    char choice;
    printf("Do you want to save your changes before exiting? (Y/N): ");
    scanf(" %c", &choice);
    if (choice == 'Y' || choice == 'y') {
        saveContacts(addressBook);
    }
    printf("Exiting the program...\n");
}

int main() {
    AddressBook addressBook = {0}; // Initialize address book

    initialize(&addressBook); // Load existing contacts

    int choice;
    while (1) {
        printf("\n1. List Contacts\n");
        printf("2. Add Contact\n");
        printf("3. Search Contact\n");
        printf("4. Edit Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Save Contacts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume the leftover newline character

        switch (choice) {
            case 1:
                listContacts(&addressBook);
                break;
            case 2:
                addContact(&addressBook);
                break;
            case 3:
                searchContact(&addressBook);
                break;
            case 4:
                editContact(&addressBook);
                break;
            case 5:
                deleteContact(&addressBook);
                break;
            case 6:
                saveContacts(&addressBook);
                break;
            case 7:
                promptSaveBeforeExit(&addressBook);
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

