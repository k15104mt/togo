#include<winsock.h>
#include<cstdio>
#include<string>
#include <fstream>

int main() {
  WSADATA wsadata;
  struct sockaddr_in server;
  SOCKET sock;


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
  char input[32], ips[32];
  int ip[4], flag = 1;
  do {
	memset(input, '0', 32);
	printf("IP�A�h���X����͂��Ă�������-->");
	fgets(input, 32, stdin);
	sscanf_s(input, "%d.%d.%d.%d\n", &ip[0], &ip[1], &ip[2], &ip[3]);
	sprintf_s(ips, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
	printf("IP=%s ok?(yes = 1/no = 0)-->", ips);
	fgets(input, 32, stdin);
	sscanf_s(input, "%d\n", &flag);

  } while (flag == 0);



  // �ڑ���w��p�\���̂̏���
  server.sin_family = AF_INET;
  server.sin_port = htons(60000);
  server.sin_addr.S_un.S_addr = inet_addr(ips);

  // �\�P�b�g�̍쐬
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == INVALID_SOCKET) {
	printf("error(socket) : %d\n", WSAGetLastError());
	return 1;
  }
  else {
	// �T�[�o�ɐڑ�
	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) != 0) {
	  printf("connect : %d\n", WSAGetLastError());
	}
	else {
	  std::ofstream writer;
	  writer.open("out.txt", std::ios::out);

	  char input[1024];
	  recv(sock, input, 1024, 0);
	  int num;
	  sscanf_s(input, "%d", &num);
	  writer << num << "\n";
	  for (int i = 0; i < num; ++i) {
		memset(input, 0, sizeof(char) * 1024);
		recv(sock, input, 1024, 0);
		writer << input << "\n";
		printf("\n--------\n%s\n--------\n", input);
	  }

	}
  }

  closesocket(sock);

  // winsock2�̏I������
  WSACleanup();

  return 0;
}