<?php

require 'Slim/Slim.php';
\Slim\Slim::registerAutoloader();

require 'connection.php';

date_default_timezone_set("America/Sao_Paulo");


$app = new \Slim\Slim();
$app->response()->header('Content-Type', 'application/json;charset=utf-8');



$app->run();
