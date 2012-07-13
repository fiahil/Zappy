 (*
  * Busina
  * 08.07.2012
  *)

let test_crit_food () =
  if (!PlayerInventory.piv.Inventory.nourriture > 5) then
    true
  else
    false

let test_food () =
  let to_lvl nb =
    if (!PlayerInventory.piv.Inventory.nourriture > (nb * 6)) then
      true
    else
      false
  in
  let aux = function
    | 1 -> to_lvl 1
    | 2 -> to_lvl 2
    | 3 -> to_lvl 2
    | 4 -> to_lvl 4
    | 5 -> to_lvl 4
    | 6 -> to_lvl 6
    | 7 -> to_lvl 6
    | _ -> false
  in
  aux !FsmBase.plvl

let test_mineral () =
  let to_lvl_two () =
    if (!PlayerInventory.piv.Inventory.linemate > 0) then
      (true, [])
    else
      (false, [Inventory.Linemate, 1])
  in
  let to_lvl_three () =
    if (!PlayerInventory.piv.Inventory.linemate > 0) &&
      (!PlayerInventory.piv.Inventory.deraumere > 0) &&
      (!PlayerInventory.piv.Inventory.sibur > 0)
    then
      (true, [])
    else
      (false, [(Inventory.Linemate, 1 - !PlayerInventory.piv.Inventory.linemate);
	       (Inventory.Deraumere, 1 - !PlayerInventory.piv.Inventory.deraumere);
	       (Inventory.Sibur, 1 - !PlayerInventory.piv.Inventory.sibur)])
  in
  let to_lvl_four () =
    if (!PlayerInventory.piv.Inventory.linemate > 1) &&
      (!PlayerInventory.piv.Inventory.sibur > 0) &&
      (!PlayerInventory.piv.Inventory.phiras > 1)
    then
      (true, [])
    else
      (false, [(Inventory.Linemate, 2 - !PlayerInventory.piv.Inventory.linemate);
	       (Inventory.Sibur, 1 - !PlayerInventory.piv.Inventory.sibur);
	       (Inventory.Phiras, 2 - !PlayerInventory.piv.Inventory.phiras)])
  in
  let to_lvl_five () =
    if (!PlayerInventory.piv.Inventory.linemate > 0) &&
      (!PlayerInventory.piv.Inventory.deraumere > 0) &&
      (!PlayerInventory.piv.Inventory.sibur > 1) &&
      (!PlayerInventory.piv.Inventory.phiras > 0)
    then
      (true, [])
    else
      (false, [(Inventory.Linemate, 1 - !PlayerInventory.piv.Inventory.linemate);
	       (Inventory.Deraumere, 1 - !PlayerInventory.piv.Inventory.deraumere);
	       (Inventory.Sibur, 2 - !PlayerInventory.piv.Inventory.sibur);
	       (Inventory.Phiras, 1 - !PlayerInventory.piv.Inventory.phiras)])
  in
  let to_lvl_six () =
    if (!PlayerInventory.piv.Inventory.linemate > 0) &&
      (!PlayerInventory.piv.Inventory.deraumere > 1) &&
      (!PlayerInventory.piv.Inventory.sibur > 0) &&
      (!PlayerInventory.piv.Inventory.mendiane > 2)
    then
      (true, [])
    else
      (false, [(Inventory.Linemate, 1 - !PlayerInventory.piv.Inventory.linemate);
	       (Inventory.Deraumere, 2 - !PlayerInventory.piv.Inventory.deraumere);
	       (Inventory.Sibur, 1 - !PlayerInventory.piv.Inventory.sibur);
	       (Inventory.Mendiane, 3 - !PlayerInventory.piv.Inventory.mendiane)])
  in
  let to_lvl_seven () =
    if (!PlayerInventory.piv.Inventory.linemate > 0) &&
      (!PlayerInventory.piv.Inventory.deraumere > 1) &&
      (!PlayerInventory.piv.Inventory.sibur > 2) &&
      (!PlayerInventory.piv.Inventory.phiras > 0)
    then
      (true, [])
    else
      (false, [(Inventory.Linemate, 1 - !PlayerInventory.piv.Inventory.linemate);
	       (Inventory.Deraumere, 2 - !PlayerInventory.piv.Inventory.deraumere);
	       (Inventory.Sibur, 3 - !PlayerInventory.piv.Inventory.sibur);
	       (Inventory.Phiras, 1 - !PlayerInventory.piv.Inventory.phiras)])
  in
  let to_lvl_eight () =
    if  (!PlayerInventory.piv.Inventory.linemate > 1) &&
      (!PlayerInventory.piv.Inventory.deraumere > 1) &&
      (!PlayerInventory.piv.Inventory.sibur > 1) &&
      (!PlayerInventory.piv.Inventory.phiras > 1) &&
      (!PlayerInventory.piv.Inventory.mendiane > 1) &&
      (!PlayerInventory.piv.Inventory.thystame > 0)
    then
      (true, [])
    else
      (false, [(Inventory.Linemate, 2 - !PlayerInventory.piv.Inventory.linemate);
	       (Inventory.Deraumere, 2 - !PlayerInventory.piv.Inventory.deraumere);
	       (Inventory.Sibur, 2 - !PlayerInventory.piv.Inventory.sibur);
	       (Inventory.Phiras, 2 - !PlayerInventory.piv.Inventory.phiras);
	       (Inventory.Mendiane, 2 - !PlayerInventory.piv.Inventory.mendiane);
	       (Inventory.Thystame, 1 - !PlayerInventory.piv.Inventory.thystame)])
  in
  let aux = function
    | 1 -> to_lvl_two ()
    | 2 -> to_lvl_three ()
    | 3 -> to_lvl_four ()
    | 4 -> to_lvl_five ()
    | 5 -> to_lvl_six ()
    | 6 -> to_lvl_seven ()
    | 7 -> to_lvl_eight ()
    | _ -> (false, [])
  in
  let rec clear_list ret = function
    | ( res , [])            -> (res, ret)
    | ( res , (t, nb)::next) ->
      if (nb < 1) then
	clear_list ret (res, next)
      else
	clear_list ((t, nb)::ret) (res, next)
  in
  clear_list [] (aux !FsmBase.plvl)

