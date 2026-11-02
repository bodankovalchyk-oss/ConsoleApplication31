#include <iostream>
#include <string>
using namespace std;

template <class T>
class PQueue {
    struct Node {
        T data;
        int pr;
        Node* next;
    };
    Node* head;
    int count;

public:
    PQueue() {
        head = NULL;
        count = 0;
    }

    ~PQueue() {
        while (head != NULL) {
            Node* t = head;
            head = head->next;
            delete t;
        }
    }

    bool empty() {
        return head == NULL;
    }

    int size() {
        return count;
    }

    void push(T x, int pr) {
        Node* n = new Node;
        n->data = x;
        n->pr = pr;
        n->next = NULL;

        if (head == NULL || pr > head->pr) {
            n->next = head;
            head = n;
        }
        else {
            Node* cur = head;
            while (cur->next != NULL && cur->next->pr >= pr)
                cur = cur->next;
            n->next = cur->next;
            cur->next = n;
        }
        count++;
    }

    bool pop(T& x, int& pr) {
        if (head == NULL)
            return false;
        Node* t = head;
        x = t->data;
        pr = t->pr;
        head = head->next;
        delete t;
        count--;
        return true;
    }

    void show() {
        Node* cur = head;
        int i = 1;
        while (cur != NULL) {
            cout << i << ". " << cur->data.name << " (" << cur->data.post
                << ", " << cur->pr << ")" << endl;
            cur = cur->next;
            i++;
        }
    }
};

struct Document {
    string name;
    string post;
};

int main() {
    PQueue<Document> q;
    int choice;

    do {
        cout << endl;
        cout << "1 - Dodaty dokument" << endl;
        cout << "2 - Vykonaty druk" << endl;
        cout << "3 - Pokazaty chergu" << endl;
        cout << "0 - Vyhid" << endl;
        cout << "Vybir: ";
        cin >> choice;

        if (choice == 1) {
            Document d;
            int p;
            cout << "Imya failu: ";
            cin >> d.name;
            cout << "Posada:" << endl;
            cout << "1 - Gist" << endl;
            cout << "2 - Administrator" << endl;
            cout << "3 - Menedzher" << endl;
            cout << "4 - Dyrektor" << endl;
            cout << "Vybir: ";
            cin >> p;

            if (p == 1) d.post = "Gist";
            else if (p == 2) d.post = "Administrator";
            else if (p == 3) d.post = "Menedzher";
            else if (p == 4) d.post = "Dyrektor";
            else {
                cout << "Nevirna posada" << endl;
                continue;
            }

            q.push(d, p);
            cout << "Dodano" << endl;
        }
        else if (choice == 2) {
            Document d;
            int p;
            if (q.pop(d, p))
                cout << "Drukuyetsya: " << d.name << " (" << d.post << ", prioritet " << p << ")" << endl;
            else
                cout << "Cherga porozhnya" << endl;
        }
        else if (choice == 3) {
            if (q.empty())
                cout << "Cherga porozhnya" << endl;
            else
                q.show();
        }
    } while (choice != 0);

    return 0;
}