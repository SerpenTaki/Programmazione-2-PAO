#ifndef QUEUEITEM_H
#define QUEUEITEM_H

template <class T>
class QueueItem{
    friend class Queue<T>;
private:
    T info;
    QueueItem* next;
    QueueItem(const T& val) : info(val), next(0) {}
};

#endif