<!--
    Project derived from an idea by a group of three members (Jared Huang, Sana Shrikant, and Akaash Venkat) working on Northrop Grumman’s
        2018 Intern Hackathon at the Woodland Hills Campus.
    Code written by Akaash Venkat.
-->

<!DOCTYPE html>
  <html lang="en"><html>
    <link type="text/css" rel="stylesheet" href="./css/stylez.css">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <head>
      <meta charset="utf-8">
    </head>
    <body>
      <header>
        <div class="container">
          <div id="branding">
	          <h1>
              CubeMate
            </h1>
          </div>
          <nav>
            <ul>
              <li>
                <a href="./index.php">
                  Campus Floor Plans
                </a>
              </li>
              <li class="current">
                <a href="route.php">
                  Campus Navigation
                </a>
              </li>
            </ul>
          </nav>
        </div>
      </header>
    </head>
    <body>
      <div class="light">
        <div class="row">
          <div class="col-sm-9 col-sm-offset-3 col-md-10 col-md-offset-2 main">
            <div class="col-sm-9 col-sm-offset-3 col-md-10 col-md-offset-2 main">
              <form method = 'GET' action='#'> 
                <div class="form-group">
                  <label for="start">
                    Start:
                  </label>
                  <?php 
                    for ($x = 0; $x < 4; $x++) 
                    {
                      echo "&nbsp;";
                    } 
                  ?>  
                  <select class="form-control" name='sBuilding' onchange="this.form.submit()">
                    <option value=NULL>
                      Building #
                    </option>
                    <?php
                      if (isset($_GET['sBuilding']) && $_GET['sBuilding'] == 'A') 
                      {
                        echo '<option selected="selected" value=A>Building A</option><br />';
                        echo '<option value=B>Building B</option><br />';
                      }
                      else if (isset($_GET['sBuilding']) && $_GET['sBuilding'] == 'B') 
                      {
                        echo '<option value=A>Building A</option><br />';
                        echo '<option selected="selected" value=B>Building B</option><br />';
                      }
                      else
                      {
                        echo '<option value=A>Building A</option><br />';
                        echo '<option value=B>Building B</option><br />';
                      }
                    ?>
                  </select>
                  <select class="form-control" name='sFloor' onchange="this.form.submit()">
                    <option value=NULL>
                      Floor #
                    </option>
                    <?php
                      if (isset($_GET['sBuilding']) && $_GET['sBuilding'] == 'A') 
                      {
                        if (isset($_GET['sFloor']) && $_GET['sFloor'] == 1)
                        {
                          echo '<option selected="selected" value=1>Floor 1</option><br />';
                          echo '<option value=2>Floor 2</option><br />';
                        }
                        else if (isset( $_GET['sFloor'] ) && $_GET['sFloor'] == 2)
                        {
                          echo '<option value=1>Floor 1</option><br />';
                          echo '<option selected="selected" value=2>Floor 2</option><br />';
                        }
                        else 
                        {
                          echo '<option value=1>Floor 1</option><br />';
                          echo '<option value=2>Floor 2</option><br />';
                        }    
                      }
                      else if (isset($_GET['sBuilding'])  && $_GET['sBuilding'] == 'B') 
                      {
                        if (isset( $_GET['sFloor'] ) && $_GET['sFloor'] == 1)
                        {
                          echo '<option selected="selected" value=1>Floor 1</option><br />';
                        }
                        else 
                        {
                          echo '<option value=1>Floor 1</option><br />';
                        }
                      }
                    ?>
                  </select>
                  <select class="form-control" name='sRoom' style="width: 250px">
                    <option value=NULL>
                      Room #
                    </option>
                    <?php
                      $sID = 0;
                      if (isset($_GET['sRoom']))
                      {
                        $sID = $_GET['sRoom'];
                      }
                      $db = new mysqli('127.0.0.1', 'root', 'pass', 'CubeMate');
                      if ($db->connect_errno > 0) 
                      {
                        die('Unable to connect to database [' . $db->connect_error . ']');
                      }       
                      $query = "SELECT ID, Name FROM Regions WHERE Building = '" . $_GET["sBuilding"] . "' AND Floor = " . $_GET["sFloor"] . ";";
                      $rs = $db->query($query);
                      while($row = mysqli_fetch_array($rs)) 
                      {
                        if (preg_match('/[^a-zA-Z]/', $row['Name'][0]))
                        {
                          if ($row['ID'] == $sID)
                          {
                            echo "<option selected='selected' value=" . $row['ID'] . ">Room " . $row['Name'] . "</option>";
                            echo "<br />";
                          }
                          else 
                          {
                            echo "<option value=" . $row['ID'] . ">Room " . $row['Name'] . "</option>";
                            echo "<br />";
                          }
                        }
                        else 
                        {
                          if ($row['ID'] == $sID)
                          {
                            echo "<option selected='selected' value=" . $row['ID'] . ">" . $row['Name'] . "</option>";
                            echo "<br />";
                          }
                          else 
                          {
                            echo "<option value=" . $row['ID'] . ">" . $row['Name'] . "</option>";
                            echo "<br />";
                          }
                        }   
                      }
                      mysqli_free_result($rs);
                    ?> 
                  </select>
                  <?php 
                    for ($x = 0; $x < 19; $x++) 
                    {
                      echo "&nbsp;";
                    } 
                  ?>    
                <class="form-group">
                  <label for="end">
                    End:
                  </label>
                  <?php 
                    for ($x = 0; $x < 5; $x++) 
                    {
                      echo "&nbsp;";
                    } 
                  ?>  
                  <select class="form-control" name='eBuilding' onchange="this.form.submit()">
                    <option value=NULL>
                      Building #
                    </option>
                    <?php
                      if (isset($_GET['eBuilding']) && $_GET['eBuilding'] == 'A') 
                      {
                        echo '<option selected="selected" value=A>Building A</option><br />';
                        echo '<option value=B>Building B</option><br />';
                      }
                      else if (isset($_GET['eBuilding']) && $_GET['eBuilding'] == 'B') 
                      {
                        echo '<option value=A>Building A</option><br />';
                        echo '<option selected="selected" value=B>Building B</option><br />';
                      }
                      else
                      {
                        echo '<option value=A>Building A</option><br />';
                        echo '<option value=B>Building B</option><br />';
                      }
                    ?>
                  </select>
                  <select class="form-control" name='eFloor' onchange="this.form.submit()">
                    <option value=NULL>
                      Floor #
                    </option>
                    <?php
                      if (isset($_GET['eBuilding']) && $_GET['eBuilding'] == 'A') 
                      {
                        if (isset( $_GET['eFloor']) && $_GET['eFloor'] == 1)
                        {
                          echo '<option selected="selected" value=1>Floor 1</option><br />';
                          echo '<option value=2>Floor 2</option><br />';
                        }
                        else if (isset($_GET['eFloor']) && $_GET['eFloor'] == 2)
                        {
                          echo '<option value=1>Floor 1</option><br />';
                          echo '<option selected="selected" value=2>Floor 2</option><br />';
                        }
                        else 
                        {
                          echo '<option value=1>Floor 1</option><br />';
                          echo '<option value=2>Floor 2</option><br />';
                        }   
                      }
                      else if (isset($_GET['eBuilding']) && $_GET['eBuilding'] == 'B') 
                      {
                        if (isset( $_GET['eFloor'] ) && $_GET['eFloor'] == 1)
                        {
                          echo '<option selected="selected" value=1>Floor 1</option><br />';
                        }
                        else 
                        {
                          echo '<option value=1>Floor 1</option><br />';
                        }
                      }
                    ?>
                  </select>
                  <select class="form-control" name='eRoom' style="width: 250px">
                    <option value=NULL>
                      Room #
                    </option>
                    <?php
                      $eID = 0;
                      if (isset($_GET['eRoom']))
                      {
                        $eID = $_GET['eRoom'];
                      }
                      $db = new mysqli('127.0.0.1', 'root', 'pass', 'CubeMate');
                      if ($db->connect_errno> 0) 
                      {
                        die('Unable to connect to database [' . $db->connect_error . ']');
                      }       
                      $query = "SELECT ID, Name FROM Regions WHERE Building = '" . $_GET["eBuilding"] . "' AND Floor = " . $_GET["eFloor"] . ";";
                      $rs = $db->query($query);
                      while($row = mysqli_fetch_array($rs)) 
                      {
                        if (preg_match('/[^a-zA-Z]/', $row['Name'][0]))
                        {
                          if ($row['ID'] == $eID)
                          {
                            echo "<option selected='selected' value=" . $row['ID'] . ">Room " . $row['Name'] . "</option>";
                            echo "<br />";
                          }
                          else 
                          {
                            echo "<option value=" . $row['ID'] . ">Room " . $row['Name'] . "</option>";
                            echo "<br />";
                          }
                        }
                        else 
                        {
                          if ($row['ID'] == $eID)
                          {
                            echo "<option selected='selected' value=" . $row['ID'] . ">" . $row['Name'] . "</option>";
                            echo "<br />";
                          }
                          else 
                          {
                            echo "<option value=" . $row['ID'] . ">" . $row['Name'] . "</option>";
                            echo "<br />";
                          }
                        }
                      }
                      mysqli_free_result($rs);
                    ?> 
                  </select>
                  <?php 
                    for ($x = 0; $x < 20; $x++) 
                    {
                      echo "&nbsp;";
                    } 
                  ?>
                  <button class="button_1" name="button1" type="submit">
                    Navigate
                  </button>
              </form>
            </div>
            <style type="text/css">
              .myImage
              {
                margin: auto;
                display: block; 
                width: auto;
                height: auto;
                max-width: 60%;
                max-height: 60%;
                border: 2px solid blue;
              }
              .myHoverImage
              {
                position: fixed;
                top: 24%;
                right: 2%;
              }
              .myHoverCompass
              {
                position: fixed;
                top: 25%;
                right: 55%;
              }
            </style>
            <?php
              if (!isset($_GET["sBuilding"]) && !isset($_GET["eBuilding"]) && !isset($_GET["sFloor"]) && !isset($_GET["eFloor"]) && !isset($_GET["sRoom"]) && !isset($_GET["eRoom"])) 
              {
                for ($x = 0; $x < 4; $x++) 
                {
		              echo "</div>";   
                }
                echo "</body>";
                for ($x = 0; $x < 21; $x++) 
                {
		              echo "&nbsp</br>";   
		            }
                //echo "<footer><p>Idea: Jared Huang, Sana Shrikant, Akaash Venkat. Implementation: Akaash Venkat. Copyright &copy; 2018</p></footer>";
                exit(0);
              }
              else
              {
                if (isset($_GET[button1]) && ($_GET["sBuilding"] == 'NULL' || $_GET["eBuilding"] == 'NULL' || $_GET["sFloor"] == 'NULL' || $_GET["eFloor"] == 'NULL' || $_GET["sRoom"] == 'NULL' || $_GET["eRoom"] == 'NULL'))
                {
                  for ($x = 0; $x < 2; $x++) 
                  {
                    echo "&nbsp</br>";   
                  }
                  echo "Error: Not all the fields above have been selected. Please select all the fields.";
                }
                else if ($_GET["sBuilding"] == $_GET["eBuilding"] && $_GET["sFloor"] == $_GET["eFloor"] && $_GET["sRoom"] == $_GET["eRoom"])
                {
                  for ($x = 0; $x < 2; $x++) 
                  {
                    echo "&nbsp</br>";   
                  }
                  echo "Error: Start and end locations are the same. Please select unique start and end locations.";
                }
                else if (isset($_GET[button1]))
                {
                /*
                  if ($_GET["sBuilding"] == 'A' && $_GET["sFloor"] == 1)
                  {
                    echo "<img src='images/A1.png' alt='icon' class='myHoverImage' width='750' height='450'/>";
                  }
                  else if ($_GET["sBuilding"] == 'A' && $_GET["sFloor"] == 2)
                  {
                    echo "<img src='images/A2.png' alt='icon' class='myHoverImage' width='750' height='450'/>";
                  }
                  else 
                  {
                    echo "<img src='images/B.png' alt='icon' class='myHoverImage' width='750' height='450'/>";
                  }
                  echo "<img src='images/compass.png' alt='icon' class='myHoverCompass' width='125' height='125'/>";
                 */
                  for ($x = 0; $x < 3; $x++) 
                  {
                    echo "</div>";   
                  }
                  echo "</body>";
                  for ($x = 0; $x < 3; $x++) 
                  {
                    echo "&nbsp</br>";   
                  }
                  exec('cd /Users/akaashvenkat/Sites/cubeMate/cpp/ && ./main_cpp 2>&1');
                  exec('chmod 777 /tmp/server.sock 2>&1');
                  error_reporting(E_ALL);
                  if (!($sock = socket_create(AF_UNIX, SOCK_STREAM, 0)))
                  {
                    $errorcode = socket_last_error();
                    $errormsg = socket_strerror($errorcode);
                    die("Couldn't create socket: [$errorcode] $errormsg \n");
                  }
                  if (!socket_connect($sock , '/tmp/server.sock'))
                  {
                    $errorcode = socket_last_error();
                    $errormsg = socket_strerror($errorcode);
                    die("Could not connect: [$errorcode] $errormsg \n");
                  }
                  $message = $_GET["sRoom"] . " " . $_GET["eRoom"] . " 99";
                  if (!socket_send( $sock , $message , strlen($message) , 0))
                  {
                    $errorcode = socket_last_error();
                    $errormsg = socket_strerror($errorcode);
                    die("Could not send data: [$errorcode] $errormsg \n");
                  }
                  if(socket_recv( $sock , $buf , 1024, MSG_WAITALL ) === FALSE)
                  {
                    $errorcode = socket_last_error();
                    $errormsg = socket_strerror($errorcode);
                    die("Could not receive data: [$errorcode] $errormsg \n");
                  }
                  if ($buf == "99")
                  {
                    sleep(1);
                    $file = fopen("navigation.txt", "r") or exit("Unable to open file!");
                    while(!feof($file))
                    {
                      echo fgets($file). "<br>";
                    }
                    fclose($file);
                  }
                  socket_close($sock);
                  
                  for ($x = 0; $x < 4; $x++) 
                  {
                    echo "</div>";   
                  }
                  for ($x = 0; $x < 4; $x++) 
                  {
                    echo "&nbsp</br>";   
                  }
                    //echo "<footer><p>Idea: Jared Huang, Sana Shrikant, Akaash Venkat. Implementation: Akaash Venkat. Copyright &copy; 2018</p></footer>";
                  exit(0);
                }
                else 
                {
                  for ($x = 0; $x < 4; $x++) 
                  {
                    echo "</div>";   
                  }
                  echo "</body>";
                  for ($x = 0; $x < 21; $x++) 
                  {
                    echo "&nbsp</br>";   
                  }
                  //echo "<footer><p>Idea: Jared Huang, Sana Shrikant, Akaash Venkat. Implementation: Akaash Venkat. Copyright &copy; 2018</p></footer>";
                  exit(0);
                }
                for ($x = 0; $x < 4; $x++) 
                {
		              echo "</div>";   
                }
                echo "</body>";
                for ($x = 0; $x < 18; $x++) 
                {
		              echo "&nbsp</br>";   
		            }
                //echo "<footer><p>Idea: Jared Huang, Sana Shrikant, Akaash Venkat. Implementation: Akaash Venkat. Copyright &copy; 2018</p></footer>";
                exit(0);
              }
              echo "&nbsp;</br>";
              for ($x = 0; $x < 3; $x++)
              {
                echo "</div>";
              }
            ?>
          </div>
        </div>
      </div>
    </body>
  </html>
