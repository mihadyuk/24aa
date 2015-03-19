/*
 * ramMtd.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: user
 */

#include "ramMtd.h"
#include <string.h>

namespace nvram {

RamMtd::RamMtd(uint8_t *bufferStorage, size_t storageSize) :
    Mtd(nullptr),
    m_bufferStorage(bufferStorage),
    m_storageSize(storageSize)
{
  // TODO Auto-generated constructor stub
  osalDbgAssert(m_bufferStorage != nullptr, "null bufferstorage");
  if (m_bufferStorage)
    memset(m_bufferStorage, 0xFF, storageSize);
}

RamMtd::~RamMtd() {
  // TODO Auto-generated destructor stub
}

msg_t RamMtd::read(uint8_t *data, size_t len, size_t offset) {

    osalDbgAssert((offset + len) <= capacity(), "Transaction out of device bounds");
    if ((offset + len) > capacity())
      return MSG_RESET;

    Mtd::acquire();
    memcpy(data, &m_bufferStorage[offset], len);
    Mtd::release();

    return MSG_OK;

}

msg_t RamMtd::write(const uint8_t *data, size_t len, size_t offset) {

  osalDbgAssert((offset + len) <= capacity(), "Transaction out of device bounds");
  if ((offset + len) > capacity())
    return MSG_RESET;

  Mtd::acquire();
  memcpy(&m_bufferStorage[offset], data, len);
  Mtd::release();

  return MSG_OK;

}

msg_t RamMtd::shred(uint8_t pattern) {
  (void)pattern;
  return MSG_OK;
}

size_t RamMtd::capacity(void) {
  return m_storageSize;
}

void RamMtd::wait_for_sync() {

}



} /* namespace nvram_fs */
