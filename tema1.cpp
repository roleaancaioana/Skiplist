// Copyright 2019 Rolea Anca-Ioana 313CA
#include <bits/stdc++.h>
#include <limits>
#include <random>
#include <ctime>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#define NMAX 1000

template <class T>
class Node {
 public:
        T key;
        Node<T>* next;
        Node<T>* prev;
        Node<T>* above;
        Node<T>* down;
        explicit Node(T key);
};

template <class T>
Node<T>::Node(T key) {
    this->key = key;
    next = nullptr;
    prev = nullptr;
    above = nullptr;
    down = nullptr;
}

template <class T>
class Skiplist {
 public:
    Node<T>* head;
    Node<T>* tail;
    int n;
    int h;
    Skiplist() {
    head = new Node<T>(INT_MIN);
    tail = new Node<T>(INT_MAX);
    head->next = tail;
    tail->prev = head;
    n = 0;
    h = 1;
    }
    ~Skiplist() {
        Node<T> *p = head;
        Node<T> *q, *r;
        while (p != NULL) {
            q = r = p;
            p = p->down;
            while (q != NULL) {
                r = q->next;
                delete q;
                q = r;
            }
        }
    }
    void insertElement(T key);
    void displayList();
    Node<T>* searchElement(T key);
    void deleteElement(T key);
};

/* daca se afla in skiplist cheia cautata, atunci functia search va returna un pointer la nodul 
care contine cheia respectiva, daca nu, functia va intoarce un pointer la nodul care contine 
cea mai mare valoare din skiplist mai mica decat cheia cautata de noi. */
template <class T>
Node<T>* Skiplist<T>::searchElement(T key) {
    Node<T>* p;
    p = head;
    while (p -> down != NULL) {
        p = p -> down;
        while (key >= p->next->key) {
            p = p -> next;
        }
    }
    if (p  -> down == NULL) {
        while (key >= p->next->key) {
            p = p -> next;
        }
    }
    return p;
}

// in skiplist inseram cheile astfel incat sa fie in ordine crescatoare
template <class T>
void Skiplist<T>::insertElement(T key) {
    // ne pozitionam acolo unde vrem sa inseram noua cheie
    Node<T>* p = searchElement(key);
    Node<T>* q = new Node<T>(key);
    int i = 0;
    q->prev = p;
    q->next = p->next;
    p->next->prev = q;
    p->next = q;
    // facem o coloana de lungime variabila pentru noua cheie introdusa
    unsigned int rs = time(nullptr);
    int Coin_Toss = rand_r(&rs) % 2;
    while (Coin_Toss == 0) {
        i++;
        if (i >= h) {
            h++;
            Node<T>* a1 = new Node<T>(INT_MIN);
            Node<T>* a2 = new Node<T>(INT_MAX);
            a1->next = a2;
            a1->down = head;
            a2->prev = a1;
            a2->down = tail;
            head->above = a1;
            tail->above = a2;
            head = a1;
            tail = a2;
        }
        while (p->above == NULL) {
            p = p->prev;
        }
        p = p -> above;
        Node<T>* aux = new Node<T>(key);
        aux->prev = p;
        aux->next = p->next;
        aux->down = q;
        p->next->prev = aux;
        p->next = aux;
        q->above = aux;
        q = aux;
        Coin_Toss = rand_r(&rs) % 2;
    }
    n++;
}

template <class T>
void Skiplist<T>::displayList() {
    Node<T>* q = head;
    for (int i = h; i > 0; i--) {
        Node<T>* aux = q;
        while (q != NULL) {
            std::cout << q -> key << " ";
            q = q->next;
        }
    aux = aux->down;
    q = aux;
    std::cout << "\n";
    }
}

template <class T>
 void Skiplist<T>::deleteElement(T key) {
    Node<T>* p = searchElement(key);
    if (p->key != key) {
        std::cout << "Error";
        exit(-1);
    } else {
        Node<T> *q;
        do {
            p->next->prev = p->prev;
            p->prev->next = p->next;
            q = p;
            p = p->above;
            delete q;
        } while (p != NULL);
    n--;
    }
}

