#include "mem-manager.h"
#include <iostream>

class BullshitClass
{
public:
  BullshitClass() : contained(20), fucker(43093094) {};
  void Print() {
    std::cout << contained << " " << fucker << std::endl;
  }
private:
  long contained;
  long unsigned fucker;
};

int main()
{
  std::cout << "BullshitClass size: " << sizeof(BullshitClass) << std::endl;
  std::cout << "Long size: " << sizeof(long) << std::endl;

  Manic::MemoryManager foo(3, sizeof(BullshitClass));

  try
  {
    BullshitClass* bar = new (foo.Get()) BullshitClass();
    BullshitClass* baz = new (foo.Get()) BullshitClass();
    BullshitClass* bae = new (foo.Get()) BullshitClass();
    bar->Print();
    baz->Print();
    bae->Print();

    foo.Release(bar);

    BullshitClass* crikey = new (foo.Get()) BullshitClass();

    crikey->Print();

    std::cout << foo.GetTotalFreeSpace() << " bytes free in " << foo.GetTotalFreeChunks() << " individual chunks." << std::endl;
    foo.Release(baz);
    foo.Release(bae);
    foo.Release(crikey);
    std::cout << foo.GetTotalFreeSpace() << " bytes free in " << foo.GetTotalFreeChunks() << " individual chunks." << std::endl;
  }
  catch (const Manic::MemoryManagerError &mme)
  {
    std::cout << mme.Message << std::endl;
  }
}