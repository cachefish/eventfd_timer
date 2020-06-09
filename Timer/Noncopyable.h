#ifndef _NONCOPYABLE_H__
#define _NONCOPYABLE_H_


class Noncopyable
{
protected:
    Noncopyable(){}
    ~Noncopyable(){}

    Noncopyable(const Noncopyable&)=delete;
    Noncopyable&operator = (const Noncopyable&) = delete;

};

#endif