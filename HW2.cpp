//CIS554 HW2
//Vincent Zhang
//Due: 11:59PM, Friday (Feb. 15)
//Implement In-place quick sort
//You are only allowed to modify pointers of nodes, but not values of nodes
//Do not modify main function
//Do not introduce new functions

#include <iostream>
using namespace std;

class node {
public:
  int value;
  node * next;
  node * previous;
  node(int i) { value = i; next = previous = nullptr; }
  node() { next = previous = nullptr; }
};

class doubly_linked_list {
public:
  node * head;
  node * tail;
  doubly_linked_list() { head = tail = nullptr; }
  void make_random_list(int m, int n); //create m nodes with value randomly in 0 ... n-1
  void print_forward();
  void print_backward();

  //inplement the following member functions:
  //Vincent's Code starts here
  void sort(node * p1, node * p2){
          //Range of sort is from *p1 to *p2
          //Use in-place quick sort algorithm to sort the linked list in ascending order.
          //You are only allowed to modify the pointers of nodes, but not values of nodes

    //Base case: pointers point to same node then no need to sort
    if (p1 == p2)
     {
       return;
     }

    //p3 points to each node while iterating through while loop
    //p4 keeps track of p3's position when swapping
    //low will store the position of where to start from left of pivot
    //high will store position of where to end from right of pivot
    //low and high will be used as parameters in recursive call.
    //check is a pointer used to check an edge case when trying to assign
    //value to "low"
    node *p3 = p1->next;
    node *p4;
    node *low,*high,*check;
    check = p1->previous;

    while (p3 != nullptr && p3!= p2+1) {
      high = p3;

      //If less than pivot, move to left of pivot
      //else ignore and move on to next node
      if (p3->value < p1->value) {
        p4 = p3->next;

        //edge case for when dealing with the last element
        //deal with nullpointer case
        if (p3->next != nullptr) {
          (p3->previous)->next = p3->next;
          (p3->next)->previous = p3->previous;
        }
        else {
          (p3->previous)->next = NULL;
          tail = p3->previous;
        }

        //edge case for inserting to the head
        //deal with nullpointer case
        if (p1->previous == nullptr) {
          p3->next = p1;
          p3->previous = NULL;
          p1->previous = p3;
          head = p3;
        }
        else {
          high = p3->previous;
          (p1->previous)->next = p3;
          p3->previous = p1->previous;
          p3->next = p1;
          p1->previous = p3;
        }
        p3=p4;
      }

      else {
        p3 = p3->next;
      }
    }



    //Edge case for when there is a new head
    if (check == nullptr) {
      low = head;
    }
    else {
      low = check->next;
    }

    //if bounds = same node then no need to recursivel call
    //Also checks edge case for:
    //When there's nothing right of the pivot, then don't need to call
    if (p1->next != NULL && p1->next != high) {
      sort(p1->next, high);
    }

    //if bounds = same node then no need to recrusively call
    //Also checks edge case for:
    //if nothing was added to left of pivot then don't need to call
    if (check != p1->previous && p1->previous != low) {
      sort(low, p1->previous);
    }
  }

};

//Vincent's Code Ends Here
void doubly_linked_list::make_random_list(int m, int n) {

  for (int i = 0; i < m; i++) {
    node * p1 = new node(rand() % n);
    p1->previous = tail;
    if (tail != nullptr) tail->next = p1;
    tail = p1;
    if (head == nullptr) head = p1;
  }
}

void doubly_linked_list::print_forward() {
  cout << endl;
  node * p1 = head;
  while (p1 != nullptr) {
    cout << p1->value << " ";
    p1 = p1->next;
  }
}

void doubly_linked_list::print_backward() {
  cout << endl;
  node * p1 = tail;
  while (p1 != nullptr) {
    cout << p1->value << " ";
    p1 = p1->previous;
  }
}

int main() {
  doubly_linked_list d1;
  d1.make_random_list(50, 20);
  d1.print_forward();
  cout << "" << endl;
  d1.print_backward();
  cout << "" << endl;
  d1.sort(d1.head, d1.tail);
  d1.print_forward();
  cout << "" << endl;
  d1.print_backward();


  getchar();
  getchar();
  return 0;
}