#include<stdio.h>//includes standard input/output functions.
#include<string.h>//allows use of string functions like strcmp,strcasecmp.
#include"contact.h"//includes your custom structure and function declaration. 
#include<ctype.h>//includes file contains function used to check and convert characters if a character is a digit,letter,uppercase,lowercase,etc.

/*Function definitions*/
//void init_intitalization(AddressBook*addressbook)
//{
//}
int valid_name(char*);//checks if name contains only alphabets and spaces.
int valid_name(char*name)
{
    //1 rule only alphabets
    for(int i=0;name[i]!='\0';i++)
    {
        if(!((name[i]>='a'&&name[i]<='z')||(name[i]>='A'&&name[i]<='Z')||name[i]==' '))
        {
            printf("Name should contains only alphabet characters! Try again.\n\n");
            return 0;
        }
    }
    return 1;
}

int valid_phone_number(char*,AddressBook*);//validates phone number for starting digit,digits only,length 10,and uniqueness.
int valid_phone_number(char*phone_number,AddressBook*addressbook)
{
    //1 rule first letter should be >=6 & <=9
    int len = strlen(phone_number);
    if(!(phone_number[0]>='6'&&phone_number[0]<='9'))
    {
        printf("phone number should be starts with >=6 and <=9.\n\n");
        return 0;
    }
    //2 rule only numbers
    for(int i=0;i<len;i++)
    {
        if(!(phone_number[i]>='0'&&phone_number[i]<='9'))
        {
            printf("Phone number should contains only numbers! Try again\n\n");
            return 0;
        }
    }
    //3 rule 10 digits
    if(len!=10)
    {
        printf("Phone number should contains 10 digits.\n\n");
        return 0;
    }
    //4 rule unique
    for(int i=0;i<addressbook->contact_count;i++)
    {
        if(strcmp(phone_number,addressbook->contact_details[i].Mobile_number)==0)
        {
            printf("Phone number should be unique! Try again\n\n");
            return 0;
        }
    }
    return 1;
}

int valid_email_id(char*,AddressBook*);//validates email for uniqueness,lowercase,one'@',correct domain,no spaces,correct'.;rules.
int valid_email_id(char*email_id,AddressBook*addressbook)
{
    //rule 1 unique email id
    for(int i=0;i<addressbook->contact_count;i++)
    {
        if(strcmp(email_id,addressbook->contact_details[i].Mail_ID)==0)
        {
            printf("Email_ID should be unique!Try again.\n\n");
            return 0;
        }
    }
    //rule 2, only 1 @
    int len = strlen(email_id);
    int count = 0;
    for(int i=0;i<len;i++)
    {
        if(email_id[i]=='@')
        {
            count++;
        }
    }
    if(count!=1)
    {
        printf("Mail_id should contain only one @ symbol! Try again.\n\n");
        return 0;
    }
    //rule 3 only lower case
    for(int i=0;i<len;i++)
    {
        if((email_id[i]>='A'&&email_id[i]<='Z'))

        {
            printf("In mail_id only lower case is consider.\n\n");
            return 0;
        }
    }
    //rule 4 @.com should be there
    char substr[6]=".com";
    char* substring=strstr(email_id,substr);
    if(substring==NULL)
    {
        printf("Mail_id should contains @ and .com\n\n");
        return 0;
    }
    //rule 5 before @ minimum 4 characters should be there
    for(int i=0;i<4;i++)
    {
        if(email_id[i]=='@')
        {
            printf("mail_id atleast contains 4 characters before the @ symbol! Try again\n\n");
            return 0;
        }
    }
    //rule 6 domain name should be after @ symbol
    int k;
    char ch = '@';
    char* str = strstr(email_id,substr);
    char* ptr = strchr(email_id,ch);
    if(str-ptr<2)//str=.com&&ptr=@then.com-@distance
    {
        printf("Domain name should be after the @ symbol! Try again");
        return 0;
    }
    //rule 7 no space
    for(int i=0;i<len;i++)
    {
        if(email_id[i]==' ')
        {
            printf("In email_id there is no spaces! Try again\n\n");
            return 0;
        }
    }
    //rule 8 A.after @
    int i;
    for(i=0;ptr[i]!='\0';i++)
    {
        if(ptr[i]=='.')
        {
            break;
        }
    }
    if(ptr[i]=='\0')
    {
        printf("In email_id address book should be after the @\n\n");
        return 0;
    }
    //rule 9 last. not there
    if(email_id[len-1]=='.')
    {
        printf("In email_id last . should not there!\n\n");
        return 0;
    }
    int j;
    for(j=0;email_id[j]!='\0';j++)
    {
        if(email_id[j]=='@')
        break;
    }
    if(email_id[j-1]=='.' || email_id[j+1]=='.')
    {
        return 0;
    }

    int l;
    int dotcount=0;
    for(l=j+1;email_id[l]!='\0';l++)
    {
        if(email_id[l]=='.')
        {
            dotcount++;
        }
    }
    if(dotcount!=1)
    {
        printf("Invalid email id ! please try again\n");
            return 0;
    }
    return 1;
}

