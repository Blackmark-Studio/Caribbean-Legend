void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bir hata var. Geliştiricilere mutlaka haber ver.";
			link.l1 = "Tamam";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarginCap":
			dialog.text = "Selam, kaptan. Benden bir şey ister misin?";
			link.l1 = "Evet. Aynen öyle. "+GetAddress_FormToNPC(NPChar)+". Gemisinde oldukça ilgimi çeken bir yolcu var. Adı "+pchar.GenQuest.Marginpassenger.q1Name+". Yolcunun benim yolcum olmasını istiyorum. Eğer senin için de uygunsa, yollarımızı ayıralım ve bir daha asla karşılaşmayalım.";
			link.l1.go = "MarginCap_1";
		break;
	
		case "MarginCap_1":
			dialog.text = "Öyle mi? Peki ya hayır dersem ne olacak?";
			link.l1 = "O halde, şu anda tam sana doğrultulmuş toplarımdan birkaç salvo ile fikrini değiştirmeye zorlayacağım. Şansını fazla zorlama, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "MarginCap_2";
		break;
		
		case "MarginCap_2":
			int MCparam = (7-sti(RealShips[sti(pchar.ship.type)].Class))*100+sti(pchar.ship.Crew.Morale)+sti(pchar.Ship.Crew.Exp.Sailors)+sti(pchar.Ship.Crew.Exp.Cannoners)+sti(pchar.Ship.Crew.Exp.Soldiers);
			int NPCparam = (7-sti(RealShips[sti(npchar.ship.type)].Class))*100+sti(npchar.ship.Crew.Morale)+sti(npchar.Ship.Crew.Exp.Sailors)+sti(npchar.Ship.Crew.Exp.Cannoners)+sti(npchar.Ship.Crew.Exp.Soldiers);
			if (MCparam > NPCparam)//отдаст сам
			{
				dialog.text = "O zaman başka seçeneğim yok. Mürettebatımın kaderi benim için bir adamın kaderinden daha değerli. Ama bu kadar kolay kurtulamayacaksın! Bunu asla unutmayacağım!";
				link.l1 = "Sakin ol, kalp krizi geçirmeden kendini toparla... Yeni yolcumu bana getir!";
				link.l1.go = "MarginCap_3";
			}
			else
			{
				dialog.text = "Gemi­mden ayrıl­sanız iyi olur, efendim, henüz izin veriyorken. Beni korkutmaya kalkmayın. Ve sakın gemime saldırmaya cesaret etmeyin, yoksa anında püskürtülürsünüz. Hâlâ iyi bir ruh halindeyken defolun!";
				link.l1 = "Seni uyardım. Geliyorum. Yakında görüşürüz, "+GetAddress_FormToNPC(NPChar)+"!";
				link.l1.go = "MarginCap_4";
			}
		break;
	
		case "MarginCap_3":
			DialogExit();
			npchar.Dialog.CurrentNode = "MarginCap_repeat";
			//отдаем пассажира
			sld = GetCharacter(NPC_GenerateCharacter("MarginPass", pchar.GenQuest.Marginpassenger.model, pchar.GenQuest.Marginpassenger.sex, pchar.GenQuest.Marginpassenger.ani, 2, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true, "quest"));
			sld.Dialog.Filename = "Quest\Marginpassenger.c";
			sld.Dialog.currentnode = "MarginPass";
			sld.name = pchar.GenQuest.Marginpassenger.q1Name;
			sld.lastname = "";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			Map_ReleaseQuestEncounter(npchar.id);
			npchar.Abordage.Enable = false; // запрет абордажа
			npchar.ShipEnemyDisable = true;
			npchar.AlwaysFriend = true;
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_4":
			DialogExit();
			NextDiag.CurrentNode = "MarginCap_repeat";
			pchar.GenQuest.Marginpassenger.Mustboarding = "true";
			AddQuestRecord("Marginpassenger", "5");
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_repeat":
			dialog.text = "Bu konuşmayı zaten yaptık, hatırlıyor musun? Gemimden defol!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarginCap_repeat";
		break;
		
		case "MarginCap_abordage":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Mustboarding"))
			{
				dialog.text = "Lanet olası herif! Yaptıkların için cehennemde yan!";
				link.l1 = "Sana yolcuyu huzur içinde teslim etme fırsatı verdim... ama teklifimi reddettin. Şimdi suç tamamen sende!";
				link.l1.go = "MarginCap_abordage_1";
			}
			else
			{
				dialog.text = "Ah, alçak herif! Neden bu sakin gemiye saldırdın? Altınımız ya da değerli eşyamız yok!";
				link.l1 = "Ama geminizde değerli biri var..."+pchar.GenQuest.Marginpassenger.q1Name+". Yolcunu istiyorum.";
				link.l1.go = "MarginCap_abordage_2";
			}
		break;
		
		case "MarginCap_abordage_1":
			dialog.text = "Sen... pis korsansın!";
			link.l1 = "Daha az konuş, dostum...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_2":
			dialog.text = "Ve bu yüzden mi gemimde katliam yaptın? Birçok adam öldü! Korsan!";
			link.l1 = "Daha az konuş, dostum...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_3":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Marginpassenger_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "MarginNeed":
			dialog.text = "Ne istiyorsun, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Sen misin "+pchar.GenQuest.Marginpassenger.q2Name+"?";
			link.l1.go = "MarginNeed_1";
		break;
		
		case "MarginNeed_1":
			dialog.text = "Evet, benim. Başvuru yapmak mı istiyorsun? O zaman bilmelisin ki...";
			link.l1 = "Bir saniye bekleyin, efendim. Benim biraz farklı bir ricam olacak...  Tanıdığınız biri var mı, adı "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1.go = "MarginNeed_2";
		break;
		
		case "MarginNeed_2":
			switch (pchar.GenQuest.Marginpassenger.sex)
			{
				case "woman":
					dialog.text = "Evet, onu tanıyorum... Tabii ki tanıyorum! Ne oldu?";
					link.l1 = "Kendini son derece tatsız bir durumda bulmuş: gemisi korsanlar tarafından ele geçirilmiş. Neyse ki, onların gemisine çıkıp zavallı kadını kurtarma fırsatım oldu. Bana senin adını söyledi ve işte buradayım.";
					link.l1.go = "MarginNeed_woman";
				break;
				case "man":
					dialog.text = "Evet, bu adamı çok iyi tanıyorum. Ne oldu?";
					link.l1 = "Kendini hiç de hoş olmayan bir durumda bulmuş: gemisi korsanlar tarafından ele geçirilmiş. Neyse ki, onların gemisine çıkıp bu esiri kurtarma fırsatım oldu. Bana senin adını söyledi ve işte buradayım.";
					link.l1.go = "MarginNeed_man";
				break;
			}
		break;
		
		case "MarginNeed_woman":
			dialog.text = "Tanrım! Şimdi nerede o? Neden onu buraya getirmedin?";
			link.l1 = "O güvende. Ve soruna gelince... o kadar basit değil. Onu kendim de eve götürebilirdim, ama bu fırsatı sana verebilirim. Tabii ki, küçük bir ücret karşılığında.";
			link.l1.go = "MarginNeed_woman_1";
		break;
		
		case "MarginNeed_woman_1":
			dialog.text = "Hm... Anlamıyorum...";
			link.l1 = "Why don't you? You pay me in gold, I give you the girl, and you can use this situation to your advantage... You want to marry her, am I right? And I'll repair my ship with those coins; she was damaged during that fight with the pirates.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_man":
			dialog.text = "Tanrım! Şimdi nerede o? Neden onu buraya getirmedin?";
			link.l1 = "O güvende. Ve soruna gelince... o kadar basit değil. Onu kendim de eve götürebilirdim, ama ailesiyle ilgili kendi çıkarların olduğunu göz önünde bulundurarak, bu fırsatı sana verebilirim. Tabii ki, mütevazı bir ücret karşılığında.";
			link.l1.go = "MarginNeed_man_1";
		break;
		
		case "MarginNeed_man_1":
			dialog.text = "Hm... Anlamıyorum...";
			link.l1 = "Why don't you? You pay me in gold, I'll give you your friend, and you'll be able to use this situation to your advantage. I have some information, you know... I'll repair my ship with those coins; she was damaged during that fight with pirates.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_money":
			dialog.text = "Pekâlâ, pekâlâ... peki, ne kadar istiyorsun?";
			link.l1 = "Unutma, ben peso değil, doblon istiyorum.";
			link.l1.go = "MarginNeed_money_1";
		break;
		
		case "MarginNeed_money_1":
			dialog.text = "Peki, peki... Kaç doblon istiyorsun?";
			Link.l1.edit = 1;			
			link.l1 = "";
			link.l1.go = "MarginNeed_money_2";
		break;
		
		case "MarginNeed_money_2":
		iTemp = sti(dialogEditStrings[1]);
		int iSum = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*5*stf(pchar.GenQuest.Marginpassenger.Chance));
		if (iTemp <= 0)
		{
			dialog.text = "Çok komik. Peki, şakanın gerçekten komik olduğunu varsayalım. Hoşça kal!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 0 && iTemp <= iSum)
		{
			if (hrand(2) > 1) // Addon-2016 Jason уменьшаем раздачу дублонов
			{
				dialog.text = "Pekala, kabul ediyorum. Gerekli miktar bende var. Nerede "+pchar.GenQuest.Marginpassenger.q1Name+"?";
				link.l1 = "Şu anda iskelede olmalı. Yani gidip yolcuyu alabilirsin.";
				link.l1.go = "MarginNeed_dublon";
			}
			else
			{
				dialog.text = "Üzgünüm, ama o kadar çok dublonum yok. Peso kabul eder misiniz?";
				link.l1 = "Altın istiyorum, ama sanırım gemi ustası pesoya da razı olur... Ver onları bana.";
				link.l1.go = "MarginNeed_peso";
				link.l2 = "Hayır, sadece doblon isterim.";
				link.l2.go = "MarginNeed_dublon_exit";
			}
			break;
		}
		if (iTemp > iSum && iTemp < 1000)
		{
			dialog.text = "Ne yazık ki, öyle bir param yok. Bu yüzden teklifini kabul edemem, ne kadar istesem de.";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 1000 && iTemp < 3000)
		{
			dialog.text = "Beyefendi, ne dediğinizin farkında mısınız? Bu miktarın fazlasıyla yüksek olduğunun farkında mısınız? Defolun buradan!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
			dialog.text = "Pekala... Efendim, derhal bir doktora görünmelisiniz. Görünüşe göre ateşiniz çok yüksek ya da... her neyse, bir doktora ihtiyacınız var. Ve ben de çok meşgulüm. Hoşça kalın!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_dublon":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1]);
			TakeNItems(pchar, "gold_dublon", iTemp);
			AddQuestRecord("Marginpassenger", "9");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
		
		case "MarginNeed_peso":
			dialog.text = "İşte burada, istediğin gibi tüm miktar peso olarak... Nerede "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1 = "Şu anda iskelede olmalı. Yani gidip yolcuyu alabilirsin.";
			link.l1.go = "MarginNeed_peso_1";
		break;
		
		case "MarginNeed_peso_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1])*500;
			AddMoneyToCharacter(pchar, iTemp);
			AddQuestRecord("Marginpassenger", "10");
			AddQuestUserData("Marginpassenger", "sSum", FindRussianMoneyString(iTemp));
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
		break;
		
		case "MarginNeed_dublon_exit":
			dialog.text = "Teklifini kabul edemem, keşke edebilseydim. Elveda!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Marginpassenger", "11");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "MarginPass":
			dialog.text = "Ne... Ne oluyor burada?!";
			link.l1 = "Çok basit, "+NPCharSexPhrase(NPChar,"kanka","kız")+". Artık benim değerli yolcumsun. Korumam altındasın. Sakın karşı koymaya kalkma, yoksa kendini ambarın dibinde bulursun.";
			link.l1.go = "MarginPass_1";
		break;
		
		case "MarginPass_1":
			dialog.text = "Yani, senin esirin miyim demek istiyorsun?";
			link.l1 = "Ah, hayır. Tabii ki değil. Bir mahkum değil, değerli bir misafir. En kıymetli misafirimiz...";
			link.l1.go = "MarginPass_2";
		break;
		
		case "MarginPass_2":
			dialog.text = "Sen... yaptıklarının bedelini ödeyeceksin!";
			link.l1 = "Yine yanılıyorsun,"+NPCharSexPhrase(NPChar,", dostum",", sevgili")+". Ödemeyeceğim, ama bana ödenecek. Yeter konuştuğun, kamarana git!";
			link.l1.go = "MarginPass_3";
		break;
		
		case "MarginPass_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "", "", "none", "", "", "", 1.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.Marginpassenger_InWorldOver.over = "yes"; //снять прерывание
			pchar.quest.Marginpassenger_Sink.over = "yes"; //снять прерывание
			pchar.GenQuest.Marginpassenger = "take";
			if (rand(2) == 1) pchar.GenQuest.Marginpassenger.lose = "true";
			else Marginpassenger_CreateNeedman();
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Boarding")) AddQuestRecord("Marginpassenger", "6");
			else AddQuestRecord("Marginpassenger", "4");
			AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
