//
// title	:	Ŀ�θ�忡�� ������忡 �����͸� ���� �� 
//				��������� ó������� ������ �� �ֵ��� ���ִ� Ŀ�� DLL
// author	:	Ŀ�θ���Ʈ.�ܺ�
// version	: 0.0.2.0


#pragma once


extern "C"
{
#include <ntddk.h>
#include <wdm.h>
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef void (NTAPI* FN_ONUSERCONNECT)(
	IN	HANDLE			processId,
	IN	PVOID			pContext
	);

typedef void (NTAPI* FN_ONUSERDISCONNECT)(
	IN	HANDLE			processId,
	IN	PVOID			pContext
	);

typedef NTSTATUS (NTAPI* FN_ONUSERIOCTL)(
	IN	ULONG			controlCode,
	IN	PVOID			pInputBuffer,
	IN	ULONG			inputBufferSize,
	OUT	PVOID			pOutputBuffer,
	IN	ULONG			outputBufferSize,
	IN	PVOID			pContext
	);

typedef struct _KNCOMM_CB_INFO
{
	FN_ONUSERCONNECT	pfnOnUserConnect;
	FN_ONUSERDISCONNECT	pfnOnUserDisconnect;
	FN_ONUSERIOCTL		pfnOnUserIoctl;
	PVOID				pCallbackContext;

} KNCOMM_CB_INFO, *PKNCOMM_CB_INFO;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NTSTATUS
NTAPI
ConnectToKnComm(
	IN	PCWSTR			pUniqueName,
	IN	PKNCOMM_CB_INFO	pKnCommInfo,
	OUT	PULONG			pKernelModeId
	);

NTSTATUS
NTAPI
DisconnectFromKnComm(
	IN	ULONG			kernelModeId
	);

NTSTATUS
NTAPI
SendToUserViaKnComm(
	IN	ULONG			kernelModeId,
	IN	PVOID			pSendData,
	IN	SIZE_T			sendDataSize,
	IN	BOOLEAN			waitReply,
	IN	LONG			waitTimeOutMS,
	OUT	PVOID*			ppReplyData,		// must Release by ReleaseKnCommDataBuffer
	OUT	PSIZE_T			pReplyDataSize
	);

void
ReleaseKnCommDataBuffer(
	IN	PVOID			pBuffer
	);