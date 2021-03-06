 (*
  * Busina
  * 08.07.2012
  *)

let _ = Random.self_init ()
let piv = ref (Inventory.empty ())
let pid = ref (Random.int 100000)

let valid iv =
  piv := (Inventory.set !piv iv.Inventory.nourriture Inventory.Nourriture);
  piv := (Inventory.set !piv iv.Inventory.linemate Inventory.Linemate);
  piv := (Inventory.set !piv iv.Inventory.deraumere Inventory.Deraumere);
  piv := (Inventory.set !piv iv.Inventory.sibur Inventory.Sibur);
  piv := (Inventory.set !piv iv.Inventory.mendiane Inventory.Mendiane);
  piv := (Inventory.set !piv iv.Inventory.phiras Inventory.Phiras);
  piv := (Inventory.set !piv iv.Inventory.thystame Inventory.Thystame)
