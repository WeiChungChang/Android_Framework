/* Copyright 2017-2018 Noovo Crop.
 * This software it the property of Noovo Crop.
 * You have to accept the terms in the license file before use
 *
 * Created by JohnChang      2017-06-12
 *
 * Copyright (c) 2017-2018 Noovo Crop.  All rights reserved
 */

#ifndef NOOVO_MEDIA_SERVER_DRIVER_H_
#define NOOVO_MEDIA_SERVER_DRIVER_H_

#include "ALooper.h"
#include "common.h"
#include "NoovoPlayer.h"

namespace android {

struct NoovoMediaServerDriver : RefBase{

    NoovoMediaServerDriver();

protected:

    ~NoovoMediaServerDriver();

private:

    sp<ALooper>     mLooper;
    sp<NoovoMediaServer> mPlayer;


    enum State {
        UNINITIALIZED,
        STOPPED,
        SCANNING,
        RECORDING,
        PAUSED
    };

};

NoovoMediaServerDriver::NoovoMediaServerDriver()
    : mLooper(new ALooper)
{
    mLooper->setName("NoovoMediaServerDriver Looper");
    mLooper->start(
            false, /* runOnCallingThread */
            false,  /* canCallJava */
            PRIORITY_AUDIO);

    mPlayer = new NoovoMediaServer;

    mLooper->registerHandler(mPlayer); 

}

NoovoMediaServerDriver::~NoovoMediaServerDriver() {
    mLooper->stop();
}

}
#endif

