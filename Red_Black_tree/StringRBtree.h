//
// Created by Rodya on 26.10.2021.
//

#ifndef RED_BLACK_TREE_STRINGRBTREE_H
#define RED_BLACK_TREE_STRINGRBTREE_H

#include <string>

class StringRBtree {
private:

	enum class Color {
		RED, BLACK
	};

	struct Node {
		std::string data;
		Color color = Color::RED;

		Node *left = nullptr, *right = nullptr, *parent = nullptr;

		explicit Node(const std::string &item) : data(item) {}
	};

	Color getColor(Node* node) const {
		if (node == nullptr)
			return Color::BLACK;
		return node->color;
	}

	void setColor(Node* node, Color color) {
		if (node == nullptr)
			return;
		node->color = color;
	}

	Node *root;

	void rotate_left(Node *&new_node) {
		Node *right_child = new_node->right;
		new_node->right = right_child->left;

		if (new_node->right != nullptr) {
			new_node->right->parent = new_node;
		}
		right_child->parent = new_node->parent;
		if (new_node->parent == nullptr) {
			root = right_child;
		}
		else if (new_node == new_node->parent->left) {
			new_node->parent->left = right_child;
		}
		else {
			new_node->parent->right = right_child;
		}
		right_child->left = new_node;
		new_node->parent = right_child;
	}

	void rotate_right(Node *&new_node) {
		Node *left_child = new_node->left;
		new_node->left = left_child->right;

		if (new_node->left != nullptr) {
			new_node->left->parent = new_node;
		}

		left_child->parent = new_node->parent;

		if (new_node->parent == nullptr) {
			root = left_child;
		}
		else if (new_node == new_node->parent->left) {
			new_node->parent->left = left_child;
		}
		else {
			new_node->parent->right = left_child;
		}

		left_child->right = new_node;
		new_node->parent = left_child;
	}

	Node *insert(Node *parent, Node *new_node) {
		if (parent == nullptr)
			return new_node;

		if (new_node->data < parent->data) {
			parent->left = insert(parent->left, new_node);
			parent->left->parent = parent;
		} else if (new_node->data > parent->data) {
			parent->right = insert(parent->right, new_node);
			parent->right->parent = parent;
		}

		return parent;
	}

	void insert_clean_up(Node *&node) {
		Node *parent = nullptr, *grandparent = nullptr, *uncle = nullptr;
		while (node != root && getColor(node) == Color::RED && getColor(node->parent) == Color::RED) {
			parent = node->parent;
			grandparent = parent->parent;
			if (parent == grandparent->left) {
				uncle = grandparent->right;
				if (getColor(uncle) == Color::RED) {
					setColor(uncle, Color::BLACK);
					setColor(parent, Color::BLACK);
					setColor(grandparent, Color::RED);
					node = grandparent;
				} else {
					if (node == parent->right) {
						rotate_left(parent);
						node = parent;
						parent = node->parent;
					}
					rotate_right(grandparent);
					std::swap(parent->color, grandparent->color);
					node = parent;
				}
			} else {
				uncle = grandparent->left;
				if (getColor(uncle) == Color::RED) {
					setColor(uncle, Color::BLACK);
					setColor(parent, Color::BLACK);
					setColor(grandparent, Color::RED);
					node = grandparent;
				} else {
					if (node == parent->left) {
						rotate_right(parent);
						node = parent;
						parent = node->parent;
					}
					rotate_left(grandparent);
					std::swap(parent->color, grandparent->color);
					node = parent;
				}
			}
		}
		setColor(root, Color::BLACK);
	}

	void erase_nodes(Node *node) {
		if (node != nullptr) {
			erase_nodes(node->left);
			erase_nodes(node->right);
			delete node;
		}
	}

	template<class Action>
	void direct_traversal(Node* node, Action on_each) {
		if (node == nullptr) return;

		on_each(node->data);
		direct_traversal(node->left, on_each);
		direct_traversal(node->right, on_each);
	}

