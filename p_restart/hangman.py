import time
import csv
import random
import winsound

name = input("What is your name?")

print("Hi ",name,'Time to play hangman game!')

print()

time.sleep(1)

print("start Loading...")
print()
time.sleep(1)

words = []

with open('./resource/word_list.csv','r') as f:
    reader = csv.reader(f)
    next(reader)
    for c in reader:
        words.append(c)

random.shuffle(words)
q = random.choice(words)
    


word = q[0].strip ()
print(word)

guesses = ''

turns = 10

while turns>0 :
    failed = 0
    for char in word:
        if char in guesses:
            print(char, end =' ')
        else:
            print("_",end = ' ')
        failed+=1
    if failed == 0:
        print()
        print()
        winsound.playsound('./sound/good.wav',winsound.SND_FILENAME)
        print('Congratulations! The Guesses is correct')
        
        break
    print()

    print()
    print('Hint : {}'.format(q[1].strip()))
    guess = input("guess a charater.")
    guesses+= guess

    if guess not in word:
        turns -=1
        print("Oops! Worng")
        print("You have", turns, 'more gusses!' )

        if turns==0:
            print("you hangman game failed. Bye!")
            winsound.playsound('./sound/bad.wav',winsound.SND_FILENAME)





