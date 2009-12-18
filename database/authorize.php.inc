<?php

include_once dirname(__FILE__).'/../utils/conf.php.inc';
include_once dirname(__FILE__).'/pdo_mysql.php.inc';

class Authorize {

  private $connection = null;

  public function __construct() {
    // Connect to the database
    $this->connection = PDOMysql::getInstance();
  }

  public function Login($username, $password) {
    // Get configuration
    global $conf;

    // Start the session
    session_start();

    // Create sql data array
    $data = array(
      'username' => $username,
      'password' => md5($password)
    );

    // Create statement
    $statement = 'SELECT id, fullname, level, last_login
                  FROM account WHERE username = :username
                   AND password = :password
                   AND active = 1';
    
    // Get data from database
    $query = null;
    $row = null;
    try {
      $query = $this->connection->execute($statement, $data);
      $row = $query->fetch(PDO::FETCH_ASSOC);
      $query->closeCursor();
    }
    catch (Exception $e) {
      throw new Exception('Error getting authorisation information from the database!');
    }

    if (count($row) == 4) {
      // Create session id and timestamp
      $sessid = uniqid(rand());
      $time = (int)(time());
      $expire = $time + $conf->getCookieExpire();

      // Remove expired sessions from the database
      $statement = 'DELETE FROM session WHERE time < :intime';
      try {
        $query = $this->connection->execute($statement, array('intime' => $time));
      }
      catch (Exception $e) {
        throw new Exception('Error deleting expired session ids: ' . $e->getMessage());
      }

      // Insert session into the database
      $statement = 'INSERT INTO session VALUES(:sessid, :expire)';
      try {
        $data = array(
                  'sessid' => $sessid,
                  'expire' => $expire
                );
        $query = $this->connection->execute($statement, $data);
      }
      catch (Exception $e) {
        throw new Exception('Error inserting new session into the database: ' . $e->getMessage());
      }

      // Update last login
      $statement = 'UPDATE account SET last_login = :lastLogin WHERE username = :username';
      try {
        $data = array(
                  'lastLogin' => time(),
                  'username'  => $username
                );
        $query = $this->connection->execute($statement, $data);
      }
      catch (Exception $e) {
        throw new Exception('Error updateing last login time in the database: ' . $e->getMessage());
      }

      // Set cookie
      setcookie($conf->getCookieName(), $sessid);

      // Set session information on the server
      $_SESSION['sessid']    = $sessid;
      $_SESSION['id']        = $row['id'];
      $_SESSION['level']     = $row['level'];
      $_SESSION['lastLogin'] = $row['last_login'];
      $_SESSION['username']  = $username;
      $_SESSION['fullname']  = $row['fullname'];
      $_SESSION['retries']   = 0;
    }
    else {
      if ($_SESSION['retries'] >= 2) {
        // Close user, this is the third try
        $statement = 'UPDATE account SET active=0 WHERE username = :username';
        try {
          $query = $this->connection->execute($statement, array('username' => $username));
        }
        catch (Exception $e) {
          throw new Exception('Error communicating with the database: ' . $e->getMessage());
        }

        // End session
        session_destroy();
        throw new Exception('For mange login forsøge. <br />Bruger er blevet lukket, kontakt administrator');
      }
      else {
        $_SESSION['retries']++;
      }

      throw new Exception("Ingen adgang");
    }
  }

  public function isAuthorized() {
    global $conf;

    // Start session
    session_start();

    if (isset($_COOKIE[$conf->getCookieName()])) {
      // Get information saved in cookie
      $cookiedata = stripslashes($_COOKIE[$conf->getCookieName()]);

      // Extra check of session id
      if ($cookiedata != $_SESSION['sessid']) {
        $this->CleanUp();
        return false;
      }

      // Check database information about login
      $statement = 'SELECT id, time FROM session WHERE id = :sessid';
      $query = null;
      try {
        $query = $this->connection->execute($statement, array('sessid' => $cookiedata));
        $row = $query->fetch(PDO::FETCH_ASSOC);
        $query->closeCursor();
      }
      catch (Exception $e) {
        throw new Exception('Error verifying cookie information in the database: ' . mysql_error());
      }

      if (count($row) == 2) {
        // Get time elapsed since last check
        $now = (int)(time());
        $last = $row['time'];
        $interval = $now - $last;
        $expire = $now + $conf->getCookieExpire();

        // See if cookie is expired
        if ($interval > $conf->getCookieExpire()) {
          // Session expired, remove it from the database
          $statement = 'DELETE FROM session WHERE id = :sessid';
          try {
            $query = $this->connection->execute($statement, array('sessid' => $cookiedata));
          }
          catch (Exception $e) {
            throw new Exception('Error removing expired session information: '. $e->getMessage());
          }
          $this->CleanUp();
          return false;
        }
        else {
          // Session valied update the database
          $statement = 'UPDATE session SET time = :expire WHERE id = :sessid';
          try {
            $data = array(
                      'expire' => $expire,
                      'sessid' => $cookiedata
                    );
            $query = $this->connection->execute($statement, $data);
          }
          catch (Exception $e) {
            throw new Exception('Error updateing session information in the database: '. $e->getMessage());
          }
          return true;
        }
      }
    }
    else {
      return false;
    }
  }

  public function Logout() {
    global $conf;

    // Start the session
    session_start();

    if (isset($_COOKIE[$conf->getCookieName()])) {
      // Get information saved in cookie
      $cookiedata = stripslashes($_COOKIE[$conf->getCookieName()]);

      // Remove session from the database
      $statement = 'DELETE FROM session WHERE id = :sessid';
      try {
        $query = $this->connection->execute($statement, array('sessid' => $cookiedata));
      }
      catch (Exception $e) {
        throw new Exception('Error removing expired session information: ' . mysql_error());
      }

      $this->CleanUp();
    }
  }

  private function CleanUp() {
    global $conf;
    setcookie($conf->getCookieName(), '', time() - 10*365*24*60*60);
    session_destroy();
  }
}

?>