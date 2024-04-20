// firebase.php

<?php
if(!empty($_GET))
{
    date_default_timezone_set("Asia/Kolkata");

    // Firebase project URL
    $firebaseUrl = "https://sensor-squad-3c47b-default-rtdb.firebaseio.com/";

    // Firebase authentication token
    $authToken = "OD8wa7g2vfRppdFowa5hzVGoeMvZtz6Isx20pkEH";

    // Retrieve sensor data from GET parameters
    $lpg = isset($_GET['lpg']) ? $_GET['lpg'] : null;
    $temperature = isset($_GET['temperature']) ? $_GET['temperature'] : null;
    $water = isset($_GET['water']) ? $_GET['water'] : null;
    $motion = isset($_GET['motion']) ? $_GET['motion'] : null;
    $soil = isset($_GET['soil']) ? $_GET['soil'] : null;
    $fire = isset($_GET['fire']) ? $_GET['fire'] : null;
    $ir = isset($_GET['ir']) ? $_GET['ir'] : null;
    $time = date('h:i a');
    $date = date('d-m-Y');
    
    // Construct data array
    $data = array(
        'LPG' => $lpg,
        'Temperature' => $temperature,
        'Water' => $water,
        'Motion' => $motion,
        'Soil' => $soil,
        'Fire' => $fire,
        'Door_Status' => $ir,
        'Time' => $time,
        'Date' => $date
    );

    // Convert data to JSON format
    $jsonData = json_encode($data);

    // Initialize cURL session
    $ch = curl_init();

    // Set cURL options
    curl_setopt($ch, CURLOPT_URL, $firebaseUrl . 'sensor_data.json?auth=' . $authToken);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_setopt($ch, CURLOPT_POSTFIELDS, $jsonData);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

    // Execute cURL session
    $response = curl_exec($ch);

    // Close cURL session
    curl_close($ch);

    // Check if data was successfully sent
    if ($response === false) {
        echo "Error sending data to Firebase.";
    } else {
        echo "Data sent to Firebase successfully.";
    }

}
?>