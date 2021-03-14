#ifndef BASE_LIB_LIST_H
#define BASE_LIB_LIST_H

#include <stddef.h>
#include <stdbool.h>

#define READ_ONCE(var)  (*(const volatile typeof(var) *)&(var))
#define WRITE_ONCE(var, val)  (*((volatile typeof(val) *)(&(var))) = (val))
#define container_of(ptr, type, member) ({\
    const typeof( ((type *)0)->member ) *__mptr = (ptr);         \
    (type *)(void *)((char *)(__mptr) - offsetof(type, member));})

struct ListHead {
    struct ListHead *next, *prev;
};

static inline void InitListHead(struct ListHead *list)
{
    //list->next = list;
    WRITE_ONCE(list->next, list);
    list->prev = list;
}

static inline bool __list_add_valid(struct ListHead *new, struct ListHead *prev, struct ListHead *next)
{
    return true;
}

static inline bool __list_del_entry_valid(struct ListHead *entry)
{
    return true;
}

static inline void __list_add(struct ListHead *new, struct ListHead *prev, struct ListHead *next)
{
    if (!__list_add_valid(new, prev, next)) {
        return;
    }

    next->prev = new;
    new->next = next;
    new->prev = prev;
    WRITE_ONCE(prev->next, new);
}

static inline void ListAddHead(struct ListHead *new, struct ListHead *head)
{
    __list_add(new, head, head->next);
}

static inline void ListAddTail(struct ListHead *new, struct ListHead *head)
{
    __list_add(new, head->prev, head);
}

static inline void __list_del(struct ListHead * prev, struct ListHead *next)
{
    next->prev = prev;
    WRITE_ONCE(prev->next, next);
}


static inline void __list_del_entry(struct ListHead *entry)
{
    if (!__list_del_entry_valid(entry)) {
        return;
    }
     __list_del(entry->prev, entry->next);
}

static inline void list_del(struct ListHead *entry)
{
    __list_del_entry(entry);
    entry->next = NULL;//LIST_POISON1;
    entry->prev = NULL;//LIST_POISON2;
}

static inline int ListIsFirst(const struct ListHead *list, const struct ListHead *head)
{
    return list->prev == head;
}

static inline int ListIsLast(const struct ListHead *list, const struct ListHead *head)
{
    return list->next == head;
}

static inline int ListIsEmpty(const struct ListHead *head)
{
    return READ_ONCE(head->next) == head;
}


//list size

#define list_entry(ptr, type, member) container_of(ptr, type, member)


#define list_first_entry(ptr, type, member) \
        list_entry((ptr)->next, type, member)

#define list_last_entry(ptr, type, member) \
        list_entry((ptr)->prev, type, member)

#define list_next_entry(pos, member) \
        list_entry((pos)->member.next, typeof(*(pos)), member)


#define list_for_each(pos, head) \
        for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_safe(pos, n, head) \
        for (pos = (head)->next, n = pos->next; pos != (head); \
                pos = n, n = pos->next)

#define list_for_each_continue(pos, head) \
        for (pos = pos->next; pos != (head); pos = pos->next)

#define list_for_each_prev(pos, head) \
        for (pos = (head)->prev; pos != (head); pos = pos->prev)

#define list_for_each_prev_safe(pos, n, head) \
        for (pos = (head)->prev, n = pos->prev; \
             pos != (head); \
             pos = n, n = pos->prev)

#define list_entry_is_head(pos, head, member)                           \
        (&pos->member == (head))

#define list_for_each_entry(pos, head, member)                          \
        for (pos = list_first_entry(head, typeof(*pos), member);        \
             !list_entry_is_head(pos, head, member);                    \
             pos = list_next_entry(pos, member))

#define list_for_each_entry_safe(pos, next, head, member)                                             \
        for (pos = list_first_entry(head, typeof(*pos), member), next = pos->member.next; \
             !list_entry_is_head(pos, head, member);                                                  \
             pos = list_next_entry(next, member), next = pos->member.next)


#endif /* BASE_LIB_LIST_H */
