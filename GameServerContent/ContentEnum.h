#pragma once

// 컨텐트 패킷의 enum 이름은 항상 E로 시작해야함

enum class EResultCode
{
	NONE = -1,
	ID_ERROR,
	PW_ERROR,
	OK,
	FAIL,
	MAX
};
