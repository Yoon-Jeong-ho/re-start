import pytesseract
from PIL import Image
import os
import pandas as pd
import re


pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'


def extract_text_from_images(image_directory):
    """이미지 디렉토리에서 모든 이미지를 읽고 텍스트를 추출합니다."""
    image_texts = {}
    for filename in os.listdir(image_directory):
        if filename.lower().endswith(('.png', '.jpg', '.jpeg')):
            image_path = os.path.join(image_directory, filename)
            try:
                image = Image.open(image_path)
                text = pytesseract.image_to_string(image,lang='eng')
                image_texts[filename] = text
            except Exception as e:
                print(f"Error processing {filename}: {e}")
    return image_texts

def clean_text(raw_text):
    """ 추출된 텍스트를 정제합니다. """
    return re.sub(r'[^a-zA-Z0-9]', '', raw_text)


def read_excel_data(excel_path):
    """엑셀 데이터를 불러옵니다. """
    excel_data = pd.read_excel(excel_path, sheet_name=0, index_col=0)
    for column in excel_data.columns:
        excel_data[column] = excel_data[column].map(lambda x: clean_text(str(x)))
    return excel_data

def verify_data(image_texts, excel_data):
    """추출된 이미지 텍스트와 엑셀 데이터를 비교합니다."""
    results = {}
    for image_name, text in image_texts.items():
        cleaned_text = clean_text(text)
        image_name_no_ext = os.path.splitext(image_name)[0]
        match_data = {}

        print(f"Cleaned text from {image_name}: {cleaned_text}")  # 출력 추가
        if image_name_no_ext in excel_data.columns:
            for index, value in excel_data[image_name_no_ext].items():
                match_data[index] = value in cleaned_text
        results[image_name_no_ext] = match_data
    return results

def main():
    # 경로 설정
    image_directory = r'C:\img'
    excel_path = r'C:\img\data.xlsx'
    
    # 이미지에서 텍스트 추출
    image_texts = extract_text_from_images(image_directory)
    
    # 엑셀 데이터 읽기
    excel_data = read_excel_data(excel_path)
    print(excel_data)
    
    # 데이터 검증
    verification_results = verify_data(image_texts, excel_data)
    
    # 결과 출력
    for image_name, matches in verification_results.items():
        print(f"Results for {image_name}:")
        if matches:  # 매칭 데이터가 있을 경우
            for key, match in matches.items():
                print(f"  {key}: {'Match' if match else 'No Match'}")
        else:
            print("  No data found or no matches.")

if __name__ == '__main__':
    """함수 작동"""
    main()