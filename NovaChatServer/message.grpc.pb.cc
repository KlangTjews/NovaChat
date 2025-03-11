// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: message.proto

#include "message.pb.h"
#include "message.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace message {

static const char* VarifyService_method_names[] = {
  "/message.VarifyService/GetVarifyCode",
};

std::unique_ptr< VarifyService::Stub> VarifyService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< VarifyService::Stub> stub(new VarifyService::Stub(channel, options));
  return stub;
}

VarifyService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_GetVarifyCode_(VarifyService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status VarifyService::Stub::GetVarifyCode(::grpc::ClientContext* context, const ::message::GetVarifyReq& request, ::message::GetVarifyRsp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::message::GetVarifyReq, ::message::GetVarifyRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetVarifyCode_, context, request, response);
}

void VarifyService::Stub::async::GetVarifyCode(::grpc::ClientContext* context, const ::message::GetVarifyReq* request, ::message::GetVarifyRsp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::message::GetVarifyReq, ::message::GetVarifyRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetVarifyCode_, context, request, response, std::move(f));
}

void VarifyService::Stub::async::GetVarifyCode(::grpc::ClientContext* context, const ::message::GetVarifyReq* request, ::message::GetVarifyRsp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetVarifyCode_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::message::GetVarifyRsp>* VarifyService::Stub::PrepareAsyncGetVarifyCodeRaw(::grpc::ClientContext* context, const ::message::GetVarifyReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::message::GetVarifyRsp, ::message::GetVarifyReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetVarifyCode_, context, request);
}

::grpc::ClientAsyncResponseReader< ::message::GetVarifyRsp>* VarifyService::Stub::AsyncGetVarifyCodeRaw(::grpc::ClientContext* context, const ::message::GetVarifyReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetVarifyCodeRaw(context, request, cq);
  result->StartCall();
  return result;
}

VarifyService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VarifyService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VarifyService::Service, ::message::GetVarifyReq, ::message::GetVarifyRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VarifyService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::message::GetVarifyReq* req,
             ::message::GetVarifyRsp* resp) {
               return service->GetVarifyCode(ctx, req, resp);
             }, this)));
}

VarifyService::Service::~Service() {
}

::grpc::Status VarifyService::Service::GetVarifyCode(::grpc::ServerContext* context, const ::message::GetVarifyReq* request, ::message::GetVarifyRsp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


static const char* StatusService_method_names[] = {
  "/message.StatusService/GetChatServer",
  "/message.StatusService/Login",
};

std::unique_ptr< StatusService::Stub> StatusService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< StatusService::Stub> stub(new StatusService::Stub(channel, options));
  return stub;
}

StatusService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_GetChatServer_(StatusService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Login_(StatusService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status StatusService::Stub::GetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerReq& request, ::message::GetChatServerRsp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::message::GetChatServerReq, ::message::GetChatServerRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetChatServer_, context, request, response);
}

void StatusService::Stub::async::GetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerReq* request, ::message::GetChatServerRsp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::message::GetChatServerReq, ::message::GetChatServerRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetChatServer_, context, request, response, std::move(f));
}

void StatusService::Stub::async::GetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerReq* request, ::message::GetChatServerRsp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetChatServer_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::message::GetChatServerRsp>* StatusService::Stub::PrepareAsyncGetChatServerRaw(::grpc::ClientContext* context, const ::message::GetChatServerReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::message::GetChatServerRsp, ::message::GetChatServerReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetChatServer_, context, request);
}

::grpc::ClientAsyncResponseReader< ::message::GetChatServerRsp>* StatusService::Stub::AsyncGetChatServerRaw(::grpc::ClientContext* context, const ::message::GetChatServerReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetChatServerRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status StatusService::Stub::Login(::grpc::ClientContext* context, const ::message::LoginReq& request, ::message::LoginRsp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::message::LoginReq, ::message::LoginRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Login_, context, request, response);
}

void StatusService::Stub::async::Login(::grpc::ClientContext* context, const ::message::LoginReq* request, ::message::LoginRsp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::message::LoginReq, ::message::LoginRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, std::move(f));
}

void StatusService::Stub::async::Login(::grpc::ClientContext* context, const ::message::LoginReq* request, ::message::LoginRsp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::message::LoginRsp>* StatusService::Stub::PrepareAsyncLoginRaw(::grpc::ClientContext* context, const ::message::LoginReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::message::LoginRsp, ::message::LoginReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Login_, context, request);
}

::grpc::ClientAsyncResponseReader< ::message::LoginRsp>* StatusService::Stub::AsyncLoginRaw(::grpc::ClientContext* context, const ::message::LoginReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncLoginRaw(context, request, cq);
  result->StartCall();
  return result;
}

