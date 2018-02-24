#pragma once

class CWavPlayer
{
public:
	CWavPlayer(void);
	~CWavPlayer(void);
	int player_thread(void);
	int start(void);
	HANDLE m_h_event_player_exit;
	HANDLE m_h_thread_player;
	SOCKET m_sock;
	int get_pcm_samples(void);
	int send_pcm_samples(void);
};
