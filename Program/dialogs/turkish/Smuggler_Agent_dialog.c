void ProcessDialogEvent()
{
	ref NPChar, her;
	aref Link, NextDiag;
	bool bOk = false;
    bool bOk2;
    
	int Sum, nRel, nDay, iChurchQuest2_Summ;
	ref sld;
	
	// Церковный квест № 2 -->
	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra"))
	{
		iChurchQuest2_Summ = sti(PChar.rank)*100 + (rand(3)+1)*100;
		PChar.GenQuest.ChurchQuest_2.Summ_To_Contra = sti(iChurchQuest2_Summ);
	}
	// <-- Церковный квест № 2
	
	string sColony;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	// belamour legendary edition
	bool MCGovernon = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
	bool MCAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

	//тереть нафиг аттрибут при прошествии дней (navy fix)
	if (CheckAttribute(pchar, "GenQuest.contraTravel.days") && GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
	{
		DeleteAttribute(pchar, "GenQuest.contraTravel");
		CloseQuestHeader("Gen_ContrabandTravel");
	}

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Smuggling_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			PlaceSmugglersOnShore(Pchar.quest.contraband.CurrentPlace);
			Pchar.quest.Contraband.active = true;
			pchar.GenQuest.Contraband.GuardNation = npchar.nation;
			pchar.GenQuest.Contraband.SmugglerId  = npchar.id;				
			SetAllContraGoods(&Stores[sti(Pchar.GenQuest.Contraband.StoreIdx)], npchar);
			ReOpenQuestHeader("Gen_Contraband");
            if (GetIslandByCityName(npchar.city) == "Mein")
            {
            	AddQuestRecord("Gen_Contraband", "t1_1");
            }
            else
            {
	            AddQuestRecord("Gen_Contraband", "t1");
				if (Pchar.quest.contraband.CurrentPlace == "shore30" || Pchar.quest.contraband.CurrentPlace == "shore31")
				{
					AddQuestUserData("Gen_Contraband", "sIsland", "Marie Galante");
				}
				if (Pchar.quest.contraband.CurrentPlace == "shore59")
				{
					AddQuestUserData("Gen_Contraband", "sIsland", "Tobago");
				}
				AddQuestUserData("Gen_Contraband", "sIsland", XI_ConvertString(GetIslandByCityName(npchar.city)));
			}
			AddQuestUserData("Gen_Contraband", "sLoc", GetLocationNameByID(Pchar.quest.contraband.CurrentPlace));
				
			DialogExit();
		break;
		
		case "First time":											
			//--> Jason если идёт первая часть квеста Шарля
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
            {
				dialog.text = "Monsieur, buradan gidin. Sanmıyorum ki konuşacak bir şeyimiz olsun.";
				link.l1 = "Gerçekten mi? Yüzümü beğenmedin mi? Peki, gidiyorum...";
				link.l1.go = "exit";
				break;
			}
			//<-- идёт первая часть квеста Шарля
			//--> Addon-2016 Jason блокировка контры во избежание конфликтов с квестами
			if (CheckAttribute(pchar, "GenQuest.SmugglersBlock") && pchar.GenQuest.SmugglersBlock == npchar.location)
            {
				dialog.text = "Bugün iş yok.";
				link.l1 = "Anladım.";
				link.l1.go = "exit";
				break;
			}
			//--> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
				dialog.text = "Arkadaşlarım ve ben bugün çok meşgulüz.";
				link.l1 = "Ama benim ihtiyacım var...";
				link.l1.go = "SantaMisericordia_1";
				break;
			}
			//<-- прибыла инспекция на Святом Милосердии
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.Consumption.Contra"))
            {
				dialog.text = "Ne istiyorsun, kaptan?";
				link.l1 = "Biraz konuşabilir miyiz?";
				link.l1.go = "Consumption";
				break;
			}
			//<-- Цена чахотки
			
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Ne istiyorsun, kaptan? Senin adını bilmiyorum ve kendi adımı da sana söyleyemem.";
				Link.l1 = "Ben kaptanım "+GetFullName(pchar)+".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1"; 
			}
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 1)
				{
					if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
					{
						pchar.GenQuest.CaptainComission.SpeakContra = true;
						dialog.text = "Bugün iş yok. Her körfezde devriyeler var, valimiz bir kaptan tarafından el konulan bir yükü arıyor"+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" ve onu bir yere sakladı.";
						link.l1 = "Ve bu kaptan nerede"+pchar.GenQuest.CaptainComission.Name+"?";
						link.l1.go = "CapComission_1";
						break;
					}
					else
					{
						dialog.text = "Bugün iş yok.";
						link.l1 = "Anladım.";
						link.l1.go = "exit";					
						break;
					}
				}

				if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
				{
					dialog.text = "Bugün iş yok.";
					link.l1 = "Anladım.";
					link.l1.go = "exit";
					break;
				}
				
				if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
				{
					dialog.text = "Bugün iş yok.";
					link.l1 = "Anladım.";
					link.l1.go = "exit";
					break;
				}

				Dialog.Text = "Ne istiyorsun, kaptan?";
				if (LAi_group_GetPlayerAlarm() > 0)
				{
	       			Dialog.Text = RandPhraseSimple("Çabuk ol, "+GetSexPhrase("pal","kız")+", ne istiyorsun? Peşindeler!","Ne işin var, çabuk söyle! Askerler peşinde ve fazla vaktimiz yok...");
				}
				// belamour legendary edition
				bOk2 = MCGovernon || MCAdmiral;
				if(FindContrabandGoods(PChar) != -1 && !bOk2)
				{
					Link.l1 = "Bir şey almak ya da satmak istiyorum.";
					Link.l1.go = "Meeting_3";
				}

				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
					Link.l2 = "Seyahat hakkında...";
				else
					Link.l2 = "Bir yere gitmem gerekiyor.";
				Link.l2.go = "Travel";
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakSmuggler"))
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l3 = "Sana özel bazı 'özel' mallarım var ve ilgini çekebileceğini düşünüyorum. Bir göz at!";
						link.l3.go = "SM_ShipLetters_1";
					}	
				}				

				//Jason --> мини-квест Бесчестный конкурент
				if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
				{
					Link.l8 = "Sana alışılmadık bir işim var.";
					Link.l8.go = "Shadowtrader_smugglers";
				}
				// <-- мини-квест Бесчестный конкурент
				//--> Торговля по закону
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "Dinle dostum, bana bir parti şarap ve rom lazım. Ne kadar çok, o kadar çabuk.";
					Link.l8.go = "TPZ_smugglers_1";
				}
				// <-- Торговля по закону
				//Jason --> генератор сбыта бакаута
				if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
				{
					Link.l9 = "Michael Rosenkraft ile görüşmem gerekiyor. Ona ilgi çekici bir yüküm var.";
					Link.l9.go = "bakaut";
				}
				// <-- генератор сбыта бакаута
				
				// Церковный генератор №2 -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					Link.l4 = "Bir şey öğrenmem lazım, dostum.";
					Link.l4.go = "Contra_GenQuest_Church_2_1";
				}
				
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
				{
					Link.l5 = "Senin bir meslektaşın ve benim de iyi bir dostum  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+" bazı işlerden haberdar olduğunuzu söylediler.";
					Link.l5.go = "Contra_GenQuest_Church_2_Contra2_1";
				}
				// <-- Церковный генератор №2
				
				Link.l7 = "Hiçbir şey. Görüşürüz.";
				Link.l7.go = "Exit";				
			}
		break;
		
		case "CapComission_1":
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				dialog.text = "Kalenin mahzeninde, başka nerede olacak? O kaptan, her an yetkililere gizli yeri gösterebilir, o zaman bize hiçbir şey kalmaz. Bu tantana bitmeden hiçbir işe kalkışma.";
				link.l1 = "Dinle, bu adanın her köşesini biliyorsun. Kaptanın nerede olduğuna dair gerçekten hiçbir fikrin yok mu "+pchar.GenQuest.CaptainComission.Name+"gizli yer nerede?";
				link.l1.go = "CapComission_4";
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				dialog.text = "Sanırım gökyüzünde. Mürettebatıyla birlikte asıldı. Ama idam kararında geminin korsan gemisi olduğundan bahsetmediler.";
				link.l1 = "Peki o geminin bir korsan gemisi olduğundan neden bu kadar eminsiniz?";
				link.l1.go = "CapComission_2";
			}	
		break;
		
		case "CapComission_2":
			dialog.text = "Biz kayalıklardan dövüşü izliyorduk. Dürbünle baktığımızda, geminin Jolly Roger bayrağını çektiğini gördük. Sonra, yaklaşık beş saat sonra, karanlıkta bir parıltı gördük — sanki barut mahzeninde bir patlama olmuş gibiydi. Yükü karaya çıkarmak için yeterli zaman vardı.";
			link.l1 = "Kaptanın nerede olduğunu bilmiyor musun "+pchar.GenQuest.CaptainComission.Name+"'ın gizli eşyası mı? Bu adanın her köşesini bilirsin.";
			link.l1.go = "CapComission_3";
		break;
		
		case "CapComission_3":
			dialog.text = "Hayır. Biz de onu arıyoruz, ama valinin eğlencesi için değil...";
			link.l1 = "Anladım... İyi günler.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "38");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
		break;
		
		case "CapComission_4":
			dialog.text = "Hayır. Biz de onu arıyoruz ama vali eğlensin diye değil... he-he";
			link.l1 = "Anladım... İyi günler.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "19");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		break;
				
		case "SM_ShipLetters_1":
			pchar.questTemp.different.GiveShipLetters.speakSmuggler = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Neden böyle düşündün? Ben dürüst bir tüccarım. Git ve başka bir alıcı bul.";
				link.l1 = "Teşekkürler...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Neden olmasın? Belki 'yükün' için bir kullanım bulurum. Al "+sti(pchar.questTemp.different.GiveShipLetters.price2)+" paraları al ve unut gitsin.";
					link.l1 = "Hayır, teşekkürler.";
					link.l1.go = "SM_ShipLetters_2";	
					link.l2 = "Ve doğru tahmin ettin, bunu unutmaya başladım artık!";
					link.l2.go = "SM_ShipLetters_3";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Kesinlikle! Şimdi gerçekten merak ettim. Sanırım eğer sana ödeme yaparsam "+sti(pchar.questTemp.different.GiveShipLetters.price3)+" parayı alınca, o kağıtlar umurunuzda bile olmayacak.";
						link.l1 = "Hayır, teşekkürler.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "Haklısın. Onları çoktan unuttum bile.";
						link.l2.go = "SM_ShipLetters_3";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Şimdi, o küstah herifi yakalamak için bir fırsat çıktı! Gerçekten, gerçekten merak ediyorum. Bak, sana ödeme yapacağım "+sti(pchar.questTemp.different.GiveShipLetters.price4)+" altın karşılığında, masadaki belgeleri tamamen unutacaksın, öyle mi?";
						link.l1 = "Yapmam.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "Pekâlâ, anlaştık!";
						link.l2.go = "SM_ShipLetters_3";
					}
				}
			}
		break;
		
		case "SM_ShipLetters_2":
			dialog.text = "Peki, peki, ama artık daha fazla düşman edinmeyi bırak.";
			link.l1 = "Sana da!";
			link.l1.go = "exit";
		break;
		
		case "SM_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "7");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Meeting":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 2)
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
				{
					pchar.GenQuest.CaptainComission.SpeakContra = true;
					dialog.text = "Bugün iş yok. Her koyda devriyeler var, valimiz bir kaptan tarafından el konulan bir yükü arıyor"+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" ve onu bir yere sakladı.";
					link.l1 = "Ve bu kaptan nerede"+pchar.GenQuest.CaptainComission.Name+"?";
					link.l1.go = "CapComission_1";
					break;
				}
				else
				{
					dialog.text = "Bugün iş yok.";
					link.l1 = "Anladım.";
					link.l1.go = "exit";					
					break;
				}
			}
			
			if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
			{
				dialog.text = "Bugün iş yok.";
				link.l1 = "Anladım.";
				link.l1.go = "exit";
				break;
			}
			
			if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
			{
				dialog.text = "Bugün iş yok.";
				link.l1 = "Anladım.";
				link.l1.go = "exit";
				break;
			}
			
			Dialog.Text = "Sana nasıl yardımcı olabilirim, kaptan?";
			
			bOk2 = MCGovernon || MCAdmiral;
			if(FindContrabandGoods(PChar) != -1 && !bOk2)
			{
				Link.l1 = "Mal alıp satmak istiyorum.";
				Link.l1.go = "Meeting_1";
			}
			
			Link.l2 = "Bir yere gitmem gerekiyor.";
			Link.l2.go = "Travel";				
			
			//Jason --> мини-квест Бесчестный конкурент
			if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
			{
				Link.l8 = "Sana oldukça sıradışı bir işim var.";
				Link.l8.go = "Shadowtrader_smugglers";
			}
			// <-- мини-квест Бесчестный конкурент
			//--> Торговля по закону
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "Dinle dostum, bana bir parti şarap ve rom lazım. Ne kadar çok, o kadar çabuk.";
					Link.l8.go = "TPZ_smugglers_1";
				}
			// <-- Торговля по закону
			//Jason --> генератор сбыта бакаута
			if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
			{
				Link.l9 = "Michael Rosenkraft ile görüşmem lazım. Ona ilginç gelecek bir yüküm var.";
				Link.l9.go = "bakaut";
			}
			// <-- генератор сбыта бакаута
			
			// Церковный генератор №2 -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				Link.l3 = "Bir şey öğrenmem lazım, dostum.";
				Link.l3.go = "Contra_GenQuest_Church_2_1";
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
			{
				Link.l3 = "Senin bir meslektaşın ve benim de iyi bir dostum  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+" bazı işlerden haberdar olduğunuzu söylediler.";
				Link.l3.go = "Contra_GenQuest_Church_2_Contra2_1";
			}
			// <-- Церковный генератор №2

			Link.l5 = "Hiçbir şey. Görüşürüz.";
			Link.l5.go = "Exit";				
		break;

		// Церковный генератор №2 -->
		case "Contra_GenQuest_Church_2_1":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			dialog.text = "Ben senin arkadaşın değilim. Ve bu sana pahalıya patlayabilir.";
				link.l1 = "Hm. Bana fazla pahalıya mal olmayacak bir şeyi bilmem gerekiyor "+FindRussianMoneyString(iChurchQuest2_Summ)+".";
				link.l1.go = "Contra_GenQuest_Church_2_2";
			break;
			
		case "Contra_GenQuest_Church_2_2":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			if(sti(PChar.money) >= iChurchQuest2_Summ)
			{
				dialog.text = "Paranı ver. Ve bil ki, bu kadarla fazla bir şey alamazsın.";
				link.l1 = "Bak, arkadaşlarımı özlemiştim. Bir buluşmaya geç kaldım, beni beklemediler...";
				link.l1.go = "Contra_GenQuest_Church_2_3";
				AddMOneyToCharacter(PChar, -iChurchQuest2_Summ);
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra");
			}
			else
			{
				dialog.text = "Ha, cebinde beş kuruş yok! Biraz paran olunca geri gel.";
				link.l1 = "Elbette, hemen.";
				link.l1.go = "exit";
			}
			break;
			
		case "Contra_GenQuest_Church_2_3":
				dialog.text = "Ve neden bana ihtiyacın var?";
				link.l1 = "Onlar şehirde değiller ve bir gemileri yok. Bu yüzden düşündüm ki: belki iş ortaklarınızdan biri onlara bir iyilik yapmıştır?";
				link.l1.go = "Contra_GenQuest_Church_2_4";
			break;
			
		case "Contra_GenQuest_Church_2_4":
			sColony = QuestGetColony(PChar.GenQuest.ChurchQuest_2.QuestTown);
			dialog.text = "Anladım... Birkaç adamla karşılaştım, adadan uzaklaşmak istediklerini ve nereye gideceklerinin umurlarında olmadığını söylediler. Böyle durumlarda nedenini sormayız, sadece ödeme hakkında konuşuruz. Bir yolculuğumuz vardı "+XI_ConvertString("Colony"+sColony+"Acc")+" , "+XI_ConvertString(locations[FindLocation(sColony+"_Town")].IslandID+"Dat")+" . Seni oraya götürebiliriz, eğer parayı konuşursak.";
			link.l1 = "Teşekkürler, ama kendi gemim var.";
			link.l1.go = "exit";
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "8");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + sColony + "Acc"));
			AddQuestUserData(sQuestTitle, "sIsland", XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Voc"));
			PChar.GenQuest.ChurchQuest_2.AskContra_2 = true;
			PChar.GenQuest.ChurchQuest_2.Contra_Colony = sColony;
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_1":
			dialog.text = "Seninle hiç iş yapmadım.";
			link.l1 = "Bunu düzeltebiliriz. Arkadaşlarımı buraya kısa süre önce getirdin. Bir buluşmayı kaçırdım "+GetSexPhrase("onlar","onlar")+".";
			link.l1.go = "Contra_GenQuest_Church_2_Contra2_2";
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_2":
			string sGenLocation = IslandGetLocationFromType(locations[FindLocation(PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_Town")].IslandID, "Shore");
			PChar.GenQuest.ChurchQuest_2.QuestGangShore = sGenLocation;
			PChar.GenQuest.ChurchQuest_2.BanditsInShore = true;
			dialog.text = "Hm, onları karaya çıkardık "+XI_ConvertString(sGenLocation+"Gen")+"... Biliyor musun, onların senin dostların olması senin için daha iyi olur, yoksa başka bir durumda onlara bulaşmanı hiç tavsiye etmem.";
			link.l1 = "Endişeniz için teşekkür ederim, ama hem iyi silahlanmışım hem de oldukça çekiciyim.";
			link.l1.go = "exit";
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "9");
			AddQuestUserData(sQuestTitle, "sShore", XI_ConvertString(sGenLocation + "Gen")); // belamour gen
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			SetFunctionTimerCondition("Church_GenQuest2_TimeIsLeft", 0, 0, 1, false);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2");
		break;
		// <-- Церковный генератор №2

		case "Meeting_1":
			Dialog.Text = "Hm... bu beni neden ilgilendirsin ki? Yolunu kaybetmiş olmalısın, kaptan. Git dükkana, orada ne almak ya da satmak istiyorsan onu yap.";
			Link.l1 = "Hayır, sana ihtiyacım var.";
			Link.l1.go = "Meeting_2";				
			Link.l2 = " Tavsiyeniz için teşekkür ederim. İyi günler.";
			Link.l2.go = "exit";				
		break;

		case "Meeting_2":
			Dialog.Text = "Ne için?";
			Link.l1 = "Belki özel bazı mallarla ilgilenirsiniz? Ya da belki bana sunacak bir şeyiniz vardır?"Link.l1.go ="Meeting_3";				
		break;

		case "Meeting_3":
			int iTmp = false;
			int iChIdx, i;
			
			float fMaxClass = ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5);
			if (IsEquipCharacterByArtefact(pchar, "talisman21")) fMaxClass = 2.0;
			
			if (GetCompanionQuantity(pchar) > 1) iTmp = true;
			if (GetCharacterShipClass(pchar) < fMaxClass) iTmp = true;

			// поиск мин.  те старшего класса
			/* for (i=0; i<COMPANION_MAX; i++)
			{
				iChIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iChIdx>=0)
				{
					sld = GetCharacter(iChIdx);
            		if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
				}
			} */
			
			if (iTmp)
			{
				dialog.text = NPCStringReactionRepeat("Bir dahaki sefere neden bir kraliyet savaş gemisiyle gelmiyorsun? Gemin kaleden kolayca fark ediliyor. Kafamızı riske atmayız. Bir dahaki sefere tek bir küçük gemiyle gel.","Tekrar mı edeyim? Daha küçük bir gemi bul, sonra konuşuruz.","Gerçekten bu kadar aptal mısın? Git kendine bir şoner ya da bir brig edin. Ancak o zaman iş yapabiliriz.","Ah, ne aptalım...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Pekâlâ, seni anlıyorum.","Anladım, sadece bir şeyi netleştirmek istedim.","Hayır, aptal değil, sadece cimri. Bir şeylerin değiştiğini sanmıştım. Birkaç pinas daha alırdım...","Aynaya bak...",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
				break;
			}
			bOk  = CheckAttribute(pchar, "GenQuest.contraTravel.active") && (sti(pchar.GenQuest.contraTravel.active) == true);
			bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
			bool bOk3 = CheckAttribute(Pchar, "questTemp.pirateStartQuest") && (Pchar.questTemp.pirateStartQuest == "3");
			if (bOk)
			{
			    if (GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
				{  // просрочка
					DeleteAttribute(PChar, "GenQuest.contraTravel");
					CloseQuestHeader("Gen_ContrabandTravel");
					bOk = false;
				}
			}

//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "Üzgünüm, "+GetSexPhrase("kanka","kız")+", şu anda zaten meşgulüz. Birkaç gün sonra tekrar gel.";
				Link.l1 = "Ne yazık...";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--

			if (bOk || bOk2 || bOk3)
			{
				Dialog.Text = "Önce şu anki işimizi bitirsek nasıl olur?";
				Link.l1 = "Sanırım haklısınız.";
				Link.l1.go = "Exit";				
			}
			else
			{
                if (npchar.quest.trade_date != lastspeak_date)
    			{
                    npchar.quest.trade_date = lastspeak_date;
                    
                    if (ChangeContrabandRelation(pchar, 0) > 5)
                    {
                        Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
						Pchar.quest.contraband.City = NPChar.city;
                        if (Pchar.quest.contraband.CurrentPlace != "None")//boal fix
                        {
                            if (ChangeContrabandRelation(pchar, 0) >= 70)
                            {
                                Dialog.Text = "Sizinle iş yapabileceğimizi biliyoruz.   Sizi bekliyor olacağız "+GetLocationNameByID(Pchar.quest.contraband.CurrentPlace)+".";
                            }
                            else
                            {
            				    Dialog.Text = "Hm... Belki sana bir alıcı bulabiliriz. Seni   bekliyor olacağız  "+GetLocationNameByID(Pchar.quest.contraband.CurrentPlace)+".";
            				}
            				Link.l1 = "Pekala. Orada görüşürüz.";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal fix
                            Dialog.Text = "Bugün iş yok. Yarın tekrar gel.";
            				Link.l1 = "Pekala.";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = " Bütün bunlardan sonra gerçekten seninle çalışmak isteyen biri olacağını mı sanıyorsun? Üzerine ödül avcılarını salmadığımıza şükret.";
        				Link.l1 = "Ne yazık. Kaçakçı olma şansım kalmadı.";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    Dialog.Text = "Bugün iş yok. Yarın tekrar gel.";
    				Link.l1 = "Pekala.";
    				Link.l1.go = "Exit";
				}
			}
		break;
////////////////////////////////////////////////////////////////////////////////
//	Корсарское метро
////////////////////////////////////////////////////////////////////////////////
		case "Travel":
//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "Üzgünüm, "+GetSexPhrase("kanka","kız")+", şu anda meşgulüz. Birkaç gün sonra tekrar gel.";
				Link.l1 = "Ne yazık.";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--
			//если нет корабля у ГГ и нет компаньонов все ок
			if (sti(pchar.ship.type) == SHIP_NOTUSED && GetCompanionQuantity(pchar) == 1 && GetPassengersQuantity(pchar) == 0)
			{
				//случай если уже была инфа
				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
				{
					//платил уже
					if (CheckAttribute(pchar, "GenQuest.contraTravel.payed") && sti(pchar.GenQuest.contraTravel.payed) == true)
					{
						Dialog.Text = "Anlaşmayı zaten yaptığımızı sanıyordum?";
						Link.l2 = "Gerçekten!";
					}
					//не платил, значит можно запалатить пока не вышел срок.
					else
					{
						if(GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = "Parayı getirdin mi?";
							Link.l1 = "Evet.";
							Link.l1.go = "Travel_pay";
							Link.l3 = "Fikrimi değiştirdim...";
							Link.l3.go = "Travel_abort";
							Link.l2 = "Henüz değil.";
						}
						else
						{
                            if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
							{
								Dialog.Text = "Sana zaten her şeyi anlattım.";
								Link.l2 = "Aynen öyle.";
								Link.l1 = "Fikrimi değiştirdim...";
								Link.l1.go = "Travel_abort";
							}
							else // просрочка
							{
							    Dialog.Text = "Bugün sana yardımcı olamam. İki gün sonra tekrar gel, belki o zaman senin için bir şeyler buluruz.";
								Link.l2 = "Ne yazık.";
								DeleteAttribute(PChar, "GenQuest.contraTravel");
								CloseQuestHeader("Gen_ContrabandTravel");
							}
						}
					}
				}
				//если не было договора, обговариваем условия
				else
				{
					nRel = ChangeContrabandRelation(pchar, 0);
					//если нормальные отношения и количество подстав меньше 20, работаем....
					if (nRel > 0 && Statistic_AddValue(PChar, "contr_TravelKill", 0) < 20)
					{
						//бухта...
						pchar.GenQuest.contraTravel.CurrentPlace = SelectSmugglingLocation();
						aref arTmp; makearef(arTmp, pchar.GenQuest.contraTravel);
						SetSmugglersTravelDestination(arTmp);
						//за сколько доставят 
						pchar.GenQuest.contraTravel.price = (sti(PChar.rank)*250 + (100 - nRel)*10 + rand(30)*20) + sti(arTmp.destination.days)*100;
						
						//если метро активно, и нет пассажиров у ГГ, и ещё сегодня не виделись, есть доступная бухта, и ранд ...
						bOk = !bPauseContrabandMetro && CheckNPCQuestDate(npchar, "Travel_Talk") && 
							Pchar.GenQuest.contraTravel.CurrentPlace != "None" && rand(50) < nRel;
                        bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
						if (bOk && !bOk2)
						{
							nDay = 1 + rand(3);
							SetNPCQuestDate(npchar, "Travel_Talk");
							SaveCurrentQuestDateParam("contraTravel");

							Dialog.Text = "Seni oraya götürebiliriz "+GetLocationNameByRef(&locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)])+" yakınında "+XI_ConvertString("Colony"+pchar.GenQuest.contraTravel.destination+"Gen")+" için "+pchar.GenQuest.contraTravel.price+" altın. Parayı getir "+FindRussianDaysString(nDay)+". Gemi seni bekliyor olacak "+GetLocationNameByRef(&locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)])+" tam olarak 24 saat.";

							pchar.GenQuest.contraTravel.days = nDay;
							Link.l1 = "Bana uyar.";
							Link.l1.go = "Travel_agree";
							Link.l2 = "Hayır, teşekkür ederim.";
						}
						else
						{
							Dialog.Text = "Bugün sana yardımcı olamam. İki gün sonra tekrar gel, belki o zaman senin için bir şeyler buluruz.";
							Link.l2 = "Ne yazık.";
						}
					}
					//нет, посылаем в сад
					else
					{
                        Dialog.Text = "Gerçekten de tüm bunlardan sonra seninle çalışmak isteyen biri olacağını mı sanıyorsun? Üzerine kelle avcılarını salmadığımıza şükretmelisin. Defol!";
        				Link.l2 = "Hmm, yine şansım yaver gitmedi.";
					}

				}
			}
			//корабль есть, посылаем в сад...
			else 
			{
				if(GetPassengersQuantity(pchar) != 0)
				{
					Dialog.Text = "Hayır, hepinizi almayacağız. Sadece birinizi.";
					Link.l2 = RandSwear()+"Zaten buna ihtiyacım yok!";
				}
				else
				{
					Dialog.Text = "Neden kendi gemini kullanmıyorsun? Hayır, seni götürmeyeceğiz.";
					Link.l2 = "Peki, nasıl istersen.";
				}
			}
			Link.l2.go = "Exit";
			break;

		//отмена
		case "Travel_abort":
			ChangeContrabandRelation(pchar, -2);
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			CloseQuestHeader("Gen_ContrabandTravel");
			Dialog.Text = "Ne istersen.";
			Link.l1 = "";
			Link.l1.go = "Exit";
			break;

		//ГГ согласен ехать
		case "Travel_agree":
			ReOpenQuestHeader("Gen_ContrabandTravel");
			AddQuestRecord("Gen_ContrabandTravel", "1");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_ContrabandTravel", "sLoc", GetLocationNameByID(pchar.GenQuest.contraTravel.CurrentPlace));
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetLocationNameByID(pchar.GenQuest.contraTravel.destination.loc));
			AddQuestUserData("Gen_ContrabandTravel", "sPlaceTo", XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen"));
			AddQuestUserData("Gen_ContrabandTravel", "sDays", FindRussianDaysString(sti(pchar.GenQuest.contraTravel.days)));
			AddQuestUserData("Gen_ContrabandTravel", "sPrice", pchar.GenQuest.contraTravel.price);

			//активируем квест
			pchar.GenQuest.contraTravel.active = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;

		//ГГ согласен платить
		case "Travel_pay":
			//денег хватает?
			Sum = sti(pchar.GenQuest.contraTravel.price);
			if (sti(pchar.money) >= Sum)
			{
				AddMoneyToCharacter(pchar, -1*Sum);
				//ставим флаг оплаты
				pchar.GenQuest.contraTravel.payed = true;
				Dialog.Text = "Sizinle iş yapmak zevkti. Gemiye geç kalmayın.";
				Link.l1 = "Denerim.";
				AddQuestRecord("Gen_ContrabandTravel", "2");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("",""));
				
				//ставим контру.
				PlaceSmugglersOnShore(PChar.GenQuest.contraTravel.CurrentPlace);
				//корабль на волнах в бухте....
				Sum = sti(pchar.GenQuest.contraTravel.destination.days);
				sld = GetCharacter(NPC_GenerateCharacter("Abracham_Gray", "citiz_46", "man", "man", 5, PIRATE, Sum + 2, true, "hunter"));
				//воскресим...
				sld.nation = PIRATE;
				SetRandomNameToCharacter(sld);
				SetMerchantShip(sld, rand(GOOD_PAPRIKA));
				SetFantomParamHunter(sld);
				SetCaptanModelByEncType(sld, "pirate");
				SetCharacterShipLocation(sld, PChar.GenQuest.contraTravel.CurrentPlace);

				SetTimerCondition("RemoveTravelSmugglers", 0, 0, 1, false);
			}
			//нет, посылаем в сад...
			else
			{
				Dialog.Text = "Görünüşe göre yeterince paran yok."Link.l1 ="Ne yazık, sonra tekrar geleceğim.";
			}
			Link.l1.go = "Exit";
		break;  
////////////////////////////////////////////////////////////////////////////////
//	END OF Корсарское метро
////////////////////////////////////////////////////////////////////////////////
				
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_smugglers":
			dialog.text = "Çok ilginç. Ne getirdiğini göster bakalım.";
			link.l1 = "Çok 'özel' malları cazip bir fiyata takas edebileceğin yeraltı bir dükkân olduğunu duydum, üstelik bu dükkânı kurmaya senin yardım ettiğini söylediler. Sahibiyle konuşmak istiyorum.";
			link.l1.go = "Shadowtrader_fail";
			link.l2 = "Bazılarına göre, yeraltında çok 'özel' malları cazip bir fiyata alabileceğin gizli bir dükkan varmış. Birkaç güne yelken açmam gerekiyor ve yerel dükkandan ihtiyacım olan her şeyi almak için yeterli param yok, bu yüzden biraz para biriktirmem gerek... bazıları bu konuda bana yardımcı olabileceğini söyledi.";
			link.l2.go = "Shadowtrader_smugglers_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.seeksmugglers");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fail":
			dialog.text = "Ne diyorsun sen? Hiçbir şey anlamadım. Burada dükkan falan açmadık, saçmalık bu, ha-ha! Ticaret yapmak istiyorsan, mallarını getir, her zamanki gibi konuşuruz... Dükkanmış, ha!";
			link.l1 = "Hm...";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			AddQuestRecord("Shadowtrader", "3");
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_smugglers_1":
			dialog.text = "İndirim mi istiyorsun? Kolay. Hava karardıktan sonra liman başkanının kapısına gel. Adamımız seni karşılayacak ve doğru yere götürecek. ";
			link.l1 = "Pekala. Orada olacağım!";
			link.l1.go = "Shadowtrader_smugglers_2";		
		break;
		
		case "Shadowtrader_smugglers_2":
			pchar.questTemp.Shadowtrader.SeekTrader = "true";
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
			AddQuestRecord("Shadowtrader", "5");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			SetFunctionTimerCondition("ShadowtraderTimeSmugglers_Over", 0, 0, 2, false);
			int iNation = pchar.questTemp.Shadowtrader.nation;
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+3;
			sld = GetCharacter(NPC_GenerateCharacter("ShadowAgent_1", "citiz_"+(rand(9)+41), "man", "man", iRank, iNation, 2, true, "quest"));
			SetFantomParamFromRank(sld, iRank, true);
			GiveItem2Character(sld, "blade_04");
			EquipCharacterbyItem(sld, "blade_04");
			LAi_SetCitizenType(sld);
			sld.dialog.Filename = "Common_citizen.c";
			sld.dialog.currentnode = "First time";	
			sld.greeting = "cit_common"; 
			sld.city = pchar.questTemp.Shadowtrader.City;
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City +"_town", "goto", "goto1");
			pchar.quest.Shadowtrader_SMG.win_condition.l1 = "locator";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.location = pchar.questTemp.Shadowtrader.City + "_town";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.locator_group = "reload";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.locator = "reload10_back";
			pchar.quest.Shadowtrader_SMG.win_condition.l2 = "Night";
			pchar.quest.Shadowtrader_SMG.function = "ShadowAgent";
			DialogExit();
		break;
		// <-- Бесчестный конкурент
		//--> Торговля по закону
		case "TPZ_smugglers_1":
			dialog.text = "Ha, o tezgâhın arkasındaki serseri seni gönderdi, değil mi?";
			link.l1 = "Ne fark eder? Alabilir misin, yoksa başkasını mı bulayım?";
			link.l1.go = "TPZ_smugglers_2";
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_smugglers_2":
			dialog.text = "Ne istersen bulabilirim, anladın mı? Yeter ki ödeme düzgün olsun. Ama şu lanet vali işi çok sıkı tuttu. Artık içkiye el sürmüyoruz – şişeler çok ses çıkarıyor, bir mil öteden duyuluyor, kârı da yok denecek kadar az, ipte sallanma riski ise tavan yaptı. Yani, alınma sakın.";
			link.l1 = "Hmm... Ve sen her şeyi bulabileceğini söylüyorsun.";
			link.l1.go = "TPZ_smugglers_3";		
		break;
		
		case "TPZ_smugglers_3":
			dialog.text = "Yapabilirim! Sadece istemiyorum. Şu adam var ya, vali konağının hemen yanında yaşıyor, inanabiliyor musun? Ha-ha. Ne enayi... Ne diyordum? Ha, evet. Sessizce el altından içki satıyor. Vali beyefendinin peruklu kafasının dibinde, ha-ha. Ona sor, belki sana bir ipucu verir. Yaptığı iş küçük çaplı, çocuk oyuncağı gibi ama yine de bir şeydir.";
			link.l1 = "Pek yardımcı olmadı, ama yine de sağ ol.";
			link.l1.go = "TPZ_smugglers_4";		
		break;
		
		case "TPZ_smugglers_4":
			DialogExit();
			AddQuestRecord("TPZ", "3");
			DeleteAttribute(pchar, "questTemp.TPZ_ContraInfo");
			
			// проведаем дом Кристиана
			sld = GetCharacter(NPC_GenerateCharacter("TPZ_Kristian", "citiz_17", "man", "man", 1, FRANCE, -1, false, "quest"));
			sld.name = "Christian";
			sld.lastname = "Deluce";
			LAi_SetOwnerType(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			sld.City = "BasTer";
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону

		//--> Цена чахотки
		case "Consumption":
			dialog.text = "Burada bolca eğlenen var, eğer bir işiniz yoksa, efendim, onlarla için ya da sohbet edin. Burası oldukça kalabalık.";
			link.l1 = "Bir kez daha deneyelim. Zamanın ve merakım için sana ödeme yapacağım. Cevaplara ihtiyacım var.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			if (sti(pchar.money) >= 3002)
			{
				dialog.text = "O bana ödeyecek, ha! Benim zamanım ucuz değil, efendim, 3.000 peso artı yanlışlıkla rom dedikleri bu iğrenç içkiyi isterim.";
				link.l1 = "Anlaştık! Şimdi bana kendi adamlarından birinin burada altı ay hapiste kaldıktan sonra öldüğünü anlatsana. Ona ne oldu?";
				link.l1.go = "Consumption_2";
			}
			else
			{
				dialog.text = "You'd better fill your pockets with silver, or gold would be even better. Then come and talk; I have no time to talk with you for free.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3002);
			dialog.text = "Bunu hatırlıyorum ama neden bununla ilgilendiğini anlamıyorum. O çocuk gerçekten parmaklıklar arkasında delirdi. Sarhoş oldu ve sürekli insanları alıp götüren, kimsenin ondan güvende olmadığı bir illet hakkında saçmalıyordu. Bu illetin bir adı olduğunu ve adını yüksek sesle söylemeye bile cesaret etmemek gerektiğini söylüyordu. Eğer söylersen – o da seni gelip alırmış.";
			link.l1 = "Ve sonra ona ne oldu?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "Hikayenin tuhaf bir sonu var, señor. Başta yerliler ve denizciler onun hikayesini beğenmişti, ama sonunda bıkıp usanmışlar. Her masalda böyle olur zaten. Sonunda onu ismi söylemeye kışkırttılar. Adam direndi, karşı koydu ama alaya daha fazla dayanamadı ve sonunda ismi haykırdı\nKimse özel bir şey hissetmedi, mumlar sönmedi, ama zavallı adam ertesi sabah meyhanenin arkasında boğazı kesilmiş halde ölü bulundu.";
			link.l1 = "Burada hiçbir sihir görmüyorum. Bana adını söyle.";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "İsmi hatırlıyorum, ama lanet olsun, bunu yüksek sesle söylemeyeceğim. Bunda bir tuhaflık, bir kötülük var. Bunu görmüyor musun?";
			link.l1 = "Hey, dostum, benden dolu bir cüzdan aldın, hatırlıyor musun? O zaman bana adını söyler misin?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Ah, bu iyi bitmeyecek, señor, bana güvenin... (sesini alçaltarak) Dedi ki - Juan...";
			link.l1 = "Lanet olsun sana! Juan mı? Sıradan bir isim, burada da oldukça yaygın. Nesi bu kadar özel?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Bilmiyorum, ama bu ismi söyleyen adam öldürüldü. İçgüdülerime güveniyorum, bu isimde bir gariplik var. Sormak istediğin tek şey bu muydu?";
			link.l1 = "Sanırım öyle. Kendine bir içki ısmarlayabilirsin. Görüşürüz!";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Consumption.Contra");
			pchar.questTemp.Consumption.AskJuan = 0;
			pchar.questTemp.Consumption = "current";
			AddQuestRecord("Consumption", "6");
		break;
		//<-- Цена чахотки
		
		//Jason --> генератор сбыта бакаута
		case "bakaut":
			dialog.text = "Öyle mi? Peki. Bay Rosenkraft'ın bir miktar demir ağacına ihtiyacı var, ama en azından "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" . Yeterince yükün var mı?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "Evet, biliyorum. Mynheer Rosenkraft'ı nerede bulabilirim?";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Hm. Şu anda o kadar param yok.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			dialog.text = "Öyleyse mynheer Rosenkraft'ı rahatsız etme. Yeterli yükün olduğunda gel.";
			link.l1 = "Pekâlâ.";
			link.l1.go = "exit";
		break;
		
		case "bakaut_1":
			dialog.text = "Galyonu   kıyılara   yakın   seyredecek "+XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen")+" birkaç gündür burada. O yüzden geç kalma – başka bir adaya yelken açabilir.";
			link.l1 = "Pekala, hızlanacağım. Teşekkürler!";
			link.l1.go = "bakaut_2";
		break;
		
		case "bakaut_2":
			DialogExit();
			sld = characterFromId("Rozencraft");
			sld.DeckDialogNode = "bakaut";
			DeleteAttribute(sld, "DontDeskTalk"); // можно выслать шлюпку
			pchar.GenQuest.Bakaut.Info = "true";
			ReOpenQuestHeader("Bakaut");
			AddQuestRecord("Bakaut", "1");
			AddQuestUserData("Bakaut", "sIsland", XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen"));
			AddQuestUserData("Bakaut", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Bakaut.DaysQty)));
			AddQuestUserData("Bakaut", "sQty", FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)));
			// таймер
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1 = "Timer";
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.function = "Bakaut_RozencraftRemove";
		break;
		// <-- генератор сбыта бакаута
		
		//--> прибыла инспекция на Святом Милосердии
		case "SantaMisericordia_1":
			dialog.text = "Ve yarına kadar hayatta kalmam lazım. Lanet olası 'Mercy' şehirde. Git.";
			link.l1 = "Büyük bir olay...";
			link.l1.go = "exit";
		break;
		//<-- прибыла инспекция на Святом Милосердии
	}
}
