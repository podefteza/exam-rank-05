// SEARCHABLE_ARRAY_BAG.HPP
   #pragma once
   #include "array_bag.hpp"
   #include "searchable_bag.hpp"

   class searchable_array_bag : public array_bag, public searchable_bag {
   public:
     searchable_array_bag();
     searchable_array_bag(const searchable_array_bag&);
     searchable_array_bag& operator=(const searchable_array_bag&);
     bool has(int) const;
     ~searchable_array_bag();
   };

// SEARCHABLE_ARRAY_BAG.CPP
   #include "searchable_array_bag.hpp"

   searchable_array_bag::searchable_array_bag() {}
   searchable_array_bag::searchable_array_bag(const searchable_array_bag& src) : array_bag(src) {}

   searchable_array_bag& searchable_array_bag::operator=(const searchable_array_bag& src) {
     if (this != &src) {
       array_bag::operator=(src);
     }
     return *this;
   }

   bool searchable_array_bag::has(int value) const {
     for (int i = 0; i < this->size; i++) {
       if (this->data[i] == value) return true;
     }
     return false;
   }

   searchable_array_bag::~searchable_array_bag() {}


// SEARCHABLE_TREE_BAG.HPP
   #pragma once
   #include "tree_bag.hpp"
   #include "searchable_bag.hpp"

   class searchable_tree_bag : public tree_bag, public searchable_bag {
   private:
     bool search(node* nodePtr, int value) const;
   public:
     searchable_tree_bag();
     searchable_tree_bag(const searchable_tree_bag&);
     searchable_tree_bag& operator=(const searchable_tree_bag&);
     bool has(int) const;
     ~searchable_tree_bag();
   };

// SEARCHABLE_TREE_BAG.CPP#include "searchable_tree_bag.hpp"
    searchable_tree_bag::searchable_tree_bag() {}
    searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& src) : tree_bag(src) {}

    searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& src) {
      if (this != &src) {
        tree_bag::operator=(src);
      }
      return *this;
    }

    bool searchable_tree_bag::search(node* n, int value) const {
      if (n == nullptr) return false;
      if (n->value == value) return true;
      if (value < n->value) return search(n->l, value);
      return search(n->r, value);
    }

    bool searchable_tree_bag::has(int value) const {
      return search(this->tree, value);
    }

    searchable_tree_bag::~searchable_tree_bag() {}

// SET.HPP
#pragma once
    #include "searchable_bag.hpp"

    class set {
    private:
      searchable_bag& bag;
    public:
      set() = delete;
      set(const set&) = delete;
      set& operator=(const set&) = delete;
      explicit set(searchable_bag&);

      bool has(int) const;
      void insert(int);
      void insert(int*, int);
      void print() const;
      void clear();

      const searchable_bag& get_bag() const;
      ~set();
    };

// SET.CPP
#include "set.hpp"
    set::set(searchable_bag& s_bag) : bag(s_bag) {}
    bool set::has(int v) const { return bag.has(v); }
    void set::insert(int v) {
      if (!this->has(v)) bag.insert(v);
    }
    void set::insert(int* arr, int n) {
      for (int i = 0; i < n; i++) this->insert(arr[i]);
    }
    void set::print() const { bag.print(); }
    void set::clear() { bag.clear(); }
    const searchable_bag& set::get_bag() const { return this->bag; }
    set::~set() {}

