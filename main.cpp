#include "binaryTree.h"
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>
using namespace std;
long long lineRand()
{
	long long i = rand();
	i = (i << 32) | rand();
	return i;
}
void random_test(int n)
{
	BinaryTree<long long, int> testTree;
	long long* m = new long long[n];
	srand(time(NULL));
	for(int i=0; i<n; i++)
	{
		m[i]=lineRand();
		testTree.insert(m[i], 1);
	}
	cout << "Размер дерева до теста: " << testTree.getSize() <<endl;
	//обнуление счётчиков трудоёмкости вставки,
	//удаления и поиска
	double I=0;
	double D=0;
	double S=0;
	//генерация потока операций, 10% - промахи операций
	for(int i=0;i<n/2;i++)
	if(i%10==0)
	//10% промахов
	{
		testTree.remove(lineRand());
		D += testTree.getCountLastLooked();
		testTree.insert(m[rand()%n],1);
		I += testTree.getCountLastLooked();
		try{
			testTree.getData(lineRand());
			S+=testTree.getCountLastLooked();
		}
		//обработка исключения при ошибке операции поиска
		catch(out_of_range& e){ S += testTree.getCountLastLooked(); }
	}
	else //90% успешных операций
	{
		int ind = rand()%n;
		testTree.remove(m[ind]);
		D += testTree.getCountLastLooked();
		long long key = lineRand();
		testTree.insert(key, 1);
		I += testTree.getCountLastLooked();
		m[ind]=key;
		try{
		testTree.getData(m[rand()%n]);
		S += testTree.getCountLastLooked();
		}
		//обработка исключения при ошибке операции поиска
		catch(out_of_range& e){
			//cout << e.what() << endl;
			S+=testTree.getCountLastLooked();
			}
	} //конец теста
	//вывод результатов:
	//вывод размера дерева после теста
	cout << "Размер дерево после теста: " << testTree.getSize() << endl;
	//теоретической оценки трудоёмкости операций BST
	cout << "Теоретическая трудоемкость: 1.39*log2(n)=" <<1.39*(log((double)n)/log(2.0))<<endl;
	//экспериментальной оценки трудоёмкости вставки
	cout<<"Экспериментальная трудоемкость вставки: " << I/(n/2) <<endl;
	//экспериментальной оценки трудоёмкости удаления
	cout<<"Экспериментальная трудоемкость удаления: " << D/(n/2) <<endl;
	//экспериментальной оценки трудоёмкости поиска
	cout<<"Экспериментальная трудоемкость поиска: " << S/(n/2) <<endl;
	//освобождение памяти массива m[]
	delete[] m;
}

