import cv2
import numpy as np
from django.template.defaultfilters import center
from array import array

imageName = "imgs/hand2F.jpg";
image = cv2.imread(imageName)


skin_min = np.array([0, 40, 150], np.uint8)
skin_max = np.array([20, 150, 255], np.uint8)
#skin_min = np.array([234, 204, 219], np.uint8)
#skin_max = np.array([84, 61, 66], np.uint8)


gaussian_blur = cv2.GaussianBlur(image, (5, 5), 0)
blur_hsv = cv2.cvtColor(gaussian_blur, cv2.COLOR_BGR2HSV)

tre_green = cv2.inRange(blur_hsv, skin_min, skin_max)
__, contours, hierarchy = cv2.findContours(tre_green, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

count = 0
font = cv2.FONT_HERSHEY_SIMPLEX
print(len(contours))
allPoints = []
sx = 0
sy = 0
if len(contours) > 0 :
    for contour in contours:
        print "===== %d ========="%count
        for cpoint in contour:
            point = (cpoint[0][0], cpoint[0][1])
            print point
            allPoints.append(cpoint[0])
            sx = sx + cpoint[0][0]
            sy = sy + cpoint[0][1]
            cv2.putText(image,'.',point,font,1,(255,255,255),1)
            count = count + 1

mx = sx / count
my = sy / count

moments = cv2.moments(np.asarray(allPoints))
area = cv2.contourArea(contours[1])
print "== XDDD  === "
print area 
print moments
#Central mass of first order moments
if moments['m00']!=0:
    cx = int(moments['m10']/moments['m00']) # cx = M10/M00
    cy = int(moments['m01']/moments['m00']) # cy = M01/M00
centerMass=(mx, my) 
centerMass2=(cx, cy) 
print centerMass
point = (466, 540)

cv2.putText(image,'X',tuple(centerMass),font,2,(223, 88, 76),2)  
cv2.putText(image,'O',tuple(centerMass2),font,2,(0, 88, 76),2)  

cv2.imshow(imageName,image)
cv2.waitKey(0)
cv2.destroyAllWindows()