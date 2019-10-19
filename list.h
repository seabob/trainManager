#ifndef __LIST_H__
#define __LIST_H__

/**********************************************/
/****************KERNEL LIST******************/
/**********************************************/

typedef struct list{
    struct list *prev;
    struct list *next;
}list_t;

static inline void init_list(list_t *list)
{
    list->next = list;
    list->prev = list;
}

static inline void __list_add(list_t *entry, list_t *prev, list_t *next)
{
    next->prev = entry;
    entry->next = next;
    entry->prev = prev;
    prev->next = entry;
}

static inline void list_add(list_t *entry, list_t *head)
{
    __list_add(entry, head, head->next);
}

static inline void list_add_tail(list_t *entry, list_t *head)
{
	head->prev->next = entry;
	entry->prev = head->prev;
	head->prev = entry;
	entry->next = head;
}

static inline void __list_del(list_t *prev, list_t *next)
{
    next->prev = prev;
    prev->next = next;
}

static inline void list_del(list_t *entry)
{
//    __list_del(entry->prev, entry->next);
	entry->next->prev = entry->prev;
	entry->prev->next = entry->next;
	entry->next = entry;
	entry->prev = entry;
//    init_list(entry);
}

static inline int list_empty(list_t *head)
{
    return head->next == head;
}

/**
 * Returns a pointer to the container of this list element.
 *
 * Example:
 * struct foo* f;
 * f = CONTAINER_OF(&foo->entry, struct foo, entry);
 * assert(f == foo);
 *
 * @param ptr Pointer to the struct list_head.
 * @param type Data type of the list element.
 * @param member Member name of the struct list_head field in the list element.
 * @return A pointer to the data struct containing the list head.
 */
#define CONTAINER_OF(ptr, type, member) \
            (type *)((char*)(ptr) - (char *) &((type *)0)->member)

/**
 * Alias of CONTAINER_OF
 */

#define LIST_ENTRY(ptr, type, member) \
            CONTAINER_OF(ptr, type, member)

#define __CONTAINER_OF(ptr, sample, member) \
            CONTAINER_OF((ptr), typeof(*(sample)), member)

/**
 * Loop through the list given by head and set pos to struct in the list.
 *
 * Example:
 * struct foo *iterator;
 * LIST_FOR_EACH_ENTRY(iterator, &bar->list_of_foos, entry) {
 *      [modify iterator]
 * }
 *
 * This macro is not safe for node deletion. Use LIST_FOR_EACH_ENTRY_SAFE
 * instead.
 *
 * @param pos Iterator variable of the type of the list elements.
 * @param head List head
 * @param member Member name of the struct list in the list elements.
 *
 */
#define LIST_FOR_EACH_ENTRY(pos, head, member) \
            for((pos = __CONTAINER_OF((head)->next, pos, member)); \
                &pos->member != head; \
                pos = __CONTAINER_OF(pos->member.next, pos, member))

/**
 * Loop through the list, keeping a backup pointer to the element. This
 * macro allows for the deletion of a list element while looping through the
 * list.
 *
 * See LIST_FOR_EACH_ENTRY for more details.
 */
#define LIST_FOR_EACH_ENTRY_SAFE(pos, tmp, head, member)   \
            for(pos = __CONTAINER_OF((head)->next, pos, member), \
                tmp = __CONTAINER_OF(pos->member.next, pos, member); \
                &pos->member != head; \
                pos = tmp, tmp = __CONTAINER_OF(pos->member.next, pos, member))

#define LIST_FOR_EACH_ENTRY_SAFE_ONE(pos, tmp, head, member)   \
            for(pos = __CONTAINER_OF((head)->next, pos, member), \
                tmp = __CONTAINER_OF(pos->member.next, pos, member); \
                &tmp->member != head; \
                pos = tmp, tmp = __CONTAINER_OF(pos->member.next, pos, member))

#define LIST_FOR_EACH_ENTRY_SAFE_ONE_A(pos, tmp, begin, head, member)   \
            for(pos = __CONTAINER_OF((begin)->next, pos, member), \
                tmp = __CONTAINER_OF(pos->member.next, pos, member); \
                &tmp->member != head; \
                pos = tmp, tmp = __CONTAINER_OF(pos->member.next, pos, member))



#define LIST_FOR_EACH_ENTRY_PREV_SAFE(pos, tmp, head, member)   \
            for(pos = __CONTAINER_OF((head)->prev, pos, member), \
                tmp = __CONTAINER_OF(pos->member.prev, pos, member); \
                &pos->member != head; \
                pos = tmp, tmp = __CONTAINER_OF(pos->member.prev, pos, member))


#endif
