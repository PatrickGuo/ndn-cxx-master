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

#ifndef NDN_SECURITY_SIGNATURE_SHA256_HPP
#define NDN_SECURITY_SIGNATURE_SHA256_HPP

#include "../data.hpp"
#include "../encoding/tlv.hpp"

namespace ndn {

/**
 * Representing of SHA256 signature in a data packet.
 */
class SignatureSha256 : public Signature
{
public:
  class Error : public Signature::Error
  {
  public:
    explicit
    Error(const std::string& what)
      : Signature::Error(what)
    {
    }
  };

  SignatureSha256()
  {
    m_info = Block(Tlv::SignatureInfo);

    m_type = Signature::Sha256;
    m_info.push_back(nonNegativeIntegerBlock(Tlv::SignatureType, Tlv::DigestSha256));
  }

  SignatureSha256(const Signature& signature)
    : Signature(signature)
  {
    if (getType() != Signature::Sha256)
      throw Error("Incorrect signature type");
  }
};

} // namespace ndn

#endif //NDN_SECURITY_SIGNATURE_SHA256_HPP
