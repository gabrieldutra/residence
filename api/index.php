<?php

require 'Slim/Slim.php';
\Slim\Slim::registerAutoloader();

require 'connection.php';
require 'temperatureDAO.php';

date_default_timezone_set("America/Sao_Paulo");


$app = new \Slim\Slim();
$app->response()->header('Content-Type', 'application/json;charset=utf-8');

$app->get('/temperatures', function() {
    $authorization = \Slim\Slim::getInstance()->request->headers->get("Authorization");
    $answer = new stdClass();
    $temperatures = TemperatureDAO::getAll();

    $answer->auth_key = $authorization;
    $answer->temperatures = $temperatures;
    if (true) {
        echo json_encode($answer);
    } else {
        $error = new stdClass();
        $error->error = 2;
        $error->description = "Permissões insuficientes!";
        echo json_encode($error);
    }
});

$app->post('/temperatures', function() {
    $authorization = \Slim\Slim::getInstance()->request->headers->get("Authorization");
    // recupera o request
    $request = \Slim\Slim::getInstance()->request();


    if (true) {
        // insere o cliente
        $temperatureBody = json_decode($request->getBody());
        if (isset($temperatureBody->temperature)) {
            $ntemperature = TemperatureDAO::addTemperature($temperatureBody->temperature, 1);
            echo json_encode($ntemperature);
        } else {
            $error = new stdClass();
            $error->error = 2;
            $error->description = "Faltam informações!";
            echo json_encode($error);
        }
    } else {
        $error = new stdClass();
        $error->error = 2;
        $error->description = "Permissões insuficientes!";
        echo json_encode($error);
    }
});


$app->run();
