# [Platinum V] PSAT 특별과정 - 28073 

[문제 링크](https://www.acmicpc.net/problem/28073) 

### 성능 요약

메모리: 87092 KB, 시간: 924 ms

### 분류

너비 우선 탐색, 그래프 이론, 그래프 탐색

### 제출 일자

2024년 2월 17일 01:18:14

### 문제 설명

<p>서강대학교 알고리즘 학회 Sogang ICPC team의 학회장인 회윤이는 학회원 중 백준 채점 현황이 마음에 들지 않는 학생들을 모아 특훈을 시키려고 한다.</p>

<p>훈련 과정의 이름은 PSAT(PS Aaak Training)으로 대답은 <span style="color:#e74c3c;"><code>Aaak!</code></span>으로 통일한다.</p>

<p>훈련 참가자는 각 문제를 풀면 자신의 티켓에 알파벳이 하나 적힌 도장을 받을 수 있으며, 조건에 맞게 순서대로 문제를 풀어 문자열을 만들고, 문자열이 특정 조건에 맞으면 훈련을 수료할 수 있다.</p>

<p>조건에 맞는 문자열의 시작 알파벳인 $S$와 마지막 알파벳인 $E$는 이미 정해져 있기 때문에 참가자들은 모두 $S$의 도장을 찍어주는 문제들 중 하나에서 시작한다. 그리고 각 문제마다 연결된 문제들이 정해져 있어서 연결된 문제들 중 하나만 골라서 풀 수 있다.</p>

<p style="text-align: center;"><img alt="" src=""></p>

<p>예를 들어 위와 같은 구조로 훈련 과정을 구성했고, $S$는 <code>S</code>, $E$는 <code>C</code>로 정했다면 가장 왼쪽의 1번 문제에서 시작해 1번 → 3번 → 2번 → 4번 문제의 순서로 풀어 <span style="color:#e74c3c;"><code>SUPC</code></span>의 문자열을 완성하여 훈련을 수료할 수 있다. 물론 <span style="color:#e74c3c;"><code>SPPDC</code></span>, <span style="color:#e74c3c;"><code>SPSUC</code></span> 등도 가능하다.</p>

<p>호영이도 최근 채점 현황이 처참해서 훈련에 참가하게 됐다. 호영이는 자칫하면 사이클에 빠져 무한히 문제를 풀지도 모르는 이 지옥 훈련을 빨리 끝내고 싶었기 때문에 미리 코스의 정보를 알아 왔다. 일단 빨리 끝내는 게 목적이기 때문에 가장 짧은 코스로 끝내되, 그런 코스들 중 사전 순으로 가장 앞서는 문자열을 만들어 내는 코스로 가고 싶다. 예를 들어 위 코스에서는 <span style="color:#e74c3c;"><code>SPC</code></span>와 <span style="color:#e74c3c;"><code>SUC</code></span>가 가장 짧은 코스의 문자열이지만 그중 <span style="color:#e74c3c;"><code>SPC</code></span>가 사전 순으로 더 앞서기 때문에 <span style="color:#e74c3c;"><code>SPC</code></span>라는 문자열을 만들어 수료하게 된다.</p>

<p>채점 현황이 형편없는 호영이는 지금 만들어진 이 문제도 풀고 싶지 않다. 따라서 어떤 문자열을 만들어 수료하게 될지는 당신이 구해야 한다.</p>

### 입력 

 <p>첫 번째 줄에 문제의 개수 $N$ $(2 \le N \le 1\,000\,000)$과 문제의 연결 관계의 수 $M$ $(0 \le M \le \min(1\,000\,000,\cfrac{N(N-1)}{2}))$이 공백으로 구분되어 주어진다. 각 문제는 1번부터 차례대로 $N$번까지 번호가 매겨진다.</p>

<p>두 번째 줄에 수료하기 위한 문자열의 조건인 시작 문자 $S$와 종료 문자 $E$가 공백으로 구분되어 주어진다.</p>

<p>세 번째 줄에 각 문제들을 풀었을 때 찍어주는 도장의 알파벳을 나타내는 N개의 알파벳이 1번 문제부터 $N$번 문제까지 공백 없이 차례로 주어진다.</p>

<p>$S$, $E$와 도장의 알파벳들은 전부 알파벳 대문자이며, $S$와 $E$에 해당하는 도장이 각각 적어도 한 개는 있다. 또 $S$와 $E$는 같은 문자일 수 있다.</p>

<p>네 번째 줄부터 $M + 3$번째 줄까지 서로 연결된 두 문제의 번호 $u$, $v$ $(1 \le u < v \le N)$가 공백으로 구분되어 주어진다. 이때 연결에 방향은 없다. 즉, $u$번 문제를 푼 후 $v$번 문제를 풀 수도 있고, $v$번 문제를 푼 후 $u$번 문제를 풀 수도 있다.</p>

### 출력 

 <p>첫 번째 줄에 문제의 조건에 맞는 문자열을 출력한다.</p>

<p>단, 조건에 맞는 문자열을 만들어 낼 수 없다면 <span style="color:#e74c3c;"><code>Aaak!</code></span>을 출력한다.</p>

