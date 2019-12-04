# BaseballGame
BaseballGame Repository 는 CodeSquard 의 마스터즈 코스 온라인 테스를 위한 저장소입니다.  
step-1 Branch 는 야구게임 만들기 1단계에 해당하는 *step-1* 에 대한 요구사항을 구현 한 브랜치 입니다.  
## 각 Class 설명
### BaseballGameManager Class
Pitching Result/OfficialScorer/ScoreBoard/StatusPrinter 객체 생성 및  
step-1 의 시나리오를 만족하기 위한 flow 가 구현 되는 class 이다.
### PitchingResultGenerator Class
각 투구의 결과를 랜덤하게 생성하는 역할을 하는 class 이다.  
랜덤하게 생성되는 투구의 결과는 아래와 같다.  
* Strike
* Ball
* Hits (안타)
* Out
### OfficialScorer Class
PitchingResultGenerator 클래스로부터 생성 된 투구 결과를 토대로 ScoreBoard 의 값을 조작하는 class 이다.  
조작하는 값은 아래와 같다.  
* Strike 를 전달 받았을 때
** ScoreBoard 객체의 Strike Count 를 1 증가시킨다.
*** ScoreBoard 의 Strike Count 를 1 증가시킨 후의 값이 3 이면 Strike/Ball Count 를 0 으로 만들고 Out Count 를 1 증가시킨다.
* Ball 을 전달 받았을 때
** ScoreBoard 의 Ball Count 를 1 증가시킨다.
*** ScoreBoard 의 Ball Count 를 1 증가시킨 후의 값이 4 면 Strike/Ball Count 를 0 으로 만들고 Hits Count 를 1 증가시킨다.
* Hits Count 를 전달 받았을 때
** ScoreBoard 의 Hits Count 를 1 증가시킨 후 Strike/Ball Count 를 0 으로 만든다.
* Out Count 을 전달 받았을 때
** ScoreBoard 의 Out Count 를 1 증가시킨다.
### ScoreBoard Class
경기중 상태 (Strike/Ball/Out) 및 안타 (Hits) 수를 저장하고 있는 class 이다.  
저장되는 값은 아래와 같다.
* Strike Count
* Ball Count
* Hits Count
* Out Count
### StatusPrinter Class
Console 창에 경기 상태에 대한 내용을 사용자에게 알려주기 위한 class 이다.  
![StatusPrinter](https://user-images.githubusercontent.com/58318174/70122836-aec08b80-16b4-11ea-814e-87352ae8f29b.png)
