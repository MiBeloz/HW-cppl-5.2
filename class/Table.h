#pragma once


template<class T>
class Table {
public:
	Table(const size_t row, const size_t col);

	T*& operator[](const size_t i);
	const T*& operator[](const size_t i) const;
	
	size_t size() const;
	
	~Table();
	
private:
	size_t m_col;
	size_t m_row;
	T** m_array;
};


template<class T>
Table<T>::Table(const size_t row, const size_t col) {
	if (row > ULONG_MAX || col > ULONG_MAX) {
		throw std::runtime_error("table is too long");
	}
	m_row = row;
	m_col = col;
	m_array = new T*[m_row]{};
	for (size_t i = 0; i < m_row; ++i) {
		m_array[i] = new T[m_col]{};
	}
}

template<class T>
T*& Table<T>::operator[](const size_t i) {
	if (i >= m_row) {
		throw std::runtime_error("out of range");
	}
	return m_array[i];
}

template<class T>
const T*& Table<T>::operator[](const size_t i) const {
	std::cout << "const";
	return m_array[i];
}

template<class T>
size_t Table<T>::size() const {
	return m_row * m_col;
}

template<class T>
Table<T>::~Table() {
	for (size_t i = 0; i < m_row; ++i) {
		delete[] m_array[i];
	}
	delete[] m_array;
}
