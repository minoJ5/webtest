#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

class Leaf {
 public:
  std::string name;
  int age;
  Leaf(std::string iname, int iage);
};

class List {
 public:
  unsigned long int size;

  struct Node {
    Leaf data;
    struct Node* next;
    struct Node* prev;
    Node(const Leaf& pdata) : data(pdata), next(nullptr), prev(nullptr) {}
  };

  std::unordered_map<int, Node*> exists;

  struct Node* head;

  bool insert(const Leaf& p);

  bool find_node_map(int seek);

  struct Node* find_node(int seek);

  void delete_node_map(int age);

  void delete_node(int age);

  void print_list();

  List();

  ~List();
};

void LOG(std::string message);