StatusService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      StatusService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< StatusService::Service, ::message::GetChatServerReq, ::message::GetChatServerRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](StatusService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::message::GetChatServerReq* req,
             ::message::GetChatServerRsp* resp) {
               return service->GetChatServer(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      StatusService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< StatusService::Service, ::message::LoginReq, ::message::LoginRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](StatusService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::message::LoginReq* req,
             ::message::LoginRsp* resp) {
               return service->Login(ctx, req, resp);
             }, this)));
}

StatusService::Service::~Service() {
}

::grpc::Status StatusService::Service::GetChatServer(::grpc::ServerContext* context, const ::message::GetChatServerReq* request, ::message::GetChatServerRsp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status StatusService::Service::Login(::grpc::ServerContext* context, const ::message::LoginReq* request, ::message::LoginRsp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


static const char* ChatService_method_names[] = {
  "/message.ChatService/NotifyAddFriend",
  "/message.ChatService/RplyAddFriend",
  "/message.ChatService/SendChatMsg",
  "/message.ChatService/NotifyAuthFriend",
  "/message.ChatService/NotifyTextChatMsg",
};

std::unique_ptr< ChatService::Stub> ChatService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ChatService::Stub> stub(new ChatService::Stub(channel, options));
  return stub;
}

ChatService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_NotifyAddFriend_(ChatService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_RplyAddFriend_(ChatService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_SendChatMsg_(ChatService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_NotifyAuthFriend_(ChatService_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_NotifyTextChatMsg_(ChatService_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ChatService::Stub::NotifyAddFriend(::grpc::ClientContext* context, const ::message::AddFriendReq& request, ::message::AddFriendRsp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::message::AddFriendReq, ::message::AddFriendRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_NotifyAddFriend_, context, request, response);
}

void ChatService::Stub::async::NotifyAddFriend(::grpc::ClientContext* context, const ::message::AddFriendReq* request, ::message::AddFriendRsp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::message::AddFriendReq, ::message::AddFriendRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NotifyAddFriend_, context, request, response, std::move(f));
}

void ChatService::Stub::async::NotifyAddFriend(::grpc::ClientContext* context, const ::message::AddFriendReq* request, ::message::AddFriendRsp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NotifyAddFriend_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::message::AddFriendRsp>* ChatService::Stub::PrepareAsyncNotifyAddFriendRaw(::grpc::ClientContext* context, const ::message::AddFriendReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::message::AddFriendRsp, ::message::AddFriendReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_NotifyAddFriend_, context, request);
}

::grpc::ClientAsyncResponseReader< ::message::AddFriendRsp>* ChatService::Stub::AsyncNotifyAddFriendRaw(::grpc::ClientContext* context, const ::message::AddFriendReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncNotifyAddFriendRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ChatService::Stub::RplyAddFriend(::grpc::ClientContext* context, const ::message::RplyFriendReq& request, ::message::RplyFriendRsp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::message::RplyFriendReq, ::message::RplyFriendRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_RplyAddFriend_, context, request, response);
}

void ChatService::Stub::async::RplyAddFriend(::grpc::ClientContext* context, const ::message::RplyFriendReq* request, ::message::RplyFriendRsp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::message::RplyFriendReq, ::message::RplyFriendRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_RplyAddFriend_, context, request, response, std::move(f));
}

void ChatService::Stub::async::RplyAddFriend(::grpc::ClientContext* context, const ::message::RplyFriendReq* request, ::message::RplyFriendRsp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_RplyAddFriend_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::message::RplyFriendRsp>* ChatService::Stub::PrepareAsyncRplyAddFriendRaw(::grpc::ClientContext* context, const ::message::RplyFriendReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::message::RplyFriendRsp, ::message::RplyFriendReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_RplyAddFriend_, context, request);
}

::grpc::ClientAsyncResponseReader< ::message::RplyFriendRsp>* ChatService::Stub::AsyncRplyAddFriendRaw(::grpc::ClientContext* context, const ::message::RplyFriendReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncRplyAddFriendRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ChatService::Stub::SendChatMsg(::grpc::ClientContext* context, const ::message::SendChatMsgReq& request, ::message::SendChatMsgRsp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::message::SendChatMsgReq, ::message::SendChatMsgRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_SendChatMsg_, context, request, response);
}

void ChatService::Stub::async::SendChatMsg(::grpc::ClientContext* context, const ::message::SendChatMsgReq* request, ::message::SendChatMsgRsp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::message::SendChatMsgReq, ::message::SendChatMsgRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SendChatMsg_, context, request, response, std::move(f));
}

void ChatService::Stub::async::SendChatMsg(::grpc::ClientContext* context, const ::message::SendChatMsgReq* request, ::message::SendChatMsgRsp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SendChatMsg_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::message::SendChatMsgRsp>* ChatService::Stub::PrepareAsyncSendChatMsgRaw(::grpc::ClientContext* context, const ::message::SendChatMsgReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::message::SendChatMsgRsp, ::message::SendChatMsgReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_SendChatMsg_, context, request);
}

::grpc::ClientAsyncResponseReader< ::message::SendChatMsgRsp>* ChatService::Stub::AsyncSendChatMsgRaw(::grpc::ClientContext* context, const ::message::SendChatMsgReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncSendChatMsgRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ChatService::Stub::NotifyAuthFriend(::grpc::ClientContext* context, const ::message::AuthFriendReq& request, ::message::AuthFriendRsp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::message::AuthFriendReq, ::message::AuthFriendRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_NotifyAuthFriend_, context, request, response);
}

void ChatService::Stub::async::NotifyAuthFriend(::grpc::ClientContext* context, const ::message::AuthFriendReq* request, ::message::AuthFriendRsp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::message::AuthFriendReq, ::message::AuthFriendRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NotifyAuthFriend_, context, request, response, std::move(f));
}

void ChatService::Stub::async::NotifyAuthFriend(::grpc::ClientContext* context, const ::message::AuthFriendReq* request, ::message::AuthFriendRsp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NotifyAuthFriend_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::message::AuthFriendRsp>* ChatService::Stub::PrepareAsyncNotifyAuthFriendRaw(::grpc::ClientContext* context, const ::message::AuthFriendReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::message::AuthFriendRsp, ::message::AuthFriendReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_NotifyAuthFriend_, context, request);
}

::grpc::ClientAsyncResponseReader< ::message::AuthFriendRsp>* ChatService::Stub::AsyncNotifyAuthFriendRaw(::grpc::ClientContext* context, const ::message::AuthFriendReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncNotifyAuthFriendRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ChatService::Stub::NotifyTextChatMsg(::grpc::ClientContext* context, const ::message::TextChatMsgReq& request, ::message::TextChatMsgRsp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::message::TextChatMsgReq, ::message::TextChatMsgRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_NotifyTextChatMsg_, context, request, response);
}

void ChatService::Stub::async::NotifyTextChatMsg(::grpc::ClientContext* context, const ::message::TextChatMsgReq* request, ::message::TextChatMsgRsp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::message::TextChatMsgReq, ::message::TextChatMsgRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NotifyTextChatMsg_, context, request, response, std::move(f));
}

