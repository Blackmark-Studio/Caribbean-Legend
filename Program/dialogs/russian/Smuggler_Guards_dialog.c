void ProcessDialogEvent() 
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
    int iTemp, i; // нужно для вычислений любых целых (нации)
	string attrName; // любые строки для вычислений
	ref sld;

    switch(Dialog.CurrentNode)
	{
		case "exit":
			StopCoastalGuardPursuit();
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			LAi_SetPlayerType(Pchar);
		break;

		case "First time":			
			chrDisableReloadToLocation = false;
   			LAi_LockFightMode(pchar, false);
			// Captain Beltrop, 14.02.2021 - правка проверки репутации и навыков владения оружием
			bool FencingSkills = (GetCharacterSkillToOld(Pchar, "FencingL") >= 8) || (GetCharacterSkillToOld(Pchar, "FencingS") >= 8) || (GetCharacterSkillToOld(Pchar, "FencingH") >= 8);
			dialog.text = RandPhraseSimple("Кажется, здесь происходит что-то незаконное.",
                                     "Именем "+NationKingsName(npchar)+ ", прекратить творить беззаконие!!!");
			Link.l1 = "Нет-нет, офицер. Мы с друзьями просто отдыхаем у моря.";
			// belamour legendary edition включим обаяние ГГ, если оно есть
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Link.l1.go = "ThisTimeFree";
			}
			else
			{
				if (int(pchar.reputation.nobility) >= 70 && GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) >= 5)
				{
					Link.l1.go = "ThisTimeFree";
				}
				else
				{
                    Link.l1.go = "IDontBelieveYou";
                }
			}
			Link.l2 = "Я раздаю деньги. Это можно считать незаконным занятием?";
			Link.l2.go = "GiveMeSomeMoneyToo";
			Link.l3 = "Проваливай, солдафон. Это тебя не касается!";
			if(int(pchar.reputation.nobility) <= 25 && FencingSkills)
			{
				Link.l3.go = "GettingLostFromHere";
			}
			else
			{
				Link.l3.go = "howDareYou";
			}
		break;

		case "ThisTimeFree":
			dialog.snd = "Voice\COGU\COGU002";		
			dialog.text = "Не морочьте нам голову, капитан " + Pchar.name + "! И кто мог подумать, что такой положительный и уважаемый всеми человек, как вы, займётся контрабандой!";
			Link.l1 = "Увы, все совершают ошибки. Но я уже раскаиваюсь!";
			Link.l1.go = "ThisTimeFree_1";
			Link.l2 = "Сейчас я отрежу тебе голову!";
			Link.l2.go = "ThisTimeFree_fight";				
		break;

		case "ThisTimeFree_1":	
			dialog.snd = "Voice\COGU\COGU003";	
			dialog.text = "Поскольку я слышал о вас только хорошее, в этот раз я отпускаю вас. А этих мерзавцев мы прихватим!";
			Link.l1 = "Благодарю вас, офицер. Всего вам хорошего!";
			Link.l1.go = "ThisTimeFree_exit";
		break;

		case "ThisTimeFree_fight":	
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться 130313
			ChangeCharacterNationReputation(pchar, int(NPChar.Nation), -1);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			for (i = 1; i <= int(Pchar.quest.contraband.SoldierQty); i++)
			{
    			attrName = "SoldierIDX"+i;
				sld = GetCharacter(int(Pchar.quest.contraband.(attrName)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetRelation(pchar.GenQuest.Smugglers_Group, "CoastalGuards", LAI_GROUP_ENEMY);
			LAi_group_SetHearRadius("CoastalGuards", 100.0);
			LAi_group_SetHearRadius(pchar.GenQuest.Smugglers_Group, 100.0);
			LAi_group_FightGroups("CoastalGuards", pchar.GenQuest.Smugglers_Group, true);
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
            LAi_SetFightMode(Pchar, true);
		break;

		case "ThisTimeFree_exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			
            DialogExit();
			StopCoastalGuardPursuit();
			ChangeContrabandRelation(pchar, -30);
			for (i = 1; i <= int(Pchar.quest.contraband.SoldierQty); i++)
			{
    			attrName = "SoldierIDX"+i;
				sld = GetCharacter(int(Pchar.quest.contraband.(attrName)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			LAi_group_SetRelation(pchar.GenQuest.Smugglers_Group, "CoastalGuards", LAI_GROUP_ENEMY);			
			LAi_group_FightGroups(pchar.GenQuest.Smugglers_Group, "CoastalGuards", true);
			LAi_SetPlayerType(Pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться 130313
		break;

		case "IDontBelieveYou":
			dialog.snd = "Voice\COGU\COGU004";
			dialog.text = "Что вы мне рассказываете! Я не слепой! Следуйте за нами - вы арестованы, а товар конфискован!";
			Link.l1 = "Скорее, я выпущу вам кишки!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "GiveMeSomeMoneyToo":
            attrName = XI_ConvertString("Chance");
            int iRand = hrand(99, "&Bribe" + PChar.Location);
            int iMoney = PChar.Money;
            int iBaseChance = GetCharacterSkill(PChar, SKILL_SNEAK) + GetCharacterSkill(PChar, SKILL_LEADERSHIP);
			dialog.snd = "Voice\COGU\COGU005";		
			dialog.text = "Вот как? Нет, конечно, это занятие совершенно правомочно... Если нам, конечно, тоже достанется. А по сколько вы раздаете?";
            if (iMoney >= 25000)
            {
                iTemp = iBaseChance > 100 ? 100 : iBaseChance;
                link.l1 = "Вам, офицер, я готов отдать 25000 песо! (" + attrName + " " + iTemp + "%)";
                link.l1.go = iTemp > iRand ? "MoneyAccepted10" : "TryingToGiveBribe";
            }
            if (iMoney >= 12000)
            {
                iTemp = iBaseChance / 2 + 10;
                if (iTemp > 100) iTemp = 100;
                link.l2 = "Как насчёт 12000 песо? (" + attrName + " " + iTemp + "%)";
                link.l2.go = iTemp > iRand ? "MoneyAccepted5" : "TryingToGiveBribe";
            }
            if (iMoney >= 5000)
            {
                iTemp = iBaseChance / 2 - 10;
                if (iTemp > 100) iTemp = 100;
                link.l3 = "Думаю, 5000 песо будет достаточно. (" + attrName + " " + iTemp + "%)";
                link.l3.go = iTemp > iRand ? "MoneyAccepted2" : "TryingToGiveBribe";
            }
			link.l4 = StringFromKey("smuggling_3");
			link.l4.go = "ThisTimeFree_fight";
		break;

		case "TryingToGiveBribe":
			dialog.snd = "Voice\COGU\COGU006";
			dialog.text = "Ага, предлагаете взятку? Нет уж, мне честь мундира дороже! Извольте следовать за нами!";
			Link.l1 = "Проклятье! Жаль вас разочаровывать, но вряд ли вы куда-либо сейчас пойдёте!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "MoneyAccepted10":
            AddMoneyToCharacter(PChar, -25000);
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "С радостью приму ваше пожертвование. Раз уж вы занимаетесь благотворительностью.";
			Link.l1 = "Всегда к вашим услугам.";
			Link.l1.go = "GettingLostFromHere_exit";
		break;

		case "MoneyAccepted5":
            AddMoneyToCharacter(PChar, -12000);
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "С радостью приму ваше пожертвование. Раз уж вы занимаетесь благотворительностью.";
			Link.l1 = "Всегда к вашим услугам.";
			Link.l1.go = "GettingLostFromHere_exit";
		break;

		case "MoneyAccepted2":
            AddMoneyToCharacter(PChar, -5000);
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "С радостью приму ваше пожертвование. Раз уж вы занимаетесь благотворительностью.";
			Link.l1 = "Всегда к вашим услугам.";
			Link.l1.go = "GettingLostFromHere_exit";
		break;

		case "GettingLostFromHere":
			dialog.snd = "Voice\COGU\COGU008";
			dialog.text = "Но... Дьявол... Я же должен вас арестовать!";
			Link.l1 = "Арргх! Ты ещё здесь? Жить надоело?";
			Link.l1.go = "GettingLostFromHere_1";
		break;

		case "GettingLostFromHere_1":
			dialog.snd = "Voice\COGU\COGU009";
			dialog.text = "Я... Я буду жаловаться! Я этого так не оставлю...";
			Link.l1 = "Пфф!";
			Link.l1.go = "GettingLostFromHere_exit";
		break;

		case "GettingLostFromHere_exit":
			ChangeContrabandRelation(pchar, 10);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
            DialogExit();
            
			StopCoastalGuardPursuit();
			for (i = 1; i <= int(Pchar.quest.contraband.SoldierQty); i++)
			{
                attrName = "SoldierIDX"+i;
                LAi_SetActorType(&Characters[int(Pchar.quest.contraband.(attrName))]);
                LAi_ActorRunToLocation(&Characters[int(Pchar.quest.contraband.(attrName))], "reload", "Reload1", "none", "", "", "", 40);
			}
			LAi_SetPlayerType(Pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться 130313
		break;

		case "howDareYou":
			dialog.snd = "Voice\COGU\COGU010";
			dialog.text = "Ах ты, собака! Теперь тебе точно не отвертеться. Ты на этом берегу сдохнешь!";
			Link.l1 = "Попробуй воплотить слова в жизнь, пустозвон!";
			Link.l1.go = "ThisTimeFree_fight";
		break;
	}
}
