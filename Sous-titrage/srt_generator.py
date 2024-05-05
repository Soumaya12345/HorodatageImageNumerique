import time

def generate_subtitle(subtitle_number, start_time, end_time, text):
    return f"{subtitle_number}\n{start_time} --> {end_time}\n{text}\n\n"

def main():
    # Open the SRT file in append mode
    with open("subtitles.srt", "a") as f:
        subtitle_number = 1
        while True:
            # Get the current system time
            current_time = time.strftime("%H:%M:%S")
            
            # Format the subtitle
            start_time = current_time + ",000"
            end_time = (current_time + ",999") if subtitle_number > 1 else "99:59:59,999"
            subtitle_text = f"Current Time: {current_time}"
            subtitle = generate_subtitle(subtitle_number, start_time, end_time, subtitle_text)
            
            # Write the subtitle to the file
            f.write(subtitle)
            
            # Increment subtitle number
            subtitle_number += 1
            
            # Wait for 1 second before generating the next subtitle
            time.sleep(1)

if __name__ == "__main__":
    main()
