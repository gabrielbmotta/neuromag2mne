template<typename T>
class Pointer{
public: 
    Pointer(){ptr = new T();};
    ~Pointer(){delete ptr;};

    T* operator -> () const
    {
        return *ptr;
    }
private:
    T* ptr;
};