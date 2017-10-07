#include<windows.h>
#include<cstdio>
#include<iostream>
#include <string> 
#include <fstream>
#include<vector>


int main() {
  std::ifstream readstream;
  readstream.open("out.txt", std::ios::in);

  std::vector<std::string> input;
  std::cout << "------" << std::endl;
  while (!readstream.eof()) {
	std::string tmp;
	std::getline(readstream, tmp);
	input.push_back(tmp);
	std::cout << tmp << std::endl;
	std::cout << "------" << std::endl;
  }

  WSADATA wsadata;
  SOCKET sock, sock0;
  struct sockaddr_in addr, client;
  int len;

  //������
  int err;
  if (err = WSAStartup(MAKEWORD(2, 0), &wsadata) != 0) {
	switch (err) {
	case WSASYSNOTREADY:
	  //�l�b�g���[�N�T�u�V�X�e�����l�b�g���[�N�ւ̐ڑ��������ł��Ă��Ȃ�
	  printf("WSASYSNOTREADY\n");
	  break;
	case WSAVERNOTSUPPORTED:
	  //�v�����ꂽwinsock�̃o�[�W�������T�|�[�g����Ă��Ȃ�
	  printf("WSAVERNOTSUPPORTED\n");
	  break;
	case WSAEINPROGRESS:
	  //�u���b�L���O����̎��s���ł��邩�A �܂��̓T�[�r�X�v���o�C�_���R�[���o�b�N�֐����������Ă���
	  printf("WSAEINPROGRESS\n");
	  break;
	case WSAEPROCLIM:
	  //winsock�������ł���ő�v���Z�X���ɒB����
	  printf("WSAEPROCLIM\n");
	  break;
	case WSAEFAULT:
	  //�������ł���lpWSAData �͗L���ȃ|�C���^�ł͂Ȃ�
	  printf("WSAEFAULT\n");
	  break;
	}
	return 1;
  }


  //�\�P�b�g�̍쐬
  sock0 = socket(AF_INET, SOCK_STREAM, 0);
  if (sock0 == INVALID_SOCKET) {
	printf("error(socket) : %d\n", WSAGetLastError());
	//return 1;
  }


  //�\�P�b�g�̐ݒ�
  addr.sin_family = AF_INET;
  addr.sin_port = htons(60000);
  addr.sin_addr.S_un.S_addr = INADDR_ANY;

  //******************************************************
  char name[32];
  struct hostent *hostent1;
  struct in_addr inaddr1;

  gethostname(name, sizeof(name));

  hostent1 = gethostbyname(name);
  for (int i = 0; (hostent1->h_addr_list[i]) != NULL; ++i) {
	inaddr1.S_un.S_addr = **(unsigned int **)(hostent1->h_addr_list + i);

	printf("IP�A�h���X %d = %s\n", i, inet_ntoa(inaddr1));
  }
  printf("�|�[�g�ԍ� = %d\n", ntohs(addr.sin_port));
  //******************************************************



  //TIME_WAIT��Ԃ̃|�[�g�����݂��Ă��Ă�bind���ł���悤�ɂ���
  BOOL T = 1;
  setsockopt(sock0, SOL_SOCKET, SO_REUSEADDR, (const char *)&T, sizeof(T));

  if (bind(sock0, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
	printf("error(bind) : %d\n", WSAGetLastError());
	//return 1;
  }


  //TCP�N���C�A���g����̐ڑ��v����҂Ă��Ԃɂ���
  if (listen(sock0, 5) != 0) {
	printf("error(listen) : %d\n", WSAGetLastError());
	//return 1;
  }


  while (1) {
	//TCP�N���C�A���g����̐ڑ��v�����󂯕t����
	printf("----------------------------\nWaiting...\n");
	len = sizeof(client);
	sock = accept(sock0, (struct sockaddr *)&client, &len);
	printf("Connecting...\n");
	if (sock == INVALID_SOCKET) {
	  printf("error(accept) : %d\n", WSAGetLastError());
	  //return 1;
	}
	else {
	  //accept��������̊m�F
	  printf("accepted connection from %s, port=%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

	  //�s�[�X�̐��������Ő�ɑ���
	  for (int i = 0; i < 4; ++i) {
		send(sock, input[i].c_str(), 1024,0);
	  }
	  
	}
	printf("End\n");
	closesocket(sock);
  }

  closesocket(sock0);

  // winsock2�̏I������
  WSACleanup();


  return 0;
}