#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
using namespace std;

struct Node {
	int value;
	Node* next;

	Node() : value(0), next(nullptr) {

	}
	Node(int value, Node* next) : value(value), next(next) {

	}
};

class AbstractContainer {
public:
	virtual int Size() const = 0;
	virtual bool IsEmpty() const = 0;
private:

};

class AbstractQueue : public AbstractContainer {
public:
	virtual void PushBack(int value) = 0;
	virtual void PopFront() = 0;
	virtual int Front() const = 0;
	virtual void Front(int value) = 0;
private:

};

class AbstractStack : public AbstractContainer {
public:
	virtual void Push(int value) = 0;
	virtual void Pop() = 0;
	virtual int Top() const = 0;
	virtual void Top(int value) = 0;
private:

};

class ArrayQueue : public AbstractQueue {
public:
	ArrayQueue() : size_(0), arr_(nullptr) {

	}
	ArrayQueue(int size, int value) : size_(size) {
		arr_ = new int[size];
		for (int i = 0; i < size; i++) {
			arr_[i] = value;
		}
	}
	ArrayQueue(const ArrayQueue& other) : size_(other.size_) {
		arr_ = new int[other.size_];
		for (int i = 0; i < size_; i++) {
			arr_[i] = other.arr_[i];
		}
	}
	ArrayQueue(ArrayQueue&& other) {
		arr_ = other.arr_;
		other.arr_ = nullptr;
		size_ = other.size_;
		other.size_ = 0;
	}
	~ArrayQueue() {
		delete[] arr_;
	}

	ArrayQueue& operator= (ArrayQueue& other) {
		if (this != &other) {
			delete[] arr_;
			arr_ = new int[other.size_];
			size_ = other.size_;
			for (int i = 0; i < other.size_; i++) {
				arr_[i] = other.arr_[i];
			}
		}
		return *this;
	}
	ArrayQueue& operator= (ArrayQueue&& other) {
		if (this != &other) {
			delete[] arr_;
			arr_ = other.arr_;
			size_ = other.size_;
			other.arr_ = nullptr;
			other.size_ = 0;
		}
		return *this;
	}

	int Size() const override {
		return size_;
	}
	bool IsEmpty() const override {
		return size_ == 0;
	}
	void PushBack(int value) override {
		int* new_arr = new int[size_ + 1];
		for (int i = 0; i < size_; i++) {
			new_arr[i] = arr_[i];
		}
		new_arr[size_] = value;
		delete[] arr_;
		arr_ = new_arr;
		size_++;
	}
	void PopFront() override {
		int* new_arr = new int[size_ - 1];
		for (int i = 0; i < size_ - 1; i++) {
			new_arr[i] = arr_[i + 1];
		}
		delete[] arr_;
		arr_ = new_arr;
		size_--;
	}
	int Front() const override {
		if (IsEmpty()) {
			throw runtime_error("No front element: array is empty");
		}
		return arr_[size_ - 1];
	}
	void Front(int value) override {
		arr_[size_ - 1] = value;
	}
private:
	int size_;
	int* arr_;
};

/*

class ListQueue : public AbstractQueue {
public:

private:

};

*/

class LimitedArrayStack : public AbstractStack {
public:
	LimitedArrayStack(int limit) : size_(limit),  limit_size_(limit) {
		lim_arr_ = new int[limit];
	}
	LimitedArrayStack(int size, int value) : size_(size), limit_size_(size) {
		lim_arr_ = new int[size];
		for (int i = 0; i < size; i++) {
			lim_arr_[i] = value;
		}
	}
	LimitedArrayStack(const LimitedArrayStack& other) : limit_size_(other.limit_size_), size_(other.size_) {
		lim_arr_ = new int[other.limit_size_];
		for (int i = 0; i < size_; i++) { 
			lim_arr_[i] = other.lim_arr_[i];
		}
	}
	LimitedArrayStack(LimitedArrayStack&& other) {
		lim_arr_ = other.lim_arr_;
		other.lim_arr_ = nullptr;
		limit_size_ = other.limit_size_;
		other.limit_size_ = 0;
		size_ = other.size_;
		other.size_ = 0;
	}
	~LimitedArrayStack() {
		delete[] lim_arr_;
	}

	LimitedArrayStack& operator= (LimitedArrayStack& other) {
		if (this != &other) {
			delete[] lim_arr_;
			lim_arr_ = new int[other.limit_size_];
			limit_size_ = other.limit_size_;
			size_ = other.size_;
			for (int i = 0; i < other.size_; i++) {
				lim_arr_[i] = other.lim_arr_[i];
			}
		}
		return *this;
	}
	LimitedArrayStack& operator= (LimitedArrayStack&& other) {
		if (this != &other) {
			delete[] lim_arr_;
			lim_arr_ = other.lim_arr_;
			other.lim_arr_ = nullptr;
			limit_size_ = other.limit_size_;
			other.limit_size_ = 0;
			size_ = other.size_;
			other.size_ = 0;
		}
		return *this;
	}


	int Size() const override {
		return size_;
	}
	bool IsEmpty() const override {
		return size_ == 0;
	}
	void Push(int value) override {
		if (size_ == limit_size_) {
			throw runtime_error("Limit is riched");
		}
		lim_arr_[size_] = value;
		size_++;
	}
	void Pop() override {
		if (IsEmpty()) {
			throw runtime_error("Cant pop: array is empty");
		}
		size_--;
	}
	int Top() const override {
		if (IsEmpty()) {
			throw runtime_error("No top element: array is empty");
		}
		return lim_arr_[size_ - 1];
	}
	void Top(int value) override {
		lim_arr_[size_ - 1] = value;
	}
private:
	int limit_size_;
	int size_;
	int* lim_arr_;
};

