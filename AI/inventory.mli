(*
 * Fiahil
 * 06.07.2012
 *)

type resources =
  | Joueur
  | Nourriture
  | Linemate
  | Deraumere
  | Sibur
  | Mendiane
  | Phiras
  | Thystame

type t =
    {
      joueur : int;
      nourriture : int;
      linemate : int;
      deraumere : int;
      sibur : int;
      mendiane : int;
      phiras : int;
      thystame : int
    }

(*
 * Return an empty inventory
 *)
val empty : unit -> t

(*
 * Increment a resource
 *)
val inc : t -> resources -> t

(*
 * Decrease a resource
 *)
val dec : t -> resources -> t


(*
 * Set a value to a resource
 *)
val set : t -> int -> resources -> t
