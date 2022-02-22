#include <iostream>
#include "priority_queue.h"
using namespace std;
int main() {
  PriorityQueue<int> queue;
  PriorityQueue<int> queue2;
  int type;
  cout << "enter type of request\n";
  cout << "1: push\n";
  cout << "2: push with moving\n";
  cout << "3: getsize\n";
  cout << "4: get front element's value\n";
  cout << "5: get front element's priority\n";
  cout << "6: get count of high priority\n";
  cout << "7: get count of medium priority\n";
  cout << "8: get count of low priority\n";
  cout << "9: check if queue is empty\n";
  cout << "10: pop element\n";
  cout << "11: queue2 = queue\n";
  cout << "12: queue2 = queue with moving\n";
  cout << "13: queue3(queue)\n";
  cout << "14: queue3(queue) with moving\n";
  cout << "0:end work\n";
  do {
    cin >> type;
    switch (type) {
      int a, priority;
      case 1:
        cin >> a >> priority;
        switch (priority) {
          case 1 : {
            queue.Push(a, PriorityQueue<int>::Priority::high);
            break;
          }
          case 2 : {
            queue.Push(a, PriorityQueue<int>::Priority::medium);
            break;
          }
          case 3 : {
            queue.Push(a, PriorityQueue<int>::Priority::low);
            break;
          }
        }
        //system("pause");
        break;
      case 2:
        cin >> a >> priority;
        switch (priority) {
          case 1 : {
            queue.Push(std::move(a), PriorityQueue<int>::Priority::high);
            break;
          }
          case 2 : {
            queue.Push(std::move(a), PriorityQueue<int>::Priority::medium);
            break;
          }
          case 3 : {
            queue.Push(std::move(a), PriorityQueue<int>::Priority::low);
            break;
          }
        }
        //system("pause");
        break;
      case 3:
        cout << queue.Size() << endl;
        //system("pause");
        break;
      case 4:
        cout << queue.GetValueOfHead() << endl;
        //system("pause");
        break;
      case 5:
        cout << static_cast<int>(queue.GetPriorityOfHead()) << endl;
        //system("pause");
        break;
      case 6:
        cout << queue.GetCountOfHighPriority() << endl;
        //system("pause");
        break;
      case 7:
        cout << queue.GetCountOfMediumPriority() << endl;
        //system("pause");
        break;
      case 8:
        cout << queue.GetCountOfLowPriority() << endl;
        //system("pause");
        break;
      case 9:
        if (queue.IsEmpty()) {
          cout << "queue is empty" << endl;
        } else {
          cout << "queue is not empty" << endl;
        }
        //system("pause");
        break;
      case 10:
        queue.Pop();
        break;
        //system("pause");
      case 11:
        queue2 = queue;
        break;
      case 12:
        queue2 = std::move(queue);
        break;
      case 13: {
        PriorityQueue<int> queue3(queue);
        break;
      }
      case 14: {
        PriorityQueue<int> queue3(std::move(queue));
        break;
      }
      default:
        if (type != 0) {
          cout << "Wrong number\n";
          //system("pause");
        }
        break;
    }
  } while (type != 0);
  return 0;
}
