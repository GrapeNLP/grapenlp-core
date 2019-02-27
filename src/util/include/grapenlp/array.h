/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2019 Javier Miguel Sastre Martínez <javier.sastre@telefonica.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *
 */

/*
 *  @author Javier Sastre
 */

#ifndef GRAPENLP_ARRAY_H
#define GRAPENLP_ARRAY_H

#include <stdexcept>

#include <array>

#include <grapenlp/iostream.h>
#include <grapenlp/algorithm.h>

namespace grapenlp {
    template<typename T>
    class array {
    public:
        // type definitions
        typedef T value_type;
        typedef T *iterator;
        typedef const T *const_iterator;
        typedef T &reference;
        typedef const T &const_reference;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        T *elems;    //array of elements of type T
        size_type count;

        array() : elems(nullptr), count(0) {}

        template<std::size_t N>
        array(const T (&elems_)[N]): elems(new T[N]), count(N) { std::copy(elems_, elems_ + N, elems); }

        array(T *elems_, size_type count_) : elems(elems_), count(count_) {}

        array(std::pair<T *, size_type> elems_x_count) : elems(elems_x_count.first), count(elems_x_count.second) {}

/*		array(const T* elems_, size_type count_): elems(new T[count_]), count(count_)
		{
			size_type i;
			for (i = 0; i < count_; ++i)
				elems[i] = elems_[i];
		}*/

        template<typename Function>
        array(const T *elems_, size_type count_, Function f): elems(new T[count_]), count(count_) {
            std::transform(elems_, elems_ + count_, elems, f);
        }

        array(size_type count_) : elems(new T[count_]), count(count_) {}

        array(const T &elem, size_type count_) : elems(new T[count_]), count(count_) {
            iterator i(begin());
            for (; i != end(); ++i)
                *i = elem;
        }

        array(const array<T> &a) : elems(new T[a.size()]), count(a.size()) { std::copy(a.begin(), a.end(), begin()); }

        array(array<T> &&a) : elems(a.elems), count(a.count) {
            a.elems = nullptr;
            a.count = 0;
        }

        template<typename Function>
        array(const array<T> &a, Function f): elems(new T[a.size()]), count(a.size()) {
            std::transform(a.begin(), a.end(), elems, f);
        }

        template<std::size_t N>
        array(const std::array <T, N> &a): elems(new T[N]), count(N) { std::copy(a.begin(), a.end(), begin()); }

        array(const array<T> &a, const T &t) : elems(new T[a.size() + 1]), count(a.size() + 1) {
            std::copy(a.begin(), a.end(), begin());
            elems[a.size()] = t;
        }

        array(const array<T> &a, const array<T> &b) : elems(new T[a.size() + b.size()]), count(a.size() + b.size()) {
            std::copy(a.begin(), a.end(), begin());
            std::copy(b.begin(), b.end(), begin() + a.size());
        }

        template<typename Iterator>
        array(Iterator a_begin, Iterator a_end): elems(new T[a_end - a_begin]), count(a_end - a_begin) {
            std::copy(a_begin, a_end, begin());
        }

        template<typename Iterator>
        array(Iterator seq_begin, Iterator seq_end, std::size_t count_): elems(new T[count_]), count(count_) {
            std::copy(seq_begin, seq_end, begin());
        }

        template<typename Iterator, typename Function>
        array(Iterator seq_begin, Iterator seq_end, std::size_t count_, Function f): elems(new T[count_]),
                                                                                     count(count_) {
            std::transform(seq_begin(), seq_end(), elems, f);
        }

        //Concatenation-with-sequence constructor
        template<typename Iterator>
        array(const array<T> &a, Iterator b_begin, Iterator b_end): elems(new T[a.size() + b_end - b_begin]),
                                                                    count(a.size() + b_end - b_begin) {
            std::copy(b_begin, b_end, std::copy(a.begin(), a.end(), begin()));
        }

        //Reverse concatenation-with-sequence constructor
        template<typename Iterator>
        array(Iterator b_begin, Iterator b_end, const array<T> &a): elems(new T[a.size() + b_end - b_begin]),
                                                                    count(a.size() + b_end - b_begin) {
            std::copy(a.begin(), a.end(), std::copy(b_begin, b_end, begin()));
        }

        array &reset() {
            if (elems) delete[] elems;
            elems = nullptr;
            count = 0;
            return *this;
        }

        template<std::size_t N>
        array &reset(const T (&elems_)[N]) {
            if (elems) delete[] elems;
            elems = new T[N];
            count = N;
            std::copy(elems_, elems_ + N, elems);
            return *this;
        }

        array &reset(T *elems_, size_type count_) {
            if (elems) delete[] elems;
            elems = elems_;
            count = count_;
            return *this;
        }

        array &reset(std::pair<T *, size_type> elems_x_count) {
            if (elems) delete[] elems;
            elems = elems_x_count.first;
            count = elems_x_count.second;
            return *this;
        }

