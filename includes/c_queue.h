#ifndef _C_QUEUE_HEADER_
#define _C_QUEUE_HEADER_

#include "c_helper.h"

typedef struct QueueBase {
	void* elems; unsigned int elemsize; unsigned int logiclen; unsigned int alloclen;
	void* front; void* rear;

	int(*DataCmp)(void *key1, void *key2, unsigned int keysize);
	void(*FreeFunc)(void* elems);
}QueueBase;

typedef struct QueueIter {
	void* data;
	void* prevfront;
	unsigned int index;
}QueueIter;

#define QueueT(T) \
struct { QueueBase base; T* ref; T data_; }

#define QueueNew(s, DataCmp, FreeFunc) \
	QueueNew_(&(s)->base, sizeof((s)->data_), DataCmp, FreeFunc)

#define QueuePush(s, data) \
	((s)->data_ = (data), \
	QueuePush_(&(s)->base, &(s)->data_))

#define QueuePop(s) \
	(s)->ref = QueueGet_(&(s)->base, &(s)->data_)

#define QueueTop(s) \
	(s)->ref = QueueGet_(&(s)->base, &(s)->data_)

#define QueueClear(s) \
	QueueClear_(&(s)->base)

#define QueueDelete(s) \
	QueueDelete_(&(s)->base)

#define QueueIterator(s) \
	QueueIterator_(&(s)->base)

#define QueueNext(s, iter) \
	QueueNext_(&(s)->base, iter)

#define QueueSize(s) \
	QueueSize_(&(s)->base)

void QueueNew_(QueueBase* q, unsigned int elem_size,
	int(*DataCmp)(void *key1, void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems));
void QueuePush_(QueueBase* q, void* elem);
void* QueuePop_(QueueBase* q);
void* QueueTop_(QueueBase* q);
void QueueClear_(QueueBase* q);
void QueueDelete_(QueueBase* q);
QueueIter* QueueIterator_(QueueBase* q);
void* QueueNext_(QueueBase* q, QueueIter* stackiter);
unsigned int QueueSize_(QueueBase* q);

typedef QueueT(void*) Queue;
typedef QueueT(double) QueueDouble;
typedef QueueT(float) QueueFloat;
typedef QueueT(int) QueueInt;
typedef QueueT(char*) QueueString;
typedef QueueT(char) QueueChar;
typedef QueueT(bool) QueueBool;

#endif