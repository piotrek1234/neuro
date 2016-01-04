## @file calcpy/tests.py
#  @brief c++ calculation library Python API unit testing

import django.test
import calc
import views
import time

cmdmgr = calc.CommandManager()
configPath="calc/config.xml"

class CalcPyLibraryTestCase(django.test.TestCase):
    """integration test, call C++ library interface from Python"""

    """def test01getNumber(self):
        self.assertEqual( calc.getNumber(), 1234 )

    def test02command(self):
        cmdmgr = calc.CommandManager()
        cmd_id = cmdmgr.start()
        self.assertNotEqual( cmdmgr.getState(cmd_id), calc.DONE )
        for i in range(100):
            time.sleep(0.1)
            if cmdmgr.getState(cmd_id) == calc.DONE:
                break
        self.assertEqual( cmdmgr.getState(cmd_id), calc.DONE )
        self.assertEqual( len(cmdmgr.getIds()), 1 )"""
    
    def test01AddAndKillPlayer(self):
        cmdmgr.addTokenConfigPath(calc.Color.BLUE, configPath)
        cmdmgr.addTokenConfigPath(calc.Color.RED, configPath)
        cmdmgr.addTokenConfigPath(calc.Color.GREEN, configPath)
        cmdmgr.addTokenConfigPath(calc.Color.YELLOW, configPath)
        self.assertEqual(cmdmgr.addPlayer("player1"), True)
        self.assertEqual(cmdmgr.addPlayer("player2"), True)
        self.assertEqual(cmdmgr.addPlayer("player3"), True)
        self.assertEqual(cmdmgr.addPlayer("player4"), True)
        self.assertEqual(cmdmgr.addPlayer("player5"), False)
        self.assertEqual(cmdmgr.getPlayersNames(), ["player1", "player2", "player3", "player4"])
        
        self.assertEqual(cmdmgr.killPlayer(calc.Color.GREEN), True)
        self.assertEqual(cmdmgr.killPlayer(calc.Color.YELLOW), True)
        self.assertEqual(cmdmgr.killPlayer(calc.Color.GREEN), False)
        self.assertEqual(cmdmgr.getPlayersNames(), ["player1", "player2"])
        
        player = cmdmgr.getCurrentPlayer()
        self.assertEqual(player["name"], "player1")
        self.assertEqual(player["color"], calc.Color.BLUE)
        self.assertEqual(player["tokens"], [1])
        self.assertEqual(player["stack_size"], 7)
        
        player = cmdmgr.getNextPlayer()
        self.assertEqual(player["name"], "player2")
        self.assertEqual(player["color"], calc.Color.RED)
        self.assertEqual(player["tokens"], [1])
        self.assertEqual(player["stack_size"], 7)
        
        cmdmgr.removeAllPlayers()
        self.assertEqual(cmdmgr.getPlayersNames(), [])
    
    def test02getPlayers(self):
        cmdmgr.restartGame()
        self.assertEqual(cmdmgr.addPlayer("player1"), True)
        self.assertEqual(cmdmgr.addPlayer("player2"), True)
        self.assertEqual(cmdmgr.getPlayersNames(), ["player1", "player2"])
        
        player = cmdmgr.getCurrentPlayer()
        self.assertEqual(player["name"], "player1")
        self.assertEqual(player["color"], calc.Color.BLUE)
        self.assertEqual(player["tokens"], [1])
        self.assertEqual(player["stack_size"], 7)
        
        player = cmdmgr.getNextPlayer()
        self.assertEqual(player["name"], "player2")
        self.assertEqual(player["color"], calc.Color.RED)
        self.assertEqual(player["tokens"], [1])
        self.assertEqual(player["stack_size"], 7)
        
        player = cmdmgr.getCurrentPlayer()
        self.assertEqual(player["name"], "player2")
        
        player = cmdmgr.getNextPlayer()
        self.assertEqual(player["name"], "player1")
        
        players= cmdmgr.getPlayers()
        self.assertEqual(players, [{'color': calc.Color.BLUE, 'tokens': [1], 'name': 'player1', 'stack_size': 7}, {'color': calc.Color.RED, 'tokens': [1], 'name': 'player2', 'stack_size': 7}])
        
    
    def test03addAndThrowTokens(self):
        cmdmgr.restartGame()
        self.assertEqual(cmdmgr.addPlayer("player1"), True)
        self.assertEqual(cmdmgr.addPlayer("player2"), True)
        self.assertEqual(cmdmgr.getPlayersNames(), ["player1", "player2"])
        player = cmdmgr.getCurrentPlayer()
        self.assertEqual(player["name"], "player1")
        self.assertEqual(player["stack_size"], 7)
        self.assertFalse(cmdmgr.addToken(5, calc.Color.BLUE, 1, -1, 0))
        self.assertTrue(cmdmgr.addToken(1, calc.Color.BLUE, 1, -1, 0))
        self.assertFalse(cmdmgr.addToken(1, calc.Color.BLUE, 1, -1, 0))
        self.assertFalse(cmdmgr.addToken(1, calc.Color.GREEN, 1, -1, 0))
        
        player = cmdmgr.getCurrentPlayer()
        self.assertEqual(player["stack_size"], 6)
        
        player = cmdmgr.getNextPlayer()
        self.assertEqual(player["name"], "player2")
        self.assertEqual(player["stack_size"], 7)
        self.assertFalse(cmdmgr.throwToken(1, calc.Color.RED))
        self.assertFalse(cmdmgr.addToken(1, calc.Color.RED, 1, -1, 0))
        self.assertTrue(cmdmgr.addToken(1, calc.Color.RED, 0, -1, 0))
        player = cmdmgr.getCurrentPlayer()
        self.assertEqual(player["stack_size"], 6)
        
        player = cmdmgr.getNextPlayer()
        self.assertEqual(player["name"], "player1")
        self.assertEqual(player["tokens"], [2, 3, 4])
        self.assertTrue(cmdmgr.throwToken(2, calc.Color.BLUE))
        player = cmdmgr.getCurrentPlayer()
        self.assertEqual(player["stack_size"], 5)
        self.assertEqual(player["tokens"], [3, 4])
    
    def test04getBoard(self):
        board = cmdmgr.getBoard()
        self.assertEqual(board,  {(1, -1, 0): 1, (0, -1, 1): 1})
    
    def test05actionTokens(self):
        pass
        

"""class CalcPyViewTestCase(django.test.TestCase):

    def test01getNumber(self):
        self.assertEqual( views.getNumber({}), {'number': 1234})

    def test02getCommands(self):
        self.assertEqual( views.getCommands({}),
                          {1: {'progress': 0.995, 'state': 'DONE'}})
        dict1 = views.getCommands({})
        views.startCommand({});
        dict2 = views.getCommands({})
        self.assertEqual( len(dict1) + 1, len(dict2) )"""







