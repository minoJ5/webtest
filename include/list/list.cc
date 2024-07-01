#include "list.h"

#include <malloc.h>
#include <unistd.h>

Leaf::Leaf(std::string iname, int iage)
    : name(iname), age(iage), stream_lock(){};

List::Node::Node(Leaf* pdata)
    : data(pdata), next(nullptr), prev(nullptr), lock_(){};

bool List::Finder::find(undex seek) {
  std::shared_lock lock(stream_lock_);
  return !(exists.find(seek) == exists.end());
};

void List::Finder::insert(undex seek, Node* node) {
  std::unique_lock lock(stream_lock_);
  exists[seek] = node;
};

List::Node* List::Finder::get(undex seek) {
  std::shared_lock lock(stream_lock_);
  return exists.at(seek);
};

void List::Finder::del(undex seek) {
  std::unique_lock lock(stream_lock_);
  exists.erase(seek);
};

List::List() : size(0), head(nullptr), finder(new Finder){};

List::~List() {
  Node* current = head;
  while (current != nullptr) {
    Node* next = current->next;
    delete current;
    current = next;
  }
  head = nullptr;
  delete finder;
  size = 0;
}

bool List::insert(Leaf* p) {
  std::unique_lock lock(stop_world);
  // sleep(10);
  if (finder->find(p->age)) {
    return false;
  }
  struct Node* new_node = new Node(p);
  // std::cout << new_node << "\n";
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
  finder->insert(p->age, new_node);
  return true;
}

// struct List::Node* List::find_node(int seek) {
//   struct Node* temp = head;
//   while (temp != nullptr) {
//     if (temp->data->age == seek) {
//       return temp;
//     }
//     temp = temp->next;
//   }
//   return nullptr;
// }

void List::delete_node_map(int age) {
  if (head == nullptr) {
    return;
  }
  if (!finder->find(age)) {
    return;
  }
  Node* to_delete = finder->get(age);
  //std::cout << to_delete << "\n";
  //std::cout << finder->get(age) << "\n";
  if (to_delete == head) {
    head = nullptr;
    finder->del(age);
    //std::cout << to_delete << "\n";
    delete to_delete->data;
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
  delete to_delete->data;
  delete to_delete;
  finder->del(age);
  size--;
  // malloc_trim(0);
}

// void List::delete_node(int age) {
//   Node* temp = head;
//   Node* prev = nullptr;
//   while (temp != nullptr && temp->data->age != age) {
//     prev = temp;
//     temp = temp->next;
//   }
//   if (temp == nullptr) {
//     return;
//   }
//   if (prev == nullptr) {
//     head = temp->next;
//   } else {
//     prev->next = temp->next;
//   }
//   delete temp;
//   size--;
// }

void List::print_list() {
  std::shared_lock lock(stop_world);
  // sleep(5);
  std::string list_string;
  list_string.append("[");
  Node* temp = head;
  std::string nodes_string;
  while (temp != nullptr) {
    nodes_string.append(std::to_string(temp->data->age));
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