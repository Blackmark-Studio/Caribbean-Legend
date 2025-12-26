void ProcessDialogEvent()
{
	ref NPChar, TempChar, sld;
	aref Link, Diag;
	
	int i, iTemp;
	string sTemp, sTemp1;
	string sGroup;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "First time":
			chrDisableReloadToLocation = false;
			//Lai_SetPlayerType(pchar);
			
			dialog.text = GetFullName(PChar)+"! "+"Seni uzun zamandır izliyorduk, sonunda artık bizimlesin.";
			Link.l1 = "Sen kimsin ve benden ne istiyorsun?";
			Link.l1.go = "meeting"; 
			
			PChar.GenQuest.HunterStart = true;
		break;

		case "meeting":
			dialog.text = XI_ConvertString(Nations[sti(NPChar.nation)].Name)+" başına iyi bir ödül koydular, seni onların herhangi bir kolonisinde teslim etmemiz yeterli, ister canlı ister ölü ol, paramızı alacağız.";
			Link.l1 = "Dinle, beni rahat bırakırsan sana para vereceğim.";
			Link.l1.go = "Cost_Head"; 
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 2 || bBettaTestMode)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+GetSexPhrase("Affedersiniz, ama bir yanlışlık olmalı. Ben "+GetFullName(TempChar)+" - bu topraklarda iyi tanınan bir tüccar.","Affedersiniz, ama bir yanlışlık olmalı. Ben sadece sıradan bir kızım ve babam ise "+GetFullName(TempChar)+" - bu topraklarda tanınmış bir tüccar.")+".";
    			Link.l2.go = "lier";
			}
            Link.l3 = "Pekâlâ, eğer istersen şansını deneyebilirsin.";
			Link.l3.go = "battle";
		break;
        
        case "lier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150) || bBettaTestMode)
            {
                dialog.text = "Ah! Belki de gerçekten yanılmışızdır. Lütfen bizi affedin, "+GetAddress_Form(NPChar)+".";
                Link.l1 = "Bazen olur, dert etme...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "Bence yalan söylüyorsun!";
                Link.l1 = "Dinle, beni rahat bırakırsan sana para vereceğim.";
			    Link.l1.go = "Cost_Head";
			    Link.l2 = "Pekala, istersen şansını deneyebilirsin.";
			    Link.l2.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
            
        break;
        
        case "lier_2":
            AddDialogExitQuest("GoAway_Hunters_Land");
            DialogExit();
        break;
        // boal <--
        
        case "battle":
            AddDialogExitQuest("Battle_Hunters_Land");    // BOAL Весь код я перенес сюда по всем нациям, просто не переименовал
            DialogExit();
        break;

        case "Cost_Head2":
            AddMoneyToCharacter(pchar, -sti(PChar.HunterCost));

            AddDialogExitQuest("GoAway_Hunters_Land"); 
            DialogExit();
        break;

        case "Cost_Head":
			dialog.text = "Bence "+PChar.HunterCost+" peso bizim için yeterli olacak.";
            if(makeint(Pchar.money) < sti(PChar.HunterCost))
            {
                Link.l1 = "Ama bende o kadar para yok.";
                Link.l1.go = "NoMoney";
            }else{
                Link.l1 = "Al paran burada, al ve kaybol.";
                Link.l1.go = "Cost_Head2";
                Link.l2 = "Böyle bir parayı sizin gibi alçaklara vermek... Sanırım hepinizi burada gebertmeyi tercih ederim!";
                Link.l2.go = "battle";
            }
		break;

        case "NoMoney":
			dialog.text = "Öyleyse, konuşmamız burada bitiyor!";
			Link.l1 = "Beni asla canlı ele geçiremeyeceksin.";
			Link.l1.go = "battle"; 
		break;
		
		case "TreasureHunter":
			dialog.text = "Bekle, "+GetSexPhrase("dostum","kız")+"... Sanırım yanında ilginç bir şey var. Arkadaşlar buldukları hazineleri birbirleriyle paylaşmalı, sence de öyle değil mi?";
            Link.l1 = "Dinle, beni rahat bırakırsan sana para vereceğim.";
			Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 3)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+GetSexPhrase("Affedersiniz, ama yanılıyorsunuz. Ben "+GetFullName(TempChar)+" - bu topraklarda tanınmış bir vatandaş, ama kesinlikle bir hazine avcısı değil.","Affedersiniz, ama bir yanlışlık olmalı. Ben sadece sıradan bir kızım, hazine avcısı değilim. Ve babam da "+GetFullName(TempChar)+" - buralarda tanınmış bir vatandaş")+"!";
    			Link.l2.go = "TreasureHunterLier";
			}
            Link.l3 = "Görünüşe bakılırsa, kafalarınızın bedenlerinizden ayrılma vakti geldi.";
			Link.l3.go = "battle";
		break;
		
		case "TreasureHunterLier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150))
            {
                dialog.text = "Ah! O zaman gerçekten yanılmış olabiliriz. Lütfen bizi affedin, "+GetAddress_Form(NPChar)+".";
                Link.l1 = "Böyle şeyler olur, kafana takma...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "Bence yalan söylüyorsun!";
			    Link.l1 = "O halde kılıcımın şarkısını dinle.";
			    Link.l1.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
        break;
		
		case "TreasureCaptain":
			dialog.text = LinkRandPhrase("Demek hazine haritamı çalan sensin! Sanırım artık aldığın her şeyi geri vermenin vakti geldi...","Ah, bir rakip! Hazinelerimin ağırlığıyla fazla ileri gidemezsin...","Hah, sonunda seni yakaladım! Bu mağaradaki bütün hazineler bana ait, anladın mı? Şimdi, ceplerini boşalt bakalım, dostum!");
			Link.l1 = LinkRandPhrase("Artık kılıcımla tanışma vaktin geldi, dostum!","Hazinelerin mi? Demek senindi, çünkü artık benim!","Sana dostum, kılıcımla bağırsaklarını deşmeyi tercih ederim.");
			Link.l1.go = "TreasureCaptain_fight"; 
		break;
		
		case "TreasureCaptain_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться // patch-6
			for(i=1; i<=4; i++)
			{
				sld = characterFromId("Treasure_sailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "TreasureOfficer":
			dialog.text = LinkRandPhrase("Demek ki albay haklıymış, hazine bu mağarada saklanmış... Cebindekileri boşalt, denizci!","Sonunda seni bu lanet ormanlarda, dikenlerde ve bataklıklarda izini sürüp yakaladık. Şimdi, alçak herif, bize her şeyini vereceksin...","Hey, denizci! O korsanın hazineleri bize ait, o yüzden o pis ellerini onlardan çek!");
			Link.l1 = LinkRandPhrase("Doğrusu, bunu bir ordu subayından beklemezdim! Ama peki, sana yine de bir ders vereceğim...","Şuna bak, subay üniforması giymiş bir korsan...","Gerçekten de, askerlerle korsanlar bugünlerde pek de farklı sayılmaz...");
			Link.l1.go = "TreasureOfficer_fight"; 
		break;
		
		case "TreasureOfficer_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться // patch-6
			for(i=1; i<=4; i++)
			{
				sld = characterFromId("Treasure_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// генератор "A reason to hurry"
		case "ReasonToFast_THunter_1":
			if(CheckAttribute(pchar,"GenQuest.CannotWait"))	DeleteAttribute(pchar, "GenQuest.CannotWait");
			dialog.text = "Ve işte altınımız geliyor. En azından bekleyişimiz boşa gitmedi.";
			link.l1 = RandPhraseSimple("Ne diyorsunuz beyler? Ben Hollanda Batı Hindistan Şirketi'nin bir temsilcisiyim ve buradan sadece geçiyorum! Sadece kıyı manzarasını seyretmek için durdum!","Beni başka biriyle karıştırdınız sanırım. Ben "+GetSexPhrase("Francua Marie Paganel, ","Maria-Theresa, ")+"Bir doğa bilimcisiyim. Buradaki yerel bitki örtüsünden örnekler topluyorum. Yuka yapraklarından oluşan koleksiyonuma bakmak ister misin? Çok ilginç birkaç tane var!");
			link.l1.go = "ReasonToFast_THunter_2";
			link.l2 = "Ne istiyorsun?! Yolumdan çekil!";
			link.l2.go = "ReasonToFast_THunter_2";
		break;
		
		case "ReasonToFast_THunter_2":
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.Treasure.Location);
			dialog.text = "Ah hayır, "+GetSexPhrase("sevgili dostum","güzel kızım")+". Bu işe yaramaz. Haritanın sana ait olduğunu kesin olarak biliyoruz "+GetName(pchar.questTemp.ReasonToFast.mapIdx,pchar.questTemp.ReasonToFast.map,NAME_GEN)+"Ve öyle bir cimriydi ki sandıkları içten patlayacak gibiydi, para doluydu. Yani buradan eli boş ayrılmayacağız.";
			link.l1 = "Haklısın. Sandıklar gerçekten doluydu. Ama onları alamayacaksın. O mağarayı ziyaret etmeyi deneyebilirsin, birkaç delik deşik kova hâlâ orada olmalı.";
			link.l1.go = "ReasonToFast_THunter_3";
			if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
				&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
			{
				link.l2 = "Haklısın. Hazineni alabilirsin. Ama unutma, bu hazine kana bulanmış olduğu için sana mutluluk getirmeyecek.";
				link.l2.go = "ReasonToFast_THunter_4";
			}	
		break;
		
		case "ReasonToFast_THunter_3":
			dialog.text = ""+GetSexPhrase("Heh, kaptan, ölmek için fazla genç değil misin...","Heh, kızım, ölmek için fazla genç değil misin...")+"...";
			link.l1 = "Aslında, ölmeyeceğim!";
			link.l1.go = "ReasonToFastTHunter_Fight";
		break;
		
		case "ReasonToFast_THunter_4":
			dialog.text = "İşte bu, aklı başında birinin sözleri!";
			link.l1 = "Seni ve o hazinelerini lanet olsun...";
			link.l1.go = "ReasonToFast_THunter_GoAway";
		break;
		
		case "ReasonToFast_THunter_GoAway":			
			iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}	
			if(pchar.questTemp.ReasonToFast == "GetTreasure")
			{
				AddQuestRecord("ReasonToFast", "24");
				AddQuestUserData("ReasonToFast", "sName", GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN));
				CloseQuestHeader("ReasonToFast");	
			}
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFastTHunter_Fight":
			sGroup = "LAND_HUNTER";
			sTemp = "LandHunter0";
			iTemp = sti(pchar.HunterCost.Qty);
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			for(i = 1; i <= iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_TrHuntersDied");	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "ReasonToFast_HunterShore1":
			dialog.text = "Hey,"+GetSexPhrase("dostum","kız")+"! "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" bize bir şeyin olduğunu söyledin.";
			link.l1 = "Ne demek istiyorsun?";
			link.l1.go = "ReasonToFast_HunterShore11";
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
		break;

		case "ReasonToFast_HunterShore11":
			if(pchar.questTemp.ReasonToFast == "GetMap") 
			{
				dialog.text = "Bir harita "+GetName(pchar.questTemp.ReasonToFast.mapIdx,pchar.questTemp.ReasonToFast.map,NAME_GEN);
				link.l1 = "Al bunu ve   selamımı ilet "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Ona yakında görüşeceğimizi söyle...";
				link.l1.go = "ReasonToFast_HunterShore12_1";
				link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+"   onun için ateşten kestane çıkaracağımı sanıyorsa, fena halde yanılıyor.";
				link.l2.go = "ReasonToFast_HunterShore23";
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				dialog.text = "Validenin valisinden çaldığın mücevherler.";
				if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
					&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
				{
					link.l1 = "Al bunu ve ona selam söyle "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Ona yakında görüşeceğimizi söyle...";
					link.l1.go = "ReasonToFast_HunterShore12_2";
				}	
				link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+"   onun için ateşten kestane çıkaracağımı sanıyorsa fena halde yanılıyor.";
				link.l2.go = "ReasonToFast_HunterShore23";				
			}
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore12_1":
			TakeNItems(pchar, "mapQuest", -1); 
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "a map of");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFast_HunterShore12_2":
			iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}			
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "treasures");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DialogExit();	
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.city + "_townhall");
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.LakeyLocation);
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFast_HunterShore2":
			dialog.text = "Hey,"+GetSexPhrase("dostum","kız")+"! "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" sizinle ilgili birkaç sorusu var.";
			link.l1 = "Peki, neden onlara kendisi sormuyor?";
			link.l1.go = "ReasonToFast_HunterShore21";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore21":
			dialog.text = "Rütbesine göre değil. Operasyonumuzu mahvettin ve kaybettik "+sti(pchar.questTemp.ReasonToFast.p10)+" pesos yüzünden senin sayende. Şimdi ödenecek bir borcun var.";
			link.l1 = "Al bunu ve ona selam söyle "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Ona yakında buluşacağımızı söyle...";
			link.l1.go = "ReasonToFast_HunterShore22";
			link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+"   onun için ateşten kestane çıkarmaya kalkacağımı sanıyorsa, fena halde yanılıyor.";
			link.l2.go = "ReasonToFast_HunterShore23";
		break;
		
		case "ReasonToFast_HunterShore22":
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p10))
			{
				AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p10)));
				AddQuestRecord("ReasonToFast", "20");
				AddQuestUserData("ReasonToFast", "sText", "money");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
				DialogExit();	
				AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
			}
			else
			{
				dialog.text = "Ah, o kadar paran yokmuş! Eh, seçimini yaptın... ";
				link.l1 = "Uzun zaman önce...";
				link.l1.go = "ReasonToFastTHunter_Fight";	
				if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
				{
					pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
					pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
				}
			}
		break;
		
		case "ReasonToFast_HunterShore23":
			dialog.text = "Pekala, seçimini yaptın...";
			link.l1 = "Uzun zaman önce...";
			link.l1.go = "ReasonToFastTHunter_Fight";
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
			{
				pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
				pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
			}
		break;
		// генератор "A reason to hurry"
	}
}

string GetLocHunterName()
{
	int nLoc = FindLocation(Pchar.location);
	string ret = "";

	if (CheckAttribute(&locations[nLoc],"islandId"))
	{
		if (locations[nLoc].islandId != "Mein")
		{
			ret = "island of " + GetIslandNameByID(locations[nLoc].islandId);
		}
		else
		{
			ret = "mainland of ";
		}
	}
	//
	if (CheckAttribute(&locations[nLoc],"fastreload"))
	{
		ret += " (" +GetCityName(locations[nLoc].fastreload) + ")";
	}

	return ret;	
}
