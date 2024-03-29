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
 */

#include "common.hpp"

#include "tcp-transport.hpp"
#include "stream-transport.hpp"

namespace ndn {

TcpTransport::TcpTransport(const std::string& host, const std::string& port/* = "6363"*/)
  : m_host(host)
  , m_port(port)
{
}

TcpTransport::~TcpTransport()
{
}

void
TcpTransport::connect(boost::asio::io_service& ioService,
                      const ReceiveCallback& receiveCallback)
{
  if (!static_cast<bool>(m_impl)) {
    Transport::connect(ioService, receiveCallback);

    m_impl = make_shared<Impl>(ref(*this), ref(ioService));
  }

  boost::asio::ip::tcp::resolver::query query(m_host, m_port);
  m_impl->connect(query);
}

void
TcpTransport::send(const Block& wire)
{
  m_impl->send(wire);
}

void
TcpTransport::send(const Block& header, const Block& payload)
{
  m_impl->send(header, payload);
}

void
TcpTransport::close()
{
  m_impl->close();
}

void
TcpTransport::pause()
{
  m_impl->pause();
}

void
TcpTransport::resume()
{
  m_impl->resume();
}

} // namespace ndn
