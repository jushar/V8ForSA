local functions = {
	{"setPlayerMoney", setPlayerMoney}
}

for k, info in ipairs(functions) do
	bindV8Function(info[1], info[2])
end