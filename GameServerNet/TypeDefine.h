#pragma once

class TCPSession;
class TCPListener;
class ServerPacketBase;
class LoginPacket;

using PtrSTCPListener = std::shared_ptr<TCPListener>;
using PtrWTCPListener = std::weak_ptr<TCPListener>;

using PtrSTCPSession = std::shared_ptr<TCPSession>;
using PtrWTCPSession = std::weak_ptr<TCPSession>;

using PtrSPacketBase = std::shared_ptr<ServerPacketBase>;
using PtrWPacketBase = std::weak_ptr<ServerPacketBase>;

using PtrSLoginPacket = std::shared_ptr<LoginPacket>;
using PtrWLoginPacket = std::weak_ptr<LoginPacket>;
