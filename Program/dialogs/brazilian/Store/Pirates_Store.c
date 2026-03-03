// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Pode falar, o que você quer?","Acabamos de falar sobre isso. Você deve ter esquecido...","É a terceira vez hoje que você traz essa pergunta...","Olha, aqui é uma loja. As pessoas vêm comprar coisas. Não me atrapalhe!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabe, "+NPChar.name+", talvez da próxima vez.","Certo, por algum motivo eu esqueci...","Sim, realmente é a terceira vez...","Hm, eu não vou...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Escute, "+npchar.name+", você viu Miguel Dichoso na Isla Tesoro recentemente?";
				link.l1.go = "tieyasal";
			}
			// Addon 2016-1 Jason пиратскаЯ линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_start")
			{
				link.l1 = ""+npchar.name+", estou aqui em nome de Marcus Tyrex. Ele disse que você precisava de um homem para um serviço.";
				link.l1.go = "mtraxx";
			}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_win")
			{
				link.l1 = ""+npchar.name+", o 'Rosbohom' foi encontrado e capturado. Devemos começar a descarregar e contar?";
				link.l1.go = "mtraxx_5";
			}
		break;
				
		// город майя
		case "tieyasal":
			dialog.text = "Sim, eu vi. Ele comprou mantimentos para o navio aqui. Foi bem recentemente, aliás. Vocês se desencontraram por poucos dias. Aliás, ele pode ainda estar nesta vila. Eu não fico vigiando ninguém, sabe. Pergunte por aí mais um pouco e, quem sabe, talvez encontre seu don.";
			link.l1 = "Tudo bem. Obrigado pela informação!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
			pchar.quest.Mtraxx_PasqualeLate.over = "yes";
            dialog.text = "Exatamente! Que bom que você chegou a tempo. Agora deixe-me te contar o cerne da questão...";
			link.l1 = "Estou ouvindo.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
			string sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")));
            dialog.text = "Neste momento um "+sTemp+", o navio holandês chamado 'Rosbohom', está chegando às nossas águas acompanhado por um navio de escolta. Ela está carregada de ébano e partiu de Willemstad para encontrar outra escolta e garantir uma viagem segura até a Europa. Não sei qual rota ela vai seguir, se por Sint Maarten ou por Espanyol, mas sei as coordenadas do ponto de encontro deles\nSua missão é encontrar o navio holandês lá, abordar o mercante e trazer a carga para mim. Pagarei assim que a carga for entregue.";
			link.l1 = "Entendi. Hora e local?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
			int i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
			int n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
            dialog.text = ""+sti(pchar.questTemp.Mtraxx.Crdn.degN)+" "+i+" Norte e "+sti(pchar.questTemp.Mtraxx.Crdn.degW)+" "+n+"Oeste. Deve estar em algum lugar ao sul ou sudoeste da Isla Tesoro. Não sou bom nisso, não sou marinheiro, mas você é. Você tem cerca de cinco dias para concluir o trabalho.";
			link.l1 = "Entendido... Já saquei. Então, sem perder tempo!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Boa sorte, capitão. Estarei esperando por você e pela carga.";
			link.l1 = "...";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_convoy";
		   i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
           n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
		   AddQuestRecord("Roger_4", "3");
		   AddQuestUserData("Roger_4", "sShip", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")+ "Gen")));
		   AddQuestUserData("Roger_4", "sdegN", sti(pchar.questTemp.Mtraxx.Crdn.degN));
		   AddQuestUserData("Roger_4", "sminN", i);
		   AddQuestUserData("Roger_4", "sdegW", sti(pchar.questTemp.Mtraxx.Crdn.degW));
		   AddQuestUserData("Roger_4", "sminW", n);
		   SetFunctionTimerCondition("Mtraxx_PasqualeTimeConvoy", 0, 0, 6, false);
		   SetFunctionTimerCondition("Mtraxx_PasqualeConvoyOver", 0, 0, 7, false);
		break;
		
		case "mtraxx_5":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_EBONY);
			if (iTotalTemp < 1)
			{
				dialog.text = "Você está brincando comigo, rapaz? Seus porões não têm uma única tábua de ébano! Isso é uma trapaça insolente! Saia daqui! Vou informar o Marcus sobre isso! Fora!!!";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < makeint(sti(pchar.questTemp.Mtraxx.Crdn.Ebony)/4))
			{
				dialog.text = "Está brincando comigo, rapaz? Seu porão de carga só tem uns fiapos de ébano! Isso é um absurdo, uma enganação! Saia daqui! Vou avisar o Marcus sobre isso! Fora!!!";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < sti(pchar.questTemp.Mtraxx.Crdn.Ebony)-20)
			{
				dialog.text = "O Rosbohom tinha pelo menos "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.Crdn.Ebony))+" de ébano. Por que você trouxe menos?";
				link.l1 = "Bem... sabe, tive que me livrar de parte dela durante a briga. E ainda tem os ratos, malditos...";
				link.l1.go = "mtraxx_7";
				break;
			}
            dialog.text = "Muito bem. Quanto você tem? "+FindRussianQtyString(iTotalTemp)+"? Excelente! Vou pagar 150 pesos por cada peça.";
			link.l1 = "150 peças de oito? Imagino que o ébano custe bem mais.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_6":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_angry";
		   DoQuestReloadToLocation("Pirates_town", "reload", "reload6", "");
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_7":
            dialog.text = "Ratos? Muito bem... Mas tudo certo. 100 pesos por cabeça e você está livre para ir.";
			link.l1 = "100 pesos só? Isso é um roubo descarado!";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
			AddMoneyToCharacter(pchar, iTotalTemp*100);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "Roubo é o seu ofício, capitão, eu sou apenas um simples comerciante. Pegue seu dinheiro e vamos encerrar essa discussão, você já ganhou uma boa quantia vendendo parte da minha carga em outro lugar.";
			link.l1 = "Então vá pro inferno, então!";
			link.l1.go = "mtraxx_9";
		break;
		
		case "mtraxx_9":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_fail";
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_10":
            dialog.text = "And you are right, captain, but first, try selling stolen goods and see how much other merchants will pay you for them. The price I am offering is very high. Second, it was my lead; you would never have found that caravan on your own. Besides, there were other valuables and goods on it, and I am not claiming them. Third, I will give you the highest credit in the eyes of Marcus Tyrex, and that is worth a great deal, trust me. And finally, fourth, a poor merchant must make a living somehow.";
			link.l1 = "Opa! Preciso recuar diante de argumentos tão fortes "+npchar.name+". Vamos fazer umas contas.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
			AddMoneyToCharacter(pchar, iTotalTemp*150);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "Excelente. Pegue suas moedas. Foi um prazer. Não deixe de visitar minha loja de vez em quando. Que a sorte te acompanhe no mar!";
			link.l1 = "E você no seu ramo...";
			link.l1.go = "mtraxx_12";
		break;
		
		case "mtraxx_12":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_complete";
		   AddQuestRecord("Roger_4", "9");
		   pchar.quest.mtr_pasq_fin.win_condition.l1 = "location";
		   pchar.quest.mtr_pasq_fin.win_condition.l1.location = "Pirates_town";
		   pchar.quest.mtr_pasq_fin.function = "Mtraxx_PasqualeJeffry";
		   bDisableFastReload = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
