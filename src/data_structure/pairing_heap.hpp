#pragma once

#include <functional>

template <typename T, typename Compare = std::less<T>> class PairingHeap {
    struct Node {
        T v;
        Node *child, *sibling;
        Node *prev; // if it's the leftmost child, points to parent, otherwise points to
                    // its left sibling
        Node(const T &_v) : v(_v), child(), sibling(), prev() {}
        Node(T &&_v) : v(std::move(_v)), child(), sibling(), prev() {}
    };

    using node_ptr = Node *;

    Compare comp;
    node_ptr root;
    size_t m_size;

    // meld two heap naively
    node_ptr meld(node_ptr x, node_ptr y) {
        if (!x) return y;
        if (!y) return x;

        if (!comp(x->v, y->v)) {
            std::swap(x, y);
        }

        if (x->child) {
            x->child->prev = y;
        }
        y->sibling = x->child;
        x->child = y;
        y->prev = x;

        return x;
    }

    // merge all slibings of a child
    node_ptr merge(node_ptr x) {
        if (!x) {
            return nullptr;
        }

        x->prev = nullptr;
        if (!x->sibling) {
            return x;
        }

        auto y = x->sibling;
        auto rest = y->sibling;

        y->prev = nullptr;
        x->sibling = nullptr;
        y->sibling = nullptr;

        return meld(merge(rest), meld(x, y));
    }

    node_ptr modify(node_ptr root, node_ptr x, const T& val) {
        x->v = val;
        if (x == root) {
            return root;
        }

        if (x->prev->child == x) { // if x is the leftmost child
            x->prev->child = x->sibling;
        } else {
            x->prev->sibling = x->sibling;
        }

        if (x->sibling) {
            x->sibling->prev = x->prev;
        }
        x->sibling = nullptr;
        x->prev = nullptr;

        return meld(root, x);
    }

  public:
    using point_iterator = Node *;

    PairingHeap() : root(), m_size() {}

    T top() const { return root->v; }

    bool empty() const {
        return m_size == 0;
    }

    size_t size() const {
        return m_size;
    }

    T pop() {
        auto res = std::move(root->v);
        auto old_root = root;
        root = merge(root->child);
        delete old_root;
        return res;
    }

    point_iterator push(const T &val) {
        auto node = new Node{val};
        root = meld(root, node);
        return node;
    }

    void modify(point_iterator it, const T& val) {
        assert(!comp(it->v, val));
        root = modify(root, it, val);
    }

    ~PairingHeap() {
        auto del = [](auto& slf, node_ptr p) -> void {
            if (!p) return;
            slf(slf, p->child);
            slf(slf, p->sibling);
            delete p;
        };
        del(del, root);
    }
};
