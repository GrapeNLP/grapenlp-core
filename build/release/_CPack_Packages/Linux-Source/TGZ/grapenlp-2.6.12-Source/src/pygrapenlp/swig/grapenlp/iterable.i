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

%module iterable

%include "exception.i"

%define ITERABLE(Collection, Element, Iterator, StopIterator)
%inline %{
class StopIterator {};
class Iterator {
  public:
    Iterator(typename Collection::iterator _cur, typename Collection::iterator _end) : cur(_cur), end(_end) {}
    Iterator* __iter__()
    {
      return this;
    }
    typename Collection::iterator cur;
    typename Collection::iterator end;
  };
%}


%exception Iterator::next {
  try
  {
    $action // calls %extend function next() below
  }
  catch (StopIterator)
  {
    PyErr_SetString(PyExc_StopIteration, "End of iterator");
    return NULL;
  }
}

%extend Iterator
{
  Element& next()
  {
    if ($self->cur != $self->end)
    {
      // dereference the iterator and return reference to the object,
      // after that it increments the iterator
      return *$self->cur++;
    }
    throw StopIterator();
  }
}

%extend Collection {
  Iterator __iter__()
  {
    // return a constructed Iterator object
    return Iterator($self->begin(), $self->end());
  }
};
%enddef

%define CONST_ITERABLE(Collection, Element, Iterator, StopIterator)
%inline %{
class StopIterator {};
class Iterator {
  public:
    Iterator(typename Collection::const_iterator _cur, typename Collection::const_iterator _end) : cur(_cur), end(_end) {}
    Iterator* __iter__()
    {
      return this;
    }
    typename Collection::const_iterator cur;
    typename Collection::const_iterator end;
  };
%}


%exception Iterator::next {
  try
  {
    $action // calls %extend function next() below
  }
  catch (StopIterator)
  {
    PyErr_SetString(PyExc_StopIteration, "End of iterator");
    return NULL;
  }
}

%extend Iterator
{
  const Element next()
  {
    if ($self->cur != $self->end)
    {
      // dereference the iterator and return reference to the object,
      // after that it increments the iterator
      return *$self->cur++;
    }
    throw StopIterator();
  }
}

%extend Collection {
  Iterator __iter__()
  {
    // return a constructed Iterator object
    return Iterator($self->begin(), $self->end());
  }
};
%enddef
