#pragma once

using PtrSTCPListener = std::shared_ptr<class TCPListener>;
using PtrWTCPListener = std::weak_ptr<class TCPListener>;

using PtrSTCPSession = std::shared_ptr<class TCPSession>;
using PtrWTCPSession = std::weak_ptr<class TCPSession>;

using PtrSPacketBase = std::shared_ptr<class ServerPacketBase>;
using PtrWPacketBase = std::weak_ptr<class ServerPacketBase>;

using PtrSLoginPacket = std::shared_ptr<class LoginPacket>;
using PtrWLoginPacket = std::weak_ptr<class LoginPacket>;

using PtrSChatMsgPacket = std::shared_ptr<class ChatMessagePacket>;
using PtrWChatMsgPacket = std::weak_ptr<class ChatMessagePacket>;
