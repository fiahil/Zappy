 (*
  * Busina
  * 05.07.2012
  *)

(* type pattern = int;; *)

let view_lvl = [| 0; 2; 6; 12; 20; 30; 42; 56; 72 ; 1000 |]

let piv = ref (Inventory.empty ())
  (* { *)
    (* nourriture = 0; *)
    (* linemate = 0; *)
    (* deraumere = 0; *)
    (* sibur = 0; *)
    (* mendiane = 0; *)
    (* phiras = 0; *)
    (* thystame = 0; *)
  (* } *)

let plvl = ref 1

let set_lvl tab =
  let rec aux tab idx =
    if (view_lvl.(idx) > (Array.length tab)) then
      plvl := (idx - 1)
    else
      aux tab (idx + 1)
  in
  aux tab 0

(* Find function *)
let find rcs =
  Bridge.push (Bridge.Voir);

  let nb_rcs tab id = function
    | Inventory.Nourriture -> tab.(id).Inventory.nourriture
    | Inventory.Linemate   -> tab.(id).Inventory.linemate
    | Inventory.Deraumere  -> tab.(id).Inventory.deraumere
    | Inventory.Sibur      -> tab.(id).Inventory.sibur
    | Inventory.Mendiane   -> tab.(id).Inventory.mendiane
    | Inventory.Phiras     -> tab.(id).Inventory.phiras
    | Inventory.Thystame   -> tab.(id).Inventory.thystame
  in
  let rec line_finder tab idx idxl =
    let test_line tab idx idxl (left, right) =
      if (left != 0) then
	view_lvl.(idx) + idxl
      else if (right != 0) then
	view_lvl.(idx) - idxl
      else
	line_finder tab idx (idxl + 1)
    in
    if (idxl > idx) then
      (-1)
    else
      test_line tab idx idxl
	(nb_rcs tab (view_lvl.(idx) + idxl) rcs, nb_rcs tab (view_lvl.(idx) - idxl) rcs)
  in
  let rec in_find tab idx =
    let test_ret tab idx = function
      | -1 -> in_find tab (idx + 1)
      | rt ->
	begin
	  set_lvl tab;
	  rt
	end
    in
    if (idx > 8 || (view_lvl.(idx) + 1) >= (Array.length tab)) then
      begin
	set_lvl tab;
	(-1)
      end
    else
      test_ret tab idx (line_finder tab idx 0)
  in
  in_find (Bridge.voir (Bridge.pull Bridge.Voir)) 0


(* Move function *)
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
  if (off = 0) then
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
  else if (off >= (72 - 8) && off <= (72 + 8)) then
    begin
      forward 8;
      turn off 72
    end
  else
    ()

(* Gather functions *)
let gather rcs nb =
  let rec in_gather = function
    | 0 -> ()
    | it ->
      begin
	Bridge.push (Bridge.Prend rcs);
	piv := (Inventory.inc !piv rcs);
	in_gather (it - 1)
      end
  in
  in_gather nb

let gather_all () =
  Bridge.push (Bridge.Voir);
  let aux tab =
    gather Inventory.Nourriture tab.(0).Inventory.nourriture;
    gather Inventory.Linemate tab.(0).Inventory.linemate;
    gather Inventory.Deraumere tab.(0).Inventory.deraumere;
    gather Inventory.Sibur tab.(0).Inventory.sibur;
    gather Inventory.Mendiane tab.(0).Inventory.mendiane;
    gather Inventory.Phiras tab.(0).Inventory.phiras;
    gather Inventory.Thystame tab.(0).Inventory.thystame
  in
  aux (Bridge.voir (Bridge.pull Bridge.Voir))

let gather_all_rcs rcs =
  Bridge.push (Bridge.Voir);
  let aux tab = function
    | Inventory.Nourriture -> gather Inventory.Nourriture tab.(0).Inventory.nourriture
    | Inventory.Linemate   -> gather Inventory.Linemate tab.(0).Inventory.linemate
    | Inventory.Deraumere  -> gather Inventory.Deraumere tab.(0).Inventory.deraumere
    | Inventory.Sibur      -> gather Inventory.Sibur tab.(0).Inventory.sibur
    | Inventory.Mendiane   -> gather Inventory.Mendiane tab.(0).Inventory.mendiane
    | Inventory.Phiras     -> gather Inventory.Phiras tab.(0).Inventory.phiras
    | Inventory.Thystame   -> gather Inventory.Thystame tab.(0).Inventory.thystame
  in
  aux (Bridge.voir (Bridge.pull Bridge.Voir)) rcs
