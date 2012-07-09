 (*
  * Busina
  * 08.07.2012
  *)


let to_lvl_two () =
  if (!PlayerInventory.piv.Inventory.nourriture > 4)
    && (!PlayerInventory.piv.Inventory.linemate > 0) then
    begin
      Bridge.push (Bridge.Pose Inventory.Linemate);
      PlayerInventory.piv := (Inventory.dec !PlayerInventory.piv Inventory.Linemate);
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
