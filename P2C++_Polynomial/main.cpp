#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class ListNode{
public:
    double coef;
    int exp;
    ListNode* next;
    char prefixChar = '+';
    ListNode(double coef, int exp){
        this->coef = coef;
        this->exp = exp;
        this->next = nullptr;
    }

    ListNode(double coef, int exp, char prefixChar){
        this->prefixChar = prefixChar;
        if(prefixChar=='+'){
            this->coef = coef;
            this->exp = exp;
            this->next = nullptr;
        }
        if(prefixChar=='-'){
            this->coef = -coef;
            this->exp = exp;
            this->next = nullptr;
        }
    }

    void printFirstTerm(){
        if(this->coef==0) return;
        if(exp==0){
             cout << coef;
        }else{
            if(coef > 0){
                 cout << coef;
            }else{
                coef == -1 ? cout << "-" : cout << coef;
                //cout << coef;
            }
            exp == 1 ? cout << "x" : cout << "x^" << exp;
        }
    }
    void printFirstTerm(ofstream& outFile){
        if(this->coef==0) return;
        if(exp==0){
            outFile << coef;
        }else{
            if(coef > 0){
                outFile << coef;
            }else{
                coef == -1 ? outFile << "-" : outFile << coef;
                //cout << coef;
            }
            exp == 1 ? outFile << "x" : outFile << "x^" << exp;
        }
    }

    void printNode(){
         if(this->coef==0) return;
         if(exp==0){
             coef > 0 ? cout << prefixChar << coef : cout << coef;
         }else{
             if(coef > 0){
                 coef == 1 ? cout << prefixChar : cout << prefixChar << coef;
             }else{
                 coef == -1 ? cout << "-" : cout << coef;
                 //cout << coef;
             }
             exp == 1 ? cout << "x" : cout << "x^" << exp;
         }
    }
    void printNode(ofstream& outFile){
        if(this->coef==0) return;
        if(exp==0){
            coef > 0 ? outFile << prefixChar << coef : outFile << coef;
        }else{
            if(coef > 0){
                coef == 1 ? outFile << prefixChar : outFile << prefixChar << coef;
            }else{
                coef == -1 ? outFile << "-" : outFile << coef;
                //cout << coef;
            }
            exp == 1 ? outFile << "x" : outFile << "x^" << exp;
        }
    }
};

