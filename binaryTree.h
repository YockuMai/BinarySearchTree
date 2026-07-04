#include <iostream>
#include <vector>


template <typename Key, typename Data> 
class BinaryTree
{
private:
	template <typename Key, typename Data>
	class TreeNode
	{
	public:
		//ключ объекта
		Key key;
		//значение объекта в элементе
		Data data;
		// указатель на левого сына
		TreeNode* left;
		//указатель на правого сына
		TreeNode* right;
		//конструктор с параметрами
		TreeNode(Data d, Key k) : key(k), data(d), left(nullptr), right(nullptr) {}
		void print() { std::cout << "k: " << key << "; d: " << data << std::endl; }
	};
//размер дерева
	int size; 
//указатель на корень
	TreeNode<Key, Data> *root;
//количество просмотренных элементов
	int cnt_last_looked;	
public:
//конструктор без параметров
	BinaryTree() 
    {
        root = nullptr;
        size = 0;
        cnt_last_looked = 0;
    }                                              
//конструктор копирования
	BinaryTree(const BinaryTree<Data, Key>& anotherTree)
    {
        root = nullptr;
        size = 0;
        cnt_last_looked = 0;
        _copy(anotherTree.root);
    }            
//деструктор
	~BinaryTree()
    {
        clear();
    }                                                                                
//очистка дерева
	void clear()
    {
        _clear(root);
        root = nullptr;
        size = 0;
		cnt_last_looked = 0;
    }   
//опрос размера дерева
	int getSize()
    {
        return size;
    }                                    
//проверка дерева на пустоту
	bool isEmpty()
    {
        if (root == nullptr || size == 0)
            return true;
        return false;
    }                                       
//доступ к данным с заданным ключом
	Data& getData(Key key)
	{
		cnt_last_looked = 0;
		TreeNode<Key, Data>* currentNode = root;
		while (currentNode != nullptr)
		{
			cnt_last_looked++;
			if (key == currentNode->key)
				return currentNode->data;
			else if (key < currentNode->key)
				currentNode = currentNode->left;
			else
				currentNode = currentNode->right;
		}
		throw std::out_of_range("Такого ключа нет(исключение)");
		
	}
	Data& operator[](Key key) {
        return getData(key);
    }	
//включение данных с заданным ключом
	bool insert(Key key, Data data)
    {
		cnt_last_looked = 0;
        if (root == nullptr) 
        {
            root = new TreeNode<Key, Data>(data, key);
            size++;
            return true;

        }

        TreeNode<Key, Data>* t = root;
        TreeNode<Key, Data>* pred = nullptr;
        while (t != nullptr) 
        {
			cnt_last_looked++;
            pred = t;
            if (key == t->key) {
                return false;
            } else if (key < t->key) {
                t = t->left;
            } else {
                t = t->right;
            }
        }
        if (key < pred->key) {
            pred->left = new TreeNode<Key, Data>(data, key);
        } else {
            pred->right = new TreeNode<Key, Data>(data, key);
        }
        size++;
        return true;
    }           
//удаление данных с заданным ключом
	bool remove(Key key){
		cnt_last_looked = 0;
		TreeNode<Key, Data>* parent = nullptr;
		TreeNode<Key, Data>* current = root;
		cnt_last_looked++;
        // Поиск узла с заданным ключом
        while (current != nullptr && current->key != key) {
            parent = current;
            if (key < current->key)
                current = current->left;
            else
                current = current->right;
			cnt_last_looked++;
        }
		
        if (current == nullptr)	// узел с заданным ключом не найден
            return false;
		
		if (current->left == nullptr && current->right == nullptr) {	// У удаляемого нет потомков
            if (current != root) {
                if (parent->left == current)
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
            }
            else
                root = nullptr;
            delete current;
        }
        else if (current->left == nullptr) {	// у удаляемого есть только правый потомок
            if (current != root) {
                if (parent->left == current)
                    parent->left = current->right;
                else
                    parent->right = current->right;
            }
            else
                root = current->right;
            delete current;
        }
        else if (current->right == nullptr) { // только левый потомок
            if (current != root) {
                if (parent->left == current)
                    parent->left = current->left;
                else
                    parent->right = current->left;
            }
            else
                root = current->left;
            delete current;
        }
        else {	// есть оба потомка
            TreeNode<Key, Data>* temp = current->right;
            TreeNode<Key, Data>* tempParent = current;

            while (temp->left != nullptr) {
				cnt_last_looked++;
                tempParent = temp;
                temp = temp->left;
            }
			//cnt_last_looked++;
            current->key = temp->key;

            if (tempParent->left == temp)
                tempParent->left = temp->right;
            else
                tempParent->right = temp->right;

            delete temp;
        }
		size--;
        return true;
	}                   
//вывод структуры дерева на экран
	void print()
    {
        std::cout << "Размер: " << size << std::endl;
        _print(root, 0);
    }                                       
	int getCountLastLooked()
	{
		return cnt_last_looked;
	}

