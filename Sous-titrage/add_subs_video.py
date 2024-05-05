import subprocess
from datetime import datetime

def add_subtitle(video_path, text):
    # Run the command to add subtitles using FFMPEG
    output_file = f"video_subtitles.mp4"
    subprocess.run(["ffmpeg", "-i", video_path, "-vf", f"drawtext=text='{text}':x=50:y=50:fontsize=24:fontcolor=white", "-c:a", "copy", output_file])

def capture_video_with_subtitle():
    # Get current date and time
    current_time = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    
    # Define the output file path
    output_file = f"video_{current_time}.mp4"
    
    # Capture an image using rpicam-still
    record_command = ["rpicam-vid", "-o", output_file]
    subprocess.run(record_command)
    
    # Add subtitles to the captured image
    add_subtitle(output_file, current_time)

if __name__ == "__main__":
    # Call the function to capture the image with subtitles
    capture_video_with_subtitle()
