/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/09/03 22:07:17               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   rb_tree.hpp                                                              */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include <memory>
# include <stddef.h>
# include "algorithm.hpp"
# include "utility.hpp"

namespace ft {
    enum Color {
        RED,
        BLACK
    };
    template <class T, class Compare, class Alloc = std::allocator<T> >
    struct rb_tree {
        struct node {
             T                              val;
             node*                          left;
             node*                          right;
             node*                          parent;
             Color                          color;
         };
        typedef typename Alloc::template rebind<node>::other allocator_type;
        rb_tree(const Compare& comp = Compare(), const Alloc& alloc = Alloc()): tree(NULL), first(&root), last(&root), root((node){}), size(0), comp(comp), alloc(alloc) {
        };
        rb_tree(const rb_tree& x): first(&root), last(&root), root((node){}), size(0), comp(x.comp), alloc(x.alloc) {
            this->tree = copy_tree(x, x.tree);
            if (this->tree)
                tree->parent = &this->root;
        };
        ~rb_tree() {
            clear_all();
        };
        rb_tree&                            operator=(const rb_tree& x) {
            clear_all();
            this->tree = copy_tree(x, x.tree);
            clear_root();
            return *this;
        };
        template <class U>
        struct map_iterator {
                typedef U value_type;
                typedef std::bidirectional_iterator_tag iterator_category;
                typedef ptrdiff_t difference_type;
                typedef U* pointer;
                typedef U& reference;
                map_iterator(): _node(NULL) {
                };
                map_iterator(node* leaf): _node(leaf) {
                };
                map_iterator(const node* leaf): _node((node*)leaf) {
                };
                map_iterator(const map_iterator<value_type>& other): _node(other._node) {
                };

                operator map_iterator<const value_type>() {
                    return map_iterator<const value_type>(this->_node);
                };
                
