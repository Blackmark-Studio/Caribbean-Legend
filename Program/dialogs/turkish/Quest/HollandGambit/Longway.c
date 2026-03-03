// китаец Лонгвэй, подручный Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Chuanzhang. Benim adım Longway. Longway gemisini emrinize veriyor. Longway de artık sizin emrinizde. Mynheer Rodenburg'un emriyle.";
			link.l1 = "Selam, Longway. Charles de Maure, hizmetinizde. Jacob van Berg'i ortadan kaldırma operasyonuyla ilgili bir bilgin var mı?";
			link.l1.go = "Longway_friend";
			link.l2 = "Seni görmek güzel, Longway. Benim adım Charles de Maure. Zaman kaybetmeye gerek yok – Bay Rodenburg hızlı ve kaliteli işi takdir eder. Jacob van Berg şu anda nerede saklanıyor?";
			link.l2.go = "Longway_neutral";
			link.l3 = "Pekâlâ, benim adım da Charles de Maure! Umarım bizimkiler iyi anlaşır! Peki, Bay Longway, lütfen söyleyin, bizimkiler Jacob van Berg’i nerede aramalı?";
			link.l3.go = "Longway_enemy";
			NextDiag.TempNode = "First time";
			pchar.questTemp.HWIC.Holl.JacobCity = SelectJacobCity();
		break;
		
