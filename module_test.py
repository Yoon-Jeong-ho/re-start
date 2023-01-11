#모듈 사용 실습

import sys
print(sys.path)
sys.path.append(r'C:\Users\k\OneDrive\문서\re-start')
print(sys.path)
import oop_module_package   # print 출력을 막기 위해서는 원문에 가서 if __name__ == '__main__': 를 프린트문 앞에 넣어야됨


print(oop_module_package.power(10,2))