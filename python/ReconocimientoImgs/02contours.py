import numpy as np
import cv2

# Load an color image in grayscale
img = cv2.imread('test.jpg', 0)
cv2.imshow('test.jpg',img)

ret,thresh = cv2.threshold(img,127,255,0)
(imageCountours,contours, hierarchy) = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
totalContornos = len(contours)
cnt = contours[0]
lenCnt = len(cnt)
print "Contornos: %d   lenCnt: %d" % (totalContornos, lenCnt)
cv2.drawContours(img,contours,-1,(0,255,0),-1)
cv2.imshow('output',img)
cv2.waitKey(0)
cv2.imwrite("contourn.jpg",img)
cv2.destroyAllWindows()