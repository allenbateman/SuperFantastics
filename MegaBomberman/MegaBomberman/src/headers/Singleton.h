#pragma once

#include "../simple_types.h"

template<class T>
class Singleton {
protected:
	static T* pInstance;

	Singleton();
	~Singleton();
public:
	static T* getInstance();
};

template<class T>
inline Singleton<T>::Singleton()
{
}

template<class T>
inline Singleton<T>::~Singleton()
{
	pInstance = NULL;
}

template<class T>
inline T * Singleton<T>::getInstance()
{
	if (pInstance == NULL) {
		pInstance = new T();
	}

	return pInstance;
}

template <class T>
T* Singleton<T>::pInstance = NULL;