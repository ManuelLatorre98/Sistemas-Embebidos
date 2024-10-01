import cv2
import showImage as shi
import humanDetector as hd
capture = cv2.VideoCapture(0)
human_detector= hd.HumanDetector()
print("START!")
while True:
  success, img = capture.read()
  img = cv2.imread('messi2.jpg')
  img = human_detector.findLandMarks(img)
  img = human_detector.draw_bounding_box(img)
  human_detector.calculate_distance(img)
  print(human_detector.calculate_angle_from_center(img))
  shi.show_image(img)