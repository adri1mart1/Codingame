import sys
import math

n = int(input())

class Player:
    def __init__(self, n, s):
        self.num = n
        self.sign = s

class Match:
    round = 0
    played = False
    p1 = None
    p2 = None
    winner = 0

    def __init__(self, p1, p2, r):
        self.p1 = p1
        self.p2 = p2
        self.round = r

    def play(self):
        self.played = True

    def get_winner(self):
        self.winner = 1
        if self.p1.sign == self.p2.sign:
            if self.p1.num < self.p2.num:
                return self.p1
            else:
                self.winner = 2
                return self.p2
        if self.p1.sign == 'R':
            if self.p2.sign == 'C' or self.p2.sign == 'L':
                return self.p1
        elif self.p1.sign == 'L':
            if self.p2.sign == 'S' or self.p2.sign == 'P':
                return self.p1
        elif self.p1.sign == 'S':
            if self.p2.sign == 'C' or self.p2.sign == 'R':
                return self.p1
        elif self.p1.sign == 'C':
            if self.p2.sign == 'P' or self.p2.sign == 'L':
                return self.p1
        elif self.p1.sign == 'P':
            if self.p2.sign == 'R' or self.p2.sign == 'S':
                return self.p1
        self.winner = 2
        return self.p2

    def get_oponent(self):
        return self.p2 if self.winner == 1 else self.p1

class Tournament:
    players = []
    matches = []
    rounds = 0
    winner = 0

    def add_player(self, p):
        self.players.append(p)

    # this function perform all matches round per round
    # each match has a winner
    # each winner is assigned to a new match, all news 
    # matches are added to the matches list
    def run_all_matches(self):
        self.__prepare_matches(self.players, 1)
        self.rounds = int(math.log(n, 2))
        for r in range(1, self.rounds+1):
            remaining_players = []
            for i in range(len(self.matches)):
                if self.matches[i].played == False:
                    self.matches[i].play()
                    remaining_players.append(self.matches[i].get_winner())
            self.__prepare_matches(remaining_players, r+1)

    # prepare a list of match based on a list of players
    def __prepare_matches(self, players, r):
        ret = []
        for i in range(1, len(players), 2):
            m = Match(players[i-1], players[i], r)
            self.matches.append(m)

    def print_winner(self):
        for m in self.matches:
            if m.round == self.rounds:
                self.winner = m.get_winner().num
                print("{}".format(self.winner))
                break

    def print_winner_opponents(self):
        for r in range(1, self.rounds+1):
            space = "" if r == self.rounds else " "
            for m in self.matches:
                if m.round == r and (m.p1.num == self.winner or m.p2.num == self.winner):
                    print("{}{}".format(m.get_oponent().num, space), end='')
                    break
        print('') #  last \n char

tournament = Tournament()

for i in range(n):
    numplayer, signplayer = input().split()
    numplayer = int(numplayer)
    p = Player(numplayer, signplayer)
    tournament.add_player(p)

tournament.run_all_matches()
tournament.print_winner()
tournament.print_winner_opponents()