#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

// 单链表节点的结构 
struct ListNode { 
    int val; 
    ListNode *next; 
    ListNode(int x) { val = x; } 
    };

//recursive
ListNode* reverse(ListNode *head) { 
    if (head->next == NULL) return head; 
    ListNode *last = reverse(head->next); 
    head->next->next = head; 
    head->next = NULL; 
    return last; 
    }

ListNode* successor = NULL; // 后驱节点 // 反转以 head 为起点的 n 个节点，返回新的头结点 
ListNode* reverseN(ListNode *head, int n) { 
    if (n == 1) { // 记录第 n + 1 个节点 
        successor = head->next; 
        return head; 
    }// 以 head.next 为起点，需要反转前 n - 1 个节点 
    ListNode *last = reverseN(head->next, n - 1); 
    head->next->next = head;
    // 让反转之后的 head 节点和后⾯的节点连起来 
    head->next = successor; 
    return last; 
}
ListNode* reverseBetween(ListNode *head, int m, int n) { // base case 
    if (m == 1) { 
        return reverseN(head, n); 
        }// 前进到反转的起点触发 base case 
        head->next = reverseBetween(head->next, m - 1, n - 1); 
        return head; 
    }

//iterative
ListNode* reverseBetween(ListNode* head, int m, int n) {
       ListNode *dummy = new ListNode(0), *pre = dummy, *cur;
       dummy -> next = head;
       for (int i = 0; i < m - 1; i++) {
           pre = pre -> next;
       }
       cur = pre -> next;
       for (int i = 0; i < n - m; i++) {
           ListNode* temp = pre -> next;
           pre -> next = cur -> next;
           cur -> next = cur -> next -> next;
           pre -> next -> next = temp;
       }
       return dummy -> next;
   }



