(*
 * Busina
 * 07.07.2012
 *)

let rec survival iv =
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
	FsmBase.gather_all ()
      end
  in
  action (FsmBase.find Inventory.Nourriture)
