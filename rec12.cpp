// Nathanael Leyton
// Rec12

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
    friend ostream& operator<<(ostream& os, const List& rhs){
        Node* node = rhs.header->next;
        while (node->next != nullptr){
            os << node->data << ' ';
            node = node->next;
        }
        return os;
    }
private:
    struct Node{
        Node(int data = 0, Node* next = nullptr, Node* prior = nullptr) : data(data), next(next), prior(prior) {}
        int data;
        Node* next;
        Node* prior;
    };
    Node* header;
    Node* trailer;
    int theSize = 0;
public:
    class Iterator {
        friend List;
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return lhs.index != rhs.index; }
    public:
        Iterator(Node* idx) : index(idx) {}
        Iterator& operator++() {
            index = index->next;
            return *this;
        }
        Iterator& operator--() {
            index = index->prior;
            return *this;
        }
        int& operator*() { return index->data; }
    private:
        Node* index;
    };

    List() {
        header = new Node(0);
        trailer = new Node(0);
        header->next = trailer;
        trailer->prior = header;
    }
    List(const List& rhs);
    List& operator=(const List& rhs);
    
    // Task 1:
    void push_back(int data) {
        Node* newNode = new Node(data);
        Node* oldPrior = trailer->prior;
        oldPrior->next = newNode;
        newNode->prior = oldPrior;
        trailer->prior = newNode;
        newNode->next = trailer;
        ++theSize;
    }
    Node* pop_back() {
        Node* back = trailer->prior;
        Node* newPrior = trailer->prior->prior;
        delete trailer->prior;
        trailer->prior = newPrior;
        newPrior->next = trailer;
        --theSize;
        return back;
    }
    int front() { return header->next->data; }
    int back() { return trailer->prior->data; }
    int size() const { return theSize; }
    // Task 2:
    void push_front(int data) {
        Node* newNode = new Node(data);
        Node* oldNext = header->next;
        header->next = newNode;
        newNode->prior = header;
        newNode->next = oldNext;
        oldNext->prior = newNode;
        ++theSize;
    }
    Node* pop_front() {
        Node* front = header->next;
        Node* newNext = header->next->next;
        delete header->next;
        header->next = newNext;
        newNext->prior = header;
        --theSize;
        return front;
    }
    // Task 3:
    void clear() {
        Node* ptr = header->next;
        while (ptr != trailer){
            delete ptr;
            ptr = ptr->next;
        }
        header->next = trailer;
        trailer->prior = header;
        theSize = 0;
    }
    // Task 4:
    int& operator[](size_t index) {
        Node* cursor = header->next;
        int count = 0;
        while (count != index){
            cursor = cursor->next;
            ++count;
        }
        return cursor->data;
    }
    int operator[](size_t index) const {
        const Node* cursor = header->next;
        int count = 0;
        while (count != index){
            cursor = cursor->next;
            ++count;
        }
        return cursor->data;
    }
    // Task 5:
    Iterator begin() { return Iterator(header->next); }
    Iterator end() { return Iterator(trailer); }
    // Task 6:
    Iterator insert(Iterator iter, int data){
        Node* newNode = new Node(data);
        Node* iterNode = iter.index;
        Node* iterNodePrior = iter.index->prior;
        iterNode->prior = newNode;
        iterNodePrior->next = newNode;
        newNode->next = iterNode;
        newNode->prior = iterNodePrior;
        ++theSize;
        return ++iter;
    }
    // Task 7:
    Iterator erase(Iterator iter){
        Node* iterNode = iter.index;
        Node* iterPrior = iter.index->prior;
        Node* iterNext = iter.index->next;
        delete iterNode;
        iterPrior->next = iterNext;
        iterNext->prior = iterPrior;
        --theSize;
        return ++iter;
    }
};

void printListInfo(List& myList) {
    cout << "size: " << myList.size()
    << ", front: " << myList.front()
    << ", back(): " << myList.back()
    << ", list: " << myList << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}

int main() {
    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";
    
    // Task2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";
    
    // Task3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";
    // Task4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
    << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

//    // Task 8
//    cout << "\n------Task Eight------\n";
//    cout << "Copy control\n";
//    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
//    myList.clear();
//    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
//    printListInfo(myList);
//    cout << "Calling doNothing(myList)\n";
//    doNothing(myList);
//    cout << "Back from doNothing(myList)\n";
//    printListInfo(myList);
//
//    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
//    List listTwo;
//    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
//    printListInfo(listTwo);
//    cout << "listTwo = myList\n";
//    listTwo = myList;
//    cout << "myList: ";
//    printListInfo(myList);
//    cout << "listTwo: ";
//    printListInfo(listTwo);
//    cout << "===================\n";
}