// aceasta functie ne ajuta sa verificam daca urmeaza sau nu o operatie de print
bool isEqual(std::string a, std::string b) {
    if (b[0] != a[0]) {
        return false;
    } else {
        return true;
    }
}

class player_t {
 public:
    int time;
    int points;
    int print_position;
    int id;
    int current_position;
};

int number_of_players(player_t *player, int p, int n) {
    int i;
    for (i = 0; i < n; ++i) {
        if (player[i].time == 0) {
            p--;
        }
    }
    return p;
}

bool sort_time(player_t player1, player_t player2) {
    if (player1.time != player2.time) {
        return (player1.time > player2.time);
    }
    return (player1.current_position >
        player2.current_position);
}

bool sort_time_first_position(player_t player1, player_t player2) {
    if (player1.time != player2.time) {
        return (player1.time > player2.time);
    }
    return (player1.id > player2.id);
}

bool sort_points(player_t player1, player_t player2) {
    if (player1.points != player2.points) {
        return player1.points < player2.points;
    }
        return player1.id > player2.id;
}


bool compare_id(player_t player1, player_t player2) {
    return player1.id < player2.id;
}

void number_of_points(int p, player_t *player) {
    int i = -p/2, c = 0;
    while (i <= p/2) {
        if (p % 2 == 0 && i == 0) {
            i++;
        } else {
            if (player[c].time != 0) {
                player[c].points += i;
                i++;
            } else {
                player[c].points += 0;
                i++;
            }
        c++;
        }
    }
}

void difference_levels(player_t* player, int n, int* level, int c) {
    int i;
    // conditia aceasta ma ajuta sa tin cont de faptul ca pentru primul
    // print diferenta de nivel va fi 0 pentru toti pariticipantii
    if (c > 1) {
        for (i = 0; i < n; i++) {
            level[i] = i - player[i].print_position;
        }
    }
}

int main() {
    srand((unsigned) time(NULL));
    int n, m, k, i, j, x, p, c = 0;
    std::string s;
    std::ifstream f;
    f.open("races.in");
    std::ofstream g;
    g.open("races.out");
    f >> n >> m >> k;
    player_t *player = new player_t[NMAX];
    // vectorul level stocheaza diferenta de nivel
    int *level = new int[NMAX];

    for (i = 0; i < n; i++) {
        level[i] = 0;
        player[i].points = 0;
        player[i].print_position = i + 1;
        player[i].id = i + 1;
    }

    for (j = 0; j < m + k; ++j) {
        p = n;
        f >> s;
        if (isEqual(s, "print")) {
            Skiplist<int> mySL;
            int points[NMAX], a = 0, i;
            c++;
            for (i = 0; i < n; ++i) {
                mySL.insertElement(player[i].points);
            }
            Node<int> *p = mySL.searchElement(INT_MIN);
            p = p -> next;
            while (p -> key != INT_MAX) {
                points[a++] = p -> key;
                p = p -> next;
            }
            difference_levels(player, n, level, c);
            for (i = n - 1; i >= 0; i--) {
                g << player[i].id << " "
                << points[i] << " " << level[i] << " " <<"\n";
            }
            for (i = 0; i < n; ++i) {
                player[i].print_position = i;
            }
            g << "\n";
        } else {
            x = 0;
            std::sort(player, player + n, compare_id);
            player[x++].time = stoi(s);
            for (i = 1; i < n; i++) {
                f >> player[x].time;
                x++;
            }
            if (j == 0) {
                std::sort(player, player + n, sort_time_first_position);
            } else {
                std::sort(player, player + n, sort_time);
            }
            p = number_of_players(player, p, n);
            number_of_points(p, player);
            std::sort(player, player + n, sort_points);
            for (i = 0; i < n; i++) {
                player[i].current_position = n - i;
            }
        }
    }
    delete [] player;
    delete [] level;
    f.close();
    g.close();
return 0;
}



