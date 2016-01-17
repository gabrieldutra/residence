<?php

class Connection
{
  public static $database = "residence";
//  public static $address = "150.164.102.160";
 // public static $user = "daw-aluno2";
 // public static $password = "wisney";
  public static $address = "localhost";
  public static $user = "root";
  public static $password = "allods6655";


  public static function getConnection() {
    $connection = mysqli_connect(Connection::$address, Connection::$user, Connection::$password, Connection::$database);
    mysqli_set_charset($connection , 'utf8');
    return $connection;
  }
}
