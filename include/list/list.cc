#include "list.h"

Leaf::Leaf(std::string iname, int iage) {
  name = iname;
  age = iage;
};

List::List() : size(0), head(nullptr) {}

List::~List() {
  Node* current = head;
  while (current != nullptr) {
    Node* next = current->next;
    delete current;
    current = next;
  }
  head = nullptr;
  size = 0;
}

bool List::insert(const Leaf& p) {
  if (find_node_map(p.age)) {
    return false;
  }
  struct Node* new_node = new Node(p);
  new_node->prev = nullptr;
  if (head == nullptr) {
    new_node->next = nullptr;
    head = new_node;
  } else {
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
  }
  size++;
  exists[p.age] = new_node;
  return true;
}

bool List::find_node_map(int seek) {
  return !(exists.find(seek) == exists.end());
}

struct List::Node* List::find_node(int seek) {
  struct Node* temp = head;
  while (temp != nullptr) {
    if (temp->data.age == seek) {
      return temp;
    }
    temp = temp->next;
  }
  return nullptr;
}

void List::delete_node_map(int age) {
  if (head == nullptr) {
    return;
  }
  if (!find_node_map(age)) {
    return;
  }
  Node* to_delete = exists.at(age);
  if (to_delete == head) {
    head = nullptr;
    exists.erase(age);
    delete to_delete;
    return;
  }
  Node* to_delete_next = to_delete->next;
  Node* to_delete_prev = to_delete->prev;
  if (to_delete_next == nullptr) {
    to_delete_prev->next = nullptr;
  } else {
    to_delete_prev->next = to_delete_next;
  }
  delete to_delete;
  exists.erase(age);
  size--;
  // malloc_trim(0);
}

void List::delete_node(int age) {
  Node* temp = head;
  Node* prev = nullptr;
  while (temp != nullptr && temp->data.age != age) {
    prev = temp;
    temp = temp->next;
  }
  if (temp == nullptr) {
    return;
  }
  if (prev == nullptr) {
    head = temp->next;
  } else {
    prev->next = temp->next;
  }
  delete temp;
  size--;
}

void List::print_list() {
  std::string list_string;
  list_string.append("[");
  Node* temp = head;
  std::string nodes_string;
  while (temp != nullptr) {
    nodes_string.append(std::to_string(temp->data.age));
    nodes_string.append(",");
    temp = temp->next;
  }
  if (nodes_string.length() != 0) {
    nodes_string.pop_back();
  }
  list_string.append(nodes_string);
  list_string.append("]\n");
  std::cout << list_string;
}

void LOG(std::string message) { std::cout << message << "\n"; }
