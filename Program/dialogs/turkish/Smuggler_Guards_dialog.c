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
			dialog.text = RandPhraseSimple("Burada yasa dışı bir şey yaptığınız anlaşılıyor.","Adına "+NationKingsName(npchar)+",   bu kanunsuzluğu derhal durdurmanızı emrediyorum!");
			Link.l1 = "Hayır, hayır, memur bey. Arkadaşlarım ve ben sadece burada güneşleniyoruz.";
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
			Link.l2 = "Hayır işi yapıyorum. Bu gerçekten yasadışı mı?";
			Link.l2.go = "GiveMeSomeMoneyToo";
			Link.l3 = "Buradan uzaklaş, asker. Bu seni ilgilendirmez!";
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
			dialog.text = "Bizi aptal yerine koyma, Kaptan "+Pchar.name+"! Kimse senin gibi pozitif ve saygın bir adamın kaçakçılık yapacağını asla beklemezdi.";
			Link.l1 = "Hiç kimse mükemmel değildir. Ama şimdiden pişmanım!";
			Link.l1.go = "ThisTimeFree_1";
			Link.l2 = "Şu anda kafanı keseceğim.";
			Link.l2.go = "ThisTimeFree_fight";				
		break;

		case "ThisTimeFree_1":	
			dialog.snd = "Voice\COGU\COGU003";	
			dialog.text = "Senin hakkında sadece iyi şeyler duydum, bu yüzden bu seferlik seni bırakıyorum, ama bir daha yapma. Ama şu adamlara aynı şeyi söyleyemem!";
			Link.l1 = "Teşekkür ederim, memur bey. İyi günler!";
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
			dialog.text = "Yalan söylemeyi bırak!!! Kör değilim ben! Bizi takip et, tutuklusun ve mallarına el konuldu.";
			Link.l1 = "Bağırsaklarını deşsem iyi olacak!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "GiveMeSomeMoneyToo":
            attrName = XI_ConvertString("Chance");
            int iRand = hrand(99, "&Bribe" + PChar.Location);
            int iMoney = PChar.Money;
            int iBaseChance = GetCharacterSkill(PChar, SKILL_SNEAK) + GetCharacterSkill(PChar, SKILL_LEADERSHIP);
			dialog.snd = "Voice\COGU\COGU005";		
			dialog.text = "Gerçekten mi? Eh, bu iş tamamen yasal... tabii ki payımızı alırsak. Peki, cömertliğiniz ne kadar?";
            if (iMoney >= 25000)
            {
                iTemp = iBaseChance > 100 ? 100 : iBaseChance;
                link.l1 = "Senin için, subayım, bende var 25000 peso! (" + attrName + " " + iTemp + "%)";
                link.l1.go = iTemp > iRand ? "MoneyAccepted10" : "TryingToGiveBribe";
            }
            if (iMoney >= 12000)
            {
                iTemp = iBaseChance / 2 + 10;
                if (iTemp > 100) iTemp = 100;
                link.l2 = "Ne dersin 12000 peso? (" + attrName + " " + iTemp + "%)";
                link.l2.go = iTemp > iRand ? "MoneyAccepted5" : "TryingToGiveBribe";
            }
            if (iMoney >= 5000)
            {
                iTemp = iBaseChance / 2 - 10;
                if (iTemp > 100) iTemp = 100;
                link.l3 = "Bence 5000 peso yeterli olacak. (" + attrName + " " + iTemp + "%)";
                link.l3.go = iTemp > iRand ? "MoneyAccepted2" : "TryingToGiveBribe";
            }
			link.l4 = StringFromKey("smuggling_3");
			link.l4.go = "ThisTimeFree_fight";
		break;

		case "TryingToGiveBribe":
			dialog.snd = "Voice\COGU\COGU006";
			dialog.text = "Rüşvet mi? Hayır, onurum benim için her şeyden önemli! Şimdi, lütfen bizimle gelir misiniz!";
			Link.l1 = "Kahretsin! Sizi hayal kırıklığına uğrattığım için üzgünüm, ama hiçbir yere gitmiyorum!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "MoneyAccepted10":
            AddMoneyToCharacter(PChar, -25000);
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Nezaketin için teşekkür ederim.";
			Link.l1 = "Her zaman hizmetinizdeyim.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -int(int(Pchar.money)/10));
		break;
		
		case "MoneyAccepted5":
            AddMoneyToCharacter(PChar, -12000);
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Nezaketin için teşekkür ederim.";
			Link.l1 = "Her zaman hizmetinizdeyim.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -int(int(Pchar.money)/5));
		break;
		
		case "MoneyAccepted2":
            AddMoneyToCharacter(PChar, -5000);
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Nezaketin için teşekkür ederim.";
			Link.l1 = "Her zaman hizmetinizdeyim.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -int(int(Pchar.money)/2));
		break;

		case "GettingLostFromHere":
			dialog.snd = "Voice\COGU\COGU008";
			dialog.text = "Ama... kahretsin! Seni tutuklamak zorundayım!";
			Link.l1 = "Ne?! Hâlâ buradasın? Hayattan bıktın mı yoksa?";
			Link.l1.go = "GettingLostFromHere_1";
		break;

		case "GettingLostFromHere_1":
			dialog.snd = "Voice\COGU\COGU009";
			dialog.text = "Ben... Ben şikayet edeceğim! Bunu öylece bırakmayacağım...";
			Link.l1 = "Hah!";
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
			dialog.text = "Allah kahretsin...! Kahrolası köpek! Bu koy senin mezarın olacak!";
			Link.l1 = "Buraya gel de kanıtlamaya çalış!";
			Link.l1.go = "ThisTimeFree_fight";
		break;
	}
}
