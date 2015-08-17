#include "mem-manager.h"
#include <iostream>

namespace Manic
{

  MemoryManager::MemoryManager(unsigned chunks, long unsigned chunkSize) :
    ChunksNum(chunks), ChunksFree(chunks), ChunkSize(chunkSize)
  {
    Memory = new char[ChunksNum * ChunkSize];
    Chunks = new ChunkInfo[ChunksNum];

    for (int i = 0; i < ChunksNum; ++i)
    {
      Chunks[i].SetUnallocated();
      Chunks[i].SetAddress(Memory + i * ChunkSize);
    }
  }

  MemoryManager::~MemoryManager()
  {
    delete [] Memory;
    delete [] Chunks;
  }

  void * MemoryManager::Get()
  {
    if (ChunksNum <= 0) throw OutOfMemoryError();

    for (int i = 0; i < ChunksNum; ++i)
    {
      if (!Chunks[i])
      {
        Chunks[i].SetAllocated();
        --ChunksFree;
        return Memory + i * ChunkSize;
      }
    }

    throw OutOfMemoryError(); // Should never get here
  }

  void MemoryManager::Release(void * address)
  {
    int chunkToClear = static_cast<char *>(address) - Memory;
    chunkToClear /= ChunkSize;
    Chunks[chunkToClear].SetUnallocated();
    ++ChunksFree;
  }

  long unsigned MemoryManager::GetTotalFreeSpace()
  {
    return GetTotalFreeChunks() * ChunkSize;
  }

  unsigned MemoryManager::GetTotalFreeChunks()
  {
    return ChunksFree;
  }

  ChunkInfo::operator bool()
  {
    return Allocated;
  }

  void ChunkInfo::SetUnallocated()
  {
    Allocated = false;
  }

  void ChunkInfo::SetAllocated()
  {
    Allocated = true;
  }

  void ChunkInfo::SetAddress(void * address)
  {
    Address = address;
  }

} // Manic