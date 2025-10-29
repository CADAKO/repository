import pytest
from selenium.webdriver.remote.webdriver import WebDriver
from pages.product_page import ProductPage
import time


class TestFindAddToCartBtn:
    def test_find_add_to_cart_btn(self, browser: WebDriver,  url:str):
        product_page = ProductPage(browser)

        product_page.open(url)
        buttons = product_page.find_button()
        time.sleep(10)

        assert buttons== 1,\
        f"Тест провален на URL: в {url} найдено {buttons} кнопок 'Добавить в корзину', а ожидалось 1"