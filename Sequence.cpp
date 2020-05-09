#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

template <typename T>
struct node
{
  T field;
  struct node *next;
  struct node *prev;
};

struct student
{
    char name[20];
    char lastname[20];
    char group[8];
    student *next= NULL;
};

template <typename T> class HashTable {
public:
    student *h[541]={NULL};

    void add(student element)
    {
        int hashes[3], result=0;
        hashes[0]=abs(hash(element.lastname));
        hashes[1]=abs(hash(element.name));
        hashes[2]=abs(hash(element.group));
        for (int i=0; i<3; i++)
        {
            result+=hashes[i];
        }
        result= result % 541;
        student *temp= h[result];
        if (h[result]==NULL)
        {
            temp=new student;
            strcpy(temp->lastname,element.lastname);
            strcpy(temp->name,element.name);
            strcpy(temp->group,element.group);
            h[result]=temp;
            temp->next=NULL;
        }
        else
        {
            while (temp->next!=NULL)
                temp=temp->next;
            temp->next= new student;
            temp=temp->next;
            strcpy(temp->lastname,element.lastname);
            strcpy(temp->name,element.name);
            strcpy(temp->group,element.group);
        }
    }

    int hash(char s[20])
    {
        int a=0;
		for(int i=0; i<strlen(s); i++)
			a+=s[i];
		return a % 541;
	}

    void printHashTable()
    {
        student *temp;
		int i;
		cout << "Фамилия Имя Группа\n";
		for(i=0;i<541;++i){
			temp=h[i];
			while(temp!=NULL){
				cout << temp->lastname << temp->name << temp->group << endl;
				temp=temp->next;}
			}
    }
    };


template <typename T> class Tree {
public:
    struct Leaf {
        T element;
        int index = 0;
        Leaf *Left = NULL;
        Leaf *Right = NULL;
    };
    int size;
    Leaf *root;
    Tree() : root(NULL), size(0){}
    void add(T elem, int index) {
        Leaf *leaf = new Leaf;
        leaf->element = elem;
        leaf->index = index;
        size++;
        Leaf *p = root;
        if (p == NULL) {
            this->root = leaf;
            return;
        }
        else {
            Leaf *n = root;
            while (n){
                p = n;
                if (elem < p->element)
                    n = p->Left;
                else if (elem > p->element)
                    n = p->Right;
                else
                    break;
            }
            if (elem < p->element)
                p->Left = leaf;
            else
                p->Right = leaf;
        }

    }
    int find(T elem) {

        Leaf *p = this->root;

        while (p){
            if (p->element > elem) {
                p = p->Left;
            }
            else if (p->element < elem) {
                p = p->Right;
            }
            else {
                return p->index;
            }
        }
        cout << "Not found..." << endl;
    }

void inorder(Leaf* p, int deep)
{
	if (p){
		for (int i = 0; i <= deep; i++)
			cout << "--";
		cout << p->element << endl;
		inorder(p->Left, deep + 1);
		inorder(p->Right, deep + 1);

	}
	else{
		for (int i = 0; i <= deep; i++)
			cout << "--";
		cout << "NULL" << endl;
	}
}
};