	// Метод для получения ключей в порядке обхода узлов по схеме Lt > t > Rt
    std::vector<Key> keysInOrder()
	{
        std::vector<Key> keys;
        inOrderTraversal(root, keys);
        return keys;
    }       
	
//определение длины внешнего пути дерева  (рекурсивно)
	int externalPathLength()
	{
		cnt_last_looked = 0;
		if (root == nullptr) 
			return 0;
		int externalPath = 0;
		_externalPathLength(root, 1, externalPath);
		return externalPath;
	}                         
 
private:
//вспомогательная функция для копирования дерева
	void _copy(TreeNode<Key, Data> *node){
		if(node == nullptr)
			return;
		insert(node->key, node->data);
		_copy(node->left);
		_copy(node->right);
    }                             
//вспомогательная функция для очистки дерева по LtR (рекурсия)
	void _clear(TreeNode<Key, Data>* node)
    {
        if (node == nullptr)
            return;

        _clear(node->left);
        _clear(node->right);
        delete node;
    }                             
//вспомогательная функция для вывода структуры
	void _print(TreeNode<Key, Data> *node, int level)
    {
        if (node == nullptr)
            return;

        _print(node->right, level + 1);
        for (int i = 0; i < level; ++i)
            std::cout << "    ";
        std::cout << node->key << std::endl;
        _print(node->left, level + 1);
    }                 
// Рекурсивная функция для обхода узлов дерева в порядке Lt > t > Rt
    void inOrderTraversal(TreeNode<Key, Data>* node, std::vector<Key>& keys){
        if (node == nullptr)
            return;

        inOrderTraversal(node->left, keys);
        keys.push_back(node->key);
        inOrderTraversal(node->right, keys);
    }
//вспомогательная функция для определения внешнего пути
	void _externalPathLength(TreeNode<Key, Data> *node, int level, int& externalPath)
	{
		cnt_last_looked++;
		if (node == nullptr) 
			return;
		_externalPathLength(node->left, level + 1, externalPath);
		_externalPathLength(node->right, level + 1, externalPath);
		if (node->left == nullptr || node->right == nullptr)
			externalPath += level;
	}  
//поиск максимального по ключу узла в поддереве 
	TreeNode<Key, Data>* _max(TreeNode<Key, Data> *cur)
	{
		if (cur == nullptr)
			return nullptr;
		while (cur->right != nullptr)
			cur = cur->right;
		return cur;
	}                              
//поиск минимального по ключу узла в поддереве 
	TreeNode<Key, Data>* _min(TreeNode<Key, Data> *cur)
	{
		if (cur == nullptr)
			return nullptr;
		while (cur->left != nullptr)
			cur = cur->left;
		return cur;
	}                           
//поиск ближайшего правого родителя для заданного узла дерева
	TreeNode<Key, Data>* _rightParent(TreeNode<Key, Data> *t, TreeNode<Key, Data> *x)
	{
		if(t == x) return nullptr;
		TreeNode<Key, Data>* parent = nullptr;
		if (x->key > t->key)
		{
			parent = _rightParent(t->right,x);
			if (parent != nullptr) 
				return parent;
			else return t;
		}
		else return _rightParent(t->left,x);
	}            
//поиск ближайшего левого родителя для заданного узла дерева
	TreeNode<Key, Data>* _leftParent(TreeNode<Key, Data> *t, TreeNode<Key, Data> *x)
	{
		if(t == x) return nullptr;
		TreeNode<Key, Data>* parent = nullptr;
		if (x->key < t->key)
		{
			parent = _leftParent(t->left, x);
			if (parent != nullptr) 
				return parent;
			else return t;
		}
		else return _leftParent(t->right, x);
	}
//рекурсивный алгоритм поиска предыдущего по ключу узла
	TreeNode<Key, Data>* _BSTPredecessor(TreeNode<Key, Data> *x)
	{
		if (x == nullptr) return nullptr;
		if (x->left != nullptr)
			return _max(x->left);
		else return _rightParent(root, x);
	}	
//рекурсивный алгоритм поиска следующего по ключу узла
	TreeNode<Key, Data>* _BSTSuccessor(TreeNode<Key, Data> *x)
	{
		if (x == nullptr) return nullptr;
		if (x->right != nullptr)
			return _min(x->right);
		else return _leftParent(root, x);
	}                   
            

public:
	class Iterator
	{
	private:
//указатель на объект коллекции
		BinaryTree<Data, Key> *ptr_tree;	                        
//указатель на текущий элемент коллекции
		TreeNode<Key, Data> *cur;	                        
	public:
//конструктор
		Iterator(BinaryTree<Data, Key>* tree, TreeNode<Key, Data>* curr): ptr_tree(tree), cur(curr) {}
		
