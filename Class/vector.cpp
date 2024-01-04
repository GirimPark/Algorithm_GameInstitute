#include <iostream>
#include <vector>

class Cat
{
public:
    Cat() { std::cout << "Cat created\n"; }
    Cat(const int id) {

        m_id = id;
        std::cout << m_id << " Cat created with id\n";
    }
    Cat(const Cat& rhs) {

        m_id = rhs.m_id;
        std::cout << m_id << " Cat created by copying\n";
    }


    Cat(Cat&& rhs) noexcept {

        m_id = rhs.m_id;
        std::cout << m_id << " Cat created by moving\n";
    }

    ~Cat()
    {
        static int cnt;
        std::cout << m_id << " Cat destroyed " << ++cnt << " is Total. \n";
    }

    void Speak() const { std::cout << m_id << "  Meow\n"; }

    // assignment operators
    Cat& operator=(const Cat& rhs) { m_id = rhs.m_id; std::cout << m_id << " Cat assigned by copying\n"; return *this; }
    Cat& operator=(Cat&& rhs) noexcept { m_id = rhs.m_id;  std::cout << m_id << " Cat assigned by moving\n"; return *this; }


private:

    int m_id = 0;
};


void Test_Reserve()
{
    // 결과를 예상해 봅시다.  
    std::vector<Cat> v;
    v.reserve(3);
    //v.reserve(6);

    //v[0] = Cat(1); //가능할까요 ?

    std::cout << " \n capacity: " << v.capacity() << " size : " << v.size() << " \n  \n";

    v.push_back(100);
    v.push_back(200);
    v.push_back(300);

    std::cout << " \n capacity: " << v.capacity() << " size : " << v.size() << " \n  \n";

    v.push_back(400);
    v.push_back(500);
    v.push_back(600);

    std::cout << " \n capacity: " << v.capacity() << " size : " << v.size() << " \n  \n";

    for (const auto& cat : v)
    {
        cat.Speak();
    }

    std::cout << "\n --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- \n ";
}

void Test_Resize()
{
    // 결과를 예상해 봅시다.  
    std::vector<Cat> v;
    v.resize(3);
    //v.resize(6);

    std::cout << " \n capacity: " << v.capacity() << " size : " << v.size() << " \n  \n";

    v.push_back(100);
    v.push_back(200);
    v.push_back(300);

    std::cout << " \n capacity: " << v.capacity() << " size : " << v.size() << " \n  \n";

    v.push_back(400);
    v.push_back(500);
    v.push_back(600);

    std::cout << " \n capacity: " << v.capacity() << " size : " << v.size() << " \n  \n";

    for (const auto& cat : v)
    {
        cat.Speak();
    }

    std::cout << "\n --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- \n ";
}

void Test_Resize_2()
{
    // 결과를 예상해 봅시다.  
    std::vector<Cat> v;
    v.resize(3);
    //v.resize(6);

    std::cout << " \n capacity: " << v.capacity() << " size : " << v.size() << " \n  \n";

    for (int i = 0; i < 3; ++i)
    {
        v[i] = Cat(100 * (i + 1));
    }

    std::cout << " \n capacity: " << v.capacity() << " size : " << v.size() << " \n  \n";

    //v[3] = Cat(100 * (i + 1)); 가능할까요?

    for (const auto& cat : v)
    {
        cat.Speak();
    }

    std::cout << "\n --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- \n ";
}

int main()
{
    // Reserve 와 Resize 에 대해 알아 봅시다. 
    //Test_Reserve();
    Test_Resize();
    //Test_Resize_2();

    system("pause");

    return 0;
}