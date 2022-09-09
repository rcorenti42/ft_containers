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

enum Color {
	RED,
	BLACK
};
template <typename T, class Compare, class Allocator = std::allocator<T> >
struct rb_tree {
	typedef T value_type;
	typedef size_t size_type;
	typedef Compare valuecompare;
	typedef Allocator allocator_type;
    rb_tree(const valuecompare& comp = valuecompare(), const allocator_type& alloc = allocator_type()): root(node()), tree(NULL), first(&root), last(&root), size(0), comp(comp), allocator(alloc) {
    }
	rb_tree(const rb_tree& other): root(node()), first(&root), last(&root), size(0), comp(other.comp), allocator(other.allocator) {
		tree = copy(other, other.tree);
		if (tree)
			tree->parent = &this->root;
		clear_helper();
	}
	~rb_tree() {
		clear();
	}
	rb_tree&                                                operator=(const rb_tree& other)
	{
		clear();
		this->tree = copy(other, other.tree);
		clear_helper();
		return *this;
	}
	struct node {
        T		value;
		Color	color;
        node*   parent;
        node*   left;
		node*   right;
	};
	template <typename U>
	class map_iterator {
            map_iterator&   next(node* n, node* old_node = NULL) {
		    	if (n->left && old_node == n->parent)
		    		return next(n->left, n);
		    	if (old_node == n->parent) {
		    		this->root = n;
		    		return *this;
		    	}
		    	if (n->left && old_node == n->left) {
		    		this->root = n;
		    		return *this;
		    	}
		    	if (n->right && n->right != old_node)
		    		return next(n->right, n);
                return n->parent ? next(n->parent, n) : *this;
		    }
		    map_iterator&   prev(node* n, node* old_node = NULL) {
		    	if (n->right && old_node == n->parent)
		    		return prev(n->right, n);
		    	if (old_node == n->parent) {
		    		this->root = n;
		    		return *this;
		    	}
		    	if (n->right && n->right == old_node) {
		    		this->root = n;
		    		return *this;
		    	}
		    	if (n->left && n->left != old_node)
		    		return prev(n->left, n);
                return n->parent ? prev(n->parent, n) : *this;
		    }
        public:
		    typedef ptrdiff_t difference_type;
		    typedef std::bidirectional_iterator_tag iterator_category;
		    typedef U value_type;
		    typedef U& reference;
		    typedef U* pointer;
		    map_iterator() {
            }
		    map_iterator(node* n): root(n) {
            }
		    map_iterator(const node* n): root((node*)n) {
            }
		    map_iterator(const map_iterator<U>& src): root(src.root) {
            }
            operator map_iterator<const U>() {
		    	return map_iterator<const U>(this->root);
		    }
		    map_iterator&   operator=(const map_iterator& src) {
		    	this->root = src.root;
		    	return *this;
		    }
		    U*              operator->() const {
                return &this->root->value;
            }
		    U&              operator*() const {
                return this->root->value;
            }
		    map_iterator&   operator++() {
                return next(this->root);
            }
		    map_iterator&   operator--() {
                return prev(this->root);
            }
		    map_iterator    operator++(int) {
		    	const map_iterator tmp = *this;
		    	next(this->root);
		    	return tmp;
		    }
		    map_iterator    operator--(int) {
		    	map_iterator tmp = *this;
		    	prev(this->root);
		    	return tmp;
		    }
            node*           root;
	};
	typedef map_iterator<value_type> iterator;
	typedef map_iterator<const value_type> const_iterator;
	node*                                               create_node(node create_node) {
		node*   tmp = this->allocator.allocate(1);
		this->allocator.construct(tmp, create_node);
		this->size++;
		return tmp;
	}
    node*                                               copy(node base) {
		node    *tmp = create_node(base->value, base);
		if (base.left) {
			base.left = copy(base->left);
			base.left->parent = tmp;
        }
		if (base.right) {
			base.right = copy(base->right);
			base.right->parent = tmp;
        }
	}
    node*	                                            copy(rb_tree const &other, node *other_tree) {
        node    new_node;
        node*   ret = NULL;
		if (other_tree) {
            new_node.value = other_tree->value;
            new_node.color = other_tree->color;
            new_node.parent = NULL;
            new_node.left = copy(other, other_tree->left);
            new_node.right = copy(other, other_tree->right);
            ret = this->create_node(new_node);
		    if (other_tree == other.first)
		    	this->first = ret;
		    if (other_tree == other.last)
		    	this->last = ret;
		    if (new_node.left)
		    	new_node.left->parent = ret;
		    if (new_node.right)
		    	new_node.right->parent = ret;
        }
        return ret;
	}
	void                                                erase_helper(node*& node) {
		if (node == this->first)
			this->first = node->parent;
		if (node == this->last)
			this->last = node->parent;
		this->allocator.destroy(node);
		this->allocator.deallocate(node, 1);
		node = NULL;
		this->size--;
	}
    void                                                erase(iterator base) {
		node*   tmp = base.root;
        node*   tmp2;
		if (tmp == this->first)
			this->first = (++iterator(tmp)).root;
		if (tmp == this->last)
			this->last = (--iterator(tmp)).root;
		if (!tmp->left && !tmp->right && this->tree == base.root) {
			erase_helper(this->tree);
			this->tree = NULL;
			this->root.left = NULL;
			this->root.right = NULL;
		}
        else {
		    if (tmp->left && tmp->right)
		    	swap(tmp, (++iterator(base)).root);
		    if (tmp->color == RED) {
                tmp == tmp->parent->right ? tmp->parent->right = NULL : tmp->parent->left = NULL;
		    	erase_helper(base.root);
		    }
            else {
		        if (tmp->left && tmp->left->color == RED) {
		        	tmp->left->color = BLACK;
                    if (tmp == tmp->parent->right)
                        tmp->parent->right = tmp->left;
                    if (tmp == tmp->parent->left)
                        tmp->parent->left = tmp->left;
                    if (tmp->left)
                        tmp->left->parent = tmp->parent;
                    if (tmp == this->tree)
                        this->tree = tmp->left;
		        	tmp->left = NULL;
		        	erase_helper(base.root);
		        }
		        else if (tmp->right && tmp->right->color == RED) {
		        	tmp->right->color = BLACK;
                    if (tmp == tmp->parent->right)
                        tmp->parent->right = tmp->right;
                    if (tmp == tmp->parent->left)
                        tmp->parent->left = tmp->right;
                    if (tmp->right)
                        tmp->right->parent = tmp->parent;
                    if (tmp == this->tree)
                        this->tree = tmp->right;
		        	tmp->right = NULL;
		        	erase_helper(base.root);
		        }
                else {
		            while (tmp != this->tree && tmp->color == BLACK)
		            {
		            	if (tmp == tmp->parent->left) {
		            		tmp2 = tmp->parent->right;
		            		if (tmp2->color == RED) {
		            			tmp2->color = BLACK;
		            			tmp->parent->color = RED;
		            			right_rot(tmp->parent);
		            			tmp2 = tmp->parent->right;
		            		}
		            		if ((!tmp2->left || tmp2->left->color == BLACK) && (!tmp2->right || tmp2->right->color == BLACK)) {
		            			tmp2->color = RED;
		            			tmp = tmp->parent;
		            		}
                            else {
		            			if (!tmp2->right || tmp2->right->color == BLACK) {
		            				tmp2->left->color = BLACK;
		            				tmp2->color = RED;
		            				left_rot(tmp2);
		            				tmp2 = tmp->parent->right;
		            			}
		            			tmp2->color = tmp->parent->color;
		            			tmp->parent->color = BLACK;
		            			if (tmp2->right)
		            				tmp2->right->color = BLACK;
		            			right_rot(tmp->parent);
		            			tmp = this->tree;
		            		}
		            	}
                        else {
		            		tmp2 = tmp->parent->left;
		            		if (tmp2->color == RED) {
		            			tmp2->color = BLACK;
		            			tmp->parent->color = RED;
		            			left_rot(tmp->parent);
		            			tmp2 = tmp->parent->left;
		            		}
		            		if ((!tmp2->left || tmp2->left->color == BLACK) && (!tmp2->right || tmp2->right->color == BLACK)) {
		            			tmp2->color = RED;
		            			tmp = tmp->parent;
		            		} 
                            else {
		            			if (!tmp2->left || tmp2->left->color == BLACK) {
		            				tmp2->right->color = BLACK;
		            				tmp2->color = RED;
		            				right_rot(tmp2);
		            				tmp2 = tmp->parent->left;
		            			}
		            			tmp2->color = tmp->parent->color;
		            			tmp->parent->color = BLACK;
		            			if (tmp2->left)
		            				tmp2->left->color = BLACK;
		            			left_rot(tmp->parent);
		            			tmp = this->tree;
		            		}
		            	}
		            }
		            tmp->color = BLACK;
                    base.root == base.root->parent->right ? base.root->parent->right = NULL : base.root->parent->left = NULL;
		            erase_helper(base.root);
                }
            }
        }
	}
    void	                                            clear_helper() {
        this->root.left = this->tree;
        this->root.right = this->tree;
		if (this->tree)
			this->tree->parent = &this->root;
		if (this->first && this->first->left)
			this->first = this->first->left;
		if (this->last && this->last->right)
			this->last = this->last->right;
	}
	void	                                            clear() {
		clear(this->tree);
		clear_helper();
	}
	void                                                clear(node*& node) {
		if (node) {
		    if (node->right)
		    	clear(node->right);
		    if (node->left)
		    	clear(node->left);
		    erase_helper(node);
        }
	}
	node*                                               left_rot(node* base) {
        node*   tmp = base->left;
        node**  tmp2;
        if (base->parent && base->parent->left == base && base->parent != &this->root)
            tmp2 = &base->parent->left;
        else
            tmp2 = base->parent && base->parent != &this->root ? &base->parent->right : NULL;
		tmp->parent = base->parent;
		base->left = tmp->right;
        if (tmp->right && tmp->right != &this->root)
			tmp->right->parent = base;
		tmp->right = base;
		base->parent = tmp;
		if (!tmp2) {
			this->tree = tmp;
			this->tree->parent = &this->root;
			this->root.left = this->tree;
			this->root.right = this->tree;
		}
		else
			*tmp2 = tmp;
		return base;
	}
	node*                                               right_rot(node* base) {
		node*   tmp = base->right;
        node**  tmp2;
		if (base->parent && base->parent->left == base && base->parent != &this->root)
            tmp2 = &base->parent->left;
        else
            tmp2 = base->parent && base->parent != &this->root ? &base->parent->right : NULL;
        tmp->parent = base->parent;
		base->right = tmp->left;
        if (tmp->left && tmp->left != &this->root)
			tmp->left->parent = base;
		tmp->left = base;
		base->parent = tmp;
		if (!tmp2)
		{
			this->tree = tmp;
			this->tree->parent = &this->root;
			this->root.left = this->tree;
			this->root.right = this->tree;
		}
		else
			*tmp2 = tmp;
		return base;
	}
	ft::pair<iterator, bool>                            insert(node* base) {
        node*   tmp = base;
		node*   tmp2;
        bool    cond = true;
        while (cond) {
            cond = false;
		    if (tmp->parent->color == BLACK)
		    	return ft::pair<iterator, bool>(iterator(base), true);
            if (!(tmp->parent->parent && tmp->parent->parent != &this->root)) {
		    	tmp->parent->color = BLACK;
		    	return ft::pair<iterator, bool>(iterator(base), true);
		    }
            if (!(tmp->parent && tmp->parent != &this->root) || !(tmp->parent->parent && tmp->parent->parent != &this->root))
                tmp2 = NULL;
            else if (tmp->parent->parent->left == tmp->parent)
                tmp2 = tmp->parent->parent->right;
            else
                tmp2 = tmp->parent->parent->left;
            if (tmp2 && tmp2 != &this->root && tmp2->color == RED) {
		    	tmp->parent->parent->color = RED;
		    	tmp->parent->color = BLACK;
		    	tmp2->color = BLACK;
		    	tmp = tmp->parent->parent;
                if (tmp && tmp->parent && tmp != &this->root && tmp->parent != &this->root)
                    cond = true;
                else
		    	    return ft::pair<iterator, bool>(iterator(base), true);
		    }
        }
		if (tmp == tmp->parent->left) {
			if (tmp->parent->parent->right == tmp->parent) {
				left_rot(tmp->parent);
                tmp->parent->color = RED;
				tmp->color = BLACK;
				right_rot(tmp->parent);
			}
			else {
                tmp->parent->parent->color = RED;
				tmp->parent->color = BLACK;
				left_rot(tmp->parent->parent);
			}
		}
		else {
			if (tmp->parent->parent->left == tmp->parent) {
				right_rot(tmp->parent);
                tmp->parent->color = RED;
				tmp->color = BLACK;
				left_rot(tmp->parent);
			}
			else {
                tmp->parent->parent->color = RED;
				tmp->parent->color = BLACK;
				right_rot(tmp->parent->parent);
			}
		}
		return ft::pair<iterator, bool>(iterator(base), true);
	}
	ft::pair<iterator, bool>	                        insert(node*& base, node* parent, const value_type& value) {
		if (!base) {
            base = create_node(node());
            base->parent = parent;
            base->color = RED;
            base->value = value;
			clear_helper();
			return insert(base);
		}
		if (comp(value, base->value))
			return insert(base->left, base, value);
        return comp(base->value, value) ? insert(base->right, base, value) : ft::pair<iterator, bool>(iterator(base), false);
	}
	ft::pair<iterator, bool>	                        insert(const value_type& value) {
		return insert(this->tree, &this->root, value);
	}
	ft::pair<iterator, bool>	                        insert(iterator hint, const value_type& value) {
		iterator    tmp = hint;
		tmp++;
		if (hint.root != &this->root && comp(hint.root->value, value) && (comp(value, tmp.root->value) || tmp.root == &this->root))
            return hint.root->right ? insert(tmp.root->left, tmp.root, value) : insert(hint.root->right, hint.root, value);
		return insert(this->tree, &this->root, value);
	}
	void                                                swap(rb_tree& value) {
		ft::swap(first, value.first);
		ft::swap(last, value.last);
        ft::swap(tree, value.tree);
		ft::swap(size, value.size);
		if (first == &value.root)
			first = &this->root;
		if (last == &value.root)
			last = &this->root;
		if (value.first == &root)
			value.first = &value.root;
		if (value.last == &root)
			value.last = &value.root;
		value.clear_helper();
		clear_helper();
	}
    void 	                                            swap(node* lhs, node* rhs) {
		node*   tmp;
        Color   color = lhs->color;
		if (lhs->right)
			lhs->right->parent = rhs;
		if (lhs->left)
			lhs->left->parent = rhs;
		if (rhs->right)
			rhs->right->parent = lhs;
		if (rhs->left)
			rhs->left->parent = lhs;
		tmp = lhs->right;
		lhs->right = rhs->right;
		rhs->right = tmp;
		tmp = lhs->left;
		lhs->left = rhs->left;
		rhs->left = tmp;
		if (lhs->parent->right == lhs)
			lhs->parent->right = rhs;
		if (lhs->parent->left == lhs)
			lhs->parent->left = rhs;
		if (rhs->parent->right == rhs)
			rhs->parent->right = lhs;
		if (rhs->parent->left == rhs)
			rhs->parent->left = lhs;
		tmp = lhs->parent;
		lhs->parent = rhs->parent;
		rhs->parent = tmp;
		lhs->color = rhs->color;
		rhs->color = color;
		if (this->tree == lhs)
			this->tree = rhs;
		else if (this->tree == rhs)
			this->tree = lhs;
	}
	iterator                                            find(const value_type& value) const {
		return find(this->tree, value);
	}
	iterator                                            find(node* node, const value_type& value) const {
		while (node) {
			if (comp(value, node->value))
				node = node->left;
			else if (comp(node->value, value))
				node = node->right;
			else
				return iterator(node);
		}
        return iterator(&this->root);
	}
    iterator                                            bound_helper(const value_type& value, node* lhs, node* rhs) const {
		if (lhs) {
		    if (!comp(lhs->value, value) && (rhs == &root || comp(lhs->value, rhs->value)))
		    	rhs = lhs;
		    if (comp(value, lhs->value))
		    	return bound_helper(value, lhs->left, rhs);
            return comp(lhs->value, value) ? bound_helper(value, lhs->right, rhs) : iterator(lhs);
        }
        return iterator(rhs);
	}
	iterator                                            upper_bound(const value_type& value) const {
		iterator    it = bound_helper(value, this->tree, (node*)&this->root);
        if (it != end() && !comp(value, *it) && !comp(*it, value))
            it++;
		return (it);
	}
	iterator                                            lower_bound( const value_type& key ) const {
		return bound_helper(key, this->tree, (node*)&this->root);
	}
    iterator                                            begin() {
        return iterator(this->first);
    }
	const_iterator                                      begin() const {
        return const_iterator(this->first);
    }
	iterator                                            end() {
        return iterator(&this->root);
    }
	const_iterator                                      end() const{
        return const_iterator(&this->root);
    }
	node                                                root;
    node*                                               tree;
	node*                                               first;
	node*                                               last;
	size_type                                           size;
	const Compare&                                      comp;
    typename Allocator::template rebind<node>::other    allocator;
};

#endif