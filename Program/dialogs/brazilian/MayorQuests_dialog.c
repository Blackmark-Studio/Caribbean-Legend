void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		//----------------- уничтожение банды ----------------------
		case "DestroyGang_begin":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //боевке можно
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); //энкаунтеры можно 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
			dialog.text = LinkRandPhrase("Dinheiro na hora "+GetSexPhrase("companheiro","moça")+"! Meu nome é "+GetFullName(npchar)+", e eu não estou acostumado com objeções...","Agora mostre sua bolsa, "+GetSexPhrase("companheiro","moça")+", e seja rápido! Meu nome é  "+GetFullName(npchar)+", e espero que já tenha ouvido falar de mim...","Entregue tudo de valor que você tem, e também estou requisitando o conteúdo da sua bolsa. E ande logo, paciência não é meu ponto forte. Já minha sede de sangue, não posso dizer o mesmo!");
			Link.l1 = LinkRandPhrase("Hein, então você é aquele bandido famoso "+GetFullName(npchar)+", sobre quem o governador local "+sTemp+" nunca para de falar?","Ah, então você é aquele bandido que está sendo caçado pelo governador local "+sTemp+"?!","Feliz"+GetSexPhrase("","")+" te ver, "+GetFullName(npchar)+". O governador local, "+sTemp+" está falando só de você.");
			Link.l1.go = "DestroyGang_1";
		break;		
		case "DestroyGang_1":
			dialog.text = LinkRandPhrase("Sim, sou bem conhecido por essas bandas, he-he... Espera aí, você não é outro "+GetSexPhrase("cachorro imundo","vadia imunda")+" do governador que o mandou me caçar?","O governador é meu bom amigo, isso é verdade. E você, por acaso, não é "+GetSexPhrase("mais um herói, enviado","outra heroína, enviada")+" por ele pela minha cabeça?","O governador é meu grande amigo, isso não é segredo, he-he. Mas como você sabe disso? Será que foi ele que te mandou atrás de mim?");
			Link.l1 = LinkRandPhrase("Exatamente, canalha. Prepare-se para morrer!","Você é bem esperto, hein! Muito bem, hora de acabar com você. Chega de conversa.","É isso mesmo, sou eu. Saca tua arma, camarada! Vamos ver de que cor é o teu sangue.");
			Link.l1.go = "DestroyGang_ExitFight";	
			Link.l2 = LinkRandPhrase("Ah, deixa pra lá! Não preciso desse tipo de problema mesmo...","Não, não, de jeito nenhum sou um herói...","Não, não, eu jamais faria isso! Não quero confusão...");
			Link.l2.go = "DestroyGang_2";	
		break;
		case "DestroyGang_2":
			dialog.text = LinkRandPhrase("Assim está melhor, "+GetSexPhrase("companheiro","moça")+"...E agora, suma daqui!","E essa é a decisão certa. Queria que você soubesse quantos heróis já mandei para o outro mundo... Chega de conversa. Cai fora, "+GetSexPhrase("merda","vadia")+"!","Bom "+GetSexPhrase("garoto","garota")+"! Uma decisão muito sábia – não se meter nos assuntos dos outros... Certo, pode ir embora, "+GetSexPhrase("companheiro","moça")+".");
			Link.l1 = "Adeus, e boa sorte para você...";
			Link.l1.go = "DestroyGang_ExitAfraid";	
		break;

		case "DestroyGang_ExitAfraid":
			pchar.GenQuest.DestroyGang = "Found"; //флаг нашёл, но струсил
			npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
			pchar.money = 0;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar)-1, false, "DestroyGang_SuddenAttack");
			for(i = 1; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;	
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
				LAi_SetImmortal(sld, true);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DestroyGang_SuddenAttack");
			}
			DialogExit();
		break;

		case "DestroyGang_ExitFight":
			for(i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// ОЗГ - пассажир
		case "ContraPass_abordage":
			dialog.text = "Arghh, seu canalha! Como ousa atacar meu navio?! Você vai pagar por isso!";
			link.l1 = "Pelo contrário, estou sendo pago por isso. Você tem um certo homem a bordo, chamado "+pchar.GenQuest.TakePassenger.Name+". Ele é quem eu preciso.";
			link.l1.go = "ContraPass_abordage_1";
		break;
		
		case "ContraPass_abordage_1":
			dialog.text = "Eu sabia que esse canalha ia trazer problemas pra gente... Mas você não vai me pegar tão fácil assim! Defenda-se, pirata imundo!";
			link.l1 = "É você quem precisa pensar em se defender, seu cachorro.";
			link.l1.go = "ContraPass_abordage_2";
		break;
		
		case "ContraPass_abordage_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "ContraPass_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Tempsailor":
			dialog.text = "Capitão, revistamos as cabines e o porão, como o senhor mandou. Aquele canalha tentou se esconder, mas nós o encontramos.";
			link.l1 = "Excelente! Onde ele está agora?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Ele está no porão, como você nos mandou.";
			link.l1 = "Excelente! Agora vamos sair deste velho barco. Está na hora de voltar.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Já vou, capitão!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			sld = GetCharacter(NPC_GenerateCharacter("ContraPass", "citiz_"+(rand(9)+11), "man", "man", 10, sti(pchar.GenQuest.TakePassenger.Nation), -1, true, "quest"));
			sld.name = pchar.GenQuest.TakePassenger.Name;
			sld.lastname = "";
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.TakePassenger.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
		break;
		
		case "Fugitive_city": // ходит по городу
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "O que deseja, senhor?";
			link.l1 = "Ora, ora... Então você é "+pchar.GenQuest.FindFugitive.Name+", não é? Fico muito feliz em ver você...";
			link.l1.go = "Fugitive_city_1";
		break;
		
		case "Fugitive_city_1":
			dialog.text = "Bem, sou eu mesmo, de fato, mas por que você está feliz em me ver? Acho estranho, já que nunca te vi antes... Quer se explicar?";
			link.l1 = "Mas é claro. Eu vim de "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity+"Gen")+", por ordem do governador local. Você está preso e devo levá-lo para essa mesma cidade... Ah, e mantenha as mãos longe do seu sabre! Não tente nada tolo, meu bom homem, ou as coisas vão acabar mal para você!";
			link.l1.go = "Fugitive_city_2";
		break;
		
		case "Fugitive_city_2":
			dialog.text = "Então, você me encontrou afinal... Senhor, me escute e talvez mude de ideia. Sim, eu desertei da guarnição. Mas eu não podia assistir à degradação do nosso exército!\nEu queria uma vida tranquila, e encontrei isso aqui, nesta vila... Me deixe em paz, diga a eles que não conseguiu me encontrar ou que fugi com piratas para o mar aberto. Em troca, lhe dou esta bolsa de âmbar. É um item muito valioso, devo dizer...";
			link.l1 = "Nem pense em me subornar, senhor! Entregue sua arma e venha comigo!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Hmm... Degradação? Uma vida tranquila e pacífica? Tudo bem, acho que posso realizar seu desejo. Onde está seu âmbar?";
			link.l2.go = "Fugitive_city_gift";
		break;
		
		case "Fugitive_city_fight":
			dialog.text = "Então saque sua lâmina, mercenário! Você não vai me derrotar tão fácil!";
			link.l1 = "Certo, vamos ver do que você é capaz!";
			link.l1.go = "Fugitive_fight_1";
		break;
		
		case "Fugitive_city_gift":
			TakeNItems(pchar, "jewelry8", 50+hrand(25));
			TakeNItems(pchar, "jewelry7", 2+hrand(5));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received amber");
			dialog.text = "Aqui... E espero sinceramente nunca mais ver você ou qualquer outro 'enviado' novamente.";
			link.l1 = "Eu lhe garanto que não vai. Adeus, senhor!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_gift_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.FindFugitive = "Found"; //флаг провалил
			AddQuestRecord("MayorsQuestsList", "12-4");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity));
		break;
		
		case "Fugitive_fight_1":// в городе и бухте
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Fugitive_afterfight":
			dialog.text = "Maldição! Você venceu, desgraçado! Eu me rendo...";
			link.l1 = "Cuidado com o que diz, senhor! Agora, entregue-me seu sabre, por favor... Siga-me, e nada de truques idiotas!";
			link.l1.go = "Fugitive_afterfight_1";
		break;
		
		case "Fugitive_afterfight_1":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			//DeleteAttribute(npchar, "LifeDay");
			npchar.lifeday = 0;
			LAi_SetImmortal(npchar, true);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.FindFugitive.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			pchar.GenQuest.FindFugitive = "Execute"; //флаг выполнил успешно
			pchar.quest.FindFugitive1.win_condition.l1 = "location";
			pchar.quest.FindFugitive1.win_condition.l1.location = pchar.GenQuest.FindFugitive.Startcity+"_townhall";
			pchar.quest.FindFugitive1.function = "FindFugitive_inResidence";
			SetFunctionTimerCondition("FindFugitive_Over", 0, 0, 30, false);
		break;
		
		case "Fugitive_shore": // в бухте
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Senhor, não estou com vontade de conversar com você, então...";
			link.l1 = "No entanto, você vai ter que falar comigo. Você é "+pchar.GenQuest.FindFugitive.Name+", não é? Acho que você não deveria negar isso.";
			link.l1.go = "Fugitive_shore_1";
		break;
		
		case "Fugitive_shore_1":
			dialog.text = "E eu não vou negar, sou eu mesmo. Mas o que você quer?";
			link.l1 = "Preciso te levar para "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+", o governador local está ansioso para vê-lo. Sem gracinhas, por favor! Entregue sua arma e me acompanhe!";
			link.l1.go = "Fugitive_shore_2";
		break;
		
		case "Fugitive_shore_2":
			dialog.text = "Entendo... Senhor, antes que faça algo precipitado, deixe-me lhe contar uma coisa. Sim, eu desertei da guarnição. Mas tive meus motivos. Não consigo mais servir, é mais do que posso suportar! Você me entende? Eu não posso!\nQuero uma vida tranquila, e encontrei isso aqui, nesta vila... Me deixe em paz, diga a eles que não conseguiu me encontrar ou que fugi com piratas para o mar aberto. Em troca, lhe dou minha coleta semanal de pérolas. É tudo o que tenho.";
			link.l1 = "Nem pense em me subornar, senhor! Entregue sua arma e venha comigo!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Hmm... Está cansado do serviço militar? Quer uma vida tranquila? Tudo bem, acho que posso realizar seu desejo. Onde estão suas pérolas?";
			link.l2.go = "Fugitive_shore_gift";
		break;
		
		case "Fugitive_shore_gift":
			TakeNItems(pchar, "jewelry52", 100+hrand(40));
			TakeNItems(pchar, "jewelry53", 400+hrand(100));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received pearls");
			dialog.text = "Aqui... E espero sinceramente nunca mais ver você ou outros 'emissários' por aqui.";
			link.l1 = "Eu lhe garanto, você não vai. Adeus, senhor!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern": // в таверне
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Ehhh... hic! Senhor, não estou procurando companhia – especialmente a sua. Cai fora!";
			link.l1 = "Mas EU estou procurando a sua companhia, "+pchar.GenQuest.FindFugitive.Name+"! E você vai aguentar minha companhia no porão do meu navio. Nós vamos  "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+", para o governador da cidade. Ele está quase morrendo de vontade de te ver.";
			link.l1.go = "Fugitive_tavern_1";
		break;
		
		case "Fugitive_tavern_1":
			dialog.text = "H- Hic!"+RandSwear()+" Então ele me encontrou, afinal! Escuta, amigo, você não sabe o que aconteceu, você não estava lá! Eu não podia continuar no serviço, simplesmente não dava! Até hoje eu bebo toda noite pra tentar esquecer.\nOlha, vamos fazer um acordo. Diz pra ele que não conseguiu me achar, ou que eu fugi com piratas pro mar aberto. Em troca, te dou todas as pepitas que achei na caverna daqui. É tudo que eu tenho, entendeu? Estou te dando tudo, só pra nunca mais ter que ver "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+"...";
			link.l1 = "Nem pense em me subornar, senhor! Entregue sua arma e venha comigo!";
			link.l1.go = "Fugitive_tavern_fight";
			link.l2 = "Hmm... Uma história desagradável? Você está sendo atormentado por pesadelos ou pela consciência pesada? Tudo bem, acho que posso deixar você lidar com isso sozinho. Onde estão seus trocados?";
			link.l2.go = "Fugitive_tavern_gift";
		break;
		
		case "Fugitive_tavern_gift":
			TakeNItems(pchar, "jewelry5", 50+hrand(30));
			TakeNItems(pchar, "jewelry6", 100+hrand(50));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received nuggets");
			dialog.text = "Aqui... E espero mesmo nunca mais ver você ou qualquer outro 'emissário' de novo.";
			link.l1 = "Eu lhe garanto que não vai. Adeus, senhor!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern_fight":
			dialog.text = "Então desembainhe sua lâmina, mercenário! Você não vai me pegar tão fácil assim!";
			link.l1 = "Certo, vamos ver do que você é capaz!";
			link.l1.go = "Fugitive_fight_2";
		break;
		
		case "Fugitive_fight_2":// в таверне
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetImmortal(npchar, false);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
