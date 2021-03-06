/// @file app.js
/// @brief main client module, AngularJS application with routing

angular.module('myApp', ['ngRoute', 'pascalprecht.translate',
                            'hexDirective', 'hexMapDirective', 'userBoardDirective', 'popupDirective', 'tableHexDirective', 'operationBoardDirective', 'battleDirective', 'endGameDirective',
                            'mainController', 'operationBoardController', 'popupController', 'tableHexController', 'hexMapController', 'battleController', 'endGameController', 'actionController'] )
    .config(['$routeProvider', '$translateProvider',
             function($routeProvider, $translateProvider) {
                 $routeProvider.when('/main', {
                     templateUrl: 'views/main.html',
                 });
                 $routeProvider.otherwise( {
                     redirectTo: '/main'
                 });
             }]);