template <typename T>
    class Sequence
{
public:
    Tree<T> *tree;
    HashTable<T> *hashTable;
    Sequence(){
        tree = new Tree<T>;
        hashTable = new HashTable<T>;
    };
    virtual int getLength() {} ;
    virtual int getIsEmpty() {};
    virtual void setN(int a) {};
    virtual void init() {}
    virtual void print() {}
    virtual T Get(int index) {}
    virtual T GetFirst() {}
    virtual T GetLast() {}
    virtual void Append(T elem) {}
    virtual void Prepend (T elem) {}
    virtual void InsertAt(int index, T elem) {}
    virtual void Remove (T elem) {}
    virtual Sequence <T> *GetSubsequence(int startIndex, int endIndex) {}
    virtual T binarySearch(T elem) = 0;
    virtual T binaryTreeSearch(T elem) = 0;
    virtual void InitHashTable() {}

};

 template <typename T> class ArraySequence : public  Sequence<T>
{
public:
    int N;
    T *arr;
void setarr(T *A)
{
    arr=A;
}

void setN(int n)
{
    N=n;
}

void init()
{
    for (int i=0; i<N; i++)
    {
        T elem;
        cin >> elem;
        *(arr+i)=elem;
    }
}

void print()
{
    cout << "Текущий массив" << endl;
    for (int i=0; i<N; i++)
    {
        cout << arr[i] << endl;//cout << *(arr+i) << endl;
    }
}

int getLength()
{
    return N ;
}

int getIsEmpty()
{
    if (N==0) {return 1;} else {return 0;}
}

/*void RandInit()
{
    N=10;
    arr=(T*)realloc(arr,sizeof(T)*(N+1));
    for (int i=0; i<10; i++)
    {
        arr[i]=rand()%1000;
    }
}*/

T Get (int index)
{
    if (index >= N || index < 0) return 404;
    else
    return *(arr+index);
}

T GetFirst ()
{
    return *(arr);
}
T GetLast ()
{
    return *(arr+ N - 1);
}

void Append (T elem)
{
    arr=(T*)realloc(arr,sizeof(T)*(N+1));
    *(arr+N) = elem;
    N++;
}

void Prepend (T elem)
{
    int i;
    arr=(T*)realloc(arr,sizeof(T)*(N+1));
    T elem1;
         for(i=N+1;i>0;--i)
        *(arr+i)=*(arr+i-1);
    *(arr)=elem;
    N++;
}


void InsertAt (int index, T elem)
{
     int i;
     if (index==0) Prepend(elem);
     if (index==N) Append (elem);
     if ((index!=0) && (index!=N))
     {
        arr=(T*)realloc(arr,sizeof(T)*(N+1));
        for(i=N+1;i>index;--i)
          *(arr+i)=*(arr+i-1);
          *(arr+index)=elem;
       N++;
     }

}

void Remove (T elem)
{
    int i, j;
    for (i=0; i<N; i++)
    {
        if ( *(arr+i) == elem)
        {
            for (j=i; j<N; j++)
            *(arr+j)=*(arr+j+1);
            arr=(T*)realloc(arr,sizeof(T)*(N-1));
            N--;
            i--;
        }
    }
}

ArraySequence<T> *GetSubsequence(int i, int j){
    int k;
    ArraySequence <T> B;///создаем и инициалиализируем последовательность, в которую будем заносить подпоследовательность
    B.setN((j-i)/2);
    T *b;
    b=new T [(j-i)/2];
    B.setarr(b);
    for(k=i;k<=j;k++)
        B.Append(*(arr+k));
    return &B;
}

void *copymas(T *b){
    for (int i=0; i<N; i++)
    {
        b[i]=arr[i];
    }
    return(b);
}
void bubbleSort(T *b, int n)
{
    T temp = 0;
    bool exit = false;
    while (!exit)
    {
    exit = true;
    for (int i = 0; i < (N - 1); i++)
        if (b[i] > b[i + 1])
        {
        temp = b[i];
        b[i] = b[i + 1];
        b[i + 1] = temp;
        exit = false;
        }
    }
}

void QuickSort(){
  quickSort(arr,0,N-1);
}
void quickSort(T *arr, int left, int right) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];

      /* partition */
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };

      /* recursion */
      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}

void shellSort(int n, int mass[])
{
    int i, j, step;
    int tmp;
    for (step = n / 2; step > 0; step /= 2)
        for (i = step; i < n; i++)
        {
            tmp = mass[i];
            for (j = i; j >= step; j -= step)
            {
                if (tmp < mass[j - step])
                    mass[j] = mass[j - step];
                else
                    break;
            }
            mass[j] = tmp;
        }
}

void ShellSort()
{
    shellSort(N, arr);
}

T binarySearch(T elem)  {
        int m;
        int index1 = 0, index2 = N-1;
        ShellSort();
        while (true){
            if (index1 > index2) {
                cout << "Элемент не найден" << endl;
                return -1;
            }
            m = index1 + (index2 - index1) / 2;
            if (Get(m) < elem) index1 = m+1;
            if (Get(m) > elem) index2 = m-1;
            if (Get(m) == elem) {
                break;
            }
        }
        return m;
    }

