import cv2
import numpy as np

def canny(image):
    gray = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
    # BGR2GRAY, BGR2HSV, BGR2RGB, BGR2LAB등의 옵션으로 image를 바꿔줌
    # 컬러 영상의 순간 장면을 흑백으로 바꾸는거죠
    blur = cv2.GaussianBlur(gray, (5, 5), 0)
    #cv2.GaussianBlur(src, ksize, sigmaX, dst=None, sigmaY=None, borderType=None) -> dst
    # src: 입력영상.각채널별로처리됨.
    # dst: 출력영상.src와같은크기, 같은타입.
    # ksize: 가우시안커널크기.(0, 0)을지정하면sigma값에의해자동결정됨 (홀수, 홀수)
    # sigmaX: x방향sigma.
    # sigmaY: y방향sigma.0이면sigmaX와같게설정.
    # borderType: 가장자리픽셀확장방식.
    # 노이즈 제거를 위해 블러처리를 시켜서 부드럽게 만든다.
    canny = cv2.Canny(blur, 50, 150)
    #cv2.Canny(src, threshold1, threshold2) -> 윤관선 따진 이미지
    # threshold1: 다른 엣지와의 인접 부분(엣지가 되기 쉬운 부분)에 있어 엣지인지 아닌지를 판단하는 임계값
    # threshold2: 엣지인지 아닌지를 판단하는 임계값. 둘 다 실험적으로 결정ㅎ기

    return canny

def region_of_interest(image):
    height = image.shape[0]
    width = image.shape[1]
    # numpyArray.shape -> [height, width]

    polygons = np.array([
        [(int(0.2 * width), height), (int(0.8 * width), height), (int(0.5 * width), int(0.6 * height))]
    ])
    # 꼭지점들 정보있는 넘파이배열 만들기. 사다리꼴모양
    mask = np.zeros_like(image)
    # 이미지 크기만큼의 빈 배열 만들기
    cv2.fillPoly(mask, polygons, 255)
    # cv2.fillPoly(img, pts, color, lineType, shift, offset)
    # 이미지, 좌표점, 색상, 선 종류, shift, offset
    # 검출한 대상에대한 선을 img위로 덮기
    masked_image = cv2.bitwise_and(image, mask)
    # 비트연산 AND. 두 개의 값이 모두 True일때
    return masked_image
    # 관심영역 지정한 친구를 리턴

def display_lines(image, lines):
    line_image = np.zeros_like(image)
    # 이미지 크기의 빈배열 만들기
    if lines is not None:
        for line in lines:
            x1, y1, x2, y2 = line.reshape(4)
            # lines에 있는 요소들이 이차원인데 1차원으로 변환함
            cv2.line(line_image, (x1, y1), (x2, y2), (0, 0, 255), 10)
            # 이미지 크기의 빈배열에 라인 그려넣음        

    return line_image

def main():
    cap = cv2.VideoCapture(0)
    # 0번째 카메라를 열어서 cap에 객체로 저장

    while cap.isOpened(): # 열리면 True니까 while문 계속 작동됨
        _, frame = cap.read()  # 카메라 열였는지에 대한 Bool, 현재프레임
        canny_image = canny(frame)
        cropped_image = region_of_interest(canny_image)
        # 모서리 따진 친구 & 관심영역 설정된 친구
        lines = cv2.HoughLinesP(cropped_image, 2, np.pi / 180, 100, np.array([]), minLineLength=40, maxLineGap=5)
        # cv2.HoughLinesP(image, rho, theta, threshold, lines=None, minLineLength=None, maxLineGap=None) -> lines
        # cv2.HoughLinesP(이미지, 축적배열의 픽셀간격, 1간격, 직선으로 판단할 임계값, 선분 시작과 끝좌표, 선분의 최소길이, 직선으로 간주할 최대 에지 점 간격) -> lines
        # 허프변환 사용하여 라인(형태: [[x1, y1, x2, y2]]) 검출 완료.
        print(lines)
        line_image = display_lines(frame, lines)

        combo_image = cv2.addWeighted(frame, 0.8, line_image, 1, 1)

        
        # cv2.addWeighted(src1, alpha, src2, beta, gamma, dst=None, dtype=None) -> dst
        # cv2.addWeighted(이미지1, 가중치1, 이미지2, 가중치2, 이미지에 더할 추가 값) -> dst
        cv2.imshow("result", combo_image)
        # 보여줌

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
