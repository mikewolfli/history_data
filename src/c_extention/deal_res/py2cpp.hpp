/*
  Modify from https://github.com/dubzzz/Py2Cpp

*/
#ifndef __PY2CPP_HPP__
#define __PY2CPP_HPP__

#include <cassert>
#include <climits>
#include <sstream>
#include <stdexcept>
#include <typeinfo>

#include <map>
#include <set>
#include <string>
#include <tuple>
#include <ctime>
#include <vector>

#include <Python.h>
#include <datetime.h>

namespace dubzzz {
namespace Py2Cpp {

template <class T>
struct CppBuilder;

template <>
struct CppBuilder<PyObject*>
{
  PyObject* operator() (PyObject* pyo)
  {
    assert(pyo);
    return pyo;
  }
};

template <>
struct CppBuilder<bool>
{
  bool operator() (PyObject* pyo)
  {
    assert(pyo);
    if (PyBool_Check(pyo))
    {
      return pyo == Py_True;
    }
    throw std::invalid_argument("Not a PyBool instance");
  }
};


template <>
struct CppBuilder<int>
{
  int operator() (PyObject* pyo)
  {
    assert(pyo);
    if (PyLong_Check(pyo))
    {
      long v { PyLong_AsLong(pyo) };
      if (v < INT_MIN || v > INT_MAX)
      {
        throw std::overflow_error("Out of <int> boundaries");
      }
      return static_cast<int>(v);
    }
#if PY_MAJOR_VERSION <=2
    else if (PyInt_Check(pyo))
    {
      long v { PyInt_AS_LONG(pyo) };
      if (v < INT_MIN || v > INT_MAX)
      {
        throw std::overflow_error("Out of <int> boundaries");
      }
      return static_cast<int>(v);
    }
#endif // PY_MAJOR_VERSION
    throw std::invalid_argument("Not a PyLong instance");
  }
};

template <>
struct CppBuilder<unsigned int>
{
  unsigned int operator() (PyObject* pyo)
  {
    assert(pyo);
    if (PyLong_Check(pyo))
    {
      unsigned long v { PyLong_AsUnsignedLongMask(pyo) };
      if (v > UINT_MAX)
      {
        throw std::overflow_error("Out of <unsigned int> boundaries");
      }
      return static_cast<unsigned int>(v);
    }
#if PY_MAJOR_VERSION <=2
    else if (PyInt_Check(pyo))
    {
      unsigned long v { PyInt_AsUnsignedLongMask(pyo) };
      if (v > UINT_MAX)
      {
        throw std::overflow_error("Out of <unsigned int> boundaries");
      }
      return static_cast<int>(v);
    }
#endif // PY_MAJOR_VERSION
    throw std::invalid_argument("Not a PyLong instance");
  }
};

template <>
struct CppBuilder<long>
{
  long operator() (PyObject* pyo)
  {
    assert(pyo);
    if (PyLong_Check(pyo))
    {
      return PyLong_AsLong(pyo);
    }
#if PY_MAJOR_VERSION <=2
    else if (PyInt_Check(pyo))
    {
      return PyInt_AS_LONG(pyo);
    }
#endif // PY_MAJOR_VERSION
   /* else  if(PyDate_Check(pyo))
    {
            struct tm tim;

            tim.tm_year = PyDateTime_GET_YEAR(pyo) ;
            tim.tm_mon = PyDateTime_GET_MONTH(pyo) ;
            tim.tm_mday = PyDateTime_GET_DAY(pyo) ;

            std::time_t date_res= mktime(&tim);
            return date_res;
    }*/
    throw std::invalid_argument("Not a PyLong instance");

  }
};

template <>
struct CppBuilder<unsigned long>
{
  unsigned long operator() (PyObject* pyo)
  {
    assert(pyo);
    if (PyLong_Check(pyo))
    {
      return PyLong_AsUnsignedLong(pyo);
    }
#if PY_MAJOR_VERSION <=2
    else if (PyInt_Check(pyo))
    {
      return PyInt_AsUnsignedLongMask(pyo);
    }
#endif // PY_MAJOR_VERSION
    throw std::invalid_argument("Not a PyLong instance");
  }
};

template <>
struct CppBuilder<long long>
{
  long long operator() (PyObject* pyo)
  {
    assert(pyo);
    if (PyLong_Check(pyo))
    {
      return PyLong_AsLongLong(pyo);
    }
#if PY_MAJOR_VERSION <=2
    else if (PyInt_Check(pyo))
    {
      return PyInt_AS_LONG(pyo);
    }
#endif // PY_MAJOR_VERSION
    throw std::invalid_argument("Not a PyLong instance");
  }
};

template <>
struct CppBuilder<unsigned long long>
{
  unsigned long long operator() (PyObject* pyo)
  {
    assert(pyo);
    if (PyLong_Check(pyo))
    {
      return PyLong_AsUnsignedLongLong(pyo);
    }
#if PY_MAJOR_VERSION <=2
    else if (PyInt_Check(pyo))
    {
      return PyInt_AsUnsignedLongLongMask(pyo);
    }
#endif // PY_MAJOR_VERSION
    throw std::invalid_argument("Not a PyLong instance");
  }
};

template <>
struct CppBuilder<double>
{
  double operator() (PyObject* pyo)
  {
    assert(pyo);


     if(PyNumber_Check(pyo))
     {
         PyObject *f = PyNumber_Float(pyo);

        // MessageBox(NULL,"test",  "对话框（标题）", MB_OK);
        if (!f) return 0.00;

         return PyFloat_AS_DOUBLE(f);
     }
    else if (PyFloat_Check(pyo))
    {
         //
      return PyFloat_AS_DOUBLE(pyo);
    }
    else if (PyLong_Check(pyo))
    {

      return PyLong_AsDouble(pyo);
    }
#if PY_MAJOR_VERSION <=2
    else if (PyInt_Check(pyo))
    {
      return PyInt_AS_LONG(pyo);
    }
#endif // PY_MAJOR_VERSION
    throw std::invalid_argument("Neither a PyDouble nor a PyLong instance");
  }
};

template <>
struct CppBuilder<std::string>
{
  std::string operator() (PyObject* pyo)
  {
    assert(pyo);

    if(pyo==Py_None)
        return "";


    if (PyUnicode_Check(pyo))
    {

#if PY_MAJOR_VERSION >=3 and PY_MINOR_VERSION >=3
      Py_ssize_t size;
      const char* str { PyUnicode_AsUTF8AndSize(pyo, &size) };
#else
      long unsigned int size { PyUnicode_GET_DATA_SIZE(pyo) }; // depreciated since 3.3
      const char* str { PyUnicode_AS_DATA(pyo) }; // depreciated since 3.3
#endif
      return std::string(str, size);
    }else if (PyLong_Check(pyo))
    {
        int i_catalog = static_cast<int>(PyLong_AsLong(pyo));

        char s_v[4];
        sprintf(s_v,"%d", i_catalog);

        return std::string(s_v);
    }
    else//if(PyDate_Check(pyo)||PyDateTime_Check(pyo) )
    {
        int i_year {PyDateTime_GET_YEAR(pyo) };
        int i_month { PyDateTime_GET_MONTH(pyo) } ;
        int i_day  { PyDateTime_GET_DAY(pyo) };

        char s_date[16];

        sprintf(s_date, "%d-%02d-%02d", i_year,i_month,i_day);
        //MessageBox(NULL, s_date, "对话框（标题）", MB_OK);

        return std::string(s_date);
    }
    //throw std::invalid_argument("Not a PyUnicode or PyDateTime instance");
  }
};

template <class TUPLE, std::size_t pos>
void _feedCppTuple(TUPLE& tuple, PyObject* root)
{}

template <class TUPLE, std::size_t pos, class T, class... Args>
void _feedCppTuple(TUPLE& tuple, PyObject* root)
{

  std::get<pos>(tuple) = CppBuilder<T>()(PyTuple_GetItem(root, pos));
  _feedCppTuple<TUPLE, pos +1, Args...>(tuple, root);
}

template <class... Args>
struct CppBuilder<std::tuple<Args...>>
{
  std::tuple<Args...> operator() (PyObject* pyo)
  {
    assert(pyo);
    if (PyTuple_Check(pyo))
    {
      if (PyTuple_Size(pyo) == sizeof...(Args))
      {
        std::tuple<Args...> tuple { std::make_tuple(Args()...) };
        _feedCppTuple<std::tuple<Args...>, 0, Args...>(tuple, pyo);
        return tuple;
      }
      else
      {
        std::ostringstream oss;
        oss << "PyTuple length differs from asked one: "
            << "PyTuple(" << PyTuple_Size(pyo) << ") "
            << "and std::tuple<...>(" << sizeof...(Args) << ")";
        throw std::length_error(oss.str());
      }
    }
    throw std::invalid_argument("Not a PyTuple instance");
  }
};

/**
 * VECTOR has to have the following characteristics:
 *
 * (constructor):
 *    VECTOR(size_type count)
 *    build a VECTOR of size count
 *
 * ::begin()
 * ::end()
 * ::iterator compatible with ++it
 */
template <class VECTOR>
struct CppBuilder
{
  VECTOR operator() (PyObject* pyo)
  {
    assert(pyo);
    if (PyList_Check(pyo))
    {
      unsigned int i { 0 };
      VECTOR v(PyList_Size(pyo));
      for (typename VECTOR::iterator it { v.begin() } ; it != v.end() ; ++it, ++i)
      {
        *it = CppBuilder<typename VECTOR::value_type>()(PyList_GetItem(pyo, i));
      }
      return v;
    }
    throw std::invalid_argument("Not a PyList instance");
  }
};

template <class T>
struct CppBuilder<std::set<T>>
{
  std::set<T> operator() (PyObject* pyo)
  {
    assert(pyo);
    if (PySet_Check(pyo))
    {
      long size { PySet_Size(pyo) };
      std::vector<PyObject*> backup(size);
      std::set<T> s;
      for (long i { 0 } ; i != size ; ++i)
      {
        PyObject* popped { PySet_Pop(pyo) };
        backup[i] = popped;
        s.insert(CppBuilder<T>()(popped));
      }
      for (PyObject* popped : backup)
      {
        PySet_Add(pyo, popped);
        Py_DECREF(popped);
      }
      return s;
    }
    throw std::invalid_argument("Not a PySet instance");
  }
};

template <class K, class T>
struct CppBuilder<std::map<K,T>>
{
  std::map<K,T> operator() (PyObject* pyo)
  {
    assert(pyo);
    if (PyDict_Check(pyo))
    {
      std::map<K,T> dict;
      PyObject *key, *value;
      Py_ssize_t pos = 0;
      while (PyDict_Next(pyo, &pos, &key, &value))
      {
        dict[CppBuilder<K>()(key)] = CppBuilder<T>()(value);
      }
      return dict;
    }
    throw std::invalid_argument("Not a PyDict instance");
  }
};

}
}

#endif

