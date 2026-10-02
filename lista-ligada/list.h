/*
 * list.h
 *
 * Lista ligada simple (Linked List) generica.
 * Operaciones: insertion, search, update, deleteAt y toString.
 */
#ifndef LIST_H_
#define LIST_H_

#include <string>
#include <sstream>

template <class T> class List;

/* Nodo de la lista */
template <class T>
class Link {
private:
	Link(T val) : value(val), next(0) {}
	Link(T val, Link<T> *nxt) : value(val), next(nxt) {}

	T value;
	Link<T> *next;

	friend class List<T>;
};

template <class T>
class List {
public:
	List();
	~List();

	void insertion(T val);
	int search(T val) const;
	void update(int pos, T val);
	T deleteAt(int pos);

	bool empty() const;
	int length() const;
	void clear();
	std::string toString() const;

private:
	// La lista maneja memoria dinamica; no se permite copiarla.
	List(const List<T> &);
	List<T>& operator=(const List<T> &);

	Link<T> *head;
	int size;
};

template <class T>
List<T>::List() : head(0), size(0) {}

template <class T>
List<T>::~List() {
	clear();
}

template <class T>
bool List<T>::empty() const {
	return head == 0;
}

template <class T>
int List<T>::length() const {
	return size;
}

/*
 * insertion
 * Inserta el elemento al final de la lista.
 * Pre: estructura valida. Post: estructura modificada.
 */
template <class T>
void List<T>::insertion(T val) {
	Link<T> *newLink = new Link<T>(val);

	if (empty()) {
		head = newLink;
	} else {
		Link<T> *p = head;
		while (p->next != 0) {
			p = p->next;
		}
		p->next = newLink;
	}
	size++;
}

/*
 * search
 * Regresa la posicion (base 0) de la primera ocurrencia de val,
 * o -1 si no existe.
 */
template <class T>
int List<T>::search(T val) const {
	Link<T> *p = head;
	int pos = 0;

	while (p != 0) {
		if (p->value == val) {
			return pos;
		}
		p = p->next;
		pos++;
	}
	return -1;
}

/*
 * update
 * Cambia el valor del elemento en la posicion pos (base 0).
 * Si la posicion no es valida la lista no cambia.
 */
template <class T>
void List<T>::update(int pos, T val) {
	if (pos < 0 || pos >= size) {
		return;
	}

	Link<T> *p = head;
	for (int i = 0; i < pos; i++) {
		p = p->next;
	}
	p->value = val;
}

/*
 * deleteAt
 * Elimina el elemento en la posicion pos (base 0) y regresa su valor.
 * Si la posicion no es valida la lista no cambia y se regresa T().
 */
template <class T>
T List<T>::deleteAt(int pos) {
	if (pos < 0 || pos >= size) {
		return T();
	}

	Link<T> *p = head;
	T val;

	if (pos == 0) {
		head = p->next;
	} else {
		Link<T> *prev = head;
		for (int i = 0; i < pos - 1; i++) {
			prev = prev->next;
		}
		p = prev->next;
		prev->next = p->next;
	}

	val = p->value;
	delete p;
	size--;
	return val;
}

template <class T>
void List<T>::clear() {
	Link<T> *p = head;

	while (p != 0) {
		Link<T> *nxt = p->next;
		delete p;
		p = nxt;
	}
	head = 0;
	size = 0;
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

#endif /* LIST_H_ */
