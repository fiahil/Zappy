 (*
  * Busina
  * 05.07.2012
  *)

type pattern = int;;

let timeout t =
    ignore (Unix.select [] [] [] t)

let find rcs =
  Bridge.push (Bridge.Voir);
  let rec in_find (Bridge.R_voir (Bridge.RP_voir tab)) idx rcs =
    if (idx > (Array.lenght tab)) then
      (-1)
    else
      let find_rcs = function
	| 0 -> in_find (Bridge.R_voir (Bridge.RP_voir tab)) (idx + 1) rcs
	| _ -> idx
      in
      match rcs with
	| Inventory.Nourriture -> find_rcs tab.(idx).Inventory.nourriture
	| Inventory.Linemate   -> find_rcs tab.(idx).Inventory.linemate
	| Inventory.Deraumere  -> find_rcs tab.(idx).Inventory.deraumere
	| Inventory.Sibur      -> find_rcs tab.(idx).Inventory.sibur
	| Inventory.Mendiane   -> find_rcs tab.(idx).Inventory.mendiane
	| Inventory.Phiras     -> find_rcs tab.(idx).Inventory.phiras
	| Inventory.Thystame   -> find_rcs tab.(idx).Inventory.thystame
  in
  in_find (Bridge.pull ()) 0 rcs

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

let gather_all rcs =
  Bridge.push (Bridge.Voir);
  let in_gather_all (Bridge.R_voir (Bridge.RP_voir tab)) = function
    | Inventory.Nourriture -> gather Inventory.Nourriture tab.(0).Inventory.nourriture
    | Inventory.Linemate   -> gather Inventory.Linemate tab.(0).Inventory.linemate
    | Inventory.Deraumere  -> gather Inventory.Deraumere tab.(0).Inventory.deraumere
    | Inventory.Sibur      -> gather Inventory.Sibur tab.(0).Inventory.sibur
    | Inventory.Mendiane   -> gather Inventory.Mendiane tab.(0).Inventory.mendiane
    | Inventory.Phiras     -> gather Inventory.Phiras tab.(0).Inventory.phiras
    | Inventory.Thystame   -> gather Inventory.Thystame tab.(0).Inventory.thystame
  in
  in_gather_all (Bridge.pull ()) rcs

let rec unitest () =
  ignore (Bridge.pull ());
  ignore (Bridge.pull ());
  gather_all Inventory.Nourriture;
  gather Inventory.Linemate 1;
  move 4;
  gather_all Inventory.Nourriture;
  move 12;
  gather Inventory.Linemate 2;
  gather_all Inventory.Nourriture;
  unitest ()
