#ifndef EXCELLENTEAM_ELLA_CPP_SINGLETON_HODAYAMAR_SFAETREADSINGELTON_H
#define EXCELLENTEAM_ELLA_CPP_SINGLETON_HODAYAMAR_SFAETREADSINGELTON_H

#include <iostream>         //std
#include <semaphore.h>

template<typename T>
class Singleton
{
public:
    static T* GetInstance();

private:

    Singleton(Singleton const&);
    Singleton& operator=(Singleton const&);
    static void destroy();

protected:

    static T* m_instance;
    pthread_mutex_t mtx;
    Singleton();
    ~Singleton();
};

template<typename T>
Singleton<T>::Singleton()
{
    m_instance = static_cast <T*> (this);
    if ( pthread_mutex_init ( &mtx, NULL ) != 0 )
    {
        std::cout << "\n mutex init failed\n" << std::endl;
    }
}

template<typename T>
Singleton<T>::~Singleton()
{
    destroy();
}

template<typename T>
T* Singleton<T>::m_instance = NULL;

template<typename T>
T* Singleton<T>::GetInstance()
{
    pthread_mutex_lock( &Singleton<T>::mtx );
    // insert memory barrier

    if (m_instance == NULL) {
        try {
            m_instance = new T;
            // insert memory barrier
        }
        catch (std::bad_alloc) {
            pthread_mutex_unlock(&Singleton<T>::mtx);
            throw;
        }
        pthread_mutex_unlock(&Singleton<T>::mtx);
    }
    return m_instance;
}

template<typename T>
void Singleton<T>::destroy()
{
    delete Singleton<T>::m_instance;
    Singleton<T>::m_instance = 0;
    pthread_mutex_destroy( &Singleton<T>::mtx );

}

#endif //EXCELLENTEAM_ELLA_CPP_SINGLETON_HODAYAMAR_SFAETREADSINGELTON_H
