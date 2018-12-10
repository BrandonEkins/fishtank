<?php
$fh = fopen("info.html", "w") or die("can't open file!");

fwrite($fh, "<!DOCTYPE html><html>");
fwrite($fh, $_GET['temp']);
fwrite($fh, " Degrees");
fwrite($fh, "</br>");
fwrite($fh, $_GET['photo']);
fwrite($fh, "/600");
fwrite($fh, "</html>");

fclose($fh);
?>
