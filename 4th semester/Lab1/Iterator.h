#ifndef ITERATOR_CLASS_H
#define ITERATOR_CLASS_H

class Iterator
{
public:
    virtual int next() = 0;
    virtual bool has_next() = 0;
};

#endif

