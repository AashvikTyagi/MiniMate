# this is the minimate code that runs on the computer!
# again, these codes are samples: a lot more can be done with them
# in another update i'll be commenting more lines to explain code
# TODO: use serial over bluetooth instead of usb so minimate can move around

from pvrecorder import PvRecorder
import pvrhino, pvcheetah
from joke.jokes import geek, icanhazdad, chucknorris, icndb
from random import choice
import pyttsx3
import serial

print('\n\n\n\n\n')

engine = pyttsx3.init()

ultimateJoke = lambda jokeType=choice([geek, icanhazdad, chucknorris, icndb]): jokeType()

# this is the port my arduino is connected to
arduino = serial.Serial('/dev/cu.wchusbserial220',115200)

# sorry, i'm not giving away my access key!
key='PICOVOICE_CODE'

cheetah = pvcheetah.create(access_key=key)
rhino = pvrhino.create(
    access_key=key,
    context_path='Mini-Mate-Commands_en_mac_v2_1_0.rhn'
)

# replace the sound device string with the name of your mix
# run print(PvRecorder.get_audio_devices()) to get a list of connected devices
recorder = PvRecorder(device_index=PvRecorder.get_audio_devices().index('USB PnP Sound Device'),frame_length=512)
recorder.start()

# I made a function for this so that the recorder wouldnt spam errors
def say(x): 
    recorder.stop()
    engine.say(x)
    engine.runAndWait()
    recorder.start()

say("Minimate Ready!")

def getNextAudioFrame():
    return recorder.read()

def jokeAround():
    arduino.write(b'j')
    print('jo')
    say(ultimateJoke())

def dance():
    arduino.write(b'd')
    print('da')
    say('One can not but dance in such a situation')

def spin():
    arduino.write(b's')
    print("sp")
    say('Spinnnny')

# this function is being updated!
def search():
    print('se')
    say(f'So you wanna know about {cheetah.flush()}, huh?')

while True:
    audioFrame = getNextAudioFrame()
    isFinalized = rhino.process(audioFrame)
    isEndpoint = cheetah.process(getNextAudioFrame())[1]
    if isFinalized:
        inference = rhino.get_inference()
        if inference.is_understood:
            recorder.stop()
            intent = inference.intent
            slots = inference.slots
            recorder.start()
            print(f"\n\nintent: {intent}\nslots: {slots}\n\n")
            match intent:
                case 'do':
                    if 'joke' in list(slots.values()):
                        jokeAround()
                    elif 'dance' in list(slots.values()):
                        dance()
                    elif 'spin' in list(slots.values()):
                        spin()
                case 'search':
                    if isEndpoint:
                        print(cheetah.flush())

rhino.delete()
cheetah.delete()