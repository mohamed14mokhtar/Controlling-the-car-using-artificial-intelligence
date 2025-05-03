import cv2
import serial
import time

# Serial port setup for STM32
ser = serial.Serial('COM9', 9600, timeout=1)
time.sleep(2)

# Define HSV color ranges
def get_color(frame):
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Red color range
    lower_red = (0, 100, 100)
    upper_red = (10, 255, 255)
    mask_red = cv2.inRange(hsv, lower_red, upper_red)

    # Yellow color range
    lower_yellow = (20, 100, 100)
    upper_yellow = (30, 255, 255)
    mask_yellow = cv2.inRange(hsv, lower_yellow, upper_yellow)

    # Green color range
    lower_green = (40, 100, 100)
    upper_green = (70, 255, 255)
    mask_green = cv2.inRange(hsv, lower_green, upper_green)

    if cv2.countNonZero(mask_red) > 500:
        return "RED"
    elif cv2.countNonZero(mask_yellow) > 500:
        return "YELLOW"
    elif cv2.countNonZero(mask_green) > 500:
        return "GREEN"
    else:
        return "UNKNOWN"

video = cv2.VideoCapture(0)

while True:
    ret, frame = video.read()
    frame = cv2.flip(frame, 1)

    color = get_color(frame)
    cv2.putText(frame, f'Traffic Light: {color}', (20, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (255,255,255), 2)

    if color == "RED":
        ser.write(b'R\n')
    elif color == "YELLOW":
        ser.write(b'Y\n')
    elif color == "GREEN":
        ser.write(b'G\n')

    cv2.imshow("Traffic Light Detection", frame)
    if cv2.waitKey(1) & 0xFF == ord('k'):
        break

video.release()
cv2.destroyAllWindows()