#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{

    char *kelime;
    struct Node *next;
    int adet;

};

void printList(struct Node *node)
{
    int i=1;
    while (node != NULL)
    {
        printf("%d. %s: %d\n",i, node->kelime,node->adet);
        node = node->next;
        i++;
    }
}

int is_in_list(struct Node **basla, char *kelime)
{
    struct Node *iter = (*basla);
    while(iter != NULL)
    {
        if(strcmp(iter->kelime,kelime) == 0)
        {
            return 1;
        }
        iter = iter->next;
    }
    return 0;

}

void swap(struct Node *a, struct Node *b)
{
    int temp = a->adet;
    char *temp1 = a->kelime;
    a->adet = b->adet;
    a->kelime = b->kelime;
    b->adet = temp;
    b->kelime = temp1;
}

void bubbleSort(struct Node *basla)
{
    int swapped;
    struct Node *ptr1;
    struct Node *lptr = NULL;

    /* Checking for empty list */
    if (basla == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = basla;

        while (ptr1->next != lptr)
        {
            if (ptr1->adet < ptr1->next->adet)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void ekle(struct Node** basla, char *kelime)
{
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node *son = (*basla);
    new_node->kelime = kelime;
    new_node->next = NULL;

    if(*basla == NULL)
    {
        (*basla) = new_node;
        return;
    }
    while(son->next != NULL)
    {
        son = son->next;
    }
    son->next = new_node;
    return;
}

void sona_ekle(struct Node** basla, char *kelime, int adet)
{
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node *son = (*basla);
    new_node->kelime = kelime;
    new_node->adet = adet;
    new_node->next = NULL;

    if(*basla == NULL)
    {
        *basla = new_node;
        return;
    }
    while(son->next != NULL)
    {
        son = son->next;
    }
    son->next = new_node;
    return;
}

void basa_ekle(struct Node** basla, char *kelime, int adet)
{
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->kelime = kelime;
    new_node->adet = adet;
    new_node->next = (*basla);
    (*basla) = new_node;
}

void araya_ekle(struct Node** basla, char *kelime, int adet)
{
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node *son = (*basla);
    new_node->kelime = kelime;
    new_node->adet = adet;
    new_node->next = NULL;

    while(son->next != NULL)
    {
        son = son->next;
    }
    son->next = new_node;

    bubbleSort((*basla));

    return;
}

int main()
{
    FILE *text = fopen("D:\\Prolab\\Proje3\\Proje3\\Deneme.txt","r");
    if(text==NULL)
    {
        printf("Dosyaya erisilemedi!");//Txt dosyaniz yok ise açmayacaktir.
        exit(1);
    }

    fseek(text,0,SEEK_END);
    long int txt_size = ftell(text);
    fseek(text,0,SEEK_SET);
    char *paragraf = (char *)malloc(sizeof(char) * txt_size);
    fgets(paragraf,txt_size+1,text);
    fclose(text);
    char *kelime;

    kelime = strtok(paragraf," ");

    struct Node *root1 = NULL;
    struct Node *root2 = NULL;
    while(kelime != NULL)
    {
        //puts(kelime);
        ekle(&root1,kelime);
        kelime = strtok(NULL," ");
    }
    struct Node *iter1 = root1;
    struct Node *iter3;
    //printList(root1);
    //printf("%d %s",is_in_list(&root1,root1->next->next->next->kelime),iter1->next->next->next->kelime);

    Loop:
    while(iter1 != NULL)
    {
        int sayac = 0;
        struct Node *iter2 = root1;
        if(is_in_list(&root2,iter1->kelime))
        {
            iter1 = iter1->next;
            continue;
        }
        while(iter2 != NULL)
        {
            if(strcmp(iter1->kelime,iter2->kelime)==0)
            {
                sayac++;
            }
            iter2 = iter2->next;
        }
        if(root2 == NULL)
        {
            basa_ekle(&root2,iter1->kelime,sayac);
            iter3 = root2;
        }
        else
        {
            while(iter3 != NULL)
            {
                if(sayac > iter3->adet)
                {
                    basa_ekle(&root2,iter1->kelime,sayac);
                    iter3 = root2;
                    iter1 = iter1->next;
                    goto Loop;
                }
                /*if(sayac <=iter3->adet && sayac > iter3->next->adet && iter3->next != NULL)
                {
                    araya_ekle(&root2,iter1->kelime,sayac);
                    iter3 = root2;
                    iter1 = iter1->next;
                    goto Loop;
                }*/
                else if(sayac <= iter3->adet && iter3->next==NULL)
                {
                    sona_ekle(&root2,iter1->kelime,sayac);
                    iter3 = root2;
                    iter1 = iter1->next;
                    goto Loop;
                }
                else
                {
                    araya_ekle(&root2,iter1->kelime,sayac);
                    iter3 = root2;
                    iter1 = iter1->next;
                    goto Loop;
                }
                 iter3 = iter3->next;
            }
        }

        iter1 = iter1->next;
    }

     /*basa_ekle(&root2,"kaan",3);
     sona_ekle(&root2,"alperen",1);
     araya_ekle(&root2,"ahmet",2);
     basa_ekle(&root2,"asda",5);
     sona_ekle(&root2,"adas",1);
     araya_ekle(&root2,"dasda",4);
     */
     //printf("%s %d\n",root1->kelime,root1->adet);
     //printf("%s %d\n",root2->kelime,root2->adet);
    printList(root2);
    return 0;
}
