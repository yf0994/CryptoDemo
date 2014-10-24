#include <map>
#include <list>
#include <iterator>
#include <android/log.h>
using std::map;
using std::pair;
using std::list;
using std::iterator;

namespace callback
{

template<typename T, typename T2>
class CallbackCache
{
public:
    typedef bool (*Callback)(void* args, T2 &t);

    CallbackCache() : _limit(0), _good(true) {}
    ~CallbackCache(){}
    void setLimit(unsigned limit){ _limit = limit; }
    void setCallback(Callback func, void *args){ _func = func; _args = args;}
    void add(T const &t)
    { 
	_cache.push_back(t);
	if (_cache.size() >= _limit)
	    flush();
    }
    
    list<T> data(){ return _cache; }
    
    void addList(T2 const & t)
    {
	_cache.insert(_cache.end(), t.begin(), t.end());
	if (_cache.size() >= _limit)
	    flush();
    }

    /*
    template<typename T3>
    void addList(list<T>::iterator const &begin, list<T>::iterator const &end)
    {
	unsigned rest = _limit - _cache.size();
	if (end - begin > rest)
	{
	    auto iter = begin;
	    if (rest > 0)
	    {
		for (int i = 0; i < rest; ++i)
		    _cache.push_back(*(iter++));
	    }
	    flush();
	    addList(iter, end);
	}
	else
	{
	    _cache.insert(_cache.end(), begin, end);
	    if (_cache.size() >= _limit)
		flush();
	}
    }
    */
    
    void flush()
    {
	if (_cache.empty())
	    return;

	if(!_func(_args, _cache))
	{
	    _good = false;
	}
	else
	{
	    _good = true;
	    _cache.clear();
	}
    }

    void clear()
    {
	_cache.clear();
    }

    bool isGood() { return _good; }

    bool isEmpty(){ return _cache.empty(); }	
    T lastElement(){ return _cache.back(); }
    T firstElement(){ return _cache.front(); }
    T removeLastElement(){ T t = _cache.back(); _cache.pop_back(); return t;}
	
private:
    Callback _func;
    void *_args;
    list<T> _cache;	
    unsigned _limit;
    bool _good;
};

}

