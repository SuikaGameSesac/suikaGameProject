from PIL import ImageFont, ImageDraw, Image
import numpy as np
import cv2
import mediapipe as mp
from fastapi import FastAPI, APIRouter
from fastapi.responses import StreamingResponse
import uvicorn
import socket

##### TCP socket #####
def start_server(host='127.0.0.1', port=65432):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as  socket_server:
        # 소켓을 주어진 호스트와 포트에 연결하기
        socket_server.bind((host, port))

        # 클라이언트에서 연결하기를 기다리기
        socket_server.listen()

        global conn

        # 클라이언트로부터 연결이 수립되면, accept 메서드는 연결된 클라이언트의 소켓 객체와 주소를 반환합니다.
        conn, addr = socket_server.accept()
        print(f"Connection Successful / address: {addr}")

##### mediapipe #####
# 한글을 출력하기 위한 함수
def draw_text(img, text, position, font_size, font_color):
    font_path = "C:/Windows/Fonts/gulim.ttc"  # Windows에서 Gulim 폰트 경로

    # opencv 이미지를 PIL이미지로 변환
    img_pil = Image.fromarray(img)

    # PIL Draw 객체 생성
    draw = ImageDraw.Draw(img_pil)

    # 폰트 스타일 지정
    font = ImageFont.truetype(font_path, font_size)

    # PIL 이미지에 텍스트 입력
    draw.text(position, text, font=font, fill=font_color)
    return np.array(img_pil) # 최종 numpy array 로 이미지 형태 반환

# 손가락의 개폐 상태를 판별하는 함수
def get_hand_pose(hand_landmarks):
    # 손가락 끝과 PIP(손가락 중간 관절) 사이의 거리를 비교하여 손가락이 펴져 있는지 확인
    open_fingers = []
    for i in [4, 8, 12, 16, 20]:  # 엄지부터 새끼손가락까지의 끝 랜드마크 인덱스
        tip = hand_landmarks.landmark[i]  # 손가락 끝
        pip = hand_landmarks.landmark[i - 2]  # 손가락 중간 관절

        # if handedness.classification[0].label == "Right":  # 오른손인 경우 판별하기

        # 엄지는 x좌표를, 나머지 손가락은 y좌표를 사용하여 개폐 상태 확인 - 오른손 기준
        if i == 4:  # 엄지손가락인 경우
            open_fingers.append(tip.x > pip.x)
        else:
            open_fingers.append(tip.y < pip.y)
    
    # Hold, Release 판별
    if open_fingers.count(True) >= 4:
        return False
    else:
        return True

# MediaPipe Hands 모듈 초기화 - 미리 설정후 시작해보기
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(
    max_num_hands=1,               # 동시에 추적할 최대 손의 수
    min_detection_confidence=0.5,  # 손 검출을 위한 최소 신뢰도
    min_tracking_confidence=0.5)   # 손 추적을 위한 최소 신뢰도
mp_drawing = mp.solutions.drawing_utils  # 그리기 함수 초기화

# 비디오 스트리밍 함수
def generate_frames():
    cap = cv2.VideoCapture(0)

    # 소켓 연결
    start_server(host='127.0.0.1', port=65432)

    while cap.isOpened():
        success, frame = cap.read()
        if not success:
            continue

        frame = cv2.flip(frame, 1)

        # BGR 이미지를 RGB로 변환
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        # MediaPipe를 통해 손 검출
        results = hands.process(frame)

        # 이미지를 RGB에서 BGR로 변환하여 그리기 작업 준비
        frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

        # 검출된 손의 랜드마크를 이미지에 그림
        if results.multi_hand_landmarks:
            for hand_landmarks in results.multi_hand_landmarks:
                mp_drawing.draw_landmarks(
                    frame, hand_landmarks, mp_hands.HAND_CONNECTIONS,
                    mp_drawing.DrawingSpec(color=(121, 22, 76), thickness=2, circle_radius=4),
                    mp_drawing.DrawingSpec(color=(250, 44, 250), thickness=2))
                
                # 0~640
                x = int(hand_landmarks.landmark[9].x * frame.shape[1])
                if x < 0:
                    x = 0
                elif x > 640:
                    x = 640
                
                # Is Holding
                pose = get_hand_pose(hand_landmarks)

                # Socket Send
                conn.sendall(bytes(str(x), 'utf-8'))
                conn.sendall(bytes(str(pose), 'utf-8'))

                # Socket Recieve
                # data = socket_connect.recv(1024)

                # 한글 출력을 위한 작업
                frame = draw_text(frame, str(x), (10, 50), 30, (255, 255, 255))
                frame = draw_text(frame, str(pose), (10, 100), 30, (255, 255, 255))
                # frame = draw_text(frame, str(data), (10, 50), 30, (255, 255, 255))
            
        ret, buffer = cv2.imencode('.jpg', frame)
        frame = buffer.tobytes()
        yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

##### API #####
app = FastAPI()

@app.get("/")
def root_index():
    return "server running"
 
router_vedio = APIRouter(prefix="/vedio")

@router_vedio.get("/")
async def read_vedio():
    return StreamingResponse(generate_frames(), media_type="multipart/x-mixed-replace; boundary=frame")

app.include_router(router_vedio)

if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8000)