class LinkedList{
public:
    ListNode* head;
    LinkedList(){
        head = new ListNode(0,0);
    }
    //Addition functionality
    void insertAfter(ListNode* node){
        if(node->coef == 0) return;
        if(head->next==nullptr){
            head->next = node;
            return;
        }
        ListNode* curr = head->next;
        ListNode* prev = head;
        while(curr != nullptr){
            if(curr->exp == node->exp){
                curr->coef = curr->coef + node->coef;
                if(curr->coef==0){
                    prev->next = curr->next;
                    curr = curr->next;
                }
                delete node;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        curr = head;
        while(curr->next != nullptr){
            if(node->exp < curr->exp && node->exp > curr->next->exp){
                node->next = curr->next;
                curr->next = node;
                return;
            }else if(node->exp > curr->next->exp){
                node->next = curr->next;
                curr->next = node;
                return;
            }
            curr = curr->next;
        }
        curr->next = node;
    }
    //Insert node for multiplication
    LinkedList* multiply_InsertAfter(LinkedList *list2){
        cout << endl;
        LinkedList *result = new LinkedList();
        ListNode *p2 = list2->head->next;
        while(p2 != nullptr){
            ListNode *p1 = this->head->next;
            while(p1 != nullptr){
                ListNode *newNode = new ListNode(p1->coef*p2->coef, p1->exp+p2->exp);
                result->insertAfter(newNode);
                p1 = p1->next;
            }
            p2 = p2->next;
        }
        //result->printList();
        return result;
    }

    void printList(){
        cout << endl;
        ListNode* curr = head->next;
       //cout << "Test: " << curr->coef<< " "<< curr->exp << endl;
        if(curr!=nullptr && curr->coef>0){
           curr->printFirstTerm();
           curr = curr->next;
        }
        while(curr != nullptr){
            curr->printNode();
            curr = curr->next;
        }
    }
    void printList(ofstream& outFile){
        ListNode* curr = head->next;
       // outFile << "Test: " << curr->coef<< " "<< curr->exp << endl;
        if(curr!=nullptr && curr->coef>0){
            curr->printFirstTerm(outFile);
            curr = curr->next;
        }
        while(curr != nullptr){
            curr->printNode(outFile);
            curr = curr->next;
        }
    }

    ~LinkedList(){
        while(head!=nullptr){
            ListNode* curr = head;
            head = head->next;
            delete curr;
        }
    }
};

class Polynomial{

public:
    LinkedList *list;
    Polynomial(){
        list = new LinkedList();
    }

    LinkedList* getList(){
        return list;
    }
    void setList(LinkedList *curList){
        list = curList;
    }
    void printPoly(ofstream& outFile){
        this->list->printList(outFile);
    }

    Polynomial*  operator*(Polynomial *B){
        cout << endl  << endl << "Multiply Two Polynomial: "  << endl;
        Polynomial *C = new Polynomial();
        ListNode *pa = this->list->head->next;
        while(pa != nullptr){
            ListNode *newNode = new ListNode(pa->coef, pa->exp);
            C->getList()->insertAfter(newNode);
            pa = pa->next;
        }
        LinkedList *newList = C->getList()->multiply_InsertAfter(B->getList());
        C->setList(newList);
        C->getList()->printList();
        //ListNode *pb = B->getList()->head->next;
        return C;
    }

    Polynomial* operator-(Polynomial *B){
        cout << endl  << endl  << "Minus Two Polynomial: "  << endl;
        Polynomial *C = new Polynomial();
        ListNode *pa = this->list->head->next;
        while(pa != nullptr){
            ListNode *newNode = new ListNode(pa->coef, pa->exp);
            C->getList()->insertAfter(newNode);
            pa = pa->next;
        }
        ListNode *pb = B->getList()->head->next;
        while(pb != nullptr){
           ListNode *newNode = new ListNode((-1.0)*(pb->coef), pb->exp); // set polynomial B to -B, and then -B + A
           C->getList()->insertAfter(newNode);
           pb = pb->next;
        }
        C->getList()->printList();
        return C;
    }

    Polynomial* operator+(Polynomial *B){
        cout << endl  << endl  << "Add Two Polynomial: "  << endl;
        Polynomial *C = new Polynomial();
        ListNode *pa = this->list->head->next;
        while(pa != nullptr){
            ListNode *newNode = new ListNode(pa->coef, pa->exp);
            //cout << "Term: " << newNode->coef << " " << newNode->exp << endl;
            C->getList()->insertAfter(newNode);
            pa = pa->next;
        }
        ListNode *pb = B->getList()->head->next;
        while(pb != nullptr){
            ListNode *newNode = new ListNode(pb->coef, pb->exp);
            //cout << "Term: " << newNode->coef << " " << newNode->exp << endl;
            C->getList()->insertAfter(newNode);
            pb = pb -> next;
        }
        C->getList()->printList();
        return C;
    }


};

//Extract data from stringstream
vector<int> splitString(const string& str, char delim)
{
    vector<int> tokens;
    if (str == "") return tokens;
    string currentToken;
    stringstream ss(str);
    int x = 0;
    while (getline(ss, currentToken, delim))
    {
        x = stoi(currentToken);
        tokens.push_back(x);
    }

    return tokens;
}


int  main(int argc, const char *argv[]){
    //Read data from input file
    string line;
    vector<string> polys;
    vector <int> func1;
    vector <int> func2;
    ifstream fin;
    fin.open(argv[1]);
    int lineNum = 1;
    if(fin.is_open()){
        while(getline(fin, line)){
           if(lineNum==1){
               func1 = splitString(line, ' ');
               lineNum++;
           }else{
               func2 = splitString(line, ' ');
           }
        }
    }
  /*  for(int a : func1) cout << a << " " ;
    cout << endl;
    for(int b : func2) cout << b << " ";
    cout << endl; */

    ofstream outFile(argv[2]);

    // Construct Polynomial by using infile data
    LinkedList list1, list2;
    int i=0, j=0;
    double coef = 0;
    int exp = 0;
    while(i<func1.size()){
        coef = (double)func1[i++];
        exp = func1[i++];
        ListNode *newNode = new ListNode(coef, exp);
        //cout << newNode->coef << " " << newNode->exp << endl;
        list1.insertAfter(newNode);
    }
    while(j<func2.size()){
        coef = (double)func2[j++];
        exp = func2[j++];
        ListNode *newNode = new ListNode(coef, exp);
        //cout << newNode->coef << " " << newNode->exp << endl;
        list2.insertAfter(newNode);
    }
    // Create Two Polynomial
    Polynomial *poly1 = new Polynomial();
    Polynomial *poly2 = new Polynomial();

    *(poly1->list) = list1;
    *(poly2->list) = list2;
    list1.printList();
    list2.printList();
    outFile << "1. " << endl;
    outFile << "First Polynomial : " ;
    poly1->getList()->printList(outFile);
    outFile <<  endl <<  "Second Polynomial :  ";
    poly2->getList()->printList(outFile);
    // Operation on Polynomial
    Polynomial *add = (*poly1) + poly2;
    Polynomial *minus = (*poly1) - poly2;
    Polynomial *multiply = (*poly1) * poly2;

    outFile << endl << "2. Add Two Polynomial: " << endl;
    add->printPoly(outFile);
    outFile << endl <<  "3. Minus Two Polynomial: " << endl;
    minus->printPoly(outFile);
    outFile << endl << "4. Multiply Two Polynomial: " << endl;
    multiply->printPoly(outFile);

    return 0;
}

/*
Test data1:
6 2 2 3 4 1
-3 2 2 3 3 1

Test data2:
5 2 4 1 2 0
-5 1 -5 0

    ListNode* node1 = new ListNode(3, 2);
    ListNode* node2 = new ListNode(4, 1);
    ListNode* node3 = new ListNode(3, 2);
    ListNode* node4 = new ListNode(2, 3);

    ListNode* node5 = new ListNode(-5, 2);
    ListNode* node6 = new ListNode(3, 1);
    ListNode* node7 = new ListNode(2, 3);
    ListNode* node8 = new ListNode(2, 2);

    list1.insertAfter(node1);
    list1.insertAfter(node4);
    list1.insertAfter(node2);
    list1.insertAfter(node3);

    list2.insertAfter(node5);
    list2.insertAfter(node6);
    list2.insertAfter(node7);
    list2.insertAfter(node8);

*/

