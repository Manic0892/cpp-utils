#include <string>

namespace Manic
{

namespace // No one should access ChunkInfo except for the MemoryManager
{

class ChunkInfo
{
  public:
    operator bool();
    void SetUnallocated();
    void SetAllocated();
    void SetAddress(void * address);
  private:
    bool   Allocated;
    void * Address;
};

}

class MemoryManager
{
  public:
    MemoryManager(unsigned chunks = 64, long unsigned chunkSize = 4096);
    ~MemoryManager();

    // Allocate or deallocate pre-allocated memory
    void * Get();
    void Release(void * address);
    // Information about the memory manager
    long unsigned GetTotalFreeSpace();
    unsigned GetTotalFreeChunks();

  private:
    ChunkInfo*    Chunks;
    unsigned      ChunksNum;
    unsigned      ChunksFree;
    long unsigned ChunkSize;
    char*         Memory; 
};

class MemoryManagerError
{
  public:
    MemoryManagerError(const char* message = "Memory error.") : Message(message) {}
    const std::string Message;
};

class OutOfMemoryError : public MemoryManagerError
{
  public:
    OutOfMemoryError() : MemoryManagerError("Out of memory.") {}
};

} // Manic