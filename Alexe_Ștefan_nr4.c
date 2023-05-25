#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nod{
    struct nod *next;    /* *ptr = &(*ptr)->next  */
    struct nod *prev;
    int pret;
    int nr;
    char tip[10];
    char marca[15];
};

static inline int cerinta_1(struct nod *p)
{
    int suma = 0;
    while(p) {
        suma += p->pret;
        p = *(struct nod **)(p);
    }
    return suma;
}

static inline void swap(struct nod *ptr1, struct nod *ptr2)
{
    struct nod tmp;
    tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
    tmp.next = (*ptr1).next;
    (*ptr1).next = (*ptr2).next;
    (*ptr2).next = tmp.next;\
    tmp.prev = (*ptr1).prev;
    (*ptr1).prev = (*ptr2).prev;
    (*ptr2).prev = tmp.prev;
}

static void sort(struct nod **ptr)
{
    for(struct nod **i = ptr; *i && **(struct nod ***)(i); i = (struct nod **)(*i)){
        for(struct nod **j = (struct nod **)(*i); j && *j; j = (struct nod **)(*j)) {
            if((*i)->pret < (*j)->pret) {
                swap(*i, *j);
            }
        }
    }
}

static inline char true()
{
    return 1;
}

static inline char mai_putin_de_10(struct nod *p)
{
    return p->nr < 10;
}

static inline char pret_mai_mare_de_1000(struct nod *p)
{
    return p->pret > 1000;
}

static inline void afisare(struct nod *p, char (*f)())
{
    while(p) {
        if((*f)(p)) {
            printf("%s\n%s\n%d\n%d\n\n", p->tip, p->marca, p->pret, p->nr);
        }
        p = *(struct nod **)(p);
    }
    printf("\n");
}

static int acelasi_tip(struct nod *p)
{
    char tip[10];
    printf("\nspuneti tipul:\n\n");
    scanf("%s", tip);
    int valoare = 0;
    while(p) {
        if(!strcmp(tip, p->tip)) {
            valoare += p->pret;
        }
        p = *(struct nod **)(p);
    }
    return valoare;
}

static void eliminare(struct nod **ptr, int val)
{
    while(ptr && *ptr){
        if((*ptr)->nr == val) {
            struct nod *p = *ptr;
            if(!(*ptr)->prev) {
                *ptr = **(struct nod ***)(ptr);
                if(*ptr) {
                    (*ptr)->prev = NULL;
                }
            }
            else {
                struct nod *p1 = (*ptr)->prev;
                struct nod *p2 = **(struct nod ***)(ptr);
                if(p1) {
                    p1->next = p2;
                }
                if(p2) {
                    p2->prev = p1;
                }
            }
            free(p);
        }
        else {
            ptr = (struct nod **)(*ptr);
        }
    }
}

int main()
{
    struct nod *head = NULL;
    struct nod **ptr = &head;
    struct nod *previous = NULL;
    struct nod *clear = NULL;
    int n;
    char cerinta;

    while(1) {
        printf("\ncerinta:\n\n");
        scanf("%hhu", &cerinta);
        printf("\n");
        switch (cerinta) {
        case 0:
            __asm__(
            "movq $60, %rax\n"
            "movq $0,  %rdi\n"
            "syscall"
            );
        case 1:
            clear = head;
            while(head) {
                head = *(struct nod **)(head);
                free(clear);
                clear = head;
            }
            ptr = &head;
            previous = NULL;
            printf("\nCate elemente:\n\n");
            scanf("%d", &n);
            while(n--) {
                *ptr = (struct nod *)malloc(sizeof(struct nod));
                if(*ptr == NULL) {
                    break;
                }
                **(struct nod ***)(ptr) = NULL;
                (*ptr)->prev = NULL;
                (*ptr)->prev = previous;
                scanf("%s", (*ptr)->tip);
                scanf("%s", (*ptr)->marca);
                scanf("%d", &(*ptr)->pret);
                scanf("%d", &(*ptr)->nr);
                previous = *ptr;
                ptr = (struct nod **)(*ptr);
            }
            break;
        case 2:
            afisare(head, &true);
            break;
        case 3:
            /* cerinta 1 */
            printf("\n%d\n\n\n", cerinta_1(head));
            break;
        case 4:
            /* cerinta 2 */
            sort(&head);
            afisare(head, &true);
            break;
        case 5:
            /* cerinta 3 */
            afisare(head, &mai_putin_de_10);
            break;
        case 6:
            /* cerinta 4 */
            afisare(head, &pret_mai_mare_de_1000);
            break;
        case 7:
            /* cerinta 5 */
            printf("%d\n\n\n", acelasi_tip(head));
            break;
        case 8:
            /* cerinta 6 */
            eliminare(&head, 0);
            afisare(head, &true);
            break;
        }
    }
    return 1;
}
