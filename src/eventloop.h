// Copyright (c) 2020 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_EVENTLOOP_H
#define BITCOIN_EVENTLOOP_H

#include <sync.h>

#include <atomic>
#include <condition_variable>
#include <functional>

class CScheduler;

struct EventLoop {
public:
    EventLoop() {}
    ~EventLoop();

    bool startEventLoop(CScheduler &scheduler,
                        std::function<void()> runEventLoop,
                        int64_t deltaMilliSeconds);
    bool stopEventLoop();

private:
    /**
     * Start stop machinery.
     */
    std::atomic<bool> stopRequest{false};
    bool running GUARDED_BY(cs_running) = false;

    Mutex cs_running;
    std::condition_variable cond_running;
};

#endif // BITCOIN_EVENTLOOP_H
