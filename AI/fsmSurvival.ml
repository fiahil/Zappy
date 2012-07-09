(*
 * Busina
 * 07.07.2012
 *)

let rec survival () =
  let default = function
    | 0 -> Bridge.push Bridge.Avance
    | 1 -> Bridge.push Bridge.Droite
    | _ -> Bridge.push Bridge.Gauche
  in
  let action = function
    | -1 ->
      begin
	default (Random.int 3);
	Bridge.push Bridge.Avance
      end
    | ps ->
      begin
	FsmBase.move ps;
	FsmBase.gather_all ();
	if (FsmIncant.test_incant ()) then
	  begin
	    Bridge.push Bridge.Incantation;
	    ignore (Unix.select [] [] [] 30.)
	  end
      end
  in
  action (FsmBase.find Inventory.Nourriture);
  Printf.printf "Test :: Un cycle and my lvl is %d\n" !FsmBase.plvl;
  Printf.printf "      : and my inventory is like = \n";
  Printf.printf "      : - nourriture : %2d units\n" !PlayerInventory.piv.Inventory.nourriture;
  Printf.printf "      : - linemate   : %2d units\n" !PlayerInventory.piv.Inventory.linemate;
  Printf.printf "      : - deraumere  : %2d units\n" !PlayerInventory.piv.Inventory.deraumere;
  Printf.printf "      : - sibur      : %2d units\n" !PlayerInventory.piv.Inventory.sibur;
  Printf.printf "      : - mendiane   : %2d units\n" !PlayerInventory.piv.Inventory.mendiane;
  Printf.printf "      : - phiras     : %2d units\n" !PlayerInventory.piv.Inventory.phiras;
  Printf.printf "      : - thystame   : %2d units\n" !PlayerInventory.piv.Inventory.thystame;
  flush stdout;
  PlayerInventory.valid ();
  Printf.printf "New   :: Un cycle and my lvl is %d\n" !FsmBase.plvl;
  Printf.printf "      : and my inventory is like = \n";
  Printf.printf "      : - nourriture : %2d units\n" !PlayerInventory.piv.Inventory.nourriture;
  Printf.printf "      : - linemate   : %2d units\n" !PlayerInventory.piv.Inventory.linemate;
  Printf.printf "      : - deraumere  : %2d units\n" !PlayerInventory.piv.Inventory.deraumere;
  Printf.printf "      : - sibur      : %2d units\n" !PlayerInventory.piv.Inventory.sibur;
  Printf.printf "      : - mendiane   : %2d units\n" !PlayerInventory.piv.Inventory.mendiane;
  Printf.printf "      : - phiras     : %2d units\n" !PlayerInventory.piv.Inventory.phiras;
  Printf.printf "      : - thystame   : %2d units\n" !PlayerInventory.piv.Inventory.thystame;
  flush stdout;
  survival ()
