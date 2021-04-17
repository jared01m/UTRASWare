/**
 * DACSPI.c
 * Devices: LM4F120; TM4C123
 * Description: Low level drivers for the TLV5616CP SPI DAC chip.
 * Authors: Matthew Yu.
 * Last Modified: 04/17/21
 */

/** Device specific imports. */
#include <lib/DAC/DACSPI.h>


/**
 * DACSPIInit initializes a given SSI port.
 * @param SSIConfig Struct defining relevant SSI module details for output.
 * @note Multiple DACs can be configured, but the user retains responsibility
 *       for managing the SSI data structures.
 */
void DACSPIInit(SSISelect_t ssi) {
    SSIConfig_t config = {
        .SSI=ssi, 
        .frameFormat=FREESCALE_SPI, 
        .isPrimary=true, 
        .isTransmitting=true,
        .isClockDefaultHigh=true,
        .polarity=true,
        .dataBitSize=16
    };

    SSIInit(config);
}

/**
 * DACSPIOut outputs data to the relevant SSI port initialized by DACSPIInit.
 * @param ssi Enum determining which SSI port to output to.
 * @param data A value from 0 - 4096.
 */
void DACSPIOut(SSISelect_t ssi, uint16_t data) {
    /* Fast mode, normal operation. */
    SPIWrite(ssi, (data & 0x0FFF) | 0x4000);
}