                value_type&     operator*() const {
                    return this->_node->val;
                };
                value_type*     operator->() const {
                    return &(this->_node->val);
                };
                map_iterator&   operator++() {
                    return next(this->_node, NULL);
                };
                map_iterator    operator++(int) {
                    const map_iterator  tmp(*this);
                    next(this->_node, NULL);
                    return tmp;
                };
                map_iterator&   operator--() {
                    return prev(this->_node, NULL);
                };
                map_iterator    operator--(int) {
                    map_iterator    tmp(*this);
                    prev(this->_node, NULL);
                    return tmp;
                };
                map_iterator&   operator=(const map_iterator& rhs) {
                    this->_node = (node*)rhs._node;
                    return *this;
                };
                map_iterator&   next(node* new_node, node* parent) {
                    if (new_node->left && parent == new_node->parent)
                        return next(new_node->left, new_node);
                    if (new_node->parent == parent) {
                        this->_node = (node*)new_node;
                        return *this;
                    }
                    if (new_node->left && new_node->left == parent) {
                        this->_node = (node*)new_node;
                        return *this;
                    }
                    if (new_node->right && new_node->right == parent)
                        return next(new_node->right, new_node);
                    if (new_node->parent)
                        return next(new_node->parent, new_node);
                    return *this;
                };
                map_iterator&   prev(node* new_node, node* parent) {
                    if (new_node->right && parent == new_node->parent)
                        return prev(new_node->right, new_node);
                    if (new_node->parent == parent) {
                        this->_node = (node*)new_node;
                        return *this;
                    }
                    if (new_node->right && new_node->right == parent) {
                        this->_node = (node*)new_node;
                        return *this;
                    }
                    if (new_node->left && new_node->left == parent)
                        return prev(new_node->left, new_node);
                    if (new_node->parent)
                        return prev(new_node->parent, new_node);
                    return *this;
                };
                node*           _node;
        };
        typedef map_iterator<T> iterator;
        typedef map_iterator<const T> const_iterator;
        map_iterator<T>                     begin() {
            return map_iterator<T>(this->first);
        };
        map_iterator<const T>               begin() const {
            return map_iterator<const T>(this->first);
        };
        map_iterator<T>                     end() {
            return map_iterator<T>(&this->root);
        };
        map_iterator<const T>               end() const {
            return map_iterator<const T>(&this->root);
        };
        node*                               create_node(node leaf) {
            node*   new_node = this->alloc.allocate(1);
            this->alloc.construct(new_node, leaf);
            this->size++;
            return new_node;
        };
        node*                               copy_node(node leaf) {
            node*   new_node = create_node(leaf->val);
            if (leaf.left) {
                leaf.left = copy_node(leaf->left);
                leaf.left->parent = new_node;
            }
            if (leaf.right) {
                leaf.right = copy_node(leaf->right);
                leaf.right->parent = new_node;
            }
            return new_node;
        }
        void                                delete_node(node*& leaf) {
            if (leaf == this->first)
                this->first = leaf->parent;
            if (leaf == this->last)
                this->last = leaf->parent;
            this->alloc.destroy(leaf);
            this->alloc.deallocate(leaf, 1);
            leaf = NULL;
            this->size--;
        };
        node*                               copy_tree(const rb_tree& x, node* leaf) {
            //node    new_node;
            node*   ret = NULL;
            if (leaf) {
                //new_node.parent = NULL;
                //new_node.left = copy_tree(x, leaf->left);
                //new_node.right = copy_tree(x, leaf->right);
                //new_node.val = leaf->val;
                //new_node.color = leaf->color;
                node new_node = {leaf->val, copy_tree(x, leaf->left), copy_tree(x, leaf->right), NULL, leaf->color};
                ret = create_node(new_node);
                if (leaf == x.first)
                    this->first = ret;
                if (leaf == x.last)
                    this->last = ret;
                if (new_node.left)
                    new_node.left->parent = ret;
                if (new_node.right)
                    new_node.right->parent = ret;
            }
            return ret;
        };
        void                                clear_root() {
            this->root.left = this->tree;
            this->root.right = this->tree;
            if (this->tree)
                this->tree->parent = &this->root;
            if (this->first && this->first->left)
                this->first = this->first->left;
            if (this->last && this->last->right)
                this->last = this->last->right;
        };
        void                                clear_helper(node*& leaf) {
            if (leaf) {
                if (leaf->left)
                    clear_helper(leaf->left);
                if (leaf->right)
                    clear_helper(leaf->right);
                delete_node(leaf);
            }
        };
        void                                clear_all() {
            clear_helper(this->tree);
            clear_root();
        };
        void                                clear_tree(map_iterator<T> it) {
            node*   leaf = it._node;
            node*   tmp;
            if (this->first == leaf)
                this->first = (++map_iterator<T>(leaf))._node;
            if (this->last == leaf)
                this->last = (--map_iterator<T>(leaf))._node;
            if (it._node == this->tree && !leaf->right && !leaf->left) {
                delete_node(this->tree);
                this->tree = NULL;
                this->root.left = NULL;
                this->root.right = NULL;
                return ;
            }
            if (leaf->left && leaf->right)
                swap(leaf, (++map_iterator<T>(it))._node);
            if (leaf->color == RED) {
                leaf->parent->right == leaf ? leaf->parent->right = NULL : leaf->parent->left = NULL;
                delete_node(it._node);
                return ;
            }
            if (leaf->left && leaf->left->color == RED) {
                leaf->left->color = BLACK;
                if (leaf == leaf->parent->left)
                    leaf->parent->left = leaf->left;
                if (leaf == leaf->parent->right)
                    leaf->parent->right = leaf->left;
                if (leaf->left)
                    leaf->left->parent = leaf->parent;
                if (leaf == this->tree)
                    this->tree = leaf->left;
                leaf->left = NULL;
                delete_node(it._node);
                return ;
            }
            if (leaf->right && leaf->right->color == RED) {
                leaf->right->color = BLACK;
                if (leaf == leaf->parent->left)
                    leaf->parent->left = leaf->right;
                if (leaf == leaf->parent->right)
                    leaf->parent->right = leaf->right;
                if (leaf->right)
                    leaf->right->parent = leaf->parent;
                if (leaf == this->tree)
                    this->tree = leaf->right;
                leaf->right = NULL;
                delete_node(it._node);
                return ;
            }
            while (leaf != this->tree && leaf->color == BLACK) {
                if (leaf == leaf->parent->left) {
                    tmp = leaf->parent->right;
                    if (tmp->color == RED) {
                        tmp->color = BLACK;
                        leaf->parent->color = RED;
                        right_rot(leaf->parent);
                        tmp = leaf->parent->right;
                    }
                    if ((!tmp->left || tmp->left->color == BLACK) && (!tmp->right || tmp->right->color == BLACK)) {
                        tmp->color = RED;
                        leaf = leaf->parent;
                    }
                    else {
                        if (!tmp->right || tmp->right->color == BLACK) {
                            tmp->left->color = BLACK;
                            tmp->color = RED;
                            left_rot(tmp);
                            tmp = leaf->parent->right;
                        }
                        tmp->color = leaf->parent->color;
                        leaf->parent->color = BLACK;
                        if (tmp->right)
                            tmp->right->color = BLACK;
                        right_rot(leaf->parent);
                        leaf = this->tree;
                    }
                }
                else {
                    tmp = leaf->parent->left;
                    if (tmp->color == RED) {
                        tmp->color = BLACK;
                        leaf->parent->color = RED;
                        left_rot(leaf->parent);
                        tmp = leaf->parent->left;
                    }
                    if ((!tmp->right || tmp->right->color == BLACK) && (!tmp->left || tmp->left->color == BLACK)) {
                        tmp->color = RED;
                        leaf = leaf->parent;
                    }
                    else {
                        if (!tmp->left || tmp->left->color == BLACK) {
                            tmp->right->color = BLACK;
                            tmp->color = RED;
                            right_rot(tmp);
                            tmp = leaf->parent->left;
                        }
                        tmp->color = leaf->parent->color;
                        leaf->parent->color = BLACK;
                        if (tmp->left)
                            tmp->left->color = BLACK;
                        left_rot(leaf->parent);
                        leaf = this->tree;
                    }
                }
            }
            leaf->color = BLACK;
            it._node->parent->right == it._node ? it._node->parent->right = NULL : it._node->parent->left = NULL;
            delete_node(it._node);
        };
        ft::pair<map_iterator<T>, bool>    insert_helper(node* leaf) {
            node*   tmp = leaf;
            node*   x;
            if (leaf->parent->color == BLACK)
                return ft::pair<map_iterator<T>, bool>(map_iterator<T>(leaf), true);
            if (!(leaf->parent->parent && leaf->parent->parent != &this->root)) {
                leaf->parent->color = BLACK;
                return ft::pair<map_iterator<T>, bool>(map_iterator<T>(leaf), true);
            }
            if (!(leaf->parent && leaf->parent != &this->root) || !(leaf->parent->parent && leaf->parent->parent != &this->root))
                x = NULL;
            else if (leaf->parent->parent->left == leaf->parent)
                x = leaf->parent->parent->right;
            else
                x = leaf->parent->parent->left;
            if (x && x != &this->root && x->color == RED) {
                leaf->parent->color = BLACK;
                x->color = BLACK;
                leaf->parent->parent->color = RED;
                tmp = leaf->parent->parent;
                if (leaf && leaf->parent && leaf != &this->root && leaf->parent != &this->root)
                    insert_helper(tmp);
                return ft::pair<map_iterator<T>, bool>(map_iterator<T>(leaf), true);
            }
            if (tmp == leaf->parent->left) {
                if (leaf->parent->parent->right == leaf->parent) {
                    left_rot(leaf->parent);
                    leaf->color = BLACK;
                    leaf->parent->color = RED;
                    right_rot(leaf->parent);
                }
                else {
                    leaf->parent->color = BLACK;
                    leaf->parent->parent->color = RED;
                    left_rot(leaf->parent->parent);
                }
            }
            else {
                if (leaf->parent->parent->left == leaf->parent) {
                    right_rot(leaf->parent);
                    leaf->color = BLACK;
                    leaf->parent->color = RED;
                    left_rot(leaf->parent);
                }
                else {
                    leaf->parent->color = BLACK;
                    leaf->parent->parent->color = RED;
                    right_rot(leaf->parent->parent);
                }
            }
            return ft::pair<map_iterator<T>, bool>(map_iterator<T>(leaf), true);
        };
        ft::pair<map_iterator<T>, bool>    insert(node*& leaf, node* parent, const T& val) {
            node    tmp;
            if (!leaf) {
                //tmp.val = val;
                //tmp.color = RED;
                //tmp.parent = parent;
                //tmp.left = NULL;
                //tmp.right = NULL;
                //leaf = create_node(tmp);
                leaf = create_node((node){val, NULL, NULL, parent, RED});
                clear_root();
                return insert_helper(leaf);
            }
            if (comp(val, leaf->val))
                return insert(leaf->left, leaf, val);
            if (comp(leaf->val, val))
                return insert(leaf->right, leaf, val);
            return insert(leaf->right, leaf, val);
        };
        ft::pair<map_iterator<T>, bool>    insert(const T& val) {
            return insert(this->tree, &this->root, val);
        };
        ft::pair<map_iterator<T>, bool>    insert(map_iterator<T> position, const T& val) {
            map_iterator<T>    it = position;
            it++;
            if (position._node != &root && comp(position._node->val, val) && (it._node == &root || comp(val, it._node->val)))
                return position._node->right ? insert(it._node->left, it._node, val) : insert(position._node->right, position._node, val);
            return insert(this->tree, &this->root, val);
        };
        node*           left_rot(node* leaf) {
            node**  base;
            node*   tmp = leaf->left;
            if (leaf->parent && leaf->parent != &this->root && leaf->parent->left == leaf)
                base = &leaf->parent->left;
            else if (leaf->parent && leaf->parent != &this->root)
                base = &leaf->parent->right;
            else
                base = NULL;
            tmp->parent = leaf->parent;
            leaf->left = tmp->right;
            if (tmp->right && tmp->right != &this->root)
                tmp->right->parent = leaf;
            tmp->right = leaf;
            leaf->parent = tmp;
            if (base)
                *base = tmp;
            else {
                this->tree = tmp;
                this->tree->parent = &this->root;
                this->root.left = this->tree;
                this->root.right = this->tree;
            }
            return leaf;
        };
        node*           right_rot(node* leaf) {
            node**  base;
            node*   tmp = leaf->right;
            if (leaf->parent && leaf->parent != &this->root && leaf->parent->left == leaf)
                base = &leaf->parent->left;
            else if (leaf->parent && leaf->parent != &this->root)
                base = &leaf->parent->right;
            else
                base = NULL;
            tmp->parent = leaf->parent;
            leaf->right = tmp->left;
            if (tmp->left && tmp->left != &this->root)
                tmp->left->parent = leaf;
            tmp->left = leaf;
            leaf->parent = tmp;
            if (base)
                *base = tmp;
            else {
                this->tree = tmp;
                this->tree->parent = &this->root;
                this->root.left = this->tree;
                this->root.right = this->tree;
            }
            return leaf;
        };
        map_iterator<T>     find(node* leaf, const T& val) const {
            while (leaf) {
                if (comp(val, leaf->val))
                    leaf = leaf->left;
                else if (comp(leaf->val, val))
                    leaf = leaf->right;
                else
                    return map_iterator<T>(leaf);
            }
            return map_iterator<T>(&this->root);
        };
        map_iterator<T>     find(const T& val) const {
            return find(this->tree, val);
        };
        void                swap(node* first, node* second) {
            node*   tmp;
            Color   tmp_color;
            if (first->right)
                first->right->parent = second;
            if (first->left)
                first->left->parent = second;
            if (second->right)
                second->right->parent = first;
            if (second->left)
                second->left->parent = first;
            tmp = first->right;
            first->right = second->right;
            second->right = tmp;
            tmp = first->left;
            first->left = second->left;
            second->left = tmp;
            if (first->parent->right == first)
                first->parent->right = second;
            if (first->parent->left == first)
                first->parent->left = second;
            if (second->parent->right == second)
                second->parent->right = first;
            if (second->parent->left == second)
                second->parent->left = first;
            tmp = first->parent;
            first->parent = second->parent;
            second->parent = tmp;
            tmp_color = first->color;
            first->color = second->color;
            second->color = tmp_color;
            if (first == this->tree)
                this->tree = second;
            else if (second == this->tree)
                this->tree = first;
        };
        void            swap(rb_tree& x) {
            ft::swap(this->tree, x.tree);
            ft::swap(this->first, x.first);
            ft::swap(this->last, x.last);
            ft::swap(this->size, x.size);
            if (this->first == &x.root)
                this->first = &this->root;
            if (this->last == &x.root)
                this->last = &this->root;
            if (x.first == &this->root)
                x.first = &x.root;
            if (x.last == &this->root)
                x.last = &x.root;
            x.clear_root();
            clear_root();
        };
        map_iterator<T> bound_helper(node* leaf, const T& val, node* base) const {
            if (!leaf)
                return map_iterator<T>(base);
            if ((base == &this->root || comp(leaf->val, base->val)) && !comp(leaf->val, val))
                base = leaf;
            if (comp(val, leaf->val))
                return bound_helper(leaf->left, val, base);
            if (comp(leaf->val, val))
                return bound_helper(leaf->right, val, base);
            return map_iterator<T>(base);
        };
        map_iterator<T> lower_bound(const T& val) const {
            return bound_helper(this->tree, val, (node*)&this->root);
        };
        map_iterator<T> upper_bound(const T& val) const {
            map_iterator<T> it = bound_helper(this->tree, val, (node*)&this->root);
            if (it != end() && !comp(*it, val) && !comp(val, *it))
                it++;
            return it;
        };
        node*           tree;
        node*           first;
        node*           last;
        node            root;
        size_t          size;
        const Compare&  comp;
        allocator_type  alloc;
    };
};

#endif