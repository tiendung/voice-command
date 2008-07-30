[Userguide]
This the demo of how speech recognition can used in a 3D game.
You can use your voice to control a character (the yello monster).
After you run "bin/3dGameEngine.exe"
Press right mouse button to start HTK speech recognition engine
Say one of the following commands:
{jump, pain, point, salute, stand} to control the monster
close} to close the app

[Speech Recognition]
I link Hvite to my app via share-memory.
I used Vietnamese acoustic models (HMMs) for Englishs command because I do not have database and time for training.
So, the accuracy is not so high.


[Other information]
"src" contains the source code.
"src/bokken" contains "bokken game engine" written by myself. I tried to apply computer gaphics knowledge and software engineering when building this simple eingine