	template<class Action>
	void direct_traversal(Node* node, Action on_each) const {
		if (node == nullptr) return;

		on_each(node->data);
		direct_traversal(node->left, on_each);
		direct_traversal(node->right, on_each);
	}

	template<class Action>
	void symmetrical_traversal(Node* node, Action on_each) {
		if (node == nullptr) return;

		symmetrical_traversal(node->left, on_each);
		on_each(node->data);
		symmetrical_traversal(node->right, on_each);
	}

	template<class Action>
	void symmetrical_traversal(Node* node, Action on_each) const {
		if (node == nullptr) return;

		symmetrical_traversal(node->left, on_each);
		on_each(node->data);
		symmetrical_traversal(node->right, on_each);
	}

	void concatenate_leaves(Node* node, std::string& result) const {
		if (node == nullptr) {
			return;
		} else if (node->left == nullptr && node->right == nullptr) {
			result += node->data + ", ";
		} else {
			concatenate_leaves(node->left, result);
			concatenate_leaves(node->right, result);
		}
	}

	void graphvizStr(Node *node, std::string &str) const {
		if (node == nullptr)
			return;

		if (node->left != nullptr) {
			str += "\"" + node->data + "\" -> \"" + node->left->data + "\";\n";
		} else {
			std::string null_node = "\"l_null_" + node->data + "\"";
			str += "\"" + node->data + "\" -> " + null_node + "; " + null_node + " [color = black];\n";
		}

		if (node->right != nullptr) {
			str += "\"" + node->data + "\" -> \"" + node->right->data + "\";\n";
		} else {
			std::string null_node = "\"r_null_" + node->data + "\"";
			str += "\"" + node->data + "\" -> " + null_node + "; " + null_node + " [color = black];\n";
		}

		if (node->color == Color::RED) {
			str += "\"" + node->data + "\"" + "[color = red];\n";
		}
		else {
			str += "\"" + node->data + "\"" + "[color = black];\n";
		}

		graphvizStr(node->left, str);
		graphvizStr(node->right, str);
	}

public:
	explicit StringRBtree(const std::string &root_data) {
		root = new Node(root_data);
		setColor(root, Color::BLACK);
	}

	explicit StringRBtree() {
		root = nullptr;
	}

	~StringRBtree() {
		erase_nodes(root);
	}

	void insert(const std::string &item) {
		Node *new_node = new Node(item);
		root = insert(root, new_node);
		insert_clean_up(new_node);
	}

	template<class Action>
	void direct_traversal(Action on_each) {
		if (root == nullptr) return;

		on_each(root->data);
		direct_traversal(root->left, on_each);
		direct_traversal(root->right, on_each);
	}

	template<class Action>
	void direct_traversal(Action on_each) const {
		if (root == nullptr) return;

		on_each(root->data);
		direct_traversal(root->left, on_each);
		direct_traversal(root->right, on_each);
	}

	template<class Action>
	void symmetrical_traversal(Action on_each) {
		if (root == nullptr) return;

		symmetrical_traversal(root->left, on_each);
		on_each(root->data);
		symmetrical_traversal(root->right, on_each);
	}

	template<class Action>
	void symmetrical_traversal(Action on_each) const {
		if (root == nullptr) return;

		symmetrical_traversal(root->left, on_each);
		on_each(root->data);
		symmetrical_traversal(root->right, on_each);
	}

	size_t height() const {
		size_t height = 0;
		if (root != nullptr) {
			for (Node* node = root; node->left != nullptr; node = node->left) {
				if (getColor(node) == Color::BLACK) {
					height++;
				}
			}
			height++;
		}
		return height;
	}

	std::string concatenate_leaves() const {
		std::string result;
		concatenate_leaves(root, result);
		return result;
	}

	std::string to_graphviz(const std::string& name = "RBtree") const {
		std::string result = "digraph " + name + " {\nnode [fontcolor = white; style = filled];\n";
		graphvizStr(root, result);
		result += "}";
		return result;
	}
};

#endif //RED_BLACK_TREE_STRINGRBTREE_H