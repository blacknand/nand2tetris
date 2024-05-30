import re
import sys

class Parser:
    def __init__(self, asmFile):
        self.asmFile = open(asmFile, "r")
        self.lines = self.asmFile.readlines()
        self.currentLine = 0

    def hasMoreLines(self):
        if len(self.lines) > 0:
            return True
        else:
            return False
        
    def advance(self):
        for line in self.lines:
            match = (re.search("//", line))
            if match:
                i = match.span()
                for char in line[0:i[0]]:
                    if char != " ":
                        break
                    else:
                        self.currentLine += 1
            else:
                self.currentLine += 1

    def close(self):
        self.asmFile.close()

def main():
    parser = Parser(sys.argv[1])
    parser.advance()

if __name__ == "__main__":
    main()