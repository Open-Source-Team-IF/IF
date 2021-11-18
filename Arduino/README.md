# 로드셀 결선 방법
> 빨간색과 검은색은 E에 결선하고 초록색과 하얀색은 A에 결선한다.
>
>
> ![image](https://user-images.githubusercontent.com/37334007/141078242-3a48a7d0-cde6-49de-849a-1e1b28f48a7f.png)
> ![image](https://user-images.githubusercontent.com/37334007/142414814-73a9f329-5123-4afa-a630-9bff5e7280c7.png)

## 로드셀 라이브러리 import
> HX711.h 파일을 다운로드 후 import
> ![image](https://user-images.githubusercontent.com/37334007/141078321-25a782c6-95b4-4242-bd4f-6aeed059198a.png)

# 라인트레이싱 결선 방법
> + TB6612FNG 모터드라이브를 기준작성하였다. <br>
>   * AIN, BIN : 바퀴의 방향을 조절 (정방향 / 역방향) <br>
>   * PWMA, PWMB : 바퀴의 세기를 조절 <br>
>   * STB : 모터의 완전정지에 사용 (사용하지 않아도 무방) <br>
> + 아두이노를 이용해 IN, PWM 에 값을 입력하여주면 Output PIN을 통하여 모터 제어가 가능하다.
> ![image](https://user-images.githubusercontent.com/37334007/141080347-0a801f15-aa1e-4b46-bfe8-139adb28470c.png)
> ![image](https://user-images.githubusercontent.com/37334007/141081223-07ce5435-f928-473b-a001-9a97f794579a.png)



