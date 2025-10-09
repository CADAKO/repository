from selenium import webdriver
from selenium.webdriver.common.by import By
import time

try:
    browser = webdriver.Chrome()
    browser.get("http://suninjuly.github.io/registration1.html")

    # Заполняем обязательные поля
    input1 = browser.find_element(By.CSS_SELECTOR, ".first_block .first")
    input1.send_keys("Ivan")

    input2 = browser.find_element(By.CSS_SELECTOR, ".first_block .second")
    input2.send_keys("Petrov")

    input3 = browser.find_element(By.CSS_SELECTOR, ".first_block .third")
    input3.send_keys("test@example.com")

    # Отправляем заполненную форму
    button = browser.find_element(By.CSS_SELECTOR, "button.btn")
    button.click()

    # Проверяем успешность регистрации
    time.sleep(1)
    welcome_text_elt = browser.find_element(By.TAG_NAME, "h1")
    assert "Congratulations! You have successfully registered!" == welcome_text_elt.text


finally:
    time.sleep(5)
    browser.quit()