void ord_test(int n)
{
	BinaryTree<long long, int> testTree;
	long long* m = new long long[n];
	srand(time(NULL));
	for(int i=0; i<n; i++)
	{
		m[i]=10000*i;
		testTree.insert(m[i], 1);
	}
	cout << "Размер дерева до теста: " << testTree.getSize() <<endl;
	//обнуление счётчиков трудоёмкости вставки,
	//удаления и поиска
	double I=0;
	double D=0;
	double S=0;
	//генерация потока операций, 10% - промахи операций
	for(int i=0;i<n/2;i++)
	if(i%10==0)
	//10% промахов
	{
		long long k = lineRand()%(10000*n);
		k=k+!(k%2); //случайный нечётный ключ
		
		testTree.remove(k);
		D += testTree.getCountLastLooked();
		testTree.insert(m[rand()%n],1);
		I += testTree.getCountLastLooked();
		
		k = lineRand()%(10000*n);
		k=k+!(k%2); //случайный нечётный ключ
		try{
			testTree.getData(k);
			S+=testTree.getCountLastLooked();
		}
		//обработка исключения при ошибке операции поиска
		catch(out_of_range& e){ S += testTree.getCountLastLooked(); }
	}
	else //90% успешных операций
	{
		int ind = rand()%n;
		testTree.remove(m[ind]);
		D += testTree.getCountLastLooked();
		long long key = lineRand()%(10000*n);
		//key=key+key%2; // случайный чётный ключ
		testTree.insert(key, 1);
		I += testTree.getCountLastLooked();
		m[ind]=key;
		try{
		testTree.getData(m[rand()%n]);
		S += testTree.getCountLastLooked();
		}
		//обработка исключения при ошибке операции поиска
		catch(out_of_range& e){
			//cout << e.what() << endl;
			S+=testTree.getCountLastLooked();
			}
	} //конец теста
	//вывод результатов:
	//вывод размера дерева после теста
	cout << "Размер дерева после теста: " << testTree.getSize() << endl;
	//теоретической оценки трудоёмкости операций BST
	cout << "Теоретическая трудоемкость: n/2 = " << n/2 <<endl;
	//экспериментальной оценки трудоёмкости вставки
	cout<<"Экспериментальная трудоемкость вставки: " << I/(n/2) <<endl;
	//экспериментальной оценки трудоёмкости удаления
	cout<<"Экспериментальная трудоемкость удаления: " << D/(n/2) <<endl;
	//экспериментальной оценки трудоёмкости поиска
	cout<<"Экспериментальная трудоемкость поиска: " << S/(n/2) <<endl;
	//освобождение памяти массива m[]
	delete[] m;
}
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    BinaryTree<int, int> tree;
	
	int q = 0, search = 0, wr = 0;

    // Вставляем несколько элементов
    /*tree.insert(10, 1);
    tree.insert(5, 2);
    tree.insert(15, 3);
    tree.insert(7, 5);
    tree.insert(3 ,5);
    tree.insert(12, 45);
    tree.insert(18, 53);
    tree.insert(20, 5);
    tree.insert(2, 23);*/
	//tree._min(tree.root)->print();
	//if(tree._BSTSuccessor(tree._max(tree.root)) == nullptr) cout<< "NULLLL" <<endl;
	//if(tree._BSTPredecessor(tree._min(tree.root)) == nullptr) cout<< "NULLLL" <<endl;
	
	//tree._max(tree.root)->print();
    /*cout << "Рандомные тесты" << endl;
	random_test(50000);
    cout << "Вырожденные тесты" << endl;
	ord_test(5000);*/
	
	BinaryTree<int, int>::Iterator iter = tree.begin();
	/*for(iter = tree.begin(); iter != tree.end(); ++iter)
		iter.print();*/
	
	BinaryTree<int, int>::ReverseIterator iterR = tree.rbegin();
	/*for(iterR = tree.rbegin(); iterR != tree.rend(); ++iterR)
		iterR.print();*/
	
    while (true)
    {
        cout << "Методы дерева:" << endl;
        cout << "1. Опрос размера дерева" << endl;
        cout << "2. Очистка дерева" << endl;
        cout << "3. Проверка дерева на пустоту" << endl;
        cout << "4. Доступ по чтению/записи к данным по ключу" << endl;
        cout << "5. Включение данных с заданным ключом" << endl;
        cout << "6. Удаление данных с заданным ключом" << endl;
        cout << "7. Список ключей в порядке обхода узлов L-t-R" << endl;
        cout << "8. Определение длины внешнего пути дерева" << endl;
        cout << "9. Вывод дерева" << endl;
        cout << "10. Количество просмотренных элементов" << endl;
        cout << "\nМетоды прямого итератора:" << endl;
        cout << "11. Назначить прямой итератор" << endl;
        cout << "23. Записать данные прямого итератора" << endl;
        cout << "13. Вывести данные прямого итератора" << endl;
        cout << "15. Сравнить прямой итератор" << endl;
        cout << "17. Шаг вперёд прямого итератора" << endl;
        cout << "18. Шаг назад прямого итератора" << endl;
        cout << "\nМетоды обратного итератора:" << endl;
        cout << "12. Назначить обратный итератор" << endl;
        cout << "24. Записать данные обратного итератора" << endl;
        cout << "14. Вывести данные обратного итератора" << endl;
        cout << "16. Сравнить обратный итератор" << endl;
        cout << "19. Шаг вперёд обратного итератора" << endl;
        cout << "20. Шаг назад обратного итератора" << endl;
        cout << "\nФункции для тестов:" << endl;
        cout << "21. Тесты для случайного дерева" << endl;
        cout << "22. Тесты для вырожденного дерева" << endl;
        cout << "\n0. Выход" << endl;
        cout << "Введите значение: ";
        cin >> q;
        switch (q)
        {
        case 1:
            cout << "Размер дерева: " << tree.getSize() << endl;
            break;
        case 2:
            tree.clear();
            cout << "Дерево очищено" << endl;
            break;
        case 3:
            if (tree.isEmpty())
                cout << "Дерево пусто" << endl;
            else
                cout << "Дерево не пусто" << endl;
            break;
        case 4:
            cout << "1. Прочитать значение" << endl;
            cout << "0. Перезаписать значение" << endl;
            cin >> q;
            if (q == 1)
            {
                cout << "Введите ключ: " ;
                cin >> search;
                try
                {
                    cout << "Значение: " << tree[search] << endl;;
                }
                catch (out_of_range& e)
                {
                    cout << e.what() << endl;
                }
            }
            else
            {
                cout << "Введите значение: " ;
                cin >> search;
                cout << "Введите новое значение: " << endl;
                cin >> wr;
                try
                {
                    tree[search] = wr;
                    cout << "Успешно" << endl;
                }
                catch (out_of_range& e)
                {
                    cout << e.what() << endl;
                }
            }
            break;
        case 5:
            cout << "Введите значение ключа: " ;
            cin >> search;
			cout << "Введите данные: " ;
            cin >> q;
            if(tree.insert(search, q))
            cout << "Успешно" << endl;
            else
                cout << "Ошибка" << endl;
            break;
        case 6:
            cout << "Введите ключ: ";
            cin >> search;
            if (tree.remove(search))
                cout << "Успешно" << endl;
            else
                cout << "Ошибка" << endl;
            break;
        case 7:
            cout << "Обход дерева L-t-R: ";
            for (auto i : tree.keysInOrder())
                cout << i<<" ";
            break;
        case 8:
            cout << "Длина внешнего пути: "<<tree.externalPathLength();
            break;
        case 9:
            tree.print();
            break;
        case 10:
            cout << "Количество просмотренных элементов: " << tree.getCountLastLooked() << endl;
            break;
        case 11:
            iter = tree.begin();
            cout << "Прямой итератор назначен" << endl;
            break;
        case 12:
            iterR = tree.rbegin();
            cout << "Обратный итератор назначен" << endl;
            break;
        case 13:
            try
            {
                cout << *iter << endl;
            }
            catch (out_of_range& e)
            {
                cout << e.what() << endl;
            }
            break;
        case 14:
            try
            {
                cout << *iterR << endl;
            }
            catch (out_of_range& e)
            {
                cout << e.what() << endl;
            }
            break;
        case 15:
            if (iter == tree.end())
                cout << "Итераторы равны" << endl;
            else
                cout << "Итераторы не равны" << endl;
            break;
        case 16:
            if (iterR == tree.rend())
                cout << "Итераторы равны" << endl;
            else
                cout << "Итераторы не равны" << endl;
            break;
        case 17:
            ++iter;
            break;
        case 18:
            --iter;
            break;
        case 19:
            ++iterR;
            break;
        case 20:
            --iterR;
            break;
        case 21:
            cout << "\nВведите число элементов: ";
            cin >> search;
            cout << "\n";
            random_test(search);
            break;
        case 22:
            cout << "\nВведите число элементов(не более 5000): ";
            cin >> search;
            cout << "\n";
            ord_test(search);
            break;
        case 23:
            try {
                cout << "Введите данные: " << endl;
                cin >> search;
                *iter = search;
            }
            catch (out_of_range& e)
            {
                cout << e.what() << endl;
            }
            //cout << *iter;
            break;
        case 24:
            try {
                cout << "Введите данные: " << endl;
                cin >> search;
                *iterR = search;
            }
            catch (out_of_range& e)
            {
                cout << e.what() << endl;
            }
            break;
        case 0:
            exit(0);
        default:
            break;
        }
        _getch();
        system("cls");
    }
    return 0;
}