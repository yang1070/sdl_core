/**
* Copyright (c) 2013, Ford Motor Company
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following
* disclaimer in the documentation and/or other materials provided with the
* distribution.
*
* Neither the name of the Ford Motor Company nor the names of its contributors
* may be used to endorse or promote products derived from this software
* without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef SRC_COMPONENTS_MEDIA_MANAGER_SRC_SOCKET_VIDEO_STREAMER_ADAPTER_H_
#define SRC_COMPONENTS_MEDIA_MANAGER_SRC_SOCKET_VIDEO_STREAMER_ADAPTER_H_

#include "media_manager/media_adapter_impl.h"
#include "utils/logger.h"
#include "utils/shared_ptr.h"
#include "utils/message_queue.h"
#include "utils/threads/thread.h"
#include "utils/threads/thread_delegate.h"

namespace media_manager {
class SocketVideoStreamerAdapter : public MediaAdapterImpl {
  public:
    SocketVideoStreamerAdapter();
    ~SocketVideoStreamerAdapter();
    virtual void SendData(int application_key,
                          const protocol_handler::RawMessagePtr& message);
    virtual void StartActivity(int application_key);
    virtual void StopActivity(int application_key);
    virtual bool is_app_performing_activity(int application_key);

  private:
    class VideoStreamer : public threads::ThreadDelegate {
      public:
        /*
         * Default constructor
         *
         * @param server  Server pointer
         */
        explicit VideoStreamer(SocketVideoStreamerAdapter* const server);

        /*
         * Destructor
         */
        ~VideoStreamer();

        /*
         * Function called by thread on start
         */
        void threadMain();

        /*
         * Function called by thread on exit
         */
        bool exitThreadMain();

        /*
         * Checks if server is ready
         *
         * @return TRUE if socket is ready otherwise FALSE
         */
        bool is_ready() const;

        /*
         * Stops server
         *
         */
        void stop();

        /*
         * Sends data to connected client
         *
         * @param block Pointer to the data
         */
        bool send(const protocol_handler::RawMessagePtr& msg);

      private:
        SocketVideoStreamerAdapter* const server_;
        int socket_fd_;
        bool is_first_loop_;
        volatile bool is_client_connected_;
        volatile bool stop_flag_;

        DISALLOW_COPY_AND_ASSIGN(VideoStreamer);
    };


    int port_;
    std::string ip_;
    int socket_;
    bool is_ready_;
    volatile int current_application_;
    VideoStreamer* delegate_;
    threads::Thread* thread_;
    MessageQueue<protocol_handler::RawMessagePtr> messages_;
    static log4cxx::LoggerPtr logger_;

    DISALLOW_COPY_AND_ASSIGN(SocketVideoStreamerAdapter);
};
}  //  namespace media_manager


#endif  //  SRC_COMPONENTS_MEDIA_MANAGER_SRC_SOCKET_VIDEO_STREAMER_ADAPTER_H_
