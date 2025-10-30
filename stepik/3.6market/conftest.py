import pytest
from selenium import webdriver
from selenium.webdriver.chrome.options import Options as ChromeOptions
from selenium.webdriver.firefox.options import Options as FirefoxOptions

@pytest.fixture(scope="function")
def url():
    return "https://selenium1py.pythonanywhere.com/ru/catalogue/coders-at-work_207/"

def pytest_addoption(parser):
    """Добавление опций командной строки pytest."""
    parser.addoption(
        "--browser_name",
        action="store",
        default="chrome",
        help="Choose browser: chrome or firefox"
    )
    parser.addoption(
        "--language",
        action="store",
        default="ru",
        help="Choose user language: es, en, ru, de, fr"
    )
    parser.addoption(
        "--headless",
        action="store_true",
        default=False,
        help="Run browser in headless mode"
    )


@pytest.fixture(scope="function")
def browser(request):
    """Фикстура для инициализации и закрытия браузера."""
    browser_name = request.config.getoption("browser_name")
    user_language = request.config.getoption("language")
    headless_mode = request.config.getoption("headless")
    driver = None

    if browser_name == "chrome":
        print("\nstart chrome browser for test..")
        options = ChromeOptions()
        # Настройки для отключения менеджера паролей Chrome
        prefs = {
            "credentials_enable_service": False,
            "profile.password_manager_enabled": False,
            "profile.password_manager_leak_detection": False
        }
        options.add_experimental_option("prefs", prefs)

        # Установка языка
        options.add_experimental_option('prefs', {'intl.accept_languages': user_language})

        # Запуск в Headless режиме, если опция включена
        if headless_mode:
            options.add_argument("--headless=new")
            options.add_argument("--window-size=1920,1080")

        driver = webdriver.Chrome(options=options)

    elif browser_name == "firefox":
        print("\nstart firefox browser for test..")
        options = FirefoxOptions()

        # Установка языка
        options.set_preference("intl.accept_languages", user_language)

        # Запуск в Headless режиме, если опция включена
        if headless_mode:
            options.add_argument("-headless")

        driver = webdriver.Firefox(options=options)

    else:
        raise pytest.UsageError("--browser_name should be chrome or firefox")

    yield driver

    driver.quit()

    
