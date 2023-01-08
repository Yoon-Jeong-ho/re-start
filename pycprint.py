print('hi')
print("hii")
print('''hi''')
print()
print("""hi""")

# separator

print('p','y','t')

print('p','y','t',sep=',')

# end 마지막이 엔터말고 이어 줄 수 있음

print('welcome to',end=' 12 ')
print('IT news',end=' ')
print("web Site")

# file (import) (sys.stdout 콘솔에 적음 파일에 작성할 때 사용 나중에)
import sys

print('Learn Python', file=sys.stdout)

# format(d 정수:3,s 문자열:python,f 실수:3.14,o .....)
print('%s %s'%('wer','werw'))
print('{} {}'.format('wer','werd'))
print('{1} {0}'.format('wer','werde'))
# %s
print('%10s'%('asdf'))
print('%10s'%('123456789101112'))
print('{:>10}'.format('123456789101112'))


print('%-10s'%('asdf')) 
print('%-10s'%('123456789101112'))
print('{:10}'.format('123456789101112'))

print('{:->10}'.format('12345'))
print('{:^10}'.format('12345'))
print('{:.^10}'.format('12345'))

print('%.10s'%('123456789101112'))
print('{:10.5}'.format('123456789101112'))

# %d %f 똑같이 됨
print('%f'%(3.123456789))
print('{:f}'.format(3.123456789))

print('%1.3f'%(3.123456789))
print('{:1.3f}'.format(3.123456789))

print('%08.3f'%(3.123456789))