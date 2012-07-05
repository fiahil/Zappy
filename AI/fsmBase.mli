 (*
  * Busina
  * 05.07.2012
  *)

type pattern

(* find a resources with a "voir" instruction,
   return the offset of the resources in a pattern *)
val find : Bridge.resources -> pattern

(* follow the pattern to move the player
   with "avance", "gauche" and "droite" instruction *)
val move : pattern -> unit

(* gather the specified quantity of the ressources at the current position *)
val gather : Bridge.resources -> int -> unit;

(* gather all of the resources at the current position *)
val gather_all : Bridge.ressources -> unit;