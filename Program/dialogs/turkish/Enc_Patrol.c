void ProcessDialogEvent()
{
	ref NPChar, sld;
	ref arItem;
	aref Link, Diag;
	int i, iShipType, iShipGoods;
	int jewelType;
	string sItemName = "";
	string sItem;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Patrol" + locations[FindLocation(npchar.location)].index + "_";
	string sGroup = "PatrolGroup_" + locations[FindLocation(npchar.location)].index;
	string sTemp1, sTemp2;

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_fight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);				
			}
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			if (pchar.nation == npchar.nation)
				{
					dialog.text = RandPhraseSimple("Bak hele, bu alçak burada alarmı kaldırmış gibi görünüyor "+XI_ConvertString("Colony"+npchar.city+"Dat")+"! Yakalayın h"+GetSexPhrase("im","er")+"!!","Heh, şuna bak! Birkaç "+NationNamePeople(sti(pchar.nation))+"   düşman olmayı başarırsın   "+NationNameAblative(sti(npchar.nation))+" Alçağı yakalayın!!!");
				}
				else
				{
					dialog.text = RandPhraseSimple("Yakınlarda düşman ajanı var "+XI_ConvertString("Colony"+npchar.city+"Gen")+"! Yakala h"+GetSexPhrase("im","er")+"!!","Hey, bak, "+NationNamePeople(sti(pchar.nation))+" neredeyse ortalıkta dolaşıyorlar "+XI_ConvertString("Colony"+npchar.city+"Dat")+"   Onu hemen yakalayın!!!");
				}
				link.l1 = RandPhraseSimple("Pekâlâ, deneyebilirsin. Burada yalnızız...","Heh, burada kimse sana yardım eli uzatmaz.");
				link.l1.go = "exit_fight"; 				
			}
			else
			{				
				// belamour legendary edition
				sTemp1 = "";
				if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation)) sTemp1 = "Vice Admiral! ";
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE) sTemp1 = "Your Excellency Governor General! ";
				
				dialog.text = LinkRandPhrase("İzin verin kendimi tanıtayım! Ben   bir devriye subayıyım,   "+XI_ConvertString("Colony"+npchar.city+"Gen")+", kaçak bir mahkûmu arıyoruz.","Merhaba, ben bu devriyenin başıyım. Kaçmış bir köleyi arıyoruz "+XI_ConvertString("Colony"+npchar.city+"Gen")+".","Selamlar sana, "+GetAddress_Form(NPChar)+". Birliğim   bölgedeki   topraklarda devriye geziyor "+XI_ConvertString("Colony"+npchar.city+"Gen")+".");
				Link.l1 = LinkRandPhrase("Çok iyi. Size nasıl yardımcı olabilirim?","Çok iyi. Size başka bir konuda yardımcı olabilir miyim, "+GetAddress_FormToNPC(NPChar)+"?","Çok iyi. Sizin için yapabileceğim bir şey var mı?");
				Link.l1.go = "Node_2";
			}
		break;
		
		case "Node_2":
			dialog.text = RandPhraseSimple("Mahallede şüpheli bir şey gördünüz mü?","Şüpheli davranan birini gördün mü, "+GetAddress_Form(NPChar)+"?");
			Link.l1 = RandPhraseSimple("Hayır, öyle bir şey yok.","Hayır, memur bey, her şey sakin görünüyordu.");
			Link.l1.go = "Node_3";		
		break;

		case "Node_3":
			Diag.TempNode = "GoodBye";
			dialog.text = RandPhraseSimple("Pekala, o zaman sizi daha fazla oyalamayayım. Hoşça kalın, "+GetAddress_Form(NPChar)+".","Anladım. O zaman hoşça kal.");
			Link.l1 = "İyi şanslar.";
			Link.l1.go = "exit_noFight";
		break;

		case "GoodBye":
			Diag.TempNode = "GoodBye";
			dialog.text = LinkRandPhrase("Bizi görevimizden alıkoyma.","Bizi yalnız bırakmanızı istiyorum!","Ah, yine sen... Kendi yoluna git ve bizi rahatsız etme.");
			Link.l1 = "Pekâlâ.";
			Link.l1.go = "Exit";			
		break;
		
		// генератор "A reason to hurry"
		case "Reason_To_Fast_1":
				if(Pchar.Location == Pchar.location.from_sea)
				{
					dialog.text = "Hmm... Seni daha önce görmedim. Kimsin sen?";
					link.l1 = "Beklediğin kişi benim...";
					link.l1.go = "Reason_To_Fast_11";
					link.l2 = "Ben kaptanım "+GetFullName(pchar)+". Neden bu kadar acele ettiğini ve genelevde neredeyse pantolonunu unutacak kadar telaşlı olduğunu öğrenmek isterim...";
					link.l2.go = "Reason_To_Fast_21";
					link.l3 = "Ben kaptanım "+GetFullName(pchar)+". Burada sadece dolaşıyorum, tuzlu deniz havasını içime çekiyorum...";
					link.l3.go = "Reason_To_Fast_31";
				}
				else
				{
					Diag.TempNode = "GoodBye";
					dialog.text = "Sonunda geldin. Seni bir daha hiç göremeyeceğim sanmıştım. Peki, yanındaki adam kim?";
					link.l1 = "Ne tür?";
					link.l1.go = "Reason_To_Fast_Hunter";
				} 
		break;
		
		case "Reason_To_Fast_Hunter":
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_MeetHunter");
		break;
		
		case "Reason_To_Fast_11":
			dialog.text = "Sana güvenebileceğim biri gibi pek görünmüyorsun "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+".";
			if(!CheckCharacterItem(pchar,"mapQuest"))
			{
				link.l1 = "Pekala, söylediklerinin hepsini ona anlatacağım.";
				link.l1.go = "Reason_To_Fast_12";
			}	
			link.l2 = "Ve bu da kim "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+"?";
			link.l2.go = "Reason_To_Fast_13";
		break;
		
		case "Reason_To_Fast_21":
			dialog.text = "Merak, kedilerden çok daha fazla insanın sonunu getirmiştir...";
			link.l1 = "Vay canına!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_31":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "The tide is coming in. You'd better leave the cove; the water here rises to the level of the palm tree.";
			link.l1 = " Sorun değil, iyi bir yüzücüyüm. ";
			link.l1.go = "Reason_To_Fast_GoodBye_0";
			pchar.questTemp.ReasonToFast = "MeetPatrolFail";
		break;
		
		case "Reason_To_Fast_12":
			jewelType = sti(pchar.questTemp.ReasonToFast.p4);
			pchar.questTemp.ReasonToFast.item = "jewelry" + jewelType;
			sItem = "jewelry" + jewelType;
			switch (jewelType)
			{
				case 1:
					sItemName = "amethysts";
				break;
				case 2:
					sItemName = "diamonds";
				break;
				case 3:
					sItemName = "rubies";
				break;
				case 4:
					sItemName = "emeralds";
				break;
			}
			pchar.questTemp.ReasonToFast.jewType = sItemName;
			dialog.text = "Pekala, pekala. Sana 30 söz verildi "+sItemName+" seninle mi?";
			link.l1 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+"   Bu kadar çok mücevheri toplamak için yeterli zaman olmadığını söyledi. Bunun yerine para teklif etmemi emretti.";
			link.l1.go = "Reason_To_Fast_14";
			if (GetCharacterItem(pchar, pchar.questTemp.ReasonToFast.item) >= 30)
			{
				link.l2 = "Buyurun.";
				link.l2.go = "Reason_To_Fast_15";
			}			
		break;
		
		case "Reason_To_Fast_13":
			dialog.text = "Heh! Bunu cehennemde öğrenirsin!";
			link.l1 = "Ne özgüven ...";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_14":
			dialog.text = "Pekâlâ, o zaman bana borçlusun "+sti(pchar.questTemp.ReasonToFast.p5)+" peso, anlaştığımız gibi.";
			link.l1 = "Bu biraz fazla değil mi?";
			link.l1.go = "Reason_To_Fast_16";
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				link.l2 = "Buyurun.";
				link.l2.go = "Reason_To_Fast_17";
			}	
			link.l3 = "Ama yanımda o kadar param yok!";
			link.l3.go = "Reason_To_Fast_18";	
			AddQuestRecord("ReasonToFast", "9");
			AddQuestUserData("ReasonToFast", "sText", pchar.questTemp.ReasonToFast.jewType);
		break;
		
		case "Reason_To_Fast_15":
			TakeNItems(pchar, pchar.questTemp.ReasonToFast.item, -30); 
			dialog.text = "Her şey anlaşmaya uygun. Buyurun. Bu harita, hakkında konuşulan asılan korsandan alındı, "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" sormuştum.";
			link.l1 = "Anlaşma tamam!";
			link.l1.go = "Reason_To_Fast_15_1";
		break;
		
		case "Reason_To_Fast_15_1":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			DialogExit();
			AddQuestRecord("ReasonToFast", "10");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			pchar.questTemp.ReasonToFast = "PatrolSuccess_2";
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);	
			DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером 
			AddDialogExitQuest("pchar_back_to_player");	
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
		break;
		
		case "Reason_To_Fast_16":
			dialog.text = "Tutarı hallettik "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_ABL)+" önceden. Hiç hoşuma gitmiyor. Onu öldür "+GetSexPhrase("im","er")+", çocuklar!";
			link.l1 = "Pekâlâ, deneyebilirsin!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_17":
			pchar.questTemp.ReasonToFast = "PatrolSuccess_1";
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p5)));
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.chain")) DeleteAttribute(pchar,"questTemp.ReasonToFast.chain");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.ShipName");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipTypeName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.TypeName");
			switch (sti(pchar.questTemp.ReasonToFast.target))
			{
				case 0: // корабль с товаром
					sTemp1 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					iShipType = ReasonToFast_GetVictimShipType();
					iShipGoods = ReasonToFast_GetVictimShipGoods();
					dialog.text = "Mükemmel! Şimdi işe koyulalım. Şunu ele geçirdik ki "+GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipTypeName)+" '"+sTemp1+"'  bir yükle birlikte "+GetGoodsNameAlt(iShipGoods)+", mürettebat zaten gözaltında, ve 'yük' hâlâ gemide. Mürettebat, limandaki serserilerden tutuldu, ve limana ancak yarın varacaklar. Onlarla nasıl istersen öyle ilgilenebilirsin.";
					link.l1 = "Pekala. Mesajınızı ileteceğim "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+".";
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A0";
					pchar.questTemp.ReasonToFast.ShipName = sTemp1;										
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером
					AddQuestRecord("ReasonToFast", "11");
					AddQuestUserData("ReasonToFast", "sShipType", pchar.questTemp.ReasonToFast.ShipTypeName);					
					AddQuestUserData("ReasonToFast", "sShipName", sTemp1);
					AddQuestUserData("ReasonToFast", "sGoodsName", GetGoodsNameAlt(iShipGoods));
					ReasonToFast_GenerateVictimShip(iShipType, iShipGoods);					
				break;

				case 1: // сокровища губернатора
					switch(rand(3))
					{
						case 0:
							sTemp1 = "The governor's daughter dowry is";
						break;
						case 1:
							sTemp1 = "Governor's gifts for the Viceroy are";
						break;
						case 2:
							sTemp1 = "The presents for governor's jubilee are";
						break;
						case 3:
							sTemp1 = "Governors 'pensionary' money is";
						break;
					}
					switch(rand(3))
					{
						case 0:
							sTemp2 = "Cheat";
						break;
						case 1:
							sTemp2 = "Mischief";
						break;
						case 2:
							sTemp2 = "Prank";
						break;
						case 3:
							sTemp2 = "Naughty";
						break;
					}
					pchar.questTemp.ReasonToFast.password = sTemp2;
					sTemp2 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					dialog.text = "Mükemmel! "+sTemp1+" odasında saklanıyor. Kurye gemisi her an gelebilir, ama yine de yetişmelisin. Uşak 'bizim' adamımız. Parola: '"+pchar.questTemp.ReasonToFast.password+"', reply: '"+sTemp2+"'.";
					link.l1 = "Pekala. Mesajınızı ileteceğim "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+".";
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A1";
					AddQuestRecord("ReasonToFast", "12");
					pchar.questTemp.ReasonToFast.ShipName = sTemp2;
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером
					
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1 = "Timer";
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.function = "ReasonToFast_ClearLakey";
				break;				
			}
		break;
		
		case "Reason_To_Fast_18":
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				dialog.text = "Beni kandırmaya mı çalışıyorsun?! Seni köpek!";
				link.l1 = "Kes sesini, yeter artık!";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
			else
			{
				dialog.text = "Paralarımı içkiye harcadın! Benim! Paramı!... Kahretsin.";
				link.l1 = "Kahretsin!";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
		break;

		case "Reason_To_Fast_GoodBye_0":
			LAi_SetPlayerType(pchar);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "Reason_To_Fast_GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);				
			}
			pchar.quest.RemovePatrolFromShore.win_condition.l1          = "ExitFromLocation";
			pchar.quest.RemovePatrolFromShore.win_condition.l1.location = pchar.location; 
            pchar.quest.RemovePatrolFromShore.function    				= "ReasonToFast_DeletePatrolFromShore"; 
			DialogExit();			
		break;
		
		case "Reason_To_Fast_GoodBye":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "Koydan çıksan iyi olur, gelgit zaten yükseliyor...";
			link.l1 = "Evet, evet, gidiyorum.";
			link.l1.go = "Exit";
		break;
		
		case "Reason_To_Fast_ExitFight":
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			if(pchar.questTemp.ReasonToFast == "PatrolAngry")
			{
				sld = CharacterFromID("ReasonToFast_Hunter");
				if(sld != -1) 
				{ 
					LAi_SetWarriorType(sld); 
					LAi_group_MoveCharacter(sld, sGroup);
				}
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Reason_To_Fast_AfterHunter1":
			dialog.text = "Habercinin yalnız gelmesi gerektiği konusunda anlaşmamış mıydık?";
			link.l1 = "Koordinasyon eksikliği. Haberci yolunu kaybetti. Yerine ben geldim.";
			link.l1.go = "Reason_To_Fast_11";
			link.l2 = "Ve ben yalnız geldim, ama beklediğin şey için değil.";
			link.l2.go = "Reason_To_Fast_AfterHunter2";
		break;
		
		case "Reason_To_Fast_AfterHunter2":
			dialog.text = "Demek sonunda beni buldun. Az sonra olacaklar için üzgünüm...";
			link.l1 = "Arrgh!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfterHunter";	
		break;
		
		case "Reason_To_Fast_AfterHunter3":
			dialog.text = "Seni alçak! Az kalsın inanıyordum! Muhafızlar! Yakala h"+GetSexPhrase("im","er")+"...";
			link.l1 = "Deneyin bakalım, alçaklar!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAngry";	
		break;
		// генератор "A reason to hurry"
	}
}
