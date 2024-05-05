import cv2
import smbus
from datetime import datetime

# I2C address of the RTC module
RTC_ADDRESS = 0x68

# Create an I2C bus object
bus = smbus.SMBus(1)  # Use bus 1 for Raspberry Pi 2 and newer

def read_rtc_time():
    # Read the current time from the RTC module
    rtc_data = bus.read_i2c_block_data(RTC_ADDRESS, 0, 7)

    # Extract the date and time components from the RTC data
    year = rtc_data[6] + 2000
    month = rtc_data[5]
    day = rtc_data[4]
    hour = rtc_data[2]
    minute = rtc_data[1]
    second = rtc_data[0]

    # Return the date and time as a datetime object
    return datetime(year, month, day, hour, minute, second)

def add_subtitle(image, text):
    # Choose font and position for subtitles
    font = cv2.FONT_HERSHEY_SIMPLEX
    position = (50, 50)  # Coordinates of the bottom-left corner of the text
    font_scale = 1
    font_color = (255, 255, 255)  # White color
    thickness = 2

    # Add subtitles to the image
    cv2.putText(image, text, position, font, font_scale, font_color, thickness)

    return image

def capture_image():
    # Capture an image (assuming using Raspberry Pi camera module)
    cap = cv2.VideoCapture(0)
    ret, frame = cap.read()  # ret: if return value aka image capture is successful

    if ret:
        return frame
    else:
        print("Error: Failed to capture image.")
        return None

def main():
    # Read the current time from the RTC module
    rtc_time = read_rtc_time()

    # Capture an image
    frame = capture_image()

    if frame is not None:
        # Get current RTC time as timestamp text
        timestamp_text = rtc_time.strftime("%Y-%m-%d %H:%M:%S")

        # Add subtitles to the image
        frame_with_subtitles = add_subtitle(frame, timestamp_text)

        # Save the modified image
        cv2.imwrite("image_with_subtitles.jpg", frame_with_subtitles)

        print("Image captured and saved successfully.")

    # Release the camera
    cap.release()

if __name__ == "__main__":
    main()

