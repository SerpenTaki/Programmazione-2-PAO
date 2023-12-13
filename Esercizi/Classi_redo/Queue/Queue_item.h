#ifndef QUEUEITEM_H
#define QUEUEITEM_H

template <class T>
class QueueItem{
public:
    QueueItem(const T& val) : info(val), next(0) {}
    T info;
    QueueItem* next;
};

#endif