void ChatService::Stub::async::NotifyTextChatMsg(::grpc::ClientContext* context, const ::message::TextChatMsgReq* request, ::message::TextChatMsgRsp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NotifyTextChatMsg_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::message::TextChatMsgRsp>* ChatService::Stub::PrepareAsyncNotifyTextChatMsgRaw(::grpc::ClientContext* context, const ::message::TextChatMsgReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::message::TextChatMsgRsp, ::message::TextChatMsgReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_NotifyTextChatMsg_, context, request);
}

::grpc::ClientAsyncResponseReader< ::message::TextChatMsgRsp>* ChatService::Stub::AsyncNotifyTextChatMsgRaw(::grpc::ClientContext* context, const ::message::TextChatMsgReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncNotifyTextChatMsgRaw(context, request, cq);
  result->StartCall();
  return result;
}

ChatService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChatService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChatService::Service, ::message::AddFriendReq, ::message::AddFriendRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ChatService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::message::AddFriendReq* req,
             ::message::AddFriendRsp* resp) {
               return service->NotifyAddFriend(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChatService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChatService::Service, ::message::RplyFriendReq, ::message::RplyFriendRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ChatService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::message::RplyFriendReq* req,
             ::message::RplyFriendRsp* resp) {
               return service->RplyAddFriend(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChatService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChatService::Service, ::message::SendChatMsgReq, ::message::SendChatMsgRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ChatService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::message::SendChatMsgReq* req,
             ::message::SendChatMsgRsp* resp) {
               return service->SendChatMsg(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChatService_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChatService::Service, ::message::AuthFriendReq, ::message::AuthFriendRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ChatService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::message::AuthFriendReq* req,
             ::message::AuthFriendRsp* resp) {
               return service->NotifyAuthFriend(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChatService_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChatService::Service, ::message::TextChatMsgReq, ::message::TextChatMsgRsp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ChatService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::message::TextChatMsgReq* req,
             ::message::TextChatMsgRsp* resp) {
               return service->NotifyTextChatMsg(ctx, req, resp);
             }, this)));
}

ChatService::Service::~Service() {
}

::grpc::Status ChatService::Service::NotifyAddFriend(::grpc::ServerContext* context, const ::message::AddFriendReq* request, ::message::AddFriendRsp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ChatService::Service::RplyAddFriend(::grpc::ServerContext* context, const ::message::RplyFriendReq* request, ::message::RplyFriendRsp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ChatService::Service::SendChatMsg(::grpc::ServerContext* context, const ::message::SendChatMsgReq* request, ::message::SendChatMsgRsp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ChatService::Service::NotifyAuthFriend(::grpc::ServerContext* context, const ::message::AuthFriendReq* request, ::message::AuthFriendRsp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ChatService::Service::NotifyTextChatMsg(::grpc::ServerContext* context, const ::message::TextChatMsgReq* request, ::message::TextChatMsgRsp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace message

