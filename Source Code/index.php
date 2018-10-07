<!--
    @author Akaash Venkat
-->

<!DOCTYPE html>
  <html lang="en">
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
            <li class="current">
              <a href="index.php">
                Campus Floor Plans
              </a>
            </li>
            <li>
              <a href="./route.php">
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
                .myHover
                {
                  position: fixed;
                  top: 16%;
                  right: 2%;
                }
              </style>
              <img src="images/compass.png" alt="icon" class="myHover" width="200" height="200"/>
              <?php 
                for($x = 0; $x < 1; $x++) 
                {
                  echo "&nbsp;</br>";
                } 
                echo '<img src="images/A1.png" alt="icon" class="myImage"/>';
                for($x = 0; $x < 3; $x++) 
                {
                  echo "&nbsp;</br>";
                } 
                echo '<img src="images/A2.png" alt="icon" class="myImage"/>';
                for($x = 0; $x < 3; $x++) 
                {
                  echo "&nbsp;</br>";
                } 
                echo '<img src="images/B.png" alt="icon" class="myImage"/>';
                for($x = 0; $x < 2; $x++) 
                {
                  echo "&nbsp;</br>";
                } 
              ?>         
            </form>
          </div>
        </div>
        <?php
          for($x = 0; $x < 3; $x++) 
          {
            echo "</div>";
          } 
          echo "</body>";
          echo '<footer><p>Idea: Jared Huang, Sana Shrikant, Akaash Venkat. Implementation: Akaash Venkat. Copyright &copy; 2018</p></footer>';
          exit(0);
        ?>
      </div>
    </body>
  </html>
