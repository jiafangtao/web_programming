import sys
import av


if len(sys.argv >= 2):
    path_to_video = sys.argv[1]
else:
    path_to_video = input("Please input the path of the video file:")

if not path_to_video:
    sys.exit(1)

container = av.open(path_to_video)

for frame in container.decode(video=0):
    frame.to_image().save('frame-%04d.jpg' % frame.index)
