import requests
import json
from keys import API_KEY


class APIException(Exception):
    pass


class InvalidAmountError(Exception):
    pass


class MoneyTransfer:
    @staticmethod
    def get_price(base, quote):
        r = requests.get(
            f"http://apilayer.net/api/live?access_key={API_KEY}&currencies={quote}&source={base}&format=1")
        rates = json.loads(r.content)["quotes"][f"{base}{quote}"]
        return rates
