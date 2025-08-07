import cv2
import mediapipe as mp
import numpy as np
from tensorflow.keras.models import load_model
from PIL import Image

# Load your trained Keras model
model = load_model('asl_model.keras')

# Your ASL class labels (order must match your training)
labels = ['1', 'q', 'm', 's', 'r', 'p', 'e', '6', '3', '4', 'd', '5', 'l', 'y', 'v',
          'a', '0', '2', 'h', 'u', 'w', '8', 'j', 'f', '9', 'g', 'i', 'k', 'z', 'b',
          '7', 'o', 'c', 'x', 'n', 't']

# Initialize MediaPipe Hands
mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils
hands_detector = mp_hands.Hands(
    max_num_hands=1,
    min_detection_confidence=0.7,
    min_tracking_confidence=0.5)

def preprocess_hand_image(hand_img):
    # Convert BGR to RGB
    img_rgb = cv2.cvtColor(hand_img, cv2.COLOR_BGR2RGB)
    # Convert to PIL Image
    pil_img = Image.fromarray(img_rgb)
    # Resize to 64x64 as model expects
    pil_img = pil_img.resize((64, 64))
    # Convert to numpy array and normalize
    img_array = np.array(pil_img) / 255.0
    # Add batch dimension
    return np.expand_dims(img_array, axis=0).astype(np.float32)

# Open webcam
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Flip horizontally (mirror view)
    frame = cv2.flip(frame, 1)

    # Convert to RGB for MediaPipe processing
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    results = hands_detector.process(rgb_frame)

    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            # Draw landmarks on original frame
            mp_drawing.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)

            h, w, _ = frame.shape

            # Get bounding box coords
            xs = [lm.x for lm in hand_landmarks.landmark]
            ys = [lm.y for lm in hand_landmarks.landmark]
            min_x, max_x = int(min(xs) * w), int(max(xs) * w)
            min_y, max_y = int(min(ys) * h), int(max(ys) * h)

            # Add padding and clamp within frame size
            pad = 20
            min_x = max(min_x - pad, 0)
            min_y = max(min_y - pad, 0)
            max_x = min(max_x + pad, w)
            max_y = min(max_y + pad, h)

            # Draw bounding box
            cv2.rectangle(frame, (min_x, min_y), (max_x, max_y), (0, 255, 0), 2)

            # Crop the hand area
            hand_crop = frame[min_y:max_y, min_x:max_x]

            # Show cropped hand preview window
            if hand_crop.size != 0:
                hand_preview = cv2.resize(hand_crop, (128, 128))
                cv2.imshow("Cropped Hand Preview", hand_preview)

                # Preprocess and predict
                input_img = preprocess_hand_image(hand_crop)
                preds = model.predict(input_img)
                pred_idx = np.argmax(preds[0])
                confidence = preds[0][pred_idx]
                label = labels[pred_idx]

                # Display prediction text
                text = f"{label} ({confidence*100:.2f}%)"
                cv2.putText(frame, text, (min_x, min_y - 10),
                            cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    else:
        # Optionally display no hand detected
        cv2.putText(frame, "No hand detected", (10, 30),
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

        # Clear cropped hand preview window if no hand detected
        black_img = np.zeros((128, 128, 3), dtype=np.uint8)
        cv2.imshow("Cropped Hand Preview", black_img)

    cv2.imshow("ASL Recognition", frame)

    if cv2.waitKey(1) & 0xFF == 27:  # Press ESC to quit
        break

cap.release()
cv2.destroyAllWindows()
