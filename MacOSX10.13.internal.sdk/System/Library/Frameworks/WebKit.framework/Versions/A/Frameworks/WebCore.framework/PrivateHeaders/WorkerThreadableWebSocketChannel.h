/*
 * Copyright (C) 2011 Google Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(WEB_SOCKETS)

#include "ThreadableWebSocketChannel.h"
#include "WebSocketChannelClient.h"
#include "WorkerGlobalScope.h"

#include <wtf/RefCounted.h>
#include <wtf/RefPtr.h>
#include <wtf/text/WTFString.h>

namespace WebCore {

class URL;
class ScriptExecutionContext;
class ThreadableWebSocketChannelClientWrapper;
class WorkerGlobalScope;
class WorkerLoaderProxy;
class WorkerRunLoop;

class WorkerThreadableWebSocketChannel : public RefCounted<WorkerThreadableWebSocketChannel>, public ThreadableWebSocketChannel {
    WTF_MAKE_FAST_ALLOCATED;
public:
    static Ref<ThreadableWebSocketChannel> create(WorkerGlobalScope& workerGlobalScope, WebSocketChannelClient& client, const String& taskMode, SocketProvider& provider)
    {
        return adoptRef(*new WorkerThreadableWebSocketChannel(workerGlobalScope, client, taskMode, provider));
    }
    virtual ~WorkerThreadableWebSocketChannel();

    // ThreadableWebSocketChannel functions.
    void connect(const URL&, const String& protocol) override;
    String subprotocol() override;
    String extensions() override;
    ThreadableWebSocketChannel::SendResult send(const String& message) override;
    ThreadableWebSocketChannel::SendResult send(const JSC::ArrayBuffer&, unsigned byteOffset, unsigned byteLength) override;
    ThreadableWebSocketChannel::SendResult send(Blob&) override;
    unsigned bufferedAmount() const override;
    void close(int code, const String& reason) override;
    void fail(const String& reason) override;
    void disconnect() override; // Will suppress didClose().
    void suspend() override;
    void resume() override;

    // Generated by the bridge.  The Peer and its bridge should have identical
    // lifetimes.
    class Peer : public WebSocketChannelClient {
        WTF_MAKE_NONCOPYABLE(Peer); WTF_MAKE_FAST_ALLOCATED;
    public:
        Peer(Ref<ThreadableWebSocketChannelClientWrapper>&&, WorkerLoaderProxy&, ScriptExecutionContext&, const String& taskMode, SocketProvider&);
        ~Peer();

        void connect(const URL&, const String& protocol);
        void send(const String& message);
        void send(const JSC::ArrayBuffer&);
        void send(Blob&);
        void bufferedAmount();
        void close(int code, const String& reason);
        void fail(const String& reason);
        void disconnect();
        void suspend();
        void resume();

        // WebSocketChannelClient functions.
        void didConnect() final;
        void didReceiveMessage(const String& message) final;
        void didReceiveBinaryData(Vector<uint8_t>&&) final;
        void didUpdateBufferedAmount(unsigned bufferedAmount) final;
        void didStartClosingHandshake() final;
        void didClose(unsigned unhandledBufferedAmount, ClosingHandshakeCompletionStatus, unsigned short code, const String& reason) final;
        void didReceiveMessageError() final;
        void didUpgradeURL() final;

    private:
        Ref<ThreadableWebSocketChannelClientWrapper> m_workerClientWrapper;
        WorkerLoaderProxy& m_loaderProxy;
        RefPtr<ThreadableWebSocketChannel> m_mainWebSocketChannel;
        String m_taskMode;
    };

    using RefCounted<WorkerThreadableWebSocketChannel>::ref;
    using RefCounted<WorkerThreadableWebSocketChannel>::deref;

protected:
    void refThreadableWebSocketChannel() override { ref(); }
    void derefThreadableWebSocketChannel() override { deref(); }

private:
    // Bridge for Peer.  Running on the worker thread.
    class Bridge : public RefCounted<Bridge> {
    public:
        static Ref<Bridge> create(Ref<ThreadableWebSocketChannelClientWrapper>&& workerClientWrapper, Ref<WorkerGlobalScope>&& workerGlobalScope, const String& taskMode, Ref<SocketProvider>&& provider)
        {
            return adoptRef(*new Bridge(WTFMove(workerClientWrapper), WTFMove(workerGlobalScope), taskMode, WTFMove(provider)));
        }
        ~Bridge();
        void initialize();
        void connect(const URL&, const String& protocol);
        ThreadableWebSocketChannel::SendResult send(const String& message);
        ThreadableWebSocketChannel::SendResult send(const JSC::ArrayBuffer&, unsigned byteOffset, unsigned byteLength);
        ThreadableWebSocketChannel::SendResult send(Blob&);
        unsigned bufferedAmount();
        void close(int code, const String& reason);
        void fail(const String& reason);
        void disconnect();
        void suspend();
        void resume();

        using RefCounted<Bridge>::ref;
        using RefCounted<Bridge>::deref;

    private:
        Bridge(Ref<ThreadableWebSocketChannelClientWrapper>&&, Ref<WorkerGlobalScope>&&, const String& taskMode, Ref<SocketProvider>&&);

        static void setWebSocketChannel(ScriptExecutionContext*, Bridge* thisPtr, Peer*, Ref<ThreadableWebSocketChannelClientWrapper>&&);

        // Executed on the main thread to create a Peer for this bridge.
        static void mainThreadInitialize(ScriptExecutionContext&, WorkerLoaderProxy&, Ref<ThreadableWebSocketChannelClientWrapper>&&, const String& taskMode, Ref<SocketProvider>&&);

        // Executed on the worker context's thread.
        void clearClientWrapper();

        void setMethodNotCompleted();
        void waitForMethodCompletion();

        Ref<ThreadableWebSocketChannelClientWrapper> m_workerClientWrapper;
        RefPtr<WorkerGlobalScope> m_workerGlobalScope;
        WorkerLoaderProxy& m_loaderProxy;
        String m_taskMode;
        Peer* m_peer { nullptr };
        Ref<SocketProvider> m_socketProvider;
    };

    WEBCORE_EXPORT WorkerThreadableWebSocketChannel(WorkerGlobalScope&, WebSocketChannelClient&, const String& taskMode, SocketProvider&);

    class WorkerGlobalScopeDidInitializeTask;

    Ref<WorkerGlobalScope> m_workerGlobalScope;
    Ref<ThreadableWebSocketChannelClientWrapper> m_workerClientWrapper;
    RefPtr<Bridge> m_bridge;
    Ref<SocketProvider> m_socketProvider;
};

} // namespace WebCore

#endif // ENABLE(WEB_SOCKETS)
