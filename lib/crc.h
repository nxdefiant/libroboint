/**
 * \file /tmp/crc-test/crc.h
 * Functions and types for CRC checks.
 *
 * Generated on Wed Aug  8 12:34:17 2007,
 * by pycrc v0.6, http://www.tty1.net/pycrc/
 * using the configuration:
 *    Width        = 16
 *    Poly         = 0x1021
 *    XorIn        = 0xffff
 *    ReflectIn    = False
 *    XorOut       = 0x0000
 *    ReflectOut   = False
 *    Algorithm    = table-driven
 *****************************************************************************/
#ifndef __CRC_H__
#define __CRC_H__

#include <stdint.h>
#include <unistd.h>

/**
 * \brief   The definition of the used algorithm.
 *****************************************************************************/
#define CRC_ALGO_TABLE_DRIVEN 1

/**
 * \brief   The type of the CRC values.
 *
 * This type must be big enough to contain at least 16 bits.
 *****************************************************************************/
typedef uint16_t crc_t;

/**
 * \brief      Calculate the initial crc value.
 * \return     The initial crc value.
 *****************************************************************************/
static inline crc_t crc_init(void)
{
    return 0xffff;
}

/**
 * \brief          Update the crc value with new data.
 * \param crc      The current crc value.
 * \param data     Pointer to a buffer of \a data_len bytes.
 * \param data_len Number of bytes in the \a data buffer.
 * \return         The updated crc value.
 *****************************************************************************/
crc_t crc_update(crc_t crc, const unsigned char *data, size_t data_len);

/**
 * \brief      Calculate the final crc value.
 * \param crc  The current crc value.
 * \return     The final crc value.
 *****************************************************************************/
static inline crc_t crc_finalize(crc_t crc)
{
    return crc ^ 0x0000;
}

#endif      /* __CRC_H__ */
