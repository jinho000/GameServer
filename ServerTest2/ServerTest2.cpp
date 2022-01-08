#include <iostream>

#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h> // inet_pton 함수 헤더

#pragma comment(lib, "ws2_32") 

//  윈도우 소켓 사용 방법
// 
//  서버
//  Winsock을 초기화 합니다.
//  소켓을 만듭니다.
//  소켓을 바인딩합니다.
//  클라이언트의 소켓에서 수신 대기 합니다.
//  클라이언트에서 연결을 허용 합니다.
//  데이터를 받고 보냅니다.
//  케이블.
// 
//  클라이언트
//  Winsock을 초기화 합니다.
//  소켓을 만듭니다.
//  서버에 커넥트 합니다.
//  데이터를 보내고 받습니다.
//  케이블.
// 
//

int main()
{
	/*
        * WSADATA
        * 소켓라이브러리 초기화 후 정보를 받아오는 구조체
        * 
		* struct WSADATA {
		*	   WORD wVersion;	
		*	   WORD wHighVersion;
		*	   char szDescription[WSADESCRIPTION_LEN+1];
		*	   char szSystemStatus[WSASYSSTATUS_LEN+1];
		*	   unsigned short iMaxSockets;
		*	   unsigned short iMaxUdpDg;
		*	   char FAR * lpVendorInfo;
		* }; 
	*/
    WSADATA ws;

	/*
		* WSAStartup
		* 소켓라이브러리 초기화 함수
        * WS232.dll의 사용을 시작 하기 위해 호출 하는 함수
		*
		* int WSAStartup(
        *         WORD      wVersionRequired,
        *   [out] LPWSADATA lpWSAData
        * );
        * 
        * @param
        * wVersionRequired  :   소켓의 버전 정보 전달
        *                       MAKEWORD: 바이트 단위로 쪼개어 반환해주는 매크로      
        *                       MAKEWORD(2, 2): 2.2 버전
        * 
        * lpWSAData         :   초기화된 라이브러리의 정보를 받기위한 구조체
        *                       주소값을 전달받아야함
        * 
        * @return
        * int               :   성공시 0 반환
        *                       0이 아닌경우 에러코드 반환
        * 
        * 
	*/
    if (0 != WSAStartup(MAKEWORD(2, 2), &ws))
    {
        std::cout << "WSAStartUp err!\n";
        return 0;
    }

    /*
    * socket
    * 윈도우 소켓 생성 함수
    *
    *   SOCKET WSAAPI socket(
    *     [in] int af,
    *     [in] int type,
    *     [in] int protocol
    *   );
    *
    * @param
    * af            :   소켓이 사용할 프로토콜 체계(protocol family) 전달
    *                   protocol family: 주소값 프로토콜 체계
    *                   AF_UNSPEC           : 주소값 체계를 설정하지 않음
    *                   AF_INET(PF_INET)    : IPv4 주소 체계 사용
    *                   AF_IPX              : IPv6 주소체계 사용
    *
    *
    * type          :   소켓의 데이터 전송방식 설정
    *                   SOCK_STREAM : 연결 지향형 소켓(TCP)
    *                   SOCK_DGRAM  : 비연결 지향형 소켓(UDP)
    * 
    * protocol      :   사용할 프로토콜 설정
    *                   가능한 프로토콜은 설정한 프로토콜 체계(af)와 전송방식(type)에 따라 다름
    *                   IPPROTO_TCP
    *                   IPPROTO_UDP
    * 
    * @return
    * SOCKET        :   성공시 생성된 소켓 반환
    *                   실패시 INVALID_SOCKET 
    *
    */

    // 연결지향형 소켓
    // 서버와 클라간 연결을 유지하며 데이터를 전송하는 방식
    // 연결이 유지되므로 데이터가 전송순서대로 수신됨
    // 연결을 유지하는데 비용이 듦
    // 
    // 비 연결 지향형 소켓
    // 서버와 클라간 연결을 유지하지 않는 데이터 전송방식
    // 데이터 전송순서를 보장하지 않음
    // 
    // IPv4 주소체계를 사용하는 연결지향형 TCP 소켓
    SOCKET acceptSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == acceptSocket)
    {
        std::cout << "Socket err!\n";
        return 0;
    }



    // IP(Internet Protocol)
    // 네트워크상에서 통신하기위해 각 컴퓨터에 부여한 주소
    // 주소체계
    // IPv4: 4바이트로 표현되는 주소체계
    // IPv6: 16바이트로 표현되는 주소체계
    // 
    // Port
    // 컴퓨터내에서 소켓을 구분할 목적으로 부여하는 번호
    // 하나의 컴퓨터 안에서 포트가 여러개 있을 수 있으며 중복 불가
    // 2바이트의 범위를 가지며 0 ~ 65535까지의 값을 가질 수 있음
    // 프로토콜 타입이 다르면 포트값이 같아도 상관없음
    // 


    /*
    * SOCKADDR_IN
    * 생성한 소켓에 필요한 정보를 넘기기 위한 구조체
    * 
    *   struct sockaddr_in{
    *      ADDRESS_FAMILY   sin_family;
    *      USHORT           sin_port;
    *      IN_ADDR          sin_addr;
    *      CHAR             sin_zero[8];
    *   }SOCKADDR_IN;
    * 
    *   ADDRESS_FAMILY  sin_family      :   주소체계
    *                                       Address Family
    *                                       AF_INET : IPv4 주소체계
    *                                       AF_INET6: IPv6 주소체계
    * 
    *   USHORT          sin_port        :   16비트의 포트 번호(네트워크 바이트순서로 저장)
    *   IN_ADDR         sin_addr        :   32비트 IP주소(네트워크 바이트순서로 저장)
    *   CHAR            sin_zero[8]     :   사용되지 않음
    *
    */

    // 네트워크 바이트 순서(Network Byte Order)
    // Host Byte Order: CPU가 데이터를 저장하는 방식 리틀엔디언과 빅엔디언 방식이 있음
    // 네트워크로 연결된 컴퓨터가 서로 통신시 Host Byte Order가 다를경우 데이터를 다르게 처리하기 때문에 문제가 있음
    // 데이터 전송시 통일된 기준을 정함 -> 빅엔디언 방식
    // 리틀엔디안 방식의 CPU에서는 빅엔디언 방식으로 데이터를 정렬해서 저장해야함
    // 
    // 바이트 순서 변환함수
    // htons, ntohs, ... (host to network short, network to host short, ...)
    // 
    // -> 데이터를 전송하기전 직접 네트워크 바이트 순서로 바꾸지 않아도 자동으로 변환해줌
    // 
    // 
    // 서버: 사용할 주소체계, 포트, 주소값을 소켓에 넘김
    // 클라: 연결할 서버의 주소체계, 포트, 주소값을 소켓에 넘김
    //
    SOCKADDR_IN sockAddrIn = { 0, };
    sockAddrIn.sin_family = AF_INET;
    sockAddrIn.sin_port = htons(30000);

    /*
    * inet_pton
    * ip 주소값을 해당 주소체계에 맞는 네트워크 바이트 주소값으로 변환해줌
    *
    *   INT WSAAPI inet_pton(
    *     [in]  INT   Family,
    *     [in]  PCSTR pszAddrString,
    *     [out] PVOID pAddrBuf
    *   );
    *
    * @param
    * Family        :   변환할 주소체계
    *                   AF_INET(PF_INET)    : IPv4 주소 체계 사용
    *                   AF_INET6            : IPv6 주소체계 사용
    *
    *
    * pszAddrString :   변환할 주소 IP값
    *                   IPv4 주소체계인경우 점으로 구분된 십진수 값이 있는 텍스트여야함
    *                   IPv6 주소체계인경우 IPv6주소표기법 텍스트여야함
    *
    * pAddrBuf      :   변환한 값을 저장할 버퍼
    *
    * @return
    * SOCKET        :   성공시 1을 반환, 이외의 값은 err
    *
    */
    std::string ip = "192.168.1.211";
    if (1 != inet_pton(AF_INET, ip.c_str(), &sockAddrIn.sin_addr))
    {
        std::cout << "inet pton err!\n";
        return 0;
    }
    

    /*
    * bind
    * 주소정보를 소켓에 연결해주는 함수
    *
    *   int bind(
    *       [in] SOCKET         socket,
    *           const sockaddr *addr,
    *       [in] int            namelen
    *   );
    *
    * @param
    * socket        :   주소정보를 전달받을 소켓
    *
    *
    * addr          :   전달할 주소값 sockaddr구조체 포인터
    *
    * namelen       :   주소값의 길이
    *
    * @return
    * int           :   성공시 0을 반환, 실패할경우 SOCKET_ERROR반환
    *
    */
    if (SOCKET_ERROR == bind(acceptSocket, (const sockaddr*)&sockAddrIn, sizeof(SOCKADDR_IN)))
    {
        std::cout << "socket bind err!\n";
        return 0;
    }
    
    /*
    * listen
    * 소켓을 수신 가능상태로 바꿔주는 함수
    *
    *   int WSAAPI listen(
    *     [in] SOCKET socket,
    *     [in] int    backlog
    *   );
    *
    * @param
    * socket    :   수신상태로 바꿀 소켓
    *         
    * backlog   :   보류중인 연결대기열의 최대 길이
    *          
    * @return  
    * int       :   성공시 0을 반환, 실패할경우 SOCKET_ERROR반환
    *
    */
    if (SOCKET_ERROR == listen(acceptSocket, 512))
    {
        std::cout << "socket listen err!\n";
        return 0;
    }

    // 클라이언트 요청을 받는 함수 실행
    std::cout << "서버 접속 함수 실행" << std::endl;
    SOCKADDR_IN userAddrIn = { 0, };
    int len = sizeof(SOCKADDR_IN);

    // 클라이언트 요청에 대한 소켓 반환
    // 서버 통신 대기 함수
    SOCKET sessionSocket = accept(acceptSocket, (sockaddr*)&userAddrIn, &len);
    if (INVALID_SOCKET == sessionSocket)
    {
        std::cout << "session socket Error" << std::endl;
        return 0;
    }


    std::cout << "접속자가 있습니다" << std::endl;

    /*
        * send
        * 연결된 소켓에 데이터 전달함수
        *
        * int send(
        *   SOCKET      s       
        *   const char* buf     
        *   int         len     
        *   int         flags   
        *   );
        *
        * @param
        * SOCKET        :   데이터 전송대상과의 연결을 의미하는 소켓
        * 
        * const char*   :   전송할 데이터를 저장하고 있는 버퍼 주소값
        * 
        * int           :   전송할 바이트 수
        * 
        * int           :   데이터 전송시 적용할 옵션
        * 
        * @return
        * int           :   성공시 전송된 바이트 수 반환
        *                   실패시 SOCKET_ERROR 반환
        *
        *
    */

    return 0;
}

