import cv2
import numpy as np

cam = cv2.VideoCapture(0)
cam.set(3, 640)
cam.set(4, 480)
ret, image = cam.read()

skin_min = np.array([0, 40, 150], np.uint8)
skin_max = np.array([20, 150, 255], np.uint8)

while True:
	ret, image = cam.read()
	gaussian_blur = cv2.GaussianBlur(image, (5, 5), 0)
	blur_hsv = cv2.cvtColor(gaussian_blur, cv2.COLOR_BGR2HSV)
	
	tre_green = cv2.inRange(blur_hsv, skin_min, skin_max)
	__, contours, hierarchy = cv2.findContours(tre_green, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
	
	print(len(contours))
	
	cv2.drawContours(image, contours, -1, (0, 255, 0), 3)
	cv2.imshow('real', image)
	cv2.imshow('tre_green', tre_green)
	
	key = cv2.waitKey(10)
	if key == 27:
		break