int create_contact(AddressBook* addressbook)//takes user input,validates name/phone/email,and stores the new contact in structure.
{
    int k=1;
    while(k)
    {
        char name[30];
        printf("Enter the Name:");
        n_m:
        scanf(" %[^\n]",name);
        int valid_n = valid_name(name);
        //int valid_n=1
        if(valid_n!=0)
        {
            strcpy(addressbook->contact_details[addressbook->contact_count].Name,name);
        }
        else
        {
            printf("Enter name again:");
            goto n_m;
        }

        char phone_number[11];
        printf("Enter phone number:");
        p_n:
        scanf(" %[^\n]",phone_number);
        int valid_p = valid_phone_number(phone_number,addressbook);

        //int valid_p=1
        if(valid_p!=0)
        {
            strcpy(addressbook->contact_details[addressbook->contact_count].Mobile_number,phone_number);
        }
        else
        {
            printf("Enter phone number again:");
            goto p_n;
        }

        char email_id[20];
        printf("Enter email_id:");
        e_i:
        scanf(" %[^\n]",email_id);
        int valid_e = valid_email_id(email_id,addressbook);
        //int valid_e = 1;
        if(valid_e!=0)
        {
           strcpy(addressbook->contact_details[addressbook->contact_count].Mail_ID,email_id);
        }
        else
        {
            printf("Enter Email id again:");
            goto e_i;
        }
        //i++;

        addressbook->contact_count++;

        printf("Do you want to create contact?\n1.Yes\n0.No\n");
        scanf("%d",&k);
    }
    return 0;
}

