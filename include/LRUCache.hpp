#ifndef LRU_CACHE_HPP_
#define LRU_CACHE_HPP_

class LRUCacheBase
{
  public:
    virtual int get(int key) = 0;
    virtual void set(int key, int value) = 0;
};

#endif // LRU_CACHE_HPP_
