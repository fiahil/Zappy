 (*
  * Busina
  * 08.07.2012
  *)


let to_lvl_two () =
  if (!FsmBase.piv.Inventory.nourriture > 4) && (!FsmBase.piv.Inventory.linemate > 0) then
    begin
      print_endline "Incantation authorized !";
      Bridge.push (Bridge.Pose Inventory.Linemate);
      FsmBase.piv := (Inventory.dec !FsmBase.piv Inventory.Linemate);
      true
    end
  else
    false

let test_incant () =
  let aux = function
    | 1 -> to_lvl_two ()
    | 2 -> false
    | 3 -> false
    | 4 -> false
    | 5 -> false
    | 6 -> false
    | 7 -> false
    | _ -> false
  in
  aux !FsmBase.plvl
