from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC


class ProductPage:
    ADD_TO_BSKT_BTN = (By.CLASS_NAME, "btn-add-to-basket")

    def __init__(self, driver):
        self.driver = driver

    def open(self, url):
        self.driver.get(url)

    def find_button(self):
        try:
            wait = WebDriverWait(self.driver, 5)
            wait.until(EC.EC.visibility_of_all_elements_located(self.ADD_TO_BSKT_BTN))
            buttons = self.driver.find_elements(*self.ADD_TO_BSKT_BTN)
            return len(buttons)
        except:
            return 0
