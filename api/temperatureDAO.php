<?php

class TemperatureDAO{
    
    public static function addTemperature($temperature,$device_id){
        $connection = Connection::getConnection();
        $sql = "INSERT INTO rs_temperatures (temperature,device_id,time)"
                . "VALUES('$temperature', '$device_id' ,NOW())";
        $result = mysqli_query($connection, $sql);
        
        $ar = new stdClass();
        if($result){
            $ar->result = true;
            $ar->descricao = "Temperatura adicionada.";
        } else {
            $ar->error = 3;
            $ar->description = "Erro na execução da query.";
        }
        return $ar;
    }
    
    public static function getTemperatureById($id) {
        $connection = Connection::getConnection();
        $sql = "SELECT id,device_id,temperature,DATE_FORMAT(time, '%d/%m/%Y %H:%i') as time FROM rs_temperatures WHERE id = $id";
        $result = mysqli_query($connection, $sql);
        $temperature = mysqli_fetch_object($result);

        return $temperature;
    }
    
    public static function getAll() {
        $connection = Connection::getConnection();
        $sql = "SELECT id,device_id,temperature,DATE_FORMAT(time, '%d/%m/%Y %H:%i') as time FROM rs_temperatures";

        // recupera todos os categorias
        $result = mysqli_query($connection, $sql);
        $temperatures = array();
        while ($temperature = mysqli_fetch_object($result)) {
            if ($temperature != null) {
                $temperatures[] = $temperature;
            }
        }
        return $temperatures;
    }
}

?>