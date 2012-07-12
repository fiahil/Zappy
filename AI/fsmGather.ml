 (*
  * Busina
  * 09.07.2012
  *)

let fls_round = ref 0

let rec gather iv =
  let default = function
    | 0 -> Bridge.push Bridge.Avance
    | 1 -> Bridge.push Bridge.Droite
    | _ -> Bridge.push Bridge.Gauche
  in
  let action = function
    | -1 ->
      begin
	fls_round := !fls_round + 1;
        default (Random.int 3);
        Bridge.push Bridge.Avance
      end
    | ps ->
      begin
	fls_round := 0;
        FsmBase.move ps;
        FsmBase.gather_all ()
      end
  in
  action (FsmBase.mineral_find iv)