let call_player nb =
  IncantManager.init_incant_id ();
  Broadcast.bc (Broadcast.Icq (!IncantManager.id, !FsmBase.plvl));
  let pars_bc list = function
    | Broadcast.Icr (idi, idp, _) ->
      begin
	if (idi = !IncantManager.id) then
	  idp::list
	else
	  list
      end
    | _ -> list
  in

  let rec loop list it =
    Bridge.init ();
    if (it < 50) then
      begin
	let come_at_me_bro list =
	  Broadcast.bc (Broadcast.Ici (!IncantManager.id, list));
	  let rec pars_come_info cnt = function
	    | Broadcast.Icr (idi, idp, rdy) ->
	      begin
		if (idi = !IncantManager.id) && (rdy) then
		  pars_come_info (cnt + 1) (Broadcast.pp (Bridge.take))
		else if idi = !IncantManager.id then
                  pars_come_info cnt (Broadcast.pp (Bridge.take))
                else
		  pars_come_info cnt (Broadcast.pp (Bridge.take))
	      end
            | Broadcast.Err ""          -> cnt
	    | _                         -> pars_come_info cnt (Broadcast.pp (Bridge.take))
	  in

	  let rec come_loop cnt =
	    Bridge.init ();
	    if (test_crit_food ()) then
	      begin
		if (cnt = nb) then
		  true
		else
		  begin
		    Broadcast.bc (Broadcast.Icz !IncantManager.id);
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

	if (List.length list = nb) then
	  come_at_me_bro list
	else
	  loop (pars_bc list (Broadcast.pp (Bridge.take))) (it + 1)
      end
    else
      false
  in

  if ((loop [] 0) = false) then
    begin
      Broadcast.bc (Broadcast.Ica !IncantManager.id);
      false
    end
  else
    begin
      Broadcast.bc (Broadcast.Icl !IncantManager.id);
      true
    end