        array &reset(const T *elems_, size_type count_) {
            if (elems) delete[] elems;
            elems = new T[count_];
            count = count_;
            std::copy(elems_, elems_ + count_, elems);
            return *this;
        }

        template<typename Function>
        array &reset(const T *elems_, size_type count_, Function f) {
            if (elems) delete[] elems;
            elems = new T[count_];
            count = count_;
            std::transform(elems_, elems_ + count_, elems, f);
            return *this;
        }

        array &reset(size_type count_) {
            if (elems) delete[] elems;
            elems = new T[count_];
            count = count_;
            return *this;
        }

        array &reset(const T &elem, size_type count_) {
            if (elems) delete[] elems;
            elems = new T[count_];
            count = count_;
            iterator i(begin());
            for (; i != end(); ++i)
                *i = elem;
            return *this;
        }

        array &reset(const array<T> &a) {
            if (elems) delete[] elems;
            elems = new T[a.size()];
            count = a.size();
            std::copy(a.begin(), a.end(), begin());
            return *this;
        }

        template<typename Function>
        array &reset(const array<T> &a, Function f) {
            if (elems) delete[] elems;
            elems = new T[a.size()];
            count = a.size();
            std::transform(a.begin(), a.end(), elems, f);
            return *this;
        }

        template<std::size_t N>
        array &reset(const std::array <T, N> &a) {
            if (elems) delete[] elems;
            elems = new T[N];
            count = N;
            std::copy(a.begin(), a.end(), begin());
            return *this;
        }

        array &reset(const array<T> &a, const T &t) {
            if (elems) delete[] elems;
            elems = new T[a.size() + 1];
            count = a.size() + 1;
            std::copy(a.begin(), a.end(), begin());
            elems[a.size()] = t;
            return *this;
        }

        array &reset(const array<T> &a, const array<T> &b) {
            if (elems) delete[] elems;
            elems = new T[a.size() + b.size()];
            count = a.size() + b.size();
            std::copy(a.begin(), a.end(), begin());
            std::copy(b.begin(), b.end(), begin() + a.size());
            return *this;
        }

        template<typename Iterator>
        array &reset(Iterator a_begin, Iterator a_end) {
            if (elems) delete[] elems;
            elems = new T[a_end - a_begin];
            count = a_end - a_begin;
            std::copy(a_begin, a_end, begin());
            return *this;
        }

        ~array() {
            if (elems) delete[] elems;
        }

        // iterator support
        iterator begin() { return elems; }

        const_iterator begin() const { return elems; }

        iterator end() { return elems + count; }

        const_iterator end() const { return elems + count; }

        // reverse iterator support
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        reverse_iterator rbegin() { return reverse_iterator(end()); }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() { return reverse_iterator(begin()); }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }

        // operator[]
        reference operator[](size_type i) {
            return elems[i];
        }

        const_reference operator[](size_type i) const {
            return elems[i];
        }

        // at() with range check
        reference at(size_type i) {
            rangecheck(i);
            return elems[i];
        }

        const_reference at(size_type i) const {
            rangecheck(i);
            return elems[i];
        }

        // front() and back()
        reference front() {
            return elems[0];
        }

        const_reference front() const {
            return elems[0];
        }

        reference back() {
            return elems[count - 1];
        }

        const_reference back() const {
            return elems[count - 1];
        }

        array<T> substr(std::size_t i, std::size_t j) const { return array(begin() + i, begin() + j); }

        array<T> substr(std::size_t i) { return array(begin() + i, end()); }

        array<T> prefix() const { return substr(0, count - 1); }

        // size is constant
        size_type size() const { return count; }

        bool empty() const { return size() == 0; }

        size_type max_size() const { return size(); }

        // swap (note: constant complexity)
        void swap(array<T> &y) {
            T *elems_aux(elems);
            std::size_t count_aux(count);
            elems = y.elems;
            count = y.count;
            y.elems = elems_aux;
            y.count = count_aux;
        }

        // direct access to data (read-only)
        const T *data() const { return elems; }

        // size is constant
        size_type size_in_bytes() const { return count * sizeof(T); }

        // direct access to data bytes (read-only)
        const unsigned char *get_bytes() const { return reinterpret_cast<const unsigned char *>(elems); }

        // direct bytes write to data bytes
        void set_bytes(unsigned char *bytes) { elems = reinterpret_cast<T *>(bytes); }

        // use array as C array (direct read/write access to data)
        T *c_array() { return elems; }

        const T *c_array() const { return elems; }

        // assignment with type conversion
        array<T> &operator=(const array<T> &rhs) {
            reset(rhs.count);
            std::copy(rhs.begin(), rhs.end(), begin());
            return *this;
        }

        // assignment with type conversion
        array<T> &operator=(T const *const rhs) {
            size_type i;
            for (i = 0; i < count; ++i)
                elems[i] = rhs[i];
            return *this;
        }

        // assign one value to all elements
        void assign(const T &value) {
            std::fill_n(begin(), size(), value);
        }

        // check range
        void rangecheck(size_type i) {
            if (i >= size()) {
                throw std::range_error("array<>: index out of range");
            }
        }