void list_contacts(AddressBook*addressbook)//displays all savedcontacts in formatted table format.
{
    printf("%-15s %-10s %-10s\n","Name","Phone_number","Email_id");
    for(int i=0;i<addressbook->contact_count;i++)
    {
        printf("%-15s %-10s %-10s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
    }
}

int search_contacts(AddressBook*addressbook)//searches a contact by name/phone number/email and returns index.
{
    printf("Search Menu\n1.search by name\n2.search by mobile number\n3.search by email_id\n4.exit\n");
    int option,option1;
    scanf("%d",&option);
    char name[20];
    char Mobile_number [11];
    char email_id[20];
    int count;
    int arr[count];
    int i,j;
    switch(option)
    {
        case 1:
        count = 0;
        printf("Enter the name:");
        scanf(" %[^\n]",name);
        for(i=0;i<addressbook->contact_count;i++)
        {
            if(strcmp(addressbook->contact_details[i].Name,name)==0)
            {
                printf("%s-%s-%s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
                arr[count]=i;
                count++;
            }
        }
        if(count>1)
        {
            printf("There are %d contacts with the same name\nSearch the contact details by phone_number and email_id\n1.phone number\n2.email_id\n",count);
            scanf("%d",&option1);
            if(option1==1)
            {
                printf("Enter the mobile number:");
                scanf(" %[^\n]",Mobile_number);
                for(j=0;j<count;j++)
                {
                    if(strcmp(addressbook->contact_details[arr[j]].Mobile_number,Mobile_number)==0)

                    {
                        printf("%s-%s-%s\n",addressbook->contact_details[arr[j]].Name,addressbook->contact_details[arr[j]].Mobile_number,addressbook->contact_details[arr[j]].Mail_ID);
                        return arr[j];
                    }
                }
            }
            if(option1==2)
            {
                printf("Enter the Email_Id:");
                scanf(" %[^\n]",email_id);
                for(j=0;j<count;j++)
                {
                   if(strcmp(addressbook->contact_details[arr[j]].Mail_ID,email_id)==0)
                   {
                        printf("%s-%s-%s\n",addressbook->contact_details[arr[j]].Name,addressbook->contact_details[arr[j]].Mobile_number,addressbook->contact_details[arr[j]].Mail_ID);
                        return arr[j];
                   }
                }
            }
        }
        else if(count==1)
        {
            return arr[0];
        }
        break;

        case 2:
        printf("Enter the Mobile number:");
        scanf(" %[^\n]",Mobile_number);
        for(i=0;i<addressbook->contact_count;i++)
        {
            if(strcmp(addressbook->contact_details[i].Mobile_number,Mobile_number)==0)
            {
                 printf("%s-%s-%s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
                 return i;
                 break;  
            }
        }
        break;

        case 3:
        printf("Enter the email id:");
        scanf(" %[^\n]",email_id);
        for(i=0;i<addressbook->contact_count;i++)
        {
            if(strcmp(addressbook->contact_details[i].Mail_ID,email_id)==0)
            {
                printf("-%15s\n-%10s\n-%15s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
                return i;
                break;
            }
        }
        break;

        case 4:
        printf("Thank You\n");
        break;
    }
    printf("Contact is not found\n");
}


int edit_contact(AddressBook*addressbook)//searches a contact asks user what to update, validates input,and update structure.
{
    int search_contacts(AddressBook*);
    int i=search_contacts(addressbook);
    int option;
    if(i>=0 && i<=addressbook->contact_count)
    {
        printf("Edit Contact menu:\n1.Nmae\n2.Mobile number\n3.Mail id\n4.exit\nEnter the option");
        scanf("%d",&option);
        switch(option)
        {
            case 1://edit by name
            char e_name[20];
            e_n:
            printf("Enter the editted name:");
            scanf(" %[^\n]",e_name);
            int valid_e_n = valid_name(e_name);
            if(valid_e_n!=0)
            {
                strcpy(addressbook->contact_details[i].Name,e_name);
                printf("Edit completed.\n\n");
            }
            else
            {
                goto e_n;
            }
            break;

            case 2://edit by mobile number
            char e_phone[11];
            e_p:
            printf("Enter the editted mobile number:");
            scanf(" %[^\n]",e_phone);
            int valid_e_p = valid_phone_number(e_phone,addressbook);
            if(valid_e_p!=0)
            {
                strcpy(addressbook->contact_details[i].Mobile_number,e_phone);
                printf("Edit completed.\n\n");
            }
            else
            {
                goto e_p;
            }
            break;

            case 3://edit by email id
            char e_email_id[30];
            e_e_id:
            printf("Enter the editted email id:");
            scanf(" %[^\n]",e_email_id);
            int valid_e_e = valid_email_id(e_email_id,addressbook);
            if(valid_e_e!=0)
            {
                strcpy(addressbook->contact_details[i].Mail_ID,e_email_id);
                printf("Edit completed.\n\n");
            }
            else
            {
                goto e_e_id;
            }
            break;

            case 4:
            printf("THANK YOU\n");
            return 0;

        }
    }
}

int delete_contact(AddressBook*addressbook)//searches a contact and delets it by shiting remaining contacts.
{
    int search_contacts(AddressBook*);
    int i=search_contacts(addressbook);
    int option;
    if(i>=0 && i<=addressbook->contact_count)
    {
        printf("Do You Really want to Delete the details?\n1.Yes\n2.N0\n");
        scanf("%d",&option);
        if(option==1)
        {
            addressbook->contact_count--;
            for(int j=i;j<addressbook->contact_count;j++)
            {
                addressbook->contact_details[j]=addressbook->contact_details[j+1];
            }
            printf("Delete Completed\n");
        }
        return 0;
    }
}

int save_contacts(AddressBook*addressbook)//sorts contacts aplhabetically and writesthem into data.txt.
{
    FILE* fptr=fopen("data.txt","w");//read existing contacts from file using 
    if(fptr==NULL)//checks if file failed to open.
    {
        printf("File not found\n");//prints error message if file not opened
        return 0;//stops function when file not available.
    }
    rewind(fptr);//moves file pointer to beginning of file.
    fprintf(fptr,"#%d\n",addressbook->contact_count);//writes total contact count as header
    for(int i=0;i<addressbook->contact_count;i++)//iterates through all saved contacts.
    {
        fprintf(fptr,"%s,%s,%s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);//writes name,phone,email.
    }
    fclose(fptr);//closes the file after writing.
    return 0;//returns success status.
}