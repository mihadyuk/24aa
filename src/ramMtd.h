/*
 * ramMtd.h
 *
 *  Created on: Mar 18, 2015
 *      Author: user
 */

#ifndef EEPROM_SRC_RAMMTD_H_
#define EEPROM_SRC_RAMMTD_H_
#include "mtd.hpp"

namespace nvram {

  class RamMtd : public Mtd {
  public:
    RamMtd(uint8_t *bufferStorage, size_t storageSize);
    ~RamMtd();
    msg_t read(uint8_t *data, size_t len, size_t offset) override;
    msg_t write(const uint8_t *data, size_t len, size_t offset) override;
    msg_t shred(uint8_t pattern) override;
    size_t capacity(void) override;
  private:
    uint8_t *m_bufferStorage = nullptr;
    size_t m_storageSize     = 0;
  protected:
    void wait_for_sync(void) override;
  };

} /* namespace nvram_fs */

#endif /* EEPROM_SRC_RAMMTD_H_ */
