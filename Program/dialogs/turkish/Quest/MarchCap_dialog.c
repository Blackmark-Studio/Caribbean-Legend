void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iQty;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bir hata var. Geliştiricilere mutlaka haber ver.";
			link.l1 = "Tamam.";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarchCap":
			pchar.quest.MarchCapOver.over = "yes"; //снять прерывание
			dialog.text = "Buyurun, kaptan. Teklifimin ayrıntılarını konuşalım. Bunu neden herkesin içinde konuşmak istemediğimi anlayacaksınız.";
			link.l1 = "Devam edin, efendim. Sizi dinliyorum.";
			link.l1.go = "MarchCap_1";
		break;
		
		case "MarchCap_1":
			pchar.GenQuest.MarchCap.Goods = SelectMarchCapGoods1();//целевой товар
			switch (rand(2))
			{
				case 0: //конвой у острова, установка параметров
					pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					while(pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					}
					pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
					while(pchar.GenQuest.MarchCap.Island.Shore == "")
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
						pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
						if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore)) pchar.GenQuest.MarchCap.Island.Shore = "";
					}
					pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island)+3;
					dialog.text = "Şunu öğrenmeyi başardım ki, "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" bir bayrak altında küçük bir ticaret konvoyu "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+", iki ticaret gemisi ve bir muhafız gemisi,   yakından geçecek "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+", bu  çok da uzak değil "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+". Tüccarların çok fazla "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" ambarlarında. Bu bilgiyi kullanmamak aptallık olurdu, kaptan\nSeninle ben muhafızlarla kolayca başa çıkabiliriz ve yükü kendimize alırız. Ne dersin, var mısın?";
					link.l1 = "Kulağa cazip geliyor. Evet derim!";
					link.l1.go = "MarchCap_1_1";
					link.l2 = "Bazı"+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" benim   ile aramı bozmak için yeterli değil "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+"Hayır, bunu yapmayacağım! Elveda, efendim, beni durdurmaya bile kalkmayın!";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 1: //энкаунтер на глобалке, установка параметров
					pchar.GenQuest.MarchCap.Startcity = SelectAnyColony(pchar.GenQuest.MarchCap.basecity);
					pchar.GenQuest.MarchCap.Finishcity = SelectAnyColony2(pchar.GenQuest.MarchCap.basecity, pchar.GenQuest.MarchCap.Startcity);
					pchar.GenQuest.MarchCap.DaysQty = 5+hrand(5);
					dialog.text = "Bunu   öğrenmeyi başardım,   "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" bir bayrak altında küçük bir ticaret konvoyu "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+", iki ticaret gemisi ve bir muhafız gemisi,   "+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Startcity+"Gen")+" to "+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Finishcity+"Acc")+". Tüccarların bolca var "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" ambarlarında. Bu bilgiyi kullanmamak aptallık olurdu, kaptan.\nSeninle ben muhafızlarla kolayca başa çıkabilir ve yükü kendimize alabiliriz. En zoru, onları bu iki koloni arasındaki açık denizde bulmak. Yani, var mısın?";
					link.l1 = "Kulağa hoş geliyor. Evet derim!";
					link.l1.go = "MarchCap_2_1";
					link.l2 = "Bazı "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+"   benim   ile olan ilişkilerimi mahvetmem için yeterli değil "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+" Hayır, bunu yapmayacağım! Elveda, efendim, beni durdurmaya bile kalkışmayın!";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 2: //одиночный пиратский кулсейлор у бухты, установка параметров
					pchar.GenQuest.MarchCap.Goods = GOOD_GOLD + hrand(makeint(GOOD_SILVER - GOOD_GOLD));
					pchar.GenQuest.MarchCap.GoodsQty = sti(pchar.rank)*50+170+rand(30);
					if (sti(pchar.GenQuest.MarchCap.GoodsQty) > 1600) pchar.GenQuest.MarchCap.GoodsQty = 1500+rand(100);
					pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					while(pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					}
					pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
					while(pchar.GenQuest.MarchCap.Island.Shore == "")
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
						pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
						if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore)) pchar.GenQuest.MarchCap.Island.Shore = "";
					}
					pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island)+1;
					pchar.GenQuest.MarchCap.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);//пират
					pchar.GenQuest.MarchCap.ShipType = SelectPirateShipType();
					pchar.GenQuest.MarchCap.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.MarchCap.ShipType));
					dialog.text = "Bir korsan hakkında bilgilendirildim, adı "+GetName(NAMETYPE_ORIG,pchar.GenQuest.MarchCap.PirateName,NAME_NOM)+". Bu haydut yakın zamanda çaldı "+RandPhraseSimple(RandPhraseSimple("İngilizce","French"),RandPhraseSimple("İspanyol","Dutch"))+" ve ambarını doldurdu "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+". Ama ne yazık ki, gemisi "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.ShipType),"Name")+"Acc"))+" ağır hasar aldı, bu yüzden tamir etmek için biraz zaman harcaması gerekti.\nŞu anda "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+" of "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+"   Sanırım yaklaşık    "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+"   direkleri ve gövdedeki delikleri onarması için. Acele edersek ve hepimiz   "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" bizim olacak\nBu korsanla tek başıma baş edemem, çok yetenekli bir denizci ve dövüşçü, ama ikimiz birlikte onun deneyimine rağmen üstesinden gelebiliriz. O halde, var mısın yok musun?";
					link.l1 = "Kulağa cazip geliyor. Evet derim!";
					link.l1.go = "MarchCap_3_1";
					link.l2 = "Hm. Görünen o ki bu ödül sadece senin değil, ikimizin de erişemeyeceği bir yerde. Hayır, bunu yapmayacağım. Elveda, bayım, beni durdurmaya bile kalkışma!";
					link.l2.go = "MarchCap_exit";
				break;
			}
		break;
		
		case "MarchCap_1_1":
			dialog.text = "Sana güvenebileceğimi biliyordum! Bir dakika bile kaybetmeyelim. Gemine git ve önden git, ben seni takip edeceğim. Yelken açma vakti geldi!";
			link.l1 = "Demir almamız için emir verin, kaptan!";
			link.l1.go = "MarchCap_1_2";
		break;
		
		case "MarchCap_1_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "Timer";
			pchar.quest.MarchCap1_1.win_condition.l1.date.hour  = sti(GetTime()+rand(10));
			pchar.quest.MarchCap1_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l2 = "location";
			pchar.quest.MarchCap1_1.win_condition.l2.location = pchar.GenQuest.MarchCap.Island;
			pchar.quest.MarchCap1_1.function = "MarchCap1_CreateConvoy";
			SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty)+2, false); //таймер на нахождение
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "1");
			AddQuestUserData("MarchCap", "sShore", XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen"));
			AddQuestUserData("MarchCap", "sIsland", XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		break;
		
		case "MarchCap_TimeOver":
			dialog.text = "Ve neden seninle iş birliği yaptım, kaptan? Senin yüzünden çok değerli bir ganimeti kaybettik! Bir dahaki sefere en iyisi tek başıma yelken açayım...";
			link.l1 = "Senin suçun, benim değil. Hoşça kal.";
			link.l1.go = "MarchCap_Talk_exit";
			pchar.GenQuest.MarchCap = "late";
		break;
		
		case "MarchCap_Talk_exit":
			pchar.quest.MarchCap1_fail2.over = "yes"; //снять прерывание
			pchar.quest.MarchCap1_fail1.over = "yes"; //снять прерывание
			pchar.quest.MarchCap1_fail.over = "yes"; //снять прерывание
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			DeleteAttribute(npchar, "AlwaysFriend");
			npchar.DontDeskTalk = true;
			if (CheckAttribute(pchar, "GenQuest.MarchCap.Deck"))
			{
				PChar.quest.Munity = "Deads";
				LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			}
			else
			{
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				chrDisableReloadToLocation = false;
			}
			RemoveCharacterCompanion(pchar, npchar);
			npchar.location = pchar.location;
			if (pchar.GenQuest.MarchCap == "late") AddQuestRecord("MarchCap", "2");
			if (pchar.GenQuest.MarchCap == "bad") AddQuestRecord("MarchCap", "5");
			if (pchar.GenQuest.MarchCap == "poor" || pchar.GenQuest.MarchCap == "good" || pchar.GenQuest.MarchCap == "exellent")
			{
				iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
				iTemp = iQty-sti(pchar.GenQuest.MarchCap.CapPart);
				RemoveCharacterGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods), iQty);
				AddCharacterGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods), iTemp);
				if (pchar.GenQuest.MarchCap == "poor") AddQuestRecord("MarchCap", "6");
				if (pchar.GenQuest.MarchCap == "good") AddQuestRecord("MarchCap", "7");
				if (pchar.GenQuest.MarchCap == "exellent") AddQuestRecord("MarchCap", "8");
			}
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
			CloseQuestHeader("MarchCap");
			DeleteAttribute(pchar, "GenQuest.MarchCap");
		break;
		
		case "MarchCap_AfterBattle":
			iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty))*sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			pchar.GenQuest.MarchCap.CapPart = iQty/sti(pchar.GenQuest.MarchCap.Parts);
			if (iTemp < 50)
			{
				dialog.text = "Sen tam bir beceriksizsin, kaptan! Payımızı alamadık! Ve hepsi senin yüzünden! Başarısızlığımızın sebebi sensin, kahrolasıca!";
				link.l1 = "Öyle mi? Kendine bak! Savaşta bana yardım etmedin! Seninle sadece zamanımı harcadım... Gemimden defol!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 50 && iTemp < 500)
			{
				dialog.text = "Bu baskın beklediğim kadar başarılı olmadı, ganimetimiz gerçekten çok az... Neyse kaptan, şu kırıntıları paylaşalım da birbirimize veda edelim.";
				link.l1 = "Eğer gökyüzündeki kuşları saymak yerine bana yardım etseydin, baskın başarılı olurdu... Al payını - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+" ve kaybol!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 500 && iTemp < 1500)
			{
				dialog.text = "Aferin, kaptan! Dediğim gibi – o tüccarların ambarlarını boşaltmak pek de zor olmadı, ha-ha... Ödül ise "+FindRussianQtyString(iQty)+"  parça. Benim payım  "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "Doğru. "+npchar.name+". Hiçbir itirazım yok. Sandallar şu anda yükleniyor. Belki gelecekte birlikte başka bir sefere çıkarız? Bana uygun bir yol arkadaşı gibi görünüyorsun.";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "Mükemmel, kaptan! Dediğim gibi - o tüccarların ambarlarını boşaltmak oldukça kolaydı, ha-ha... Ödül çok büyük, beklediğimden de fazla. Bu "+FindRussianQtyString(iQty)+" para. Benim payım "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "Doğru, "+npchar.name+". Hiçbir itirazım yok. Sandallar şu anda yükleniyor. Belki gelecekte bir baskını daha birlikte yaparız? Bana uygun bir yol arkadaşına benziyorsun.";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		//если будет время - здесь создаем ещё одного клона с уникальным ИД для продолжения квеста
		case "MarchCap_Deck_continue":
			dialog.text = "Bir ihtimal var, kaptan. Eğer kendi başıma peşine düşemeyeceğim kârlı bir ipucu daha bulursam, seni bulurum. Savaşta da bana güvenilir bir yoldaş gibi görünüyorsun.";
			link.l1 = "Güzel! Hoşça kal, kaptan. İyi şanslar!";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_2_1":
			dialog.text = "Sana güvenebileceğimi biliyordum! Bir dakika bile kaybetmeyelim. Gemine git ve önden git, ben seni takip edeceğim. Yelken açma zamanı geldi!";
			link.l1 = "Demir almamızı emredin, kaptan.";
			link.l1.go = "MarchCap_2_2";
		break;
		
		case "MarchCap_2_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "Timer";
			pchar.quest.MarchCap1_1.win_condition.l1.date.hour  = sti(GetTime()+rand(10));
			pchar.quest.MarchCap1_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.function = "MarchCap2_CreateConvoy";
			pchar.GenQuest.MarchCap.WdmEnc = "true";
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "10");
			AddQuestUserData("MarchCap", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Startcity+"Gen"));
			AddQuestUserData("MarchCap", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Finishcity+"Acc"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		break;
		
		case "MarchCap_3_1":
			dialog.text = "Sana güvenebileceğimi biliyordum! Bir dakika bile kaybetmeyelim. Gemine git ve bana yol göster. Yelken açma zamanı geldi!";
			link.l1 = "Demir almalarını emredin, kaptan.";
			link.l1.go = "MarchCap_3_2";
		break;
		
		case "MarchCap_3_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "location";
			pchar.quest.MarchCap1_1.win_condition.l1.location = pchar.GenQuest.MarchCap.Island;
			pchar.quest.MarchCap1_1.function = "MarchCap3_CreatePirate";
			SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty), false); //таймер
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			pchar.GenQuest.MarchCap.Pirate = "true";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "11");
			AddQuestUserData("MarchCap", "sShore", XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen"));
			AddQuestUserData("MarchCap", "sIsland", XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
			AddQuestUserData("MarchCap", "sName1", GetName(NAMETYPE_ORIG, pchar.GenQuest.MarchCap.PirateName, NAME_NOM));
		break;
		
		case "MarchCap_DieHard":
			dialog.text = "Korkaksın, kahretsin seni! Savaş alanından az önce kaçtın!";
			link.l1 = "Peki, ne yapmamı bekliyordun? O korsanın gemimi batırmasına izin mi verecektim? Asla, aptalca ölüp gitmektense, hayatta kalıp korkak olmayı tercih ederim!";
			link.l1.go = "MarchCap_DieHard_1";
		break;
		
		case "MarchCap_DieHard_1":
			dialog.text = "Ve ben neden seninle iş birliği yaptım, kaptan? Korkusuzca gemi basan bir adam bulmalıydım!";
			link.l1 = " Şimdi senden gemimden ayrılmanı istiyorum - onu tamir etmem gerekiyor.";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_AfterBattleGold":
			iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty))*sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			pchar.GenQuest.MarchCap.CapPart = iQty/sti(pchar.GenQuest.MarchCap.Parts);
			if (iTemp < 10)
			{
				dialog.text = "Sen tam bir beceriksizsin, kaptan! Ödülümüzden tek bir parça bile alamadık! Ve bunun hepsi senin yüzünden! Başarısızlığımızın sebebi sensin, kahrolası herif!";
				link.l1 = "Öyle mi? Kendine bak! Savaşta bana hiç yardım etmedin! Seninle sadece zamanımı boşa harcadım... Gemimden defol!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 10 && iTemp < 100)
			{
				dialog.text = "Pekâlâ, bu baskın beklediğim kadar başarılı olmadı, ganimetimiz gerçekten çok az... Neyse, kaptan, şu kırıntıları paylaşalım ve birbirimize veda edelim.";
				link.l1 = "Eğer gökyüzündeki kuşları saymak yerine bana yardım etseydin, baskın başarılı olurdu... Al payını - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+" ve kaybol!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 100 && iTemp < 500)
			{
				dialog.text = "Aferin, Kaptan! Ödülün "+FindRussianQtyString(iQty)+" parça. Benim payım "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "Doğru. "+npchar.name+". Bir itirazım yok. Sandallar şu anda yükleniyor. Belki tekrar karşılaşırız...";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "Mükemmel, kaptan! Dediğim gibi - oldukça kolaydı, ha-ha... Ödül çok büyük, beklediğimden de fazla. Bu "+FindRussianQtyString(iQty)+"  parça. Benim payım  "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "Doğru, "+npchar.name+". Hiçbir itirazım yok. Sandallar şu anda yükleniyor. Belki gelecekte birlikte başka bir baskına çıkarız? Bana uygun bir yol arkadaşı gibi görünüyorsun.";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "MarchCap_repeat":
			dialog.text = ""+GetAddress_Form(NPChar)+", gemine git. Sohbet edecek vaktimiz yok. Hadi yelken açalım!";
			link.l1 = "Evet, evet, tabii ki, haklısın.";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarchCap_repeat";
		break;
		
		case "MarchCap_exit":
			dialog.text = "Hm... Yapmayacağım. Defol! Kendim hallederim!";
			link.l1 = "Pekâlâ, o zaman iyi yolculuklar...";
			link.l1.go = "MarchCap_DeckExit";
		break;
		
		case "MarchCap_DeckExit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(npchar, "AlwaysFriend");
			npchar.DontDeskTalk = true;
			DeleteAttribute(pchar, "GenQuest.MarchCap");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

int SelectMarchCapGoods1()
{
	int iGoods;
	switch (hrand(5))
	{
		case 0: iGoods = GOOD_EBONY; break;
		case 1: iGoods = GOOD_MAHOGANY; break;
		case 2: iGoods = GOOD_CINNAMON; break;
		case 3: iGoods = GOOD_COFFEE; break;
		case 4: iGoods = GOOD_CHOCOLATE; break;
		case 5: iGoods = GOOD_TOBACCO; break;
	}
	return iGoods;
}

int SelectPirateShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 5;
	if(iRank >= 12 && iRank < 21) iClass = 4;
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}
