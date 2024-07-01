#include <unistd.h>  //sleep()

#include <chrono>
#include <iostream>
#include <string>

#include "list.h"
int main() {
  using std::chrono::duration;
  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;
  using std::chrono::milliseconds;
  Leaf* p = new Leaf("mino", 28);
  List l;
  std::cout << l.size << "\n";
  bool ok = l.insert(p);
  if (!ok) {
    std::cout << p->age << " already exits!\n";
  }
  l.print_list();

  ok = l.insert(p);
  if (!ok) {
    std::cout << p->age << " already exits!\n";
  }
  Leaf *p2 = new Leaf("mino", 29);
  ok = l.insert(p2);
  if (!ok) {
    std::cout << p->age << " already exits!\n";
  }
  l.print_list();
  l.delete_node_map(28);
  l.delete_node_map(29);
  l.print_list();

  unsigned long int number = 10;
  LOG("allocating memory");
  auto t1 = high_resolution_clock::now();
  for (int i = 0; i < number; i++) {
    Leaf p("mino", i);
    l.insert(&p);
  }
  auto t2 = high_resolution_clock::now();
  duration<double, std::milli> ms_double = t2 - t1;
  std::cout << ms_double.count() << "ms\n";
  LOG("allocation complete!");
  LOG("begin delete!");
  t1 = high_resolution_clock::now();
  for (int i = 0; i < number; i++) {
    l.delete_node_map(i);
  }
  t2 = high_resolution_clock::now();
  ms_double = t2 - t1;
  std::cout << ms_double.count() << "ms\n";
  LOG("delete complete");
  l.print_list();
  return 0;
}