class UnlimitedArrayStack : public AbstractStack {
public:
	UnlimitedArrayStack() : size_(0), unlim_arr_(nullptr) {

	}
	UnlimitedArrayStack(int size, int value) : size_(size) {
		unlim_arr_ = new int[size];
		for (int i = 0; i < size; i++) {
			unlim_arr_[i] = value;
		}
	}
	UnlimitedArrayStack(const UnlimitedArrayStack& other) : size_(other.size_) {
		unlim_arr_ = new int[other.size_];
		for (int i = 0; i < size_; i++) {
			unlim_arr_[i] = other.unlim_arr_[i];
		}
	}
	UnlimitedArrayStack(UnlimitedArrayStack&& other) {
		unlim_arr_ = other.unlim_arr_;
		other.unlim_arr_ = nullptr;
		size_ = other.size_;
		other.size_ = 0;
	}
	~UnlimitedArrayStack() {
		delete[] unlim_arr_;
	}

	UnlimitedArrayStack& operator= (UnlimitedArrayStack& other) {
		if (this != &other) {
			delete[] unlim_arr_;
			unlim_arr_ = new int[other.size_];
			size_ = other.size_;
			for (int i = 0; i < other.size_; i++) {
				unlim_arr_[i] = other.unlim_arr_[i];
			}
		}
		return *this;
	}
	UnlimitedArrayStack& operator= (UnlimitedArrayStack&& other) {
		if (this != &other) {
			delete[] unlim_arr_;
			unlim_arr_ = other.unlim_arr_;
			other.unlim_arr_ = nullptr;
			size_ = other.size_;
			other.size_ = 0;
		}
		return *this;
	}

	int Size() const override {
		return size_;
	}
	bool IsEmpty() const override {
		return size_ == 0;
	}
	void Push(int value) override {
		int* new_unlim_arr = new int[size_ + 1];
		for (int i = 0; i < size_; i++) {
			new_unlim_arr[i] = unlim_arr_[i];
		}
		new_unlim_arr[size_] = value;
		delete[] unlim_arr_;
		unlim_arr_ = new_unlim_arr;
		size_++;
	}
	void Pop() override {
		if (IsEmpty()) {
			throw runtime_error("Cant pop: array is empty");
		}
		int* new_unlim_arr = new int[size_ - 1];
		for (int i = 0; i < size_ - 1; i++) {
			new_unlim_arr[i] = unlim_arr_[i];
		}
		delete[] unlim_arr_;
		unlim_arr_ = new_unlim_arr;
		size_--;
	}
	int Top() const override {
		if (IsEmpty()) {
			throw runtime_error("No top element: array is empty");
		}
		return unlim_arr_[size_ - 1];
	}
	void Top(int value) override {
		unlim_arr_[size_ - 1] = value;
	}
private:
	int size_;
	int* unlim_arr_;
};

class ListStack : public AbstractStack {
public:
	ListStack() : head_(nullptr) {

	}
	ListStack(int size, int value) {
		if (size != 0) {
			head_->value = value;
			head_->next = nullptr;
			for (int i = 1; i < size; i++) {
				AppendForStack(value);
			}
		} else {
			head_ = nullptr;
		}
	}
	ListStack(ListStack& other) : size_(other.size_) {
		if (other.size_ != 0) {
			head_->value = other.head_->value;
			head_->next = nullptr;
			for (int i = 1; i < other.size_; i++) {
				Node* new_node = other.head_;
				for (int j = 0; j < i; j++) {
					new_node = new_node->next;
				}
				AppendForStack(new_node->value);
			}
		}
		else {
			head_ = nullptr;
		}
	}
	ListStack(ListStack&& other) {
		if (other.size_ != 0) {
			Node* new_head;
			new_head->next = other.head_->next;
			new_head->value = other.head_->value;
			head_ = new_head;
			/*
				other.head_->next = nullptr;
				other.head_->value = 0;
			*/

			other.head_ = nullptr;
		}
		else {
			head_ = nullptr;
		}
	}
	~ListStack() {
		for (int i = 1; i < size_; i++) {
			Node* new_node = head_;
			for (int j = 0; j < i; j++) {
				new_node = new_node->next;
			}
			delete new_node;
		}
	}


	void Push(int value) override {
		AppendForStack(value);
	}
	void Pop() override {
		Node* new_head;
		new_head = head_->next;
		delete head_;
		head_ = new_head;
	}
	void Top(int value) override {
		head_->value = value;
	}
	int Top() const override {
		return head_->value;
	}

private:
	Node* head_;
	int size_;

	void Append(int value) {
		Node* new_node;
		new_node = head_;
		while (new_node->next != nullptr) {
			new_node = new_node->next;
		}
		Node* new_element;
		new_node->next = new_element;
		new_element->value = value;
		new_element->next = nullptr;
	}

	void AppendForStack(int value) {
		Node* new_node;
		new_node->next = head_;
		new_node->value = value;
		head_ = new_node;
	}
};

int main() {

	AbstractStack* st = new UnlimitedArrayStack;

	return 0;
}