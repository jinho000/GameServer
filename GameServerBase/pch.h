#pragma once

// OS 기본
#define _WINSOCK_DEPRECATED_NO_WARNINGS // gethost함수 사용

#include <WS2tcpip.h> // inet_pton 함수를 사용하기 위한 헤더
#include <WinSock2.h>
#include <Windows.h> // 아래쪽에 놔야 합니다.
#include <MSWSock.h>
#include <iostream>

// 쓰레드
#include <thread>
#include <mutex>
#include <memory>
#include <process.h>
#include <atomic>

// 수학
#include <math.h>
#include <random>

// 자료구조
#include <list>
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <string_view>
#include <sstream>
#include <deque>

// 디버깅
#include <functional>
#include <assert.h>
#include <cassert>
#include <crtdbg.h>

// 메모리 릭 검출 라이브러러
//#include <vld.h>


#pragma comment (lib, "ws2_32") // 서버통신용 구현이 들어있는 라이브러리
#pragma comment (lib, "mswsock.lib")
