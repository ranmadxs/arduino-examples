import numpy as np
import cv2

img = cv2.imread('hand2.jpg', 1)

gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
blur = cv2.GaussianBlur(gray,(5,5),0)
ret,thresh1 = cv2.threshold(blur,70,255,cv2.THRESH_BINARY_INV+cv2.THRESH_OTSU)
cv2.imshow('Corner-Gray',thresh1)
gray = np.float32(gray)

corners = cv2.goodFeaturesToTrack(gray, 100, 0.01, 10)
corners = np.int0(corners)

print "corners: %d"%len(corners)

for corner in corners:
    x,y = corner.ravel()
    print "(%d, %d)"%(x, y)
    cv2.circle(img,(x,y),3,255,-1)
    
cv2.imshow('Corner',img)

cv2.waitKey(0)
cv2.imwrite("corners.jpg",img)
cv2.destroyAllWindows()