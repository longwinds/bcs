#include "StdAfx.h"
#include "WavPlayer.h"

DWORD WINAPI call_player_thread(LPVOID pvoid)
{
	TRACE("%s \r\n",__FUNCTION__);
	CWavPlayer* pobj = (CWavPlayer*)pvoid;
	pobj->player_thread();
	return 0;
}


CWavPlayer::CWavPlayer(void)
{
}

CWavPlayer::~CWavPlayer(void)
{
}

int CWavPlayer::player_thread(void)
{
	TRACE("%s start\r\n",__FUNCTION__);
	do
	{
		if(WAIT_OBJECT_0 == WaitForSingleObject(m_h_event_player_exit,0))
		{
			TRACE("%s exit 0\n",__FUNCTION__);
			return 0;
		}
		get_pcm_samples();
		send_pcm_samples();
		Sleep(500);
	}while (1);
	TRACE("%s exit 1\n",__FUNCTION__);
	return 0;
}

int CWavPlayer::start(void)
{
	m_h_event_player_exit = CreateEvent( 
		NULL,               // default security attributes
		FALSE,               // manual-reset event
		FALSE,               // initial state is signaled
		NULL				 // object name
		); 

	if (m_h_event_player_exit == NULL) 
	{ 
		TRACE("Create receiver exit Event failed (%d)\n", GetLastError());
		return -1;
	}
	DWORD id;
	TRACE("%s \r\n",__FUNCTION__);
	m_h_thread_player = CreateThread( 
		NULL,              // default security attributes
		0,                 // use default stack size  
		call_player_thread,          // thread function 
		this,             // argument to thread function 
		0,                 // use default creation flags 
		&id);   // returns the thread identifier 
	if (m_h_thread_player == NULL) 
	{
		TRACE("create receiver thread err:%d\r\n",GetLastError());
		return -1;
	}
	m_sock = socket(AF_INET,SOCK_DGRAM,0); 
	// set rcv timeout
	int nTvlen=200;  //1s
	setsockopt(m_sock,SOL_SOCKET,SO_RCVTIMEO,(const char*)&nTvlen, sizeof(nTvlen));

	return 0;
}

int CWavPlayer::get_pcm_samples(void)
{

	return 0;
}

int CWavPlayer::send_pcm_samples(void)
{
	/*if (sendto(m_sock,(char*)buf,len,0,(struct sockaddr*)&addr_remote,sock_len)!=SOCKET_ERROR)
	{
		rcv_len = recvfrom(m_sock,(char*)rcv_buf,sizeof(rcv_buf),0,(struct sockaddr*)&addr_remote,&sock_len);
		if (rcv_len >0 )
		{
			printf("rcv from server[%d]\n",rcv_len);
			memcpy(&crc,rcv_buf+DH_CRC_P,2);
			crc = ntohs(crc);
			memset(rcv_buf+DH_CRC_P,0,2);
			if(crc != dh_crc16(rcv_buf,rcv_len))
			{
				TRACE("%s,crc err:%04X->%04X\r\n",__FUNCTION__,crc,dh_crc16(rcv_buf,rcv_len));
			}
		}
	}*/
	return 0;
}
