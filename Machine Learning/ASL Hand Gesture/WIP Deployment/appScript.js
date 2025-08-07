const video = document.getElementById('webcam');
const predictionDiv = document.getElementById('prediction');
const startBtn = document.getElementById('startBtn');

const canvas = document.createElement('canvas');
const ctx = canvas.getContext('2d');
canvas.width = 64;
canvas.height = 64;

let camera;

// Initialize MediaPipe Hands
const hands = new Hands({
  locateFile: (file) => `https://cdn.jsdelivr.net/npm/@mediapipe/hands/${file}`
});

hands.setOptions({
  maxNumHands: 1,
  minDetectionConfidence: 0.7,
  minTrackingConfidence: 0.5
});

hands.onResults(async (results) => {
  if (results.multiHandLandmarks && results.multiHandLandmarks.length > 0) {
    const landmarks = results.multiHandLandmarks[0];

    // Calculate bounding box
    const videoWidth = video.videoWidth;
    const videoHeight = video.videoHeight;
    const xs = landmarks.map(lm => lm.x * videoWidth);
    const ys = landmarks.map(lm => lm.y * videoHeight);

    const minX = Math.max(Math.min(...xs) - 10, 0);
    const maxX = Math.min(Math.max(...xs) + 10, videoWidth);
    const minY = Math.max(Math.min(...ys) - 10, 0);
    const maxY = Math.min(Math.max(...ys) + 10, videoHeight);
    const boxWidth = maxX - minX;
    const boxHeight = maxY - minY;

    // Crop the detected hand region from video and draw to canvas 64x64
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.drawImage(
      video,
      minX, minY, boxWidth, boxHeight,
      0, 0, canvas.width, canvas.height
    );

    // Convert canvas crop to blob and send to backend
    canvas.toBlob(async (blob) => {
      if (!blob) {
        predictionDiv.innerText = 'Error capturing hand image';
        return;
      }
      const formData = new FormData();
      formData.append('file', blob, 'hand.jpg');

      try {
        const response = await fetch('http://localhost:5000/predict', {
          method: 'POST',
          body: formData
        });
        if (response.ok) {
          const data = await response.json();
          predictionDiv.innerText = `Prediction: ${data.prediction} (Confidence: ${(data.confidence * 100).toFixed(2)}%)`;
        } else {
          predictionDiv.innerText = 'Prediction failed';
        }
      } catch (error) {
        predictionDiv.innerText = 'Error contacting API';
        console.error(error);
      }
    }, 'image/jpeg');
  } else {
    predictionDiv.innerText = 'No hand detected';
  }
});

async function startCamera() {
  camera = new Camera(video, {
    onFrame: async () => {
      await hands.send({ image: video });
    },
    width: 640,
    height: 480
  });
  await camera.start();
}

startBtn.addEventListener('click', async () => {
  startBtn.disabled = true;
  await startCamera();
});
