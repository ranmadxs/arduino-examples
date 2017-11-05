import cv2
import numpy as np
from django.template.defaultfilters import center
from array import array

imageName = "imgs/hand2F.jpg";
image = cv2.imread(imageName)


skin_min = np.array([0, 40, 150], np.uint8)
skin_max = np.array([20, 150, 255], np.uint8)
#skin_min = np.array([234, 204, 219], np.uint8)
#skin_max = np.array([66, 61, 84], np.uint8)


gaussian_blur = cv2.GaussianBlur(image, (5, 5), 0)
blur_hsv = cv2.cvtColor(gaussian_blur, cv2.COLOR_BGR2HSV)

tre_green = cv2.inRange(blur_hsv, skin_min, skin_max)
__, contours, hierarchy = cv2.findContours(tre_green, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

count = 0
font = cv2.FONT_HERSHEY_SIMPLEX
print(len(contours))
allPoints = []
averageContour = []
totalAll = 0
sx = 0
sy = 0

ax = 0
ay = 0

if len(contours) > 0 :
    for contour in contours:
        print "===== %d ========="%count
        spx = 0
        spy = 0
        totalContour = 0
        for cpoint in contour:
            totalContour = totalContour + 1
            point = (cpoint[0][0], cpoint[0][1])
            print point
            allPoints.append(cpoint[0])
            spx = spx + cpoint[0][0]
            spy = spy + cpoint[0][1]
            cv2.putText(image,'.',point,font,1,(255,255,255),1)
        sx = sx + (spx / totalContour)
        sy = sy + (spy / totalContour)
        ax = ax + spx
        ay = ay + spy
        totalAll = totalContour + totalAll
        count = count + 1

print totalAll
mx = sx / count
my = sy / count

amx = ax / totalAll
amy = ay / totalAll

moments = cv2.moments(np.asarray(allPoints))
area = cv2.contourArea(contours[1])
print "== count  === "
print count 
print moments
#Central mass of first order moments
if moments['m00']!=0:
    cx = int(moments['m10']/moments['m00']) # cx = M10/M00
    cy = int(moments['m01']/moments['m00']) # cy = M01/M00
centerMass1=(mx, my)
centerMass2=(amx, amy) 
centerMass3=(cx, cy) 

centerMass4=((mx + amx)/2, (my + amy)/2)

print "========================"
print centerMass4
print "========================"



cv2.putText(image,'X',tuple(centerMass1),font,1,(223, 88, 76),1)    
cv2.putText(image,'C',tuple(centerMass2),font,1,(123, 88, 0),1)  
cv2.putText(image,'O',tuple(centerMass3),font,1,(0, 88, 76),1)  
cv2.putText(image,'*',tuple(centerMass4),font,1,(71,83,222),1)

cv2.imshow(imageName,image)
cv2.waitKey(0)
cv2.destroyAllWindows()