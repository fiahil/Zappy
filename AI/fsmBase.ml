 (*
  * Busina
  * 05.07.2012
  *)

type pattern = int;;

let timeout t =
    ignore (Unix.select [] [] [] t)

let find rcs =
  1
;;

let gather_all rcs =
  ()
;;

let move off =
  let rec forward = function
    | 0 -> ()
    | it ->
      begin
	Bridge.push Bridge.Avance;
	forward (it - 1)
      end
  in
  let turn off midd =
    if (off - midd) = 0 then
      ()
    else if (off - midd) < 0 then
      begin
	Bridge.push Bridge.Gauche;
	forward ((off - midd) * -1)
      end
    else
      begin
	Bridge.push Bridge.Droite;
	forward (off - midd)
      end
  in
  if (off == 0) then
    ()
  else if (off >= (2 - 1) && off <= (2 + 1)) then
    begin
      forward 1;
      turn off 2
    end
  else if (off >= (6 - 2) && off <= (6 + 2)) then
    begin
      forward 2;
      turn off 6
    end
  else if (off >= (12 - 3) && off <= (12 + 3)) then
    begin
      forward 3;
      turn off 12
    end
  else if (off >= (20 - 4) && off <= (20 + 4)) then
    begin
      forward 4;
      turn off 20
    end
  else if (off >= (30 - 5) && off <= (30 + 5)) then
    begin
      forward 5;
      turn off 30
    end
  else if (off >= (42 - 6) && off <= (42 + 6)) then
    begin
      forward 6;
      turn off 42
    end
  else if (off >= (56 - 7) && off <= (56 + 7)) then
    begin
      forward 7;
      turn off 56
    end
  else
    ()
;;

let gather rcs nb =
  let rec in_gather = function
    | 0 -> ()
    | it ->
      begin
	Bridge.push (Bridge.Prend rcs);
	in_gather (it - 1)
      end
  in
  in_gather nb
;;

let unitest () =
  gather Bridge.Nourriture 5;
  timeout 0.1;
  gather Bridge.Linemate 1;
  timeout 0.1;
  move 4;
  timeout 0.1;
  gather Bridge.Nourriture 3;
  timeout 0.1;
  move 12;
  timeout 0.1;
  gather Bridge.Linemate 2;
  timeout 0.1;
  gather Bridge.Nourriture 6
;;
