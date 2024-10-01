import cv2
import time
c_time = 0
p_time = 0
def show_image(img):
    #SHOW FPS
    global c_time, p_time
    c_time = time.time()
    fps = 1/(c_time-p_time)
    p_time = c_time
    cv2.putText(img, str(int(fps)), (1250, 700), cv2.FONT_HERSHEY_PLAIN, 1, (0, 255, 0),2)

    #SHOW IMAGE
    cv2.imshow("Image", img)
    cv2.waitKey(1)

