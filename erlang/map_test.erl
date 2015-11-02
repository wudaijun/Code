-module(map_test).

-compile([export_all]).

create_map(0, Map) -> Map;
create_map(N, Map) ->
  NewMap = maps:put(N, data, Map),
  create_map(N-1, NewMap).

create_dict(0, Dict) -> Dict;
create_dict(N, Dict) ->
  NewDict = dict:store(N, data, Dict),
  create_dict(N-1, NewDict).


create_ets(0, Ets) -> Ets;
create_ets(N, Ets) ->
  true=ets:insert(Ets,{N, data}),
  create_ets(N-1, Ets).



now_ms() ->
  erlang:system_time(micro_seconds)/1000.

write_map(0, Map, _Size) -> Map;
write_map(N, Map, Size) ->
  Key = random:uniform(2*Size),
  NewMap = maps:put(Key, newdata, Map),
  write_map(N-1, NewMap, Size).

write_dict(0, Dict, _Size) -> Dict;
write_dict(N, Dict, Size) ->
  Key = random:uniform(2*Size),
  NewDict = dict:store(Key, newdata, Dict),
  write_dict(N-1, NewDict, Size).


write_ets(0, Ets, _Size) -> Ets;
write_ets(N, Ets, Size) ->
  Key = random:uniform(2*Size),
  true = ets:insert(Ets,{Key, newdata}),
  write_ets(N-1, Ets, Size).


read_map(0, Map, _Size) -> Map;
read_map(N, Map, Size) ->
  Key = random:uniform(2*Size),
  maps:get(Key, Map,1),
  read_map(N-1, Map, Size).

read_dict(0, Dict, _Size) -> Dict;
read_dict(N, Dict, Size) ->
  Key = random:uniform(2*Size),
  dict:find(Key, Dict),
  read_dict(N-1, Dict, Size).


read_ets(0, Ets, _Size) -> Ets;
read_ets(N, Ets, Size) ->
  Key = random:uniform(2*Size),
  ets:lookup(Ets,Key),
  read_ets(N-1, Ets, Size).



test(Size) ->

  Time1 = now_ms(),
  Map   = create_map(Size, #{}),
  Time2 = now_ms(),
  Dict  = create_dict(Size, dict:new()),
  Time3 = now_ms(),
  Ets  = create_ets(Size, ets:new(xx,[])),
  Time4 = now_ms(),

  _NewMap = write_map(10000, Map, Size),
  Time5 = now_ms(),

  _NewDict = write_dict(10000, Dict, Size),
  Time6 = now_ms(),

  _NewEts = write_ets(10000, Ets, Size),
  Time7 = now_ms(),

  read_map(10000, Map, Size),
  Time8 = now_ms(),

  read_dict(10000, Dict, Size),
  Time9 = now_ms(),

  read_ets(10000, Ets, Size),
  Time10 = now_ms(),


  io:format("test size: ~p~n", [Size]),

  io:format("map create cost ~p ms~n", [Time2-Time1]),
  io:format("dict create cost ~p ms~n", [Time3-Time2]),
  io:format("ets create cost ~p ms~n", [Time4-Time3]),

  io:format("---------~n", []),

  io:format("map write cost ~p ms~n", [Time5-Time4]),
  io:format("dict write cost ~p ms~n", [Time6-Time5]),
  io:format("ets write cost ~p ms~n", [Time7-Time6]),

  io:format("---------~n", []),

  io:format("map query cost ~p ms~n", [Time8-Time7]),
  io:format("dict query cost ~p ms~n", [Time9-Time8]),
  io:format("ets query cost ~p ms~n", [Time10-Time9]),

  ok.


