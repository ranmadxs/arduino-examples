import cv2
import numpy as np

img = cv2.imread('prueba01.jpg')
blur = cv2.GaussianBlur(img, (15, 15), 2)
hsv = cv2.cvtColor(blur, cv2.COLOR_BGR2HSV)
lower_green = np.array([37, 0, 0])
upper_green = np.array([179, 255, 255])
mask = cv2.inRange(hsv, lower_green, upper_green)
masked_img = cv2.bitwise_and(img, img, mask=mask)
cv2.imshow('', masked_img)
cv2.waitKey()