// Бесчестный конкурент
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Isto é um bug. Avise os desenvolvedores";
			link.l1 = "Claro!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShadowGuarder":
			dialog.text = "O que você precisa?";
			link.l1 = "Você é "+pchar.questTemp.Shadowtrader.Guardername+"? O comerciante local me enviou. Ele está aguardando ansiosamente a sua presença neste exato momento.";
			link.l1.go = "ShadowGuarder_1";
			DelLandQuestMark(npchar);
		break;
	
		case "ShadowGuarder_1":
			dialog.text = "A-ah, mas eu estava esperando por ele aqui! Disseram que ele viria à taverna! Desculpe, já estou indo.";
			link.l1 = "Muito bem!";
			link.l1.go = "ShadowGuarder_2";
		break;
	
		case "ShadowGuarder_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("ShadowGuarder");	
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", pchar.questTemp.Shadowtrader.City +"_store", "goto", "goto2", "OpenTheDoors", 6);
			pchar.questTemp.Shadowtrader = "begin";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowAgent":
			dialog.text = "Boa noite, capitão. Procurando umas mercadorias baratas, hein? Me siga!";
			link.l1 = "Mostre o caminho.";
			link.l1.go = "ShadowAgent_1";
		break;
	
		case "ShadowAgent_1":
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS4", "CommonFlamHouse", "barmen", "stay", "Shadow_inRoom", 40);
		break;
	
		case "ShadowTrader":
			dialog.text = "Boa noite, senhor. É um prazer conhecer um novo cliente, ha! Permita-me apresentar: eu sou "+GetFullName(npchar)+". Eu tenho as mercadorias mais baratas desta cidade, pode acreditar.";
			link.l1 = "Finalmente, nos encontramos..."+npchar.name+". Suponho que vou te decepcionar: não vim aqui para negociar, mas para acabar com essa sua sujeira. Você tem sido uma grande dor de cabeça para um homem importante. A dor ficou tão insuportável que ele está decidido a te calar... custe o que custar.";
			link.l1.go = "ShadowTrader_1";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "Pare aí mesmo, seu criminoso! Você não sabia que precisa pagar impostos para ter um negócio? Ninguém quebra a lei enquanto eu estiver de olho! "+GetFullName(npchar)+", você quebrou a lei e seus bens roubados agora estão confiscados! Há soldados armados bem atrás de mim, do lado de fora da porta, então nem pense em bancar o inocente!";
				link.l2.go = "ShadowTrader_2";
			}
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowTrader_1":
			dialog.text = "Sério? Eu não esperava por isso... Quem diabos é você?! Isso é uma armadilha! Acho que já sei quem está por trás disso! Não importa como... rapazes, matem ele!";
			link.l1 = "Vamos dançar, canalha!";
			link.l1.go = "ShadowTrader_fight";
			NextDiag.currentnode = "ShadowTrader_6";
		break;
	
	case "ShadowTrader_2":
		dialog.text = "Meu Deus... oficial, escute! Vamos fazer um acordo. O senhor é um homem sábio e misericordioso! Eu lhe pago 5.000 peças de oito e você deixa a gente fugir pelo segundo andar. Você também fica com as mercadorias, precisa delas, não é? Pra que precisaria de mim? Eu vou sair da cidade agora mesmo e ninguém mais vai nos ver. E o seu dinheiro está garantido. O que me diz, oficial?";
		link.l1 = "Você realmente acha, verme, que eu desonraria meu dever por uma quantia tão miserável?";
		link.l1.go = "ShadowTrader_3";
		break;
	
	case "ShadowTrader_3":
		dialog.text = "Tá bom, tá bom, senhor oficial, leve tudo que eu tenho – 10.000 pesos. É tudo que eu tenho, eu juro!";
		link.l1 = "Hm... Se eu te prender, todo o seu dinheiro será confiscado... Muito bem! Este posto de contrabando está fechado e toda a mercadoria foi apreendida... Me dê as moedas e suma daqui. Não apareça mais por aqui!";
		link.l1.go = "ShadowTrader_4";
		break;
		
	case "ShadowTrader_4":
			dialog.text = "Muito obrigado, muito obrigado, muito obrigado, oficial! Aqui está o seu dinheiro, e você não vai me ver aqui de novo. Vamos embora!";
			link.l1 = "Saia daqui ou vou ter que te prender!";
			link.l1.go = "ShadowTrader_escape";
		break;
	
		case "ShadowTrader_fight":
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				sld.nation = PIRATE;
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "ShadowTrader_afterfight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	
		case "ShadowTrader_escape"://напугали
			AddMoneyToCharacter(pchar, 10000);
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			}
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 9.0);
			pchar.questTemp.Shadowtrader.End.Escape = "true";
			AddQuestRecord("Shadowtrader", "8");
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 250);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
	
		case "ShadowTrader_6":
			dialog.text = "Ah! Misericórdia, não me mate! Eu te dou tudo o que tenho!";
			link.l1 = "Todas as suas mercadorias serão confiscadas pelas autoridades. Você realmente acha que eu teria piedade de você depois do que acabou de acontecer aqui?";
			link.l1.go = "ShadowTrader_7";
		break;
	
		case "ShadowTrader_7":
			dialog.text = "Eu... eu te dou todo o meu dinheiro e meus pertences! Só me deixa ir! Vou embora da ilha hoje mesmo e você nunca mais vai me ver por aqui!";
			link.l1 = "Muito bem. Me dê tudo o que você tem com você e suma daqui. E nunca mais tente fazer negócios por aqui – da próxima vez, não vou poupar essa sua vidinha miserável, seu bandido.";
			link.l1.go = "ShadowTrader_free";
			link.l2 = "De jeito nenhum, canalha, você não vai me comprar. A única maneira de lidar com gente como você é com aço frio e chumbo quente!";
			link.l2.go = "ShadowTrader_killed";
		break;
		
		case "ShadowTrader_free"://отпустили
			AddMoneyToCharacter(pchar, 20550);
			TakeNItems(pchar, "jewelry1", rand(5));
			TakeNItems(pchar, "jewelry2", rand(20));
			TakeNItems(pchar, "jewelry5", rand(20));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received items");
			LAi_SetPlayerType(pchar);
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 7.0);
			pchar.questTemp.Shadowtrader.End.Free = "true";
			AddQuestRecord("Shadowtrader", "9");
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddComplexSelfExpToScill(70, 70, 70, 70);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
	
		case "ShadowTrader_killed":
			DialogExit();
			AddDialogExitQuestFunction("ShadowTrader_KillToTrader_kino");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
