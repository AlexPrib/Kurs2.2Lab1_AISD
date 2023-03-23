#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

class Set
{
    struct TreeNode
    {
        int data;
        TreeNode * left, * right;
        TreeNode(int data, TreeNode* left, TreeNode* right) : data(data), left(left), right(right){};
    };
    TreeNode* root;

    TreeNode* _copying(TreeNode* copy)
    {
        if (!copy) { return nullptr; }
        TreeNode* root_copy = new TreeNode(copy->data, nullptr, nullptr);
        root_copy->left = _copying(copy->left);
        root_copy->right = _copying(copy->right);
        return root_copy;
    }

	static void to_vector_(vector<int>& vec, const TreeNode* root) {
		if (!root) { return; }
		to_vector_(vec,root->left);
		vec.push_back(root->data);
		to_vector_(vec, root->right);
	}

    void print_tree(const TreeNode* root)
    {
        if (!root) { return; }
        print_tree(root->left);
        cout << root->data << " ";
        print_tree(root->right);
    }

    void free_tree(TreeNode* root)
    {
        if (!root) { return; }
        if (root->left) { free_tree(root->left); }
        if (root->right) { free_tree(root -> right); }
        root = nullptr;
    }

    bool _contains(int key, TreeNode* root)
    {
        if (!root) { return false; }
        if (key == root->data)
        {
            return true;
        }
        if (key < root -> data)
        {
           return _contains(key, root->left);
        }
        if (key > root->data)
        {
            return _contains(key, root->right);
        }
        
    }

    TreeNode* _insert(int key, TreeNode* root)
    {
        if (!root) { return new TreeNode(key, nullptr, nullptr); }
        if (key < root->data) {root->left = _insert(key, root->left); }
        if (key > root->data) {root->right = _insert(key, root->right); }
        return root;
    }

    TreeNode* min(TreeNode* root)
    {
        if (!root->left) { return root; }
        return min(root->left);
    }


    TreeNode* _erase(int key, TreeNode* root)
    {
        if (!root) { return root; }
        if (key < root->data) {root -> left = _erase(key, root->left); }
        else if (key > root->data) {root -> right = _erase(key, root->right); }
        else if (root->left && root->right)
        {
            root->data = min(root->right)->data;
            root->right = _erase(root->data, root->right);
        }
        else
        {
            if (root->left) { root = root->left; }
            else if (root->right) { root = root->right;}
            else { return nullptr; }

        }
        return root;
    }



public:
    Set()
    {
        root = nullptr;
    }
    ~Set()
    {
        if (root) { free_tree(root); delete root; }
    }
    Set& operator = (const Set& copy) {
        if (!copy.root) {
            free_tree(root);
            delete root;
            return *this;
        }
        else 
        {
            if (!root)
            {
                root = _copying(copy.root);
            }
            else
            {
                free_tree(root);
                delete root;
                root = _copying(copy.root);
            }
            return *this;
        }
    }

    void tree_print()
    {
        print_tree(root);
    }

    bool insert(int key)
    {
        if (!_contains(key, root)) {root = _insert(key, root); return true; }
        return false; 
    }

    bool contains(int key)
    {
        return _contains(key, root);
    }

    bool erase(int key)
    {
        if (_contains(key, root)) { _erase(key, root); return true; }
        return false;
    }

	vector<int> to_vector() const {
		vector<int> tmp;
		to_vector_(tmp, root);
		return tmp;
	}

	void clear() { free_tree(root); }
};
//vector<int> task (const vector<int>& v)
//{
//    vector<int> tmp;
//    vector<int>tmp2;
//    for (size_t i = 0; i < v.size()-1; i++)
//    {
//        for (size_t j=i+1; j < v.size(); j++)
//        {
//            if (v[i] ==v[j] && !binary_search(tmp2.begin(),tmp2.end(),v[i]))
//            {
//                tmp2.push_back(v[i]);
//                break;
//            }
//        }
//    }
//    for (size_t i = 0; i < v.size();i++)
//    {
//        bool flag = true;
//        for (size_t j = 0; j < tmp2.size(); j++)
//        {
//            if (v[i] == tmp2[j]) { flag = false; }
//        }
//        if (flag) { tmp.push_back(v[i]); }
//    }
//    return tmp;
//
//}