		// Переход к следующему узлу в дереве
		Iterator& operator++()
		{
			cur = ptr_tree->_BSTSuccessor(cur);
			return *this;
		}
		// Переход к предыдущему узлу в дереве
		Iterator& operator--()
		{
			cur = ptr_tree->_BSTPredecessor(cur);
			return *this;
		}
		// Проверка на равенство
		bool operator==(const Iterator& other)
		{
			return (cur == other.cur);
		} 
		// Проверка на неравенство
		bool operator!=(const Iterator& other)
		{
			return (cur != other.cur);
		}	        
			//доспуп к данным текущего элемента
		Data& operator*()
		{
			if (cur != nullptr)
				return cur->data;
			else
				throw std::out_of_range("Итератор вышел за пределы(исключение)");
		}
		void print()
		{
			if (cur != nullptr)
			cur->print();
			else
				throw std::out_of_range("Итератор вышел за пределы(исключение)");
		}
	};
	// Возвращает прямой итератор на начало
	Iterator begin()
	{
		return Iterator(this, _min(root));
	}
	// Возвращает прямой итератор на конец
    Iterator end()
	{
		return Iterator(this, nullptr);
	} 
	
	class ReverseIterator
	{
	private:
//указатель на объект коллекции
		BinaryTree<Data, Key> *ptr_tree;	                        
//указатель на текущий элемент коллекции
		TreeNode<Key, Data> *cur;	                        
	public:
//конструктор
		ReverseIterator(BinaryTree<Data, Key>* tree, TreeNode<Key, Data>* curr): ptr_tree(tree), cur(curr) {}
		
		// Переход к следующему узлу в дереве
		ReverseIterator& operator++()
		{
			cur = ptr_tree->_BSTPredecessor(cur);
			return *this;
		}
		// Переход к предыдущему узлу в дереве
		ReverseIterator& operator--()
		{
			cur = ptr_tree->_BSTSuccessor(cur);
			return *this;
		}
		// Проверка на равенство
		bool operator==(const ReverseIterator& other)
		{
			return (cur == other.cur);
		} 
		// Проверка на неравенство
		bool operator!=(const ReverseIterator& other)
		{
			return (cur != other.cur);
		}	        
			//доспуп к данным текущего элемента
		Data& operator*()
		{
			if (cur != nullptr)
				return cur->data;
			else
				throw std::out_of_range("Итератор вышел за пределы(исключение)");
		}
		void print()
		{
			if (cur != nullptr)
				cur->print();
			else
				throw std::out_of_range("Итератор вышел за пределы(исключение)");
		}
	};
	// Возвращает обратный итератор на начало
	ReverseIterator rbegin()
	{
		return ReverseIterator(this, _max(root));
	} 
	// Возвращает обратный итератор на конец
    ReverseIterator rend()
	{
		return ReverseIterator(this, nullptr);
	} 
	
	
	friend class Iterator;
	friend class ReverseIterator;
};
