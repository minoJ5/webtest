#include "list.h"

Lineardb::Leaf::Leaf(std::string iname, int iage)
    : name(iname), age(iage), stream_lock_(){};

Lineardb::List::Node::Node(Leaf* pdata)
    : data(pdata), next(nullptr), prev(nullptr), lock_(){};

bool Lineardb::List::Finder::find(undex seek) {
  std::shared_lock lock(stream_lock_);
  return !(exists.find(seek) == exists.end());
};

void Lineardb::List::Finder::insert(undex seek, Node* node) {
  std::unique_lock lock(stream_lock_);
  exists[seek] = node;
};

Lineardb::List::Node* Lineardb::List::Finder::get(undex seek) {
  std::shared_lock lock(stream_lock_);
  return exists.at(seek);
};

void Lineardb::List::Finder::del(undex seek) {
  std::unique_lock lock(stream_lock_);
  exists.erase(seek);
};

Lineardb::List::List() : size(0), head(nullptr), finder(new Finder){};

Lineardb::List::~List() {
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

bool Lineardb::List::insert(Leaf* p) {
  std::unique_lock lock(stop_world_);
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

void Lineardb::List::delete_node_map(int age) {
  if (head == nullptr) {
    return;
  }
  if (!finder->find(age)) {
    return;
  }
  Node* to_delete = finder->get(age);
  // std::cout << to_delete << "\n";
  // std::cout << finder->get(age) << "\n";
  if (to_delete == head) {
    head = nullptr;
    finder->del(age);
    // std::cout << to_delete << "\n";
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

void Lineardb::List::print_list() {
  std::shared_lock lock(stop_world_);
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

void Lineardb::LOG(std::string message) { std::cout << message << "\n"; }