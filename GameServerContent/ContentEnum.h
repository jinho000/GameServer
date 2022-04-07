#pragma once

// ����Ʈ ��Ŷ�� enum �̸��� �׻� E�� �����ؾ���

enum class EResultCode
{
	NONE = -1,
	OK,
	FAIL,
	MAX
};

enum class ELoginResultCode
{
	FAIL,
	ID_ERROR,
	PW_ERROR,
	OK,
	MAX
};

enum class EJoinResultCode
{
	FAIL,
	ID_DUPLE,
	OK,
	MAX
};

enum class ECreateCharacterResultCode
{
	FAIL,
	ID_DULE,
	OK,
	MAX
};
