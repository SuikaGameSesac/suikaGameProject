import socket

host = "127.0.0.1"
port = 65432

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as socket_server: # IPv4 // socket.SOCK_STREAM tcp/ip
    socket_server.bind((host, port)) # 포트 지정 후, 클라이언트로부터 연결을 대기
    
    socket_server.listen()
    print("Server is Connected")

    conn, addr = socket_server.accept()
    
    with conn:
        print(f"Connected Socket is {addr}")

        while True:
            data = conn.recv(1024)
            if not data:
                break
            conn.sendall(data)

# add ) 클라이언트가 여러개인 경우?
# conn, addr = socket_server.accept() 를 while 결과를 리스트에 저장