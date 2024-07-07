#pragma once

#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace Lineardb {
typedef unsigned long long undex;

class DataVector {
 public:
  std::string name;
  std::vector<std::string> data;

 private:
  mutable std::shared_mutex protect_data_;
};

class DataMatrix {
 public:
  std::string name;
  std::vector<DataVector*> matrix;
 private:
  mutable std::shared_mutex block_;
};

class Leaf {
 public:
  std::string name;
  int age;
  DataMatrix* data;
  Leaf(std::string iname, int iage);

 private:
  mutable std::shared_mutex stream_lock_;
};

class List {
 private:
  mutable std::shared_mutex stop_world_;

 public:
  unsigned long long size;

  class Node {
   public:
    Leaf* data;
    struct Node* next;
    struct Node* prev;
    Node(Leaf* pdata);

   private:
    mutable std::shared_mutex lock_;
  };

  class Finder {
   public:
    bool find(undex seek);
    void insert(undex seek, Node* node);
    Node* get(undex seek);
    void del(undex seek);
    Finder() = default;

   private:
    std::unordered_map<undex, Node*> exists;
    mutable std::shared_mutex stream_lock_;
  };

  struct Finder* finder;

  struct Node* head;

  bool insert(Leaf* p);

  struct Node* find_node(int seek);

  void delete_node_map(int age);

  void delete_node(int age);

  void print_list();

  List();

  ~List();
};

void LOG(std::string message);
}