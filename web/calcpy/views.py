## @file calcpy/views.py
#  @brief calculation library interface to client

"""
calc library interface to client

export calculation results to client
"""
import calc

cmdmgr = calc.CommandManager()

def addPlayer(name):
    """add player command"""
    return cmdmgr.addPlayer(name.encode("UTF-8"))

def getPlayersNames():
    """get players names list command"""
    return cmdmgr.getPlayersNames()

def removeAllPlayers():
    """remove all players command"""
    cmdmgr.removeAllPlayers()

def getPlayers():
    """get players list command"""
    return cmdmgr.getPlayers()

def getBoard():
    """get tokens on board command"""
    return cmdmgr.getBoard()

def restartGame():
    """restart game command"""
    cmdmgr.restartGame()

def addToken(tokenId, color, q, r , angle):
    """add token on board command"""
    return cmdmgr.addToken(tokenId, color, q, r , angle)

def throwToken(tokenId, color):
    """throw away token from players stack command"""
    return cmdmgr.throwToken(tokenId, color)

def getNextPlayer():
    """get next player decription with tokens on hands and change current player command"""
    return cmdmgr.getNextPlayer()

def getCurrentPlayer():
    """get current player decription with tokens on hands command"""
    return cmdmgr.getCurrentPlayer()

def killPlayer(color):
    """kill player command"""
    return cmdmgr.killPlayer(color)

def addTokenConfigPath(color, path):
    """add path to file with token config command"""
    return cmdmgr.addTokenConfigPath(color, path)

def actionTokenBattle(tokenId, color):
    """command for token action of type battle"""
    return cmdmgr.actionTokenBattle(tokenId, color)

def actionTokenMove(tokenId, color, fromQ, fromR, toQ, toR):
    """command for token action of type move"""
    return cmdmgr.actionTokenMove(tokenId, color, fromQ, fromR, toQ, toR)

def actionTokenPush(tokenId, color, fromQ, fromR, toQ, toR):
    """command for token action of type push"""
    return cmdmgr.actionTokenPush(tokenId, color, fromQ, fromR, toQ, toR)

def getTokenHand(tokenId, color):
    """get details for given token from hand"""
    return cmdmgr.getTokenHand(tokenId, color)

def getTokenBoard(q, r):
    """get details for given token from board"""
    return cmdmgr.getTokenBoard(q, r)

def performBattle():
    """perform battle without token action"""
    cmdmgr.performBattle()

def getMoves(q, r):
    """returns possible move targets for given position"""
    return cmdmgr.getMoves(q, r)

def getPushes(q, r):
    """returns possible push targets for given position"""
    return cmdmgr.getPushes(q, r)
