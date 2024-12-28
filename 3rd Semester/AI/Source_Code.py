import cv2
from ultralytics import YOLO  # Import YOLO from ultralytics
import pyfirmata2 as pyfirmata
import numpy as np

class ObjectDetection:
    def __init__(self):
        self.model = self.load_model()
        self.class_names = ["person", "bicycle", "car", "motorbike", "aeroplane", "bus", "train", "truck", "boat", "traffic light", "fire hydrant", "stop sign", "parking meter", "bench", "bird", "cat", "dog", "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe", "backpack", "umbrella", "handbag", "tie", "suitcase", "frisbee", "skis", "snowboard", "sports ball", "kite", "baseball bat", "baseball glove", "skateboard", "surfboard", "tennis racket", "bottle", "wine glass", "cup", "fork", "knife", "spoon", "bowl", "banana", "apple", "sandwich", "orange", "broccoli", "carrot", "hot dog", "pizza", "donut", "cake", "chair", "sofa", "pottedplant", "bed", "diningtable", "toilet", "tvmonitor", "laptop", "mouse", "remote", "keyboard", "cell phone", "microwave", "oven", "toaster", "sink", "refrigerator", "book", "clock", "vase", "scissors", "teddy bear", "hair drier", "toothbrush"]

    def load_model(self):
        return YOLO('yolov10n.pt')  # Load YOLOv10 model

    def get_video(self):
        return cv2.VideoCapture(1)

    def score_frame(self, frame):
        results = self.model(frame)
        predictions = results[0].boxes
        labels = predictions.cls.numpy()
        cord = predictions.xyxy.numpy()

        bird_class_index = self.class_names.index("bird")
        bird_indices = [i for i, label in enumerate(labels) if label == bird_class_index]
        bird_cord = cord[bird_indices]

        return bird_cord

    def plot_boxes(self, bird_cord, frame):
        for box in bird_cord:
            x1, y1, x2, y2 = map(int, box[:4])
            cx, cy = (x1 + x2) // 2, (y1 + y2) // 2  # Center of the box
            cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
            cv2.putText(frame, "Bird", (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 255, 0), 2)
            cv2.circle(frame, (cx, cy), 5, (0, 0, 255), -1)  # Mark center
        return frame

class BirdTrackingRobot:
    def __init__(self):
        self.detector = ObjectDetection()
        self.cap = self.detector.get_video()
        self.ws, self.hs = 1920, 1080
        self.cap.set(3, self.ws)
        self.cap.set(4, self.hs)

        self.port = "COM3"
        self.board = pyfirmata.Arduino(self.port)
        self.servo_pinX = self.board.get_pin('d:9:s')
        self.servo_pinY = self.board.get_pin('d:10:s')

        self.servoPos = [90, 90]  # Initial servo position
        self.servo_pinX.write(self.servoPos[0])
        self.servo_pinY.write(self.servoPos[1])
        self.tracked_bird = None

    def run(self):
        while self.cap.isOpened():
            ret, frame = self.cap.read()
            if not ret:
                break

            bird_cord = self.detector.score_frame(frame)

            if len(bird_cord) > 0:
                if self.tracked_bird is None:  # Track the first detected bird
                    self.tracked_bird = bird_cord[0]

                # Check if the tracked bird is still visible
                tracked_found = False
                for box in bird_cord:
                    if np.allclose(self.tracked_bird, box, atol=20):  # Match with small tolerance
                        self.tracked_bird = box  # Update tracked bird position
                        tracked_found = True
                        break

                if not tracked_found:
                    self.tracked_bird = None  # Reset tracking if bird disappears
                else:
                    x1, y1, x2, y2 = map(int, self.tracked_bird[:4])
                    cx, cy = (x1 + x2) // 2, (y1 + y2) // 2

                    # Map center coordinates to servo angles
                    servoX = np.interp(cx, [0, self.ws], [0, 180])
                    servoY = np.interp(cy, [0, self.hs], [0, 180])
                    servoX = 180 - servoX  # Invert X-axis for correct servo motion

                    self.servoPos[0] = np.clip(servoX, 0, 180)
                    self.servoPos[1] = np.clip(servoY, 0, 180)

                    self.servo_pinX.write(self.servoPos[0])
                    self.servo_pinY.write(self.servoPos[1])

            # Resize and display the frame
            frame = cv2.resize(frame, (self.ws, self.hs))
            frame = self.detector.plot_boxes(bird_cord, frame)
            cv2.putText(frame, f'Servo X: {int(self.servoPos[0])} deg', (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (255, 0, 0), 2)
            cv2.putText(frame, f'Servo Y: {int(self.servoPos[1])} deg', (50, 100), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (255, 0, 0), 2)

            cv2.imshow("Bird Tracking", frame)

            if cv2.waitKey(1) & 0xFF == ord('q'):  # Quit on 'q'
                break

        self.cap.release()
        cv2.destroyAllWindows()

if __name__ == "__main__":
    robot = BirdTrackingRobot()
    robot.run()
