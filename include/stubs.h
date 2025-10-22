#include <libultraship.h>

#ifdef _WIN32
#define bzero(b, len) (memset((b), '\0', (len)), (void) 0)
#define bcopy(b1, b2, len) (memmove((b2), (b1), (len)), (void) 0)
#endif

/**
 * @brief The type of TV the system is connected to (NTSC, PAL, etc.).
 */
extern u32 osTvType;

/**
 * @brief The type of reset that occurred (cold boot, NMI, etc.).
 */
extern u32 osResetType;

/**
 * @brief A buffer for NMI (Non-Maskable Interrupt) data.
 */
extern u8 osAppNmiBuffer[64];

/**
 * @brief Prints a formatted string to the debug console.
 */
void rmonPrintf(const char* fmt, ...);

void func_80040030(u8* arg0, u8* arg1);
void func_80040174(void*, s32, s32);

/**
 * @brief Sets the frequency of the audio interface.
 * @param freq The frequency to set.
 * @return 0 on success, -1 on failure.
 */
s32 osAiSetFrequency(u32 freq);

void mio0decode(u8* arg0, u8* arg1);
s32 mio0encode(s32 input, s32, s32);

/**
 * @brief Starts a thread.
 * @param thread A pointer to the thread to start.
 */
void osStartThread(OSThread* thread);

/**
 * @brief Creates a new thread.
 * @param thread A pointer to the OSThread structure to initialize.
 * @param id The thread ID.
 * @param entry The entry point of the thread.
 * @param arg An argument to pass to the thread's entry point.
 * @param sp The stack pointer for the new thread.
 * @param pri The priority of the new thread.
 */
void osCreateThread(OSThread* thread, OSId id, void (*entry)(void*), void* arg, void* sp, OSPri pri);

/**
 * @brief Initializes the operating system.
 */
void osInitialize(void);

/**
 * @brief Sets the priority of a thread.
 * @param thread A pointer to the thread to modify.
 * @param pri The new priority for the thread.
 */
void osSetThreadPri(OSThread* thread, OSPri pri);

/**
 * @brief Loads a task onto the Signal Processor (SP).
 * @param task A pointer to the task to load.
 */
void osSpTaskLoad(OSTask* task);

/**
 * @brief Starts a loaded SP task.
 * @param task A pointer to the task to start.
 */
void osSpTaskStartGo(OSTask* task);

/**
 * @brief Yields the current SP task.
 */
void osSpTaskYield(void);

/**
 * @brief Checks if an SP task has been yielded.
 * @param task A pointer to the task to check.
 * @return The yield result.
 */
OSYieldResult osSpTaskYielded(OSTask* task);

/**
 * @brief Deletes a file from the Controller Pak.
 * @return 0 on success, or an error code on failure.
 */
s32 osPfsDeleteFile(OSPfs* pfs, u16 company_code, u32 game_code, u8* game_name, u8* ext_name);

/**
 * @brief Reads from or writes to a file on the Controller Pak.
 * @return 0 on success, or an error code on failure.
 */
s32 osPfsReadWriteFile(OSPfs* pfs, s32 file_no, u8 flag, int offset, int size_in_bytes, u8* data_buffer);

/**
 * @brief Allocates a new file on the Controller Pak.
 * @return 0 on success, or an error code on failure.
 */
s32 osPfsAllocateFile(OSPfs* pfs, u16 company_code, u32 game_code, u8* game_name, u8* ext_name, int file_size_in_bytes,
                      s32* file_no);

/**
 * @brief Checks if a Controller Pak is plugged in.
 * @return 0 on success, or an error code on failure.
 */
s32 osPfsIsPlug(OSMesgQueue* queue, u8* pattern);

/**
 * @brief Initializes the Controller Pak file system.
 * @return 0 on success, or an error code on failure.
 */
s32 osPfsInit(OSMesgQueue* queue, OSPfs* pfs, int channel);

/**
 * @brief Gets the number of files on the Controller Pak.
 * @return 0 on success, or an error code on failure.
 */
s32 osPfsNumFiles(OSPfs* pfs, s32* max_files, s32* files_used);

/**
 * @brief Gets the state of a file on the Controller Pak.
 * @return 0 on success, or an error code on failure.
 */
s32 osPfsFileState(OSPfs* pfs, s32 file_no, OSPfsState* state);

/**
 * @brief Gets the number of free blocks on the Controller Pak.
 * @return 0 on success, or an error code on failure.
 */
s32 osPfsFreeBlocks(OSPfs* pfs, s32* bytes_not_used);

/**
 * @brief Finds a file on the Controller Pak.
 * @return 0 on success, or an error code on failure.
 */
s32 osPfsFindFile(OSPfs* pfs, u16 company_code, u32 game_code, u8* game_name, u8* ext_name, s32* file_no);
