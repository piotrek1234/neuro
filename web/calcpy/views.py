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
    cmd_id = cmdmgr.addPlayer(name)

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
    cmdgr.restartGame()

def addToken(tokenId, color, q, r , angle):
    """get tokens on board command"""
    return cmdmgr.addToken(tokenId, color, q, r , angle)

def throwToken(tokenId, color):
    """get tokens on board command"""
    return cmdmgr.throwToken(tokenId, color)

def getNextPlayer():
    """get tokens on board command"""
    return cmdmgr.getNextPlayer()

def getCurrentPlayer():
    """get tokens on board command"""
    return cmdmgr.getCurrentPlayer()

def killPlayer(color):
    """get tokens on board command"""
    return cmdmgr.killPlayer(color)

def addTokenConfigPath(color, path):
    """get tokens on board command"""
    return cmdmgr.addTokenConfigPath(color, path)

def actionTokenBattle(tokenId, color):
    """get tokens on board command"""
    return cmdmgr.actionTokenBattle(tokenId, color)

def actionTokenMove(tokenId, color, fromQ, fromR, toQ, toR):
    """get tokens on board command"""
    return cmdmgr.actionTokenMove(tokenId, color, fromQ, fromR, toQ, toR)

def actionTokenPush(tokenId, color, fromQ, fromR, toQ, toR):
    """get tokens on board command"""
    return cmdmgr.actionTokenPush(tokenId, color, fromQ, fromR, toQ, toR)