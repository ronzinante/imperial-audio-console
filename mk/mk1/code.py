import board
import audiocore
import digitalio
import audiobusio
import time

# LEDs
led = digitalio.DigitalInOut(board.LED)
ledPillar = digitalio.DigitalInOut(board.GP0)
led.direction = digitalio.Direction.OUTPUT
ledPillar.direction = digitalio.Direction.OUTPUT

# Button
button = digitalio.DigitalInOut(board.GP1)
button.switch_to_input(pull=digitalio.Pull.DOWN)

led.value = True
ledPillar.value = False

# I2S pins
bit_clock = board.GP13
word_select = board.GP14
data = board.GP15

# Initialize I2S output
i2s = audiobusio.I2SOut(
    bit_clock=bit_clock,
    word_select=word_select,
    data=data
)

# Open WAV file once
f = open("output8k.wav", "rb")
wav = audiocore.WaveFile(f)

while True:
    if button.value:  # button pressed
        ledPillar.value = True

        i2s.play(wav, loop=False)

        while i2s.playing:
            time.sleep(0.01)

        ledPillar.value = False

        # rewind WAV so it can play again
        wav = audiocore.WaveFile(f)

        # wait for button release (debounce)
        while button.value:
            time.sleep(0.05)

