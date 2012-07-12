 (*
  * Busina
  * 09.07.2012
  *)

let fls_round = ref 0


let call_rsc iv =
  Broadcast.bc (Broadcast.Rsn iv);
  let loop = function
    | 50 -> Broadcast.bc Broadcast.Rsa;
    | cnt ->
      begin
	let rec pars_come_info = function
          | Broadcast.Rsh (id, idp)   ->
	    if (id = (*ID*)) then
	      Broadcast.bc (Broadcast.Rsc (!ResourcesManager.id, idp))
	    else
	      pars_come_info (Broadcast.pp (Bridge.take))
          | Broadcast.Err ""          -> ()
          | _                         -> pars_come_info (Broadcast.pp (Bridge.take))
	in
	pars_come_info (Broadcast.pp (Bridge.take)))

      end
  in
  loop 0

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
  if (fls_round > 4) then
    begin
      call_rsc iv;
      fls_roud := 0
    end
  else
    action (FsmBase.mineral_find iv)
