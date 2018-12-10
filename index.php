<?php
#shell_exec("sudo touch test");
$output = shell_exec("sudo python tankMove.py");
echo $output;

?>