//-----------------------------------------------за Голландию-----------------------------------------------
		case "Longway_neutral":
			dialog.text = "Longway emin ki birlikte iyi çalışacağız, chuanzhang. Jacob van Berg şu anda "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+". Onunla yerel meyhanede bir buluşma ayarladım. Orada olacak.";
			link.l1 = "Hadi yelken açalım!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayNeutral = "true";//признак враждебности китайца
		break;
		
		case "Longway_enemy":
			dialog.text = "Longway için mynheer Rodenburg'un emri... Jacob van Berg şu anda "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+". Onunla yerel meyhanede bir buluşma ayarladım. Orada olacak.";
			link.l1 = "Hadi yelken açalım!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayEnemy = "true";//признак враждебности китайца
			Notification_Approve(false, "Longway");
		break;
		
		case "Longway_friend":
			dialog.text = "Longway elinden geleni yapacak, chuanzhang. Ve Jacob van Berg şu anda "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+". Onunla yerel meyhanede bir buluşma ayarladım. Orada olacak.";
			link.l1 = "Hadi yelken açalım!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayFriend = "true";//признак враждебности китайца
			Notification_Approve(true, "Longway");
		break;
		
		case "Longway_JacobGo":
			//Лонгвэя - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 18;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", -1);
			AddQuestRecord("Holl_Gambit", "1-8");
			ForceHeroAutolevel(npchar);
			SetCharacterPerk(npchar, "Captain");
			AddQuestUserData("Holl_Gambit", "sCity", XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat"));
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Holl.JacobCity, true);
			AddLandQuestMark(characterFromId(""+pchar.questTemp.HWIC.Holl.JacobCity+"_tavernkeeper"), "questmarkmain");
			pchar.questTemp.HWIC.Holl = "JacobOnMain";
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 30, false);
			}
			else SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 15, false);
		break;
		
		case "hired":
			dialog.text = "Longway ne yapabilir, chuanzhang?";
			link.l1 = "Şimdilik bir şey yok.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			if (pchar.questTemp.HWIC.Holl == "MirageFail")
			{
				dialog.text = "Sen ahmak, aptal Moğol, chuanzhang! Bize kolay bir görev verilmişti - 'Mirage'ı ele geçirmek, hem de 'Meifeng'i kaybetmeden. Kaptansızken kolay bir hedefti, ama sen işi beceremedin\nLongway artık sana hizmet etmeyecek, seni de bir daha görmeyecek. Longway, Mynheer Rodenburg'un da bu kararını onaylayacağından emin.";
				link.l1 = "Sana ve efendine lanet olsun!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-10");
			}
			if (pchar.questTemp.HWIC.Holl == "JacobOnMain" || pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "Sen ne aptal bir Moğol'sun, chuanzhang! Kendi işlerinle uğraşırken Jacob van Berg'le buluşmak yerine çok fazla zaman kaybettik. O artık çoktan gitti "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+"\nGörevi tamamlayamadınız. Longway artık size hizmet etmek de, sizi tekrar görmek de istemiyor. Longway, Mynheer Rodenburg'un da bu kararını onaylayacağından emin.";
				link.l1 = "Sana da efendine de lanet olsun!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-9");
			}
			if (pchar.questTemp.HWIC.Holl == "lateVillemstad")
			{
				dialog.text = "Chuanzhang, çok fazla zaman harcadın ve hiçbir sonuç alamadın. Burası senin gemin değil ve Longway de senin ırgatın değil. Longway Willemstad'a dönüyor\nLongway artık sana hizmet etmeyecek ve seni bir daha görmek istemiyor. Longway, Bay Rodenburg'un da bu kararını onaylayacağından emin.";
				link.l1 = "Sen de efendin de cehenneme gitsin!";
				link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)//если сам на Мейфенг
			{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "Boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i=1; i < COMPANION_MAX; i++)
				{
					int iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Holl.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Longway_hire":
			PlaySound("Voice\English\hambit\Longway-03.wav");
			dialog.text = "Chuanzhang, Longway Mynheer Rodenburg'dan ayrıldı. Longway ona asla geri dönmeyecek. Sen Longway'e iyi davrandın ve cesur bir chuanzhang'sın. Longway, Mürettebatına hizmetkarın olarak katılmak istiyor, Kaptanım.";
			link.l1 = "Bir hizmetçi olarak değil, bir subay olarak! Gemimize hoş geldin, dostum!";
			link.l1.go = "Longway_hire_1";	
			link.l2 = "Teşekkürler Longway, gerek yok. Sen özgür bir adamsın. Hizmetine ihtiyacım yok.";
			link.l2.go = "Longway_exit";	
		break;
		
		case "Longway_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 30.0);
			AddQuestRecord("Holl_Gambit", "1-37");
		break;
		
		case "Longway_hire_1"://нанимаем китайца
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
		
			npchar.CanTakeMushket = true;
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Longway_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 200, 200);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddQuestRecord("Holl_Gambit", "1-38");
			ForceHeroAutolevel(npchar);
			
			//Sinistra - квест Лонгвэя "Путеводная звезда"
			PChar.quest.PZ_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Start.win_condition.l1.location = "Curacao";
			PChar.quest.PZ_Start.win_condition = "PZ_Start";
		break;
		
//---------------------------------------------против всех-------------------------------------------------
		case "Longway_abordage":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			dialog.text = "Neden durdun? Öldür beni. Longway yoruldu, Longway ölmek istiyor. Xing... beni affet.";
			link.l1 = "O kadar acele etme, Çinli. İstesem seni öldürebilirim, ama önce seninle konuşmam gerek. Kaderin bundan sonra ne yapacağına bağlı. Şimdilik, ambarıma hoş geldin!";
			link.l1.go = "Longway_abordage_1";			
		break;
		
		case "Longway_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-45");
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "LongwayPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveLongwayOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Longway_prisoner":
			DelLandQuestMark(npchar);
			dialog.text = "";
			link.l1 = "Artık kulaklarımda çınlayan çelik sesleri olmadan konuşabiliriz. Dinle, Longway, bilgiye ihtiyacım var ve senin aradığım şeyleri bildiğinden hiç şüphem yok. Soru şu: Bana kolay yoldan mı anlatacaksın, yoksa zor yoldan mı?";
			link.l1.go = "Longway_prisoner_1";			
		break;
		
		case "Longway_prisoner_1":
			dialog.text = "";
			link.l1 = "Sessiz mi kalıyorsun? Peki. Sana bir teklifim var. Hayatını bağışlayıp seni ilk karaya çıkaracağım. Karşılığında bana Lucas Rodenburg'un seni nereye ve neden gönderdiğini anlatacaksın. Anlaştık mı?";
			link.l1.go = "Longway_prisoner_2";			
		break;
		
		case "Longway_prisoner_2":
			dialog.text = "";
			link.l1 = "İngilizce, Hollandaca ve Fransızca bildiğini biliyorum. Dinlemeyi de iyi biliyorsun. Ama artık konuşma zamanı geldi. Sonunda bana bildiğin her şeyi anlatacaksın. Sizin Çinliler işkence sanatınızla övünürsünüz, biliyorum, ama biz Batılılar da bu eski ilimde kendi ilerlemelerimizi kaydettik. Alonso'nun dili çözdürme konusunda ustalığı vardır. Gemime katılmadan önce Santiago'da Kutsal Engizisyon'un sorgucusuydu. İnsanlara itiraf ettirme sanatını mükemmelleştiren kutsal babalardan öğrendiği her türlü numarayı bilir... Protestan olman bile gerekmez!";
			link.l1.go = "Longway_prisoner_3";			
		break;
		
		case "Longway_prisoner_3":
			dialog.text = "";
			link.l1 = "Zekâm senin için boşa harcanıyor. Bana her şeyi anlatacaksın, çekik gözlü dostum... Her şeyi... Ama ondan sonra uzun süre yaşamayacaksın, hayır, yaşamayacaksın. Alonso'yla tanıştıktan sonra bedenin büyük acılar çekecek. Yani seçim senin. Ya bana gerçeğin tamamını anlatır ve yaşarsın, ya da bana gerçeğin tamamını anlatır ve işkence sehpasında acı içinde ölürsün. Acıyla kıvranırsın o sehpanın üstünde. Anladın mı? Merak etme, yanında bir rahip olmasını sağlayacağım, seni vaftiz edip pagan ruhunu cehennemin sonsuz ateşinden kurtarması için.";
			link.l1.go = "Longway_prisoner_4";
		break;
		
		case "Longway_prisoner_4":
			dialog.text = "";
			link.l1 = "Karanlık gözlerinde şüphe büyüyor. Neden efendinin günahları için ölmeyesin? Buna değer mi? Rodenburg gerçekten acı çeken bedeninden ruhunun koparılmasına değecek biri mi?";
			link.l1.go = "Longway_prisoner_5";			
		break;
		
		case "Longway_prisoner_5":
			dialog.text = "Longway konuşacak. Ama önce, Longway senin sözünü tutacağından emin olmak istiyor, chuanzhang.";
			link.l1 = "Ha! Akıllıca sözler! Sana söz veriyorum, delikanlı.";
			link.l1.go = "Longway_prisoner_6";			
		break;
		
		case "Longway_prisoner_6":
			dialog.text = "Üzgünüm, chuanzhang, sözün yeterli değil. Bilgiyi alıp Longway'i sonra öldürürsün! Longway teminat istiyor.";
			link.l1 = "Sıkı pazarlık yapıyorsun. Ne tür garantiler istiyorsun?";
			link.l1.go = "Longway_prisoner_7";			
		break;
		
		case "Longway_prisoner_7":
			dialog.text = "Guadeloupe'un güneyinde küçük bir ada var, Marie Galante. Ulaşılamaz Burun. Longway'i oraya indir ve ona bir silah ver. Ancak o zaman Longway sana Lucas Rodenburg hakkında bildiği her şeyi anlatacak.";
			link.l1 = "Benimle pazarlık edecek durumda değilsin, Çinli.";
			link.l1.go = "Longway_prisoner_8";			
		break;
		
		case "Longway_prisoner_8":
			dialog.text = "Sen de Longway olsaydın aynısını yapardın, chuanzhang. Adamların beni konuşturmakta zorlanırdı, işkence etseler bile. Longway zayıf bir beyaz adam değildir.";
			link.l1 = "Pekala. Anlaştık. Ama seni uyarıyorum – beni kandırmaya kalkma yoksa seni bizzat parça parça doğrarım. Hem de bin bir türlü, yavaş yavaş... tıpkı imparatorların yaptığı gibi. Alonso!";
			link.l1.go = "Longway_prisoner_9";
			// belamour legendary edition -->
			link.l2 = "Doğruyu söylüyorsun. Ama unutma - bu noktaya kadar geldim, senin yüzünden her şeyin mahvolmasına izin vermem. Beni durdurmaya kalkarsan, bir böceği ezmek kadar kolayca hayatına son veririm.";
			link.l2.go = "Longway_prisoner_9a";
		break;
		
		case "Longway_prisoner_9a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_9":
			ChangeCharacterComplexReputation(pchar, "nobility",-5);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_0":
			dialog.text = "Marie Galante'a vardık mı, kaptan?";
			link.l1 = "Sakin ol, yakında orada olacağız.";
			link.l1.go = "exit";
			NextDiag.Tempnode = "Longway_prisoner_0";
		break;
		
		case "Longway_prisoner_10":
			dialog.text = "Sözünü tuttun, chuanzhang. Longway de tutacak. Longway'in görevi hakkında bir şeyler öğrenmek ister misin?";
			link.l1 = "Evet. Ama bana verdiğin sözü hatırlatmama izin ver: Bildiğin *her şeyi* bana anlatacaksın.";
			link.l1.go = "Longway_prisoner_11";			
		break;
		
		case "Longway_prisoner_11":
			dialog.text = "Longway hatırlar. Rodenburg hakkında ne sorarsan sor, cevaplayacaktır, chuanzhang.";
			link.l1 = "Konuşmaya başla.";
			link.l1.go = "Longway_prisoner_12";			
		break;
		
		case "Longway_prisoner_12":
			dialog.text = "'Meifeng', Willemstad limanından kuzeye, St. Christopher kıyılarına doğru yol alıyordu. Beş gün sonra, Peter Stuyvesant'ın komutasında bir kalyon olacaktı. Longway'in emri, bu gemiyi kaptanıyla birlikte batırmaktı.";
			link.l1 = "Tanrı aşkına! Rodenburg sana Stuyvesant'ı öldürmeni mi emretti? Bu delilik!";
			link.l1.go = "Longway_prisoner_13";			
		break;
		
		case "Longway_prisoner_13":
			dialog.text = "Longway doğruyu söylüyor, kaptan. Bu, Bay Rodenburg'un emriydi. Longway bundan hoşlanmadı ama emirlere karşı gelmez.";
			link.l1 = "Ne kadar da Çinliye benziyor. Efendin neyin peşinde?";
			link.l1.go = "Longway_prisoner_14";			
		break;
		
		case "Longway_prisoner_14":
			dialog.text = "Not my master anymore, chuanzhang. Longway is not going to return to Mynheer Rodenburg. Rodenburg has seized power in Curacao. Mathias Beck was easy prey; Rodenburg's authority and connections with the commandant were enough to put the governor in jail\nThe only obstacle left is the West India Company director, Mynheer Stuyvesant. Once Stuyvesant is eliminated, Rodenburg will hold every office of power in the Dutch colonies.";
			link.l1 = "Söylesene Longway, Rodenburg gibi saygın ve güçlü bir adamı, kendi şirketine ve cumhuriyetine karşı böylesine radikal adımlar atmaya iten neydi? Ve sakın bana güneş çarpması ya da bir delilik nöbeti deme.";
			link.l1.go = "Longway_prisoner_15";			
		break;
		
		case "Longway_prisoner_15":
			dialog.text = "Longway bunu bizzat senden duymak istedi, chuanzhang. Şirketin posta gemisini ele geçirip mektubu Rodenburg’a getiren sendin, değil mi? Sebep o mektubun içindeydi.";
			link.l1 = "Şimdi anlıyorum... Görünen o ki, John Murdock'un arşivinde Rodenburg'u kendi ülkesine karşı isyan başlatacak kadar korkutacak pek çok dikkat çekici şey var.";
			link.l1.go = "Longway_prisoner_16";			
		break;
		
		case "Longway_prisoner_16":
			dialog.text = "Başka bir şey öğrenmek ister misiniz, kaptan?";
			link.l1 = "Evet. Rodenburg başka ne yaptı?";
			link.l1.go = "Longway_prisoner_17";			
		break;
		
		case "Longway_prisoner_17":
			dialog.text = "Mynheer Rodenburg ölümünü emretti. Longway, Stuyvesant'ın peşine düşmeden önce Caracas'taydı, Chuanzhang Jacob ile buluştu ve ona talimatlar verdi.";
			link.l1 = "Kaptan Jacob van Berg?";
			link.l1.go = "Longway_prisoner_18";			
		break;
		
		case "Longway_prisoner_18":
			dialog.text = "İyi bilgilendirilmişsiniz. Evet. Chuanzhang Jacob van Berg sizi arıyor, kaptan. Sonunda sizi bulacak. Hiç kimse van Berg'den uzun süre saklanamaz.";
			link.l1 = "Eğer kanıyorsa, onu öldürebilirim. Van Berg ve o meşhur hayalet gemisiyle ben ilgileneceğim.";
			link.l1.go = "Longway_prisoner_19";			
		break;
		
		case "Longway_prisoner_19":
			dialog.text = "Çok şey biliyorsun, chuanzhang. Longway'in ekleyeceği bir şey yok. Soracak başka bir şeyin varsa sor.";
			link.l1 = "Stuyvesant, St. Christopher kıyılarına yakın olacak mı?";
			link.l1.go = "Longway_prisoner_20";			
		break;
		
		case "Longway_prisoner_20":
			dialog.text = "Evet, chuanzhang. Onun kalyonunu yaklaşık bir hafta sonra bu adanın kıyılarında bulabileceksiniz.";
			link.l1 = "Güzel! Bu tilkiyi kendi tuzağında yakalayalım... Başka sorum yok. Bilmek istediğim her şeyi öğrendim.";
			link.l1.go = "Longway_prisoner_21";			
		break;
		
		case "Longway_prisoner_21":
			dialog.text = "Son bir tavsiye daha, chuanzhang. Eğer kalyona saldırıya uğramadan yaklaşmak istiyorsan, 'Meifeng'i mutlaka yanına almalısın.";
			link.l1 = "Anladım. Bilgi için teşekkür ederim.";
			link.l1.go = "Longway_prisoner_22";			
		break;
		
		case "Longway_prisoner_22":
			dialog.text = "Longway şimdi gidiyor. Elveda, chuanzhang.";
			link.l1 = "Yolun açık olsun, Doğulu dostum.";
			link.l1.go = "Longway_prisoner_23";			
		break;
		
		case "Longway_prisoner_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "ReturnShoreToNormal", -1);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-49");
			pchar.questTemp.HWIC.Self = "MeetingStivesant";
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Nevis";
			pchar.quest.Seek_Piter.function = "CreatePiterHalleon";
			pchar.quest.RemoveLongwayTimer.over = "yes";//снять прерывание
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 8, false); // таймер
			AddMapQuestMarkIsland("Nevis", true);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Longway_officer":
			dialog.text = "Dikkatle dinliyorum, kaptan.";
			// Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "¿Cuáles son las órdenes, señor capitán?";
				Link.l1 = ""+npchar.name+", he decidido viajar a Europa — a casa de mi padre. El camino no será fácil, y no tengo idea de cuándo podré regresar. Parece que ha llegado el momento de separarnos. Dudo que quieras esperarme aquí — y tampoco sería seguro.";
				Link.l1.go = "SharlieEpilog_Longway_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Longway, Tayasal adlı eski bir Kızılderili şehrine gidiyorum. Açık konuşayım, bu gerçekten tehlikeli ve aynı zamanda gizemli bir yolculuk olacak – oraya bir teleport idolüyle ulaşacağız. Sen... bana katılır mısın?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Longway, bana gemiyle ilgili tam bir rapor ver.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Her limana yanaştığımızda belirli malları satın almanı istiyorum.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Emriniz üzerine geldim, Kaptan.";
				Link.l2 = "Sana birkaç emir vermem gerekiyor.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Longway_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Emrimi dinle!";
            Link.l1.go = "stay_follow";
			link.l2 = "Hiçbir şey. Gidebilirsin!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Longway_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Longway hiçbir zaman gemi katibi olmadı, chuanzhang. Longway sana Trinidad'dan Havana'ya nasıl gidileceğini ve ne kadar süreceğini söyleyebilir. Ama Longway asla yük, satış ya da ticaret hesabı yapmaz.";
			Link.l1 = "Sanırım haklısın. Böyle yetenekli bir rotacıyı harcamak yazık olurdu.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Longway, gwailo ile ticaret yapmaz, chuanzhang. Longway her zaman dümenin başında olmuştur, eski kancaburun son sekizliği pazarlık ederken dükkânda değil.";
			link.l1 = "Hm, haklısın. Muhtemelen tüccarları korkuturdun.";
			link.l1.go = "exit";
		break;

		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Dinliyorum.";
			Link.l1 = "Hadi gemiye çıkmayı konuşalım.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Geminiz hakkında konuşalım.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "Bir süreliğine filomdan ayrılıp kendi şansını denemeni istiyorum.";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Şimdilik bir şey yok.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "Dileğiniz nedir?";
			Link.l1 = "Düşman gemilerine çıkma. Kendine ve mürettebata dikkat et.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Düşman gemilerine saldırgan bir şekilde çıkmanı istiyorum.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "Dileğin nedir?";
			Link.l1 = "Gemiyi ele geçirdikten sonra başka bir gemiyle değiştirme. O çok değerli.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Düşman gemilerine bindiğinde, eğer düzgünlerse onları kendine alabilirsin.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Aye aye.";
			Link.l1 = "Rahat ol.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Yapılacak.";
			Link.l1 = "Rahat ol.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Aye aye.";
			Link.l1 = "Yapılacak.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Bu iş tamamdır.";
			Link.l1 = "Rahat ol.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		case "stay_follow":
            dialog.Text = "Emirleriniz nedir, kaptan?";
            Link.l1 = "Sıkı dur!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Beni takip et ve yetiş!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Ateşli silahlarınız için cephane türünü değiştirin.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Tüfeğinizin mühimmat türünü değiştirin.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "Yakın dövüş için ana silahını değiştir.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "Düşmana belirli bir mesafeden ateş etmeni istiyorum, Lonway.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Mühimmat türünü seçme:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;

		case "SetMusketBullets":
			Dialog.Text = "Mühimmat türünü seç:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Savaşın başında şunları kullanacaksın:";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Musket";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Bir tutum değişikliği var!";
            Link.l1 = "Serbestsin.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Bir değişiklik var!";
            Link.l1 = "Serbestsin.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "Peki, o mesafe ne kadar olacak? Unutmayın Kaptanım, yirmi metreden uzağa tüfekle ateş edemezsiniz.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Ne demek istiyorsunuz, Kaptanım?";
				link.l1 = "Affedersin, bazen şaka kaldırmadığını unutuyorum.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Yerimi koruyup fazla yaklaşan düşmana ateş açacağım. Bunu mu istiyorsun?";
				link.l1 = "Evet, aynen öyle, Lonway.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Bu çok uzak, Kaptanım. Kalabalığa isabet ettirebilirsiniz, ama tek bir hedefi vurmak - imkânsız.";
				link.l1 = "Denemeye değer olabilir, peki öyle olsun.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Anladım, Kaptanım.";
			link.l1 = "Mükemmel.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Longway seni uzun zamandır takip ediyor. Longway her zamanki gibi seni takip edecek. Longway chuanzhang'ını asla bırakmaz.";
			link.l1 = "Teşekkür ederim, Longway! Senin hakkında yanılmadığıma sevindim.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Ne zaman başlayacağız?";
			link.l1 = "Biraz sonra. Buna hazırlanmamız gerekiyor.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "24");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// Эпилог
		case "SharlieEpilog_Longway_1":
			dialog.text = ""+npchar.name+" pensar que él es amigo del gran capitán. Yo listo para seguirte a donde sea — incluso a Europa, si hace falta.";
			link.l1 = "¿Pero recuerdas cómo tratan aquí a los forasteros como tú? En Europa es aún peor. Claro que no permitiré que te hagan daño — pero no podré protegerte de las miradas ni de las burlas. Por eso no puedo darte una orden — debes decidir tú: ¿vienes conmigo o...";
			link.l1.go = "SharlieEpilog_Longway_2";
		break;

		case "SharlieEpilog_Longway_2":
			dialog.text = ""+npchar.name+" acostumbrado a ese trato. Después de la muerte de Chang Shin, el capitán fue el único que importó a Longway. Yo seguirte y cuidar tu espalda.";
			link.l1 = "Bueno... Aprecio tu lealtad, amigo mío, y me alegra de corazón que estés conmigo. Sabes, hasta te envidio un poco. Has visto China, el Caribe — y ahora verás Europa. Pocos han recorrido un camino tan largo... El nombre que te dio Van Marden resultó profético.";
			link.l1.go = "SharlieEpilog_Longway_3";
		break;

		case "SharlieEpilog_Longway_3":
			dialog.text = "...";
			link.l1 = "Zarpamos en dos semanas. Antes de eso, quiero celebrarlo debidamente en la taberna. Estás invitado. Y que conste — no se aceptan negativas.";
			link.l1.go = "SharlieEpilog_Longway_4";
		break;

		case "SharlieEpilog_Longway_4":
			dialog.text = ""+npchar.name+" no pensar en rechazar. Yo venir, señor capitán.";
			link.l1 = "No esperaba otra respuesta. Te avisaré cuando empiece la fiesta. Primero tengo que ocuparme de lo demás.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Longway_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Longway = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;
	}
}

string SelectJacobCity()
{
	string sTemp;
	switch (hrand(4))
	{
		case 0: sTemp = "Cumana" break;
		case 1: sTemp = "Caracas" break;
		case 2: sTemp = "Maracaibo" break;
		case 3: sTemp = "Cartahena" break;
		case 4: sTemp = "Portobello" break;
	}
	return sTemp;
}
