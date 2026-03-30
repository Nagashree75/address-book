/*Name:Nagashree N
Submission date:7/12/2025
Project Name: AdressBook
Description:In addressbook there are 7 function:
1.create contact:if user giving input ,storing it in string and validating it ,if that string is valid then am adding it to structure.
2.search contact:asking how to search,by name or by phone number or by email_id....if name is repeating again asking for search by phone_number or email_id,if it is present printing the details,if not printing contact not found.
3.edit contact:firstly search,if present then asking which part do you want to edit ,name,phone number or email id,after taking input validating it and is it is valid then add to structure.
4.delete contact:first search ,if it is present then delete the whole details in structure.
5.save contact:after completing the task save the structure into file.
6.save and exit:after completing the task save the structure into file and exit the code.
*/
#include <stdio.h>//includes standard input/output functions
#include "contact.h"//includes your custom header file containing & function declaration
/* Structure declaration */

int main()
{
    /* Variable and structre defintion */
    int option;//stores the users menu choice
    AddressBook addressbook;//creates a structure variable for the entire address book.
    addressbook.contact_count = 0;//initialize number of contacts to zero
    FILE*fptr = fopen("data.txt","r");//opens the file for reading saved contacts.
    if(fptr==NULL)//checks if the file exists.
    {
        printf("File not found\n");
    }
    else
    {
        rewind(fptr);//moves file pointer to the begining of the file.
        fscanf(fptr,"#%d\n",&addressbook.contact_count);//reads how many contacts are stored in the file
        for(int i=0;i<addressbook.contact_count;i++)//loops through each saved contacts.
        {
            fscanf(fptr," %[^,],%[^,],%[^\n]",addressbook.contact_details[i].Name,addressbook.contact_details[i].Mobile_number,addressbook.contact_details[i].Mail_ID);//reads name,mobile number,mail id separated by commas.
        }
    }
    fclose(fptr);//close the file.
    

    // init_intitalization(&addressbook);

    while (1)//runs the menu continuously until exit.
    {
        printf("\nAddress book menu\n"); /* Give a prompt message for a user */
        printf("1.Add contact\n2.search contact\n3.Edit contact\n4.Delete contact\n5.Display contact\n6.Save contact\n7.Exit\n");
        printf("Enter the option : ");//display main menu heading.
        scanf("%d", &option);//reads the user choice.

        switch (option) /* Based on choosed option */
        {
        case 1:
        {
            
                create_contact(&addressbook);//calls function to add a new contact.
                
            
            break;
        }

        case 2:
        {
            int choose=1;
            while (choose)

            {
            printf("Search Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4. Exit\nEnter the option : "); /* Providing menu */
            search_contacts(&addressbook);//calls function to search contacts.
            printf("do you want to continue\n1.yes\n0.No\n");
                scanf("%d",&choose);
            }
            
            break;
        }
        case 3:
        {
                int choose = 1;
                while(choose)
                {
                printf("Edit Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\nEnter the option : "); /* Providing menu */

                edit_contact(&addressbook);//calls function to modify a contact.
                printf("do you want to continue\n1.yes\n0.No\n");
                scanf("%d",&choose);
                }
            break;
        }

        case 4:
        {
            int choose = 1;
            while(choose)
            {
            printf("Delete Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\nEnter the option : "); /* Providing menu */

            delete_contact(&addressbook);//calls function to remove a contact.
            printf("do you eant to continue\n1.yes\n0.No\n");
            scanf("%d",&choose);
            }
            break;
        }
        case 5:
        {
            printf("List Contacts:");
            list_contacts(&addressbook);//display all contacts.
            break;
        }

        case 6:
        {
            printf("Saving contacts\n");
            save_contacts(&addressbook);//writes all contacts back to the file.
            break;
        }
        case 7:
            printf("INFO : Save and Exit...\n");
            return 0;//ends the programme.

        default:
            printf("Invalid option \n");
            break;
        }
    }
    return 0;
}
