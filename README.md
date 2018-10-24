# BullCowGame

https://www.udemy.com/unrealcourse/learn/v4/t/lecture/4385598?start=0

Enhanced version of the Bull cow game developed in section 2 of the Udemy course. Features beyond the course:
- Game stores previous guesses and tells the player if they are repeating a guess
- Player can choose a word length at the start of the game
- The game starts with the hidden word as an isogram from the 'SOWPODS' https://www.wordgamedictionary.com/sowpods/ word list of the right length.

Potential future enhancements:
- Create a dictionary handler class, rather than hiding everything in BCGame
- Better info to player, and a nicer interface. 

Notes from Daniel at Udemy... 
A couple of improvements you could make

1. Instead of std::stoi you should use the new std::from_chars from C++17, It's fast, non-throwing and non-allocating. So you don't need the try/catch block.

2. Instead of several isogram.txts just have one. Load them into a std::vector and then just filter the word lengths either by using std::find or work out their positions and save those.