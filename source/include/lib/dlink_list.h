#ifndef DLLIST_H
#define DLLIST_H

#include "lib/nostdio.h"
#include "lib/nostdlib.h"

typedef struct dl_node_t {
	struct dl_node_t* prev;
	struct dl_node_t* next;
} dl_node;

static inline void init_dl_node (dl_node* node) {
	node->prev = node;
	node->next = node;
}

static inline void add_node (dl_node* before, dl_node* after, dl_node* node) {
	before->next = node;
	node->prev = before;
	after->prev = node;
	node->next = after;
}

static inline void delete_node (dl_node* node) {
	if (node != NULL) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
}

static inline void unpin_node (dl_node* node) {
	if (node != NULL) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
}

static inline void delete_tail (dl_node* head) {
	unpin_node (head->next);
}

static inline void add_tail (dl_node* head, dl_node* node) {
	add_node (head, head->next, node);
}

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE, MEMBER) __compiler_offsetof(TYPE, MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE*)0)->MEMBER)
#endif

#define container_of( ptr, type, member ) \
   ( \
      { \
         const typeof( ((type *)0)->member ) *__mptr = (ptr); \
         (type *)( (char *)__mptr - offsetof( type, member ) ); \
      } \
   )

#define list_entry(ptr, type, member)\
	container_of(ptr, type, member)

#define define_list(name, type) \
	typedef struct name##_head_t { \
		dl_node _private;\
	}name##_head;\
	\
	static inline type* name##_head_first (name##_head* head) {\
		return list_entry (head->_private.next, type, name);\
	}\
	\
	static inline type* name##_head_prev (name##_head* head) {\
		return list_entry (head->_private.prev, type, name);\
	}\
	\
	static inline type* name##_next (const type* node) { \
		return list_entry (node->name.next, type, name);\
	}\
	\
	static inline int name##_is_last (name##_head* head, const type* node) {\
		return &(head->_private) - &(node->name);\
	}\
	\
	static inline void name##_init (name##_head* head) {\
		init_dl_node (&head->_private);\
	}\
	\
	static inline void name##_add_tail (name##_head* head, type* node) {\
		add_tail (&head->_private, &node->name);\
	}


#endif
