 (*
  * Busina
  * 08.07.2012
  *)

let test_food () =
  let to_lvl_two () =
    if (!PlayerInventory.piv.Inventory.nourriture > 4) then
      true
    else
      false
  in
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

let test_mineral () =
  let to_lvl_two () =
    if (!PlayerInventory.piv.Inventory.linemate > 0) then
      true
    else
      false
  in
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

let incant () =
  let to_lvl_two () =
    Bridge.push (Bridge.Pose Inventory.Linemate);
    Bridge.push Bridge.Incantation
  in
  let aux = function
    | 1 -> to_lvl_two ()
    | 2 -> ()
    | 3 -> ()
    | 4 -> ()
    | 5 -> ()
    | 6 -> ()
    | 7 -> ()
    | _ -> ()
  in
  aux !FsmBase.plvl
