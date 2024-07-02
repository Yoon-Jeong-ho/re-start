import requests
from bs4 import BeautifulSoup # 원하는 정보 추출하는 용!
import random
import os # exit 사용
# https://comic.naver.com/webtoon/detail?titleId=725586&no=247&week=fri

days =["mon","tue","wed","thu","fri","sat","sun"]
dic ={}
for i in days:
    url = f"https://comic.naver.com/webtoon?tab={i}"
    res = requests.get(url)
    soup = BeautifulSoup(res.text,"lxml")
    # div 태그 밑에 a를 찾아야 한다.
    print(i)
    #'div.Poster__thumbnail_area--gviWY.Poster__type160x207--EQAM8 > img'
    for j in soup.select('div.Poster__bullet_wrap--VcWFJ > img'):
        print(j)
        subject =j.get('alt') # 웹툰 제목
        number = j.get('src').split('webtoon/')[1].split('/')[0] #id href의 데이터 중간에 있다.
        dic[subject] = number # 저장
        
        
while True:
    for num, i in enumerate(dic,1):
        print(f"{num}.{i}")
    user = input("웹툰을 입력하세요: ")
    if (user == 'q'):
        exit()
    elif user.isnumeric(): #숫자를 입력
        user = int(user)
        if user >=1 and user <=num: # 원하는 범위 내에서 입력
            sel_subject = list(dic.keys())[int(user)-1]# 인덱스는 0부터 시작되는 것 중요1
            print(f"{sel_subject}를 선택하셨습니다.")
            break
        else:
            print("다시 입력하세요.")
    else:
        print("다시 입력하세요")


n= int(input("다운받을 회차를 입력해주세요:"))
f = open(f"{sel_subject}_{n}.html","w",encoding='utf-8')

res = requests.get(f"https://comic.naver.com/webtoon/detail?titleId={dic[sel_subject ]}&no={n}")

f.write(res.text)

print(f"{sel_subject} {n}화 다운로드 완료.")