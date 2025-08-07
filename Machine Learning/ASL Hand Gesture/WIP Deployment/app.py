from fastapi import FastAPI, UploadFile, File
from fastapi.middleware.cors import CORSMiddleware
import uvicorn
import numpy as np
from PIL import Image
import io
import tensorflow as tf

app = FastAPI()

# Allow CORS for frontend calls (adjust origins accordingly)
app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:8000"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Load the Keras model once on startup
model = tf.keras.models.load_model('asl_model.keras')

# Your class labels (replace with your exact class order)
labels = ['h', 'q', 'm', 's', 'r', 'p', 'e', '6', '3', '4', 'd', '5', 'l', 'y', 'v', 'a', '0', '2', '1', 'u', 'w', '8', 'j', 'f', '9', 'g', 'i', 'k', 'z', 'b', '7', 'o', 'c', 'x', 'n', 't']

def preprocess_image(image_bytes):
    image = Image.open(io.BytesIO(image_bytes)).convert('RGB')
    image = image.resize((64, 64))  # exact size used for training
    img_array = np.array(image) / 255.0  # normalize to 0-1
    img_array = np.expand_dims(img_array, axis=0)  # batch dimension
    return img_array.astype(np.float32)


@app.post("/predict")
async def predict(file: UploadFile = File(...)):
    # Read uploaded image bytes
    image_bytes = await file.read()
    # Preprocess image
    input_arr = preprocess_image(image_bytes)
    # Predict with model
    predictions = model.predict(input_arr)
    pred_index = np.argmax(predictions[0])
    confidence = float(predictions[0][pred_index])
    pred_label = labels[pred_index]
    return {
        "prediction": pred_label,
        "confidence": confidence
    }

if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=5000)
