//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _Singleton_
#define _Singleton_



#include <iostream>

template <class T>
class Singleton
{
public:
 
  static
  T* getInstance()
  {
    if (!instance_)
      {
        instance_ = new T();
      }

    return instance_;
  }
  static
  void destroyInstance()
  {
    delete instance_;
    instance_ = nullptr;
  }

private:
  static T* instance_;
  //Singleton(Singleton const&);              // Don't Implement
  //Singleton();
  void operator=(Singleton const&); // Don't implement
};

template <class T> T*  Singleton<T>::instance_ = nullptr;



#endif