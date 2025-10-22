#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <common_structs.h>
/**
 * @brief Decodes data compressed with the MIO0 format.
 *
 * @param src A pointer to the source (compressed) data.
 * @param dst A pointer to the destination (decompressed) buffer.
 */
#ifdef TARGET_N64
void mio0decode(u8* arg0, u8* arg1);
#endif

/**
 * @brief An unused MIO0 decoding function.
 *
 * This function appears to be an alternative or older version of `mio0decode`
 * that is not currently used in the game.
 *
 * @param src A pointer to the source (compressed) data.
 * @param dst A pointer to the destination (decompressed) buffer.
 */
void func_80040030(u8* arg0, u8* arg1);

#endif
