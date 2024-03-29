/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2013-2014 Regents of the University of California.
 *
 * This file is part of ndn-cxx library (NDN C++ library with eXperimental eXtensions).
 *
 * ndn-cxx library is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * ndn-cxx library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 *
 * You should have received copies of the GNU General Public License and GNU Lesser
 * General Public License along with ndn-cxx, e.g., in COPYING.md file.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * See AUTHORS.md for complete list of ndn-cxx authors and contributors.
 *
 * @author Alexander Afanasyev <http://lasr.cs.ucla.edu/afanasyev/index.html>
 */

#ifndef NDN_ENCODING_BUFFER_HPP
#define NDN_ENCODING_BUFFER_HPP

#include "../common.hpp"

#include <vector>

namespace ndn {

class Buffer;
typedef shared_ptr<const Buffer> ConstBufferPtr;
typedef shared_ptr<Buffer> BufferPtr;

/**
 * @brief Class representing a general-use automatically managed/resized buffer
 *
 * In most respect, Buffer class is equivalent to std::vector<uint8_t> and is in fact
 * uses it as a base class.  In addition to that, it provides buf() and buf<T>() helper
 * method for easier access to the underlying data (buf<T>() casts pointer to the requested class)
 */
class Buffer : public std::vector<uint8_t>
{
public:
  /**
   * @brief Creates an empty buffer
   */
  Buffer()
  {
  }

  /**
   * @brief Creates a buffer with pre-allocated size
   * @param size size of the buffer to be allocated
   */
  explicit
  Buffer(size_t size)
    : std::vector<uint8_t>(size, 0)
  {
  }

  /**
   * @brief Create a buffer by copying the supplied data from a const buffer
   * @param buf const pointer to buffer
   * @param length length of the buffer to copy
   */
  Buffer(const void* buf, size_t length)
    : std::vector<uint8_t>(reinterpret_cast<const uint8_t*>(buf),
                           reinterpret_cast<const uint8_t*>(buf) + length)
  {
  }

  /**
   * @brief Create a buffer by copying the supplied data using iterator interface
   *
   * Note that the supplied iterators must be compatible with std::vector<uint8_t> interface
   *
   * @param first iterator to a first element to copy
   * @param last  iterator to an element immediately following the last element to copy
   */
  template <class InputIterator>
  Buffer(InputIterator first, InputIterator last)
    : std::vector<uint8_t>(first, last)
  {
  }

  /**
   * @brief Get pointer to the first byte of the buffer
   */
  uint8_t*
  get()
  {
    return &front();
  }

  /**
   * @brief Get pointer to the first byte of the buffer (alternative version)
   */
  uint8_t*
  buf()
  {
    return &front();
  }

  /**
   * @brief Get pointer to the first byte of the buffer and cast
   * it (reinterpret_cast) to the requested type T
   */
  template<class T>
  T*
  get()
  {
    return reinterpret_cast<T*>(&front());
  }

  /**
   * @brief Get pointer to the first byte of the buffer (alternative version)
   */
  const uint8_t*
  buf() const
  {
    return &front();
  }

  /**
   * @brief Get const pointer to the first byte of the buffer
   */
  const uint8_t*
  get() const
  {
    return &front();
  }

  /**
   * @brief Get const pointer to the first byte of the buffer and cast
   * it (reinterpret_cast) to the requested type T
   */
  template<class T>
  const T*
  get() const
  {
    return reinterpret_cast<const T*>(&front());
  }
};

} // ndn

#endif // NDN_ENCODING_BUFFER_HPP
