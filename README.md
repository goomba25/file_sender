# file_sender
c++ file transfer program using socket communication

### study order

1. client to server (string)
2. client to server (file)
3. client to server (file) - multithread
4. client to server (multi file) - multithread

### 소켓

* 소켓 생성
* 소켓 바인딩 (bind)
* 연결 대기 (listen)
* 연결 수락 (accept)
* 데이터 송수신 (send, recv)
* 연결 종료 (close)

### 최소 소켓 개수

1. 연결부터 대기까지 역할을 수행하는 소켓
2. 수락 및 데이터 교환 소켓
3. 클라이언트로부터 서버와 통신할 소켓

### 최종

Server는 정해진 폴더 위치를 지정하면서 실행될 수 있도록.
Client는 여러 파일을 지정하면서 실행될 수 있도록.