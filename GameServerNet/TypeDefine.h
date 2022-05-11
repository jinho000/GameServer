#pragma once

using PtrSTCPListener = std::shared_ptr<class TCPListener>;
using PtrWTCPListener = std::weak_ptr<class TCPListener>;

using PtrSTCPSession = std::shared_ptr<class TCPSession>;
using PtrWTCPSession = std::weak_ptr<class TCPSession>;

using PtrSUDPSession = std::shared_ptr<class UDPSession>;
using PtrWUDPSession = std::weak_ptr<class UDPSession>;