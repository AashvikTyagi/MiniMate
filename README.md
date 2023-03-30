# MiniMate
Minimate is an open-source companion robot to help people overcome depression. It was developed for ATL Marathon '23 by Aashvik Tyagi and Vivaan Mansukhani.


This repository has all the code we've created till now for Minimate. Minimate isn't just one robot: it is an concept, the idea of a friendly pet robot that cheers you up but doesn't require maintainence.


Our Minimate uses and Arduino Nano in the robot and a desktop computer for processing text and speech, so the two files you'll find in this repository are the file for the code that runs on our Nano, which has functions for moving and dancing, and the python file that runs on the computer, which listens for Commands and instructs the Arduino over Serial
We have used services from picovoice for the voice-control and pyttsx3 for text-to-speech.
This base can even be combined with other services to create different Minimates!

These are constantly being updated, with new features like searching the web for news and exploring the environment coming along the way.
