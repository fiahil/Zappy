 (*
  * Busina
  * 05.07.2012
  *)

val plvl : int ref

val mineral_find : (Inventory.resources * int) list -> int

(* find a resources with a "voir" instruction,
   return the offset of the resources in a pattern *)
val find : Inventory.resources -> int

(* follow the pattern to move the player
   with "avance", "gauche" and "droite" instruction *)
val move : int -> unit

(* gather the specified quantity of the ressources at the current position *)
val gather : Inventory.resources -> int -> unit

(* gather all of the resources at the current position *)
val gather_all : unit -> unit

(* gather all of the specified resources at the current position *)
val gather_all_rcs : Inventory.resources -> unit
