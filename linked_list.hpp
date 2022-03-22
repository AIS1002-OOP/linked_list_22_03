
#ifndef SINGLY_LINKED_LIST_LINKED_LIST_HPP
#define SINGLY_LINKED_LIST_LINKED_LIST_HPP

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace ais1002 {

    template<typename T>
    class linked_list {

    public:
        
        linked_list(): size_(0) {}
        
        // disable copy and move for this type
        linked_list(const linked_list<T>&) = delete;
        linked_list(const linked_list<T>&&) = delete;
        
        [[nodiscard]] size_t size() const {
            return size_;
        }

        T &operator[](unsigned int index) {
            if (index >= size_) {
                throw std::runtime_error("Index too large: " + std::to_string(index));
            }

            std::shared_ptr<node<T>> current = head_;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }

            return current->value;
        }

        T remove(unsigned int index) {
            if (index >= size_) {
                throw std::runtime_error("Index too large: " + std::to_string(index));
            }

            std::shared_ptr<node<T>> current = head_;
            std::shared_ptr<node<T>> prev = nullptr;

            for (int i = 0; i < index; i++) {
                prev = current;
                current = current->next;
            }

            if (!prev) {
                head_ = current->next;
            } else {
                prev->next = current->next;
            }

            size_--;

            T data = std::move(current->value);

            return data;
        }

        std::vector<T> toVector() const {
            std::vector<T> v;
            v.reserve(size_);

            std::shared_ptr<node<T>> current = head_;
            while (current != nullptr) {
                v.push_back(current->value);
                current = current->next;
            }

            return v;
        }

        void addFirst(const T &value) {
            insert(value, 0);
        }

        void addLast(const T &value) {
            insert(value, size_);
        }

        void insert(const T &value, unsigned int index) {
            if (index > size_) {
                throw std::runtime_error("Index too large: " + std::to_string(index));
            }

            std::shared_ptr<node<T>> current = head_;
            std::shared_ptr<node<T>> prev = nullptr;

            for (int i = 0; i < index; i++) {
                prev = current;
                current = current->next;
            }

            std::shared_ptr<node<T>> insert = std::make_shared<node<T>>(value);
            insert->next = current;
            if (!prev) {
                head_ = insert;
            } else {
                prev->next = insert;
            }

            size_++;
        }

        friend std::ostream &operator<<(std::ostream &os, const linked_list<T> &v) {
            os << "[";
            node<T>* current = v.head_.get();
            while (current != nullptr) {
                os << current->value;
                if (current->next) {
                    os << " ,";
                }
                current = current->next.get();
            }
            os << "]";
            return os;
        }

    private:
        template<class T>
        struct node {

            T value;
            std::shared_ptr<node<T>> next;

            explicit node(const T &value) : value(value) {}
        };

        size_t size_;
        std::shared_ptr<node<T>> head_ = nullptr;
    };


}// namespace ais1002


#endif//SINGLY_LINKED_LIST_LINKED_LIST_HPP
