#include <stdio.h>
#include<string.h>
#include <stdlib.h>

struct type
{
    int id;
    char name[100];
    char phone[15];
    char email[100];

    struct type *next;
};

typedef struct type contact;


contact *head;

void display_menu();
void choose_options();
void add_new_contact();
void delete_contact();
void list_all_contact();
void modify_contact();
void find_contact_by_name();
void save_and_quit();
void read_from_database();

int main()
{
    read_from_database();

    printf("         Welcome To Contact Database");

    display_menu();

    return 0;
}

void display_menu()
{
    printf("\n\n");
    printf("--------------------------\n");
    printf("1 - Add a new contact     \n");
    printf("2 - Delete contact        \n");
    printf("3 - List all contact      \n");
    printf("4 - Modify contact        \n");
    printf("5 - Find a contact by name\n");
    printf("Q - Save and quit         \n");
    printf("--------------------------\n");
    printf("\n");

    choose_options();
}


void choose_options()
{
    char option;
    fflush(stdin);
    fflush(stdout);

    scanf("%c",&option);

    switch(option)
    {
    case '1':
    {
        add_new_contact();
    }
    break;
    case '2':
    {
        delete_contact();
    }
    break;
    case '3':
    {
        list_all_contact();
    }
    break;
    case '4':
    {
        modify_contact();
    }
    break;
    case '5':
    {
        find_contact_by_name();
    }
    break;
    case 'Q':
    {
        save_and_quit();
    }
    break;
    default:
    {
        choose_options();
    }
    break;
    }
}


void add_new_contact()
{
    contact *temp, *counter;

    counter=head;

    temp=malloc(sizeof(contact));
    temp->next=NULL;

    fflush(stdin);
    fflush(stdout);

    printf("\n");
    printf("Enter Name        : ");
    scanf("%s",temp->name);
    printf("Enter Phone Number: ");
    scanf("%s",temp->phone);
    printf("Enter E-Mail ID   : ");
    scanf("%s",temp->email);

    if(counter==NULL)
    {
        temp->id=1;
        head=temp;
        printf("\nNew contact added with id 1 !");
    }
    else
    {
        while(counter->next!=NULL)
        {
            counter=counter->next;
        }
        temp->id=counter->id+1;
        counter->next=temp;
        printf("\nNew contact added with id %d !",temp->id);
    }

    display_menu();
}



void delete_contact()
{
    int id, flag = 0;
    contact *temp, *counter;

    counter=head;

    printf("\n\nEnter a contact ID to delete: ");
    scanf("%d",&id);

    if(counter==NULL)
    {
        printf("\nLIst is empty !");
    }
    else if(counter->id==id)
    {
        head=counter->next;
        free(counter);

        flag = 1;

        temp=head;

        while(temp!=NULL)
        {
            temp->id=flag++;
            temp=temp->next;
        }

        printf("\nSuccessfully deleted the contact !");
    }
    else
    {
        temp=counter;
        counter=counter->next;

        while(counter!=NULL)
        {
            if(counter->id==id)
            {
                temp->next=counter->next;
                flag=counter->id;
                break;
            }
            else
            {
                temp = counter;
                counter=counter->next;
            }
        }

        if(flag==0)
        {
            printf("\nNo data found for this ID !");
        }
        else
        {
            temp=temp->next;

            while(temp!=NULL)
            {
                temp->id=flag++;
                temp=temp->next;
            }

            printf("\nSuccessfully deleted the contact !");
        }
    }

    display_menu();
}



void list_all_contact()
{
    contact *counter;

    counter = head;

    fflush(stdin);
    fflush(stdout);

    if(counter==NULL)
    {
        printf("\n\nList is empty !");
    }
    else
    {
        printf("\n\n");
        while(counter!=NULL)
        {
            printf("\n");
            printf("ID          : %d\n",counter->id);
            printf("Name        : %s\n",counter->name);
            printf("Phone Number: %s\n",counter->phone);
            printf("E-Mail ID   : %s\n",counter->email);

            counter=counter->next;
        }
    }

    display_menu();
}



void modify_contact()
{
    int id, flag=0, dump=0;
    contact *counter;

    counter = head;

    printf("\nEnter a contact ID to modify: ");
    scanf("%d",&id);

    while(counter!=NULL)
    {
        if(counter->id==id)
        {
            printf("Modify name? [Enter 1=yes, anykey=skip]: ");
            scanf("%d",&dump);
            if(dump==1)
            {
                printf("Enter new name for id %d: ",id);
                scanf("%s",counter->name);
            }

            printf("Modify phone number? [Enter 1=yes, anykey=skip]: ");
            scanf("%d",&dump);
            if(dump==1)
            {
                printf("Enter new phone number for id %d: ",id);
                scanf("%s",counter->phone);
            }

            printf("Modify E-Mail ID? [Enter 1=yes, anykey=skip]: ");
            scanf("%d",&dump);
            if(dump==1)
            {
                printf("Enter new E-Mail for id %d: ",id);
                scanf("%s",counter->email);
            }

            printf("\nSuccessfully modified your contact !");

            flag++;

            break;
        }
        else
        {
            counter=counter->next;
        }
    }

    if(flag==0)
    {
        printf("\nNo data found for this ID !");
    }

    display_menu();
}



void find_contact_by_name()
{
    char name[100];
    int flag=0;
    contact *counter;

    counter = head;

    printf("\nEnter a name: ");
    scanf("%s",name);

    while(counter!=NULL)
    {
        if(strcmp(counter->name,name)==0)
        {
            printf("\nData Found !\n");
            printf("\n");
            printf("ID          : %d\n",counter->id);
            printf("Name        : %s\n",counter->name);
            printf("Phone Number: %s\n",counter->phone);
            printf("E-Mail ID   : %s\n",counter->email);

            flag++;

            break;
        }
        else
        {
            counter=counter->next;
        }
    }

    if(flag==0)
    {
        printf("\nNo data found for this ID !");
    }

    display_menu();
}



void save_and_quit()
{
    FILE *file;
    contact *counter;

    counter=head;

    file=fopen("contacts.txt","w");


    while(counter!=NULL)
    {
        fputs(counter->name, file);
        fputs("\n", file);
        fputs(counter->phone, file);
        fputs("\n", file);
        fputs(counter->email, file);
        fputs("\n", file);

        counter=counter->next;
    }

    fclose(file);

    printf("\nData Storage Completed!\n\n");
}



void read_from_database()
{
    FILE *file;
    contact *temp, *counter;
    int id_counter = 1;

    temp=malloc(sizeof(contact));
    temp->next=NULL;

    if(file=fopen("contacts.txt","r"))
    {
        while(fscanf(file, "%s", temp->name)==1 && fscanf(file, "%s", temp->phone)==1 && fscanf(file, "%s", temp->email)==1)
        {
            temp->id=id_counter++;

            if(head==NULL)
            {
                head=temp;
                counter=head;
            }
            else
            {
                counter->next=temp;
                counter=counter->next;
            }

            temp=malloc(sizeof(contact));
            temp->next=NULL;
        }

        fclose(file);
    }
}
