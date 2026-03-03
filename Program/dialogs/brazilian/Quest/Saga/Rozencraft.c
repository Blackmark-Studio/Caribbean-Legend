// Михаэль Розенкрафт - голландский капитан, квестовый покупатель бакаута
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Quer alguma coisa?";
			link.l1 = "Não, não é nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "rozencraft":
			if (pchar.questTemp.Saga.Oyster == "cantalk")
			{
				dialog.text = "Hm... E onde está o Molligan? Ele mesmo não queria me ver?";
				link.l1 = "Nosso pobre Paul está com febre. Ele não está com disposição para negociar. Estou aqui no lugar dele.";
				link.l1.go = "rozencraft_1";
			}
			else
			{
				dialog.text = "O que deseja, senhor?";
				link.l1 = "Imagino que você está esperando para comprar um pouco de pau-ferro?";
				link.l1.go = "rozencraft_no";
			}
		break;
		
		case "rozencraft_no":
			dialog.text = "Quem lhe contou essa bobagem, senhor? Não estou esperando ninguém, nem nada. Meu navio está patrulhando esta área por ordem do governador de Willemstad. Então, poderia fazer o favor de deixar meu navio? Deve estar enganado.";
			link.l1 = "Hum... Entendo. Me desculpe por incomodar você.";
			link.l1.go = "rozencraft_no_1";
		break;
		
		case "rozencraft_no_1":
			DialogExit();
			AddQuestRecord("Testament", "8");
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_no_repeat":
			dialog.text = "Já não tivemos essa conversa, senhor?";
			link.l1 = "Sim, sim. Já estou indo e embarcando no meu navio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_1":
			dialog.text = "E quem é você?";
			link.l1 = "Você não se importa com quem faz negócios? Trouxe madeira de ferro para vender. Quanto paga?";
			link.l1.go = "rozencraft_2";
		break;
		
		case "rozencraft_2":
			dialog.text = "Conforme combinado - quarenta doblões por peça.";
			link.l1 = "Hm...";
			link.l1.go = "rozencraft_3";
		break;
		
		case "rozencraft_3":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Amigo, a gente fez um acordo com o Molligan. Esse preço está bom, você não vai achar melhor. Então não venha bancar o camponês na feira. Quanto pau-ferro você tem?";
			link.l1 = ""+FindRussianQtyString(sti(npchar.quest.bakaut))+".";
			link.l1.go = "rozencraft_4";
		break;
		
		case "rozencraft_4":
			iTemp = sti(npchar.quest.bakaut);
			if(iTemp >= 90)
			{
				dialog.text = "Excelente. Isso é mais do que eu esperava. Aqui, pegue o ouro. Se conseguir mais pau-ferro, vá até a taverna em Saint Martin e fale com... você sabe quem. Ele vai marcar um encontro para nós. Vejo que você é um parceiro muito melhor do que aquele idiota do Molligan.";
				link.l1 = "Certo. Está combinado.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Muito bem. Aqui, pegue o ouro. Se conseguir mais pau-ferro, vá até a taverna em Philipsburg e fale com... você sabe quem. Ele vai entrar em contato comigo. Vejo que podemos fazer negócios com você tão bem quanto com aquele idiota do Molligan.";
				link.l1 = "Certo. Está combinado.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 40 && iTemp < 70)
			{
				dialog.text = "Hm... Eu esperava mais. Tudo bem. Aqui, pegue o ouro. E diga ao Molligan que da próxima vez ele deve trazer um lote de pelo menos cem peças.";
				link.l1 = "Tudo bem. Eu vou falar com ele.";
				link.l1.go = "rozencraft_5";
				break;
			}
			dialog.text = "Você está brincando comigo? Tínhamos um acordo com o Molligan, o lote não pode ter menos de cinquenta peças! Cai fora e só volte quando tiver o suficiente.";
			link.l1 = "Tá bom, tá bom, calma.";
			link.l1.go = "rozencraft_5";
		break;
		
		case "rozencraft_5":
			DialogExit();
			npchar.DontDeskTalk = true; // чтоб не доставал, в генераторе - снимаем
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp < 40) DeleteAttribute(npchar, "quest.bakaut");
			else 
			{
				TakeNItems(pchar, "gold_dublon", iTemp*40);
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
				// считаем, сколько мы должны Свенсону
				int ibak = makeint((iTemp*40-2000)/2);
				sld = characterFromId("Svenson");
				sld.quest.bakaut_sum = ibak; // доля Яна
				AddQuestRecord("Testament", "9");
				AddQuestUserData("Testament", "sSum", iTemp*40);
				AddQuestUserData("Testament", "sSum1", ibak);
				if (CheckAttribute(pchar, "GenQuest.Bakaut")) AddQuestUserData("Testament", "sText", "In addition, if I get ironwood, I will be able to sell it to Michael Rosencraft by having a meeting arranged with his man at the tavern in Philipsburg.");
				pchar.questTemp.Saga = "removebakaut";
				// корабль Розенкрафта сохраняем, в АИ на него будет стоять проверка на попадание
				pchar.quest.Saga_Rozencraft_GetOut.over = "yes"; //снять прерывание
				pchar.quest.Saga_Rozencraft_AfterBattle.over = "yes"; //снять прерывание
				// ставим новое прерывание на потопление Розенкрафта
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1 = "Group_Death";
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1.group = "Rozencraft_Group";
				pchar.quest.Bakaut_Rozencraft_Die.function = "Bakaut_RozencraftDie";
				pchar.quest.Bakaut_Rozencraft_Remove.win_condition.l1 = "MapEnter";
				pchar.quest.Bakaut_Rozencraft_Remove.function = "Bakaut_RozencraftRemove";
			}
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
	// ------------------------------------генератор сбыта бакаута-----------------------------------------------
		case "bakaut":
			dialog.text = "Oh, meu velho amigo! Trouxe um pouco de madeira de ferro para vender?";
			link.l1 = "Exatamente, Michel. Vamos negociar.";
			link.l1.go = "bakaut_0";
		break;
		
		case "bakaut_0":
			dialog.text = "Quanto você tem? Eu preciso de um lote não menor que "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+".";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "Eu sei disso. Eu já tenho "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SANDAL))+"  de madeira de ferro que você está tão ansioso para conseguir.";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Hum. Infelizmente, não tenho tanto assim.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			if (!CheckAttribute(npchar, "quest.bakaut_angry"))
			{
				dialog.text = "Droga, não te avisaram? Ou os ratos já comeram a madeira? Eu preciso "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" e nem uma peça a menos. Da próxima vez, traga tanta madeira quanto meu agente lhe pedir. Espero que não me decepcione de novo, ou terei que recusar seus serviços.";
				link.l1 = "Certo, senhor, serei mais atento da próxima vez.";
				link.l1.go = "bakaut_no_1";
			}
			else
			{
				if (sti(npchar.quest.bakaut_angry) == 1)
				{
					dialog.text = "Você está me ferrando pela segunda vez. Não gosto disso. Saiba que esta é a última advertência, da próxima vez recusarei seus serviços.";
					link.l1 = "Malditos ratos estragaram minhas mercadorias! Eu te juro, Michel, essa vai ser a última vez.";
					link.l1.go = "bakaut_no_1";
				}
				else
				{
					dialog.text = "E agora minha paciência acabou! Não quero mais fazer negócios com você. Cai fora e esqueça que eu existo.";
					link.l1 = "Mas senhor...";
					link.l1.go = "bakaut_no_2";
				}
			}
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; //снять прерывание
		break;
		
		case "bakaut_no_1":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			if (!CheckAttribute(npchar, "quest.bakaut_angry")) npchar.quest.bakaut_angry = 1;
			else npchar.quest.bakaut_angry = sti(npchar.quest.bakaut_angry)+1;
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			AddQuestRecord("Bakaut", "3");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_no_2":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			pchar.quest.Bakaut_Rozencraft_Fail.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Fail.function = "Bakaut_RozencraftDie";
			AddQuestRecord("Bakaut", "4");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_1":
			iTemp = GetSquadronGoods(pchar, GOOD_SANDAL);
			if (iTemp > sti(pchar.GenQuest.Bakaut.Value)+20)
			{ // перебор
				dialog.text = "Caramba! Me desculpe, amigo, mas só posso comprar "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+", eu não tenho dinheiro suficiente para toda a sua carga. Eu estava esperando um lote de "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" peças a quarenta dobrões cada...";
				link.l1 = "Certo. Pegue "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+" agora, e eu vou te vender o resto da próxima vez.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = sti(pchar.GenQuest.Bakaut.Value)+20;
			}
			else
			{
				dialog.text = "Muito bem. O preço é o de sempre, quarenta dobrões por cada peça.";
				link.l1 = "Por mim, tudo certo. Pegue sua parte.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = iTemp;
			}
		break;
		
		case "bakaut_2":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,10);
			dialog.text = "Foi um prazer fazer negócios com você. Volte sempre que quiser vender mais pau-ferro.";
			link.l1 = "Até logo, senhor. Nossa colaboração foi muito lucrativa para mim. Adeus!";
			link.l1.go = "bakaut_3";
		break;
		
		case "bakaut_3":
			DialogExit();
			iTemp = sti(npchar.quest.bakaut);
			TakeNItems(pchar, "gold_dublon", iTemp*40);
			RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; //снять прерывание
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			AddQuestRecord("Bakaut", "2");
			AddQuestUserData("Bakaut", "sQty", iTemp);
			AddQuestUserData("Bakaut", "sDublon", iTemp*40);
			AddQuestUserData("Bakaut", "sDublon1", iTemp*40-iTemp*30);
			CloseQuestHeader("Bakaut");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
