#pragma once


//TABLE_VARIANT 0 - с вспомогательным классом 'RowProxy'
//TABLE_VARIANT 1 - без вспомогательного класса 'RowProxy'(требование ДЗ)
#define TABLE_VARIANT 0

#if TABLE_VARIANT

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
	m_array = new T * [m_row] {};
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
	if (i >= m_row) {
		throw std::runtime_error("out of range");
	}
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
	m_array = nullptr;
}

#else

template<typename T>
class Table {
public:
	Table(const size_t row, const size_t col);

	class RowProxy;
	RowProxy operator[](const size_t i);
	const RowProxy operator[](const size_t i) const;

	size_t size() const;

	~Table();

	class RowProxy {
	public:
		RowProxy(T* data, const size_t size) : m_data(data), m_size(size) {}

		T& operator[](const size_t j);
		const T& operator[](const size_t j) const;

	private:
		T* m_data;
		size_t m_size;
	};

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
	m_array = new T * [m_row] {};
	for (size_t i = 0; i < m_row; ++i) {
		m_array[i] = new T[m_col]{};
	}
}
template<class T>
typename Table<T>::RowProxy Table<T>::operator[](const size_t i) {
	if (i >= m_row) {
		throw std::runtime_error("out of range");
	}
	return RowProxy(m_array[i], m_col);
}

template<class T>
const typename Table<T>::RowProxy Table<T>::operator[](const size_t i) const {
	if (i >= m_row) {
		throw std::runtime_error("out of range");
	}
	return RowProxy(m_array[i], m_col);
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
	m_array = nullptr;
}

template<class T>
T& Table<T>::RowProxy::operator[](const size_t j) {
	if (j >= m_size) {
		throw std::runtime_error("out of range");
	}
	return m_data[j];
}

template<class T>
const T& Table<T>::RowProxy::operator[](const size_t j) const {
	if (j >= m_size) {
		throw std::runtime_error("out of range");
	}
	return m_data[j];
}

#endif // TABLE_VARIANT