let incant () =
  let to_lvl_two () =
    Bridge.push (Bridge.Pose Inventory.Linemate);
    Bridge.push Bridge.Incantation
  in
  let to_lvl_three () =
    if (call_player 1) then
      begin
	Bridge.push (Bridge.Pose Inventory.Linemate);
	Bridge.push (Bridge.Pose Inventory.Deraumere);
	Bridge.push (Bridge.Pose Inventory.Sibur);
	Bridge.push Bridge.Incantation;
	Broadcast.bc (Broadcast.Icl !IncantManager.id)
      end
    else
      ()
  in
  let to_lvl_four () =
    if (call_player 1) then
      begin
	Bridge.push (Bridge.Pose Inventory.Linemate);
	Bridge.push (Bridge.Pose Inventory.Linemate);
	Bridge.push (Bridge.Pose Inventory.Sibur);
	Bridge.push (Bridge.Pose Inventory.Phiras);
	Bridge.push (Bridge.Pose Inventory.Phiras);
	Bridge.push Bridge.Incantation;
	Broadcast.bc (Broadcast.Icl !IncantManager.id)
      end
    else
      ()
  in
  let to_lvl_five () =
    if (call_player 3) then
      begin
	Bridge.push (Bridge.Pose Inventory.Linemate);
	Bridge.push (Bridge.Pose Inventory.Deraumere);
	Bridge.push (Bridge.Pose Inventory.Sibur);
	Bridge.push (Bridge.Pose Inventory.Sibur);
	Bridge.push (Bridge.Pose Inventory.Phiras);
	Bridge.push Bridge.Incantation;
	Broadcast.bc (Broadcast.Icl !IncantManager.id)
      end
    else
      ()
  in
  let to_lvl_six () =
    if (call_player 3) then
      begin
	Bridge.push (Bridge.Pose Inventory.Linemate);
	Bridge.push (Bridge.Pose Inventory.Deraumere);
	Bridge.push (Bridge.Pose Inventory.Deraumere);
	Bridge.push (Bridge.Pose Inventory.Sibur);
	Bridge.push (Bridge.Pose Inventory.Mendiane);
	Bridge.push (Bridge.Pose Inventory.Mendiane);
	Bridge.push (Bridge.Pose Inventory.Mendiane);
	Bridge.push Bridge.Incantation;
	Broadcast.bc (Broadcast.Icl !IncantManager.id)
      end
    else
      ()
  in
  let to_lvl_seven () =
    if (call_player 5) then
      begin
	Bridge.push (Bridge.Pose Inventory.Linemate);
	Bridge.push (Bridge.Pose Inventory.Deraumere);
	Bridge.push (Bridge.Pose Inventory.Deraumere);
	Bridge.push (Bridge.Pose Inventory.Sibur);
	Bridge.push (Bridge.Pose Inventory.Sibur);
	Bridge.push (Bridge.Pose Inventory.Sibur);
	Bridge.push (Bridge.Pose Inventory.Phiras);
	Bridge.push Bridge.Incantation;
	Broadcast.bc (Broadcast.Icl !IncantManager.id)
      end
    else
      ()
  in
  let to_lvl_eight () =
    if (call_player 5) then
      begin
	Bridge.push (Bridge.Pose Inventory.Linemate);
	Bridge.push (Bridge.Pose Inventory.Linemate);
	Bridge.push (Bridge.Pose Inventory.Deraumere);
	Bridge.push (Bridge.Pose Inventory.Deraumere);
	Bridge.push (Bridge.Pose Inventory.Sibur);
	Bridge.push (Bridge.Pose Inventory.Sibur);
	Bridge.push (Bridge.Pose Inventory.Phiras);
	Bridge.push (Bridge.Pose Inventory.Phiras);
	Bridge.push (Bridge.Pose Inventory.Mendiane);
	Bridge.push (Bridge.Pose Inventory.Mendiane);
	Bridge.push (Bridge.Pose Inventory.Thystame);
	Bridge.push Bridge.Incantation;
	Broadcast.bc (Broadcast.Icl !IncantManager.id)
      end
    else
      ()
  in
  let aux = function
    | 1 -> to_lvl_two ()
    | 2 -> to_lvl_three ()
    | 3 -> to_lvl_four ()
    | 4 -> to_lvl_five ()
    | 5 -> to_lvl_six ()
    | 6 -> to_lvl_seven ()
    | 7 -> to_lvl_eight ()
    | _ -> ()
  in
  aux !FsmBase.plvl
