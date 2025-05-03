import cv2
import numpy as np
import serial
import time

# Set up serial communication (adjust COM port and baudrate)
ser = serial.Serial('COM3', 9600)  # Replace 'COM3' with your actual port
time.sleep(2)  # Wait for connection to STM32 to establish

# HSV color ranges
red_lower = np.array([0, 120, 70])
red_upper = np.array([10, 255, 255])

green_lower = np.array([36, 25, 25])
green_upper = np.array([86, 255, 255])

yellow_lower = np.array([20, 100, 100])
yellow_upper = np.array([30, 255, 255])

cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print("Error: Camera not found.")
    exit()

last_sent = ''  # To avoid sending repeatedly the same char

print("Running... press 'q' to quit.")

while True:
    ret, frame = cap.read()
    if not ret:
        break

    frame = cv2.resize(frame, (640, 480))
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Masks
    red_mask = cv2.inRange(hsv, red_lower, red_upper)
    green_mask = cv2.inRange(hsv, green_lower, green_upper)
    yellow_mask = cv2.inRange(hsv, yellow_lower, yellow_upper)

    red_pixels = cv2.countNonZero(red_mask)
    green_pixels = cv2.countNonZero(green_mask)
    yellow_pixels = cv2.countNonZero(yellow_mask)

    if red_pixels > 5000 and last_sent != 'R':
        print("🔴 Red Detected - Sending 'R'")
        ser.write(b'R')
        last_sent = 'R'

    elif green_pixels > 5000 and last_sent != 'G':
        print("🟢 Green Detected - Sending 'G'")
        ser.write(b'G')
        last_sent = 'G'

    elif yellow_pixels > 5000 and last_sent != 'Y':
        print("🟡 Yellow Detected - Sending 'Y'")
        ser.write(b'Y')
        last_sent = 'Y'

    # Reset if nothing is detected (optional)
    elif red_pixels < 1000 and green_pixels < 1000 and yellow_pixels < 1000:
        last_sent = ''

    # Show frame
    cv2.imshow("Camera", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
ser.close()
cv2.destroyAllWindows()