vector<int> task(const vector<int>& vec) {
	Set temp;
	vector<int> tmp;
	for (auto i : vec) {
		if (!temp.insert(i)) {
			tmp.push_back(i);
		}
	}
	for (auto i : tmp) {
		temp.erase(i);
	}
	return temp.to_vector();
}

//size_t lcg() {
//    static size_t x = 0;
//    x = (1021 * x + 24631) % 116640;
//    return x;
//}
//
//double avg(const double* ar) {
//    double sum = 0;
//    for (size_t i = 0; i < 100; ++i) {
//        sum += ar[i];
//    }
//    return sum / 100;
//}
//
//double avg1000(const double* ar) {
//    double sum = 0;
//    for (size_t i = 0; i < 1000; ++i) {
//        sum += ar[i];
//    }
//    return sum / 1000;
//}






int main()
{
    vector<int> f_vector = { 2,4,6,7,2,4,5,1,3};
    Set proverka;
    Set proverka2;
    proverka.insert(10);
    proverka.insert(8);
    proverka.insert(6);
    proverka.insert(9);
    proverka.insert(15);
	proverka.insert(13);
	proverka.insert(11);
	proverka.insert(14);
	proverka.insert(20);


    proverka2 = proverka;
    proverka2.tree_print();
	proverka2.erase(10);
	cout << endl;
	proverka2.tree_print();
    cout << endl;
    vector<int> s_vector = task(f_vector);
    for (auto i : s_vector) {
        cout << i << " ";
    }
	cout << endl;
    
	////ТЕСТЫ
	//Set timetest1000, timetest10000, timetest100000;
	//vector<int> filltest1000, filltest10000, filltest100000;

	//double fill_vattempts_1000[100], fill_vattempts_10000[100], fill_vattempts_100000[100];
	//double fillattempts_1000[100], fillattempts_10000[100], fillattempts_100000[100];

	////ЗАПОЛНЕНИЕ НА 1000

	//cout << "-------------------------------------------------------------------" << endl;

	//for (size_t i = 0; i < 100; ++i) {
	//	int counter = 0;
	//	
	//	clock_t begin = clock();
	//	while (counter != 1000) {
	//		timetest1000.insert(lcg());
	//		++counter;
	//	}
	//	clock_t end = clock();
	//	
	//	if (i != 99) { timetest1000.clear(); }
	//	fillattempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to fill tree with 1000 elem: " << avg(fillattempts_1000) << endl;

	////ЗАПОЛНЕНИЕ НА 10000
	//for (size_t i = 0; i < 100; ++i) {
	//	int counter = 0;
	//	
	//	clock_t begin = clock();
	//	while (counter != 10000) {
	//		timetest10000.insert(lcg());
	//		++counter;
	//	}
	//	clock_t end = clock();
	//	
	//	if (i != 99) { timetest10000.clear(); }
	//	fillattempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to fill tree with 10000 elem: " << avg(fillattempts_10000) << endl;

	////ЗАПОЛНЕНИЕ НА 100000
	//for (size_t i = 0; i < 100; ++i) {
	//	int counter = 0;
	//	
	//	clock_t begin = clock();
	//	while (counter != 100000) {
	//		timetest100000.insert(lcg());
	//		++counter;
	//	}
	//	clock_t end = clock();
	//	
	//	if (i != 99) { timetest100000.clear(); }
	//	fillattempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to fill tree with 100000 elem: " << avg(fillattempts_100000) << endl;

	//cout << "-------------------------------------------------------------------" << endl;

	////ЗАПОЛНЕНИЕ std::vector НА 1000
	//for (size_t i = 0; i < 100; ++i) {
	//	int counter = 0;
	//	
	//	clock_t begin = clock();
	//	while (counter != 1000) {
	//		filltest1000.push_back(lcg());
	//		++counter;
	//	}
	//	clock_t end = clock();
	//	
	//	if (i != 99) { filltest1000.clear(); }
	//	fill_vattempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to fill vector with 1000 elem: " << avg(fill_vattempts_1000) << endl;

	////ЗАПОЛНЕНИЕ std::vector НА 10000
	//for (size_t i = 0; i < 100; ++i) {
	//	int counter = 0;
	//	
	//	clock_t begin = clock();
	//	while (counter != 10000) {
	//		filltest10000.push_back(lcg());
	//		++counter;
	//	}
	//	clock_t end = clock();
	//	
	//	if (i != 99) { filltest10000.clear(); }
	//	fill_vattempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to fill vector with 10000 elem: " << avg(fill_vattempts_10000) << endl;

	////ЗАПОЛНЕНИЕ std::vector НА 100000
	//for (size_t i = 0; i < 100; ++i) {
	//	int counter = 0;
	//	
	//	clock_t begin = clock();
	//	while (counter != 100000) {
	//		filltest100000.push_back(lcg());
	//		++counter;
	//	}
	//	clock_t end = clock();
	//	
	//	if (i != 99) { filltest100000.clear(); }
	//	fill_vattempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to fill vector with 100000 elem: " << avg(fill_vattempts_100000) << endl;

	//cout << "-------------------------------------------------------------------" << endl;

	//double findattempts_1000[1000], findattempts_10000[1000], findattempts_100000[1000];
	////ПОИСК ЭЛЕМЕНТА В ДЕРЕВЕ 1000
	//for (size_t i = 0; i < 1000; ++i) {
	//	
	//	clock_t begin = clock();
	//	timetest1000.contains(lcg());
	//	clock_t end = clock();
	//	

	//	findattempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to find elem in tree with 1000 elem: " << avg1000(findattempts_1000) << endl;

	////ПОИСК ЭЛЕМЕНТА В ДЕРЕВЕ 10000
	//for (size_t i = 0; i < 1000; ++i) {
	//	
	//	clock_t begin = clock();
	//	timetest10000.contains(lcg());
	//	clock_t end = clock();
	//	

	//	findattempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to find elem in tree with 10000 elem: " << avg1000(findattempts_10000) << endl;

	////ПОИСК ЭЛЕМЕНТА В ДЕРЕВЕ 100000
	//for (size_t i = 0; i < 1000; ++i) {
	//	
	//	clock_t begin = clock();
	//	timetest100000.contains(lcg());
	//	clock_t end = clock();
	//	//end

	//	findattempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to find elem in tree with 100000 elem: " << avg1000(findattempts_100000) << endl;

	//cout << "-------------------------------------------------------------------" << endl;

	//double vfindattempts_1000[1000], vfindattempts_10000[1000], vfindattempts_100000[1000];
	////ПОИСК ЭЛЕМЕНТА В ВЕКТОРЕ 1000
	//for (size_t i = 0; i < 1000; ++i) {
	//	int elem = lcg();
	//	//start
	//	clock_t begin = clock();
	//	for (size_t i = 0; i < filltest1000.size(); ++i) {
	//		if (filltest1000[i] == elem) { break; }
	//	}
	//	clock_t end = clock();
	//	//end

	//	vfindattempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to find elem in std::vector with 1000 elem: " << avg1000(vfindattempts_1000) << endl;

	////ПОИСК ЭЛЕМЕНТА В ВЕКТОРЕ 10000
	//for (size_t i = 0; i < 1000; ++i) {
	//	int elem = lcg();
	//	//start
	//	clock_t begin = clock();
	//	for (size_t i = 0; i < filltest10000.size(); ++i) {
	//		if (filltest10000[i] == elem) { break; }
	//	}
	//	clock_t end = clock();
	//	//end

	//	vfindattempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to find elem in std::vector with 10000 elem: " << avg1000(vfindattempts_10000) << endl;

	////ПОИСК ЭЛЕМЕНТА В ВЕКТОРЕ 100000
	//for (size_t i = 0; i < 1000; ++i) {
	//	int elem = lcg();
	//	//start
	//	clock_t begin = clock();
	//	for (size_t i = 0; i < filltest100000.size(); ++i) {
	//		if (filltest100000[i] == elem) { break; }
	//	}
	//	clock_t end = clock();
	//	//end

	//	vfindattempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to find elem in std::vector with 100000 elem: " << avg1000(vfindattempts_100000) << endl;

	//cout << "-------------------------------------------------------------------" << endl;

	//double add_del_attempts_1000[1000], add_del_attempts_10000[1000], add_del_attempts_100000[1000];
	////ДОБАВЛЕНИЕ И УДАЛЕНИЕ В ДЕРЕВЕ 1000
	//for (size_t i = 0; i < 1000; ++i) {
	//	int elem = lcg();
	//	//start
	//	clock_t begin = clock();
	//	timetest1000.insert(elem);
	//	timetest1000.erase(elem);
	//	clock_t end = clock();
	//	//end

	//	add_del_attempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to add and delete elem in set with 1000 elem: " << avg1000(add_del_attempts_1000) << endl;

	////ДОБАВЛЕНИЕ И УДАЛЕНИЕ В ДЕРЕВЕ 10000
	//for (size_t i = 0; i < 1000; ++i) {
	//	int elem = lcg();
	//	//start
	//	clock_t begin = clock();
	//	timetest10000.insert(elem);
	//	timetest10000.erase(elem);
	//	clock_t end = clock();
	//	//end

	//	add_del_attempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to add and delete elem in set with 10000 elem: " << avg1000(add_del_attempts_10000) << endl;

	////ДОБАВЛЕНИЕ И УДАЛЕНИЕ В ДЕРЕВЕ 100000
	//for (size_t i = 0; i < 1000; ++i) {
	//	int elem = lcg();
	//	//start
	//	clock_t begin = clock();
	//	timetest100000.insert(elem);
	//	timetest1000.erase(elem);
	//	clock_t end = clock();
	//	//end

	//	add_del_attempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to add and delete elem in set with 100000 elem: " << avg1000(add_del_attempts_100000) << endl;

	//cout << "-------------------------------------------------------------------" << endl;

	//double add_del_vecattempts_1000[1000], add_del_vecattempts_10000[1000], add_del_vecattempts_100000[1000];
	////ДОБАВЛЕНИЕ И УДАЛЕНИЕ В VECTOR 1000
	//for (size_t i = 0; i < 1000; ++i) {
	//	int elem = lcg();
	//	//start
	//	clock_t begin = clock();
	//	filltest1000.push_back(elem);
	//	filltest1000.pop_back();
	//	clock_t end = clock();
	//	//end

	//	add_del_vecattempts_1000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to add and delete elem in set with 100000 elem: " << avg1000(add_del_vecattempts_1000) << endl;

	//

	////ДОБАВЛЕНИЕ И УДАЛЕНИЕ В VECTOR 10000
	//for (size_t i = 0; i < 1000; ++i) {
	//	int elem = lcg();
	//	//start
	//	clock_t begin = clock();
	//	filltest10000.push_back(elem);
	//	filltest10000.pop_back();
	//	clock_t end = clock();
	//	//end

	//	add_del_vecattempts_10000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to add and delete elem in set with 100000 elem: " << avg1000(add_del_vecattempts_10000) << endl;

	//

	////ДОБАВЛЕНИЕ И УДАЛЕНИЕ В VECTOR 100000
	//for (size_t i = 0; i < 1000; ++i) {
	//	int elem = lcg();
	//	//start
	//	clock_t begin = clock();
	//	filltest100000.push_back(elem);
	//	filltest100000.pop_back();
	//	clock_t end = clock();
	//	//end

	//	add_del_vecattempts_100000[i] = double(end - begin) / double(CLOCKS_PER_SEC);
	//}
	//cout << "Average time to add and delete elem in set with 100000 elem: " << avg1000(add_del_vecattempts_100000) << endl;

	//cout << "-------------------------------------------------------------------" << endl;

	return 0;
}




  