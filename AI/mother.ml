 (*
  *  Busina
  *  13.07.12
  *)

let child = ref []
let size_max = ref 8

let rec run () =

  let rec launch_fork = function
    | 0 -> ()
    | nb ->
      Bridge.push Bridge.Fork;
      ignore (Bridge.pull Bridge.Fork);
      Bridge.push Bridge.Avance;
      launch_fork (nb - 1)
  in

  let rec connect_soldier = function
    | 0  -> ()
    | nb ->
      child := ((Unix.create_process Sys.argv.(0)
		   [|
		     Sys.argv.(0);
		     "-n";
		     !Param.team;
		     "-h";
		     !Param.host;
		     "-p";
		     (string_of_int !Param.port);
		     "-s"
		   |]
		   Unix.stdin Unix.stdout Unix.stderr)::(!child));
      connect_soldier (nb - 1)
  in

  let test_connect sz = function
    | 0  -> ()
    | n ->
      if (sz < !size_max) then
	if ((n + sz) > !size_max) then
	  connect_soldier (!size_max - sz)
	else
	  connect_soldier (n)
  in

  let ret_connect = function
    | 0  -> 8
    | nb ->
      if (nb > 8) then
	0
      else
	(8 - nb)
  in

  let rec test_rcp = function
     | Broadcast.Err ""  -> ()
     | Broadcast.Err msg  ->
       if (!PlayerInventory.piv.Inventory.nourriture < 10) then
	 ()
       else
	 Bridge.push (Bridge.Broadcast msg)
     | _                 -> test_rcp (Broadcast.pp Bridge.take)
  in

  let rec cycle = function
    | 200 ->
      launch_fork 4;
      size_max := !size_max + 4;
      cycle 0
    | nb ->
      Bridge.init ();
      Bridge.push Bridge.Connect_nbr;
      test_connect (List.length !child) (Bridge.connect (Bridge.pull Bridge.Connect_nbr));
      test_rcp (Broadcast.pp Bridge.take);
      if (!PlayerInventory.piv.Inventory.nourriture < 100) then
	FsmSurvival.min_survival []
      else
	Bridge.push (Bridge.Avance)
      ;
      cycle (nb + 1)
  in

  Bridge.push Bridge.Connect_nbr;
  launch_fork (ret_connect (Bridge.connect (Bridge.pull Bridge.Connect_nbr)));
  cycle 0
