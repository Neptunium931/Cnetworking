#!./venv/bin/python3
import subprocess as sp
import socket
import sys
import string
import time
from termcolor import cprint
import difflib
import random


def perror(message: str) -> None:
    print(f"{message}", file=sys.stderr)


def testFail(testName: str, outFail: str, out: str) -> None:
    cprint("NOK", "red", end=" ")
    print(f"{testName} : ")
    print(out.encode())
    print(outFail.encode())
    diff = difflib.unified_diff(
        out.splitlines(keepends=True),
        outFail.splitlines(keepends=True),
        fromfile="ref",
        tofile="testExcution",
    )
    perror("\n".join(diff))


def testSuccess(testName: str) -> None:
    cprint("OK", "green", end=" ")
    print(f"{testName}")


def generate_random_string(length):
    # Choix des caractères possibles pour la chaîne aléatoire
    characters = string.ascii_letters + string.digits + string.punctuation
    # Génération de la chaîne aléatoire
    return "".join(random.choice(characters) for _ in range(length))


def initServer() -> None:
    sp.Popen("./CnetworkingServer", stdout=logFile, stderr=logFile)


class client:
    def __init__(self) -> None:
        self.fruits = ["peach", "mango", "kiwi"]
        self.initSocket()

    def initSocket(self, serverAddr: str = "localhost", serverPort: int = 9001):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.settimeout(1.5)
        self.s.connect((serverAddr, serverPort))

    def closeSocket(self):
        self.s.close()

    def sendCommand(self, data: str):
        self.s.sendall(data.encode())
        return self.s.recv(2048).decode().replace("\x00", "")

    def helo(self):
        self.sendCommand("helo helo.fr")

    def sendfruit(self):
        self.helo()
        self.sendCommand(f"sendfruit {self.fruits[0]} 19")
        for fruit in self.fruits[1:]:
            self.sendCommand(f"sendfruit {fruit} {random.randint(10,20)}")


def main():
    returnCode: int = 0

    for _ in range(100):
        for k in range(1, 100):
            initServer()
            time.sleep(0.1)
            c = client()
            c.helo()
            payload: str = generate_random_string(k)
            print(f"#{payload}#")
            out: str = c.sendCommand(payload)
            try:
                c.closeSocket()
            except:
                continue
    sys.exit(returnCode)


if __name__ == "__main__":
    logFile = open("fuzzing.log", "w")
    main()
    logFile.close()
