#! /usr/bin/env python3
# -*- Python -*-

####################################################################################################

import unicodedata

####################################################################################################

def strip_accents(string):
    return ''.join(c for c in unicodedata.normalize('NFD', string)
                   if unicodedata.category(c) != 'Mn')

####################################################################################################

codes = {
    'a': '.-',
    'b': '-...',
    'c': '-.-.',
    'd': '-..',
    'e': '.',
    'f': '..-.',
    'g': '--.',
    'h': '....',
    'i': '..',
    'j': '.---',
    'k': '-.-',
    'l': '.-..',
    'm': '--',
    'n': '-.',
    'o': '---',
    'p': '.--.',
    'q': '--.-',
    'r': '.-.',
    's': '...',
    't': '-',
    'u': '..-',
    'v': '...-',
    'w': '.--',
    'x': '-..-',
    'y': '-.--',
    'z': '--..',
    '0': '-----',
    '1': '.----',
    '2': '..---',
    '3': '...--',
    '4': '....-',
    '5': '.....',
    '6': '-....',
    '7': '--...',
    '8': '---..',
    '9': '----.',
    '.': '.-.-.-',
    ',': '--..--',
    '?': '..--..',
    "'": '.----.', # di-dah-di-di-dah-dit
    '!': '-.-.--', # ---. di-dah-dah-dah-dah-dit
    '/': '-..-.',
    '(': '-.--.', # brackets (parentheses) dah-di-dah-dah-di-dah
    ')': '-.--.-',
    '&': '.-...',
    ':': '---...',
    ';': '-.-.-.',
    '=': '-...-',
    '+': '.-.-.',
    '-': '-....-', # hyphen
    '_': '..--.-',
    '"': '.-..-.',
    '$': '...-..-',
    '@': '.--.-.',
    'ä': '.-.-',
    'æ': '.-.-',
    'à': '.--.-', # á
    'å': '.--.-',
    'ĉ': '-.-..',
    'ç': '-.-..',
    # 'ch' '----'
    'ð': '..--.',
    'è': '.-..-',
    'é': '..-..',
    'ĝ': '--.-.',
    'ĥ': '-.--.',
    'ĵ': '.---.',
    'ñ': '--.--',
    'ö': '---.',
    'ø': '---.',
    'ŝ': '...-.',
    'þ': '.--..',
    'ü': '..--',
    'ŭ': '..--',
}

abbreviations = {
    'SOS': '...---...', # distress message
    'end of transmission': '...-.-',
    'error': '........',
    'invitation to transmit': '-.-',
    'new page signal': '-...-', # .-.-. new paragraph
    'starting signal': '.-.-', # -·-·- new line
    'understood': '...-.',
    'wait': '.-...',
}

# End of message di-dah-di-dah-dit .-.-.
# Break dah-di-di-di-dah-di-dah -...-.-
# Going off the air ("clear") dah-di-dah-di-di-dah-di-dit -.-..-..
# Start copying dah-di-dah-di-dah -.-.-
# Change to wabun code dah-di-di-dah-dah-dah -..---
# Invite a specific station to transmit dah-di-dah-dah-dit -.--.

# .-...-. Mauvaise signalisation, réglez vos feux ! (si transmission lumineuse)
# .-...-. Lumière plus forte ! (transmission lumineuse)
# .--..-- Lumière moins forte ! (transmission lumineuse)
# ....-.. Plus lentement ! (slow down)
# -...- Séparation (« stop »), nouveau paragraphe.
# .-.-. Fin de message/transmission. (« À vous. » : j’attends une réponse de votre part)
# ..--..Pas compris, répétez !

####################################################################################################

code_max_length = 0
for code in codes.values():
    code_max_length = max(len(code), code_max_length)

with open("tmp-international-morse-code.h", 'w') as f:
    for i in range(256):
        if i <= 32:
            f.write('"",{} // {:3}\n'.format(' '*code_max_length, i))
        else:
            character = chr(i)
            character_lower = character.lower()
            code = codes.get(character_lower, "")
            if not code:
                character_without_accent = strip_accents(character)
                if character_without_accent != character:
                    code = codes.get(character_without_accent.lower(), "")
                    # print(character, character_without_accent, code)
            f.write('"{}",{} // {:3} {}\n'.format(code, ' '*(code_max_length - len(code)), i, character))

####################################################################################################

class Node:

    ##############################################

    def __init__(self):

        self.dot_branch = None
        self.dash_branch = None
        self.character = None

    ##############################################

    def add(self, code, character, level = 0):

        if level == len(code):
            self.character = character
        else:
            part = code[level]
            if part == ".":
                if self.dot_branch is None:
                    self.dot_branch = Node()
                branch = self.dot_branch
            else:
                if self.dash_branch is None:
                    self.dash_branch = Node()
                branch = self.dash_branch
            branch.add(code, character, level+1)

    ##############################################

    def dump(self, level = 0):
        indent = '    '*level
        if self.character is not None:
            print(indent + '[{}]'.format(self.character))
        if self.dot_branch is not None:
            print(indent + '.')
            self.dot_branch.dump(level+1)
        if self.dash_branch is not None:
            print(indent + '-')
            self.dash_branch.dump(level+1)

# reverse_map = {code: character for character, code in codes.items()}
# codes = sorted(reverse_map.keys())
# for code in codes:
#     print(code)
root_node = Node()
for character, code in codes.items():
    root_node.add(code, character)
root_node.dump()

####################################################################################################
#
# End
#
####################################################################################################
