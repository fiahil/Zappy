 (*
  * Busina
  * 09.07.2012
  *)

let fls_round = ref 0


let call_rsc iv =
  ResourcesManager.init_exchange ();
  Broadcast.bc (Broadcast.Rsn iv);
  let rec loop = function
    | 50 ->
      begin
	Broadcast.bc Broadcast.Rsa;
	false
      end
    | cnt ->
      begin
	let rec pars_info = function
          | Broadcast.Rsh (id, idp)   ->
	    if (id = !ResourcesManager.id) then
	      Broadcast.bc (Broadcast.Rsc (!ResourcesManager.id, idp))
	    else
	      pars_come_info (Broadcast.pp (Bridge.take))
          | Broadcast.Err ""          -> ()
          | _                         -> pars_info (Broadcast.pp (Bridge.take))
	in

	let rec pars_come_info cnt = function
          | Broadcast.Rsr (idi, rdy) ->
            begin
              if (idi = !ResourcesManager.id) && (rdy) then
		cnt + 1
            end
          | Broadcast.Err ""          -> cnt
          | _                         -> pars_come_info cnt (Broadcast.pp (Bridge.take))
        in

	let rec come_loop cnt =
          Bridge.init ();
          if (test_crit_food ()) then
            begin
              if (cnt = 1) then
                true
              else
                begin
                  Broadcast.bc (Broadcast.Rsz !ResourcesManager.id);
                  Bridge.push (Bridge.Voir);
                  ignore (Bridge.pull (Bridge.Voir));
                  Bridge.push (Bridge.Voir);
                  ignore (Bridge.pull (Bridge.Voir));
                  Bridge.push (Bridge.Voir);
                  ignore (Bridge.pull (Bridge.Voir));
                  Bridge.push (Bridge.Voir);
                  ignore (Bridge.pull (Bridge.Voir));
                  come_loop (pars_come_info cnt (Broadcast.pp (Bridge.take)))
                end
            end
          else
            false
        in

        come_loop 0
        in

	let rec pars_ret = function
	  | -1 -> loop (cnt + 1)
	  | ret -> come_loop cnt
	in
	pars_ret (parse_info (Broadcast.pp (Bridge.take))))
      end
  in
  if (loop 0 = false) then
    begin
      Broadcast.bc (Broadcast.Rsa !ResourcesManager.id);
      false
    end
  else
    begin
      (* Gather loop *)
      true
    end


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
  if (fls_round > 4 && (call_rsc iv)) then
    fls_roud := 0
  else
    action (FsmBase.mineral_find iv)
