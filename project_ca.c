#include <stdio.h>
#include <string.h>

typedef struct {
    char name[50];
    char address[50];
    int phone[10];
    char email[50];
} Contact;

void add_contact();
void view_all_contacts();
void edit_contact();
void search_contact();
void delete_contact();

int main() {
    int choice;

    while (1) {
        printf("\nPhonebook Management System\n");
        printf("===========================\n");
        printf("1. Add a contact\n");
        printf("2. View all contacts\n");
        printf("3. Edit a contact\n");
        printf("4. Search for a contact\n");
        printf("5. Delete a contact\n");
        printf("6. Exit\n");

        printf("\nEnter your choice (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_contact();
                break;
            case 2:
                view_all_contacts();
                break;
            case 3:
                edit_contact();
                break;
            case 4:
                search_contact();
                break;
                
            case 5:
                delete_contact();
                break;
            case 6:
                printf("\nExiting the program. Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}
void add_contact() {
    Contact contact;
    FILE *fp;

    printf("\nEnter the following details:\n");
    fflush(stdin);
    printf("Name: ");
    scanf("%[^\n]s", contact.name);
    printf("Address: ");
    scanf("%s", contact.address);
    printf("Phone: ");
    scanf("%d", &contact.phone);
    printf("Email: ");
    scanf("%s", contact.email);

    fp = fopen("phonebook.dat", "ab");
    if (fp == NULL) {
        printf("\nError opening file!\n");
        return;
    }
    fwrite(&contact, sizeof(Contact), 1, fp); 
    fclose(fp);

    printf("\nContact added successfully!\n");
}

void view_all_contacts() {
    Contact contact;
    FILE *fp;
    fp = fopen("phonebook.dat", "rb");
    if (fp == NULL) {
        printf("\nNo contacts found!\n");
        return;
    }

    printf("\nAll contacts:\n");
    printf("--------------\n");
    while (fread(&contact, sizeof(Contact), 1, fp)) {
    	    fflush(stdin);
        printf("Name: %s\n", contact.name);
        printf("Address: %s\n", contact.address);
        printf("Phone: %d\n", contact.phone);
        printf("Email: %s\n", contact.email);
        printf("--------------\n");
    }

    fclose(fp);
}

void edit_contact() {
    char name[50];
    Contact contact;
    FILE *fp;
    int found = 0;

    printf("\nEnter the name of the contact to edit: ");
    fflush(stdin);
    scanf("%[^\n]s", name);

    fp = fopen("phonebook.dat", "rb+");
    if (fp == NULL) {
        printf("\nNo contacts found!\n");
        return;
    }

    while (fread(&contact, sizeof(Contact), 1, fp)) {
        if (strcmp(name, contact.name) == 0) { 
            printf("\nEnter new details:\n");
            printf("Name: ");
            fflush(stdin);
            scanf("%[^\n]s", contact.name);
            printf("Address: ");
            scanf("%s", contact.address);
            printf("Phone: ");
            scanf("%d", &contact.phone);
            printf("Email: ");
            scanf("%s",contact.email);
        fseek(fp, -(long)sizeof(Contact), SEEK_CUR);  
        fwrite(&contact, sizeof(Contact), 1, fp);
        found = 1;
        break;
    }
}

if (!found) {
    printf("\nContact not found!\n");
} else {
    printf("\nContact updated successfully!\n");
}

fclose(fp);
}

void search_contact() {
char name[50];
Contact contact;
FILE *fp;
int found = 0;
printf("\nEnter the name of the contact to search: ");
fflush(stdin);

scanf("%[^\n]s", name);

fp = fopen("phonebook.dat", "rb");
if (fp == NULL) {
    printf("\nNo contacts found!\n");
    return;
}

while (fread(&contact, sizeof(Contact), 1, fp)) {
    if (strcmp(name, contact.name) == 0) {
        printf("\nContact details:\n");
        printf("Name: %s\n", contact.name);
        printf("Address: %s\n", contact.address);
        printf("Phone: %d\n", contact.phone);
        printf("Email: %s\n", contact.email);
        found = 1;
        break;
    }
}

if (!found) {
    printf("\nContact not found!\n");
}

fclose(fp);
}

void delete_contact() {
char name[50];
Contact contact;
FILE *fp, *temp;
int found = 0;
fflush(stdin);
printf("\nEnter the name of the contact to delete: ");    
scanf("%[^\n]s", name);

fp = fopen("phonebook.dat", "rb");
if (fp == NULL) {
    printf("\nNo contacts found!\n");
    return;
}

temp = fopen("temp.txt", "wb");
while (fread(&contact, sizeof(Contact), 1, fp)) {
    if (strcmp(name, contact.name) != 0) {
        fwrite(&contact, sizeof(Contact), 1, temp);
    } else {
        found = 1;
    }
}

fclose(fp);
fclose(temp);

remove("phonebook.dat");
rename("temp.dat", "phonebook.dat");

if (found) {
    printf("\nContact deleted successfully!\n");
} else {
    printf("\nContact not found!\n");
}
}
