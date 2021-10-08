#ifndef NONCOPYABLE_H__
#define NONCOPYABLE_H__

class noncopyable
{
public:
    noncopyable(const noncopyable &) = delete;
    void operator=(const noncopyable &) = delete;

protected:
    noncopyable() = delete;
    ~noncopyable() = default;
};

#endif