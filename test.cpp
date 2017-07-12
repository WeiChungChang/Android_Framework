//#include <utils/RefBase.h>
//#include <utils/Log.h>
#include <cstdlib>
#include <cassert>
#include <stdio.h>
#include "RefBase.h"
#include "Mutex.h"

#include "AHandler.h"
#include "ALooper.h"
#include "ALooperRoster.h"

#include "NoovoPlayerDriver.h"

using namespace android;

// class Memory subclass RefBase[1] so it can be reference counted
// and be accepted by template class sp<T> [2], where the sp stands for
// strong pointer
// [1]https://android.googlesource.com/platform/frameworks/native/+/jb-mr1-dev/include/utils/RefBase.h
// [2]https://android.googlesource.com/platform/frameworks/native/+/jb-mr1-dev/include/utils/StrongPointer.h

class Memory: public RefBase {
public:
    Memory(int size) : mSize(size), mData(NULL) {
        printf("        Memory constructor %p\n",this);
    }

    virtual ~Memory() {
        printf("        Memory destructor %p\n", this);
        if (mData)  free(mData);
    }

    virtual void onFirstRef() {
        printf("        onFirstRef on %p\n",this);
        mData = malloc(mSize);
    }

    int size() {return mSize;}
private:
    int mSize;
    void *mData;
};

// used as a marker in the output log
#define L(N)   printf("LINE %d TRIGGER:\n",N);
// print out the strong counter number of the object
#define C(obj) printf("        Count of %p : %d\n", (void*)obj, obj->getStrongCount());

int main()
{
    sp<NoovoMediaServerDriver> mPlayer = new NoovoMediaServerDriver;
    return 1;

}