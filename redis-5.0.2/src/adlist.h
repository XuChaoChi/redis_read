/* adlist.h - A generic doubly linked list implementation
 *
 * Copyright (c) 2006-2012, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __ADLIST_H__
#define __ADLIST_H__

/* Node, List, and Iterator are the only data structures used currently. */

//双向链表节点
typedef struct listNode {
    struct listNode *prev;
    struct listNode *next;
    void *value;
} listNode;

//迭代器
typedef struct listIter {
    listNode *next;
    int direction;//迭代器访问方向
} listIter;

typedef struct list {
    listNode *head;//头
    listNode *tail;//尾巴
    //针对不同类型值的一下函数指针
    void *(*dup)(void *ptr);//复制函数指针
    void (*free)(void *ptr);//释放函数指针
    int (*match)(void *ptr, void *key);//对比函数指针
    unsigned long len;//链表长度
} list;

/* Functions implemented as macros */
#define listLength(l) ((l)->len) //获取长度
#define listFirst(l) ((l)->head) //获取头
#define listLast(l) ((l)->tail) //获取尾
#define listPrevNode(n) ((n)->prev) //获取前置节点
#define listNextNode(n) ((n)->next) //获取后置节点
#define listNodeValue(n) ((n)->value) //获取值

#define listSetDupMethod(l,m) ((l)->dup = (m))  //设置复制函数指针
#define listSetFreeMethod(l,m) ((l)->free = (m)) //设置释放函数指针
#define listSetMatchMethod(l,m) ((l)->match = (m)) //设置对比函数只恨

#define listGetDupMethod(l) ((l)->dup) //获取复制函数指针
#define listGetFree(l) ((l)->free)  //获取释放函数指针
#define listGetMatchMethod(l) ((l)->match) //获取对比函数指针

/* Prototypes */
list *listCreate(void); 
void listRelease(list *list);
void listEmpty(list *list);
list *listAddNodeHead(list *list, void *value);
list *listAddNodeTail(list *list, void *value);
list *listInsertNode(list *list, listNode *old_node, void *value, int after);
void listDelNode(list *list, listNode *node);
listIter *listGetIterator(list *list, int direction);
listNode *listNext(listIter *iter);
void listReleaseIterator(listIter *iter);
list *listDup(list *orig);
listNode *listSearchKey(list *list, void *key);
listNode *listIndex(list *list, long index);
void listRewind(list *list, listIter *li);
void listRewindTail(list *list, listIter *li);
void listRotate(list *list);
void listJoin(list *l, list *o);

/* Directions for iterators */
//迭代器的指向
#define AL_START_HEAD 0
#define AL_START_TAIL 1

#endif /* __ADLIST_H__ */