T binaryTreeSearch(T elem)  {
        //clock_t t;
        //t = clock();
        for (int i = 0; i < N; ++i) {
            this->tree->add(Get(i), i); ///превращаем массив в дерево
        }
        //this->tree->inorder(this->tree->root, 0);
        //cout << "Индекс элемента в дереве:" << this->tree->find(elem) << endl;
        //t = clock() - t;
        //printf ("Searching time is... (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
        //cout << "Время поиска: " << t/CLOCKS_PER_SEC << endl;
        return this->tree->find(elem);
    }

/*void InitHashTable()
{
    this->hashTable->GetM(getLength());
    this->hashTable->init(arr);
    //this->hashTable->printHashTable();
}*/

void PrintHashTable()
{
    this->hashTable->printHashTable();
}

void AddToHashTable(student elem)
{
    this->hashTable->add(elem);
}

};

 template <typename T> class ListSequence : public  Sequence<T>
 {
 public:
     int N;
    // node <T> *fst = new node <T>;
    node <T> *fst;
    node <T> *lst;
     ListSequence()
     {
         fst=new node <T>;
        // fst->ptr= NULL;
         fst->next= NULL;
         fst->prev= NULL;
         lst=new node <T>;
         lst->next= NULL;
         lst->prev= NULL;
     }

void setN(int n)
{
    N=n;
}

void  init()
{
    int i;
    T elem;
    node <T> *temp=fst;
    for (i=0; i<N; i++)
        {
            cin >> elem;
            node <T> *temp1, *p;
            temp->field = elem; // записываем данные в текущий узел
            if (i==N-2) lst->prev=temp;
            if (i!=N-1){
            p= new node <T>;
            p->next= NULL; // новому элементу присваиваем значение указателя предыдущего
            p->prev= temp;
            temp->next=p; // текущий указывает на только что созданный
           // lst->prev=temp;
            temp = p; // текущим становится только что созданный
            }
        }
        lst->field=temp->field;
        lst->next=NULL;
}

void print()
{
    cout << "Текущий список" << endl;
    node <T> *temp=fst;
    //while (temp->next!=NULL)
    for (int i=0; i<N; i++)
    {
        cout << temp->field << endl;
        temp=temp->next;
    }
}

int getLength()
{
    return N ;
}

int getIsEmpty()
{
    if (N==0) {return 1;} else {return 0;}
}

T Get (int index)
{
    if (index > N || index < 0) return 404;
    else
    {
    node <T> *temp=fst;
    int i;
    for (i=0; i<index; i++)
        temp=temp->next;
    return (temp->field);
    }
}

T GetFirst ()
{
    return fst->field;
}

T GetLast ()
{
    node <T> *temp=fst;
    int i;
    for (i=0; i<N-1; i++)
        temp=temp->next;
    return (temp->field);
}

void Prepend(T elem)
{
    int i;
    node <T> *temp=new node <T>;
    temp->next=fst;
    temp->field=elem;
    fst=temp;
    N++;
}

void Append(T elem){
        struct node<T> *temp=fst;
        if(N==0)Prepend(elem); else{
        for (int i=0; i<N-1; i++)
        temp=temp->next;
        node<T> *temp1=new node <T>;
        temp->next=temp1;
        temp1->field=elem;
        temp1->next=NULL;
        N++;
        }
}


void InsertAt(int index, T elem)
{
    node <T> *temp=fst;
    node <T> *temp1; //
    node <T> *temp2= new node <T>;
    int i;
    if (index == 0) Prepend(elem);
    if (index==N) Append(elem);
    if (index!=0 && index!=N)
    {
        for (i=0;i<index-1;i++)
        {
            temp=temp->next;
        }
        temp1 = temp->next;
        temp->next = temp2;
        temp2->field = elem;
        temp2->next= temp1;
    N++;
    }
}

void Remove(T elem)
{
    node <T> *temp=fst;
    node <T> *temp1;
    while (temp->next!=NULL){
    if(temp->next->field==elem){
        temp1=temp->next;
        temp->next=temp->next->next;
        delete temp1;
        N--;
    }
    temp=temp->next;
    }
}

void bubbleSort()
{
    //T temp = 0;
    node <T> *temp = fst;
    bool exit = false;
    while (!exit)
    {
    exit = true;
    for (int i = 0; i < (N - 1); i++)
    {
        if (temp->field > temp->next->field)
        {
            node <T> *temp1= new node <T>;
            temp1->field = temp->field;
            temp->field = temp->next->field;
            temp->next->field = temp1->field;
           // temp=temp->next;
            exit=false;
        }
        temp=temp->next;
    }
    temp=fst;
    }

}

struct node<T> *getTail(struct node<T> *cur)
{
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

void CopyList(node <T> *temp)
{
    node <T> *temp1=fst;
    for (int i=0; i<N; i++)
    {
        temp->field=temp1->field;
        node <T> *temp2 = new node <T>;
        temp->next=temp2;
        temp2->prev=temp;
        temp=temp->next;
        temp1=temp1->next;
    }
}

struct node<T> *partition(struct node<T> *head, struct node<T> *end,
                       struct node<T> **newHead, struct node<T> **newEnd)
{
    struct node<T> *pivot = end;
    struct node<T> *prev = NULL, *cur = head, *tail = pivot;

    // During partition, both the head and end of the list might change
    // which is updated in the newHead and newEnd variables
    while (cur != pivot)
    {
        if (cur->field < pivot->field)
        {
            // First node that has a value less than the pivot - becomes
            // the new head
            if ((*newHead) == NULL)
                (*newHead) = cur;

            prev = cur;
            cur = cur->next;
        }
        else // If cur node is greater than pivot
        {
            // Move cur node to next of tail, and change tail
            if (prev)
                prev->next = cur->next;
            struct node<T> *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    // If the pivot data is the smallest element in the current list,
    // pivot becomes the head
    if ((*newHead) == NULL)
        (*newHead) = pivot;

    // Update newEnd to the current last node
    (*newEnd) = tail;

    // Return the pivot node
    return pivot;
}


//here the sorting happens exclusive of the end node
struct node<T> *quickSortRecur(struct node<T> *head, struct node<T> *end)
{
    // base condition
    if (!head || head == end)
        return head;

    struct node<T> *newHead = NULL, *newEnd = NULL;

    // Partition the list, newHead and newEnd will be updated
    // by the partition function
    struct node<T> *pivot = partition(head, end, &newHead, &newEnd);

    // If pivot is the smallest element - no need to recur for
    // the left part.
    if (newHead != pivot)
    {
        // Set the node before the pivot node as NULL
        struct node<T> *tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;

        // Recur for the list before pivot
        newHead = quickSortRecur(newHead, tmp);

        // Change next of last node of the left half to pivot
        tmp = getTail(newHead);
        tmp->next =  pivot;
    }

    // Recur for the list after the pivot element
    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

// The main function for quick sort. This is a wrapper over recursive
// function quickSortRecur()
void QuickSort()
{
    struct node<T> **headRef=&fst;
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
    return;
}

void InsertionSort()
{
    insertionSort(&fst);
}

void insertionSort(struct node<T> **head_ref)
{
    struct node <T> *sorted = NULL;
    struct node <T> *current = *head_ref;
    while (current != NULL)
    {

         struct node <T> *nexti = current->next;

        sortedInsert(&sorted, current);

        current = nexti;
    }

    *head_ref = sorted;
}

void sortedInsert(struct node<T>** head_ref, struct node<T>* new_node)
{
    struct node<T>* current;
    /* Special case for the head end */
    if (*head_ref == NULL || (*head_ref)->field >= new_node->field)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        current = *head_ref;
        while (current->next!=NULL &&
               current->next->field < new_node->field)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

T binarySearch(T elem) {
        int m;
        int index1 = 0, index2 = N-1;
        InsertionSort();
        while (true){
            if (index1 > index2) {
                cout << "Элемент не найден " << endl;
                return -1;
            }
            m = index1 + (index2 - index1) / 2;
            if (Get(m) < elem) index1 = m+1;
            if (Get(m) > elem) index2 = m-1;
            if (Get(m) == elem) {
                break;
            }
        }
        return m;
}

T binaryTreeSearch(T elem)  {
        clock_t t;
        t = clock();
        for (int i = 0; i < N; ++i) {
            this->tree->add(Get(i), i); ///превращаем массив в дерево
        }
        //this->tree->inorder(this->tree->root, 0);
        //cout << "Индекс элемента в дереве:" << this->tree->find(elem) << endl;
        //t = clock() - t;
        //printf ("Searching time is... (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
        //cout << "Время поиска: " << t/CLOCKS_PER_SEC << endl;
        return this->tree->find(elem);
    }


 };


void menu2()
{
    cout << "1- показать хэш таблицу" << endl;
    cout << "2- добавить элемент в хэш таблицу" << endl;
}

void menu()
{
    cout << "Введите 1 для того, чтобы узнать сколько элементов в последоватеьности" << endl;
    cout << "2- узнать, пуста ли последовательность" << endl;
    cout << "3- показать элемент с желаемым индексом" << endl;
    cout << "4- показать первый элемент последовательности " << endl;
    cout << "5 -показать последний элемент последовательности " << endl;
    cout << "6- добавить элемент в конец последовательности" << endl;
    cout << "7- добавить элемент в начало последовательности" << endl;
    cout << "8- добавить элемент в нужную позицию" << endl;
    cout << "9- удалить элемент из последовательности" << endl;
    cout << "10- извлечь подпоследовательность" << endl;
    cout << "11- показать последовательность" << endl;
    cout << "12- сортировка пузырьком" << endl;
    cout << "13- быстрая сортировка" << endl;
    cout << "14- сортировка Шелла" << endl;
    cout << "15- бинарный поиск по отсортированной последовательности" << endl;
    cout << "16- поиск по бинарному дереву поиска" << endl;
    cout << "17- работа с хэш- таблицей" << endl;
}

template<typename T>
Test(Sequence <T> *a)
{
    a->setN(0);
    if ((a->getLength() )==0) cout << "Test1:  OK"<<endl;
    else cout << "GetLengt:Error";
    a->Append(23);
    if (a->getLength()==1) cout << "Test2:  OK" <<endl ; else cout << "Test2:Error"<<endl;
    if (a->GetFirst()==23) cout << "Test3:  OK"<<endl ; else cout << "Test3:Error"<<endl;
    if (a->GetLast()==23) cout << "Test4:  OK" <<endl; else cout << "Test4:Error"<<endl;
    if (a->Get(0)==23) cout << "Test5:  OK" <<endl; else cout << "Test5:Error"<<endl;
    cout << (a->Get(-1)) << " Error" <<endl; cout << (a->Get(-1))<< " Error" <<endl;
    a->Append(43);
    if (a->getLength()==2) cout << "Test6:  OK" <<endl ; else cout << "Test6:Error"<<endl;
    if (a->GetFirst()==23) cout << "Test7:  OK"<<endl ; else cout << "Test7:Error"<<endl;
    if (a->GetLast()==43) cout << "Test8:  OK" <<endl; else cout << "Test8:Error"<<endl;
    if (a->Get(0)==23) cout << "Test9:  OK" <<endl; else cout << "Test9:Error"<<endl;
    if (a->Get(1)==43) cout << "Test10: OK" <<endl; else cout << "Test10:Error"<<endl;
    a->Prepend(53);
    if (a->getLength()==3) cout << "Test11: OK" <<endl ; else cout << "Test11:Error"<<endl;
    if (a->GetFirst()==53) cout << "Test12: OK"<<endl ; else cout << "Test12:Error"<<endl;
    if (a->Get(0)==53) cout << "Test13: OK" <<endl; else cout << "Test13:Error"<<endl;
    if (a->Get(1)==23) cout << "Test14: OK" <<endl; else cout << "Test14:Error"<<endl;
}

template<typename T>
TestBubbleSort(Sequence <T> *a)
{
    if ( a->Get(0)==2 && a->Get(1)==3 && a->Get(2)==4 && a->Get(3)==5 && a->Get(4)==6 )
        cout << "BubbleSort: OK" << endl;
    else cout << "BubbleSort: Error" << endl;
}

template<typename T>
TestQuickSort(Sequence <T> *a)
{
    if ( a->Get(0)==2 && a->Get(1)==3 && a->Get(2)==4 && a->Get(3)==5 && a->Get(4)==6 )
        cout << "QuickSort: OK" << endl;
    else cout << "QuickSort: Error" << endl;
}

template<typename T>
TestShellSort(Sequence <T> *a)
{
    if ( a->Get(0)==2 && a->Get(1)==3 && a->Get(2)==4 && a->Get(3)==5 && a->Get(4)==6 )
        cout << "ShellSort: OK" << endl;
    else cout << "ShellSort: Error" << endl;
}

template<typename T>
TestInsertionSort(Sequence <T> *a)
{
    if ( a->Get(0)==2 && a->Get(1)==3 && a->Get(2)==4 && a->Get(3)==5 && a->Get(4)==6 )
        cout << "InsertionSort: OK" << endl;
    else cout << "InsertionSort: Error" << endl;
}

template<typename T>
TestbinaryTreeSearch(Sequence <T> *a)
{
    if (a->binaryTreeSearch(5)==0 && a->binaryTreeSearch(1)==1 && a->binaryTreeSearch(4)==2 && a->binaryTreeSearch(2)==3 && a->binaryTreeSearch(3)==4 && a->binaryTreeSearch(6)==5)
        cout << "binaryTreeSearch: Ok" << endl;
        else cout << "binaryTreeSearch: Error" << endl;
}

template<typename T>
TestBinarySearch(Sequence <T> *a)
{
    if ( a->binarySearch(2)==0 && a->binarySearch(3)==1 && a->binarySearch(4)==2 && a->binarySearch(5)==3 && a->binarySearch(6)==4 )
        cout << "BinarySearch: OK" << endl;
    else cout << "BinarySearch: Error" << endl;
}



int main()
{
    setlocale(0,"Russian");
    int c, index,n, k;
    cout << "Введите 1 для работы с массивом, 2 для работы со списком, 3 для тестирования программы" << endl;
    cin >> c;
    ArraySequence <int> A;
   // ListSequence <int> B;
    switch(c)
    {
    case 1:
    {
         cout << "Введите количество элементов масисива, а затем введите элементы" << endl;
         int n;
         cin >> n;
         A.setN(n);
         int *a;
         a=new int [n];
         A.setarr(a);
         A.init();
        do
        {
         menu();
         cin >> c;
         switch(c)
         {
         case 1: {cout << A.getLength() <<" - количество элементов в массиве" << endl; break;}
         case 2: {cout << A.getIsEmpty() << endl; break;}
         case 3: {
             int index;
             cout << "Введите индекс" << endl;
             cin >> index;
            // if ((index> n) or (index < 0))
             //   cout <<"Ошибка! Слишком большой индекс" << endl;
            // else
            // {
                cout << "Элемент с индексом "<< index << "=" <<A.Get(index)  << endl;
                break;
             //}
         }
         case 4: {cout << A.GetFirst() << " - первый элемент последовательности" << endl; break;}
         case 5: {cout << A.GetLast() << "virtual int binarySearch(T elem) = 0; - последний элемент последовательности" << endl; break;}
         case 6: {
            int elem;
            cout << "Введите элемент" << endl;
            cin >> elem;
            A.Append(elem);
            break;
        }
         case 7: {
            int elem;
            cout << "Введите элемент" << endl;
            cin >> elem;
            A.Prepend(elem);
            break;
         }
         case 8:
         {
             int index;
             cout << "Введите индекс";
             cin >> index;
             if (index>n)
                 cout <<"Ошибка! Слишком большой индекс";
             else {
                int elem;
                int i;
                cout << "Введите элемент" << endl;
                cin >> elem;
                A.InsertAt(index, elem);
             }
             break;
         }
         case 9: {
            int elem;
            cout << "Введите элемент" << endl;
            cin >> elem;
            A.Remove(elem);
            break;
         }
         case 10:
         {
            int i, j;
            cout << "Введите начальный и конечный индексы" << endl;
            cin >> i >> j;
            //ArraySequence <int> *C;
           // C->setN(j-i+1);
           // int *b;
           // b=new int [j-i+1];
            //C->setarr(b);
            A.GetSubsequence(i, j)->print();
          //  C->print();
            break;
         }
         case 11: {A.print(); break;}
         case 12:
         {
            unsigned int start_time =  clock();
            A.bubbleSort(a, n);
            unsigned int end_time = clock(); // конечное время
            unsigned int search_time = end_time - start_time; // искомое время
            A.print();
            cout << "Время работы: " << search_time/1000 << endl;
            break;
         }
         case 13:
         {
             unsigned int start_time =  clock();
             A.QuickSort();
             unsigned int end_time = clock(); // конечное время
             unsigned int search_time = end_time - start_time; // искомое время
             A.print();
             cout << "Время работы: " << search_time/1000 << endl;
             break;
         }
         case 14:
            {
                A.ShellSort();
                A.print();
                break;
            }
         case 15:
            {
                int elem, k;
                cout << "Какой элемент будем искать?" << endl;
                cin >> elem;
                clock_t t;
                t = clock();
                k = A.binarySearch(elem);
                if (k!=-1 )
                cout << "Индекс этого элемента в отсортированной полседоватлеьности: " << k << endl;
                t = clock() - t;
                cout << "Время поиска: " << t/CLOCKS_PER_SEC << endl;
                break;
            }
         case 16:
            {
                int elem;
                cout << "Какой элемент будем искать?" << endl;
                cin >> elem;
                cout << "Индекс элемента в бинарном дерееве: " << A.binaryTreeSearch(elem) << endl;
                break;
            }
         case 17:
            {
               // A.InitHashTable();
                int z;
                do
                {
                    menu2();
                    cin >> z;
                    switch (z)
                    {
                    case 1:
                        {
                            A.PrintHashTable();
                            break;
                        }
                    case 2:
                        {
                            char name[20];
                            char lastname[20];
                            char group[8];
                            student elem;
                            cout << "Введите фамилию, имя и группу" << endl;
                            cin >> elem.lastname;
                            cin >> elem.name;
                            cin >> elem.group;
                            A.AddToHashTable(elem);
                            break;
                        }
                    }
                } while (z!=0);
            }
         break;
         }
        } while(c!=0);
    break;
    }
     case 2:
    {
        cout << "Введите количество элементов списка, а затем введите элементы" << endl;
        ListSequence <int> A;
        int n;
        cin >> n;
        A.setN(n);
        A.init();
        do
        {
         menu();
         cin >> c;
         switch(c)
         {
         case 1: {cout << A.getLength() <<" - количество элементов в списке" << endl; break;}
         case 2: {cout << A.getIsEmpty() << endl; break;}
         case 3: {
             int index;
             cout << "Введите индекс" << endl;
             cin >> index;
             if ((index> n) or (index < 0))
                cout <<"Ошибка! Слишком большой индекс" << endl;
             else
             {
                cout << "Элемент с индексом "<< index << "=" <<A.Get(index)  << endl;
             }
             break;
             }
         case 4: {cout << A.GetFirst() << " - первый элемент последовательности" << endl; break;}
         case 5: {cout << A.GetLast() << " - последний элемент последовательности" << endl; break;}
         case 6: {
            int elem;
            cout << "Введите элемент "<< endl;
            cin >> elem;
            A.Append(elem);
            break;
         }
         case 7: {
            int elem;
            cout << "Введите элемент "<< endl;
            cin >> elem;
            A.Prepend(elem);
            break;
         }
         case 8:
         {
             int index;
            cout << "На какую позицию будем засовывать элемент?" << endl;
             cin >> index;
             if (index>n)
                 cout <<"Ошибка! Слишком большой индекс";
             else {
             cout << "Введите элемент";
             int elem;
             cin >> elem;
             A.InsertAt(index, elem);
             }
             break;
         }
         case 9: {
             int elem;
             cout << "Какие элементы будем удалять?" << endl;
             cin >> elem;
             A.Remove(elem);
             break;
         }
         case 10:
         {
            int i, j;
            cout << "Введите начальный и конечный индексы" << endl;
            cin >> i >> j;
            A.GetSubsequence(i, j);
            break;
         }
         case 11: {A.print(); break;}

         case 12:
        {
            A.bubbleSort();
            A.print();
            break;
        }
         case 13:
        {
            A.QuickSort();
            A.print();
            break;
        }
         case 14:
         {
             A.InsertionSort();
             A.print();
             break;
         }
         case 15:
        {
            int elem, k;
            cout << "Какой элемент будем искать?" << endl;
            cin >> elem;
            clock_t t;
            t = clock();
            k = A.binarySearch(elem);
            if (k!=-1 )
            cout << "Индекс этого элемента в отсортированной полседоватлеьности: " << k << endl;
            t = clock() - t;
            cout << "Время поиска: " << t/CLOCKS_PER_SEC << endl;
            break;
        }
        case 16:
            {
                int elem;
                cout << "Какой элемент будем искать?" << endl;
                cin >> elem;
                cout << "Индекс элемента в бинарном дерееве: " << A.binaryTreeSearch(elem) << endl;
            }
         }
         }while(c!=0);

         break;
   }
   case 3:
    {
        ArraySequence <int> A;
        int *a;
        a=new int [0];
        A.setarr(a);
        ListSequence <int> B;
        A.setN(0);
        cout <<"Для массива"<< endl;
        Test(&A);
        cout << endl;
        cout << "Для списка" << endl;
        Test(&B);

        ArraySequence <int> C;
        int *c;
        c=new int [5];
        C.setN(5);
        C.setarr(c);
        c[0]=4; c[1]=3; c[2]=5; c[3]=2; c[4]=6;
        C.bubbleSort(c, n);
        cout <<"Для массива"<< endl;
        TestBubbleSort(&C);

        ArraySequence <int> F;
        int *f;
        f=new int [5];
        F.setN(5);
        F.setarr(f);
        f[0]=4; f[1]=3; f[2]=5; f[3]=2; f[4]=6;
        F.QuickSort();
        TestQuickSort(&F);

        ArraySequence <int> G;
        int *g;
        g=new int [5];
        G.setN(5);
        G.setarr(g);
        g[0]=4; g[1]=3; g[2]=5; g[3]=2; g[4]=6;
        G.ShellSort();
        TestShellSort(&G);
        TestBinarySearch(&G);

        ArraySequence <int> M;
        int *m;
        m=new int [6];
        M.setN(6);
        M.setarr(m);
        m[0]=5; m[1]=1; m[2]=4; m[3]=2; m[4]=3; m[5]=6;
        TestbinaryTreeSearch(&M);

        ListSequence <int> D;
        D.setN(0);
        D.Prepend(6); D.Prepend(2); D.Prepend(5); D.Prepend(3); D.Prepend(4);
        cout << "Для списка" << endl;
        D.bubbleSort();
        TestBubbleSort(&D);

        ListSequence <int> E;
        E.setN(0);
        E.Prepend(6); E.Prepend(2); E.Prepend(5); E.Prepend(3); E.Prepend(4);
        E.QuickSort();
        TestQuickSort(&E);

        ListSequence <int> H;
        H.setN(0);
        H.Prepend(6); H.Prepend(2); H.Prepend(5); H.Prepend(3); H.Prepend(4);
        H.InsertionSort();
        TestInsertionSort(&H);
        TestBinarySearch(&H);

        ListSequence <int> X;
        X.setN(0);
        X.Prepend(6); X.Prepend(3); X.Prepend(2); X.Prepend(4); X.Prepend(1);  X.Prepend(5);
        TestbinaryTreeSearch(&X);

        break;
    }
   }

   return 0;
}
