// SearchTextInFile.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Search2.h"

int main22(int argc, char** argv)
{
    std::cout << "Hello World!\n";

    //readFile();
    readFile2();
    getchar();
    return 0;


    boyerMoore bm;
    print = false;

    if (false) {
        if (argc == 1 || (strcmp(argv[1], "-np") && strcmp(argv[1], "-p")))
        {
            cout << "INPUT FORMAT: ./a.out -np [ If you want to only find the number of occurences ]\n";
            cout << "INPUT FORMAT: ./a.out -p [ If you want to print the  occurences as well ]\n";
            return 1;
        }
        else
            if (strcmp(argv[1], "-np"))
                print = true;
    }



    cout << "\nPlease wait while the files are being loaded..." << endl;
    bm.fileIn();
    cout << "Files Loaded Successfully!!\n";
    cout << "\n1. Case-Sensitive Search\t2. Case-Insensitive Search\t3. Exit";
    cout << "\n Enter Your Choice :";
    cin >> caseSensitive;
    getchar();
    while (caseSensitive != 3)
    {
        bm.patIn();
        bm.search();
        cout << "\n1. Case-Sensitive Search\t2. Case-Insensitive Search\t3. Exit";
        cout << "\n Enter Your Choice :";
        cin >> caseSensitive;
        getchar();
    }
    return 0;

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
