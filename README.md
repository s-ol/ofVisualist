ofVisualist started out as a digital implementation of the 'Visualist' analog video effect pedal,
with an added effect of shifting the color mapping in steps.
In development some bugs turned into features and it is now a rather distinct video effect.

[openFrameworks][of] and the [ofxMidi][ofxMidi] extension is required to build this.
The first Camera found on the system is used to stream data, and the first MIDI controller is attached to.

MIDI controls
-------------
- CC27: mix alpha channel between 1.0 and time-rotated luminosity as alpha
- CC28: mix RGB channels between source video and time-rotated hue based on pixel luminosity
- CC41, CC42: lower end and width of the luminosity scale.
- CC43: alpha offset for CC27, lightens an image with dark shadows.
- CC47: time-rotation speed (from fast backwards to fast forward)
- CC48: manual rotation offset, useful when paused
- NoteOn 9: Play/Pause time-rotation

[of]: https://openframeworks.cc/documentation/
[ofxMidi]: https://github.com/danomatika/ofxMidi
