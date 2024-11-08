#include <iostream>
#include <string>
#include <vector>

class Item {
  protected:
    std::string _title;
    std::string _author;
    int _year;
  public:
    Item(std::string title, std::string author, int year) : _title(title), _author(author), _year(year) {}
    virtual ~Item() {}
    virtual void display_info() const = 0;
};

class Book : public Item {
  private:
    int _pages;
  public:
    Book(std::string title, std::string author, int year, int pages) : Item(title, author, year), _pages(pages) {}
    void display_info() const override {
      std::cout << "title: " << this->_title << std::endl;
      std::cout << "author: " << this->_author << std::endl;
      std::cout << "year: " << this->_year << std::endl;
      std::cout << "pages: " << this->_pages << std::endl;
    }
};

class Magazine : Item {
  private:
    int _issue;
  public:
    Magazine(std::string title, std::string author, int year, int issue) : Item(title, author, year), _issue(issue) {}
    void display_info() const override {
      std::cout << "Magazine" << std::endl;
      std::cout << "title: " << this->_title << std::endl;
      std::cout << "author: " << this->_author << std::endl;
      std::cout << "year: " << this->_year << std::endl;
      std::cout << "issue: " << this->_issue << std::endl;
    }
};

class LibraryUser {
  private:
    std::string _name;
    std::vector<Item*> _borrowed_items;
  public:
    LibraryUser(std::string name) : _name(name) {}
    void borrow(Item *item);
    void return_item(Item *item);
    void list_borrowed_items();
};

void LibraryUser::borrow(Item *item) {
  this->_borrowed_items.push_back(item);
}

void LibraryUser::return_item(Item *item) {
  for (int i = 0; i < this->_borrowed_items.size(); i++) {
    if (item == this->_borrowed_items[i]) {
      this->_borrowed_items.erase(this->_borrowed_items.begin() + i);
    }
  }
}

void LibraryUser::list_borrowed_items() {
  for (int i = 0; i < this->_borrowed_items.size(); i++) {
    std::cout << this->_borrowed_items[i] << std::endl;
  }
}

class Library {
  private:
    std::vector<Item*> _items;
    std::vector<LibraryUser*> _users;
  public: 
    ~Library();
    void add_item(Item *item);
    void remove_item(Item *item);
    void register_user(LibraryUser *user);
    void borrow_item(LibraryUser *user, Item *item);
    void return_item(LibraryUser *user, Item *item);
    void list_items();
    void list_available_items();
};

Library::~Library() {
  for (int i = 0; i < this->_items.size(); i++) {
    this->_items.erase(this->_items.begin() + i);
  }

  for (int i = 0; i < this->_users.size(); i++) {
    this->_users.erase(this->_users.begin() + i);
  }
}
void Library::add_item(Item *item) {
  this->_items.push_back(item);
}

void Library::remove_item(Item *item) {
  for (int i = 0; i < this->_items.size(); i++) {
    if (item == this->_items[i]) {
      this->_items.erase(this->_items.begin() + i);
      break;
    }
  }
}

void Library::register_user(LibraryUser *user) {
  this->_users.push_back(user);
}

void Library::borrow_item(LibraryUser *user, Item *item) {
  user->borrow(item);
}

void Library::return_item(LibraryUser *user, Item *item) {
  user->return_item(item);
}

void Library::list_items() {
  for (int i = 0; i < this->_items.size(); i++) {
    this->_items[i]->display_info();
  }
}

void Library::list_available_items() {
  // check if item in borrowed by any of the lib users
  // if not print
  // i cba doing this
}

int main() {

  return 0;
}
