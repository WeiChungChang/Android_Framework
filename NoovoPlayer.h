#ifndef NOOVO_MEDIA_SERVER_H_
#define NOOVO_MEDIA_SERVER_H_

#include "AHandler.h"
#include "ALooper.h"
#include "AMessage.h"
#include "common.h"

namespace android {

struct NoovoMediaServer : public AHandler {

    NoovoMediaServer();


protected:
    virtual ~NoovoMediaServer();
    virtual void onMessageReceived(const sp<AMessage> &msg);

private:

    //sp<ALooper> mLooper;

    enum {
        kWhatTryMe              = 'Test'
    };
};


NoovoMediaServer::NoovoMediaServer()
{
}

void NoovoMediaServer::onMessageReceived(const sp<AMessage> &msg) {
    switch (msg->what()) {
        case kWhatTryMe:
        {
            SHOW_ME;
        }
    }
}

NoovoMediaServer::~NoovoMediaServer()
{
}


}
#endif
