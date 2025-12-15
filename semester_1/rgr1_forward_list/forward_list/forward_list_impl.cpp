#include "forward_list_impl.h"
ForwardList::ForwardList() : head_(nullptr), size_(0) {}
void ForwardList::PushFront(int32_t value) {
    Node* n = new Node(value);
    n->next_ = head_;
    head_ = n;
    size_++;
}
ForwardList::~ForwardList() {
    Clear();
}
void ForwardList::PopFront() {
    if (!head_)
        return;
    Node* tmp = head_;
    head_ = head_->next_;
    delete tmp;
    size_--;
}
ForwardList::ForwardList(const ForwardList& other) : head_(nullptr), size_(0) {
    Node* cur = other.head_;
    while (cur != nullptr) {
        PushBack(cur->value_);
        cur = cur->next_;
    }
}
ForwardList::ForwardList(size_t count, int32_t value) : head_(nullptr), size_(0) {
    for (size_t i = 0; i < count; ++i) {
        PushBack(value);
    }
}
ForwardList::ForwardList(std::initializer_list<int32_t> init) : head_(nullptr), size_(0) {
    for (int32_t x : init) {
        PushBack(x);
    }
}
ForwardList& ForwardList::operator=(const ForwardList& other) {
    if (this != &other) {
        Clear();
        Node* cur = other.head_;
        while (cur != nullptr) {
            PushBack(cur->value_);
            cur = cur->next_;
        }
    }
    return *this;
}
void ForwardList::PushBack(int32_t value) {
    Node* new_node = new Node(value);

    if (head_ == nullptr) {
        head_ = new_node;
    } else {
        Node* cur = head_;
        while (cur->next_ != nullptr) {
            cur = cur->next_;
        }
        cur->next_ = new_node;
    }

    ++size_;
}
void ForwardList::Remove(int32_t value) {
    while (head_ != nullptr && head_->value_ == value) {
        PopFront();
    }
    if (head_ == nullptr)
        return;
    Node* cur = head_;
    while (cur->next_ != nullptr) {
        if (cur->next_->value_ == value) {
            Node* tmp = cur->next_;
            cur->next_ = tmp->next_;
            delete tmp;
            --size_;
        } else {
            cur = cur->next_;
        }
    }
}
void ForwardList::Clear() {
    while (head_ != nullptr) {
        PopFront();
    }
}
bool ForwardList::FindByValue(int32_t value) {
    Node* cur = head_;
    while (cur != nullptr) {
        if (cur->value_ == value)
            return true;
        cur = cur->next_;
    }
    return false;
}
void ForwardList::Print(std::ostream& out) {
    Node* cur = head_;
    while (cur != nullptr) {
        out << cur->value_;
        if (cur->next_ != nullptr)
            out << ' ';
        cur = cur->next_;
    }
}
int32_t ForwardList::Front() const {
    if (head_ == nullptr) {
        throw "List is empty";
    }
    return head_->value_;
}
size_t ForwardList::Size() const {
    return size_;
}

    // your code goes here
