import telebot
from extensions import *
from keys import TOKEN, SUPPORTED_CURRENCIES

bot = telebot.TeleBot(TOKEN)


def is_valid_currency(currency_code):
    return SUPPORTED_CURRENCIES.get(currency_code)


def conversation_money(message):
    try:
        message_parts = message.text.split()
        if len(message_parts) != 3:
            raise ValueError("Не правильный формат. Используй: '<валюта1> <валюта2> <количество>'.")

        base_currency = is_valid_currency(str(message_parts[0]).lower())
        quote_currency = is_valid_currency(str(message_parts[1]).lower())

        if not base_currency:
            raise APIException(f"Неправильная валюта: {message_parts[0]}")

        if not quote_currency:
            raise APIException(f"Неправильная валюта: {message_parts[1]}")

        try:
            amount = float(message_parts[2])
        except ValueError:
            raise InvalidAmountError("Некорректное число")

        if amount < 0:
            raise InvalidAmountError("Введите корректное число")

        conversion_rate = MoneyTransfer.get_price(base_currency, quote_currency)
        converted_amount = amount * float(conversion_rate)

        bot.send_message(
            message.chat.id,
            f"{amount:.2f} {base_currency} = {converted_amount:.2f} {quote_currency}"
        )

    except ValueError as ve:
        bot.send_message(message.chat.id, str(ve))

    except APIException as ice:
        bot.send_message(message.chat.id, str(ice))

    except InvalidAmountError as iae:
        bot.send_message(message.chat.id, str(iae))


@bot.message_handler(commands=['start', 'help'])
def send_welcome(message):
    bot.send_message(message.chat.id,
                     f"Отправь в чат сообщение в формате: <валюта1> <валюта2> <сумма>, например: доллар евро 100")


@bot.message_handler(commands=['values'])
def values(message):
    bot.send_message(message.chat.id,
                     "Доллар\nЕвро\nРубль\nЙена\nЛира")


@bot.message_handler(content_types=['text'])
def money_transfer(message):
    conversation_money(message)


bot.polling(none_stop=True)