        array<T> &append(const T &e) {
            array<T> a(*this + e);
            this->swap(a);
            return *this;
        }

        array<T> &concat(const array<T> &a) {
            array<T> b(*this, a);
            this->swap(b);
            return *this;
        }

        template<typename Iterator>
        array<T> &concat(Iterator begin, Iterator end) {
            array<T> b(*this, begin, end);
            this->swap(b);
            return *this;
        }

        template<typename Iterator>
        array<T> &cconcat(Iterator begin, Iterator end) {
            array<T> b(begin, end, *this);
            this->swap(b);
            return *this;
        }

        std::ptrdiff_t compare_3w(const array<T> &a) const {
            return lexicographical_compare_3way(begin(), end(), a.begin(), a.end());
        }
    };

    template<typename T>
    class ptr_array : public array<T *> {
    public:
        typedef array<T *> base_type;
        typedef typename base_type::value_type value_type;
        typedef typename base_type::iterator iterator;
        typedef typename base_type::const_iterator const_iterator;
        typedef typename base_type::reference reference;
        typedef typename base_type::const_reference const_reference;
        typedef typename base_type::size_type size_type;
        typedef typename base_type::difference_type difference_type;

        ptr_array() : base_type() {}

        ptr_array(size_type count_) : array<T *>(count_) {}

        ~ptr_array() {
            if (base_type::elems) {
                iterator i;
                for (i = this->begin(); i != this->end(); ++i)
                    delete *i;
            }
        }
    };

    // comparisons
    template<typename T>
    bool operator==(const array<T> &x, const array<T> &y) {
        if (x.count != y.count)
            return false;
        return std::equal(x.begin(), x.end(), y.begin());
    }

    template<typename T>
    bool operator<(const array<T> &x, const array<T> &y) {
        return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
    }

    template<typename T>
    bool operator!=(const array<T> &x, const array<T> &y) {
        return !(x == y);
    }

    template<typename T>
    bool operator>(const array<T> &x, const array<T> &y) {
        return y < x;
    }

    template<typename T>
    bool operator<=(const array<T> &x, const array<T> &y) {
        return !(y < x);
    }

    template<typename T>
    bool operator>=(const array<T> &x, const array<T> &y) {
        return !(x < y);
    }

    template<typename T>
    array<T> operator+(const array<T> &a, const array<T> &b) {
        return array<T>(a, b);
    }

    template<typename T>
    array<T> operator+(const array<T> &a, const T &b) {
        return array<T>(a, b);
    }

    template<typename T, typename CharT, typename Traits>
    std::basic_istream<CharT, Traits> &operator>>(std::basic_istream<CharT, Traits> &input, array<T> &a) {
        typename array<T>::const_iterator i;
        for (i = a.begin(); i < a.end(); ++i)
            input >> *i;
        return input;
    }

    template<typename T, typename CharT, typename Traits>
    std::basic_ostream<CharT, Traits> &operator<<(std::basic_ostream<CharT, Traits> &out, const array<T> &a) {
        typename array<T>::const_iterator i;
        for (i = a.begin(); i < a.end(); ++i)
            out << *i;
        return out;
    }

    // global swap()
    template<typename T>
    void swap(array<T> &x, array<T> &y) {
        x.swap(y);
    }

    template<typename T>
    struct array_appender {
        array<T> &operator()(array<T> &a, const T &e) const { return a.append(e); }
    };

    template<typename T>
    struct array_concatenator {
        array<T> &operator()(array<T> &a, const array<T> &b) const { return a.concat(b); }
    };

    template<typename T>
    struct array_deref_appender {
        array<T> &operator()(array<T> &a, const T *e) const { return a.append(*e); }

        template<typename SourceRef>
        array<T> &operator()(array<T> &a, SourceRef src_ref, const T *e) const { return a.append(*e); }
    };

    template<typename T, typename Sequence>
    struct array_and_deref_sequence_concatenator {
        array<T> &operator()(array<T> &a, const Sequence *seq) const {
            return a.concat(seq->begin(), seq->end());
        }

        template<typename SourceRef>
        array<T> &operator()(array<T> &a, SourceRef src_ref, const Sequence *seq) const {
            return a.concat(seq->begin(), seq->end());
        }
    };

    template<typename T, typename Sequence>
    struct array_and_deref_sequence_converse_concatenator {
        array<T> &operator()(array<T> &a, const Sequence *seq) const {
            return a.cconcat(seq->begin(), seq->end());
        }

        template<typename SourceRef>
        array<T> &operator()(array<T> &a, SourceRef src_ref, const Sequence *seq) const {
            return a.cconcat(seq->begin(), seq->end());
        }
    };

    template<typename T>
    struct array_and_array_concatenator {
        array<T> &operator()(array<T> &a, const array<T> &b) const { return a.concat(b); }

        template<typename SourceRef>
        array<T> &operator()(array<T> &a, SourceRef src_ref, const array<T> &b) const { return a.concat(b); }
    };
} //namespace grapenlp

#endif /*GRAPENLP_ARRAY_H*/
